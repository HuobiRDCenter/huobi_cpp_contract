#pragma once

#include <string>
using std::optional<string>;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_order
            {
                struct CopytradingTraderAddMarginResponse
                {
                    std::optional<JS::Nullable<std::string>> tid;
                    struct CopytradingTraderAddMargin {
                        std::optional<JS::Nullable<std::string>> contract_code;
                        std::optional<JS::Nullable<std::string>> amount;
                        std::optional<JS::Nullable<int>> type;
                        std::optional<JS::Nullable<std::string>> position_side;
                        JS_OBJ(contract_code, amount, type, position_side);
                    };
                    std::optional<JS::Nullable<CopytradingTraderAddMargin>> data;
                    std::optional<JS::Nullable<long>> code;
                    JS_OBJ(tid, data, code);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures