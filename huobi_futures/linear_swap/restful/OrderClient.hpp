#pragma once

#include <future>
#include <sstream>
#include <vector>

#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/linear_swap/restful/request/order/PlaceOrderRequest.hpp"
typedef huobi_futures::linear_swap::restful::request_order::PlaceOrderRequest PlaceOrderRequest;

#include "huobi_futures/linear_swap/restful/response/order/PlaceOrderResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::PlaceOrderResponse PlaceOrderResponse;

#include "huobi_futures/linear_swap/restful/response/order/BatchOrderResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::BatchOrderResponse BatchOrderResponse;

#include "huobi_futures/linear_swap/restful/response/order/CancelOrderResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::CancelOrderResponse CancelOrderResponse;

#include "huobi_futures/linear_swap/restful/response/order/GetOrderInfoResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::GetOrderInfoResponse GetOrderInfoResponse;

#include "huobi_futures/linear_swap/restful/response/order/GetOrderDetailResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::GetOrderDetailResponse GetOrderDetailResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwitchLeverRateResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwitchLeverRateResponse SwitchLeverRateResponse;

#include "huobi_futures/linear_swap/restful/response/order/GetOpenOrderResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::GetOpenOrderResponse GetOpenOrderResponse;

#include "huobi_futures/linear_swap/restful/response/order/GetHisordersResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::GetHisordersResponse GetHisordersResponse;

#include "huobi_futures/linear_swap/restful/response/order/GetHisordersExactResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::GetHisordersExactResponse GetHisordersExactResponse;

#include "huobi_futures/linear_swap/restful/response/order/GetMatchResultsResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::GetMatchResultsResponse GetMatchResultsResponse;

#include "huobi_futures/linear_swap/restful/response/order/GetMatchResultsExactResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::GetMatchResultsExactResponse GetMatchResultsExactResponse;

#include "huobi_futures/linear_swap/restful/response/order/LinearCancelAfterResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::LinearCancelAfterResponse LinearCancelAfterResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapCrossHisordersExactResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapCrossHisordersExactResponse SwapCrossHisordersExactResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapCrossHisordersResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapCrossHisordersResponse SwapCrossHisordersResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapCrossSwitchPositionModeResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapCrossSwitchPositionModeResponse SwapCrossSwitchPositionModeResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapHisordersExactResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapHisordersExactResponse SwapHisordersExactResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapHisordersResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapHisordersResponse SwapHisordersResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapMatchResultsResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapMatchResultsResponse SwapMatchResultsResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapPositionSideResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapPositionSideResponse SwapPositionSideResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapSwitchPositionModeResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapSwitchPositionModeResponse SwapSwitchPositionModeResponse;

#include "huobi_futures/linear_swap/restful/response/order/PositionLeverResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::PositionLeverResponse PositionLeverResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapPositionLeverResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapPositionLeverResponse SwapPositionLeverResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapPositionModeResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapPositionModeResponse SwapPositionModeResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapPositionRiskLimitResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapPositionRiskLimitResponse SwapPositionRiskLimitResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapTradeOrderHistoryResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapTradeOrderHistoryResponse SwapTradeOrderHistoryResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapTradeOrderOpensResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapTradeOrderOpensResponse SwapTradeOrderOpensResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapTradeOrderResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapTradeOrderResponse SwapTradeOrderResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapTradeOrderTradesResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapTradeOrderTradesResponse SwapTradeOrderTradesResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapTradePositionHistoryResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapTradePositionHistoryResponse SwapTradePositionHistoryResponse;

