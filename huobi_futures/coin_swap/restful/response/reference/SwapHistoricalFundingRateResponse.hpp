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
                struct SwapHistoricalFundingRateResponse
                {
                    struct FundingInfo {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> fee_asset;
                        std::optional<std::string> funding_time;
                        std::optional<std::string> funding_rate;
                        std::optional<std::string> realized_rate;
                        std::optional<std::string> avg_premium_index;
                        JS_OBJ(symbol, contract_code, fee_asset, funding_time, funding_rate, realized_rate, avg_premium_index);
                    };

                    struct PageInfo {
                        std::optional<int64_t> total_page;
                        std::optional<int64_t> current_page;
                        std::optional<int64_t> total_size;
                        std::optional<std::vector<FundingInfo>> data;
                        JS_OBJ(total_page, current_page, total_size, data);
                    };
                    std::optional<std::string> status;
                    std::optional<int64_t> ts;
                    std::optional<PageInfo> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

