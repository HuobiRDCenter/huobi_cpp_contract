#pragma once

#include <string>
using std::optional<string>;

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
                struct CopytradingTraderQueryContractResponse
                {
                    struct CopytradingTraderQueryContract {
                        std::optional<JS::Nullable<std::string>> contract_code;

                        JS_OBJ(contract_code);
                    };
                    std::optional<JS::Nullable<std::string>> tid;
                    std::optional<JS::Nullable<std::vector<CopytradingTraderQueryContract>>> data;
                    std::optional<JS::Nullable<long>> code;

                    JS_OBJ(tid, data, code);


                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures