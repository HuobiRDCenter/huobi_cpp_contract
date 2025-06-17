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
            namespace response_order
            {
                struct CopytradingTraderProfitHistoryDetailsResponse
                {
                    struct ProfitItem {
                        std::optional<JS::Nullable<std::string>> user_id;
                        std::optional<JS::Nullable<std::string>> profit_currency;
                        std::optional<JS::Nullable<std::string>> profit_amont;
                        std::optional<JS::Nullable<std::string>> profit_time;

                        JS_OBJ(user_id, profit_currency, profit_amont, profit_time);
                    };

                    struct CopytradingTraderProfitHistoryDetails {
                        std::optional<JS::Nullable<std::vector<ProfitItem>>> profit_items;
                        std::optional<JS::Nullable<int64_t>> query_id;

                        JS_OBJ(profit_items, query_id);
                    };

                    std::optional<JS::Nullable<std::string>> tid;
                    std::optional<JS::Nullable<CopytradingTraderProfitHistoryDetails>> data;
                    std::optional<JS::Nullable<int64_t>> code;

                    JS_OBJ(tid, data, code);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures