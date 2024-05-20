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
            namespace response_order
            {
                struct SwapOrderInfoResponse
                {
                    std::optional<std::string> status;
                    struct OrderInfo
                    {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<double> volume;
                        std::optional<double> price;
                        std::optional<std::string> direction;
                        std::optional<std::string> offset;
                        std::optional<int64_t> lever_rate;
                        std::optional<int64_t> order_id;
                        std::optional<std::string> order_id_str;
                        std::optional<int64_t> client_order_id;
                        std::optional<int64_t> created_at;
                        std::optional<int64_t> canceled_at;
                        std::optional<double> trade_volume;
                        std::optional<double> trade_turnover;
                        std::optional<double> fee;
                        std::optional<double> trade_avg_price;
                        std::optional<double> real_profit;
                        std::optional<std::string> liquidation_type;
                        std::optional<int64_t> is_tpsl;
                        std::optional<std::string> canceled_source;
                    };
                    std::optional<OrderInfo> data;
                    std::optional<int64_t> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
