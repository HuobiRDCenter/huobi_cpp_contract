#pragma once

#include <string>
using std::string;

namespace huobi_futures
{
	namespace utils
	{
        const string DEFAULT_HOST = "api.hbdm.com";

        const string DEFAULT_ID = "api";

        const int WS_RECV_BUF_SIZE = 4096 * 100;
        const int WS_SEND_BUF_SIZE = 1024;

        // ===== 合约 V5 接口 path（对照 Java v5-interface-list.md 55 接口清单，编号一致）=====

        // REST account（6 + 1 multi_assets_margin which is also account）
        const string V5_ACCOUNT_BALANCE = "/v5/account/balance";                           // 1.GET
        const string V5_ACCOUNT_ASSET_MODE = "/v5/account/asset_mode";                    // 2.POST / 3.GET
        const string V5_ACCOUNT_FEE_DEDUCTION_CURRENCY = "/v5/account/fee_deduction_currency"; // 4.POST / 5.GET
        const string V5_ACCOUNT_BILLS = "/v5/account/bills";                             // 6.GET
        const string V5_ACCOUNT_MULTI_ASSETS_MARGIN = "/v5/account/multi_assets_margin"; // setMultiAssetsMargin POST (Java: account, not market)

        // REST trade（13）
        const string V5_TRADE_ORDER = "/v5/trade/order";                                  // 7.POST / 17.GET
        const string V5_TRADE_BATCH_ORDERS = "/v5/trade/batch_orders";                    // 8.POST
        const string V5_TRADE_CANCEL_ORDER = "/v5/trade/cancel_order";                   // 9.POST
        const string V5_TRADE_CANCEL_BATCH_ORDERS = "/v5/trade/cancel_batch_orders";      // 10.POST
        const string V5_TRADE_CANCEL_ALL_ORDERS = "/v5/trade/cancel_all_orders";          // 11.POST
        const string V5_TRADE_POSITION = "/v5/trade/position";                            // 12.POST
        const string V5_TRADE_POSITION_ALL = "/v5/trade/position_all";                    // 13.POST
        const string V5_TRADE_ORDER_OPENS = "/v5/trade/order/opens";                     // 14.GET
        const string V5_TRADE_ORDER_DETAILS = "/v5/trade/order/details";                 // 15.GET
        const string V5_TRADE_ORDER_HISTORY = "/v5/trade/order/history";                  // 16.GET
        const string V5_TRADE_CANCEL_AFTER = "/v5/trade/cancel-after";                    // 18.POST
        const string V5_TRADE_POSITION_OPENS = "/v5/trade/position/opens";                // 19.GET
        const string V5_TRADE_POSITION_HISTORY = "/v5/trade/position/history";            // (非V5清单范围，但C++代码使用)

        // REST position（7）
        const string V5_POSITION_LEVER = "/v5/position/lever";                            // 20.GET / 21.POST
        const string V5_POSITION_MODE = "/v5/position/mode";                              // 22.GET / 23.POST
        const string V5_POSITION_RISK_LIMIT = "/v5/position/risk/limit";                  // 24.GET
        const string V5_POSITION_RISK_LIMIT_TIER = "/v5/position/risk/limit_tier";       // 25.GET
        const string V5_POSITION_MARGIN = "/v5/position/margin";                          // 26.POST

        // REST market（12，公开无需 key）
        const string V5_MARKET_RISK_LIMIT = "/v5/market/risk/limit";                       // 27.GET
        const string V5_MARKET_ASSETS_DEDUCTION_CURRENCY = "/v5/market/assets_deduction_currency"; // 28.GET
        const string V5_MARKET_MULTI_ASSETS_MARGIN = "/v5/market/multi_assets_margin";    // 29.GET
        const string V5_MARKET_FUNDING_RATE = "/v5/market/funding_rate";                   // 30.GET
        const string V5_MARKET_FUNDING_RATE_HISTORY = "/v5/market/funding_rate_history";   // 31.GET
        const string V5_MARKET_OPEN_INTEREST = "/v5/market/open_interest";                // 32.GET
        const string V5_MARKET_PRICE_LIMIT = "/v5/market/price_limit";                     // 33.GET
        const string V5_MARKET_LIQUIDATION_ORDERS = "/v5/market/liquidation_orders";      // 34.GET
        const string V5_MARKET_SETTLEMENT_HISTORY = "/v5/market/settlement_history";       // 35.GET
        const string V5_MARKET_ELITE_ACCOUNT_RATIO = "/v5/market/elite_account_ratio";    // 36.GET
        const string V5_MARKET_ELITE_POSITION_RATIO = "/v5/market/elite_position_ratio";  // 37.GET
        const string V5_MARKET_ESTIMATED_SETTLEMENT_PRICE = "/v5/market/estimated_settlement_price"; // 38.GET

        // REST algo（5）
        const string V5_ALGO_ORDER = "/v5/algo/order";                                    // 39.POST / 41.GET
        const string V5_ALGO_CANCEL_ORDERS = "/v5/algo/cancel_orders";                     // 40.POST
        const string V5_ALGO_ORDER_OPENS = "/v5/algo/order/opens";                         // 42.GET
        const string V5_ALGO_ORDER_HISTORY = "/v5/algo/order/history";                     // 43.GET

        // V5 WebSocket
        const string V5_WS_NOTIFICATION_PATH = "/ws/v5/notification";                      // 推送 7 topic
        const string V5_WS_TRADE_PATH = "/linear-swap-trade";                              // 交易 5 op
    } // namespace utils
} // namespace huobi_futures