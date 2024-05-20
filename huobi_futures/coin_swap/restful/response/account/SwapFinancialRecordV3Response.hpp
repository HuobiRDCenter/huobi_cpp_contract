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
                struct SwapFinancialRecordV3Response
                {
                    struct Data {
                        std::optional<int64_t> query_id;
                        std::optional<int64_t> id;
                        std::optional<int64_t> ts;
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<int64_t> type;
                        std::optional<float> amount;
                        JS_OBJ(query_id, id, ts, symbol, contract_code, type, amount);
                    };
                    std::optional<int64_t> code;
                    std::optional<std::string> msg;
                    std::optional<int64_t> ts;
                    std::optional<std::vector<Data>> data;
                    JS_OBJ(code, msg, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures


