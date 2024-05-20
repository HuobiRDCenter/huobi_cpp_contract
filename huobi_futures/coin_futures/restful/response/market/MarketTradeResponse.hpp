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
                struct MarketTradeResponse
                {
                    struct TradeData {
                        std::optional<JS::Nullable<float>> amount;
                        std::optional<std::string> direction;
                        std::optional<JS::Nullable<int64_t>> id;
                        std::optional<std::string> price;
                        std::optional<JS::Nullable<int64_t>> ts;
                        std::optional<std::string> quantity;
                        std::optional<std::string> symbol;
                        JS_OBJ(amount, direction, id, price, ts, quantity, symbol);
                    };

                    struct TradeTick {
                        std::optional<std::vector<TradeData>> data;
                        std::optional<JS::Nullable<int64_t>> id;
                        std::optional<JS::Nullable<int64_t>> ts;
                        JS_OBJ(data, id, ts);
                    };

                    std::optional<std::string> ch;
                    std::optional<std::string> status;
                    std::optional<TradeTick> tick;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(ch, status, tick, ts);
                };
            } // namespace response_market
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures


