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
                struct SwapCrossLeverPositionLimitResponse
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
                        std::optional<string> business_type;
                        std::optional<string> contract_type;
                        std::optional<string> pair;
                        std::optional<std::vector<List>> list;
                        JS_OBJ(symbol, contract_code, margin_mode, business_type, contract_type, pair, list);
                    };
                    std::optional<std::optional<string>> status;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<std::vector<Data>> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
