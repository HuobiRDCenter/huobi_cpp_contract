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
                struct ContractEstimatedSettlementPriceResponse
                {
                    struct SettlementData {
                        std::optional<std::string> symbol;
                        struct Contract {
                            std::string contract_type;
                            std::string contract_code;
                            std::optional<JS::Nullable<float>> estimated_settlement_price;
                            std::string settlement_type;
                            JS_OBJ(contract_type, contract_code, estimated_settlement_price, settlement_type);
                        };
                        std::vector<Contract> list;
                        JS_OBJ(symbol, list);
                    };
                    std::optional<std::string> status;
                    std::optional<std::vector<SettlementData>> data;
                    std::optional<int64_t> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

