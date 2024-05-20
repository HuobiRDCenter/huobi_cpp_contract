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
                struct SwapTransferLimitResponse
                {
                    struct Data {
                        std::optional<string> symbol;
                        std::optional<string> contract_code;
                        std::optional<JS::Nullable<float>> transfer_in_max_each;
                        std::optional<JS::Nullable<float>> transfer_in_min_each;
                        std::optional<JS::Nullable<float>> transfer_out_max_each;
                        std::optional<JS::Nullable<float>> transfer_out_min_each;
                        std::optional<JS::Nullable<float>> transfer_in_max_daily;
                        std::optional<JS::Nullable<float>> transfer_out_max_daily;
                        std::optional<JS::Nullable<float>> net_transfer_in_max_daily;
                        std::optional<JS::Nullable<float>> net_transfer_out_max_daily;

                        JS_OBJ(symbol, contract_code, transfer_in_max_each, transfer_in_min_each, transfer_out_max_each,
                                transfer_out_min_each, transfer_in_max_daily, transfer_out_max_daily,
                                net_transfer_in_max_daily, net_transfer_out_max_daily);
                    };
                    std::optional<string> status;
                    std::optional<std::vector<Data>> data;

                    JS_OBJ(status, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

