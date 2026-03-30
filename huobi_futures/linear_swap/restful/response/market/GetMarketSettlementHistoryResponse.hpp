// huobi_futures/linear_swap/restful/response_market/GetMarketSettlementHistoryResponse.hpp
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
            namespace response_market
            {
                struct GetMarketSettlementHistoryResponse
                {
                    struct Data
                    {
                        std::optional<std::string> id;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> settlement_time;
                        std::optional<std::string> clawback_ratio;
                        std::optional<std::string> settlement_price;

                        JS_OBJ(id, contract_code, settlement_time, clawback_ratio, settlement_price);
                    };

                    std::optional<int32_t> code;
                    std::optional<std::vector<Data>> data;
                    std::optional<std::string> message;
                    std::optional<int64_t> ts;

                    JS_OBJ(code, data, message, ts);
                };
            }
        }
    }
}