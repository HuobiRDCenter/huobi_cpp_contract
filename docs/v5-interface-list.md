# 合约 V5 接口交付清单（55 个）

> 分支：`develop_H408547`（本仓库 commit `2790c5a`）
> 实测口径：带真实 API key 打 HTX 生产 API，非 mock。REST 私有接口真下单/撤单，WS 真订阅 + REST 触发推送。
> C++ 实测日期：2026-08-25。**55 接口全部实测通过，REST/WS 各连续两轮回归稳定全绿。**
> 用例分布：`v5_test` 42 个（account 6 + trade 12 + position 7 + market 12 + algo 5）、`v5_ws_test` 17 个（推送 7 + 交易 5 + 离线 sanity 5）。
> 覆盖口径：55 接口 = 54 个独立用例 + 1 个内联覆盖（#9 `/v5/trade/cancel_order` 无独立用例，由 4 个 trade/WS 用例的撤单步骤调用并断言 `code==200`，见下表）。
> 口径来源：Java SDK（huobi_java_contract）为权威实现，C++ SDK 从 Java 翻译，实测口径与 Java 一致；两边清单的 37 个唯一 path 已逐条比对，无差异。
>
> 文档链接：每个接口指向 HTX opend 官方文档页面（`https://www.htx.com/zh-cn/opend/newApiPages/?id=<UUID>`）。
>
> 老接口（非 V5）说明：SDK 仍含老 v3 接口（`/linear-swap-api/...`、期权等），这些是历史存量债，在统一/多资产保证金账户下不可用（报 6002/1051/1066），不在本 55 个 V5 交付范围内。

## 总览

| 类别 | 接口数 | 独立用例 | 实测通过 | 需 key | 说明 |
|---|---|---|---|---|---|
| REST account | 6 | 6 | 6 ✅ | 是 | 账户余额/资产模式/费抵币种/流水 |
| REST trade | 13 | 12（#9 内联覆盖） | 13 ✅ | 是 | 下单/撤单/全平/查询委托与成交 |
| REST position | 7 | 7 | 7 ✅ | 是 | 杠杆/模式/风险限额/保证金 |
| REST market | 12 | 12 | 12 ✅ | 否 | 公开行情，无需 key |
| REST algo | 5 | 5 | 5 ✅ | 是 | 策略委托下单/撤/查 |
| WS 推送 | 7 | 7 | 7 ✅ | 是 | 订单/成交/持仓/账户推送 |
| WS 交易 | 5 | 5 | 5 ✅ | 是 | WS 下单/撤单 |
| **合计** | **55** | **54 + 1 内联** | **55 ✅** | | 另有 5 个离线 sanity 用例（JSON 解析/空快照/cid 关联/sub ack） |

> “验证”列：**强** = `code==200` 且断言 data 必填字段非空；**基础** = 仅断言 `code==200`（接口可达 + 签名/参数正确，该接口无可稳定断言的 data）；**弱** = 接受业务可解释的非 200 返回（原因见 [验证强度说明](#验证强度说明)）。

---

## REST account（6 个，私有）

| # | method | path | 文档链接 | C++ 测试方法 | 验证 | 实测 |
|---|---|---|---|---|---|---|
| 1 | GET | `/v5/account/balance` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-195703a12d5) | `V5Account.GetContractAccountBalance` | 强 | ✅ |
| 2 | POST | `/v5/account/asset_mode` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957dd1a995) | `V5Account.SetAssetMode` | 弱 | ✅ |
| 3 | GET | `/v5/account/asset_mode` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957dd37de0) | `V5Account.GetAssetMode` | 基础 | ✅ |
| 4 | POST | `/v5/account/fee_deduction_currency` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-198826314c7) | `V5Account.SetFeeDeductionCurrency` | 强 | ✅ |
| 5 | GET | `/v5/account/fee_deduction_currency` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b723f5241) | `V5Account.GetFeeDeductionCurrency` | 基础 | ✅ |
| 6 | GET | `/v5/account/bills` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b724157a2) | `V5Account.GetAccountBills` | 基础 | ✅ |

