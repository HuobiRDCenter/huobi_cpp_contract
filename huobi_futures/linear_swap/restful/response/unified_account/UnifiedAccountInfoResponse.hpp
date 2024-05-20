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
            namespace response_unified_account
            {
                struct UnifiedAccountInfoResponse
                {
                    struct CrossSwap {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> margin_mode;
                        std::optional<JS::Nullable<float>> margin_available;
                        std::optional<JS::Nullable<float>> lever_rate;
                        std::optional<std::string> contract_type;
                        std::optional<std::string> business_type;

                        JS_OBJ(symbol, contract_code, margin_mode, margin_available, lever_rate, contract_type, business_type);
                    };

                    struct CrossFutures {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> margin_mode;
                        std::optional<JS::Nullable<float>> margin_available;
                        std::optional<JS::Nullable<float>> lever_rate;
                        std::optional<std::string> contract_type;
                        std::optional<std::string> business_type;

                        JS_OBJ(symbol, contract_code, margin_mode, margin_available, lever_rate, contract_type, business_type);
                    };

                    struct IsolatedSwap {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> margin_mode;
                        std::optional<JS::Nullable<float>> margin_available;
                        std::optional<JS::Nullable<float>> withdraw_available;
                        std::optional<int64_t> lever_rate;
                        std::optional<std::string> position_mode;

                        JS_OBJ(symbol, contract_code, margin_mode, margin_available, withdraw_available, lever_rate, position_mode);
                    };

                    struct Data {
                        std::optional<JS::Nullable<float>> margin_balance;
                        std::optional<JS::Nullable<float>> margin_static;
                        std::optional<JS::Nullable<float>> cross_profit_unreal;
                        std::optional<JS::Nullable<float>> cross_margin_static;
                        std::optional<std::string> margin_asset;
                        std::optional<JS::Nullable<float>> margin_frozen;
                        std::optional<JS::Nullable<float>> withdraw_available;
                        std::optional<JS::Nullable<float>> cross_risk_rate;
                        std::optional<std::vector<CrossSwap>> cross_swap;
                        std::optional<std::vector<CrossFutures>> cross_futures;
                        std::optional<std::vector<IsolatedSwap>> isolated_swap;

                        JS_OBJ(margin_balance, margin_static, cross_profit_unreal, cross_margin_static, margin_asset, margin_frozen,
                                withdraw_available, cross_risk_rate, cross_swap, cross_futures, isolated_swap);
                    };

                    std::optional<JS::Nullable<int64_t>> code;
                    std::optional<std::string> msg;
                    std::optional<JS::Nullable<int64_t>> ts;
                    struct Data {
                        std::optional<JS::Nullable<int64_t>> account_type;
                        JS_OBJ(account_type);
                    };
                    std::optional<std::vector<Data>> data;

                    JS_OBJ(code, msg, ts, data);
                };
            } // namespace response_unified_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures

