// huobi_futures/linear_swap/restful/response_algo/AlgoQueryOrderHistoryResponse.hpp
#pragma once

#include <string>
#include <vector>
#include <optional>
#include "huobi_futures/json_struct/json_struct.h"

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_algo
            {
                struct AlgoQueryOrderHistoryResponse
                {
                    struct Data
                    {
                        std::optional<std::string> id;
                        std::optional<std::string> volume;
                        std::optional<std::string> type;
                        std::optional<std::string> state;
                        std::optional<std::string> side;
                        std::optional<std::string> price;
                        std::optional<std::string> algo_id;
                        std::optional<std::string> algo_client_order_id;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> position_side;
                        std::optional<std::string> margin_mode;
                        std::optional<std::string> relation_order_id;
                        std::optional<std::string> actual_volume;
                        std::optional<std::string> actual_price;
                        std::optional<std::string> actual_time;
                        std::optional<std::string> created_time;
                        std::optional<std::string> updated_time;
                        std::optional<std::string> order_source;
                        std::optional<std::string> price_match;
                        std::optional<std::string> trigger_price;
                        std::optional<std::string> trigger_price_type;
                        std::optional<std::string> tp_trigger_price;
                        std::optional<std::string> tp_order_price;
                        std::optional<std::string> tp_type;
                        std::optional<std::string> tp_trigger_price_type;
                        std::optional<std::string> sl_trigger_price;
                        std::optional<std::string> sl_order_price;
                        std::optional<std::string> sl_type;
                        std::optional<std::string> sl_trigger_price_type;
                        std::optional<std::string> active_price;
                        std::optional<std::string> order_price_type;
                        std::optional<std::string> callback_rate;
                        std::optional<bool> reduce_only;

                        JS_OBJ(id, volume, type, state, side, price, algo_id, algo_client_order_id,
                               contract_code, position_side, margin_mode, relation_order_id, actual_volume,
                               actual_price, actual_time, created_time, updated_time, order_source,
                               price_match, trigger_price, trigger_price_type, tp_trigger_price, tp_order_price,
                               tp_type, tp_trigger_price_type, sl_trigger_price, sl_order_price, sl_type,
                               sl_trigger_price_type, active_price, order_price_type, callback_rate, reduce_only);
                    };

                    std::optional<int32_t> code;
                    std::optional<std::vector<Data>> data;
                    std::optional<std::string> message;
                    std::optional<int64_t> ts;

                    JS_OBJ(code, data, message, ts);
                };
            }
        }
    }
}