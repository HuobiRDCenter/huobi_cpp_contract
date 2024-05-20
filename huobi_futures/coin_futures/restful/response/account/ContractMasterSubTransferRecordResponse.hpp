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
                struct ContractMasterSubTransferRecordResponse
                {
                    struct TransferRecord {
                        std::optional<int64_t> id;
                        std::optional<int64_t> ts;
                        std::optional<std::string> symbol;
                        std::optional<std::string> sub_uid;
                        std::optional<std::string> sub_account_name;
                        std::optional<int64_t> transfer_type;
                        std::optional<float> amount;
                        JS_OBJ(id, ts, symbol, sub_uid, sub_account_name, transfer_type, amount);
                    };
                    std::optional<std::string> status;
                    std::optional<int64_t> ts;
                    struct Data {
                        std::vector<TransferRecord> transfer_record;
                        std::optional<int64_t> total_page;
                        std::optional<int64_t> current_page;
                        std::optional<int64_t> total_size;
                        JS_OBJ(transfer_record, total_page, current_page, total_size);
                    };
                    std::optional<Data> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

