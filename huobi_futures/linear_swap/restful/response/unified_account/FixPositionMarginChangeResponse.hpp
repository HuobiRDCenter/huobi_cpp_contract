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
            namespace response_unified_account
            {
                struct FixPositionMarginChangeResponse
                {
                    std::optional<JS::Nullable<int64_t>> code;
                    std::optional<std::string> msg;
                    std::optional<JS::Nullable<int64_t>> ts;
                    struct Data {
                        std::optional<std::string> order_id;
                        std::optional<JS::Nullable<int64_t>> client_order_id;
                        JS_OBJ(order_id, client_order_id);
                    };
                    std::optional<Data> data;

                    JS_OBJ(code, msg, ts, data);
                };
            } // namespace response_unified_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures

