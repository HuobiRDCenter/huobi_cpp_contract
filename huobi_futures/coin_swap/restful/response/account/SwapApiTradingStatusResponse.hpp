#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace coin_swap
    {
        namespace restful
        {
            namespace response_account
            {
                struct SwapApiTradingStatusResponse
                {
                    struct COR {
                        std::optional<int64_t> orders_threshold;
                        std::optional<int64_t> orders;
                        std::optional<int64_t> invalid_cancel_orders;
                        std::optional<float> cancel_ratio_threshold;
                        std::optional<float> cancel_ratio;
                        std::optional<int> is_trigger;
                        std::optional<int> is_active;
                        JS_OBJ(orders_threshold, orders, invalid_cancel_orders, cancel_ratio_threshold, cancel_ratio, is_trigger, is_active);
                    };

                    struct TDN {
                        std::optional<int64_t> disables_threshold;
                        std::optional<int64_t> disables;
                        std::optional<int> is_trigger;
                        std::optional<int> is_active;
                        JS_OBJ(disables_threshold, disables, is_trigger, is_active);
                    };

                    struct DataItem {
                        std::optional<int64_t> is_disable;
                        std::optional<std::string> order_price_types;
                        std::optional<std::string> disable_reason;
                        std::optional<int64_t> disable_interval;
                        std::optional<int64_t> recovery_time;
                        std::optional<COR> cor;
                        std::optional<TDN> tdn;
                        JS_OBJ(is_disable, order_price_types, disable_reason, disable_interval, recovery_time, cor, tdn);
                    };
                    std::optional<std::string> status;
                    std::optional<int64_t> ts;
                    std::vector<std::vector<DataItem>> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

