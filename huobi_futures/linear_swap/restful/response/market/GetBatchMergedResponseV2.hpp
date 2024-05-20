#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_market
            {
                struct GetBatchMergedResponseV2
                {
                    struct TickData
                    {
                        std::optional<std::string> contract_code; // Contract code or identifier
                        std::optional<std::string> business_type; // Business type: futures or swap
                        std::optional<JS::Nullable<int64_t>> id; // K-line id
                        std::optional<std::string> amount; // Trading volume (coins) in the last 24 hours
                        std::optional<std::vector<float>> ask; // [Ask price, Ask volume (lots)]
                        std::optional<std::vector<float>> bid; // [Bid price, Bid volume (lots)]
                        std::optional<std::string> open; // Opening price
                        std::optional<std::string> close; // Closing price
                        std::optional<std::string> count; // Number of trades in the last 24 hours
                        std::optional<std::string> high; // Highest price
                        std::optional<std::string> low; // Lowest price
                        std::optional<std::string> vol; // Trading volume (lots) in the last 24 hours
                        std::optional<std::string> number_of; // Trading volume (lots) in the last 24 hours
                        std::optional<JS::Nullable<int64_t>> ts; // Timestamp
                        JS_OBJ(contract_code, business_type, id, amount, ask, bid, open, close, count, high, low, vol, number_of, ts);
                    };
                    std::optional<std::string> status; // Request processing result: "ok" or "error"
                    std::optional<std::vector<TickData>> ticks; // Tick data
                    std::optional<JS::Nullable<int64_t>> ts; // Response generation timestamp in milliseconds
                    JS_OBJ(status, ticks, ts);
                };
            } // namespace response_market
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures

