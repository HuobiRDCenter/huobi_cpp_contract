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
                struct SwapAccountBalanceResponse
                {
                    std::optional<int32_t> code;

                    struct Data
                    {
                        std::string state;
                        std::string equity;
                        std::string isolated_equity;
                        std::string initial_margin;
                        std::string maintenance_margin;
                        std::string maintenance_margin_rate;
                        std::string profit_unreal;
                        std::string available_margin;
                        std::string created_time;
                        std::string updated_time;
                        struct Details
                        {
                            std::string currency;
                            std::string equity;
                            std::string isolated_equity;
                            std::string available;
                            std::string profit_unreal;
                            std::string isolated_available;
                            std::string isolated_hold;
                            std::string isolated_profit_unreal;
                            std::string initial_margin;
                            std::string maintenance_margin;
                            std::string maintenance_margin_rate;
                            std::string initial_margin_rate;
                            std::string created_time;
                            std::string updated_time;
                            JS_OBJ(currency, equity, isolated_equity, available, profit_unreal, isolated_available,
                                   isolated_hold, isolated_profit_unreal, initial_margin, maintenance_margin,
                                   maintenance_margin_rate, initial_margin_rate, created_time, updated_time);
                        };
                        std::optional<Details> details;
                        JS_OBJ(state, equity, isolated_equity, initial_margin, maintenance_margin, maintenance_margin_rate,
                               profit_unreal, available_margin, created_time, updated_time, details);
                    };

                    std::optional<Data> data;

                    std::optional<string> message;

                    int64_t ts;

                    JS_OBJ(code, data, message, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
