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
                struct CopytradingTraderQueryContractLeverResponse
                {

                    struct CopytradingTraderQueryContractLever {
                        std::optional<JS::Nullable<std::string>> contract_code;
                        std::optional<JS::Nullable<std::string>> margin_mode;
                        std::optional<JS::Nullable<int>> lever_rate_range;
                        std::optional<JS::Nullable<int>> current_lever_rate;

                        JS_OBJ(contract_code, margin_mode, lever_rate_range, current_lever_rate);
                    };

                    std::optional<JS::Nullable<std::string>> tid;
                    std::optional<JS::Nullable<CopytradingTraderQueryContractLever>> data;
                    std::optional<JS::Nullable<long>> code;

                    JS_OBJ(tid, data, code);
                } // namespace response_order
            }     // namespace restful
        }         // namespace linear_swap
    } // namespace huobi_futures