## REST trade（13 个，私有）

| # | method | path | 文档链接 | C++ 测试方法 | 验证 | 实测 |
|---|---|---|---|---|---|---|
| 7 | POST | `/v5/trade/order` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957dd521e6) | `V5Trade.TradeOrderFarPrice` | 基础 | ✅ |
| 8 | POST | `/v5/trade/batch_orders` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957de4ff8f) | `V5Trade.TradeBatchOrders` | 强 | ✅ |
| 9 | POST | `/v5/trade/cancel_order` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957defffc6) | 内联：`V5Trade.TradeOrderFarPrice` / `TradeBatchOrders` / `GetTradeOrder` / `TradeOrderOpens` 的撤单步骤（断言 `code==200`） | 基础 | ✅ |
| 10 | POST | `/v5/trade/cancel_batch_orders` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957df2abbe) | `V5Trade.CancelTradeBatchOrders` | 强 | ✅ |
| 11 | POST | `/v5/trade/cancel_all_orders` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957df6feb3) | `V5Trade.CancelAllOrders` | 基础 | ✅ |
| 12 | POST | `/v5/trade/position` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957e02b018) | `V5Trade.TradePosition` | 弱 | ✅ |
| 13 | POST | `/v5/trade/position_all` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957e05d40c) | `V5Trade.TradePositionAll` | 基础 | ✅ |
| 14 | GET | `/v5/trade/order/opens` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957e082f23) | `V5Trade.TradeOrderOpens` | 基础 | ✅ |
| 15 | GET | `/v5/trade/order/details` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957e2a0e6a) | `V5Trade.TradeOrderDetails` | 强 | ✅ |
| 16 | GET | `/v5/trade/order/history` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957efb2139) | `V5Trade.TradeOrderHistory` | 基础 | ✅ |
| 17 | GET | `/v5/trade/order` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-196a35af40e) | `V5Trade.GetTradeOrder` | 基础 | ✅ |
| 18 | POST | `/v5/trade/cancel-after` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b72307cbb) | `V5Trade.TradeCancelAfter` | 基础 | ✅ |
| 19 | GET | `/v5/trade/position/opens` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957f1fbee4) | `V5Trade.TradePositionOpens` | 基础 | ✅ |

> #9 说明：该接口无独立用例（trade 用例共 12 个），但确实被真实调用并断言成功——`TradeOrderFarPrice`、`TradeBatchOrders`、`GetTradeOrder`、`TradeOrderOpens` 均在下单后调用 `CancelTradeOrder` 并断言 `code==200`，WS 推送用例的清理阶段也会调用。

## REST position（7 个，私有）

| # | method | path | 文档链接 | C++ 测试方法 | 验证 | 实测 |
|---|---|---|---|---|---|---|
| 20 | GET | `/v5/position/lever` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957f316730) | `V5Position.PositionLever` | 基础 | ✅ |
| 21 | POST | `/v5/position/lever` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957f4a3b67) | `V5Position.SetPositionLever` | 基础 | ✅ |
| 22 | GET | `/v5/position/mode` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957f4d93fd) | `V5Position.PositionMode` | 基础 | ✅ |
| 23 | POST | `/v5/position/mode` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957f4ec40b) | `V5Position.SetPositionMode` | 弱 | ✅ |
| 24 | GET | `/v5/position/risk/limit` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-1957f50bd39) | `V5Position.PositionRiskLimit` | 基础 | ✅ |
| 25 | GET | `/v5/position/risk/limit_tier` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b4528fc88) | `V5Position.PositionRiskLimitTier` | 基础 | ✅ |
| 26 | POST | `/v5/position/margin` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b7247e4dd) | `V5Position.PositionMargin` | 弱 | ✅ |

## REST market（12 个，公开，无需 key）

| # | method | path | 文档链接 | C++ 测试方法 | 验证 | 实测 |
|---|---|---|---|---|---|---|
| 27 | GET | `/v5/market/risk/limit` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-195809dc1e8) | `V5Market.GetMarketRiskLimit` | 强 | ✅ |
| 28 | GET | `/v5/market/assets_deduction_currency` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19580a209a2) | `V5Market.GetAssetsDeductionCurrency` | 基础 | ✅ |
| 29 | GET | `/v5/market/multi_assets_margin` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19580a32ea2) | `V5Market.GetMultiAssetsMarginList` | 基础 | ✅ |
| 30 | GET | `/v5/market/funding_rate` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b738520e0) | `V5Market.GetMarketFundingRate` | 强 | ✅ |
| 31 | GET | `/v5/market/funding_rate_history` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b7389e8ee) | `V5Market.GetFundingRateHistory` | 基础 | ✅ |
| 32 | GET | `/v5/market/open_interest` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73998b8f) | `V5Market.GetOpenInterest` | 强 | ✅ |
| 33 | GET | `/v5/market/price_limit` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73a247e7) | `V5Market.GetPriceLimit` | 强 | ✅ |
| 34 | GET | `/v5/market/liquidation_orders` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73ab3d66) | `V5Market.GetLiquidationOrders` | 强 | ✅ |
| 35 | GET | `/v5/market/settlement_history` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73b16e57) | `V5Market.GetSettlementHistory` | 基础 | ✅ |
| 36 | GET | `/v5/market/elite_account_ratio` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73bd8472) | `V5Market.GetEliteAccountRatio` | 强 | ✅ |
| 37 | GET | `/v5/market/elite_position_ratio` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73c012ca) | `V5Market.GetElitePositionRatio` | 强 | ✅ |
| 38 | GET | `/v5/market/estimated_settlement_price` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73c587fc) | `V5Market.GetEstimatedSettlementPrice` | 强 | ✅ |

> V5 market 方法统一带 `Market` 前缀（`GetMarketPriceLimit` / `GetMarketOpenInterest` / `GetMarketLiquidationOrders` / `GetMarketEstimatedSettlementPrice`），与 v3 同名方法不构成重载歧义，可直接单参调用。

## REST algo（5 个，私有）

| # | method | path | 文档链接 | C++ 测试方法 | 验证 | 实测 |
|---|---|---|---|---|---|---|
| 39 | POST | `/v5/algo/order` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b72756dd7) | `V5Algo.AlgoOrder` | 基础 | ✅ |
| 40 | POST | `/v5/algo/cancel_orders` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73242ab0) | `V5Algo.AlgoCancelOrders` | 基础 | ✅ |
| 41 | GET | `/v5/algo/order` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b73278ea1) | `V5Algo.AlgoQueryOrders` | 基础 | ✅ |
| 42 | GET | `/v5/algo/order/opens` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b7345a20e) | `V5Algo.AlgoQueryOpenOrders` | 基础 | ✅ |
| 43 | GET | `/v5/algo/order/history` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b7361ac19) | `V5Algo.AlgoQueryOrderHistory` | 基础 | ✅ |

## WS 推送类（7 个，私有，需 key 鉴权）

> WS 推送地址：`wss://api.hbdm.com/ws/v5/notification`
> 文档列的 path 为空（WS 页面用 topic 而非 REST path），链接指向对应 opend 页。
> 用例均为「订阅 → 等 sub ack → REST 触发 → 断言推送字段」，避免 sleep 后盲触发导致 flaky。

| # | topic | 文档链接 | C++ 测试方法 | 验证 | 实测 |
|---|---|---|---|---|---|
| 44 | `orders` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19580a58ac9) | `WSNotifyTest.SubOrders` | 强 | ✅ |
| 45 | `trade` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19582b9e8db) | `WSNotifyTest.SubTrade` | 强 | ✅ |
| 46 | `trade_detail` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19f3fb0ed2d) | `WSNotifyTest.SubTradeDetail` | 强 | ✅ |
| 47 | `positions` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19582def41f) | `WSNotifyTest.SubPositions` | 强 | ✅ |
| 48 | `account` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19583056529) | `WSNotifyTest.SubAccount` | 强 | ✅ |
| 49 | `match_orders` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19710f62bf5) | `WSNotifyTest.SubMatchOrders` | 强 | ✅ |
| 50 | `algo_orders` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-19b981e8c47) | `WSNotifyTest.SubAlgoOrders` | 强 | ✅ |

