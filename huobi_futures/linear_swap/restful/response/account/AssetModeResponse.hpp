#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>
#include <memory>

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_account
            {
                struct AssetModeResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        int asset_mode;

                        JS_OBJ(asset_mode);
                    };

                    // V5 asset_mode：set 幂等/有持仓时 data 为 null，optional<Data> 遇 null 解析失败，改 unique_ptr
                    std::unique_ptr<Data> data;

                    std::optional<string> message;

                    int64_t ts;

                    JS_OBJ(code, data, message, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
