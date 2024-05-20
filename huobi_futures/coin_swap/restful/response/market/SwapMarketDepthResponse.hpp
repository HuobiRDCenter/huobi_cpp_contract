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
            namespace response_market
            {
                struct SwapMarketDepthResponse
                {
                    struct Tick {
                        std::optional<std::vector<std::vector<int64_t>>> asks;
                        std::optional<std::vector<std::vector<int64_t>>> bids;
                        std::optional<int64_t> id;
                        std::optional<int64_t> mrid;
                        std::optional<int64_t> ts;
                        std::optional<int64_t> version;
                        std::optional<std::string> contract_code;
                        JS_OBJ(asks, bids, id, mrid, ts, version, contract_code);
                    };
                    std::optional<std::string> ch;
                    std::optional<std::string> status;
                    std::optional<Tick> tick;
                    std::optional<int64_t> ts;
                    JS_OBJ(ch, status, tick, ts);
                };
            } // namespace response_market
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

