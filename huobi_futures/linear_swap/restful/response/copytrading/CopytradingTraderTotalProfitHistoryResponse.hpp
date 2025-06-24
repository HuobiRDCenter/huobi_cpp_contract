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
                struct CopytradingTraderTotalProfitHistoryResponse
                {
                    struct CopytradingTraderTotalProfit {
                        std::optional<JS::Nullable<std::string>> profit_currency;
                        std::optional<JS::Nullable<std::string>> total_profit_amont;

                        JS_OBJ(profit_currency, total_profit_amont);
                    };

                    struct CopytradingTraderTotalProfitHistory {
                        std::optional<JS::Nullable<std::vector<CopytradingTraderTotalProfit>>> items;

                        JS_OBJ(items);
                    };

                    std::optional<JS::Nullable<std::string>> tid;
                    std::optional<JS::Nullable<CopytradingTraderTotalProfitHistory>> data;
                    std::optional<JS::Nullable<long>> code;

                    JS_OBJ(tid, data, code);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures