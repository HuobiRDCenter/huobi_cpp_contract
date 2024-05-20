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
            namespace response_reference
            {
                struct ContractLadderMarginResponse
                {
                    struct LadderData {
                        std::optional<JS::Nullable<float>> min_margin_balance;
                        std::optional<JS::Nullable<float>> max_margin_balance;
                        std::optional<JS::Nullable<float>> min_margin_available;
                        std::optional<JS::Nullable<float>> max_margin_available;
                        JS_OBJ(min_margin_balance, max_margin_balance, min_margin_available, max_margin_available);
                    };

                    struct ListData {
                        int64_t lever_rate;
                        std::vector<LadderData> ladders;
                        JS_OBJ(lever_rate, ladders);
                    };

                    struct Data {
                        std::string symbol;
                        std::vector<ListData> list;
                        JS_OBJ(symbol, list);
                    };
                    std::string status;
                    std::vector<std::vector<Data>> data;
                    JS_OBJ(status, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

