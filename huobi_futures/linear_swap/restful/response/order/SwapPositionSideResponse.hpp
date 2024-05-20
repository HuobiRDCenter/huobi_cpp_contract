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
            namespace response_order
            {
                struct SwapPositionSideResponse
                {
                    struct Data {
                        std::optional<std::string> margin_account;
                        std::optional<std::string> position_mode;
                        JS_OBJ(margin_account, position_mode);
                    };
                    std::optional<std::string> status;
                    std::optional<std::vector<Data>> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures