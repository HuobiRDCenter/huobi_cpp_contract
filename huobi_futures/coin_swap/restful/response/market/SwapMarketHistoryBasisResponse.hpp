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
            namespace response_market
            {
                struct SwapMarketHistoryBasisResponse
                {
                    struct BasisData {
                        std::optional<JS::Nullable<int64_t>> id;
                        std::optional<JS::Nullable<float>> contract_price;
                        std::optional<std::string> index_price;
                        std::optional<std::string> basis;
                        std::optional<std::string> basis_rate;
                        JS_OBJ(id, contract_price, index_price, basis, basis_rate);
                    };
                    std::optional<std::string> ch;
                    std::optional<std::string> status;
                    std::optional<std::vector<BasisData>> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(ch, status, data, ts);
                };
            } // namespace response_market
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

