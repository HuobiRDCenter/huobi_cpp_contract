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
                struct ContractInsuranceFundResponse
                {
                    struct TickData {
                        std::optional<JS::Nullable<float>> insurance_fund;
                        std::optional<JS::Nullable<int64_t>> ts;
                        JS_OBJ(insurance_fund, ts);
                    };

                    struct SymbolData {
                        std::optional<std::string> symbol;
                        std::optional<std::vector<TickData>> tick;
                        JS_OBJ(symbol, tick);
                    };
                    std::optional<std::string> status;
                    std::optional<SymbolData> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
