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
            namespace response_account
            {
                struct ContractUserSettlementRecordsResponse
                {
                    struct SettlementPosition {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> direction;
                        std::optional<JS::Nullable<float>> volume;
                        std::optional<JS::Nullable<float>> cost_open;
                        std::optional<JS::Nullable<float>> cost_hold_pre;
                        std::optional<JS::Nullable<float>> cost_hold;
                        std::optional<JS::Nullable<float>> settlement_profit_unreal;
                        std::optional<JS::Nullable<float>> settlement_price;
                        std::optional<std::string> settlement_type;
                        JS_OBJ(symbol, contract_code, direction, volume, cost_open, cost_hold_pre, cost_hold, settlement_profit_unreal, settlement_price, settlement_type);
                    };

                    struct SettlementRecord {
                        std::optional<std::string> symbol;
                        std::optional<JS::Nullable<float>> margin_balance_init;
                        std::optional<JS::Nullable<float>> margin_balance;
                        std::optional<JS::Nullable<float>> settlement_profit_real;
                        std::optional<JS::Nullable<int64_t>> settlement_time;
                        std::optional<JS::Nullable<float>> clawback;
                        std::optional<JS::Nullable<float>> delivery_fee;
                        std::optional<JS::Nullable<float>> offset_profitloss;
                        std::optional<JS::Nullable<float>> fee;
                        std::optional<std::string> fee_asset;
                        std::optional<std::vector<SettlementPosition>> positions;
                        JS_OBJ(symbol, margin_balance_init, margin_balance, settlement_profit_real, settlement_time, clawback, delivery_fee, offset_profitloss, fee, fee_asset, positions);
                    };

                    struct Data {
                        std::optional<std::vector<SettlementRecord>> settlement_records;
                        std::optional<JS::Nullable<int64_t>> total_page;
                        std::optional<JS::Nullable<int64_t>> current_page;
                        std::optional<JS::Nullable<int64_t>> total_size;
                        JS_OBJ(settlement_records, total_page, current_page, total_size);
                    };
                    std::optional<std::string> status;
                    std::optional<Data> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

