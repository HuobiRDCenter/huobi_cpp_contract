#pragma once

#include <string>
using std::string;

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
                struct UniversalTransferRecordsResponse
                {
                    std::optional<int32_t> code;
                    std::optional<string> message;
                    int64_t ts;

                    struct DataBean
                    {
                        int64_t id;
                        int64_t transfer_id;
                        string amount;
                        string currency;
                        string status;
                        string from_account_type;
                        string to_account_type;
                        std::optional<string> from_asset_type;
                        std::optional<string> to_asset_type;
                        int64_t ts;

                        JS_OBJ(id, transfer_id, amount, currency, status, from_account_type, 
                               to_account_type, from_asset_type, to_asset_type, ts);
                    };

                    std::optional<std::vector<DataBean>> data;

                    JS_OBJ(code, message, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures