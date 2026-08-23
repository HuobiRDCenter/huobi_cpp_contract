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
                struct GetTradeOrderResponse
                {
                    std::optional<int32_t> code;
                    std::optional<std::string> msg;

                    struct Data
                    {
                        // 基础信息
                        std::optional<std::string> id;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> side;
                        std::optional<std::string> position_side;
                        std::optional<std::string> type;

                        // 订单参数
                        std::optional<std::string> price_match;
                        std::optional<std::string> order_id;
                        std::optional<std::string> client_order_id;
                        std::optional<std::string> margin_mode;
                        std::optional<std::string> price;
                        std::optional<std::string> volume;
                        std::optional<int64_t> lever_rate;

                        // 状态信息
                        std::optional<std::string> state;
                        std::optional<std::string> order_source;
                        std::optional<bool> reduce_only;
                        std::optional<std::string> time_in_force;

                        // 止盈止损
                        std::optional<std::string> tp_trigger_price;
                        std::optional<std::string> tp_order_price;
                        std::optional<std::string> tp_type;
                        std::optional<std::string> tp_trigger_price_type;
                        std::optional<std::string> sl_trigger_price;
                        std::optional<std::string> sl_order_price;
                        std::optional<std::string> sl_type;
                        std::optional<std::string> sl_trigger_price_type;

                        // 成交信息
                        std::optional<std::string> trade_avg_price;
                        std::optional<std::string> trade_volume;
                        std::optional<std::string> trade_turnover;

                        // 费用相关
                        std::optional<std::string> fee_currency;
                        std::optional<std::string> fee;

                        // 其他参数
                        std::optional<bool> price_protect;
                        std::optional<std::string> profit;
                        std::optional<std::string> contract_type;
                        std::optional<int64_t> created_time;
                        std::optional<int64_t> updated_time;

                        JS_OBJ(
                            id,
                            contract_code,
                            side,
                            position_side,
                            type,
                            price_match,
                            order_id,
                            client_order_id,
                            margin_mode,
                            price,
                            volume,
                            lever_rate,
                            state,
                            order_source,
                            reduce_only,
                            time_in_force,
                            tp_trigger_price,
                            tp_order_price,
                            tp_type,
                            tp_trigger_price_type,
                            sl_trigger_price,
                            sl_order_price,
                            sl_type,
                            sl_trigger_price_type,
                            trade_avg_price,
                            trade_volume,
                            trade_turnover,
                            fee_currency,
                            fee,
                            price_protect,
                            profit,
                            contract_type,
                            created_time,
                            updated_time
                        );
                    };
                    std::optional<Data> data;

                    std::optional<int64_t> ts;

                    JS_OBJ(code, msg, data, ts);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
