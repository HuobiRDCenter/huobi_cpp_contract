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
                struct LinearCancelAfterResponse
                {
                    struct Data {
                        std::optional<int64_t> current_time;
                        std::optional<int64_t> trigger_time;
                        JS_OBJ(current_time, trigger_time);
                    };
                    std::optional<JS::Nullable<int64_t>> code;
                    std::optional<std::string> msg;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<Data> data;
                    JS_OBJ(code, msg, ts, data);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
