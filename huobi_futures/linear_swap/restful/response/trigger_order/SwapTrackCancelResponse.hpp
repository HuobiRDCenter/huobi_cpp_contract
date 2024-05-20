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
                struct SwapTrackCancelResponse
                {
                    struct Errors {
                        std::optional<std::string> order_id;
                        std::optional<JS::Nullable<int64_t>> err_code;
                        std::optional<std::string> err_msg;
                        JS_OBJ(order_id, err_code, err_msg);
                    };

                    struct Data {
                        std::optional<string> successes;
                        std::optional<Errors> errors;
                        JS_OBJ(successes, errors);
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
