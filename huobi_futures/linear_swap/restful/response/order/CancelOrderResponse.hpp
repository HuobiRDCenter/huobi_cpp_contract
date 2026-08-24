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
                struct CancelOrderResponse
                {
                    std::optional<int32_t> code;

                    std::optional<string> msg;

                    struct Data
                    {
                        std::optional<int32_t> code;

                        std::optional<string> message;

                        std::optional<string> order_id;

                        std::optional<string> client_order_id;

                        // v3 字段（保留，可选）
                        struct Error
                        {
                            std::optional<string> order_id;
                            std::optional<int32_t> err_code;
                            std::optional<string> err_msg;
                            JS_OBJ(order_id, err_code, err_msg);
                        };
                        std::optional<std::vector<Error>> errors;
                        std::optional<std::vector<std::string>> successes;

                        JS_OBJ(code, message, order_id, client_order_id, errors, successes);
                    };
                    std::optional<Data> data;

                    std::optional<int64_t> ts;

                    JS_OBJ(code, msg, data, ts);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
