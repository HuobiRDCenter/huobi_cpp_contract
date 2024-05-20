#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace coin_futures
    {
        namespace restful
        {
            namespace response_transfer
            {
                struct FuturesTransferResponse
                {
                    std::optional<std::string> status;
                    std::optional<std::string> err_code;
                    std::optional<std::string> err_msg;
                    std::optional<JS::Nullable<int64_t>> data;
                    JS_OBJ(status, err_code, err_msg, data);
                };
            } // namespace response_transfer
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
