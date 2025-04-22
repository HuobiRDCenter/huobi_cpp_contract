#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_order
            {
                struct SwapTradePositionHistoryResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        std::string id;
                        std::string contract_code;
                        std::string position_side;
                        std::string margin_mode;
                        std::string cost_open;
                        std::string close_avg_price;
                        std::string volume;
                        std::string available;
                        std::string lever_rate;
                        std::string profit;
                        std::string profit_ratio;
                        std::string state;
                        std::string fee;
                        std::string funding_fee;
                        std::string margin_currency;
                        double last;
                        std::string business_type;
                        std::string contract_type;
                        std::string created_time;
                        std::string updated_time;

                        JS_OBJ(id, contract_code, position_side, margin_mode, cost_open, close_avg_price, volume, available, lever_rate, profit, profit_ratio, state, fee, funding_fee, margin_currency, last, business_type, contract_type, created_time, updated_time);
                    };
                    };

                    std::optional<Data> data;

                    std::optional<string> message;

                    int64_t ts;

                    JS_OBJ(code, data, message, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
