#pragma once

#include <string>
using std::string;

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
                struct EarnOrderDemandRedeemOrderResponse
                {
                    int code;
                    std::string message;
                    RedeemDto data;

                    JS_OBJ(code, message, data);
                    struct RedeemDto {
                        std::string currency;
                        std::string amount;
                        long orderId;
                        int status;

                        JS_OBJ(currency, amount, orderId, status);
                    };
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
