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
                struct ContractSubPositionInfoResponse
                {
                    struct PositionInfo {
                        std::string symbol;
                        std::string contract_code;
                        std::string contract_type;
                        std::optional<JS::Nullable<int64_t>> volume;
                        std::optional<JS::Nullable<int64_t>> available;
                        std::optional<JS::Nullable<int64_t>> frozen;
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
                        std::optional<std::string> liq_px;
                        std::optional<JS::Nullable<float>> new_risk_rate;
                        std::optional<std::string> trade_partition;
                        JS_OBJ(symbol, contract_code, contract_type, volume, available, frozen, cost_open, cost_hold, profit_unreal, profit_rate, profit, position_margin, lever_rate, direction, last_price, adl_risk_percent, liq_px, new_risk_rate, trade_partition);
                    };
                    std::string status;
                    JS::Nullable<int64_t> ts;
                    std::optional<std::vector<PositionInfo>> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

