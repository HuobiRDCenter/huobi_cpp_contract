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
            namespace response_reference
            {
                struct ContractOpenInterestResponse
                {
                    struct TradeData {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_type;
                        std::optional<JS::Nullable<float>> volume;
                        std::optional<JS::Nullable<float>> amount;
                        std::optional<std::string> contract_code;
                        std::optional<JS::Nullable<float>> trade_amount;
                        std::optional<JS::Nullable<float>> trade_volume;
                        std::optional<JS::Nullable<float>> trade_turnover;
                        JS_OBJ(symbol, contract_type, volume, amount, contract_code, trade_amount, trade_volume, trade_turnover);
                    };
                    std::optional<std::string> status;
                    std::optional<TradeData> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures


