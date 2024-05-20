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
                struct SwapSubAccountInfoListResponse
                {
                    struct AccountInfo {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::int64_t> margin_balance;
                        std::optional<std::int64_t> liquidation_price;
                        std::optional<float> risk_rate;
                        JS_OBJ(symbol, margin_balance, liquidation_price, risk_rate);
                    };

                    struct SubAccount {
                        std::int64_t sub_uid;
                        std::vector<std::vector<AccountInfo>> account_info_list;
                        JS_OBJ(sub_uid, account_info_list);
                    };

                    struct ResponseData {
                        std::vector<std::vector<SubAccount>> sub_list;
                        std::int64_t current_page;
                        std::int64_t total_page;
                        std::int64_t total_size;
                        JS_OBJ(sub_list, current_page, total_page, total_size);
                    };
                    std::string status;
                    std::int64_t ts;
                    std::optional<ResponseData> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

