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
            namespace response_account
            {
                struct SwapBalanceValuationResponse
                {
                    std::optional<Nullable<int64_t>> status;
                    struct Data {
                        std::optional<std::string> valuation_asset;
                        std::optional<std::string> balance;
                        JS_OBJ(valuation_asset, balance);
                    };
                    std::optional<std::vector<Data>> data;
                    std::optional<Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

