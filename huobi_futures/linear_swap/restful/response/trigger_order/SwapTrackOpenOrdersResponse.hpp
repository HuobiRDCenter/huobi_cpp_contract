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
                struct SwapTrackOpenOrdersResponse
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
                        std::optional<std::string> order_price_type;
                        std::optional<JS::Nullable<int64_t>> status;
                        std::optional<JS::Nullable<float>> callback_rate;
                        std::optional<JS::Nullable<float>> active_price;
                        std::optional<JS::Nullable<int64_t>> is_active;
                        std::optional<std::string> margin_mode;
                        std::optional<std::string> margin_account;
                        std::optional<string> contract_type;
                        std::optional<string> pair;
                        std::optional<string> business_type;
                        std::optional<JS::Nullable<int64_t>> reduce_only;

                        JS_OBJ(
                                symbol, contract_code, volume, order_type, direction, offset, lever_rate,
                                order_id, order_id_str, order_source, created_at, order_price_type, status,
                                callback_rate, active_price, is_active, margin_mode, margin_account, contract_type,
                                pair, business_type, reduce_only
                        );
                    };

                    struct Data {
                        std::optional<JS::Nullable<int64_t>> total_page;
                        std::optional<JS::Nullable<int64_t>> total_size;
                        std::optional<JS::Nullable<int64_t>> current_page;
                        std::optional<std::vector<Order>> orders;

                        JS_OBJ(total_page, total_size, current_page, orders);
                    };
                    std::optional<std::string> status;
                    std::optional<Data> data;
                    std::optional<JS::Nullable<int64_t>> ts;

                    JS_OBJ(status, data, ts);
                };
            } // namespace response_trigger_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
