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
                struct QueryEarnProjectListResponse
                {
                    int code;
                    std::string message;
                    PageInfoResVo data;
                    int total;
                    std::vector<SavingProjectDTO> items;

                    JS_OBJ(code, message, data, total, items);
                    struct TieredRateVo {
                        std::string amountStart;
                        std::string amountEnd;
                        std::string rate;

                        JS_OBJ(amountStart, amountEnd, rate);
                    };

                    struct SavingProjectDTO {
                        std::string projectId;
                        std::string productId;
                        int calculationType;
                        int type;
                        std::string viewYearRate;
                        std::string finishAmount;
                        int projectStatus;
                        std::string totalAmount;
                        std::string currency;
                        std::string startAmount;
                        int apyType;
                        std::vector<TieredRateVo> tieredRates;
                        std::string marketPerkUpLimit;
                        std::string marketTimeApy;
                        std::string marketPerkApy;

                        JS_OBJ(projectId, productId, calculationType, type, viewYearRate, finishAmount,
                               projectStatus, totalAmount, currency, startAmount, apyType, tieredRates,
                               marketPerkUpLimit, marketTimeApy, marketPerkApy);
                    };

                    struct PageInfoResVo {
                        int total;
                        std::vector<SavingProjectDTO> items;

                        JS_OBJ(total, items);
                    };

                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
