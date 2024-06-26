﻿#pragma once

#include <future>
#include <sstream>
#include <vector>

#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/linear_swap/restful/response/trigger_order/PlaceOrderResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_trigger_order::PlaceOrderResponse TPlaceOrderResponse;

#include "huobi_futures/linear_swap/restful/response/trigger_order/CancelOrderResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_trigger_order::CancelOrderResponse TCancelOrderResponse;

#include "huobi_futures/linear_swap/restful/response/trigger_order/GetOpenOrderResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_trigger_order::GetOpenOrderResponse GetTOpenOrderResponse;

#include "huobi_futures/linear_swap/restful/response/trigger_order/GetHisordersResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_trigger_order::GetHisordersResponse GetTHisordersResponse;

#include "huobi_futures/linear_swap/restful/response/trigger_order/TpslOrderResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_trigger_order::TpslOrderResponse TpslOrderResponse;

#include "huobi_futures/linear_swap/restful/response/trigger_order/GetRelationTpslOrderResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_trigger_order::GetRelationTpslOrderResponse GetRelationTpslOrderResponse;

#include "huobi_futures/linear_swap/restful/response/trigger_order/SwapTrackCancelResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_trigger_order::SwapTrackCancelResponse SwapTrackCancelResponse;

#include "huobi_futures/linear_swap/restful/response/trigger_order/SwapTrackHisOrdersResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_trigger_order::SwapTrackHisOrdersResponse SwapTrackHisOrdersResponse;

#include "huobi_futures/linear_swap/restful/response/trigger_order/SwapTrackOpenOrdersResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_trigger_order::SwapTrackOpenOrdersResponse SwapTrackOpenOrdersResponse;

#include "huobi_futures/linear_swap/restful/response/trigger_order/SwapTrackOrderResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_trigger_order::SwapTrackOrderResponse SwapTrackOrderResponse;

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            class TriggerOrderClient
            {

            public:
                TriggerOrderClient(const string &access_key, const string &secret_key, const string &host = utils::DEFAULT_HOST)
                {
                    pb = std::make_shared<url_base::PrivateUrlBuilder>(access_key, secret_key, host);
                }

                std::shared_ptr<TPlaceOrderResponse> IsolatedTriggerOrder(const string &contract_code, const string &trigger_type, float trigger_price,
                                                                         int volume, const string &direction, const string &offset, int lever_rate = 0,
                                                                         float order_price = 0, const string &order_price_type = "", int reduce_only = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_trigger_order";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"trigger_type\":\"" << trigger_type << "\""
                            << ",\"trigger_price\":" << trigger_price
                            << ",\"volume\":" << volume
                            << ",\"direction\":\"" << direction << "\""
                            << ",\"offset\":\"" << offset << "\"";
                    if (lever_rate != 0)
                    {
                        content << ",\"lever_rate\":" << lever_rate;
                    }
                    if (order_price != 0)
                    {
                        content << ",\"order_price\":" << order_price;
                    }
                    if (order_price_type != "")
                    {
                        content << ",\"order_price_type\":\"" << order_price_type << "\"";
                    }
                    if (reduce_only != 0)
                    {
                        content << ",\"reduce_only\":" << reduce_only;
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
                    auto result = url_base::HttpRequest::Instance().Post<TPlaceOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<TPlaceOrderResponse> CrossTriggerOrder(const string &contract_code, const string &trigger_type, float trigger_price,
                                                                      float volume, const string &direction, const string &offset, int lever_rate = 0,
                                                                      float order_price = 0, const string &order_price_type = "", const string &pair = "",
                                                                      int reduce_only)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_trigger_order";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"trigger_type\":\"" << trigger_type << "\""
                            << ",\"trigger_price\":" << trigger_price
                            << ",\"volume\":" << volume
                            << ",\"direction\":\"" << direction << "\""
                            << ",\"offset\":\"" << offset << "\"";
                    if (lever_rate != 0)
                    {
                        content << ",\"lever_rate\":" << lever_rate;
                    }
                    if (order_price != 0)
                    {
                        content << ",\"order_price\":" << order_price;
                    }
                    if (order_price_type != "")
                    {
                        content << ",\"order_price_type\":\"" << order_price_type << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<TPlaceOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<TCancelOrderResponse> IsolatedCancelTriggerOrder(const string &contract_code, const string &order_id = "",
                                                                                const string &direction = "", const string &offset = "")
                {
                    // path
                    stringstream path;
                    if (order_id != "")
                    {
                        path << "/linear-swap-api/v1/swap_trigger_cancel";
                    }
                    else
                    {
                        path << "/linear-swap-api/v1/swap_trigger_cancelall";
                    }

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\"";
                    if (order_id != "")
                    {
                        content << ",\"order_id\":\"" << order_id << "\"";
                    }
                    if (direction != "")
                    {
                        content << ",\"direction\":\"" << direction << "\"";
                    }
                    if (offset != "")
                    {
                        content << ",\"offset\":\"" << offset << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<TCancelOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<TCancelOrderResponse> CrossCancelTriggerOrder(const string &contract_code, const string &order_id = "",
                                                                             const string &direction = "", const string &offset = "",
                                                                             const string &pair = "", const string &contract_type = "")
                {
                    // path
                    stringstream path;
                    if (order_id != "")
                    {
                        path << "/linear-swap-api/v1/swap_cross_trigger_cancel";
                    }
                    else
                    {
                        path << "/linear-swap-api/v1/swap_cross_trigger_cancelall";
                    }

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\"";
                    if (order_id != "")
                    {
                        content << ",\"order_id\":\"" << order_id << "\"";
                    }
                    if (direction != "")
                    {
                        content << ",\"direction\":\"" << direction << "\"";
                    }
                    if (offset != "")
                    {
                        content << ",\"offset\":\"" << offset << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<TCancelOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetTOpenOrderResponse> IsolatedGetTriggerOpenOrder(const string &contract_code, int page_index = 0,
                                                                                  int page_size = 0, int trade_type = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_trigger_openorders";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\"";
                    if (page_index != 0)
                    {
                        content << ",\"page_index\":" << page_index;
                    }
                    if (page_size != 0)
                    {
                        content << ",\"page_size\":" << page_size;
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetTOpenOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetTOpenOrderResponse> CrossGetTriggerOpenOrder(const string &contract_code, int page_index = 0,
                                                                               int page_size = 0, int trade_type = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_trigger_openorders";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\"";
                    if (page_index != 0)
                    {
                        content << ",\"page_index\":" << page_index;
                    }
                    if (page_size != 0)
                    {
                        content << ",\"page_size\":" << page_size;
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetTOpenOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetTHisordersResponse> IsolatedGetTriggerHisorders(const string &contract_code, int trade_type, const string &status,
                                                                                  int create_date, int page_index = 0, int page_size = 0,
                                                                                  const string &sort_by = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_trigger_hisorders";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"trade_type\":" << trade_type
                            << ",\"status\":\"" << status << "\""
                            << ",\"create_date\":" << create_date;
                    if (page_index != 0)
                    {
                        content << ",\"page_index\":" << page_index;
                    }
                    if (page_size != 0)
                    {
                        content << ",\"page_size\":" << page_size;
                    }
                    if (sort_by != "")
                    {
                        content << ",\"sort_by\":\"" << sort_by << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetTHisordersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetTHisordersResponse> CrossGetTriggerHisorders(const string &contract_code, int trade_type, const string &status,
                                                                               int create_date, int page_index = 0, int page_size = 0,
                                                                               const string &sort_by = "", const string &pair = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_trigger_hisorders";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"trade_type\":" << trade_type
                            << ",\"status\":\"" << status << "\""
                            << ",\"create_date\":" << create_date;
                    if (page_index != 0)
                    {
                        content << ",\"page_index\":" << page_index;
                    }
                    if (page_size != 0)
                    {
                        content << ",\"page_size\":" << page_size;
                    }
                    if (sort_by != "")
                    {
                        content << ",\"sort_by\":\"" << sort_by << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetTHisordersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<TpslOrderResponse> IsolatedTpslOrder(const string &contract_code, const string &direction, float volume,
                                                                     float tp_trigger_price = 0, float tp_order_price = 0, const string &tp_order_price_type = "",
                                                                     float sl_trigger_price = 0, float sl_order_price = 0, const string &sl_order_price_type = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_tpsl_order";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"direction\":\"" << direction << "\""
                            << ",\"volume\":" << volume;
                    if (tp_trigger_price != 0)
                    {
                        content << ",\"tp_trigger_price\":" << tp_trigger_price;
                    }
                    if (tp_order_price != 0)
                    {
                        content << ",\"tp_order_price\":" << tp_order_price;
                    }
                    if (tp_order_price_type != "")
                    {
                        content << ",\"tp_order_price_type\":\"" << tp_order_price_type << "\"";
                    }
                    if (sl_trigger_price != 0)
                    {
                        content << ",\"sl_trigger_price\":" << sl_trigger_price;
                    }
                    if (sl_order_price != 0)
                    {
                        content << ",\"sl_order_price\":" << sl_order_price;
                    }
                    if (sl_order_price_type != "")
                    {
                        content << ",\"sl_order_price_type\":\"" << sl_order_price_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<TpslOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<TpslOrderResponse> CrossTpslOrder(const string &contract_code, const string &direction, float volume,
                                                                  float tp_trigger_price = 0, float tp_order_price = 0, const string &tp_order_price_type = "",
                                                                  float sl_trigger_price = 0, float sl_order_price = 0, const string &sl_order_price_type = "",
                                                                  const string &pair = "", const string &contract_type = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_tpsl_order";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"direction\":\"" << direction << "\""
                            << ",\"volume\":" << volume;
                    if (tp_trigger_price != 0)
                    {
                        content << ",\"tp_trigger_price\":" << tp_trigger_price;
                    }
                    if (tp_order_price != 0)
                    {
                        content << ",\"tp_order_price\":" << tp_order_price;
                    }
                    if (tp_order_price_type != "")
                    {
                        content << ",\"tp_order_price_type\":\"" << tp_order_price_type << "\"";
                    }
                    if (sl_trigger_price != 0)
                    {
                        content << ",\"sl_trigger_price\":" << sl_trigger_price;
                    }
                    if (sl_order_price != 0)
                    {
                        content << ",\"sl_order_price\":" << sl_order_price;
                    }
                    if (sl_order_price_type != "")
                    {
                        content << ",\"sl_order_price_type\":\"" << sl_order_price_type << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<TpslOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<TCancelOrderResponse> IsolatedCancelTpslOrder(const string &contract_code, const string &order_id = "",
                                                                             const string &direction = "")
                {
                    // path
                    stringstream path;
                    if (order_id != "")
                    {
                        path << "/linear-swap-api/v1/swap_tpsl_cancel";
                    }
                    else
                    {
                        path << "/linear-swap-api/v1/swap_tpsl_cancelall";
                    }

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\"";
                    if (order_id != "")
                    {
                        content << ",\"order_id\":\"" << order_id << "\"";
                    }
                    if (direction != "")
                    {
                        content << ",\"direction\":\"" << direction << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<TCancelOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<TCancelOrderResponse> CrossCancelTpslOrder(const string &contract_code, const string &order_id = "",
                                                                          const string &direction = "", const string &pair = "",
                                                                           const string &contract_type = "")
                {
                    // path
                    stringstream path;
                    if (order_id != "")
                    {
                        path << "/linear-swap-api/v1/swap_cross_tpsl_cancel";
                    }
                    else
                    {
                        path << "/linear-swap-api/v1/swap_cross_tpsl_cancelall";
                    }

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\"";
                    if (order_id != "")
                    {
                        content << ",\"order_id\":\"" << order_id << "\"";
                    }
                    if (direction != "")
                    {
                        content << ",\"direction\":\"" << direction << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<TCancelOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetTOpenOrderResponse> IsolatedGetTpslOpenOrder(const string &contract_code, int page_index = 0,
                                                                               int page_size = 0, int trade_type = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_tpsl_openorders";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\"";
                    if (page_index != 0)
                    {
                        content << ",\"page_index\":" << page_index;
                    }
                    if (page_size != 0)
                    {
                        content << ",\"page_size\":" << page_size;
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetTOpenOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetTOpenOrderResponse> CrossGetTpslOpenOrder(const string &contract_code, int page_index = 0,
                                                                            int page_size = 0, int trade_type = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_tpsl_openorders";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\"";
                    if (page_index != 0)
                    {
                        content << ",\"page_index\":" << page_index;
                    }
                    if (page_size != 0)
                    {
                        content << ",\"page_size\":" << page_size;
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetTOpenOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetTHisordersResponse> IsolatedGetTpslHisorders(const string &contract_code, const string &status, int create_date, 
                                                                               int page_index = 0, int page_size = 0, const string &sort_by = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_tpsl_hisorders";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"status\":\"" << status << "\""
                            << ",\"create_date\":" << create_date;
                    if (page_index != 0)
                    {
                        content << ",\"page_index\":" << page_index;
                    }
                    if (page_size != 0)
                    {
                        content << ",\"page_size\":" << page_size;
                    }
                    if (sort_by != "")
                    {
                        content << ",\"sort_by\":\"" << sort_by << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetTHisordersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetTHisordersResponse> CrossGetTpslHisorders(const string &contract_code, const string &status, int create_date, 
                                                                            int page_index = 0, int page_size = 0, const string &sort_by = "", const string &pair = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_tpsl_hisorders";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"status\":\"" << status << "\""
                            << ",\"create_date\":" << create_date;
                    if (page_index != 0)
                    {
                        content << ",\"page_index\":" << page_index;
                    }
                    if (page_size != 0)
                    {
                        content << ",\"page_size\":" << page_size;
                    }
                    if (sort_by != "")
                    {
                        content << ",\"sort_by\":\"" << sort_by << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetTHisordersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetRelationTpslOrderResponse> IsolatedGetRelationTpslOrder(const string &contract_code, long order_id)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_relation_tpsl_order";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"order_id\":" << order_id;

                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<GetRelationTpslOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetRelationTpslOrderResponse> CrossGetRelationTpslOrder(const string &contract_code, long order_id, const string &pair = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_relation_tpsl_order";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"order_id\":" << order_id;
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetRelationTpslOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTrackOrderResponse> SwapTrackOrder(const string &contract_code, const string &direction,
                                                                       const string &offset,const string &order_price_type,
                                                                       int reduce_only, int lever_rate, float volume, float callback_rate,
                                                                       float active_price)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_track_order";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (direction != "")
                    {
                        content << ",\"direction\":\"" << direction << "\"";
                    }
                    if (offset != "")
                    {
                        content << ",\"offset\":\"" << offset << "\"";
                    }
                    if (order_price_type != "")
                    {
                        content << ",\"order_price_type\":\"" << order_price_type << "\"";
                    }
                    if (reduce_only != 0)
                    {
                        content << ",\"reduce_only\":" << reduce_only;
                    }
                    if (lever_rate != 0)
                    {
                        content << ",\"lever_rate\":" << lever_rate;
                    }
                    if (volume != 0.0)
                    {
                        content << ",\"volume\":" << volume;
                    }
                    if (callback_rate != 0.0)
                    {
                        content << ",\"callback_rate\":" << callback_rate;
                    }
                    if (active_price != 0.0)
                    {
                        content << ",\"active_price\":" << active_price;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTrackOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTrackOrderResponse> SwapCrossTrackOrder(const string &contract_code, const string &pair,
                                                                       const string &contract_type, const string &direction,
                                                                       const string &offset,const string &order_price_type,
                                                                       int reduce_only, int lever_rate, float volume, float callback_rate,
                                                                       float active_price)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_track_order";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
                    }
                    if (direction != "")
                    {
                        content << ",\"direction\":\"" << direction << "\"";
                    }
                    if (offset != "")
                    {
                        content << ",\"offset\":\"" << offset << "\"";
                    }
                    if (order_price_type != "")
                    {
                        content << ",\"order_price_type\":\"" << order_price_type << "\"";
                    }
                    if (reduce_only != 0)
                    {
                        content << ",\"reduce_only\":" << reduce_only;
                    }
                    if (lever_rate != 0)
                    {
                        content << ",\"lever_rate\":" << lever_rate;
                    }
                    if (volume != 0.0)
                    {
                        content << ",\"volume\":" << volume;
                    }
                    if (callback_rate != 0.0)
                    {
                        content << ",\"callback_rate\":" << callback_rate;
                    }
                    if (active_price != 0.0)
                    {
                        content << ",\"active_price\":" << active_price;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTrackOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTrackCancelResponse> SwapTrackCancel(const string &contract_code, const string &order_id)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_track_cancel";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (order_id != "")
                    {
                        content << ",\"order_id\":\"" << order_id << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTrackCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTrackCancelResponse> SwapCrossTrackCancel(const string &contract_code, const string &pair,
                                                                                   const string &contract_type, const string &order_id)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_track_cancel";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
                    }
                    if (order_id != "")
                    {
                        content << ",\"order_id\":\"" << order_id << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTrackCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTrackCancelResponse> SwapTrackCancelAll(const string &contract_code, const string &direction,
                                                                              const string &offset)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_track_cancelall";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (direction != "")
                    {
                        content << ",\"direction\":\"" << direction << "\"";
                    }
                    if (offset != "")
                    {
                        content << ",\"offset\":\"" << offset << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTrackCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTrackCancelResponse> SwapCrossTrackCancelAll(const string &contract_code, const string &pair,
                                                                            const string &contract_type, const string &direction, const string &offset)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_track_cancelall";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
                    }
                    if (direction != "")
                    {
                        content << ",\"direction\":\"" << direction << "\"";
                    }
                    if (offset != "")
                    {
                        content << ",\"offset\":\"" << offset << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTrackCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTrackOpenOrdersResponse> SwapTrackOpenOrders(const string &contract_code, int trade_type, int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_track_openorders";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (page_index != 0)
                    {
                        content << ",\"page_index\":" << page_index;
                    }
                    if (page_size != 0)
                    {
                        content << ",\"page_size\":" << page_size;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTrackOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTrackOpenOrdersResponse> SwapTrackOpenOrders(const string &contract_code, int trade_type, int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_track_openorders";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (page_index != 0)
                    {
                        content << ",\"page_index\":" << page_index;
                    }
                    if (page_size != 0)
                    {
                        content << ",\"page_size\":" << page_size;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTrackOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTrackOpenOrdersResponse> SwapCrossTrackOpenOrders(const string &contract_code, const string &pair, int trade_type, int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_track_openorders";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (page_index != 0)
                    {
                        content << ",\"page_index\":" << page_index;
                    }
                    if (page_size != 0)
                    {
                        content << ",\"page_size\":" << page_size;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTrackOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTrackHisOrdersResponse> SwapTrackHisOrders(const string &contract_code, const string &status,
                                                                               const string &sort_by,
                                                                               int trade_type, int page_index, int page_size, long create_date)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_track_hisorders";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (status != "")
                    {
                        content << ",\"status\":\"" << status << "\"";
                    }
                    if (sort_by != "")
                    {
                        content << ",\"sort_by\":\"" << sort_by << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (page_index != 0)
                    {
                        content << ",\"page_index\":" << page_index;
                    }
                    if (page_size != 0)
                    {
                        content << ",\"page_size\":" << page_size;
                    }
                    if (create_date != 0)
                    {
                        content << ",\"create_date\":" << create_date;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTrackHisOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTrackHisOrdersResponse> SwapCrossTrackHisOrders(const string &contract_code, const string &pair, const string &status,
                                                                               const string &sort_by,
                                                                               int trade_type, int page_index, int page_size, long create_date)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_track_hisorders";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (status != "")
                    {
                        content << ",\"status\":\"" << status << "\"";
                    }
                    if (sort_by != "")
                    {
                        content << ",\"sort_by\":\"" << sort_by << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (page_index != 0)
                    {
                        content << ",\"page_index\":" << page_index;
                    }
                    if (page_size != 0)
                    {
                        content << ",\"page_size\":" << page_size;
                    }
                    if (create_date != 0)
                    {
                        content << ",\"create_date\":" << create_date;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTrackHisOrdersResponse>(url, data.str());
                    return result;
                }
            private:
                std::shared_ptr<url_base::PrivateUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures
