#pragma once

#include <string>
#include <vector>
#include <optional>
#include "huobi_futures/json_struct/json_struct.h"

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            namespace response_order
            {
                struct SwapPositionRiskLimitTierResponse
                {
                    // 对应Java的Integer code
                    std::optional<int32_t> code;
                    
                    // 对应Java的List<DataBean> data
                    struct DataBean
                    {
                        // 对应Java的contract_code
                        std::string contract_code;
                        
                        // 对应Java的margin_mode
                        std::string margin_mode;
                        
                        // 对应Java的tier
                        std::string tier;
                        
                        // 对应Java的max_lever
                        std::string max_lever;
                        
                        // 对应Java的maintenance_margin_rate
                        std::string maintenance_margin_rate;
                        
                        // 对应Java的max_volume
                        std::string max_volume;
                        
                        // 对应Java的min_volume
                        std::string min_volume;
                        
                        // 对应Java的volume_unit
                        std::string volume_unit;
                        
                        JS_OBJ(contract_code, margin_mode, tier, max_lever, maintenance_margin_rate, 
                               max_volume, min_volume, volume_unit);
                    };
                    
                    // data是一个列表
                    std::optional<std::vector<DataBean>> data;
                    
                    // 对应Java的message
                    std::optional<string> message;
                    
                    // 对应Java的ts
                    int64_t ts;
                    
                    JS_OBJ(code, data, message, ts);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures