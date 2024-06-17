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
                struct SwapPositionInfoResponse
                {
                    struct PositionInfo {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> contract_type;
                        std::optional<std::string> volume;
                        std::optional<std::string> available;
                        std::optional<std::string> frozen;
                        std::optional<std::string> cost_open;
                        std::optional<std::string> cost_hold;
                        std::optional<std::string> profit_unreal;
                        std::optional<std::string> profit_rate;
                        std::optional<std::string> profit;
                        std::optional<std::string> position_margin;
                        std::optional<int64_t> lever_rate;
                        std::optional<std::string> direction;
                        std::optional<std::string> last_price;
                        std::optional<JS::Nullable<float>> adl_risk_percent;
                        std::optional<std::string> liq_px;
                        std::optional<std::string> new_risk_rate;
                        std::optional<std::string> trade_partition;
                        JS_OBJ(symbol, contract_code, contract_type, volume, available, frozen, cost_open, cost_hold, profit_unreal, profit_rate, profit, position_margin, lever_rate, direction, last_price, adl_risk_percent, liq_px, new_risk_rate, trade_partition);
                    };
                    std::optional<std::string> status;
                    std::optional<PositionInfo> data;
                    std::optional<int64_t> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

