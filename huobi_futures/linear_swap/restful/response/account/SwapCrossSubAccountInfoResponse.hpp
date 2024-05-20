#pragma once

#include <string>
using std::optional<string>;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_account
            {
                struct SwapCrossSubAccountInfoResponse
                {
                    struct ContractDetail {
                        std::optional<string> symbol;
                        std::optional<string> contract_code;
                        std::optional<JS::Nullable<float>> margin_position;
                        std::optional<JS::Nullable<float>> margin_frozen;
                        std::optional<JS::Nullable<float>> margin_available;
                        std::optional<JS::Nullable<float>> profit_unreal;
                        std::optional<JS::Nullable<float>> liquidation_price;
                        std::optional<JS::Nullable<float>> lever_rate;
                        std::optional<JS::Nullable<float>> adjust_factor;
                        std::optional<string> contract_type;
                        std::optional<JS::Nullable<float>> cross_max_available;
                        std::optional<string> trade_partition;
                        std::optional<string> pair;
                        std::optional<string> business_type;
                        JS_OBJ(symbol, contract_code, margin_position, margin_frozen, margin_available, profit_unreal, liquidation_price, lever_rate, adjust_factor, contract_type, cross_max_available, trade_partition, pair, business_type);
                    };

                    struct FuturesContractDetail {
                        std::optional<string> symbol;
                        std::optional<string> contract_code;
                        std::optional<JS::Nullable<float>> margin_position;
                        std::optional<JS::Nullable<float>> margin_frozen;
                        std::optional<JS::Nullable<float>> margin_available;
                        std::optional<JS::Nullable<float>> profit_unreal;
                        std::optional<JS::Nullable<float>> liquidation_price;
                        std::optional<JS::Nullable<float>> lever_rate;
                        std::optional<JS::Nullable<float>> adjust_factor;
                        std::optional<string> contract_type;
                        std::optional<JS::Nullable<float>> cross_max_available;
                        std::optional<string> trade_partition;
                        std::optional<string> pair;
                        std::optional<string> business_type;
                        JS_OBJ(symbol, contract_code, margin_position, margin_frozen, margin_available, profit_unreal, liquidation_price, lever_rate, adjust_factor, contract_type, cross_max_available, trade_partition, pair, business_type);
                    };

                    std::optional<std::optional<string>> status;
                    struct Data {
                        std::optional<std::optional<string>> margin_mode;
                        std::optional<std::optional<string>> margin_account;
                        std::optional<std::optional<string>> margin_asset;
                        std::optional<JS::Nullable<float>> margin_balance;
                        std::optional<JS::Nullable<float>> margin_static;
                        std::optional<JS::Nullable<float>> margin_position;
                        std::optional<JS::Nullable<float>> margin_frozen;
                        std::optional<JS::Nullable<float>> profit_unreal;
                        std::optional<JS::Nullable<float>> withdraw_available;
                        std::optional<JS::Nullable<float>> risk_rate;
                        std::optional<JS::Nullable<float>> money_in;
                        std::optional<JS::Nullable<float>> money_out;
                        std::optional<JS::Nullable<float>> new_risk_rate;
                        std::optional<std::optional<string>> position_mode;
                        std::vector<ContractDetail> contract_detail;
                        std::vector<FuturesContractDetail> futures_contract_detail;
                        JS_OBJ(margin_mode, margin_account, margin_asset, margin_balance, margin_static, margin_position, margin_frozen, profit_unreal, withdraw_available, risk_rate, money_in, money_out, new_risk_rate, position_mode, contract_detail, futures_contract_detail);
                    };
                    std::optional<Data> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
