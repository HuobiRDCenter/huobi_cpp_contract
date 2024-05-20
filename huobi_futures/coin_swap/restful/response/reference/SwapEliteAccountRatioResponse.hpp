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
                struct SwapEliteAccountRatioResponse
                {
                    struct RatioData {
                        std::optional<JS::Nullable<float>> buy_ratio;
                        std::optional<JS::Nullable<float>> sell_ratio;
                        std::optional<JS::Nullable<float>> locked_ratio;
                        std::optional<JS::Nullable<int64_t>> ts;
                        JS_OBJ(buy_ratio, sell_ratio, locked_ratio, ts);
                    };

                    struct Data {
                        std::string symbol;
                        RatioData ratio_data;
                        JS_OBJ(symbol, ratio_data);
                    };

                    std::string status;
                    int64_t ts;
                    std::optional<Data> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

