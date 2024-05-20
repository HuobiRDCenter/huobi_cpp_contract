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
                struct SwapAdjustFactorResponse
                {
                    struct LadderData {
                        struct List {
                            struct Ladders {
                                std::optional<JS::Nullable<float>> min_size;
                                std::optional<JS::Nullable<float>> max_size;
                                std::optional<int64_t> ladder;
                                std::optional<JS::Nullable<float>> adjust_factor;
                                JS_OBJ(min_size, max_size, ladder, adjust_factor);
                            };
                            std::optional<JS::Nullable<float>> lever_rate;
                            std::optional<std::vector<Ladders>> ladders;
                            JS_OBJ(lever_rate, ladders);
                        };
                        std::optional<std::string> symbol;
                        std::optional<std::vector<List>> list;
                        JS_OBJ(symbol, list);
                    };
                    std::optional<std::string> status;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<LadderData> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

