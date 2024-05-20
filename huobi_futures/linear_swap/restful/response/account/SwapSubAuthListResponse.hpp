#pragma once

#include <string>
using std::optional<string>;

#include "huobi_futures/json_struct/json_struct.h"
#include <vector>
#include <optional>

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_account
            {
                struct SwapSubAuthListResponse
                {
                    struct Error {
                        std::optional<string> sub_uid;
                        std::optional<JS::Nullable<int64_t>> err_code;
                        std::optional<string> err_msg;
                        JS_OBJ(sub_uid, err_code, err_msg);
                    };

                    struct Success {
                        std::optional<string> sub_uid;
                        std::optional<JS::Nullable<int64_t>> sub_auth;
                        std::optional<JS::Nullable<int64_t>> query_id;
                        JS_OBJ(sub_uid, sub_auth, query_id);
                    };

                    struct Data {
                        std::optional<std::vector<Error>> errors;
                        std::optional<std::vector<Success>> successes;
                        JS_OBJ(errors, successes);
                    };
                    std::optional<std::optional<string>> status;
                    std::optional<Data> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
