// huobi_futures/linear_swap/restful/response_market/GetMarketOpenInterestResponse.hpp
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
            namespace response_market
            {
                struct GetMarketOpenInterestResponse
                {
                    struct Data
                    {
                        std::optional<std::string> contract_code;
                        std::optional<std::string> amount;
                        std::optional<std::string> volume;
                        std::optional<std::string> value;
                        std::optional<std::string> trade_amount;
                        std::optional<std::string> trade_volume;
                        std::optional<std::string> trade_turnover;

                        JS_OBJ(contract_code, amount, volume, value, trade_amount, trade_volume, trade_turnover);
                    };

                    std::optional<int32_t> code;
                    std::optional<Data> data;
                    std::optional<std::string> message;
                    std::optional<bool> success;
                    std::optional<int64_t> ts;

                    JS_OBJ(code, data, message, success, ts);
                };
            }
        }
    }
}