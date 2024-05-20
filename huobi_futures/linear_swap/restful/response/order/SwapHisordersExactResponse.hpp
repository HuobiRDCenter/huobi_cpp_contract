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
                struct SwapHisordersExactResponse
                {
                    struct Data {
                        std::optional<JS::Nullable<int64_t>> query_id;
                        std::optional<JS::Nullable<int64_t>> order_id;
                        std::optional<std::string> order_id_str;
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> margin_mode;
                        std::optional<std::string> margin_account;
                        std::optional<int64_t> lever_rate;
                        std::optional<std::string> direction;
                        std::optional<std::string> offset;
                        std::optional<float> volume;
                        std::optional<float> price;
                        std::optional<int64_t> create_date;
                        std::optional<std::string> order_source;
                        std::optional<std::string> order_price_type;
                        std::optional<float> margin_frozen;
                        std::optional<float> profit;
                        std::optional<float> real_profit;
                        std::optional<float> trade_volume;
                        std::optional<float> trade_turnover;
                        std::optional<float> fee;
                        std::optional<float> trade_avg_price;
                        std::optional<int64_t> status;
                        std::optional<int64_t> order_type;
                        std::optional<std::string> fee_asset;
                        std::optional<std::string> liquidation_type;
                        std::optional<int64_t> is_tpsl;
                        std::optional<int64_t> reduce_only;
                        std::optional<std::string> canceled_source;
                        JS_OBJ(
                                query_id,
                                order_id,
                                order_id_str,
                                symbol,
                                contract_code,
                                margin_mode,
                                margin_account,
                                lever_rate,
                                direction,
                                offset,
                                volume,
                                price,
                                create_date,
                                order_source,
                                order_price_type,
                                margin_frozen,
                                profit,
                                real_profit,
                                trade_volume,
                                trade_turnover,
                                fee,
                                trade_avg_price,
                                status,
                                order_type,
                                fee_asset,
                                liquidation_type,
                                is_tpsl,
                                reduce_only,
                                canceled_source
                        );
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