#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>
#include <memory>

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_order
            {
                // V5 /v5/trade/order/details - 查询成交明细。data 为成交数组，无成交时可为 null/[]
                struct GetOrderTradesResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        std::optional<string> id;
                        std::optional<string> contract_code;
                        std::optional<string> order_id;
                        std::optional<string> trade_id;
                        std::optional<string> side;
                        std::optional<string> position_side;
                        std::optional<string> order_type;
                        std::optional<string> margin_mode;
                        std::optional<string> type;
                        std::optional<string> client_order_id;
                        std::optional<string> role;
                        std::optional<string> trade_price;
                        std::optional<string> trade_volume;
                        std::optional<string> trade_turnover;
                        std::optional<int64_t> created_time;
                        std::optional<int64_t> updated_time;
                        std::optional<string> order_source;
                        std::optional<string> fee_currency;
                        std::optional<string> trade_fee;
                        std::optional<string> deduction_currency;
                        std::optional<string> deduction_amount;
                        std::optional<string> deduction_price;
                        std::optional<string> profit;
                        std::optional<string> contract_type;

                        JS_OBJ(id, contract_code, order_id, trade_id, side, position_side, order_type, margin_mode,
                               type, client_order_id, role, trade_price, trade_volume, trade_turnover, created_time,
                               updated_time, order_source, fee_currency, trade_fee, deduction_currency, deduction_amount,
                               deduction_price, profit, contract_type);
                    };

                    std::unique_ptr<std::vector<Data>> data;

                    std::optional<string> message;

                    std::optional<int64_t> ts;

                    JS_OBJ(code, data, message, ts);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
