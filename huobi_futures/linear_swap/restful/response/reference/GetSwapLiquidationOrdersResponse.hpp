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
            namespace response_reference
            {
                struct GetSwapLiquidationOrdersResponse
                {

                    struct Data {
                        std::optional<JS::Nullable<int64_t>> query_id;
                        std::optional<string> symbol;
                        std::optional<string> contract_code;
                        std::optional<JS::Nullable<int64_t>> created_at;
                        std::optional<string> direction;
                        std::optional<string> offset;
                        std::optional<JS::Nullable<float>> volume;
                        std::optional<JS::Nullable<float>> amount;
                        std::optional<JS::Nullable<float>> price;
                        std::optional<JS::Nullable<float>> trade_turnover;
                        std::optional<string> pair;
                        std::optional<string> business_type;

                        JS_OBJ(query_id, symbol, contract_code, created_at, direction, offset, volume, amount, price, trade_turnover, pair, business_type);
                    };

                    std::optional<JS::Nullable<int64_t>> code;
                    std::optional<string> msg;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::vector<Data> data;

                    JS_OBJ(code, msg, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
