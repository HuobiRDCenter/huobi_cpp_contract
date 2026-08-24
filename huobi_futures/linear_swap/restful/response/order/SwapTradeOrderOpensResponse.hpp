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
                struct SwapTradeOrderOpensResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        std::optional<std::string> id;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> side;
                        std::optional<std::string> position_side;
                        std::optional<std::string> type;
                        std::optional<std::string> price_match;
                        std::optional<std::string> order_id;
                        std::optional<std::string> client_order_id;
                        std::optional<std::string> margin_mode;
                        std::optional<std::string> price;
                        std::optional<std::string> volume;
                        std::optional<std::string> lever_rate;
                        std::optional<std::string> state;
                        std::optional<std::string> order_source;
                        std::optional<bool> reduce_only;
                        std::optional<std::string> time_in_force;
                        std::optional<std::string> tp_trigger_price;
                        std::optional<std::string> tp_order_price;
                        std::optional<std::string> tp_type;
                        std::optional<std::string> tp_trigger_price_type;
                        std::optional<std::string> sl_trigger_price;
                        std::optional<std::string> sl_order_price;
                        std::optional<std::string> sl_type;
                        std::optional<std::string> sl_trigger_price_type;
                        std::optional<std::string> trade_avg_price;
                        std::optional<std::string> trade_volume;
                        std::optional<std::string> trade_turnover;
                        std::optional<std::string> fee_currency;
                        std::optional<std::string> fee;
                        std::optional<std::string> deduction_currency;
                        std::optional<std::string> deduction_amount;
                        std::optional<std::string> profit;
                        std::optional<std::string> contract_type;
                        std::optional<std::string> created_time;
                        std::optional<std::string> updated_time;
                        JS_OBJ(id, contract_code, side, position_side, type, price_match, order_id, client_order_id, margin_mode, price, volume, lever_rate, state, order_source, reduce_only, time_in_force, tp_trigger_price, tp_order_price, tp_type, tp_trigger_price_type, sl_trigger_price, sl_order_price, sl_type, sl_trigger_price_type, trade_avg_price, trade_volume, trade_turnover, fee_currency, fee, deduction_currency, deduction_amount, profit, contract_type, created_time, updated_time);
                    };

                    std::optional<std::vector<Data>> data;

                    std::optional<string> message;

                    int64_t ts;

                    JS_OBJ(code, data, message, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
