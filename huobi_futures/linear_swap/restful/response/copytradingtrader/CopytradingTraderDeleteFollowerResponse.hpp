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
                struct CopytradingTraderDeleteFollowerResponse
                {
                    struct Data
                    {
                        std::optional<std::string> followerUid;
                        std::optional<std::string> sCode;
                        std::optional<std::string> sMsg;
                        JS_OBJ(followerUid, sCode, sMsg);
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