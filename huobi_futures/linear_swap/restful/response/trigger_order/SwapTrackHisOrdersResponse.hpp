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
            namespace response_trigger_order
            {
                struct SwapTrackHisOrdersResponse
                {
                    struct Order {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<JS::Nullable<float>> volume;
                        std::optional<JS::Nullable<int64_t>> order_type;
                        std::optional<std::string> direction;
                        std::optional<std::string> offset;
                        std::optional<JS::Nullable<int64_t>> lever_rate;
                        std::optional<JS::Nullable<int64_t>> order_id;
                        std::optional<std::string> order_id_str;
                        std::optional<std::string> order_source;
                        std::optional<JS::Nullable<int64_t>> created_at;
                        std::optional<JS::Nullable<int64_t>> update_time;
                        std::optional<std::string> order_price_type;
                        std::optional<JS::Nullable<int64_t>> status;
                        std::optional<JS::Nullable<int64_t>> canceled_at;
                        std::optional<JS::Nullable<int64_t>> fail_code;
                        std::optional<std::string> fail_reason;
                        std::optional<JS::Nullable<float>> callback_rate;
                        std::optional<JS::Nullable<float>> active_price;
                        std::optional<JS::Nullable<int64_t>> is_active;
                        std::optional<JS::Nullable<float>> market_limit_price;
                        std::optional<JS::Nullable<float>> formula_price;
                        std::optional<JS::Nullable<float>> real_volume;
                        std::optional<JS::Nullable<float>> triggered_price;
                        std::optional<std::string> relation_order_id;
                        std::optional<std::string> margin_mode;
                        std::optional<std::string> margin_account;
                        std::optional<string> contract_type;
                        std::optional<string> pair;
                        std::optional<string> business_type;
                        std::optional<JS::Nullable<int64_t>> reduce_only;

                        JS_OBJ(symbol, contract_code, volume, order_type, direction, offset, lever_rate, order_id, order_id_str,
                                order_source, created_at, update_time, order_price_type, status, canceled_at, fail_code, fail_reason,
                                callback_rate, active_price, is_active, market_limit_price, formula_price, real_volume,
                                triggered_price, relation_order_id, margin_mode, margin_account, , contract_type, pair, business_type, reduce_only)
                    };

                    struct Data {
                        std::optional<JS::Nullable<int64_t>> total_page;
                        std::optional<JS::Nullable<int64_t>> total_size;
                        std::optional<JS::Nullable<int64_t>> current_page;
                        std::vector<Order> orders;

                        JS_OBJ(total_page, total_size, current_page, orders)
                    };

                    std::optional<JS::Nullable<int64_t>> status;
                    Data data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts)

                };
            } // namespace response_trigger_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
