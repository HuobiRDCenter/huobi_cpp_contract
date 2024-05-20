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
                struct ContractOrderDetailResponse
                {
                    struct OrderInfo
                    {
                        std::string symbol;
                        std::string contract_type;
                        std::string contract_code;
                        int64_t lever_rate;
                        std::string direction;
                        std::string offset;
                        std::optional<JS::Nullable<float>> volume;
                        std::optional<JS::Nullable<float>> price;
                        int64_t created_at;
                        int64_t canceled_at;
                        std::string order_source;
                        std::string order_price_type;
                        std::optional<JS::Nullable<float>> margin_frozen;
                        std::optional<JS::Nullable<float>> profit;
                        std::string canceled_source;
                        int total_page;
                        int current_page;
                        int total_size;
                        std::optional<JS::Nullable<float>> instrument_price;
                        std::optional<JS::Nullable<float>> final_interest;
                        std::optional<JS::Nullable<float>> adjust_value;
                        std::string fee_asset;
                        std::string liquidation_type;
                        int64_t order_id;
                        std::string order_id_str;
                        int64_t client_order_id;
                        std::optional<JS::Nullable<float>> trade_volume;
                        std::optional<JS::Nullable<float>> trade_turnover;
                        std::optional<JS::Nullable<float>> fee;
                        std::optional<JS::Nullable<float>> trade_avg_price;
                        int status_int;
                        int order_type;
                        int is_tpsl;
                        std::optional<JS::Nullable<float>> real_profit;
                        std::vector<TradeInfo> trades;
                        JS_OBJ(status, symbol, contract_type, contract_code, lever_rate, direction, offset, volume, price, created_at, canceled_at, order_source, order_price_type, margin_frozen, profit, canceled_source, total_page, current_page, total_size, instrument_price, final_interest, adjust_value, fee_asset, liquidation_type, order_id, order_id_str, client_order_id, trade_volume, trade_turnover, fee, trade_avg_price, status_int, order_type, is_tpsl, real_profit, trades);
                    };
                    struct TradeInfo
                    {
                        std::string id;
                        int64_t trade_id;
                        std::optional<JS::Nullable<float>> trade_price;
                        std::optional<JS::Nullable<float>> trade_volume;
                        std::optional<JS::Nullable<float>> trade_turnover;
                        std::optional<JS::Nullable<float>> trade_fee;
                        std::string role;
                        int64_t created_at;
                        std::optional<JS::Nullable<float>> real_profit;
                        std::optional<JS::Nullable<float>> profit;
                        JS_OBJ(id, trade_id, trade_price, trade_volume, trade_turnover, trade_fee, role, created_at, real_profit, profit);
                    };
                    std::string status;
                    OrderInfo data;
                    int ts;
                    JS_OBJ(status, data, ts);

                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
