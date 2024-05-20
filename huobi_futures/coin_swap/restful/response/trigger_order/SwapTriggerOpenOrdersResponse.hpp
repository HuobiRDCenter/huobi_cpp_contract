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
            namespace response_trigger_order
            {
                struct SwapTriggerOpenOrdersResponse
                {
                    struct OrderDetail {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> contract_type;
                        std::optional<std::string> trigger_type;
                        std::optional<std::string> volume;
                        std::optional<int64_t> order_type;
                        std::optional<std::string> direction;
                        std::optional<std::string> offset;
                        std::optional<int64_t> lever_rate;
                        std::optional<int64_t> order_id;
                        std::optional<std::string> order_id_str;
                        std::optional<std::string> order_source;
                        std::optional<float> trigger_price;
                        std::optional<float> order_price;
                        std::optional<int64_t> created_at;
                        std::optional<std::string> order_price_type;
                        std::optional<int64_t> status;
                        std::optional<std::string> relation_order_id;
                        std::optional<float> triggered_price;
                        std::optional<int64_t> triggered_at;
                        std::optional<int64_t> order_insert_at;
                        std::optional<int64_t> canceled_at;
                        std::optional<int64_t> update_time;
                        std::optional<int64_t> fail_code;
                        std::optional<std::string> fail_reason;
                        std::optional<std::string> tpsl_order_type;
                        std::optional<std::string> source_order_id;
                        std::optional<std::string> relation_tpsl_order_id;
                        std::optional<float> callback_rate;
                        std::optional<float> active_price;
                        std::optional<int64_t> is_active;
                        std::optional<float> market_limit_price;
                        std::optional<float> formula_price;
                        std::optional<float> real_volume;

                        JS_OBJ(symbol, contract_code, contract_type, trigger_type, volume, order_type, direction, offset,
                               lever_rate, order_id, order_id_str, order_source, trigger_price, order_price, created_at,
                               order_price_type, status, relation_order_id, triggered_price, triggered_at, order_insert_at,
                                canceled_at, update_time, fail_code, fail_reason, tpsl_order_type, source_order_id,
                                relation_tpsl_order_id, callback_rate, active_price, is_active, market_limit_price,
                                formula_price, real_volume);
                    };

                    struct PageDetail {
                        std::optional<int64_t> total_page;
                        std::optional<int64_t> current_page;
                        std::optional<int64_t> total_size;
                        std::optional<std::vector<OrderDetail>> orders;
                        JS_OBJ(total_page, current_page, total_size, orders);
                    };
                    std::optional<std::string> status;
                    std::optional<PageDetail> data;
                    std::optional<int64_t> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_trigger_order
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
