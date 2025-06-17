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
                struct CopytradingTraderOpenOrdersResponse
                {
                    struct TradeData {
                        std::string contract_code;
                        std::string price;
                        std::string volume;
                        std::string margin_mode;
                        std::string position_side;
                        int order_direction;
                        int lever;
                        std::string avg_price;
                        std::string avg_volume;
                        std::string fee;

                        JS_OBJ(contract_code, price, volume, margin_mode, position_side,
                              order_direction, lever, avg_price, avg_volume, fee);
                    };

                    std::string tid;
                    std::vector<TradeData> data;
                    long code;

                    JS_OBJ(tid, data, code);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures