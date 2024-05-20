#pragma once

#include <future>
#include <sstream>
#include <vector>

#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/coin_futures/restful/response/trigger_order/ContractRelationTpslOrderResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_trigger_order::ContractRelationTpslOrderResponse ContractRelationTpslOrderResponse;

#include "huobi_futures/coin_futures/restful/response/trigger_order/ContractTpslOrderResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_trigger_order::ContractTpslOrderResponse ContractTpslOrderResponse;

#include "huobi_futures/coin_futures/restful/response/trigger_order/ContractTriggerCancelResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_trigger_order::ContractTriggerCancelResponse ContractTriggerCancelResponse;

#include "huobi_futures/coin_futures/restful/response/trigger_order/ContractTriggerOpenOrdersResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_trigger_order::ContractTriggerOpenOrdersResponse ContractTriggerOpenOrdersResponse;

#include "huobi_futures/coin_futures/restful/response/trigger_order/ContractTriggerOrderResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_trigger_order::ContractTriggerOrderResponse ContractTriggerOrderResponse;


namespace huobi_futures
{
    namespace coin_futures
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

                std::shared_ptr<ContractTriggerOrderResponse> ContractTriggerOrder(const string &symbol, const string &contract_type,
                                                                                   const string &contract_code, const string &trigger_type, const string &offset, float trigger_price,
                                                                                   const string &direction, long volume, int lever_rate = 0,
                                                                                   float order_price = 0, const string &order_price_type = "")
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_trigger_order";

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
                    if (trigger_type != "")
                    {
                        content << ",\"trigger_type\":\"" << trigger_type << "\"";
                    }
                    if (offset != "")
                    {
                        content << ",\"offset\":\"" << offset << "\"";
                    }
                    if (order_price_type != "")
                    {
                        content << ",\"order_price_type\":\"" << order_price_type << "\"";
                    }
                    if (trigger_price != 0.0)
                    {
                        content << ",\"trigger_price\":" << trigger_price;
                    }
                    if (volume != 0)
                    {
                        content << ",\"volume\":" << volume;
                    }
                    if (lever_rate != 0)
                    {
                        content << ",\"lever_rate\":" << lever_rate;
                    }
                    if (order_price != 0)
                    {
                        content << ",\"order_price\":" << order_price;
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTriggerOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTriggerCancelResponse> ContractTriggerCancel(const string &symbol, const string &order_id)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_trigger_cancel";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTriggerCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTriggerCancelResponse> ContractTriggerCancelAll(const string &symbol, const string &contract_code,
                                                                                           const string &contract_type, const string &direction,
                                                                                           const string &offset)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_trigger_cancelall";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTriggerCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTriggerOpenOrdersResponse> ContractTriggerOpenOrders(const string &symbol, const string &contract_code,
                                                                                        int page_index, int page_size, int trade_type)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_trigger_openorders";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTriggerOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTriggerOpenOrdersResponse> ContractTriggerHisOrders(const string &symbol, const string &contract_code,
                                                                                           const string &sort_by,const string &status,
                                                                                            int trade_type, int create_date, int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_trigger_hisorders";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (sort_by != "")
                    {
                        content << ",\"sort_by\":\"" << sort_by << "\"";
                    }
                    if (status != "")
                    {
                        content << ",\"status\":\"" << status << "\"";
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
                        content << ",\"trade_type\":" << trade_type;
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTriggerOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTpslOrderResponse> ContractTpslOrder(const string &symbol, const string &contract_type, const string &contract_code, const string &direction,
                                                                             float volume,
                                                                             float tp_trigger_price = 0, float tp_order_price = 0, const string &tp_order_price_type = "",
                                                                             float sl_trigger_price = 0, float sl_order_price = 0, const string &sl_order_price_type = "")
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_tpsl_order";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
                    }
                    if (direction != "")
                    {
                        content << ",\"direction\":\"" << direction << "\"";
                    }
                    if (tp_order_price_type != "")
                    {
                        content << ",\"tp_order_price_type\":\"" << tp_order_price_type << "\"";
                    }
                    if (sl_order_price_type != "")
                    {
                        content << ",\"sl_order_price_type\":\"" << sl_order_price_type << "\"";
                    }
                    if (volume != 0)
                    {
                        content << ",\"volume\":" << volume;
                    }
                    if (tp_trigger_price != 0)
                    {
                        content << ",\"tp_trigger_price\":" << tp_trigger_price;
                    }
                    if (tp_order_price != 0)
                    {
                        content << ",\"tp_order_price\":" << tp_order_price;
                    }
                    if (sl_trigger_price != 0)
                    {
                        content << ",\"sl_trigger_price\":" << sl_trigger_price;
                    }
                    if (sl_order_price != 0)
                    {
                        content << ",\"sl_order_price\":" << sl_order_price;
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTpslOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTriggerCancelResponse> ContractTpslCancel(const string &symbol, const string &order_id)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_tpsl_cancel";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTriggerCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTriggerCancelResponse> ContractTpslCancelAll(const string &symbol, const string &contract_code,
                                                                                     const string &contract_type, const string &direction)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_tpsl_cancelall";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTriggerCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTriggerOpenOrdersResponse> ContractTpslOpenOrders(const string &symbol, const string &contract_code,
                                                                                     int page_index, int page_size, int trade_type)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_tpsl_openorders";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTriggerOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTriggerOpenOrdersResponse> ContractTpslHisOrders(const string &symbol, const string &contract_code,
                                                                                     const string &status, const string &sort_by,
                                                                                          int page_index, int page_size, long create_date)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_tpsl_hisorders";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTriggerOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractRelationTpslOrderResponse> ContractRelationTpslOrder(const string &symbol, long order_id)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_relation_tpsl_order";

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

                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<ContractRelationTpslOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTriggerOrderResponse> ContractTrackOrder(const string &symbol, const string &direction,
                                                                               const string &contract_type, const string &contract_code,
                                                                               const string &offset,const string &order_price_type,
                                                                               int lever_rate, float volume, float callback_rate,
                                                                               float active_price)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_track_order";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
                    if (direction != "")
                    {
                        content << ",\"direction\":\"" << direction << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
                    }
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (offset != "")
                    {
                        content << ",\"offset\":\"" << offset << "\"";
                    }
                    if (order_price_type != "")
                    {
                        content << ",\"order_price_type\":\"" << order_price_type << "\"";
                    }
                    if (lever_rate != 0)
                    {
                        content << ",\"lever_rate\":" << lever_rate;
                    }
                    if (volume != 0)
                    {
                        content << ",\"volume\":" << volume;
                    }
                    if (callback_rate != 0)
                    {
                        content << ",\"callback_rate\":" << callback_rate;
                    }
                    if (active_price != 0)
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTriggerOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTriggerCancelResponse> ContractTrackCancel(const string &symbol, const string &order_id)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_track_cancel";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTriggerCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTriggerCancelResponse> ContractTrackCancelAll(const string &symbol, const string &contract_code,
                                                                                       const string &contract_type, const string &direction,
                                                                                       const string &offset)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_track_cancelall";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTriggerCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTriggerOpenOrdersResponse> ContractTrackOpenOrders(const string &symbol, const string &contract_code,
                                                                                      int trade_type, int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_track_openorders";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTriggerOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTriggerOpenOrdersResponse> ContractTrackHisOrders(const string &symbol, const string &contract_code,
                                                                                           const string &status, const string &sort_by,
                                                                                          int trade_type, long create_date, int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_track_hisorders";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
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
                    if (create_date != 0)
                    {
                        content << ",\"create_date\":" << create_date;
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTriggerOpenOrdersResponse>(url, data.str());
                    return result;
                }

            private:
                std::shared_ptr<url_base::PrivateUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures
