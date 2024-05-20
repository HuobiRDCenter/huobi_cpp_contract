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
            namespace response_account
            {
                struct ContractMasterSubTransferResponse
                {
                    std::optional<std::string> status;
                    std::optional<int64_t> ts;
                    struct Data {
                        std::optional<std::string> order_id;
                        std::optional<int64_t> client_order_id;
                        JS_OBJ(order_id, client_order_id);
                    };
                    std::optional<Data> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

