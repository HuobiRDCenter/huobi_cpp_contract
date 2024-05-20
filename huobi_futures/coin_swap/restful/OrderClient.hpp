#pragma once

#include <future>
#include <sstream>
#include <vector>

#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/coin_swap/restful/request/order/PlaceOrderRequest.hpp"
typedef huobi_futures::coin_swap::restful::request_order::PlaceOrderRequest PlaceOrderRequest;

#include "huobi_futures/coin_swap/restful/response/order/SwapBatchOrderResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_order::SwapBatchOrderResponse SwapBatchOrderResponse;

#include "huobi_futures/coin_swap/restful/response/order/SwapCancelAfterResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_order::SwapCancelAfterResponse SwapCancelAfterResponse;

#include "huobi_futures/coin_swap/restful/response/order/SwapCancelResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_order::SwapCancelResponse SwapCancelResponse;

#include "huobi_futures/coin_swap/restful/response/order/SwapHisOrdersV3Response.hpp"
typedef huobi_futures::coin_swap::restful::response_order::SwapHisOrdersV3Response SwapHisOrdersV3Response;

#include "huobi_futures/coin_swap/restful/response/order/SwapLightningClosePositionResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_order::SwapLightningClosePositionResponse SwapLightningClosePositionResponse;

#include "huobi_futures/coin_swap/restful/response/order/SwapMatchResultsV3Response.hpp"
typedef huobi_futures::coin_swap::restful::response_order::SwapMatchResultsV3Response SwapMatchResultsV3Response;

#include "huobi_futures/coin_swap/restful/response/order/SwapOpenOrdersResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_order::SwapOpenOrdersResponse SwapOpenOrdersResponse;

#include "huobi_futures/coin_swap/restful/response/order/SwapOrderDetailResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_order::SwapOrderDetailResponse SwapOrderDetailResponse;

#include "huobi_futures/coin_swap/restful/response/order/SwapOrderInfoResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_order::SwapOrderInfoResponse SwapOrderInfoResponse;

#include "huobi_futures/coin_swap/restful/response/order/SwapOrderResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_order::SwapOrderResponse SwapOrderResponse;

#include "huobi_futures/coin_swap/restful/response/order/SwapSwitchLeverRateResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_order::SwapSwitchLeverRateResponse SwapSwitchLeverRateResponse;

namespace huobi_futures
{
    namespace coin_swap
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

                std::shared_ptr<SwapCancelAfterResponse> SwapCancelAfter(int on_off, int time_out)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap-cancel-after";

                    // option
                    stringstream content;
                    if (on_off != 0)
                    {
                        content << ",\"on_off\":" << on_off;
                    }
                    if (time_out != 0)
                    {
                        time_out << ",\"time_out\":" << time_out;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapCancelAfterResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapOrderResponse> SwapOrder(const PlaceOrderRequest &request)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_order";

                    // option
                    string data = request.to_json();

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<SwapOrderResponse>(url, data);
                    return result;
                }

                std::shared_ptr<SwapBatchOrderResponse> SwapBatchOrder(const std::vector<PlaceOrderRequest> &request)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_batchorder";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapBatchOrderResponse>(url, data);
                    return result;
                }

                std::shared_ptr<SwapCancelResponse> SwapCancel(const string &order_id, const string &client_order_id, const string &contract_code)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_cancel";

                    // option
                    stringstream content;
                    if (order_id != "")
                    {
                        content << ",\"order_id\":\"" << order_id << "\"";
                    }
                    if (client_order_id != "")
                    {
                        time_out << ",\"client_order_id\":\"" << client_order_id << "\"";
                    }
                    if (contract_code != "")
                    {
                        time_out << ",\"contract_code\":\"" << contract_code << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapCancelResponse> SwapCancelAll(const string &contract_code,
                                                                     const string &direction,
                                                                     const string &offset)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_cancelall";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        time_out << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (direction != "")
                    {
                        time_out << ",\"direction\":\"" << direction << "\"";
                    }
                    if (offset != "")
                    {
                        time_out << ",\"offset\":\"" << offset << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapSwitchLeverRateResponse> SwapSwitchLeverRate(const string &contract_code, int lever_rate)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_switch_lever_rate";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (lever_rate != 0)
                    {
                        time_out << ",\"lever_rate\":" << lever_rate;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapSwitchLeverRateResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapOrderInfoResponse> SwapOrderInfo(const string &order_id, const string &client_order_id,const string &contract_code)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_order_info";

                    // option
                    stringstream content;
                    if (order_id != "")
                    {
                        content << ",\"order_id\":\"" << order_id << "\"";
                    }
                    if (client_order_id != "")
                    {
                        content << ",\"client_order_id\":\"" << client_order_id << "\"";
                    }
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapOrderInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapOrderDetailResponse> SwapOrderDetail(const string &contract_code, long order_id,
                                                                                 long created_at, int order_type,
                                                                                 int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_order_detail";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (order_id != 0)
                    {
                        content << ",\"order_id\":" << order_id;
                    }
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapOrderDetailResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapOpenOrdersResponse> SwapOpenOrders(const string &contract_code, const string &sort_by,
                                                                                 long page_index, int page_size,
                                                                                 int trade_type)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_openorders";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (sort_by != "")
                    {
                        content << ",\"sort_by\":\"" << sort_by << "\"";
                    }
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
                        content << ",\"trade_type\":" << trade_type ;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapHisOrdersV3Response> SwapHisOrders(const string &contract, const string &status,
                                                                     const string &direct, int trade_type, int type,
                                                                     long start_time, long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v3/swap_hisorders";

                    // option
                    stringstream content;
                    if (contract != "")
                    {
                        content << ",\"contract\":\"" << contract << "\"";
                    }
                    if (status != "")
                    {
                        content << ",\"status\":\"" << status << "\"";
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
                    }
                    if (trade_type != 0)
                    {
                        content << ",\"trade_type\":" << trade_type;
                    }
                    if (type != 0)
                    {
                        content << ",\"type\":" << type;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapHisOrdersV3Response>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapHisOrdersV3Response> SwapHisOrdersExact(const string &contract, const string &status,
                                                                            const string &direct, const string &price_type,
                                                                            int trade_type, int type,
                                                                             long start_time, long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v3/swap_hisorders_exact";

                    // option
                    stringstream content;
                    if (price_type != "")
                    {
                        content << ",\"price_type\":\"" << price_type << "\"";
                    }
                    if (status != "")
                    {
                        content << ",\"status\":\"" << status << "\"";
                    }
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
                    if (type != 0)
                    {
                        content << ",\"type\":" << type;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapHisOrdersV3Response>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapMatchResultsV3Response> SwapMatchResults(const string &contract, const string &direct, int trade_type,
                                                                                  long start_time, long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v3/swap_matchresults";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapMatchResultsV3Response>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapMatchResultsV3Response> SwapMatchResultsExact(const string &contract,
                                                                                             const string &direct, int trade_type,
                                                                                   long start_time, long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v3/swap_matchresults_exact";

                    // option
                    stringstream content;
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
                    }
                    if (contract != "")
                    {
                        content << ",\"contract\":\"" << contract << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapMatchResultsV3Response>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapLightningClosePositionResponse> SwapLightningClosePosition(const string &contract_code, const string &order_price_type,
                                                                                    const string &direction,
                                                                                    long volume, long client_order_id)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_lightning_close_position";

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
                    if (order_price_type != "")
                    {
                        content << ",\"order_price_type\":\"" << order_price_type << "\"";
                    }
                    if (volume != 0)
                    {
                        content << ",\"volume\":" << volume;
                    }
                    if (client_order_id != 0)
                    {
                        content << ",\"client_order_id\":" << client_order_id;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapLightningClosePositionResponse>(url, data.str());
                    return result;
                }
            private:
                std::shared_ptr<url_base::PrivateUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures
