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
            namespace response_market
            {
                struct GetMarketRiskLimitResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        std::string contract_code;
                        std::string margin_mode;
                        std::optional<int32_t> tier;
                        std::string max_lever;
                        std::string maintenance_margin_rate;
                        std::string max_volume;
                        std::string min_volume;
                        std::string volume_unit;

                        JS_OBJ(contract_code, margin_mode, tier, max_lever, maintenance_margin_rate, max_volume, min_volume, volume_unit);
                    };

                    std::optional<std::vector<Data>> data;

                    std::optional<string> message;

                    int64_t ts;

                    JS_OBJ(code, data, message, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
