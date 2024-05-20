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
                struct ContractTriggerCancelResponse
                {
                    std::optional<std::string> status;
                    struct Data {
                        struct Error {
                            std::optional<std::string> order_id;
                            std::optional<int64_t> err_code;
                            std::optional<std::string> err_msg;
                        };
                        std::optional<std::vector<Error>> errors;
                        std::optional<std::string> successes;
                        JS_OBJ(errors, successes)
                    };
                    std::optional<Data> data;
                    std::optional<int64_t> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_trigger_order
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
