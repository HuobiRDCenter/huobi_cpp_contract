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
            namespace response_order
            {
                struct ContractSwitchLeverRateResponse
                {
                    std::string status;
                    struct Data {
                        std::optional<std::string> symbol;
                        std::optional<int64_t> lever_rate;

                        JS_OBJ(symbol, lever_rate);
                    };
                    std::optional<Data> data;
                    std::optional<JS::Nullable<int64_t>> err_code;
                    std::optional<std::string> err_msg;
                    int64_t ts;

                    JS_OBJ(status, data, err_code, err_msg, ts);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
