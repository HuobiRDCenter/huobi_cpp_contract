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
            namespace response_reference
            {
                struct SwapPriceLimitResponse
                {
                    struct Data {
                        std::optional<std::string> symbol;
                        std::optional<JS::Nullable<float>> high_limit;
                        std::optional<JS::Nullable<float>> low_limit;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> contract_type;
                        JS_OBJ(symbol, high_limit, low_limit, contract_code, contract_type);
                    };
                    std::optional<std::string> status;
                    std::optional<std::vector<Data>> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures


