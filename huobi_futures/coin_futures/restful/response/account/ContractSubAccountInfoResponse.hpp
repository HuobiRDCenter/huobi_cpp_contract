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
                struct ContractSubAccountInfoResponse
                {
                    struct ResponseData {
                        std::string symbol;
                        std::optional<JS::Nullable<int64_t>> margin_balance;
                        std::optional<JS::Nullable<int64_t>> margin_position;
                        std::optional<JS::Nullable<int64_t>> margin_frozen;
                        std::optional<JS::Nullable<int64_t>> margin_available;
                        std::optional<JS::Nullable<int64_t>> profit_real;
                        std::optional<JS::Nullable<int64_t>> profit_unreal;
                        std::optional<JS::Nullable<float>> risk_rate;
                        std::optional<JS::Nullable<float>> liquidation_price;
                        std::optional<JS::Nullable<float>> withdraw_available;
                        std::optional<JS::Nullable<float>> lever_rate;
                        std::optional<JS::Nullable<float>> adjust_factor;
                        std::optional<JS::Nullable<float>> margin_static;
                        std::optional<JS::Nullable<float>> new_risk_rate;
                        std::optional<std::string> trade_partition;
                        JS_OBJ(symbol, margin_balance, margin_position, margin_frozen, margin_available, profit_real, profit_unreal, risk_rate, liquidation_price, withdraw_available, lever_rate, adjust_factor, margin_static, new_risk_rate, trade_partition);
                    };
                    std::string status;
                    JS::Nullable<int64_t> ts;
                    std::optional<std::vector<ResponseData>> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

