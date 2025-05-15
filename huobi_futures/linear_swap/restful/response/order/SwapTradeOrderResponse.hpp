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
                struct SwapTradeOrderResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        std::string order_id;
                        std::string cancel_reason;
                        std::optional<std::string> client_order_id;

                        JS_OBJ(order_id, cancel_reason, client_order_id);
                    };

                    std::optional<Data> data;

                    std::optional<string> message;

                    int64_t ts;

                    JS_OBJ(code, data, message, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
