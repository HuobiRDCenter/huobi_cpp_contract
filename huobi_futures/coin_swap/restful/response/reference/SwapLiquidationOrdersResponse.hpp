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
                struct SwapLiquidationOrdersResponse
                {
                    struct Data {
                        std::optional<JS::Nullable<int64_t>> query_id;
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> direction;
                        std::optional<std::string> offset;
                        std::optional<JS::Nullable<float>> volume;
                        std::optional<JS::Nullable<float>> amount;
                        std::optional<JS::Nullable<float>> price;
                        std::optional<JS::Nullable<int64_t>> created_at;
                        JS_OBJ(query_id, symbol, contract_code, direction, offset, volume, amount, price, created_at);
                    };
                    std::optional<JS::Nullable<int64_t>> code;
                    std::optional<std::string> msg;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<Data> data;
                    JS_OBJ(code, msg, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

