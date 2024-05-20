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
                struct ContractTpslOrderResponse
                {
                    struct OrderResult {
                        int64_t order_id;
                        std::string order_id_str;
                        JS_OBJ(order_id, order_id_str);
                    };
                    std::string status;
                    int64_t ts;

                    struct Data {
                        std::optional<OrderResult> tp_order;
                        std::optional<OrderResult> sl_order;
                        JS_OBJ(tp_order, sl_order);
                    };

                    std::optional<Data> data;
                    std::optional<int64_t> err_code;
                    std::optional<std::string> err_msg;

                    JS_OBJ(status, ts, data, err_code, err_msg);
                };
            } // namespace response_trigger_order
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
