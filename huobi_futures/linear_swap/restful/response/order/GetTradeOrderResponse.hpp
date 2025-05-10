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
            namespace response_order
            {
                struct GetTradeOrderResponse
                {
                    int64_t code;
                    std::string message;

                    struct Data
                    {
                        // 基础信息
                        std::string id;
                        std::string contractCode;
                        std::string side;
                        std::string positionSide;
                        std::string type;

                        // 订单参数
                        std::string priceMatch;
                        std::string orderId;
                        std::string clientOrderId;
                        std::string marginMode;
                        std::string price;
                        std::string volume;
                        int64_t leverRate;

                        // 状态信息
                        std::string state;
                        std::string orderSource;
                        bool reduceOnly;
                        std::string timeInForce;

                        // 止盈止损
                        std::string tpTriggerPrice;
                        std::string tpOrderPrice;
                        std::string tpType;
                        std::string tpTriggerPriceType;
                        std::string slTriggerPrice;
                        std::string slOrderPrice;
                        std::string slType;
                        std::string slTriggerPriceType;

                        // 成交信息
                        std::string tradeAvgPrice;
                        std::string tradeVolume;
                        std::string tradeTurnover;

                        // 费用相关
                        std::string feeCurrency;
                        std::string fee;

                        // 其他参数
                        bool priceProtect;
                        std::string profit;
                        std::string contractType;
                        int64_t createdTime;
                        int64_t updatedTime;

                        JS_OBJ(
                            id,
                            contract_code,
                            side,
                            position_side,
                            type,
                            price_match,
                            order_id,
                            client_order_id,
                            margin_mode,
                            price,
                            volume,
                            lever_rate,
                            state,
                            order_source,
                            reduce_only,
                            time_in_force,
                            tp_trigger_price,
                            tp_order_price,
                            tp_type,
                            tp_trigger_price_type,
                            sl_trigger_price,
                            sl_order_price,
                            sl_type,
                            sl_trigger_price_type,
                            trade_avg_price,
                            trade_volume,
                            trade_turnover,
                            fee_currency,
                            fee,
                            price_protect,
                            profit,
                            contract_type,
                            created_time,
                            updated_time
                        );
                    };
                    std::optional<Data> data;

                    int64_t ts;

                    JS_OBJ(code, message, data, ts);
                };
            } // namespace response_order
        }     // namespace restful
    }         // namespace linear_swap
} // namespace huobi_futures
