// huobi_futures/linear_swap/restful/response_algo/AlgoQueryOrdersResponse.hpp
#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include "huobi_futures/json_struct/json_struct.h"

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_algo
            {
                struct AlgoQueryOrdersResponse
                {
                    struct Data
                    {
                        std::optional<std::string> id;
                        std::optional<std::string> algo_id;
                        std::optional<std::string> algo_client_order_id;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> volume;
                        std::optional<std::string> type;
                        std::optional<std::string> state;
                        std::optional<std::string> position_side;
                        std::optional<std::string> margin_mode;
                        std::optional<std::string> side;
                        std::optional<std::string> tp_trigger_price;
                        std::optional<std::string> tp_order_price;
                        std::optional<std::string> tp_type;
                        std::optional<std::string> tp_trigger_price_type;
                        std::optional<std::string> sl_trigger_price;
                        std::optional<std::string> sl_order_price;
                        std::optional<std::string> sl_type;
                        std::optional<std::string> sl_trigger_price_type;
                        std::optional<std::string> price;
                        std::optional<std::string> price_match;
                        std::optional<std::string> trigger_price;
                        std::optional<std::string> trigger_price_type;
                        std::optional<std::string> active_price;
                        std::optional<std::string> order_price_type;
                        std::optional<std::string> callback_rate;
                        std::optional<bool> reduce_only;
                        std::optional<std::string> actual_volume;
                        std::optional<std::string> actual_price;
                        std::optional<std::string> actual_time;
                        std::optional<std::string> relation_order_id;
                        std::optional<std::string> created_time;
                        std::optional<std::string> updated_time;
                        std::optional<std::string> order_source;

                        JS_OBJ(id, algo_id, algo_client_order_id, contract_code, volume, type, state,
                               position_side, margin_mode, side, tp_trigger_price, tp_order_price, tp_type,
                               tp_trigger_price_type, sl_trigger_price, sl_order_price, sl_type,
                               sl_trigger_price_type, price, price_match, trigger_price, trigger_price_type,
                               active_price, order_price_type, callback_rate, reduce_only, actual_volume,
                               actual_price, actual_time, relation_order_id, created_time, updated_time,
                               order_source);
                    };

                    std::optional<int32_t> code;
                    std::optional<std::vector<Data>> data;
                    std::optional<std::string> message;
                    std::optional<int64_t> ts;
                    std::unique_ptr<std::vector<std::string>> args;

                    JS_OBJ(code, data, message, ts, args);
                };
            }
        }
    }
}
