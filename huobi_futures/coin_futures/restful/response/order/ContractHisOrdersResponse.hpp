#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace coin_futures
    {
        namespace restful
        {
            namespace response_order
            {
                struct ContractHisOrdersResponse
                {
                    struct QueryResponse {
                        int64_t query_id;
                        int64_t order_id;
                        std::string symbol;
                        std::string contract_code;
                        std::string contract_type;
                        int64_t lever_rate;
                        std::string direction;
                        std::string offset;
                        std::optional<JS::Nullable<float>> volume;
                        std::optional<JS::Nullable<float>> price;
                        int64_t create_date;
                        int64_t update_time;
                        std::string order_source;
                        std::string order_price_type;
                        std::optional<JS::Nullable<float>> margin_frozen;
                        std::optional<JS::Nullable<float>> profit;
                        std::optional<JS::Nullable<float>> trade_volume;
                        std::optional<JS::Nullable<float>> trade_turnover;
                        std::optional<JS::Nullable<float>> fee;
                        std::optional<JS::Nullable<float>> trade_avg_price;
                        int status;
                        int order_type;
                        std::string fee_asset;
                        std::string liquidation_type;
                        int is_tpsl;
                        std::optional<JS::Nullable<float>> real_profit;
                        std::optional<std::string> canceled_source;
                        JS_OBJ(query_id, order_id, symbol, contract_code, contract_type, lever_rate, direction, offset, volume, price, create_date, update_time, order_source, order_price_type, margin_frozen, profit, trade_volume, trade_turnover, fee, trade_avg_price, status, order_type, fee_asset, liquidation_type, is_tpsl, real_profit, canceled_source);
                    };
                    std::optional<JS::Nullable<int64_t>> code;
                    std::optional<string> msg;
                    std::optional<QueryResponse> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(code, msg, data, ts)
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
