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
                struct SwapPositionLeverResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        std::string contract_code;
                        std::string contract_type;
                        std::string margin_mode;
                        std::optional<std::string> position_side;
                        std::string lever_rate;
                        std::string available_lever;

                        JS_OBJ(contract_code, contract_type, margin_mode, position_side, lever_rate, available_lever);
                    };

                    std::optional<Data> data;

                    std::optional<string> message;

                    int64_t ts;

                    JS_OBJ(code, data, message, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
