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
                struct GetAvailableLevelRateResponse
                {
                    string status;

                    std::optional<int32_t> err_code;

                    std::optional<string> err_msg;

                    struct Data
                    {
                        string contract_code;

                        string margin_mode;

                        string available_level_rate;

                        std::optional<string> contract_type;

                        std::optional<string> pair;

                        std::optional<string> business_type;

                        JS_OBJ(contract_code, margin_mode, available_level_rate, contract_type, pair, business_type);
                    };

                    std::optional<std::vector<Data>> data;

                    int64_t ts;

                    JS_OBJ(status, err_code, err_msg, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
