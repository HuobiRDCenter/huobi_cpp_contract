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
                struct InviteeRebateReferralsResponse
                {
                    std::optional<int> code;
                    std::optional<string> message;
                    long ts;

                    struct ReferralDetailVO
                    {
                        int id;
                        int inviteUid;
                        string remark;
                        string referralCode;
                        int inviteeType;
                        string inviteeRebateRateSpotM2;
                        string inviteeRebateRateContractM2;
                        string inviteeRebateRatePartnerSpot;
                        string inviteeRebateRatePartnerContract;
                        long joinTimeM2;
                        long joinTimePartner;
                        string spotTradingVolume;
                        string futuresTradingVolume;

                        JS_OBJ(id, inviteUid, remark, referralCode, inviteeType,
                               inviteeRebateRateSpotM2, inviteeRebateRateContractM2,
                               inviteeRebateRatePartnerSpot, inviteeRebateRatePartnerContract,
                               joinTimeM2, joinTimePartner, spotTradingVolume, futuresTradingVolume);
                    };

                    struct Data
                    {
                        long nextId;
                        std::vector<ReferralDetailVO> rebateDetailList;

                        JS_OBJ(nextId, rebateDetailList);
                    };

                    std::optional<Data> data;

                    JS_OBJ(code, message, ts, data);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures