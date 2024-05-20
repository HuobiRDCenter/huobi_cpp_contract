#pragma once

#include <future>
#include <sstream>
#include <vector>

#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/coin_futures/restful/request/order/PlaceOrderRequest.hpp"
typedef huobi_futures::coin_futures::restful::request_order::PlaceOrderRequest PlaceOrderRequest;

#include "huobi_futures/coin_futures/restful/response/order/ContractBatchOrderResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_order::ContractBatchOrderResponse ContractBatchOrderResponse;

#include "huobi_futures/coin_futures/restful/response/order/ContractCancelAfterResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_order::ContractCancelAfterResponse ContractCancelAfterResponse;

#include "huobi_futures/coin_futures/restful/response/order/ContractCancelResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_order::ContractCancelResponse ContractCancelResponse;

#include "huobi_futures/coin_futures/restful/response/order/ContractHisOrdersResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_order::ContractHisOrdersResponse ContractHisOrdersResponse;

#include "huobi_futures/coin_futures/restful/response/order/ContractMatchResultsResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_order::ContractMatchResultsResponse ContractMatchResultsResponse;

#include "huobi_futures/coin_futures/restful/response/order/ContractOpenOrdersResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_order::ContractOpenOrdersResponse ContractOpenOrdersResponse;

#include "huobi_futures/coin_futures/restful/response/order/ContractOrderDetailResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_order::ContractOrderDetailResponse ContractOrderDetailResponse;

#include "huobi_futures/coin_futures/restful/response/order/ContractOrderInfoResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_order::ContractOrderInfoResponse ContractOrderInfoResponse;

#include "huobi_futures/coin_futures/restful/response/order/ContractOrderResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_order::ContractOrderResponse ContractOrderResponse;

#include "huobi_futures/coin_futures/restful/response/order/ContractSwitchLeverRateResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_order::ContractSwitchLeverRateResponse ContractSwitchLeverRateResponse;

#include "huobi_futures/coin_futures/restful/response/order/LightningClosePositionResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_order::LightningClosePositionResponse LightningClosePositionResponse;


namespace huobi_futures
{
    namespace coin_futures
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

                std::shared_ptr<ContractCancelAfterResponse> ContractCancelAfter(int on_off, int time_out)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract-cancel-after";

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
                    auto result = url_base::HttpRequest::Instance().Post<ContractCancelAfterResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractOrderResponse> ContractOrder(const PlaceOrderRequest &request)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_order";

                    // option
                    string data = request.to_json();

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<ContractOrderResponse>(url, data);
                    return result;
                }

                std::shared_ptr<ContractBatchOrderResponse> ContractBatchOrder(const std::vector<PlaceOrderRequest> &request)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_batchorder";

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
                    auto result = url_base::HttpRequest::Instance().Post<ContractBatchOrderResponse>(url, data);
                    return result;
                }

                std::shared_ptr<ContractCancelResponse> ContractCancel(const string &order_id, const string &client_order_id, const string &symbol)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_cancel";

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
                    if (symbol != "")
                    {
                        time_out << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractCancelResponse> ContractCancelAll(const string &symbol, const string &contract_code,
                                                                             const string &contract_type, const string &direction,
                                                                             const string &offset)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_cancelall";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
                    if (contract_code != "")
                    {
                        time_out << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (contract_type != "")
                    {
                        time_out << ",\"contract_type\":\"" << contract_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractSwitchLeverRateResponse> ContractSwitchLeverRate(const string &symbol, int lever_rate)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_switch_lever_rate";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractSwitchLeverRateResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractOrderInfoResponse> ContractOrderInfo(const string &order_id, const string &client_order_id,const string &symbol)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_order_info";

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
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractOrderInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractOrderDetailResponse> ContractOrderDetail(const string &symbol, long order_id,
                                                                                 long created_at, int order_type,
                                                                                 int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_order_detail";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractOrderDetailResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractOpenOrdersResponse> ContractOpenOrders(const string &symbol, const string &sort_by,
                                                                                 long page_index, int page_size,
                                                                                 int trade_type)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_openorders";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractHisOrdersResponse> ContractHisOrders(const string &symbol, const string &status,
                                                                             const string &order_type, const string &sort_by,
                                                                             const string &direct, int trade_type, int type,
                                                                             long start_time, long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/api/v3/contract_hisorders";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
                    if (status != "")
                    {
                        content << ",\"status\":\"" << status << "\"";
                    }
                    if (order_type != "")
                    {
                        content << ",\"order_type\":\"" << order_type << "\"";
                    }
                    if (sort_by != "")
                    {
                        content << ",\"sort_by\":\"" << sort_by << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractHisOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractHisOrdersResponse> ContractHisOrdersExact(const string &symbol, const string &status,
                                                                             const string &contract, const string &order_type,
                                                                             const string &direct, int trade_type, int type,
                                                                             long start_time, long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/api/v3/contract_hisorders_exact";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
                    if (status != "")
                    {
                        content << ",\"status\":\"" << status << "\"";
                    }
                    if (order_type != "")
                    {
                        content << ",\"order_type\":\"" << order_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractHisOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractMatchResultsResponse> ContractMatchResults(const string &symbol, const string &direct, int trade_type,
                                                                                  long start_time, long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/api/v3/contract_matchresults";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractMatchResultsResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractMatchResultsResponse> ContractMatchResultsExact(const string &symbol, const string &contract,
                                                                                             const string &direct, int trade_type,
                                                                                   long start_time, long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/api/v3/contract_matchresults_exact";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractMatchResultsResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<LightningClosePositionResponse> LightningClosePosition(const string &symbol, const string &contract_type,
                                                                                        const string &contract_code, const string &direction,
                                                                                       const string &order_price_type, long volume, long client_order_id)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/lightning_close_position";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
                    }
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
                    auto result = url_base::HttpRequest::Instance().Post<LightningClosePositionResponse>(url, data.str());
                    return result;
                }
            private:
                std::shared_ptr<url_base::PrivateUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures
