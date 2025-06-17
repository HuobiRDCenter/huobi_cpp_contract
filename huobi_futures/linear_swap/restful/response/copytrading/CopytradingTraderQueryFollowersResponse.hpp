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
                struct CopytradingTraderQueryFollowersResponse
                {
                    struct Follower {
                        std::optional<JS::Nullable<std::string>> follower_head_pic;
                        std::optional<JS::Nullable<std::string>> follower_name;
                        std::optional<JS::Nullable<std::string>> follower_uid;
                        std::optional<JS::Nullable<long>> follower_time;
                        std::optional<JS::Nullable<std::string>> follower_profit_amont;
                        std::optional<JS::Nullable<std::string>> follower_trade_amount;
                        JS_OBJ(follower_head_pic, follower_name, follower_uid, follower_time, follower_profit_amont, follower_trade_amount);
                    };

                    struct CopytradingTraderQueryFollowers {
                        std::optional<JS::Nullable<std::vector<Follower>>> follower;
                        std::optional<JS::Nullable<std::string>> query_id;
                        JS_OBJ(follower, query_id);
                    };

                    std::optional<JS::Nullable<std::string>> tid;
                    std::optional<JS::Nullable<CopytradingTraderQueryFollowers>> data;
                    std::optional<JS::Nullable<long>> code;
                    JS_OBJ(tid, data, code);

                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures