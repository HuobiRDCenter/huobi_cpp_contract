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
        namespace ws
        {
            namespace response_market
            {
                struct ReqTradeDetailResponse
                {
                    string rep;

                    string status;

                    string id;

                    int64_t ts;

                    struct Data
                    {
                        int64_t id;

                        string price;

                        string amount;

                        string direction;

                        int64_t ts;

                        string quantity;
                        
                        string trade_turnover;

                        JS_OBJ(id, price, amount, direction, ts, quantity, trade_turnover);
                    };

                    std::vector<Data> data;

                    JS_OBJ(rep, status, id, ts, data);
                };
            } // namespace response_market
        }     // namespace ws
    }         // namespace coin_futures
} // namespace huobi_futures
