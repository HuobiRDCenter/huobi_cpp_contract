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
                struct ContractAccountPositionInfoResponse
                {
                    struct Position {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> contract_type;
                        std::optional<JS::Nullable<float>> volume;
                        std::optional<JS::Nullable<float>> available;
                        std::optional<JS::Nullable<float>> frozen;
                        std::optional<JS::Nullable<float>> cost_open;
                        std::optional<JS::Nullable<float>> cost_hold;
                        std::optional<JS::Nullable<float>> profit_unreal;
                        std::optional<JS::Nullable<float>> profit_rate;
                        std::optional<JS::Nullable<float>> profit;
                        std::optional<JS::Nullable<float>> position_margin;
                        std::optional<JS::Nullable<int64_t>> lever_rate;
                        std::optional<std::string> direction;
                        std::optional<JS::Nullable<float>> last_price;
                        std::optional<JS::Nullable<float>> adl_risk_percent;

                        JS_OBJ(symbol, contract_code, contract_type, volume, available, frozen, cost_open, cost_hold, profit_unreal, profit_rate, profit, position_margin, lever_rate, direction, last_price, adl_risk_percent);
                    };

                    struct AccountInfo {
                        std::optional<std::string> symbol;
                        std::optional<JS::Nullable<float>> margin_balance;
                        std::optional<JS::Nullable<float>> margin_position;
                        std::optional<JS::Nullable<float>> margin_frozen;
                        std::optional<JS::Nullable<float>> margin_available;
                        std::optional<JS::Nullable<float>> profit_real;
                        std::optional<JS::Nullable<float>> profit_unreal;
                        std::optional<JS::Nullable<float>> risk_rate;
                        std::optional<JS::Nullable<float>> withdraw_available;
                        std::optional<JS::Nullable<float>> liquidation_price;
                        std::optional<JS::Nullable<int64_t>> lever_rate;
                        std::optional<JS::Nullable<float>> adjust_factor;
                        std::optional<JS::Nullable<float>> margin_static;
                        std::optional<JS::Nullable<float>> new_risk_rate;
                        std::optional<std::string> trade_partition;
                        std::optional<std::vector<Position>> positions;

                        JS_OBJ(symbol, margin_balance, margin_position, margin_frozen, margin_available, profit_real, profit_unreal, risk_rate, withdraw_available, liquidation_price, lever_rate, adjust_factor, margin_static, new_risk_rate, trade_partition, positions);
                    };
                    std::optional<std::string> status;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<std::vector<AccountInfo>> data;

                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