## WS 交易类（5 个，私有，需 key 鉴权）

> WS 交易地址：`wss://api.hbdm.com/linear-swap-trade`
> 通过 op 指令下单/撤单，应答靠 cid 关联（无 op/topic 字段）；用例均等 auth ack 后再发指令。

| # | op | 文档链接 | C++ 测试方法 | 验证 | 实测 |
|---|---|---|---|---|---|
| 51 | `place_order` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-196a85f248b) | `WSTradeTest.PlaceOrder` | 强 | ✅ |
| 52 | `place_batch_orders` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-196a951ac2c) | `WSTradeTest.PlaceBatchOrders` | 强 | ✅ |
| 53 | `cancel_order` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-196a96db3fa) | `WSTradeTest.CancelOrder` | 强 | ✅ |
| 54 | `cancel_batch_orders` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-196a97b35b6) | `WSTradeTest.CancelBatchOrders` | 强 | ✅ |
| 55 | `cancel_all_orders` | [opend](https://www.htx.com/zh-cn/opend/newApiPages/?id=8cb89359-77b5-11ed-9966-196a98d805e) | `WSTradeTest.CancelAllOrders` | 强 | ✅ |

---

## 验证强度说明

**弱验证（4 个）**——真实成功路径会改变账户状态或有资金成本，故只验证「接口可达 + 签名/参数正确」，接受业务上可解释的非 200：

| # | 接口 | 断言 | 原因 |
|---|---|---|---|
| 2 | `POST /v5/account/asset_mode` | `code ∈ {200, 1421, 6010}` | 有持仓/挂单时服务端拒绝（1421），已是目标模式（6010）；幂等设当前值 |
| 12 | `POST /v5/trade/position` | `code ∈ {200, 1048}` | 无持仓可平返回 1048；断言 200 需要先开仓，有资金成本 |
| 23 | `POST /v5/position/mode` | `code ∈ {200, 1493}` | 有挂单时服务端拒绝（1493）；幂等设当前模式 |
| 26 | `POST /v5/position/margin` | `code != 0` | 调整逐仓保证金需先开逐仓仓，成本高且改变账户状态；仅验证请求被受理 |

**基础验证（27 个）**——只断言 `code==200`：这些是写操作（下单/撤单/设杠杆等）或返回空数据属正常的查询（无委托、无流水、无强平），没有可稳定断言的 data 字段。

**强验证（24 个）**——`code==200` + data 必填字段非空（WS 12 个全部按字段级断言，含 `state==filled` 时才必填的成交字段）。

---

## 源码位置

### C++ SDK（huobi_cpp_contract，本仓库，实测口径）

- **REST client**：`huobi_futures/linear_swap/restful/{AccountClient,OrderClient,MarketClient,AlgoClient}.hpp`
  - account → `AccountClient`（6 接口）
  - trade/position → `OrderClient`（trade 13 + position 7 接口）
  - market → `MarketClient`（12 接口，公开；V5 方法统一 `GetMarket*` 前缀）
  - algo → `AlgoClient`（5 接口）
- **REST 端点常量**：`huobi_futures/utils/const_val.hpp`（`V5_*` 常量块，带编号注释）
- **WS client**：`huobi_futures/linear_swap/ws/`
  - 推送 → `WSSwapNotificationClient`（`wss://api.hbdm.com/ws/v5/notification`，7 topic，`Sub(topics, contract_code, cb)`）
  - 交易 → `WSSwapTradeClient`（`wss://api.hbdm.com/linear-swap-trade`，5 op，应答按 cid 关联）
- **签名**：`huobi_futures/url_base/PrivateUrlBuilder.hpp`（无参 GET / 带参签名 GET / POST 三个 Build 重载）
- **测试**：`test/`
  - REST → `v5_restful_{account_market,trade_position,algo}_test.hpp`（main: `v5_main.cpp`，target `v5_test`）
  - WS → `v5_ws_{notify,trade,sanity}_test.hpp`（main: `v5_ws_main.cpp`，target `v5_ws_test`）

### Java SDK（huobi_java_contract，权威实现，翻译源）

- 对应清单与测试：`docs/v5-interface-list.md`、`src/test/java/com/huobi/usdt/{api,wss}/`
- REST service：`service/usdt/{account,trade,algo}/`；WS handler：`wss/handle/{WssV5NotificationHandle,WssTradeHandle}.java`
- 端点常量：`constants/HuobiFutureAPIConstants.java`

## 复跑命令

### C++ 全量回归（macOS + brew cmake/openssl）

```bash
cd /Users/felix.yang/IdeaProjects/huobi_cpp_contract
export PATH=/opt/homebrew/bin:$PATH
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
# 默认构建：SDK + example + v5_test + v5_ws_test（老 v3 test target 已 EXCLUDE_FROM_ALL）
cmake --build build -j8

# 本机直连 api.hbdm.com 不通时，让 curl 走代理（只影响 HTTP 请求，不影响编译）
export https_proxy=http://127.0.0.1:7897 http_proxy=http://127.0.0.1:7897

# key 只放仓库外 /tmp，不入 git；测完即删
cat > /tmp/htx_keys.env <<'EOF'
export HTX_ACCESS_KEY=<your-key>
export HTX_SECRET_KEY=<your-secret>
EOF
chmod 600 /tmp/htx_keys.env && source /tmp/htx_keys.env

./build/test/v5_test        # REST 42 用例（account 6 + market 12 + trade 12 + position 7 + algo 5）
./build/test/v5_ws_test     # WS 17 用例（sanity 5 + notify 7 + trade 5）

# 只跑公开接口（无 key 也能跑）：
./build/test/v5_test --gtest_filter='V5Market.*'
# 只跑离线 sanity：
./build/test/v5_ws_test --gtest_filter='WSSanity.*'
```

### Java 全量回归（Java 8 + 阿里云镜像 + Clash 代理）

```bash
source /tmp/htx_keys.env
JAVA_HOME=/Library/Java/JavaVirtualMachines/temurin-8.jdk/Contents/Home \
  mvn -s /tmp/aliyun.xml \
  -Dtest='com.huobi.usdt.api.TradeAPITest,com.huobi.usdt.api.SrategyAPITest,com.huobi.usdt.api.MarketAPITest,com.huobi.usdt.api.AccountAPITest,WssTradeTest,WssV5NotificationSubTest' \
  -DfailIfNoTests=false -Dsurefire.timeout=600 test \
  -Dhttp.proxyHost=127.0.0.1 -Dhttp.proxyPort=7897 \
  -Dhttps.proxyHost=127.0.0.1 -Dhttps.proxyPort=7897
```

## 已知限制

1. **密钥不入库**：仓库内无任何 key，复跑需自备 API key；CSV/日志类过程文件也不入库。
2. **老 v3 接口不可用**：统一/多资产保证金账户下老接口报 6002/1051/1066，属存量债，不在本清单范围。
3. **老 v3 测试 target 编译不过**：`test` target 依赖的 `TriggerOrderClient` / `SwapTrackHisOrdersResponse` 等老 DTO 有语法错误，已设 `EXCLUDE_FROM_ALL`，默认构建不受影响；显式 `--target test` 目前仍会失败。
4. **4 个弱验证接口**见上文，不代表 200 成功路径已被覆盖。
5. **回归次数**：2026-08-25 记录为连续两轮全绿；如需按发布标准再加跑 3 轮。
