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
            namespace response_reference
            {
                struct GetSwapBatchFundingRateResponse
                {
                    std::optional<JS::Nullable<int64_t>> code;
                    std::optional<std::string> msg;
                    std::optional<JS::Nullable<int64_t>> ts;

                    struct Data {
                        std::string status;
                        std::optional<string> symbol;
                        std::optional<string> contract_code;
                        std::optional<string> fee_asset;
                        std::optional<string> funding_time;
                        std::optional<string> funding_rate;
                        std::optional<string> estimated_rate;
                        std::optional<string> next_funding_time;

                        JS_OBJ(status, symbol, contract_code, fee_asset, funding_time, funding_rate,
                                estimated_rate, next_funding_time);
                    };
                    std::optional<std::vector<Data>> data;

                    JS_OBJ(code, msg, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
