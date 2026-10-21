# HTX 合约 V5 C++ SDK 使用说明

本文面向使用 C++ SDK 开发 HTX 合约 V5 接口的客户，列出本次交付范围内的 **55 项操作：43 个 REST 操作和 12 个 WebSocket 操作**，并指出对应的 SDK 类、示例与测试入口。

## 如何开始

- SDK 使用 **C++17**，构建系统为 CMake。
- 最小可运行示例在 [`example/v5_example.cpp`](../example/v5_example.cpp)，包含公开行情查询，以及配置 API 凭证后进行的账户和委托查询。
- [`README.md`](../README.md) 的 **V5 REST** 和 **V5 WebSocket** 章节提供更多调用示例；参数和返回结构请结合对应头文件及 HTX OpenD 接口说明使用。
- 编译并运行示例：

  ```bash
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
  cmake --build build -j8
  ./build/example/v5_example
  ```

公开行情接口无需 API 凭证。账户、交易、策略单和私有 WebSocket 接口需要具备相应权限的 Access Key 和 Secret Key；请从环境或安全配置读取凭证，不要将凭证写入源码。

REST 客户端方法返回响应对象；调用方应先检查响应对象存在且 `code == 200`，再按响应类型检查 `data`。`data` 可能是可选字段、数组或单个对象。WebSocket 推送的回调参数是原始 JSON 帧；交易请求返回的 `cid` 用于关联应答。WebSocket 鉴权为异步过程，收到鉴权成功应答后再发送交易请求。

## 55 项接口与 SDK 入口

下表按交付清单编号。REST 参数和响应类型定义在对应客户端头文件中；WebSocket 通知共享 `Sub` 入口，WebSocket 交易共享同一交易客户端。

### REST 账户（6 项）

| # | HTTP 接口 | SDK 方法 |
|---:|---|---|
| 1 | [`GET /v5/account/balance`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-195703a12d5) | `AccountClient::SwapAccountBalance` |
| 2 | [`POST /v5/account/asset_mode`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957dd1a995) | `AccountClient::SetAssetMode` |
| 3 | [`GET /v5/account/asset_mode`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957dd37de0) | `AccountClient::GetAssetMode` |
| 4 | [`POST /v5/account/fee_deduction_currency`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-198826314c7) | `AccountClient::FeeDeductionCurrency` |
| 5 | [`GET /v5/account/fee_deduction_currency`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b723f5241) | `AccountClient::GetFeeDeductionCurrency` |
| 6 | [`GET /v5/account/bills`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b724157a2) | `AccountClient::SwapGetAccountBills` |

### REST 交易（13 项）

| # | HTTP 接口 | SDK 方法 |
|---:|---|---|
| 7 | [`POST /v5/trade/order`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957dd521e6) | `OrderClient::TradeOrder` |
| 8 | [`POST /v5/trade/batch_orders`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957de4ff8f) | `OrderClient::TradeBatchOrders` |
| 9 | [`POST /v5/trade/cancel_order`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957defffc6) | `OrderClient::CancelTradeOrder` |
| 10 | [`POST /v5/trade/cancel_batch_orders`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957df2abbe) | `OrderClient::CancelTradeBatchOrders` |
| 11 | [`POST /v5/trade/cancel_all_orders`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957df6feb3) | `OrderClient::CancelAllOrders` |
| 12 | [`POST /v5/trade/position`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957e02b018) | `OrderClient::TradePosition` |
| 13 | [`POST /v5/trade/position_all`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957e05d40c) | `OrderClient::TradePositionAll` |
| 14 | [`GET /v5/trade/order/opens`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957e082f23) | `OrderClient::TradeOrderOpens` |
| 15 | [`GET /v5/trade/order/details`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957e2a0e6a) | `OrderClient::TradeOrderDetails` |
| 16 | [`GET /v5/trade/order/history`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957efb2139) | `OrderClient::TradeOrderHistory` |
| 17 | [`GET /v5/trade/order`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-196a35af40e) | `OrderClient::GetTradeOrder` |
| 18 | [`POST /v5/trade/cancel-after`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b72307cbb) | `OrderClient::TradeCancelAfter` |
| 19 | [`GET /v5/trade/position/opens`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957f1fbee4) | `OrderClient::TradePositionOpens` |

### REST 持仓（7 项）

| # | HTTP 接口 | SDK 方法 |
|---:|---|---|
| 20 | [`GET /v5/position/lever`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957f316730) | `OrderClient::PositionLever` |
| 21 | [`POST /v5/position/lever`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957f4a3b67) | `OrderClient::SetPositionLever` |
| 22 | [`GET /v5/position/mode`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957f4d93fd) | `OrderClient::PositionMode` |
| 23 | [`POST /v5/position/mode`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957f4ec40b) | `OrderClient::SetPositionMode` |
| 24 | [`GET /v5/position/risk/limit`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957f50bd39) | `OrderClient::PositionRiskLimit` |
| 25 | [`GET /v5/position/risk/limit_tier`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b4528fc88) | `OrderClient::PositionRiskLimitTier` |
| 26 | [`POST /v5/position/margin`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b7247e4dd) | `OrderClient::PositionMargin` |

### REST 行情（12 项，公开）

| # | HTTP 接口 | SDK 方法 |
|---:|---|---|
| 27 | [`GET /v5/market/risk/limit`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-195809dc1e8) | `MarketClient::GetMarketRiskLimit` |
| 28 | [`GET /v5/market/assets_deduction_currency`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19580a209a2) | `MarketClient::GetAssetsDeductionCurrency` |
| 29 | [`GET /v5/market/multi_assets_margin`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19580a32ea2) | `MarketClient::GetMultiAssetsMarginList` |
| 30 | [`GET /v5/market/funding_rate`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b738520e0) | `MarketClient::GetMarketFundingRate` |
| 31 | [`GET /v5/market/funding_rate_history`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b7389e8ee) | `MarketClient::GetFundingRateHistory` |
| 32 | [`GET /v5/market/open_interest`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73998b8f) | `MarketClient::GetMarketOpenInterest` |
| 33 | [`GET /v5/market/price_limit`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73a247e7) | `MarketClient::GetMarketPriceLimit` |
| 34 | [`GET /v5/market/liquidation_orders`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73ab3d66) | `MarketClient::GetMarketLiquidationOrders` |
| 35 | [`GET /v5/market/settlement_history`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73b16e57) | `MarketClient::GetSettlementHistory` |
| 36 | [`GET /v5/market/elite_account_ratio`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73bd8472) | `MarketClient::GetMarketEliteAccountRatio` |
| 37 | [`GET /v5/market/elite_position_ratio`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73c012ca) | `MarketClient::GetMarketElitePositionRatio` |
| 38 | [`GET /v5/market/estimated_settlement_price`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73c587fc) | `MarketClient::GetMarketEstimatedSettlementPrice` |

### REST 策略委托（5 项）

| # | HTTP 接口 | SDK 方法 |
|---:|---|---|
| 39 | [`POST /v5/algo/order`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b72756dd7) | `AlgoClient::AlgoOrder` |
| 40 | [`POST /v5/algo/cancel_orders`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73242ab0) | `AlgoClient::AlgoCancelOrders` |
| 41 | [`GET /v5/algo/order`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73278ea1) | `AlgoClient::AlgoQueryOrders` |
| 42 | [`GET /v5/algo/order/opens`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b7345a20e) | `AlgoClient::AlgoQueryOpenOrders` |
| 43 | [`GET /v5/algo/order/history`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b7361ac19) | `AlgoClient::AlgoQueryOrderHistory` |

### WebSocket 推送（7 项）

连接地址为 `wss://api.hbdm.com/ws/v5/notification`。以下 topic 均通过 `WSSwapNotificationClient::Sub` 订阅。

| # | Topic | SDK 入口 |
|---:|---|---|
| 44 | [`orders`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19580a58ac9) | `WSSwapNotificationClient::Sub` |
| 45 | [`trade`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19582b9e8db) | `WSSwapNotificationClient::Sub` |
| 46 | [`trade_detail`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19f3fb0ed2d) | `WSSwapNotificationClient::Sub` |
| 47 | [`positions`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19582def41f) | `WSSwapNotificationClient::Sub` |
| 48 | [`account`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19583056529) | `WSSwapNotificationClient::Sub` |
| 49 | [`match_orders`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19710f62bf5) | `WSSwapNotificationClient::Sub` |
| 50 | [`algo_orders`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b981e8c47) | `WSSwapNotificationClient::Sub` |

