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
                struct SwapFinancialRecordResponse
                {
                    struct Data {
                        std::optional<JS::Nullable<int64_t>> query_id;
                        std::optional<JS::Nullable<int64_t>> id;
                        std::optional<JS::Nullable<int64_t>> ts;
                        std::optional<string> asset;
                        std::optional<string> contract_code;
                        std::optional<string> margin_account;
                        std::optional<string> face_margin_account;
                        std::optional<JS::Nullable<int64_t>> type;
                        std::optional<JS::Nullable<float>> amount;
                        JS_OBJ(query_id, id, ts, asset, contract_code, margin_account, face_margin_account, type, amount);
                    };
                    std::optional<JS::Nullable<int64_t>> code;
                    std::optional<std::optional<string>> msg;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<std::vector<Data>> data;
                    JS_OBJ(code, msg, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
