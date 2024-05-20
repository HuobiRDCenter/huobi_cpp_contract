#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_reference
            {
                struct GetSwapQueryElementsResponse
                {

                    struct OrderLimits {
                        std::optional<JS::Nullable<int64_t>> instrument_type;
                        std::optional<std::string> open;
                        std::optional<std::string> open_after_closing;
                        std::optional<std::string> close;
                        JS_OBJ(instrument_type, open, open_after_closing, close);
                    };

                    struct NormalLimits {
                        std::optional<JS::Nullable<int64_t>> instrument_type;
                        std::optional<std::string> open;
                        std::optional<std::string> close;
                        JS_OBJ(instrument_type, open, close);
                    };

                    struct OpenLimits {
                        std::optional<JS::Nullable<int64_t>> instrument_type;
                        std::optional<std::string> open;
                        std::optional<std::string> close;
                        JS_OBJ(instrument_type, open, close);
                    };

                    struct TradeLimits {
                        std::optional<JS::Nullable<int64_t>> instrument_type;
                        std::optional<std::string> open;
                        std::optional<std::string> close;
                        JS_OBJ(instrument_type, open, close);
                    };

                    struct PriceTicks {
                        std::optional<JS::Nullable<int64_t>> business_type;
                        std::optional<string> price;
                        JS_OBJ(business_type, price);
                    };

                    struct ContractInfos {
                        std::optional<string> contract_code;
                        std::optional<JS::Nullable<int64_t>> instrument_type;
                        std::optional<string> settlement_date;
                        std::optional<string> delivery_time;
                        std::optional<string> create_date;
                        std::optional<JS::Nullable<int64_t>> contract_status;
                        std::optional<string> delivery_date;
                        JS_OBJ(contract_code, instrument_type, settlement_date, delivery_time, create_date, contract_status, delivery_date);
                    };

                    struct Data {
                        std::optional<string> contract_code;
                        std::optional<string> funding_rate_cap;
                        std::optional<string> funding_rate_floor;
                        std::optional<string> instrument_index_code;
                        std::optional<string> min_level;
                        std::optional<string> max_level;
                        std::optional<string> price_tick;
                        std::optional<string> instrument_value;
                        std::optional<string> trade_partition;
                        std::optional<string> open_order_limit;
                        std::optional<string> offset_order_limit;
                        std::optional<string> long_position_limit;
                        std::optional<string> short_position_limit;
                        std::optional<JS::Nullable<int64_t>> mode_type;
                        std::optional<JS::Nullable<int64_t>> swap_delivery_type;
                        std::optional<JS::Nullable<int64_t>> settle_period;
                        std::optional<JS::Nullable<int64_t>> real_time_settlement;
                        std::optional<JS::Nullable<int64_t>> transfer_profit_ratio;
                        std::optional<JS::Nullable<int64_t>> cross_transfer_profit_ratio;
                        std::optional<std::vector<int64_t>> instrument_type;
                        std::optional<std::vector<ContractInfos>> contract_infos;
                        std::optional<std::vector<PriceTicks>> price_ticks;
                        std::optional<std::vector<OrderLimits>> order_limits;
                        std::optional<std::vector<NormalLimits>> normal_limits;
                        std::optional<std::vector<OpenLimits>> open_limits;
                        std::optional<std::vector<TradeLimits>> trade_limits;
                        std::optional<JS::Nullable<int64_t>> ts;
                        JS_OBJ(contract_code, funding_rate_cap, funding_rate_floor, instrument_index_code, min_level, max_level,
                                price_tick, instrument_value, trade_partition, open_order_limit, offset_order_limit, long_position_limit,
                                short_position_limit, mode_type, swap_delivery_type, settle_period, real_time_settlement, transfer_profit_ratio,
                                cross_transfer_profit_ratio, instrument_type, contract_infos, price_ticks, order_limits, normal_limits, open_limits,
                                trade_limits);
                    };

                    struct ContractInfo {
                        std::string contract_code;
                        std::vector<std::string> instrument_type;
                        std::string settlement_date;
                        std::string delivery_time;
                        std::string create_date;
                        int contract_status;
                        std::string delivery_date;
                        JS_OBJ(contract_code, instrument_type, settlement_date, delivery_time, create_date, contract_status, delivery_date);
                    };
                    std::optional<string> status;
                    std::optional<std::vector<Data>> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures

