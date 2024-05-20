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
                struct GetOpenInterestResponse
                {
                    string status;

                    std::optional<int32_t> err_code;

                    std::optional<string> err_msg;

                    int64_t ts;

                    struct Data
                    {
                        string symbol;

                        string contract_code;

                        float amount;

                        float volume;

                        float value;

                        std::optional<JS::Nullable<float>> trade_amount;

                        std::optional<JS::Nullable<float>> trade_volume;

                        std::optional<JS::Nullable<float>> trade_turnover;

                        std::optional<string> contract_type;

                        std::optional<string> pair;

                        std::optional<string> business_type;


                        JS_OBJ(symbol, contract_code, amount, volume, value, trade_amount, trade_volume, trade_turnover,
                               contract_type, pair, business_type);
                    };
                    std::optional<std::vector<Data>> data;

                    JS_OBJ(status, err_code, err_msg, ts, data);
                };
            } // namespace response_market
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
