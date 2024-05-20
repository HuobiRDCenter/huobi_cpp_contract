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
                struct SwapSubAccountListResponse
                {
                    std::string status;
                    std::optional<int64_t> ts;
                    struct Data {
                        struct List {
                            std::optional<std::string> symbol;
                            std::optional<std::string> contract_code;
                            std::optional<JS::Nullable<float>> margin_balance;
                            std::optional<JS::Nullable<float>> liquidation_price;
                            std::optional<JS::Nullable<float>> risk_rate;
                            std::optional<JS::Nullable<int64_t>> query_id;
                            JS_OBJ(symbol, margin_balance, liquidation_price, risk_rate, query_id);
                        };
                        std::optional<std::vector<List>> list;
                        std::optional<int64_t> sub_uid;
                        JS_OBJ(list, sub_uid);
                    };
                    std::optional<Data> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

