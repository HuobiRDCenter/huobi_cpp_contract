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
                struct ContractSubAuthResponse
                {
                    struct Data {
                        struct ErrorDetail {
                            std::optional<std::string> sub_uid;
                            std::optional<std::string> err_code;
                            std::optional<std::string> err_msg;
                            JS_OBJ(sub_uid, err_code, err_msg);
                        };
                        struct SuccessDetail {
                            std::optional<int64_t> query_id;
                            std::string sub_uid;
                            std::string sub_auth;
                            JS_OBJ(query_id, sub_uid, sub_auth);
                        };
                    };
                    std::optional<std::string> status;
                    std::optional<int64_t> ts;
                    std::vector<Data> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

