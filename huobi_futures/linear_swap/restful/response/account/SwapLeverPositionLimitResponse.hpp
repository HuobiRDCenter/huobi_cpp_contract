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
            namespace response_account
            {
                struct SwapLeverPositionLimitResponse
                {
                    struct List {
                        std::optional<JS::Nullable<int64_t>> lever_rate;
                        std::optional<JS::Nullable<float>> buy_limit_value;
                        std::optional<JS::Nullable<float>> sell_limit_value;
                        JS_OBJ(lever_rate, buy_limit_value, sell_limit_value);
                    };

                    struct Data {
                        std::optional<string> symbol;
                        std::optional<string> contract_code;
                        std::optional<string> margin_mode;
                        std::vector<List> list;
                        JS_OBJ(symbol, contract_code, margin_mode, list);
                    };
                    std::optional<JS::Nullable<std::optional<string>>> status;
                    std::optional<std::vector<Data>> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
