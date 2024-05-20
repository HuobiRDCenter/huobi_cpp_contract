#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace coin_futures
    {
        namespace restful
        {
            namespace response_account
            {
                struct ContractPositionLimitResponse
                {
                    struct Data {
                        struct List {
                            std::optional<JS::Nullable<std::string>> contract_type;
                            std::optional<JS::Nullable<float>> buy_limit;
                            std::optional<JS::Nullable<float>> sell_limit;

                            JS_OBJ(contract_type, buy_limit, sell_limit);
                        };
                        std::optional<string> symbol;
                        std::optional<std::vector<List>> list;

                        JS_OBJ(symbol, list);
                    };
                    std::optional<string> status;
                    std::optional<std::vector<Data>> data;
                    std::optional<int64_t> ts;
                    JS_OBJ(status, data, ts);

                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

