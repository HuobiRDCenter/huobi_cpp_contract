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
                struct ContractOpenOrdersResponse
                {
                    std::optional<std::string> status;
                    struct Data {
                        struct Order{
                            std::optional<std::string> orders;
                            std::optional<std::string> symbol;
                            std::optional<std::string> contract_type;
                            std::optional<std::string> contract_code;
                            std::optional<std::string> volume;
                            std::optional<std::string> price;
                            std::optional<std::string> order_price_type;
                            std::optional<std::string> order_type;
                            std::optional<std::string> direction;
                            std::optional<std::string> offset;
                            std::optional<std::string> lever_rate;
                            std::optional<std::string> order_id;
                            std::optional<std::string> order_id_str;
                            std::optional<std::string> client_order_id;
                            std::optional<std::string> created_at;
                            std::optional<std::string> trade_volume;
                            std::optional<std::string> trade_turnover;
                            std::optional<std::string> fee;
                            std::optional<std::string> trade_avg_price;
                            std::optional<std::string> margin_frozen;
                            std::optional<std::string> profit;
                            std::optional<std::string> is_tpsl;
                            std::optional<std::string> order_source;
                            std::optional<std::string> fee_asset;
                            std::optional<std::string> update_time;
                            std::optional<std::string> real_profit;
                            JS_OBJ(orders, symbol, contract_type, contract_code, volume, price, order_price_type, order_type, direction, offset, lever_rate, order_id, order_id_str, client_order_id, created_at, trade_volume, trade_turnover, fee, trade_avg_price, margin_frozen, profit, is_tpsl, status, order_source, fee_asset, update_time, real_profit);
                        };
                        std::optional<std::string> total_page;
                        std::optional<std::string> current_page;
                        std::optional<std::string> total_size;
                        std::vector<Order> orders;
                        JS_OBJ(total_page, current_page, total_size, orders)
                    };
                    std::optional<std::string> status;
                    std::optional<Data> data;
                    std::optional<int64_t> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
