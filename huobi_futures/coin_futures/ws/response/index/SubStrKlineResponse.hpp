﻿#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace coin_futures
    {
        namespace ws
        {
            namespace response_index
            {
                struct SubStrKlineResponse
                {
                    string ch;

                    int64_t ts;

                    struct Tick
                    {
                        int64_t id;

                        string vol;

                        string count;

                        string open;

                        string close;

                        string low;

                        string high;

                        string amount;

                        JS_OBJ(id, vol, count, open, close, low, high, amount);
                    };
                    Tick tick;

                    JS_OBJ(ch, ts, tick);
                };
            } // namespace response_market
        }     // namespace ws
    }         // namespace coin_futures
} // namespace huobi_futures