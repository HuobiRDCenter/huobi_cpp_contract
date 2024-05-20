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
            namespace response_trigger_order
            {
                struct ContractTriggerOrderResponse
                {
                    std::optional<JS::Nullable<std::string>> status;
                    std::optional<JS::Nullable<int64_t>> err_code;
                    std::optional<std::string> err_msg;
                    std::optional<int64_t> ts;
                    struct Data {
                        std::optional<int64_t> order_id;
                        std::optional<std::string> order_id_str;
                        JS_OBJ(order_id, order_id_str);
                    };
                    std::optional<Data> data;
                    JS_OBJ(status, err_code, err_msg, ts, data);
                };
            } // namespace response_trigger_order
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
