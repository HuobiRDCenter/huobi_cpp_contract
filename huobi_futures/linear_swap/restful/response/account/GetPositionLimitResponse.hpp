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
            namespace response_account
            {
                struct GetPositionLimitResponse
                {
                    string status;

                    std::optional<int32_t> err_code;

                    std::optional<string> err_msg;

                    struct Data
                    {
                        string symbol;

                        string contract_code;

                        string margin_mode;

                        float buy_limit;

                        float sell_limit;

                        std::optional<string> contract_type;
                        std::optional<string> pair;
                        std::optional<string> business_type;

                        std::optional<JS::Nullable<int>> lever_rate;

                        std::optional<JS::Nullable<int>> buy_limit_value;

                        std::optional<JS::Nullable<int>> sell_limit_value;

                        std::optional<JS::Nullable<float>> mark_price;


                        JS_OBJ(symbol, contract_code, margin_mode, buy_limit, sell_limit, contract_type, pair, business_type,
                                lever_rate, buy_limit_value, sell_limit_value, mark_price);
                    };

                    std::optional<std::vector<Data>> data;

                    int64_t ts;

                    JS_OBJ(status, err_code, err_msg, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
