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
                struct CopytradingTraderCurrentPositionsResponse
                {
                    struct CopytradingTraderCurrentPosition {
                        std::optional<JS::Nullable<std::string>> sub_position_id;
                        std::optional<JS::Nullable<std::string>> margin_mode;
                        std::optional<JS::Nullable<std::string>> position_side;
                        std::optional<JS::Nullable<std::string>> lever;
                        std::optional<JS::Nullable<std::string>> open_order_id;
                        std::optional<JS::Nullable<std::string>> open_avg_price;
                        std::optional<JS::Nullable<std::string>> open_fee;
                        std::optional<JS::Nullable<int64_t>> open_time;
                        std::optional<JS::Nullable<std::string>> position_margin;
                        std::optional<JS::Nullable<std::string>> volume;
                        std::optional<JS::Nullable<std::string>> liquidation_price;
                        std::optional<JS::Nullable<std::string>> tp_trigger_price;
                        std::optional<JS::Nullable<std::string>> sl_trigger_price;

                        JS_OBJ(sub_position_id, margin_mode, position_side, lever, open_order_id,
                               open_avg_price, open_fee, open_time, position_margin, volume,
                               liquidation_price, tp_trigger_price, sl_trigger_price);
                    };

                    struct CopytradingTraderCurrentPositions {
                        std::optional<JS::Nullable<std::vector<CopytradingTraderCurrentPosition>>> positions;
                        std::optional<JS::Nullable<int64_t>> query_id;

                        JS_OBJ(positions, query_id);
                    };
                    std::optional<JS::Nullable<std::string>> tid;
                    std::optional<JS::Nullable<CopytradingTraderCurrentPositions>> data;
                    std::optional<JS::Nullable<int64_t>> code;

                    JS_OBJ(tid, data, code);

                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures