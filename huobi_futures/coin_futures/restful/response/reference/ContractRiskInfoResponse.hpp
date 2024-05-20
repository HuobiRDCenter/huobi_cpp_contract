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
            namespace response_reference
            {
                struct ContractRiskInfoResponse
                {
                    struct SymbolData {
                        std::optional<std::string> symbol;
                        std::optional<JS::Nullable<float>> insurance_fund;
                        std::optional<JS::Nullable<float>> estimated_clawback;
                        JS_OBJ(symbol, insurance_fund, estimated_clawback);
                    };
                    std::optional<std::string> status;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<SymbolData> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
