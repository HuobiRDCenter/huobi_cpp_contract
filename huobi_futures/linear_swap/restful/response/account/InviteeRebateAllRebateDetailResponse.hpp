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
                struct InviteeRebateAllRebateDetailResponse{
                    std::string status;
                    int invitee_uid;
                    struct Data {
                        std::string invitee_type;
                        std::string invitee_rebate_rate_spot_m2;
                        std::string invitee_rebate_rate_contract_m2;
                        std::string invitee_rebate_rate_partner_spot;
                        std::string invitee_rebate_rate_partner_contract;
                        std::string join_time_m2;
                        std::string join_time_partner;
                        // 邀请人返佣
                        std::string Invitee_total_commission_usdt;
                        std::string Invitee_total_commission_trx;
                        std::string Invitee_total_commission_htx;
                        // 合伙人返佣
                        std::string partner_total_commission_usdt;
                        std::string partner_total_commission_trx;
                        std::string partner_total_commission_htx;

                        JS_OBJ(invitee_type, invitee_rebate_rate_spot_m2, invitee_rebate_rate_contract_m2,
                               invitee_rebate_rate_partner_spot, invitee_rebate_rate_partner_contract,
                               join_time_m2, join_time_partner, Invitee_total_commission_usdt,
                               Invitee_total_commission_trx, Invitee_total_commission_htx,
                               partner_total_commission_usdt, partner_total_commission_trx,
                               partner_total_commission_htx);
                    } data;
                    long ts;
                    std::string nextId;

                    JS_OBJ(status, invitee_uid, data, ts, nextId);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures…