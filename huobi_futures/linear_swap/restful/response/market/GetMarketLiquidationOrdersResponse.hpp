// huobi_futures/linear_swap/restful/response_market/GetMarketLiquidationOrdersResponse.hpp
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
                struct GetMarketLiquidationOrdersResponse
                {
                    struct Data
                    {
                        std::optional<std::string> id;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> liquidation_time;
                        std::optional<std::string> side;
                        std::optional<std::string> position_side;
                        std::optional<std::string> volume;
                        std::optional<std::string> amount;
                        std::optional<std::string> bankrupt_price;
                        std::optional<std::string> trade_turnover;

                        JS_OBJ(id, contract_code, liquidation_time, side, position_side, volume, amount, bankrupt_price, trade_turnover);
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