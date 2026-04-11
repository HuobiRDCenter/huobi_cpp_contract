#pragma once

#include <string>
#include <vector>
#include <optional>
#include "huobi_futures/json_struct/json_struct.h"

namespace huobi_futures
{
    namespace coin_futures
    {
        namespace ws
        {
            namespace response_notify
            {
                struct SubAccountResponse
                {
                    struct CurrencyDetail
                    {
                        std::optional<std::string> currency;
                        std::optional<std::string> equity;
                        std::optional<std::string> isolated_equity;
                        std::optional<std::string> available;
                        std::optional<std::string> withdraw_available;
                        std::optional<std::string> profit_unreal;
                        std::optional<std::string> isolated_profit_unreal;
                        std::optional<std::string> initial_margin;
                        std::optional<std::string> maintenance_margin;
                        std::optional<std::string> maintenance_margin_rate;
                        std::optional<std::string> initial_margin_rate;
                        std::optional<std::string> voucher;
                        std::optional<std::string> voucher_value;
                        std::optional<std::string> created_time;
                        std::optional<std::string> updated_time;

                        JS_OBJ(currency, equity, isolated_equity, available, withdraw_available,
                               profit_unreal, isolated_profit_unreal, initial_margin, maintenance_margin,
                               maintenance_margin_rate, initial_margin_rate, voucher, voucher_value,
                               created_time, updated_time);
                    };

                    struct AccountData
                    {
                        std::optional<std::string> state;
                        std::optional<std::string> equity;
                        std::optional<std::string> initial_margin;
                        std::optional<std::string> maintenance_margin;
                        std::optional<std::string> maintenance_margin_rate;
                        std::optional<std::string> profit_unreal;
                        std::optional<std::string> available_margin;
                        std::optional<std::string> voucher_value;
                        std::optional<std::string> created_time;
                        std::optional<std::string> updated_time;
                        std::optional<std::string> version;
                        std::optional<std::vector<CurrencyDetail>> details;

                        JS_OBJ(state, equity, initial_margin, maintenance_margin, maintenance_margin_rate,
                               profit_unreal, available_margin, voucher_value, created_time, updated_time,
                               version, details);
                    };

                    std::string op;
                    std::string topic;
                    std::optional<int64_t> ts;
                    std::optional<std::string> event;
                    std::optional<std::string> uid;
                    std::optional<std::vector<AccountData>> data;

                    JS_OBJ(op, topic, ts, event, uid, data);
                };
            }
        }
    }
}