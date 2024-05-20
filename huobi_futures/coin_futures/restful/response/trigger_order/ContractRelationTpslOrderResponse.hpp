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
            namespace response_trigger_order
            {
                struct ContractRelationTpslOrderResponse
                {
                    struct TpslOrderInfo {
                        std::optional<JS::Nullable<float>> volume;
                        std::optional<std::string> tpsl_order_type;
                        std::optional<std::string> direction;
                        std::optional<JS::Nullable<int64_t>> order_id;
                        std::optional<std::string> order_id_str;
                        std::optional<std::string> trigger_type;
                        std::optional<JS::Nullable<float>> trigger_price;
                        std::optional<JS::Nullable<int64_t>> created_at;
                        std::optional<std::string> order_price_type;
                        std::optional<JS::Nullable<float>> order_price;
                        std::optional<std::string> relation_tpsl_order_id;
                        std::optional<JS::Nullable<int64_t>> canceled_at;
                        std::optional<JS::Nullable<int>> fail_code;
                        std::optional<std::string> fail_reason;
                        std::optional<JS::Nullable<float>> triggered_price;
                        std::optional<std::string> relation_order_id;

                        JS_OBJ(volume, tpsl_order_type, direction, order_id, order_id_str, trigger_type, trigger_price, created_at, order_price_type, order_price, status, relation_tpsl_order_id, canceled_at, fail_code, fail_reason, triggered_price, relation_order_id);
                    };

// 内嵌结构体 data
                    struct Data {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_type;
                        std::optional<std::string> contract_code;
                        std::optional<JS::Nullable<float>> volume;
                        std::optional<JS::Nullable<float>> price;
                        std::optional<std::string> order_price_type;
                        std::optional<std::string> direction;
                        std::optional<std::string> offset;
                        std::optional<JS::Nullable<int64_t>> lever_rate;
                        std::optional<JS::Nullable<int64_t>> order_id;
                        std::optional<std::string> order_id_str;
                        std::optional<JS::Nullable<int64_t>> client_order_id;
                        std::optional<JS::Nullable<int64_t>> created_at;
                        std::optional<JS::Nullable<float>> trade_volume;
                        std::optional<JS::Nullable<float>> trade_turnover;
                        std::optional<JS::Nullable<float>> fee;
                        std::optional<JS::Nullable<float>> trade_avg_price;
                        std::optional<JS::Nullable<float>> margin_frozen;
                        std::optional<JS::Nullable<float>> profit;
                        std::optional<JS::Nullable<int>> status;
                        std::optional<JS::Nullable<int>> order_type;
                        std::optional<std::string> order_source;
                        std::optional<std::string> fee_asset;
                        std::optional<JS::Nullable<int64_t>> canceled_at;
                        std::vector<TpslOrderInfo> tpsl_order_info;

                        JS_OBJ(symbol, contract_type, contract_code, volume, price, order_price_type, direction, offset, lever_rate, order_id, order_id_str, client_order_id, created_at, trade_volume, trade_turnover, fee, trade_avg_price, margin_frozen, profit, status, order_type, order_source, fee_asset, canceled_at, tpsl_order_info);
                    };
                    std::optional<std::string> status;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<Data> data;

                    JS_OBJ(status, ts, data);
                };
            } // namespace response_trigger_order
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
