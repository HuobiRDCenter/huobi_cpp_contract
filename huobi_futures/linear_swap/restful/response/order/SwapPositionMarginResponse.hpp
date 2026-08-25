#pragma once

#include <string>
#include <optional>
#include <memory>
#include "huobi_futures/json_struct/json_struct.h"

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_order
            {
                struct SwapPositionMarginResponse
                {
                    struct Data
                    {
                        // DataBean 为空结构，添加占位字段以编译
                        std::optional<int32_t> _placeholder;
                        JS_OBJ(_placeholder);
                    };

                    std::optional<int32_t> code;
                    // V5 position/margin：无持仓或参数不全时 data 为 null，optional 遇 null 解析失败，改 unique_ptr
                    std::unique_ptr<Data> data;
                    std::optional<std::string> message;
                    std::optional<int64_t> ts;

                    JS_OBJ(code, data, message, ts);
                };
            }
        }
    }
}