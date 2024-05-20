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
                struct ContractMatchResultsResponse
                {
                    struct TradeData {
                        std::optional<JS::Nullable<long>> order_id;
                        std::optional<string> order_id_str;
                        std::optional<string> symbol;
                        std::optional<string> contract_type;
                        std::optional<string> contract_code;
                        std::optional<string> direction;
                        std::optional<string> offset;
                        std::optional<double> trade_volume;
                        std::optional<double> trade_price;
                        std::optional<double> trade_turnover;
                        std::optional<long> create_date;
                        std::optional<double> offset_profitloss;
                        std::optional<double> trade_fee;
                        std::optional<string> role;
                        std::optional<double> real_profit;
                        std::optional<string> fee_asset;
                        std::optional<string> order_source;
                        JS_OBJ(order_id, order_id_str, symbol, contract_type, contract_code, direction, offset, trade_volume, trade_price, trade_turnover, create_date, offset_profitloss, trade_fee, role, real_profit, fee_asset, order_source);
                    };
                    std::optional<JS::Nullable<int64_t>> code;
                    std::optional<string> msg;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<std::vector<TradeData>> data;
                    JS_OBJ(code, msg, ts, data);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
