#pragma once

#include <string>
using std::string;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>
#include <memory>

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_order
            {
                // V5 /v5/trade/position 与 /v5/trade/position_all 响应
                // 无持仓时 data 为 null 或 []，data 改 unique_ptr<vector> 兼容 null/空数组/有数据
                struct SwapTradePositionResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        std::optional<std::string> order_id;
                        std::optional<std::string> client_order_id;

                        JS_OBJ(order_id, client_order_id);
                    };

                    std::unique_ptr<std::vector<Data>> data;

                    std::optional<string> message;

                    std::optional<int64_t> ts;

                    JS_OBJ(code, data, message, ts);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
