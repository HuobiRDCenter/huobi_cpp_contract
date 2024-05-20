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
            namespace response_order
            {
                struct ContractBatchOrderResponse
                {
                    struct Data {
                        struct ErrorResponse {
                            std::optional<JS::Nullable<int64_t>> index;
                            std::optional<JS::Nullable<int64_t>> err_code;
                            std::optional<std::string> err_msg;
                            JS_OBJ(index, err_code, err_msg);
                        };

                        struct SuccessResponse {
                            std::optional<JS::Nullable<int64_t>> index;
                            std::optional<JS::Nullable<int64_t>> order_id;
                            std::optional<std::string> order_id_str;
                            std::optional<JS::Nullable<int64_t>> client_order_id;
                            JS_OBJ(index, order_id, order_id_str, client_order_id);
                        };
                        std::optional<std::vector<ErrorResponse>> errors;
                        std::optional<std::vector<SuccessResponse>> success;
                        JS_OBJ(errors, success);
                    };
                    std::optional<std::string> status;
                    std::optional<Data> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures
