// huobi_futures/linear_swap/restful/response_market/GetMarketPriceLimitResponse.hpp
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
            namespace response_market
            {
                struct GetMarketPriceLimitResponse
                {
                    struct Data
                    {
                        std::optional<std::string> contract_code;
                        std::optional<std::string> high_limit;
                        std::optional<std::string> low_limit;

                        JS_OBJ(contract_code, high_limit, low_limit);
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