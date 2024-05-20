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
            namespace response_market
            {
                struct MarketHistoryTradeResponse
                {
                    struct TradeData {
                        std::optional<std::vector<TradeData>> data;
                        std::optional<JS::Nullable<float>> amount;
                        std::optional<std::string> direction;
                        std::optional<JS::Nullable<int64_t>> id;
                        std::optional<std::string> price;
                        std::optional<JS::Nullable<int64_t>> ts;
                        std::optional<std::string> quantity;
                        JS_OBJ(data, amount, direction, id, price, ts, quantity);
                    };
                    std::optional<std::string> ch;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<std::vector<TradeData>> data;
                    std::optional<JS::Nullable<int64_t>> id;
                    std::optional<JS::Nullable<int64_t>> status;
                    JS_OBJ(ch, ts, data, id, status);
                };
            } // namespace response_market
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

