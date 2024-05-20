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
                struct ContractContractInfoResponse
                {
                    struct ContractDetails {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> contract_type;
                        std::optional<double> contract_size;
                        std::optional<double> price_tick;
                        std::optional<std::string> delivery_date;
                        std::optional<std::string> create_date;
                        std::optional<std::string> settlement_time;
                        std::optional<std::string> delivery_time;
                        std::optional<int64_t> contract_status;
                        JS_OBJ(symbol, contract_code, contract_type, contract_size, price_tick, delivery_date, create_date, settlement_time, delivery_time, contract_status);
                    };
                    std::optional<std::string> status;
                    std::optional<int64_t> ts;
                    std::optional<std::vector<ContractDetails>> data;
                    JS_OBJ(status, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

