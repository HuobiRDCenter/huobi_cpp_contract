#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace coin_swap
    {
        namespace restful
        {
            namespace response_account
            {
                struct SwapAccountInfoResponse
                {
                    std::optional<std::string> status;
                    struct Data {
                        std::optional<std::string> symbol;
                        std::optional<std::string> margin_balance;
                        std::optional<std::string> margin_position;
                        std::optional<std::string> margin_frozen;
                        std::optional<std::string> margin_available;
                        std::optional<std::string> profit_unreal;
                        std::optional<std::string> risk_rate;
                        std::optional<std::string> new_risk_rate;
                        std::optional<std::string> trade_partition;
                        std::optional<std::string> liquidation_price;
                        std::optional<std::string> withdraw_available;
                        std::optional<std::string> lever_rate;
                        std::optional<std::string> adjust_factor;
                        std::optional<std::string> margin_static;
                        JS_OBJ(symbol, margin_balance, margin_position, margin_frozen, margin_available,
                               profit_unreal, risk_rate, new_risk_rate, trade_partition,
                                liquidation_price, withdraw_available, lever_rate, adjust_factor, margin_static);
                    };
                    std::optional<std::vector<Data>> data;
                    std::optional<Nullable<int64_t>> ts;

                    JS_OBJ(status, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

