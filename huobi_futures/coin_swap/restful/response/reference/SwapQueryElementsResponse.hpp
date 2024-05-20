#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace coin_swap
    {
        namespace restful
        {
            namespace response_reference
            {
                struct SwapQueryElementsResponse
                {
                    struct ContractInfo {
                        struct ContractInfos {
                            std::optional<std::string> contract_code;
                            std::optional<std::vector<int64_t>> instrument_type;
                            std::optional<std::string> create_date;
                            std::optional<JS::Nullable<int64_t>> contract_status;
                            std::optional<std::string> delivery_time;
                            std::optional<std::string> delivery_date;
                            JS_OBJ(contract_code, instrument_type, create_date, contract_status, delivery_time, delivery_date)
                        };
                        std::optional<std::vector<ContractInfos>> contract_infos;
                        std::optional<JS::Nullable<float>> transfer_profit_ratio;
                        std::optional<JS::Nullable<int64_t>> min_level;
                        std::optional<JS::Nullable<int64_t>> max_level;
                        std::optional<JS::Nullable<int64_t>> open_order_limit;
                        std::optional<JS::Nullable<int64_t>> offset_order_limit;
                        std::optional<JS::Nullable<int64_t>> long_position_limit;
                        std::optional<JS::Nullable<int64_t>> short_position_limit;
                        std::optional<JS::Nullable<int64_t>> week_hig_normal_limit;
                        std::optional<JS::Nullable<int64_t>> week_min_normal_limit;
                        std::optional<JS::Nullable<int64_t>> week_hig_open_limit;
                        std::optional<JS::Nullable<int64_t>> week_min_open_limit;
                        std::optional<JS::Nullable<int64_t>> week_hig_trade_limit;
                        std::optional<JS::Nullable<int64_t>> week_min_trade_limit;
                        std::optional<JS::Nullable<int64_t>> biweek_hig_normal_limit;
                        std::optional<JS::Nullable<int64_t>> biweek_min_normal_limit;
                        std::optional<JS::Nullable<int64_t>> biweek_hig_open_limit;
                        std::optional<JS::Nullable<int64_t>> biweek_min_open_limit;
                        std::optional<JS::Nullable<int64_t>> biweek_hig_trade_limit;
                        std::optional<JS::Nullable<int64_t>> biweek_min_trade_limit;
                        std::optional<JS::Nullable<int64_t>> quarter_hig_normal_limit;
                        std::optional<JS::Nullable<int64_t>> quarter_min_normal_limit;
                        std::optional<JS::Nullable<int64_t>> quarter_hig_open_limit;
                        std::optional<JS::Nullable<int64_t>> quarter_min_open_limit;
                        std::optional<JS::Nullable<int64_t>> quarter_hig_trade_limit;
                        std::optional<JS::Nullable<int64_t>> quarter_min_trade_limit;
                        std::optional<JS::Nullable<int64_t>> biquarter_hig_normal_limit;
                        std::optional<JS::Nullable<int64_t>> biquarter_min_normal_limit;
                        std::optional<JS::Nullable<int64_t>> biquarter_hig_open_limit;
                        std::optional<JS::Nullable<int64_t>> biquarter_min_open_limit;
                        std::optional<JS::Nullable<int64_t>> biquarter_hig_trade_limit;
                        std::optional<JS::Nullable<int64_t>> biquarter_min_trade_limit;
                        std::optional<JS::Nullable<int64_t>> real_time_settlement;
                        struct OrderLimits {
                            std::optional<std::vector<int64_t>> instrument_type;
                            std::optional<std::vector<std::string>> open;
                            std::optional<std::vector<std::string>> close;
                            JS_OBJ(instrument_type, open, close)
                        };
                        std::optional<std::vector<OrderLimits>> order_limits;
                        JS_OBJ(contract_infos , transfer_profit_ratio, min_level, max_level, open_order_limit, offset_order_limit,
                                long_position_limit, short_position_limit, week_hig_normal_limit, week_min_normal_limit,
                                week_hig_open_limit, week_min_open_limit, week_hig_trade_limit, week_min_trade_limit,
                                biweek_hig_normal_limit, biweek_min_normal_limit, biweek_hig_open_limit, biweek_min_open_limit,
                                biweek_hig_trade_limit, biweek_min_trade_limit, quarter_hig_normal_limit, quarter_min_normal_limit,
                                quarter_hig_open_limit, quarter_min_open_limit, quarter_hig_trade_limit, quarter_min_trade_limit,
                                biquarter_hig_normal_limit, biquarter_min_normal_limit, biquarter_hig_open_limit,
                                biquarter_min_open_limit, biquarter_hig_trade_limit, biquarter_min_trade_limit,
                                real_time_settlement, order_limits);
                    };
                    std::optional<JS::Nullable<string>> status;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::vector<ContractInfo> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

