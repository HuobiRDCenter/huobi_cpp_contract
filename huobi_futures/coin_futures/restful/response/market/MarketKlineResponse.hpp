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
                struct MarketKlineResponse
                {
                    struct KLineData {
                        std::optional<std::string> symbol;
                        std::optional<std::string> number_of;
                        std::optional<JS::Nullable<int64_t>> id;
                        std::optional<JS::Nullable<float>> vol;
                        std::optional<JS::Nullable<float>> count;
                        std::optional<JS::Nullable<float>> open;
                        std::optional<JS::Nullable<float>> close;
                        std::optional<JS::Nullable<float>> low;
                        std::optional<JS::Nullable<float>> high;
                        std::optional<JS::Nullable<float>> amount;
                        std::optional<std::vector<float>> ask;
                        std::optional<std::vector<float>> bid;
                        std::optional<JS::Nullable<int64_t>> ts;
                        JS_OBJ(symbol, number_of, id, vol, count, open, close, low, high, amount, ask, bid, ts);
                    };
                    std::optional<std::string> ch;
                    std::optional<std::vector<KLineData>> data;
                    std::optional<std::string> status;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(ch, data, status, ts);
                };
            } // namespace response_market
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures


