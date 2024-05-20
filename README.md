# Huobi Cpp SDK For Contracts v3

This is Huobi Cpp SDK v3, you can import to your project and use this SDK to query all market data, trading and manage your account. The SDK supports RESTful API invoking, and subscribing the market, account and order update from the WebSocket connection.

If you already use SDK v1 or v2, it is strongly suggested migrate to v3 as we refactor the implementation to make it simpler and easy to maintain. The SDK v3 is completely consistent with the API documentation of the new HTX open platform. Compared to SDK versions v1 and v2, due to changes in parameters of many interfaces, in order to match the latest interface parameter situation, v3 version has made adjustments to parameters of more than 80 interfaces to ensure that requests can be correctly initiated and accurate response data can be obtained. Meanwhile, the v3 version has added over 130 new interfaces available for use, greatly expanding the number of available interfaces.

## Table of Contents

- [Quick Start](#Quick-Start)

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