### WebSocket 交易（5 项）

连接地址为 `wss://api.hbdm.com/linear-swap-trade`。请求数据按 HTX V5 格式传入 JSON 字符串；批量下单和批量撤单的数据为 JSON 数组。

| # | 操作 | SDK 方法 |
|---:|---|---|
| 51 | [`place_order`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-196a85f248b) | `WSSwapTradeClient::PlaceOrder` |
| 52 | [`place_batch_orders`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-196a951ac2c) | `WSSwapTradeClient::PlaceBatchOrders` |
| 53 | [`cancel_order`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-196a96db3fa) | `WSSwapTradeClient::CancelOrder` |
| 54 | [`cancel_batch_orders`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-196a97b35b6) | `WSSwapTradeClient::CancelBatchOrders` |
| 55 | [`cancel_all_orders`](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-196a98d805e) | `WSSwapTradeClient::CancelAllOrders` |

## 源码、示例与测试位置

| 内容 | 位置 |
|---|---|
| REST 账户、交易、行情、策略委托客户端 | [`AccountClient.hpp`](../huobi_futures/linear_swap/restful/AccountClient.hpp)、[`OrderClient.hpp`](../huobi_futures/linear_swap/restful/OrderClient.hpp)、[`MarketClient.hpp`](../huobi_futures/linear_swap/restful/MarketClient.hpp)、[`AlgoClient.hpp`](../huobi_futures/linear_swap/restful/AlgoClient.hpp) |
| WebSocket 推送与交易客户端 | [`WSSwapNotificationClient.hpp`](../huobi_futures/linear_swap/ws/WSSwapNotificationClient.hpp)、[`WSSwapTradeClient.hpp`](../huobi_futures/linear_swap/ws/WSSwapTradeClient.hpp) |
| REST 路径常量 | [`const_val.hpp`](../huobi_futures/utils/const_val.hpp) |
| 可运行的 C++ V5 示例 | [`example/v5_example.cpp`](../example/v5_example.cpp)；构建后运行 `build/example/v5_example` |
| REST 回归用例及入口 | [`v5_restful_account_market_test.hpp`](../test/v5_restful_account_market_test.hpp)、[`v5_restful_trade_position_test.hpp`](../test/v5_restful_trade_position_test.hpp)、[`v5_restful_algo_test.hpp`](../test/v5_restful_algo_test.hpp)、[`v5_main.cpp`](../test/v5_main.cpp)；target 为 `v5_test` |
| WebSocket 回归用例及入口 | [`v5_ws_notify_test.hpp`](../test/v5_ws_notify_test.hpp)、[`v5_ws_trade_test.hpp`](../test/v5_ws_trade_test.hpp)、[`v5_ws_sanity_test.hpp`](../test/v5_ws_sanity_test.hpp)、[`v5_ws_main.cpp`](../test/v5_ws_main.cpp)；target 为 `v5_ws_test` |

## 回归覆盖说明

按上述 55 项交付范围，所有 REST 和 WebSocket 操作均已纳入最终代码回归。最终回归连续执行 **5 轮 REST 和 5 轮 WebSocket**：每轮 REST 测试 50/50 通过，每轮 WebSocket 测试 25/25 通过，无失败或跳过。测试用例总数包含额外的错误响应防护、清理保护和离线解析检查；`POST /v5/trade/cancel_order` 通过下单用例的撤单清理步骤调用，不单独占一个测试用例。

部分改变账户状态的接口按当前账户状态和业务可接受返回进行验证；测试通过表示对应回归断言通过，不代表任何账户状态下都一定返回 `code == 200`。请以 HTX OpenD 最新参数要求、权限要求和业务前置条件为准。

**范围提示：** SDK 还保留 `AccountClient::SwapMultiAssetsMargin` 方法，调用 `/v5/account/multi_assets_margin`；它不属于本文列出的 55 项交付清单，也未纳入上述回归。若业务需要该方法，请先对照 HTX OpenD 核实接口和账户前置条件，再单独验证。
