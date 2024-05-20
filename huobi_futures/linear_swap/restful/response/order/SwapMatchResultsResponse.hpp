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
                struct SwapMatchResultsResponse
                {
                    struct Data {
                        std::optional<JS::Nullable<int64_t>> id;
                        std::optional<JS::Nullable<int64_t>> query_id;
                        std::optional<JS::Nullable<int64_t>> match_id;
                        std::optional<JS::Nullable<int64_t>> order_id;
                        std::optional<std::string> order_id_str;
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> margin_mode;
                        std::optional<std::string> margin_account;
                        std::optional<std::string> direction;
                        std::optional<std::string> offset;
                        std::optional<JS::Nullable<float>> trade_volume;
                        std::optional<JS::Nullable<float>> trade_price;
                        std::optional<JS::Nullable<float>> trade_turnover;
                        std::optional<JS::Nullable<int64_t>>> create_date;
                        std::optional<JS::Nullable<float>> offset_profitloss;
                        std::optional<JS::Nullable<float>> real_profit;
                        std::optional<JS::Nullable<float>> trade_fee;
                        std::optional<std::string> role;
                        std::optional<std::string> fee_asset;
                        std::optional<std::string> ht_price;
                        std::optional<std::string> order_source;
                        std::optional<std::string> contract_type;
                        std::optional<std::string> pair;
                        std::optional<std::string> business_type;
                        std::optional<JS::Nullable<int64_t>> reduce_only;
                        JS_OBJ(id, query_id, match_id, order_id, order_id_str, symbol, contract_code, margin_mode, margin_account, direction, offset,
                                trade_volume, trade_price, trade_turnover, create_date, offset_profitloss, real_profit, trade_fee, role, fee_asset, ht_price, order_source, contract_type, pair, business_type, reduce_only);
                    };
                    std::optional<JS::Nullable<int64_t>> code;
                    std::optional<std::string> msg;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<std::vector<Data>> data;
                    JS_OBJ(code, msg, ts, data);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures