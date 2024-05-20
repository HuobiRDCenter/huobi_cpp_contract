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
                struct SwapSubAuthListResponse
                {
                    struct Error {
                        std::optional<std::string> sub_uid;
                        std::optional<std::string> err_code;
                        std::optional<std::string> err_msg;
                        JS_OBJ(sub_uid, err_code, err_msg);
                    };

                    struct Success {
                        std::optional<std::string> sub_uid;
                        std::optional<std::string> sub_auth;
                        JS_OBJ(sub_uid, sub_auth);
                    };
                    struct Data {
                        std::optional<std::vector<Error>> errors;
                        std::optional<std::vector<Success>> successes;
                        JS_OBJ(errors, successes)
                    };
                    std::optional<std::string> status;
                    std::optional<Data> data;
                    std::optional<int64_t> ts;

                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

