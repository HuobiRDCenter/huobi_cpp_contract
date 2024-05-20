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
                struct ContractSettlementRecordsResponse
                {
                    struct List {
                        std::optional<std::string> contract_code;
                        std::optional<JS::Nullable<float>> settlement_price;
                        std::optional<std::string> settlement_type;
                        JS_OBJ(contract_code, settlement_price, settlement_type);
                    };

                    struct SettlementRecord {
                        std::optional<std::string> symbol;
                        std::optional<JS::Nullable<int64_t>> settlement_time;
                        std::optional<JS::Nullable<float>> clawback_ratio;
                        std::optional<std::vector<List>> list;
                        JS_OBJ(symbol, settlement_time, clawback_ratio, list);
                    };

                    struct Data {
                        std::optional<std::vector<SettlementRecord>> settlement_record;
                        std::optional<JS::Nullable<int64_t>> total_page;
                        std::optional<JS::Nullable<int64_t>> current_page;
                        std::optional<JS::Nullable<int64_t>> total_size;
                        JS_OBJ(settlement_record, total_page, current_page, total_size);
                    };
                    std::optional<std::string> status;
                    std::optional<JS::Nullable<int64_t>> ts;
                    std::optional<Data> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

