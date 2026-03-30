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
                struct CopytradingTraderFollowersResponse
                {
                    struct Data
                    {
                        std::optional<std::string> id;
                        std::optional<std::string> instType;
                        std::optional<std::string> followerAvatarLink;
                        std::optional<std::string> followerName;
                        std::optional<std::string> followerUid;
                        std::optional<std::string> followTime;
                        std::optional<std::string> followerAssetAmt;
                        std::optional<std::string> followerProfitSharingAmt;
                        std::optional<std::string> followerTradeAmt;
                        std::optional<std::string> totalProfitSharingAmt;
                        JS_OBJ(id, instType, followerAvatarLink, followerName, followerUid, 
                               followTime, followerAssetAmt, followerProfitSharingAmt, 
                               followerTradeAmt, totalProfitSharingAmt);
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