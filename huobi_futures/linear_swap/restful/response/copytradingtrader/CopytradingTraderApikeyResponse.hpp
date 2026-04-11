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
                struct CopytradingTraderApikeyResponse
                {
                    struct Data
                    {
                        std::optional<std::string> label;
                        std::optional<std::string> accessKey;
                        std::optional<std::string> secretKey;
                        std::optional<std::vector<std::string>> perm;
                        std::optional<std::string> ts;
                        JS_OBJ(label, accessKey, secretKey, perm, ts);
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