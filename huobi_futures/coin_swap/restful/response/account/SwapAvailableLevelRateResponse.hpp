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
                struct SwapAvailableLevelRateResponse
                {
                    struct AvailableLevelRate {
                        std::optional<std::string> symbol;
                        std::optional<std::string> available_level_rate;
                        JS_OBJ(symbol, available_level_rate);
                    };
                    std::optional<std::string> status;
                    std::optional<int64_t> ts;
                    std::vector<AvailableLevelRate> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

