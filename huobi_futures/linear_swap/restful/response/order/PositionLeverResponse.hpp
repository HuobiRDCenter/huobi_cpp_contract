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
                struct PositionLeverResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        std::string contract_code;
                        std::string margin_mode;
                        std::string lever_rate;

                        JS_OBJ(contract_code, margin_mode, lever_rate);
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
