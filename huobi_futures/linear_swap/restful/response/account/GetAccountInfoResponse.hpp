﻿#pragma once

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
            namespace response_account
            {
                struct GetAccountInfoResponse
                {
                    string status;

                    std::optional<int32_t> err_code;

                    std::optional<string> err_msg;

                    struct Data
                    {
                        std::optional<string> symbol;

                        std::optional<string> contract_code;

                        string margin_asset;

                        float margin_balance;

                        float margin_static;

                        float margin_position;

                        float margin_frozen;

                        std::optional<float> margin_available;

                        std::optional<float> profit_real;

                        float profit_unreal;

                        float withdraw_available;

                        std::optional<string> new_risk_rate;

                        std::optional<string> money_out;

                        std::optional<string> money_in;

                        std::optional<string> trade_partition;

                        JS::Nullable<float> risk_rate;

                        std::optional<JS::Nullable<float>>liquidation_price;

                        std::optional<float> lever_rate;

                        std::optional<float> adjust_factor;

                        string margin_mode;

                        string margin_account;

                        std::optional<string> position_mode;

                        struct ContractDetail
                        {
                            string symbol;
                            string contract_code;
                            float margin_position;
                            float margin_frozen;
                            float margin_available;
                            float profit_unreal;
                            JS::Nullable<float> liquidation_price;
                            int32_t lever_rate;
                            float adjust_factor;
                            std::optional<string> contract_type;
                            std::optional<string> cross_max_available;
                            std::optional<string> trade_partition;
                            std::optional<string> pair;
                            std::optional<string> business_type;

                            JS_OBJ(symbol, contract_code, margin_position, margin_frozen, margin_available, profit_unreal,
                                   liquidation_price, lever_rate, adjust_factor, contract_type, cross_max_available, trade_partition, pair, business_type);
                        };
                        std::optional<std::vector<ContractDetail>> contract_detail;

                        struct FuturesContractDetail
                        {
                            string symbol;
                            string contract_code;
                            float margin_position;
                            float margin_frozen;
                            float margin_available;
                            float profit_unreal;
                            JS::Nullable<float> liquidation_price;
                            int32_t lever_rate;
                            float adjust_factor;
                            std::optional<string> contract_type;
                            std::optional<string> cross_max_available;
                            std::optional<string> trade_partition;
                            std::optional<string> pair;
                            std::optional<string> business_type;

                            JS_OBJ(symbol, contract_code, margin_position, margin_frozen, margin_available, profit_unreal,
                                    liquidation_price, lever_rate, adjust_factor, contract_type, cross_max_available, trade_partition, pair, business_type);
                        };
                        std::optional<std::vector<FuturesContractDetail>> futures_contract_detail;

                        JS_OBJ(symbol, contract_code, margin_asset, margin_balance, margin_static, margin_position, margin_frozen,
                               margin_available, profit_real, profit_unreal, withdraw_available, new_risk_rate, money_out, money_in, trade_partition, risk_rate, liquidation_price,
                               lever_rate, adjust_factor, margin_mode, margin_account, position_mode, contract_detail);
                    };
                    std::optional<std::vector<Data>> data;

                    int64_t ts;

                    JS_OBJ(status, err_code, err_msg, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
