#pragma once

#include <string>
#include <optional>
#include "huobi_futures/json_struct/json_struct.h"

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_order
            {
                struct SwapTradeCancelAfterResponse
                {
                    struct Data
                    {
                        std::optional<std::string> current_time;
                        std::optional<std::string> trigger_time;

                        JS_OBJ(current_time, trigger_time);
                    };

                    std::optional<int32_t> code;
                    std::optional<Data> data;
                    std::optional<std::string> message;
                    std::optional<int64_t> ts;

                    JS_OBJ(code, data, message, ts);
                };
            }
        }
    }
}