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
            namespace response_account
            {
                struct SwapOrderLimitResponse
                {
                    std::optional<JS::Nullable<int64_t>> status;
                    std::optional<JS::Nullable<int64_t>> ts;

                    struct Data {
                        std::optional<std::string> order_price_type;

                        struct List {
                            std::optional<std::string> symbol;
                            std::optional<std::string> contract_code;
                            std::optional<JS::Nullable<int64_t>> open_limit;
                            std::optional<JS::Nullable<int64_t>> close_limit;
                            JS_OBJ(symbol, contract_code, open_limit, close_limit);
                        };

                        std::optional<std::vector<List>> list;

                        JS_OBJ(order_price_type, list);
                    };

                    std::optional<Data> data;

                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

