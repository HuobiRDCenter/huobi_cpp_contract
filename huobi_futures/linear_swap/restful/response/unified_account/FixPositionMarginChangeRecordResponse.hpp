#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_unified_account
            {
                struct FixPositionMarginChangeRecordResponse
                {
                    struct AdjustmentData {
                        std::optional<JS::Nullable<int64_t>> query_id;
                        std::optional<std::string> order_id;
                        std::optional<JS::Nullable<double>> amount;
                        std::optional<std::string> asset;
                        std::optional<std::string> symbol;
                        std::optional<JS::Nullable<int64_t>> type;
                        std::optional<JS::Nullable<int64_t>> direction;

                        JS_OBJ(query_id, order_id, amount, asset, symbol, type, direction);
                    };
                    std::optional<JS::Nullable<int64_t>> code;
                    std::optional<std::string> msg;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<std::vector<AdjustmentData>> data;

                    JS_OBJ(code, msg, ts, data);
                };
            } // namespace response_unified_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures


