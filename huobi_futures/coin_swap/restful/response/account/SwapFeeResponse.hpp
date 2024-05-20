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
                struct SwapFeeResponse
                {
                    struct Data {
                        std::optional<std::string> symbol;
                        std::optional<std::string> contract_code;
                        std::optional<std::string> fee_asset;
                        std::optional<JS::Nullable<float>> open_maker_fee;
                        std::optional<JS::Nullable<float>> open_taker_fee;
                        std::optional<JS::Nullable<float>> close_maker_fee;
                        std::optional<JS::Nullable<float>> close_taker_fee;
                        std::optional<JS::Nullable<float>> delivery_fee;

                        JS_OBJ(symbol, contract_code, fee_asset, open_maker_fee, open_taker_fee, close_maker_fee, close_taker_fee, delivery_fee);
                    };

                    std::optional<std::vector<Data>> data;

                    JS_OBJ(data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

