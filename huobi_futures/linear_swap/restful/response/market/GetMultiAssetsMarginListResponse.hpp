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
                struct GetMultiAssetsMarginListResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        std::vector<std::string> multi_assets;

                        JS_OBJ(multi_assets);
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
