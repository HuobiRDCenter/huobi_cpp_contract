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
            namespace response_reference
            {
                struct ContractApiStateResponse
                {
                    struct AccountPermissions {
                        std::optional<int64_t> open;
                        std::optional<int64_t> close;
                        std::optional<int64_t> cancel;
                        std::optional<int64_t> transfer_in;
                        std::optional<int64_t> transfer_out;
                        std::optional<int64_t> master_transfer_sub;
                        std::optional<int64_t> sub_transfer_master;
                        JS_OBJ(open, close, cancel, transfer_in, transfer_out, master_transfer_sub, sub_transfer_master);
                    };
                    std::optional<std::string> status;
                    std::optional<int64_t> ts;
                    std::optional<std::vector<AccountPermissions>> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