#include "huobi_futures/linear_swap/restful/response/order/SwapTradePositionOpensResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_order::SwapTradePositionOpensResponse SwapTradePositionOpensResponse;

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            class OrderClient
            {

            public:
                OrderClient(const string &access_key, const string &secret_key, const string &host = utils::DEFAULT_HOST)
                {
                    pb = std::make_shared<url_base::PrivateUrlBuilder>(access_key, secret_key, host);
                }

                std::shared_ptr<PlaceOrderResponse> IsolatedPlaceOrder(const PlaceOrderRequest &request)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_order";

                    // option
                    string data = request.to_json();

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<PlaceOrderResponse>(url, data);
                    return result;
                }

                std::shared_ptr<PlaceOrderResponse> CrossPlaceOrder(const PlaceOrderRequest &request)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_order";

                    // option
                    string data = request.to_json();

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<PlaceOrderResponse>(url, data);
                    return result;
                }

                std::shared_ptr<BatchOrderResponse> IsolatedBatchOrder(const std::vector<PlaceOrderRequest> &request)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_batchorder";

                    // option
                    stringstream ssdata;
                    for (auto item : request)
                    {
                        ssdata << "," << item.to_json();
                    }
                    string data = ssdata.str();
                    if (!data.empty())
                    {
                        data = "{\"orders_data\":[" + data.substr(1) + "]}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<BatchOrderResponse>(url, data);
                    return result;
                }

                std::shared_ptr<BatchOrderResponse> CrossBatchOrder(const std::vector<PlaceOrderRequest> &request)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_batchorder";

                    // option
                    stringstream ssdata;
                    for (auto item : request)
                    {
                        ssdata << "," << item.to_json();
                    }
                    string data = ssdata.str();
                    if (!data.empty())
                    {
                        data = "{\"orders_data\":[" + data.substr(1) + "]}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<BatchOrderResponse>(url, data);
                    return result;
                }

                std::shared_ptr<CancelOrderResponse> IsolatedCancelOrder(const string &contract_code, const string &order_id = "",
                                                                         const string &client_order_id = "", const string &direction = "",
                                                                         const string &offset = "")
                {
                    // path
                    stringstream path;
                    if (order_id.empty() && client_order_id.empty())
                    {
                        path << "/linear-swap-api/v1/swap_cancelall";
                    }
                    else
                    {
                        path << "/linear-swap-api/v1/swap_cancel";
                    }

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\"";
                    if (order_id != "")
                    {
                        content << ",\"order_id\":\"" << order_id << "\"";
                    }
                    if (client_order_id != "")
                    {
                        content << ",\"client_order_id\":\"" << client_order_id << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<CancelOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<CancelOrderResponse> CrossCancelOrder(const string &contract_code, const string &order_id = "",
                                                                      const string &client_order_id = "", const string &direction = "",
                                                                      const string &offset = "", const string &pair = "",
                                                                      const string &contract_type = "")
                {
                    // path
                    stringstream path;
                    if (order_id.empty() && client_order_id.empty())
                    {
                        path << "/linear-swap-api/v1/swap_cross_cancelall";
                    }
                    else
                    {
                        path << "/linear-swap-api/v1/swap_cross_cancel";
                    }

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\"";
                    if (order_id != "")
                    {
                        content << ",\"order_id\":\"" << order_id << "\"";
                    }
                    if (client_order_id != "")
                    {
                        content << ",\"client_order_id\":\"" << client_order_id << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<CancelOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwitchLeverRateResponse> IsolatedSwitchLeverRate(const string &contract_code, int lever_rate)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_switch_lever_rate";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"lever_rate\":" << lever_rate;

                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<SwitchLeverRateResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwitchLeverRateResponse> CrossSwitchLeverRate(const string &contract_code, int lever_rate,
                                                                              const string &pair = "",
                                                                              const string &contract_type = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_switch_lever_rate";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"lever_rate\":" << lever_rate;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwitchLeverRateResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetOrderInfoResponse> IsolatedGetOrderInfo(const string &contract_code, const string &order_id = "",
                                                                           const string &client_order_id = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_order_info";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\"";
                    if (order_id != "")
                    {
                        content << ",\"order_id\":\"" << order_id << "\"";
                    }
                    if (client_order_id != "")
                    {
                        content << ",\"client_order_id\":\"" << client_order_id << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetOrderInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetOrderInfoResponse> CrossGetOrderInfo(const string &contract_code, const string &order_id = "",
                                                                        const string &client_order_id = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_order_info";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\"";
                    if (order_id != "")
                    {
                        content << ",\"order_id\":\"" << order_id << "\"";
                    }
                    if (client_order_id != "")
                    {
                        content << ",\"client_order_id\":\"" << client_order_id << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetOrderInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetOrderDetailResponse> IsolatedGetOrderDetail(const string &contract_code, const string &order_id, long created_at = 0,
                                                                               int order_type = 0, int page_index = 0, int page_size = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_order_detail";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\",\"order_id\":\"" << order_id << "\"";
                    if (created_at != 0)
                    {
                        content << ",\"created_at\":" << created_at;
                    }
                    if (order_type != 0)
                    {
                        content << ",\"order_type\":" << order_type;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetOrderDetailResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetOrderDetailResponse> CrossGetOrderDetail(const string &contract_code, const string &order_id, long created_at = 0,
                                                                            int order_type = 0, int page_index = 0, int page_size = 0, const string &pair = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_order_detail";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\",\"order_id\":\"" << order_id << "\"";
                    if (created_at != 0)
                    {
                        content << ",\"created_at\":" << created_at;
                    }
                    if (order_type != 0)
                    {
                        content << ",\"order_type\":" << order_type;
                    }
                    if (page_index != 0)
                    {
                        content << ",\"page_index\":" << page_index;
                    }
                    if (page_size != 0)
                    {
                        content << ",\"page_size\":" << page_size;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetOrderDetailResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetOpenOrderResponse> IsolatedGetOpenOrder(const string &contract_code, int page_index = 0, int page_size = 0,
                                                                           const string &sort_by = "", int trade_type = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_openorders";

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
                    if (sort_by != "")
                    {
                        content << ",\"sort_by\":\"" << sort_by << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetOpenOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetOpenOrderResponse> CrossGetOpenOrder(const string &contract_code, int page_index = 0, int page_size = 0,
                                                                        const string &sort_by = "", int trade_type = 0, const string &pair = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_openorders";

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
                    if (sort_by != "")
                    {
                        content << ",\"sort_by\":\"" << sort_by << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetOpenOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetHisordersResponse> IsolatedGetHisorders(const string &contract_code, int trade_type, int type, const string &status,
                                                                           int create_date, int page_index = 0, int page_size = 0, const string &sort_by = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_hisorders";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"trade_type\":" << trade_type
                            << ",\"type\":" << type
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
                    auto result = url_base::HttpRequest::Instance().Post<GetHisordersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetHisordersResponse> CrossGetHisorders(const string &contract_code, int trade_type, int type, const string &status,
                                                                        int create_date, int page_index = 0, int page_size = 0, const string &sort_by = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_hisorders";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"trade_type\":" << trade_type
                            << ",\"type\":" << type
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
                    auto result = url_base::HttpRequest::Instance().Post<GetHisordersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetHisordersExactResponse> IsolatedGetHisordersExact(const string &contract_code, int trade_type, int type, const string &status,
                                                                                     const string &order_price_type = "", long start_time = 0, long end_time = 0,
                                                                                     long from_id = 0, int size = 0, const string &direct = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_hisorders_exact";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"trade_type\":" << trade_type
                            << ",\"type\":" << type
                            << ",\"status\":\"" << status << "\"";
                    if (order_price_type != "")
                    {
                        content << ",\"order_price_type\":\"" << order_price_type << "\"";
                    }
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
                    }
                    if (from_id != 0)
                    {
                        content << ",\"from_id\":" << from_id;
                    }
                    if (size != 0)
                    {
                        content << ",\"size\":" << size;
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetHisordersExactResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetHisordersExactResponse> CrossGetHisordersExact(const string &contract_code, int trade_type, int type, const string &status,
                                                                                  const string &order_price_type = "", long start_time = 0, long end_time = 0,
                                                                                  long from_id = 0, int size = 0, const string &direct = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_hisorders_exact";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"trade_type\":" << trade_type
                            << ",\"type\":" << type
                            << ",\"status\":\"" << status << "\"";
                    if (order_price_type != "")
                    {
                        content << ",\"order_price_type\":\"" << order_price_type << "\"";
                    }
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
                    }
                    if (from_id != 0)
                    {
                        content << ",\"from_id\":" << from_id;
                    }
                    if (size != 0)
                    {
                        content << ",\"size\":" << size;
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetHisordersExactResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetMatchResultsResponse> IsolatedGetMatchResults(const string &contract_code, int trade_type, int create_date,
                                                                                 int page_index = 0, int page_size = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_matchresults";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"trade_type\":" << trade_type
                            << ",\"create_date\":" << create_date;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetMatchResultsResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetMatchResultsResponse> CrossGetMatchResults(const string &contract_code, int trade_type, int create_date,
                                                                              int page_index = 0, int page_size = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_matchresults";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"trade_type\":" << trade_type
                            << ",\"create_date\":" << create_date;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetMatchResultsResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetMatchResultsExactResponse> IsolatedGetMatchResultsExact(const string &contract_code, int trade_type,
                                                                                           long start_time = 0, long end_time = 0, long from_id = 0,
                                                                                           int size = 0, const string &direct = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_matchresults_exact";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"trade_type\":" << trade_type;
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
                    }
                    if (from_id != 0)
                    {
                        content << ",\"from_id\":" << from_id;
                    }
                    if (size != 0)
                    {
                        content << ",\"size\":" << size;
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetMatchResultsExactResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetMatchResultsExactResponse> CrossGetMatchResultsExact(const string &contract_code, int trade_type,
                                                                                        long start_time = 0, long end_time = 0, long from_id = 0,
                                                                                        int size = 0, const string &direct = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_matchresults_exact";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"trade_type\":" << trade_type;
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
                    }
                    if (from_id != 0)
                    {
                        content << ",\"from_id\":" << from_id;
                    }
                    if (size != 0)
                    {
                        content << ",\"size\":" << size;
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetMatchResultsExactResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<PlaceOrderResponse> IsolatedLightningClosePosition(const string &contract_code, long volume, const string &direction,
                                                                                   long client_order_id = 0, const string &order_price_type = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_lightning_close_position";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"volume\":" << volume
                            << ",\"direction\":\"" << direction << "\"";
                    if (client_order_id != 0)
                    {
                        content << ",\"client_order_id\":" << client_order_id;
                    }
                    if (order_price_type != "")
                    {
                        content << ",\"order_price_type\":\"" << order_price_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<PlaceOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<PlaceOrderResponse> CrossLightningClosePosition(const string &contract_code, long volume, const string &direction,
                                                                                long client_order_id = 0, const string &order_price_type = "", const string &pair = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_lightning_close_position";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"volume\":" << volume
                            << ",\"direction\":\"" << direction << "\"";
                    if (client_order_id != 0)
                    {
                        content << ",\"client_order_id\":" << client_order_id;
                    }
                    if (order_price_type != "")
                    {
                        content << ",\"order_price_type\":\"" << order_price_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<PlaceOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<LinearCancelAfterResponse> LinearCancelAfter(int on_off, int time_out)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/linear-cancel-after";

                    // option
                    stringstream content;
                    if (on_off != 0)
                    {
                        content << ",\"on_off\":" << on_off;
                    }
                    if (time_out != 0)
                    {
                        content << ",\"time_out\":" << time_out;
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
                    auto result = url_base::HttpRequest::Instance().Post<LinearCancelAfterResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapSwitchPositionModeResponse> SwapSwitchPositionMode(const string &margin_account, const string &position_mode)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_switch_position_mode";

                    // option
                    stringstream content;
                    if (margin_account != "")
                    {
                        content << ",\"margin_account\":\"" << margin_account << "\"";
                    }
                    if (position_mode != "")
                    {
                        content << ",\"position_mode\":\"" << position_mode << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapSwitchPositionModeResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapCrossSwitchPositionModeResponse> SwapCrossSwitchPositionMode(const string &margin_account, const string &position_mode)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_switch_position_mode";

                    // option
                    stringstream content;
                    if (margin_account != "")
                    {
                        content << ",\"margin_account\":\"" << margin_account << "\"";
                    }
                    if (position_mode != "")
                    {
                        content << ",\"position_mode\":\"" << position_mode << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapCrossSwitchPositionModeResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapHisordersResponse> SwapHisorders(const string &contract, const string &direct,
                                                                     const string &status, int trade_type, long start_time,
                                                                     long end_time, long from_id, int type)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/swap_hisorders";

                    // option
                    stringstream content;
                    if (contract != "")
                    {
                        content << ",\"contract\":\"" << contract << "\"";
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
                    }
                    if (status != "")
                    {
                        content << ",\"status\":\"" << status << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
                    }
                    if (from_id != 0)
                    {
                        content << ",\"from_id\":" << from_id;
                    }
                    if (type != 0)
                    {
                        content << ",\"type\":" << type;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapHisordersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapCrossHisordersResponse> SwapCrossHisorders(const string &contract, const string &pair,
                                                                     const string &direct, const string &status, int trade_type, long start_time,
                                                                     long end_time, long from_id, int type)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/swap_cross_hisorders";

                    // option
                    stringstream content;
                    if (contract != "")
                    {
                        content << ",\"contract\":\"" << contract << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
                    }
                    if (status != "")
                    {
                        content << ",\"status\":\"" << status << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
                    }
                    if (from_id != 0)
                    {
                        content << ",\"from_id\":" << from_id;
                    }
                    if (type != 0)
                    {
                        content << ",\"type\":" << type;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapCrossHisordersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapHisordersExactResponse> SwapHisordersExact(const string &contract, const string &pair,
                                                                               const string &direct, const string &status,const string &price_type,
                                                                               int trade_type, long start_time,
                                                                               long end_time, long from_id, int type)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/swap_hisorders_exact";

                    // option
                    stringstream content;
                    if (contract != "")
                    {
                        content << ",\"contract\":\"" << contract << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
                    }
                    if (status != "")
                    {
                        content << ",\"status\":\"" << status << "\"";
                    }
                    if (price_type != "")
                    {
                        content << ",\"price_type\":\"" << price_type << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
                    }
                    if (from_id != 0)
                    {
                        content << ",\"from_id\":" << from_id;
                    }
                    if (type != 0)
                    {
                        content << ",\"type\":" << type;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapHisordersExactResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapCrossHisordersExactResponse> SwapCrossHisordersExact(const string &contract, const string &pair,
                                                                               const string &direct, const string &status,const string &price_type,
                                                                               int trade_type, long start_time,
                                                                               long end_time, long from_id, int type)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/swap_cross_hisorders_exact";

                    // option
                    stringstream content;
                    if (contract != "")
                    {
                        content << ",\"contract\":\"" << contract << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
                    }
                    if (status != "")
                    {
                        content << ",\"status\":\"" << status << "\"";
                    }
                    if (price_type != "")
                    {
                        content << ",\"price_type\":\"" << price_type << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
                    }
                    if (from_id != 0)
                    {
                        content << ",\"from_id\":" << from_id;
                    }
                    if (type != 0)
                    {
                        content << ",\"type\":" << type;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapCrossHisordersExactResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapMatchResultsResponse> SwapMatchResults(const string &contract, const string &pair,
                                                                                         const string &direct,
                                                                                         int trade_type, long start_time,
                                                                                         long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/swap_matchresults";

                    // option
                    stringstream content;
                    if (contract != "")
                    {
                        content << ",\"contract\":\"" << contract << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
                    }
                    if (from_id != 0)
                    {
                        content << ",\"from_id\":" << from_id;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapMatchResultsResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapMatchResultsResponse> SwapCrossMatchResults(const string &contract, const string &pair,
                                                                           const string &direct,
                                                                           int trade_type, long start_time,
                                                                           long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/swap_cross_matchresults";

                    // option
                    stringstream content;
                    if (contract != "")
                    {
                        content << ",\"contract\":\"" << contract << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
                    }
                    if (from_id != 0)
                    {
                        content << ",\"from_id\":" << from_id;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapMatchResultsResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapMatchResultsResponse> SwapMatchResultsExact(const string &contract,
                                                                                const string &direct,
                                                                                int trade_type, long start_time,
                                                                                long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/swap_matchresults_exact";

                    // option
                    stringstream content;
                    if (contract != "")
                    {
                        content << ",\"contract\":\"" << contract << "\"";
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
                    }
                    if (from_id != 0)
                    {
                        content << ",\"from_id\":" << from_id;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapMatchResultsResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapMatchResultsResponse> SwapCrossMatchResultsExact(const string &contract,const string &pair,
                                                                                const string &direct,
                                                                                int trade_type, long start_time,
                                                                                long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/swap_cross_matchresults_exact";

                    // option
                    stringstream content;
                    if (contract != "")
                    {
                        content << ",\"contract\":\"" << contract << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
                    }
                    if (from_id != 0)
                    {
                        content << ",\"from_id\":" << from_id;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapMatchResultsResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapMatchResultsResponse> SwapCrossMatchResultsExact(const string &contract,const string &pair,
                                                                                     const string &direct,
                                                                                     int trade_type, long start_time,
                                                                                     long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/swap_cross_matchresults_exact";

                    // option
                    stringstream content;
                    if (contract != "")
                    {
                        content << ",\"contract\":\"" << contract << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
                    }
                    if (from_id != 0)
                    {
                        content << ",\"from_id\":" << from_id;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapMatchResultsResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapPositionSideResponse> SwapPositionSide(const string &margin_account)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_position_side";
                    // option
                    stringstream option;
                    if (margin_account != "") {
                        option << "&margin_account=" << margin_account;
                    }
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<SwapPositionSideResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapPositionSideResponse> SwapCrossPositionSide(const string &margin_account)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_position_side";
                    // option
                    stringstream option;
                    if (margin_account != "") {
                        option << "&margin_account=" << margin_account;
                    }
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<SwapPositionSideResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapTradeOrderResponse> SwapTradeOrder(string contract_code, string position_side,
                                                                       string side, string type, string price_match,
                                                                       string client_order_id, string price, string volume,
                                                                       int reduce_only, string time_in_force, string tp_trigger_price,
                                                                       string tp_order_price, string tp_type,
                                                                       string tp_trigger_price_type, string sl_trigger_price,
                                                                       string sl_order_price, string sl_type, string sl_trigger_price_type,
                                                                       bool price_protect, bool trigger_protect)
                {
                    // path
                    stringstream path;
                    path << "/v5/trade/order";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (position_side != "")
                    {
                        content << ",\"position_side\":\"" << position_side << "\"";
                    }
                    if (side != "")
                    {
                        content << ",\"side\":\"" << side << "\"";
                    }
                    if (type != "")
                    {
                        content << ",\"type\":\"" << type << "\"";
                    }
                    if (price_match != "")
                    {
                        content << ",\"price_match\":\"" << price_match << "\"";
                    }
                    if (client_order_id != "")
                    {
                        content << ",\"client_order_id\":\"" << client_order_id << "\"";
                    }
                    if (price != "")
                    {
                        content << ",\"price\":\"" << price << "\"";
                    }
                    if (volume != "")
                    {
                        content << ",\"volume\":\"" << volume << "\"";
                    }
                    if (time_in_force != "")
                    {
                        content << ",\"time_in_force\":\"" << time_in_force << "\"";
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
                    if (price_protect != "")
                    {
                        content << ",\"price_protect\":\"" << price_protect << "\"";
                    }
                    if (trigger_protect != "")
                    {
                        content << ",\"trigger_protect\":\"" << trigger_protect << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTradeOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTradeOrderResponse> SwapTradeBatchorder(string contract_code, string margin_mode,
                                                                       string position_side, string side, string type, string price_match,
                                                                       string client_order_id, string price, string volume,
                                                                       int reduce_only, string time_in_force, string tp_trigger_price,
                                                                       string tp_order_price, string tp_type,
                                                                       string tp_trigger_price_type, string sl_trigger_price,
                                                                       string sl_order_price, string sl_type, string sl_trigger_price_type,
                                                                       bool price_protect, bool trigger_protect)
                {
                    // path
                    stringstream path;
                    path << "/v5/trade/batch_orders";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (margin_mode != "")
                    {
                        content << ",\"margin_mode\":\"" << margin_mode << "\"";
                    }
                    if (position_side != "")
                    {
                        content << ",\"position_side\":\"" << position_side << "\"";
                    }
                    if (side != "")
                    {
                        content << ",\"side\":\"" << side << "\"";
                    }
                    if (type != "")
                    {
                        content << ",\"type\":\"" << type << "\"";
                    }
                    if (price_match != "")
                    {
                        content << ",\"price_match\":\"" << price_match << "\"";
                    }
                    if (client_order_id != "")
                    {
                        content << ",\"client_order_id\":\"" << client_order_id << "\"";
                    }
                    if (price != "")
                    {
                        content << ",\"price\":\"" << price << "\"";
                    }
                    if (volume != "")
                    {
                        content << ",\"volume\":\"" << volume << "\"";
                    }
                    if (time_in_force != "")
                    {
                        content << ",\"time_in_force\":\"" << time_in_force << "\"";
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
                    if (price_protect != "")
                    {
                        content << ",\"price_protect\":\"" << price_protect << "\"";
                    }
                    if (trigger_protect != "")
                    {
                        content << ",\"trigger_protect\":\"" << trigger_protect << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTradeOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTradeOrderResponse> SwapCannelTradeOrder(string contract_code, string order_id,
                                                                             string client_order_id)
                {
                    // path
                    stringstream path;
                    path << "/v5/trade/cancel_order";

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
                    if (client_order_id != "")
                    {
                        content << ",\"client_order_id\":\"" << client_order_id << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTradeOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTradeOrderResponse> SwapCannelBatchTradeOrder(string contract_code, string order_id,
                                                                             string client_order_id)
                {
                    // path
                    stringstream path;
                    path << "/v5/trade/cancel_batch_orders";

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
                    if (client_order_id != "")
                    {
                        content << ",\"client_order_id\":\"" << client_order_id << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTradeOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTradeOrderResponse> SwapCannelAllOrders(string contract_code, string side,
                                                                             string position_side)
                {
                    // path
                    stringstream path;
                    path << "/v5/trade/cancel_all_orders";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (side != "")
                    {
                        content << ",\"side\":\"" << side << "\"";
                    }
                    if (position_side != "")
                    {
                        content << ",\"position_side\":\"" << position_side << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTradeOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTradeOrderResponse> SwapTradePosition(string contract_code, string margin_mode,
                                                                             string position_side, string client_order_id)
                {
                    // path
                    stringstream path;
                    path << "/v5/trade/position";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (margin_mode != "")
                    {
                        content << ",\"margin_mode\":\"" << margin_mode << "\"";
                    }
                    if (position_side != "")
                    {
                        content << ",\"position_side\":\"" << position_side << "\"";
                    }
                    if (client_order_id != "")
                    {
                        content << ",\"client_order_id\":\"" << client_order_id << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTradeOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTradeOrderResponse> SwapTradePositionAll()
                {
                    // path
                    stringstream path;
                    path << "/v5/trade/position_all";

                    // option
                    stringstream content;

                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<SwapTradeOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTradeOrderOpensResponse> SwapTradeOrderOpens(string contract_code, string margin_mode,
                                                                              string order_id, string client_order_id, long from,
                                                                              int limit, string direct)
                {
                    // path
                    stringstream path;
                    path << "/v5/trade/order/opens";
                    // option
                    stringstream option;
                    if (contract_code != "") {
                        option << "&contract_code=" << contract_code;
                    }
                    if (margin_mode != "") {
                        option << "&margin_mode=" << margin_mode;
                    }
                    if (order_id != "") {
                        option << "&order_id=" << order_id;
                    }
                    if (client_order_id != "") {
                        option << "&client_order_id=" << client_order_id;
                    }
                    if (from != 0) {
                        option << "&from=" << from;
                    }
                    if (limit != 0) {
                        option << "&limit=" << limit;
                    }
                    if (direct != "") {
                        option << "&direct=" << direct;
                    }
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<SwapTradeOrderOpensResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapTradeOrderTradesResponse> SwapTradeOrderTrades(string contract_code, string order_id,
                                                                                   string client_order_id, string start_time,
                                                                                   string end_time, long from, int limit,
                                                                                   string direct)
                {
                    // path
                    stringstream path;
                    path << "/api/v5 /trade/order/trades";
                    // option
                    stringstream option;
                    if (contract_code != "") {
                        option << "&contract_code=" << contract_code;
                    }
                    if (order_id != "") {
                        option << "&order_id=" << order_id;
                    }
                    if (client_order_id != "") {
                        option << "&client_order_id=" << client_order_id;
                    }
                    if (start_time != "") {
                        option << "&start_time=" << start_time;
                    }
                    if (end_time != "") {
                        option << "&end_time=" << end_time;
                    }
                    if (from != 0) {
                        option << "&from=" << from;
                    }
                    if (limit != 0) {
                        option << "&limit=" << limit;
                    }
                    if (direct != "") {
                        option << "&direct=" << direct;
                    }
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<SwapTradeOrderTradesResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapTradeOrderHistoryResponse> SwapTradeOrderHistory(string contract_code,
                                                                                     string state, string type, string price_match,
                                                                                     string start_time, string end_time,
                                                                                     long from, int limit, string direct, string business_type, string margin_mode)
                {
                    // path
                    stringstream path;
                    path << "/api/v5/trade/order/history";
                    // option
                    stringstream option;
                    if (contract_code != "") {
                        option << "&contract_code=" << contract_code;
                    }
                    if (order_id != "") {
                        option << "&order_id=" << order_id;
                    }
                    if (state != "") {
                        option << "&state=" << state;
                    }
                    if (type != "") {
                        option << "&type=" << type;
                    }
                    if (price_match != "") {
                        option << "&price_match=" << price_match;
                    }
                    if (start_time != "") {
                        option << "&start_time=" << start_time;
                    }
                    if (time_in_force != "") {
                        option << "&time_in_force=" << time_in_force;
                    }
                    if (end_time != "") {
                        option << "&end_time=" << end_time;
                    }
                    if (margin_mode != "") {
                        option << "&margin_mode=" << margin_mode;
                    }
                    if (from != 0) {
                        option << "&from=" << from;
                    }
                    if (limit != 0) {
                        option << "&limit=" << limit;
                    }
                    if (direct != "") {
                        option << "&direct=" << direct;
                    }
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<SwapTradeOrderHistoryResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapTradePositionOpensResponse> SwapTradePositionOpens(string contract_code)
                {
                    // path
                    stringstream path;
                    path << "/v5/trade/position/opens";
                    // option
                    stringstream option;
                    if (contract_code != "") {
                        option << "&contract_code=" << contract_code;
                    }

                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<SwapTradePositionOpensResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapTradePositionHistoryResponse> SwapTradePositionHistory(string contract_code, string contract_type,
                                                                                           string margin_mode, string start_time,
                                                                                           string end_time, long from, int limit,
                                                                                           string direct)
                {
                    // path
                    stringstream path;
                    path << "/v5/trade/position/history";
                    // option
                    stringstream option;
                    if (contract_code != "") {
                        option << "&contract_code=" << contract_code;
                    }
                    if (contract_type != "") {
                        option << "&contract_type=" << contract_type;
                    }
                    if (margin_mode != "") {
                        option << "&margin_mode=" << margin_mode;
                    }
                    if (start_time != "") {
                        option << "&start_time=" << start_time;
                    }
                    if (end_time != "") {
                        option << "&end_time=" << end_time;
                    }
                    if (from != 0) {
                        option << "&from=" << from;
                    }
                    if (limit != 0) {
                        option << "&limit=" << limit;
                    }
                    if (direct != "") {
                        option << "&direct=" << direct;
                    }

                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<SwapTradePositionHistoryResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapPositionLeverResponse> SwapPositionLever(string contract_code, string margin_mode)
                {
                    // path
                    stringstream path;
                    path << "/v5/position/lever";
                    // option
                    stringstream option;
                    if (contract_code != "") {
                        option << "&contract_code=" << contract_code;
                    }
                    if (margin_mode != "") {
                        option << "&margin_mode=" << margin_mode;
                    }

                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<SwapPositionLeverResponse>(url);
                    return result;
                }

                std::shared_ptr<PositionLeverResponse> CrossCancelOrder(string contract_code, string margin_mode, string lever_rate)
                {
                    // path
                    stringstream path;
                    path << "/v5/position/lever";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (margin_mode != "")
                    {
                        content << ",\"margin_mode\":\"" << margin_mode << "\"";
                    }
                    if (lever_rate != "")
                    {
                        content << ",\"lever_rate\":\"" << lever_rate << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<PositionLeverResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapPositionModeResponse> SwapPositionMode()
                {
                    // path
                    stringstream path;
                    path << "/api/v5/position/mode";
                    // option
                    stringstream option;

                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<SwapPositionModeResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapPositionModeResponse> SwapSetPositionMode(string position_mode)
                {
                    // path
                    stringstream path;
                    path << "/api/v5/position/mode";

                    // option
                    stringstream content;
                    if (position_mode != "")
                    {
                        content << ",\"position_mode\":\"" << position_mode << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapPositionModeResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapPositionRiskLimitResponse> SwapPositionRiskLimit(string contract_code, string margin_mode,
                                                                                     string position_side)
                {
                    // path
                    stringstream path;
                    path << "/v5/position/riskLimit";
                    // option
                    stringstream option;
                    if (contract_code != "") {
                        option << "&contract_code=" << contract_code;
                    }
                    if (margin_mode != "") {
                        option << "&margin_mode=" << margin_mode;
                    }
                    if (position_side != "") {
                        option << "&position_side=" << position_side;
                    }

                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<SwapPositionRiskLimitResponse>(url);
                    return result;
                }

                std::shared_ptr<GetTradeOrderResponse> GetTradeOrder(string contract_code,
                                                                     string margin_mode, string order_id, string client_order_id)
                {
                    // path
                    stringstream path;
                    path << "/api/v5/trade/order";
                    // option
                    stringstream option;
                    if (contract_code != "") {
                        option << "&contract_code=" << contract_code;
                    }
                    if (order_id != "") {
                        option << "&order_id=" << order_id;
                    }
                    if (client_order_id != "") {
                        option << "&client_order_id=" << client_order_id;
                    }
                    if (margin_mode != "") {
                        option << "&margin_mode=" << margin_mode;
                    }
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<GetTradeOrderResponse>(url);
                    return result;
                }


            private:
                std::shared_ptr<url_base::PrivateUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures
