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
            namespace response_order
            {
                struct SwapPositionRiskLimitResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        std::optional<std::string> contract_code;
                        std::optional<std::string> contract_type;
                        std::optional<std::string> margin_mode;
                        std::optional<std::string> position_side;
                        std::optional<std::string> max_lever;
                        std::optional<std::string> maintenance_margin_rate;
                        std::optional<std::string> max_volume;
                        std::optional<std::string> min_volume;
                        std::optional<std::string> volume_unit;

                        JS_OBJ(contract_code, contract_type, margin_mode, position_side, max_lever, maintenance_margin_rate, max_volume, min_volume, volume_unit);
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
