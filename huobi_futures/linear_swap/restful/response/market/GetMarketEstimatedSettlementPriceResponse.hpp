// huobi_futures/linear_swap/restful/response_market/GetMarketEstimatedSettlementPriceResponse.hpp
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
                struct GetMarketEstimatedSettlementPriceResponse
                {
                    struct Data
                    {
                        std::optional<std::string> contract_code;
                        std::optional<std::string> settlement_type;
                        std::optional<std::string> estimated_settlement_price;

                        JS_OBJ(contract_code, settlement_type, estimated_settlement_price);
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