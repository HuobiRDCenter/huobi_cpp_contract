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
                struct SwapCancelAfterResponse
                {
                    struct Data {
                        std::optional<JS::Nullable<int64_t>> current_time;
                        std::optional<JS::Nullable<int64_t>> trigger_time;
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
    }         // namespace coin_futures
} // namespace huobi_futures
