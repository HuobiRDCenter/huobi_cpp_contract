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
                struct SwapMasterSubTransferResponse
                {
                    struct Data {
                        std::optional<std::string> order_id;
                        std::optional<JS::Nullable<int64_t>> client_order_id;
                        JS_OBJ(order_id, client_order_id);
                    };
                    std::optional<std::string> status;
                    std::optional<Data> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

