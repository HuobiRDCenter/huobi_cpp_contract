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
                struct CopytradingTraderOrderTotalDetailResponse
                {
                    struct Last24HoursProfit {
                        std::optional<JS::Nullable<std::string>> rate;
                        std::optional<JS::Nullable<std::string>> amount;
                        std::optional<JS::Nullable<std::string>> ts;

                        JS_OBJ(rate, amount, ts);
                    };

                    struct Last90DaysProfit {
                        std::optional<JS::Nullable<std::string>> rate;
                        std::optional<JS::Nullable<std::string>> amount;
                        std::optional<JS::Nullable<std::string>> ts;

                        JS_OBJ(rate, amount, ts);
                    };

                    struct CopytradingTraderOrderTotalDetail {
                        std::optional<JS::Nullable<std::string>> total_follower_num;
                        std::optional<JS::Nullable<std::string>> current_follower_num;
                        std::optional<JS::Nullable<std::string>> total_pl;
                        std::optional<JS::Nullable<std::string>> win_rate;
                        std::optional<JS::Nullable<std::vector<Last24HoursProfit>>> last_24_hours_profit;
                        std::optional<JS::Nullable<std::vector<Last90DaysProfit>>> last_90_days_profit;

                        JS_OBJ(total_follower_num, current_follower_num, total_pl, win_rate, last_24_hours_profit, last_90_days_profit);
                    };

                    std::optional<JS::Nullable<std::string>> tid;
                    std::optional<JS::Nullable<CopytradingTraderOrderTotalDetail>> data;
                    std::optional<JS::Nullable<long>> code;

                    JS_OBJ(tid, data, code);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures