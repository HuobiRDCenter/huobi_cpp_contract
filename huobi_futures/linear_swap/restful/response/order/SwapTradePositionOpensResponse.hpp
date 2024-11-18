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
                struct SwapTradePositionOpensResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        std::string contract_code;
                        std::string position_side;
                        std::string margin_mode;
                        std::string cost_open;
                        std::string volume;
                        std::string available;
                        std::string lever_rate;
                        std::string adl_risk_percent;
                        std::string liquidation_price;
                        std::string initial_margin;
                        std::string maintenance_margin;
                        std::string margin;
                        std::string profit_unreal;
                        std::string profit_rate;
                        std::string margin_rate;
                        std::string margin_currency;
                        std::string position_mode;
                        double last;
                        std::string contract_type;
                        std::string created_time;
                        std::string updated_time;

                        JS_OBJ(contract_code, position_side, margin_mode, cost_open, volume, available, lever_rate,
                               adl_risk_percent, liquidation_price, initial_margin, maintenance_margin, margin,
                               profit_unreal, profit_rate, margin_rate, margin_currency, position_mode, last,
                               contract_type, created_time, updated_time);
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
