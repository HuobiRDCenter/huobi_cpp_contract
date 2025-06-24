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
                struct CopytradingTraderTpslOpenOrdersResponse
                {
                    struct CopytradingTraderTpslOpenOrders {
                        std::optional<JS::Nullable<std::string>> contract_code;
                        std::optional<JS::Nullable<std::string>> volume;
                        std::optional<JS::Nullable<std::string>> margin_mode;
                        std::optional<JS::Nullable<std::string>> position_side;
                        std::optional<JS::Nullable<std::string>> trigger_type;
                        std::optional<JS::Nullable<std::string>> tpsl_order_type;
                        std::optional<JS::Nullable<std::string>> price;

                        JS_OBJ(contract_code, volume, margin_mode, position_side, trigger_type, tpsl_order_type, price);
                    };

                    struct TpslOpenOrders {
                        std::optional<JS::Nullable<long>> code;

                        JS_OBJ(code);
                    };

                    std::optional<JS::Nullable<std::string>> tid;
                    std::optional<JS::Nullable<std::vector<CopytradingTraderTpslOpenOrders>>> data;
                    std::optional<JS::Nullable<std::vector<TpslOpenOrders>>> response_data;

                    JS_OBJ(tid, data, response_data);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures