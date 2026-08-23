#pragma once

#include <future>
#include <sstream>
#include <vector>
#include <map>

#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

// 引入响应结果
#include "huobi_futures/linear_swap/restful/response/algo/AlgoOrderResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_algo::AlgoOrderResponse AlgoOrderResponse;

#include "huobi_futures/linear_swap/restful/response/algo/AlgoCancelOrdersResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_algo::AlgoCancelOrdersResponse AlgoCancelOrdersResponse;

#include "huobi_futures/linear_swap/restful/response/algo/AlgoQueryOrdersResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_algo::AlgoQueryOrdersResponse AlgoQueryOrdersResponse;

#include "huobi_futures/linear_swap/restful/response/algo/AlgoQueryOpenOrdersResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_algo::AlgoQueryOpenOrdersResponse AlgoQueryOpenOrdersResponse;

#include "huobi_futures/linear_swap/restful/response/algo/AlgoQueryOrderHistoryResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_algo::AlgoQueryOrderHistoryResponse AlgoQueryOrderHistoryResponse;

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            class AlgoClient
            {
            public:
                AlgoClient(const string &access_key, const string &secret_key, const string &host = utils::DEFAULT_HOST)
                {
                    pb = std::make_shared<url_base::PrivateUrlBuilder>(access_key, secret_key, host);
                }

                // POST请求 - 策略委托下单 #39
                std::shared_ptr<AlgoOrderResponse> AlgoOrder(
                    const string &contract_code,
                    const string &type,
                    const string &position_side,
                    const string &side,
                    const string &margin_mode,
                    const string &algo_client_order_id = "",
                    const string &volume = "",
                    const string &tp_trigger_price = "",
                    const string &tp_order_price = "",
                    const string &tp_type = "",
                    const string &tp_trigger_price_type = "",
                    const string &sl_trigger_price = "",
                    const string &sl_order_price = "",
                    const string &sl_type = "",
                    const string &sl_trigger_price_type = "",
                    const string &price = "",
                    const string &price_match = "",
                    const string &trigger_price = "",
                    const string &trigger_price_type = "",
                    const string &active_price = "",
                    const string &order_price_type = "",
                    const string &callback_rate = "",
                    const string &reduce_only = "")
                {
                    // path
                    stringstream path;
                    path << utils::V5_ALGO_ORDER;

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (type != "")
                    {
                        content << ",\"type\":\"" << type << "\"";
                    }
                    if (position_side != "")
                    {
                        content << ",\"position_side\":\"" << position_side << "\"";
                    }
                    if (side != "")
                    {
                        content << ",\"side\":\"" << side << "\"";
                    }
                    if (margin_mode != "")
                    {
                        content << ",\"margin_mode\":\"" << margin_mode << "\"";
                    }
                    if (algo_client_order_id != "")
                    {
                        content << ",\"algo_client_order_id\":\"" << algo_client_order_id << "\"";
                    }
                    if (volume != "")
                    {
                        content << ",\"volume\":\"" << volume << "\"";
                    }
                    if (tp_trigger_price != "")
                    {
                        content << ",\"tp_trigger_price\":\"" << tp_trigger_price << "\"";
                    }
                    if (tp_order_price != "")
                    {
                        content << ",\"tp_order_price\":\"" << tp_order_price << "\"";
                    }
                    if (tp_type != "")
                    {
                        content << ",\"tp_type\":\"" << tp_type << "\"";
                    }
                    if (tp_trigger_price_type != "")
                    {
                        content << ",\"tp_trigger_price_type\":\"" << tp_trigger_price_type << "\"";
                    }
                    if (sl_trigger_price != "")
                    {
                        content << ",\"sl_trigger_price\":\"" << sl_trigger_price << "\"";
                    }
                    if (sl_order_price != "")
                    {
                        content << ",\"sl_order_price\":\"" << sl_order_price << "\"";
                    }
                    if (sl_type != "")
                    {
                        content << ",\"sl_type\":\"" << sl_type << "\"";
                    }
                    if (sl_trigger_price_type != "")
                    {
                        content << ",\"sl_trigger_price_type\":\"" << sl_trigger_price_type << "\"";
                    }
                    if (price != "")
                    {
                        content << ",\"price\":\"" << price << "\"";
                    }
                    if (price_match != "")
                    {
                        content << ",\"price_match\":\"" << price_match << "\"";
                    }
                    if (trigger_price != "")
                    {
                        content << ",\"trigger_price\":\"" << trigger_price << "\"";
                    }
                    if (trigger_price_type != "")
                    {
                        content << ",\"trigger_price_type\":\"" << trigger_price_type << "\"";
                    }
                    if (active_price != "")
                    {
                        content << ",\"active_price\":\"" << active_price << "\"";
                    }
                    if (order_price_type != "")
                    {
                        content << ",\"order_price_type\":\"" << order_price_type << "\"";
                    }
                    if (callback_rate != "")
                    {
                        content << ",\"callback_rate\":\"" << callback_rate << "\"";
                    }
                    if (reduce_only != "")
                    {
                        content << ",\"reduce_only\":\"" << reduce_only << "\"";
                    }

                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<AlgoOrderResponse>(url, data.str());
                    return result;
                }

                // POST请求 - 撤销策略委托 #40，body 为顶层数组 [{...}]
                std::shared_ptr<AlgoCancelOrdersResponse> AlgoCancelOrders(
                    const string &algo_id = "",
                    const string &algo_client_order_id = "",
                    const string &contract_code = "")
                {
                    // path
                    stringstream path;
                    path << utils::V5_ALGO_CANCEL_ORDERS;

                    // option
                    stringstream content;
                    if (algo_id != "")
                    {
                        content << ",\"algo_id\":\"" << algo_id << "\"";
                    }
                    if (algo_client_order_id != "")
                    {
                        content << ",\"algo_client_order_id\":\"" << algo_client_order_id << "\"";
                    }
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }

                    // data —— 单对象包装进顶层数组
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "[{" << content.str().substr(1) << "}]";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<AlgoCancelOrdersResponse>(url, data.str());
                    return result;
                }

                // GET请求 - 查询策略委托 #41，业务参数进签名
                std::shared_ptr<AlgoQueryOrdersResponse> AlgoQueryOrders(
                    const string &type,
                    const string &algo_id = "",
                    const string &algo_client_order_id = "",
                    const string &contract_code = "")
                {
                    map<string, string> params;
                    if (type != "")
                    {
                        params["type"] = type;
                    }
                    if (algo_id != "")
                    {
                        params["algo_id"] = algo_id;
                    }
                    if (algo_client_order_id != "")
                    {
                        params["algo_client_order_id"] = algo_client_order_id;
                    }
                    if (contract_code != "")
                    {
                        params["contract_code"] = contract_code;
                    }

                    // url
                    string url = pb->Build("GET", utils::V5_ALGO_ORDER, params);

                    // get
                    auto result = url_base::HttpRequest::Instance().Get<AlgoQueryOrdersResponse>(url);
                    return result;
                }

                // GET请求 - 查询当前未触发策略委托 #42，业务参数进签名
                std::shared_ptr<AlgoQueryOpenOrdersResponse> AlgoQueryOpenOrders(
                    const string &type,
                    const string &contract_code = "",
                    const string &algo_id = "",
                    const string &algo_client_order_id = "",
                    int64_t from = 0,
                    int32_t limit = 0,
                    const string &direct = "")
                {
                    map<string, string> params;
                    if (type != "")
                    {
                        params["type"] = type;
                    }
                    if (contract_code != "")
                    {
                        params["contract_code"] = contract_code;
                    }
                    if (algo_id != "")
                    {
                        params["algo_id"] = algo_id;
                    }
                    if (algo_client_order_id != "")
                    {
                        params["algo_client_order_id"] = algo_client_order_id;
                    }
                    if (from != 0)
                    {
                        params["from"] = std::to_string(from);
                    }
                    if (limit != 0)
                    {
                        params["limit"] = std::to_string(limit);
                    }
                    if (direct != "")
                    {
                        params["direct"] = direct;
                    }

                    // url
                    string url = pb->Build("GET", utils::V5_ALGO_ORDER_OPENS, params);

                    // get
                    auto result = url_base::HttpRequest::Instance().Get<AlgoQueryOpenOrdersResponse>(url);
                    return result;
                }

                // GET请求 - 查询历史策略委托 #43，业务参数进签名
                std::shared_ptr<AlgoQueryOrderHistoryResponse> AlgoQueryOrderHistory(
                    const string &type,
                    const string &contract_code = "",
                    const string &margin_mode = "",
                    const string &states = "",
                    const string &start_time = "",
                    const string &end_time = "",
                    int64_t from = 0,
                    int32_t limit = 0,
                    const string &direct = "")
                {
                    map<string, string> params;
                    if (type != "")
                    {
                        params["type"] = type;
                    }
                    if (contract_code != "")
                    {
                        params["contract_code"] = contract_code;
                    }
                    if (margin_mode != "")
                    {
                        params["margin_mode"] = margin_mode;
                    }
                    if (states != "")
                    {
                        params["states"] = states;
                    }
                    if (start_time != "")
                    {
                        params["start_time"] = start_time;
                    }
                    if (end_time != "")
                    {
                        params["end_time"] = end_time;
                    }
                    if (from != 0)
                    {
                        params["from"] = std::to_string(from);
                    }
                    if (limit != 0)
                    {
                        params["limit"] = std::to_string(limit);
                    }
                    if (direct != "")
                    {
                        params["direct"] = direct;
                    }

                    // url
                    string url = pb->Build("GET", utils::V5_ALGO_ORDER_HISTORY, params);

                    // get
                    auto result = url_base::HttpRequest::Instance().Get<AlgoQueryOrderHistoryResponse>(url);
                    return result;
                }

            private:
                std::shared_ptr<url_base::PrivateUrlBuilder> pb;
            };
        }
    }
}