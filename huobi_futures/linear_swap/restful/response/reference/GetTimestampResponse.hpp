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
                struct GetTimestampResponse
                {
                    std::optional<string> status;
                    std::optional<JS::Nullable<int64_t>> ts;

                    JS_OBJ(status, ts);

                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
