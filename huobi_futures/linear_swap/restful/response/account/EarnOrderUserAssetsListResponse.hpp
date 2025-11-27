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
                struct EarnOrderUserAssetsListResponse
                {
                    int code;
                    std::string message;
                    PageInfoResVo data;
                    int total;
                    std::vector<UserAssetsInfoCouponExpandResDto> items;

                    JS_OBJ(code, message, data, total, items);
                    struct PageInfoResVo {
                        int total;
                        std::vector<UserAssetsInfoCouponExpandResDto> items;

                        JS_OBJ(total, items);
                    };

                    struct UserAssetsInfoCouponExpandResDto {
                        int64_t projectId;
                        int64_t orderId;
                        int projectType;
                        std::string currency;
                        std::string yesterdayIncome;
                        std::string totalIncomeAmount;
                        std::string totalAmount;
                        std::string miningYearRate;
                        int apyType;

                        JS_OBJ(projectId, orderId, projectType, currency, yesterdayIncome, totalIncomeAmount, totalAmount, miningYearRate, apyType);
                    };
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
