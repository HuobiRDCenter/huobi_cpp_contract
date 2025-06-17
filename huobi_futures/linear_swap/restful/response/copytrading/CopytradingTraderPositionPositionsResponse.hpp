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
                struct CopytradingTraderPositionPositionsResponse
                {
                    struct CopytradingTraderPositionPosition {
                        std::optional<JS::Nullable<std::string>> sub_position_id;
                        std::optional<JS::Nullable<std::string>> margin_mode;
                        std::optional<JS::Nullable<std::string>> position_side;
                        std::optional<JS::Nullable<std::string>> lever;
                        std::optional<JS::Nullable<std::string>> open_order_id;
                        std::optional<JS::Nullable<std::string>> open_avg_price;
                        std::optional<JS::Nullable<int64_t>> open_time;
                        std::optional<JS::Nullable<std::string>> volume;
                        std::optional<JS::Nullable<int64_t>> close_time;
                        std::optional<JS::Nullable<std::string>> close_avg_price;
                        std::optional<JS::Nullable<std::string>> open_fee;
                        std::optional<JS::Nullable<std::string>> close_fee;
                        std::optional<JS::Nullable<std::string>> profit;
                        std::optional<JS::Nullable<std::string>> profit_rate;
                        std::optional<JS::Nullable<int32_t>> close_type;
                        std::optional<JS::Nullable<std::string>> follow_takes;

                        JS_OBJ(sub_position_id, margin_mode, position_side, lever, open_order_id, open_avg_price,
                              open_time, volume, close_time, close_avg_price, open_fee, close_fee, profit,
                              profit_rate, close_type, follow_takes);
                    };

                    struct CopytradingTraderPositionPositions {
                        std::optional<JS::Nullable<std::vector<CopytradingTraderPositionPosition>>> positions;
                        std::optional<JS::Nullable<int64_t>> query_id;

                        JS_OBJ(positions, query_id);
                    };

                    std::optional<JS::Nullable<std::string>> tid;
                    std::optional<JS::Nullable<Data>> data;
                    std::optional<JS::Nullable<int64_t>> code;

                    JS_OBJ(tid, data, code);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures