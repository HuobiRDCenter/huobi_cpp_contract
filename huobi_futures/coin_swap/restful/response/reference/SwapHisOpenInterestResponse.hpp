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
                struct SwapHisOpenInterestResponse
                {
                    struct TickData {
                        std::optional<std::string> volume;
                        std::optional<JS::Nullable<int64_t>> amount_type;
                        std::optional<JS::Nullable<int64_t>> ts;
                        JS_OBJ(volume, amount_type, ts);
                    };

                    struct Data {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_type;
                        std::optional<std::vector<TickData>> tick;
                        JS_OBJ(symbol, contract_type, tick);
                    };
                    std::optional<std::string> status;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<Data> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

