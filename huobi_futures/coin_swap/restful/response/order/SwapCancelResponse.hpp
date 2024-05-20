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
            namespace response_order
            {
                struct SwapCancelResponse
                {
                    struct Data {
                        struct ErrorData {
                            std::optional<std::string> order_id;
                            std::optional<JS::Nullable<int64_t>> err_code;
                            std::optional<std::string> err_msg;
                            JS_OBJ(order_id, err_code, err_msg);
                        };
                        std::optional<std::vector<ErrorData>> errors;
                        std::optional<std::string> successes;
                        JS_OBJ(errors, successes);
                    };
                    std::optional<std::string> status;
                    std::optional<Data> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
