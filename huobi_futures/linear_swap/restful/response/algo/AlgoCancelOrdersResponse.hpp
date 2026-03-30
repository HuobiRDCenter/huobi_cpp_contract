// huobi_futures/linear_swap/restful/response_algo/AlgoCancelOrdersResponse.hpp
#pragma once

#include <string>
#include <vector>
#include <optional>
#include "huobi_futures/json_struct/json_struct.h"

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_algo
            {
                struct AlgoCancelOrdersResponse
                {
                    struct Data
                    {
                        std::optional<std::string> algo_id;
                        std::optional<std::string> algo_client_order_id;
                        std::optional<bool> success;
                        std::optional<std::string> error_msg;
                        std::optional<int32_t> error_code;

                        JS_OBJ(algo_id, algo_client_order_id, success, error_msg, error_code);
                    };

                    std::optional<int32_t> code;
                    std::optional<std::vector<Data>> data;
                    std::optional<std::string> message;
                    std::optional<int64_t> ts;

                    JS_OBJ(code, data, message, ts);
                };
            }
        }
    }
}