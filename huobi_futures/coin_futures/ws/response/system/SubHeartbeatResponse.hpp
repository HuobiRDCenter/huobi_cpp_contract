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
        namespace ws
        {
            namespace response_system
            {
                struct SubHeartbeatResponse
                {
                    string op;

                    string topic;

                    string event;

                    int64_t ts;

                    struct Data
                    {
                        int32_t heartbeat;

                        int64_t estimated_recovery_time;

                        JS_OBJ(heartbeat, estimated_recovery_time);
                    };

                    std::optional<Data> data;

                    JS_OBJ(op, topic, event, ts, data);
                };
            } // namespace response_system
        }     // namespace ws
    }         // namespace coin_futures
} // namespace huobi_futures
