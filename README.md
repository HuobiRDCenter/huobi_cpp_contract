# Huobi Cpp SDK For Contracts (v3 + v5)

This is Huobi Cpp SDK for contracts, you can import to your project and use this SDK to query all market data, trading and manage your account. The SDK supports RESTful API invoking, and subscribing the market, account and order update from the WebSocket connection.

The SDK provides two interface groups:

| 接口组 | 说明 | 入口 |
|---|---|---|
| **v5（新增，推荐）** | HTX 合约 V5，统一/多资产保证金账户可用，55 个接口（REST 43 + WS 12） | `AccountClient` / `OrderClient` / `MarketClient`（V5 方法）、`AlgoClient`、`WSSwapNotificationClient`、`WSSwapTradeClient` |
| **v3（历史）** | 老 `linear-swap-api` / coin futures / coin swap 接口 | 见 [Client](#Client) 表 |

> v5 接口清单、逐接口文档链接、测试方法与实测状态见 [docs/v5-interface-list.md](docs/v5-interface-list.md)。老 v3 接口在统一/多资产保证金账户下会返回 6002/1051/1066，新业务建议直接用 v5。

If you already use SDK v1 or v2, it is strongly suggested migrate to v3 as we refactor the implementation to make it simpler and easy to maintain. The SDK v3 is completely consistent with the API documentation of the new HTX open platform. Compared to SDK versions v1 and v2, due to changes in parameters of many interfaces, in order to match the latest interface parameter situation, v3 version has made adjustments to parameters of more than 80 interfaces to ensure that requests can be correctly initiated and accurate response data can be obtained. Meanwhile, the v3 version has added over 130 new interfaces available for use, greatly expanding the number of available interfaces.

## Table of Contents

- [Quick Start](#Quick-Start)

- [V5 API](#V5-API)

  - [V5 REST](#V5-REST)
  - [V5 WebSocket](#V5-WebSocket)
  - [Build & Test](#Build--Test)

- [Usage](#Usage)

  - [Configuration](#Configuration)
  - [Folder structure](#Folder-Structure)
  - [Client](#Client)
  - [Response](#Response)

- [Request examples](#Request-examples)

  - [Market data](#Market-data)

- [Subscription examples](#Subscription-examples)

  - [Subscribe trade update](#Subscribe-trade-update)



## Quick Start

The SDK is run and test in C++ 17, you can import the source code after dowload it.

The folder **huobi_futures** is SDK API code source as interface library.
The folder **test** is a unit test what you can find usage of each API interface in.

If you want to create your own application, you can follow below steps:

* Create a client (xxxClient/WSxxxClient) instance.
* Call the method of client instance.

```cpp
// RESTful api
AccountClient acClient("AccessKey", "SecretKey");
auto result = acClient.IsolatedGetAccountInfo("BTC-USDT"); // isolated margin
for (auto item : result->data.value())
{
    //LOG(INFO) << item.symbol.value() << ":" << item.margin_balance;
}

result = acClient.CrossGetAccountInfo("USDT"); // cross margin
EXPECT_EQ(result->err_code.has_value(), false);
for (auto item : result->data.value())
{
    for (auto ct : item.contract_detail.value())
    {
        //LOG(INFO) << ct.contract_code << ":" << ct.margin_available;
    }
}

// websocker api
WSMarketClient ws;
ws.SubKLine("BTC-USDT", "1min", [](const SubKLineResponse &data) {
    //LOG(INFO) << data.tick.close;
});
ws.RunForever();
```

## V5 API

v5 接口共 **55 个**（REST 43 + WS 12），已在真实账户上实测通过；逐接口文档链接、C++ 测试方法与验证强度见 [docs/v5-interface-list.md](docs/v5-interface-list.md)。

### V5 REST

```cpp
#include "huobi_futures/linear_swap/restful/MarketClient.hpp"
#include "huobi_futures/linear_swap/restful/AccountClient.hpp"
#include "huobi_futures/linear_swap/restful/OrderClient.hpp"
#include "huobi_futures/linear_swap/restful/AlgoClient.hpp"

using huobi_futures::linear_swap::restful::MarketClient;
using huobi_futures::linear_swap::restful::AccountClient;
using huobi_futures::linear_swap::restful::OrderClient;
using huobi_futures::linear_swap::restful::AlgoClient;

// 公开行情：无需 key。V5 market 方法统一带 Market 前缀，避免与 v3 同名重载歧义
MarketClient market;
auto risk  = market.GetMarketRiskLimit("BTC-USDT");     // GET  /v5/market/risk/limit
auto limit = market.GetMarketPriceLimit("BTC-USDT");    // GET  /v5/market/price_limit
auto oi    = market.GetMarketOpenInterest("BTC-USDT");  // GET  /v5/market/open_interest

// 账户：私有，需 key
AccountClient account("AccessKey", "SecretKey");
auto balance = account.SwapAccountBalance();                              // GET  /v5/account/balance
auto mode    = account.GetAssetMode();                                    // GET  /v5/account/asset_mode
auto bills   = account.SwapGetAccountBills("BTC-USDT", "cross");          // GET  /v5/account/bills

// 交易 / 持仓：私有，需 key
OrderClient trade("AccessKey", "SecretKey");
auto opens  = trade.TradeOrderOpens("BTC-USDT", "cross");                 // GET  /v5/trade/order/opens
auto order  = trade.GetTradeOrder("BTC-USDT", "cross", "order_id");       // GET  /v5/trade/order
auto cancel = trade.CancelTradeOrder("BTC-USDT", "order_id");             // POST /v5/trade/cancel_order
auto lever  = trade.PositionLever("BTC-USDT", "cross", "long");           // GET  /v5/position/lever

// 策略委托：私有，需 key
AlgoClient algo("AccessKey", "SecretKey");
auto algoOpen = algo.AlgoQueryOpenOrders("trigger", "BTC-USDT");          // GET  /v5/algo/order/opens
```

响应统一为 `code` / `message` / `data`，先判 `code == 200` 再读 `data`（`data` 可能是数组、单对象或 null，按接口文档处理）。

### V5 WebSocket

推送订阅（7 个 topic：`orders` / `trade` / `trade_detail` / `positions` / `account` / `match_orders` / `algo_orders`）：

```cpp
#include "huobi_futures/linear_swap/ws/WSSwapNotificationClient.hpp"
using huobi_futures::linear_swap::ws::WSSwapNotificationClient;

WSSwapNotificationClient ws("AccessKey", "SecretKey");   // host 默认 api.hbdm.com
ws.Connect();                                            // 连接后自动鉴权
ws.Sub({"orders", "positions"}, "BTC-USDT", [](const std::string &msg) {
    // msg 为原始推送帧：{"op":"notify","topic":"orders","data":[...]}
});
// 用完调用 ws.Disconnect()（析构也会断开）
```

交易（5 个 op，应答帧无 op 字段，按 `cid` 与请求关联）：

```cpp
#include "huobi_futures/linear_swap/ws/WSSwapTradeClient.hpp"
using huobi_futures::linear_swap::ws::WSSwapTradeClient;

WSSwapTradeClient wsTrade("AccessKey", "SecretKey");
wsTrade.Connect([](const std::string &msg) {
    // {"op":"auth","err-code":0} 或 {"code":200,"cid":"1","data":{...}}
});
std::string cid = wsTrade.PlaceOrder(R"({"contract_code":"BTC-USDT","margin_mode":"cross","position_side":"long","side":"buy","type":"limit","price":"10000","volume":"1"})");
wsTrade.CancelOrder(R"({"contract_code":"BTC-USDT","order_id":"order_id"})");
// 用完调用 wsTrade.Disconnect()
```

> 注意：`Connect` 返回时只完成 WS 握手，鉴权是异步的；实际使用应先等回调收到 `{"op":"auth","err-code":0}` 再发下单/撤单指令（测试用例即如此，见 `test/v5_ws_trade_test.hpp`）。

### Build & Test

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j8      # SDK + example + v5_example + v5_test + v5_ws_test
./build/example/v5_example   # 最小示例：公开行情可直接跑；账户/交易需 env key
./build/test/v5_test         # REST 42 用例；私有接口需 env: HTX_ACCESS_KEY / HTX_SECRET_KEY
./build/test/v5_ws_test      # WS 17 用例（含 5 个离线 sanity）

./build/test/v5_test --gtest_filter='V5Market.*'    # 只跑公开接口，无需 key
```

> 老 v3 测试 target 依赖的 TriggerOrderClient / 老 DTO 存在存量语法错误，已设为 `EXCLUDE_FROM_ALL`，默认构建不包含；显式 `cmake --build build --target test` 目前仍会失败，与 v5 无关。
> 本机直连 `api.hbdm.com` 不通时，跑测试前 `export https_proxy=http://127.0.0.1:7897 http_proxy=http://127.0.0.1:7897`。

## Usage

### Configuration

The client Init function must set AccessKey/SecretKey two value when you access private data. And it not need to set AccessKey/SecretKey value when you access public data such as market data.

You can create config.hpp in your application for config AccessKey/SecretKey and other input data.

```cpp
#include <string>
using std::string;

#include <map>
using std::map;
using std::pair;

map<string, string> config;

void init_config()
{
    config.insert(pair<string,string>("Host", "api.hbdm.com"));
    config.insert(pair<string,string>("AccessKey", "x-x-x-x"));
    config.insert(pair<string,string>("SecretKey", "x-x-x-x"));
    config.insert(pair<string,string>("AccountId", "10000000"));
    config.insert(pair<string,string>("SubUid", "10000000"));
}
```

And use it as follow:

```cpp
#include "config.hpp"

extern map<string, string> config;
init_config();

accessKey := config["AccessKey"];
secretKey := config["SecretKey"];
```

### Folder Structure

This is the folder and namespace structure of SDK source code and the description

- **huobi_futures**: The SDK API lib
  - **linear_swap**: the linear swap api src inclue RESTful and websocket
  - **coin_futures**: the coin futures api src inclue RESTful and websocket
  - **coin_swap**: the coin swap api src inclue RESTful and websocket
  - **json_struct**: json string to class object class
  - **nlohmann_json**: string to json object
  - **url_base**: wrap curl lib as class
  - **wsbase**: wrap libwebsockets lib as class
  - **utils**: utils class such as signer and gzip decompress
- **test**: The unit test project
  - **xxx_test.hpp**: The google cpp unit test file
  - **v5_*_test.hpp**: V5 接口测试（REST: `v5_restful_*`，WS: `v5_ws_*`），入口 `v5_main.cpp` / `v5_ws_main.cpp`

You can find all demo in xxx_test.hpp to get/sub private/public data

### Client

In this SDK, the client is the object to access the Huobi API. All the client are listed in below table. Each client is very small and simple.

| Access Type | Client         | Privacy        | Data Category             |
| ----------- | -------------- | -------------- | ------------------------- |
| RESTful     | AccountClient  | Private        | account info              |
|             | MarketClient   | Public         | market info               |
|             | OrderClient    | Private        | about order               |
|    | ReferenceClient | Public         | basic info               |
|    | TransferClient | Public         | transfer info               |
|    | TriggerOrderClient | Public         | about trigger order               |
|    | UnifiedAccountClient | Public         | unified account info              |
| Websocket   | WSMarketClinet | Public         | market info               |
|             | WSNotifyClinet | Public/Private | market info/ account info |
|             | WSIndexClinet | Public/Private | index info |
|             | WSSystemClinet | Public/Private | system info |
| RESTful (v5) | AccountClient | Private        | V5 account: balance/asset_mode/fee/bills |
|             | OrderClient    | Private        | V5 trade + position |
|             | MarketClient   | Public         | V5 market（`GetMarket*` 方法） |
|             | AlgoClient     | Private        | V5 algo strategy orders |
| Websocket (v5) | WSSwapNotificationClient | Private | V5 推送：orders/trade/trade_detail/positions/account/match_orders/algo_orders |
|             | WSSwapTradeClient | Private     | V5 WS 交易：place/cancel order |


#### Public vs. Private

There are two types of privacy that is correspondent with privacy of API:

**Public client**: It invokes public API to get public data (Common data and Market data), therefore you can create a new instance without applying an API Key.

```cpp
MarketClient mkClient;
auto result = mkClient.GetContractInfo();
```

**Private client**: It invokes private API to access private data, you need to follow the API document to apply an API Key first, and pass the API Key to the Init.

```cpp
AccountClient acClient("AccessKey", "SecretKey");
auto result = acClient.IsolatedGetAccountInfo("BTC-USDT");
```

The API key is used for authentication. If the authentication cannot pass, the invoking of private interface will fail.

#### Rest vs. WebSocket

**Rest Client**: It invokes Rest API and get once-off response.

```cpp
AccountClient acClient("AccessKey", "SecretKey");
auto result = acClient.IsolatedGetAccountInfo("BTC-USDT");
```

**WebSocket Client**: It establishes WebSocket connection with server and data will be pushed from server actively. There are two types of method for WebSocket client:

- Request method: The method name starts with "Req", it will receive the once-off data after sending the request.
- Subscription: The method name starts with "Sub", it will receive update after sending the subscription.

```cpp
WSMarketClient ws;
ws.SubKLine("BTC-USDT", "1min", [](const SubKLineResponse &data) {
    //LOG(INFO) << data.tick.close;
});
ws.RunForever();

// other process
WSMarketClient ws;
ws.ReqKLine("BTC-USDT", "1min", 1608727852, 1608727882, [](const ReqKLineResponse &data) {
    for (auto item : data.data)
    {
        //LOG(INFO) << item.close;
    }
});
ws.RunForever();
```

#### Custom host

Each client Init support an optional host parameter, by default it is "api.hbdm.com". If you need to use different host, you can specify the custom host.

```cpp
AccountClient acClient("AccessKey", "SecretKey", "Host");
auto result = acClient.IsolatedGetAccountInfo("BTC-USDT");

WSMarketClient ws("Host");
ws.SubKLine("BTC-USDT", "1min", [](const SubKLineResponse &data) {
    LOG(INFO) << data.tick.close;
});
ws.RunForever();
```

### Response

All response data are defined as follow:

- **huobi_futures/linear_swap/restful/response/xxx.hpp**: all RESTful response data
- **huobi_futures/linear_swap/ws/response/xxx.hpp**: all websockt response data
- **huobi_futures/coin_futures/restful/response/xxx.hpp**: all RESTful response data
- **huobi_futures/coin_futures/ws/response/xxx.hpp**: all websockt response data
- **huobi_futures/coin_swap/restful/response/xxx.hpp**: all RESTful response data
- **huobi_futures/coin_swap/ws/response/xxx.hpp**: all websockt response data

## Request Examples

### Market data

```cpp
MarketClient mkClient;
auto result = mkClient.GetContractInfo();
//LOG(INFO) << result->data.value().data()->contract_code;
```

## Subscription Examples

### Subscribe trade update

```cpp
NotifyClient ws("AccessKey", "SecretKey");
ws.IsolatedSubPositions("XRP-USDT", [](const SubPositionsResponse &data) {
    for (auto item : data.data)
    {
        //LOG(INFO) << item.contract_code << ":" << item.direction << "/" << item.volume << "/" << item.margin_mode;
    }
});
```
