#pragma once

#include <string>
#include <vector>
#include <optional>
#include "huobi_futures/json_struct/json_struct.h"

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_account
            {
                struct SwapAccountBillsResponse
                {
                    struct Data
                    {
                        std::optional<std::string> id;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> margin_mode;
                        std::optional<std::string> type;
                        std::optional<std::string> currency;
                        std::optional<std::string> amount;
                        std::optional<std::string> created_time;

                        JS_OBJ(id, contract_code, margin_mode, type, currency, amount, created_time);
                    };

                    std::optional<int32_t> code;
                    std::optional<std::vector<Data>> data;
                    std::optional<std::string> message;
                    std::optional<int64_t> ts;

                    JS_OBJ(code, data, message, ts);
                };
            }
        }
    }
}