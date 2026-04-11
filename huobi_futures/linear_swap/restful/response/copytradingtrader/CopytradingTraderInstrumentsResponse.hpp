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
                struct CopytradingTraderInstrumentsResponse
                {
                    struct Data
                    {
                        std::optional<std::string> instId;
                        std::optional<std::string> instType;
                        JS_OBJ(instId, instType);
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