#pragma once

#include <string>
#include <vector>
#include <optional>
#include "huobi_futures/json_struct/json_struct.h"

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_copytradingtrader
            {
                struct CopytradingTraderStatisticsResponse
                {
                    struct ProfitDetail
                    {
                        std::optional<std::string> pnlRate;
                        std::optional<std::string> pnl;
                        std::optional<std::string> ts;
                        JS_OBJ(pnlRate, pnl, ts);
                    };

                    struct Data
                    {
                        std::optional<std::string> instType;
                        std::optional<std::string> totalFollowerNum;
                        std::optional<std::string> curFollowerNum;
                        std::optional<std::string> totalPnl;
                        std::optional<std::string> followerTotalPnl;
                        std::optional<std::string> winRate;
                        std::optional<std::string> winNum;
                        std::optional<std::string> lossNum;
                        std::optional<std::vector<ProfitDetail>> profitDetails90d;
                        JS_OBJ(instType, totalFollowerNum, curFollowerNum, totalPnl, followerTotalPnl,
                               winRate, winNum, lossNum, profitDetails90d);
                    };
                    std::optional<std::vector<Data>> data;
                    std::optional<JS::Nullable<std::string>> code;
                    std::optional<std::string> msg;
                    std::optional<JS::Nullable<long>> ts;
                    JS_OBJ(data, code, msg, ts);
                };
            }
        }
    }
}