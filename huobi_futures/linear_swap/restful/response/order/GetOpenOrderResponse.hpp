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
            namespace response_order
            {
                struct GetOpenOrderResponse
                {
                    string status;

                    std::optional<int32_t> err_code;

                    std::optional<string> err_msg;

                    struct Data
                    {
                        struct Order
                        {
                            string symbol;

                            string contract_code;

                            int32_t volume;

                            float price;

                            string order_price_type;

                            int32_t order_type;

                            string direction;

                            string offset;

                            int32_t lever_rate;

                            int64_t order_id;

                            string order_id_str;

                            JS::Nullable<int64_t> client_order_id;

                            int64_t created_at;

                            float trade_volume;

                            float trade_turnover;

                            float fee;

                            string fee_asset;

                            JS::Nullable<float> trade_avg_price;

                            float margin_frozen;

                            string margin_asset;

                            float profit;

                            int32_t status;

                            string order_source;

                            JS::Nullable<string> liquidation_type;

                            JS::Nullable<int64_t> canceled_at;

                            string margin_mode;

                            string margin_account;

                            int32_t is_tpsl;

                            int64_t update_time;

                            float real_profit;
                            std::optional<JS::Nullable<float>> reduce_only;

                            std::optional<string> contract_type;

                            std::optional<string> pair;

                            std::optional<string> business_type;

                            JS_OBJ(symbol, contract_code, volume, price, order_price_type, order_type, direction, offset,
                                   lever_rate, order_id, order_id_str, client_order_id, created_at, trade_volume,
                                   trade_turnover, fee, fee_asset, trade_avg_price, margin_frozen, margin_asset, profit,
                                   status, order_source, liquidation_type, canceled_at, margin_mode, margin_account,
                                   is_tpsl, update_time, real_profit, reduce_only, contract_type, pair, business_type);
                        };

                        std::vector<Order> orders;

                        int32_t total_page;

                        int32_t current_page;

                        int32_t total_size;

                        JS_OBJ(orders, total_page, current_page, total_size);
                    };
                    std::optional<Data> data;

                    int64_t ts;

                    JS_OBJ(status, err_code, err_msg, data, ts);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures