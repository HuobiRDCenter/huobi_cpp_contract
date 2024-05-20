#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace coin_swap
    {
        namespace restful
        {
            namespace response_reference
            {
                struct SwapFundingRateResponse
                {
                    struct FundingInfo {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> fee_asset;
                        std::optional<std::string> funding_time;
                        std::optional<float> funding_rate;
                        std::optional<float> estimated_rate;
                        std::optional<int64_t> next_funding_time;
                        JS_OBJ(symbol, contract_code, fee_asset, funding_time, funding_rate, estimated_rate, next_funding_time);
                    };
                    std::optional<std::string> status;
                    std::optional<FundingInfo> data;
                    std::optional<int64_t> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

