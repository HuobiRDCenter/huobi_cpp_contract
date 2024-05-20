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
                struct LinearSwapOverViewAccountInfoResponse
                {
                    struct MarginData {
                        std::optional<std::string> margin_asset;
                        std::optional<JS::Nullable<double>> margin_balance;
                        std::optional<JS::Nullable<double>> margin_available;

                        JS_OBJ(margin_asset, margin_balance, margin_available);
                    };
                    std::optional<JS::Nullable<int64_t>> code;
                    std::optional<std::string> msg;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<std::vector<MarginData>> data;

                    JS_OBJ(code, msg, ts, data);
                };
            } // namespace response_unified_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures

