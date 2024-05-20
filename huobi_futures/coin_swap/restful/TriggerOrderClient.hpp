#pragma once

#include <future>
#include <sstream>
#include <vector>

#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/coin_swap/restful/response/trigger_order/SwapRelationTpslOrderResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_trigger_order::SwapRelationTpslOrderResponse SwapRelationTpslOrderResponse;

#include "huobi_futures/coin_swap/restful/response/trigger_order/SwapTpslOrderResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_trigger_order::SwapTpslOrderResponse SwapTpslOrderResponse;

#include "huobi_futures/coin_swap/restful/response/trigger_order/SwapTriggerCancelResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_trigger_order::SwapTriggerCancelResponse SwapTriggerCancelResponse;

#include "huobi_futures/coin_swap/restful/response/trigger_order/SwapTriggerOpenOrdersResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_trigger_order::SwapTriggerOpenOrdersResponse SwapTriggerOpenOrdersResponse;

#include "huobi_futures/coin_swap/restful/response/trigger_order/SwapTriggerOrderResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_trigger_order::SwapTriggerOrderResponse SwapTriggerOrderResponse;


namespace huobi_futures
{
    namespace coin_swap
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

                std::shared_ptr<SwapTriggerOrderResponse> SwapTriggerOrder(const string &contract_code,
                                                                           const string &trigger_type, const string &offset,
                                                                           const string &direction, long volume, int lever_rate = 0,
                                                                           float order_price = 0, float trigger_price = 0, const string &order_price_type = "")
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_trigger_order";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (trigger_type != "")
                    {
                        content << ",\"trigger_type\":\"" << trigger_type << "\"";
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
                    if (trigger_price != 0)
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTriggerOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTriggerCancelResponse> SwapTriggerCancel(const string &contract_code, const string &order_id)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_trigger_cancel";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTriggerCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTriggerCancelResponse> SwapTriggerCancelAll(const string &contract_code, const string &direction,
                                                                                           const string &offset)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_trigger_cancelall";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTriggerCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTriggerOpenOrdersResponse> SwapTriggerOpenOrders(const string &contract_code,
                                                                                        int page_index, int page_size, int trade_type)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_trigger_openorders";

                    // option
                    stringstream content;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTriggerOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTriggerOpenOrdersResponse> SwapTriggerHisOrders(const string &contract_code,
                                                                                           const string &sort_by,const string &status,
                                                                                            int trade_type, int create_date, int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_trigger_hisorders";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTriggerOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTpslOrderResponse> SwapTpslOrder(cconst string &contract_code, const string &direction,
                                                                             float volume,
                                                                             float tp_trigger_price = 0, float tp_order_price = 0, const string &tp_order_price_type = "",
                                                                             float sl_trigger_price = 0, float sl_order_price = 0, const string &sl_order_price_type = "")
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_tpsl_order";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTpslOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTriggerCancelResponse> SwapTpslCancel(const string &contract_code, const string &order_id)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_tpsl_cancel";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTriggerCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTriggerCancelResponse> SwapTpslCancelAll(const string &contract_code, const string &direction)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_tpsl_cancelall";

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

                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<SwapTriggerCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTriggerOpenOrdersResponse> SwapTpslOpenOrders(const string &contract_code,
                                                                                     int page_index, int page_size, int trade_type)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_tpsl_openorders";

                    // option
                    stringstream content;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTriggerOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTriggerOpenOrdersResponse> SwapTpslHisOrders(const string &contract_code,
                                                                                     const string &status, const string &sort_by,
                                                                                          int page_index, int page_size, long create_date)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_tpsl_hisorders";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTriggerOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapRelationTpslOrderResponse> SwapRelationTpslOrder(const string &contract_code, long order_id)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_relation_tpsl_order";

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

                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<SwapRelationTpslOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTriggerOrderResponse> SwapTrackOrder(const string &direction,
                                                                               const string &contract_code,
                                                                               const string &offset,const string &order_price_type,
                                                                               int lever_rate, float volume, float callback_rate,
                                                                               float active_price)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_track_order";

                    // option
                    stringstream content;
                    if (direction != "")
                    {
                        content << ",\"direction\":\"" << direction << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTriggerOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTriggerCancelResponse> SwapTrackCancel(const string &contract_code, const string &order_id)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_track_cancel";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTriggerCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTriggerCancelResponse> SwapTrackCancelAll(const string &contract_code,
                                                                              const string &direction,
                                                                              const string &offset)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_track_cancelall";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTriggerCancelResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTriggerOpenOrdersResponse> SwapTrackOpenOrders(const string &contract_code,
                                                                                      int trade_type, int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_track_openorders";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTriggerOpenOrdersResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTriggerOpenOrdersResponse> SwapTrackHisOrders(const string &contract_code,
                                                                                           const string &status, const string &sort_by,
                                                                                          int trade_type, long create_date, int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_track_hisorders";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTriggerOpenOrdersResponse>(url, data.str());
                    return result;
                }

            private:
                std::shared_ptr<url_base::PrivateUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures
