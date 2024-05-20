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
            namespace response_reference
            {
                struct GetHeartbeatResponse
                {
                    std::optional<std::string> status; // "ok" or "error"
                    struct Data
                    {
                        std::optional<JS::Nullable<int64_t>> heartbeat; // 1: Available, 0: Not available (maintenance)
                        std::optional<JS::Nullable<int64_t>> swap_heartbeat; // 1: Available, 0: Not available (maintenance)
                        std::optional<JS::Nullable<int64_t>> estimated_recovery_time; // null: normal, estimated recovery time in ms
                        std::optional<JS::Nullable<int64_t>> swap_estimated_recovery_time; // null: normal, estimated recovery time in ms
                        std::optional<JS::Nullable<int64_t>> linear_swap_heartbeat; // U-based contract 1: Available, 0: Not available
                        std::optional<JS::Nullable<int64_t>> linear_swap_estimated_recovery_time; // null: normal, estimated recovery time in ms
                        JS_OBJ(heartbeat, swap_heartbeat, estimated_recovery_time, swap_estimated_recovery_time, linear_swap_heartbeat, linear_swap_estimated_recovery_time);
                    };
                    std::optional<Data> data;
                    std::optional<JS::Nullable<int64_t>> ts;
                    JS_OBJ(status, data, ts);
                };
            } // namespace response_account
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
