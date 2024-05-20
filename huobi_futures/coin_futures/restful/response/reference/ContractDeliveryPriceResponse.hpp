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
                struct ContractDeliveryPriceResponse
                {
                    struct DeliveryData {
                        std::optional<JS::Nullable<float>> delivery_price;
                        JS_OBJ(delivery_price);
                    };
                    std::optional<std::string> status;
                    std::optional<DeliveryData> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace coin_futures
} // namespace huobi_futures

