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
                struct CopytradingTraderPositionListResponse
                {
                    struct CopytradingTraderPosition {
                        std::optional<JS::Nullable<std::string>> margin_mode;
                        std::optional<JS::Nullable<std::string>> position_side;
                        std::optional<JS::Nullable<std::string>> lever;
                        std::optional<JS::Nullable<std::string>> open_avg_price;
                        std::optional<JS::Nullable<std::string>> position_margin;
                        std::optional<JS::Nullable<std::string>> margin_rate;
                        std::optional<JS::Nullable<std::string>> volume;
                        std::optional<JS::Nullable<std::string>> liquidation_price;
                        std::optional<JS::Nullable<std::string>> unreal_profit;
                        std::optional<JS::Nullable<std::string>> profit;
                        std::optional<JS::Nullable<std::string>> profit_rate;
                        std::optional<JS::Nullable<std::string>> contract_code;

                        JS_OBJ(margin_mode, position_side, lever, open_avg_price, position_margin,
                              margin_rate, volume, liquidation_price, unreal_profit, profit,
                              profit_rate, contract_code);
                    };

                    struct CopytradingTraderPositionList {
                        std::optional<JS::Nullable<std::vector<CopytradingTraderPosition>>> positions;

                        JS_OBJ(positions);
                    };

                    std::optional<JS::Nullable<std::string>> tid;
                    std::optional<JS::Nullable<CopytradingTraderPositionList>> data;
                    std::optional<JS::Nullable<long>> code;

                    JS_OBJ(tid, data, code);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures