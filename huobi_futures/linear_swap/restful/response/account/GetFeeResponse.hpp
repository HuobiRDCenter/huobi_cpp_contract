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
                struct GetFeeResponse
                {
                    string status;

                    std::optional<int32_t> err_code;

                    std::optional<string> err_msg;

                    struct Data
                    {
                        string symbol;

                        string contract_code;

                        string open_maker_fee;

                        string open_taker_fee;

                        string close_maker_fee;

                        string close_taker_fee;

                        string fee_asset;

                        std::optional<string> contract_type;

                        std::optional<string> pair;

                        std::optional<string> business_type;

                        std::optional<string> delivery_fee;


                        JS_OBJ(symbol, contract_code, open_maker_fee, open_taker_fee, close_maker_fee, close_taker_fee, fee_asset,
                                contract_type, pair, business_type, delivery_fee);
                    };

                    std::optional<std::vector<Data>> data;

                    int64_t ts;

                    JS_OBJ(status, err_code, err_msg, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
