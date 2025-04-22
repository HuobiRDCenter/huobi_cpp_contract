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
                struct SwapTradeOrderTradesResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        std::string id;
                        std::string contract_code;
                        std::string order_id;
                        std::string trade_id;
                        std::string side;
                        std::string position_side;
                        std::string order_type;
                        std::string margin_mode;
                        std::string type;
                        std::string client_order_id;
                        std::string role;
                        std::string trade_price;
                        std::string trade_volume;
                        std::string trade_turnover;
                        int64_t created_time;
                        int64_t updated_time;
                        std::string order_source;
                        std::string fee_currency;
                        std::string trade_fee;
                        std::string deduction_currency;
                        std::string deduction_amount;
                        std::string deduction_price;
                        std::string profit;
                        std::string contract_type;

                        JS_OBJ(id, contract_code, order_id, trade_id, side, position_side, order_type, margin_mode, type, client_order_id, role, trade_price, trade_volume, trade_turnover, created_time, updated_time, order_source, fee_currency, trade_fee, deduction_currency, deduction_amount, deduction_price, profit, contract_type);
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
