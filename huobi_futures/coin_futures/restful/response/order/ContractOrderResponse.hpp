#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace coin_futures
    {
        namespace restful
        {
            namespace response_order
            {
                struct ContractOrderResponse
                {
                    std::optional<std::string> status;
                    std::optional<JS::Nullable<int64_t>> ts;
                    struct OrderData {
                        std::optional<JS::Nullable<int64_t>> order_id;
                        std::optional<std::string> order_id_str;
                        std::optional<JS::Nullable<int64_t>> client_order_id;
                        JS_OBJ(order_id, order_id_str, client_order_id);
                    };
                    std::optional<OrderData> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
