#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>
#include <memory>

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_order
            {
                // V5 /v5/trade/batch_orders 与 /v5/trade/cancel_batch_orders 响应
                // data 为数组，每元素含 code/message/order_id/client_order_id
                struct SwapTradeBatchResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        std::optional<int32_t> code;
                        std::optional<string> message;
                        std::optional<string> order_id;
                        std::optional<string> client_order_id;

                        JS_OBJ(code, message, order_id, client_order_id);
                    };

                    std::unique_ptr<std::vector<Data>> data;

                    std::optional<string> message;

                    std::optional<int64_t> ts;

                    JS_OBJ(code, data, message, ts);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
