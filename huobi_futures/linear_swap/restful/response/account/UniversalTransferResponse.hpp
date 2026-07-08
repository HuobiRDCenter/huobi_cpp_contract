#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <optional>

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_account
            {
                struct UniversalTransferResponse
                {
                    std::optional<int32_t> code;
                    std::optional<string> message;
                    int64_t ts;
                    std::optional<int64_t> data;

                    JS_OBJ(code, message, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures