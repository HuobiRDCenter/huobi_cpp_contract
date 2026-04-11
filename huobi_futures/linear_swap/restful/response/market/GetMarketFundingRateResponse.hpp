// huobi_futures/linear_swap/restful/response_market/GetMarketFundingRateResponse.hpp
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
                struct GetMarketFundingRateResponse
                {
                    struct Data
                    {
                        std::optional<std::string> contract_code;
                        std::optional<std::string> funding_rate;
                        std::optional<std::string> funding_time;
                        std::optional<std::string> next_funding_time;
                        std::optional<std::string> min_funding_rate;
                        std::optional<std::string> max_funding_rate;

                        JS_OBJ(contract_code, funding_rate, funding_time, next_funding_time, min_funding_rate, max_funding_rate);
                    };

                    std::optional<int32_t> code;
                    std::optional<std::vector<Data>> data;
                    std::optional<std::string> message;
                    std::optional<bool> success;
                    std::optional<int64_t> ts;

                    JS_OBJ(code, data, message, success, ts);
                };
            }
        }
    }
}