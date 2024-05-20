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
                struct SwapIndexResponse
                {
                    struct IndexDetails {
                        std::optional<std::string> symbol;
                        std::optional<double> index_price;
                        std::optional<int64_t> index_ts;
                        JS_OBJ(symbol, index_price, index_ts);
                    };
                    std::optional<std::string> status;
                    std::optional<int64_t> ts;
                    std::optional<std::vector<IndexDetails>> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

