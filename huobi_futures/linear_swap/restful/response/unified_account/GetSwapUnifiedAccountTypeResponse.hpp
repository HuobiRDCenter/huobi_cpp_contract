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
            namespace response_unified_account
            {
                struct GetSwapUnifiedAccountTypeResponse
                {

                    std::optional<JS::Nullable<int64_t>> code;

                    std::optional<string> msg;

                    std::optional<JS::Nullable<int64_t>> ts;

                    struct Data
                    {
                        std::optional<JS::Nullable<int64_t>> account_type;

                        JS_OBJ(account_type);
                    };
                    std::optional<Data> data;

                    JS_OBJ(code, msg, ts, data);
                };
            } // namespace response_unified_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures

