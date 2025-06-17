#pragma once

#include <future>
#include <sstream>
#include <vector>

#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/linear_swap/restful/request/copytrading/PlaceOrderRequest.hpp"
typedef huobi_futures::linear_swap::restful::request_copytrading::PlaceOrderRequest PlaceOrderRequest;

#include "huobi_futures/linear_swap/restful/response/copytrading/PlaceOrderResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_copytrading::PlaceOrderResponse PlaceOrderResponse;

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            class CopytradingClient
            {

            public:
                CopytradingClient(const string &access_key, const string &secret_key, const string &host = utils::DEFAULT_HOST)
                {
                    pb = std::make_shared<url_base::PrivateUrlBuilder>(access_key, secret_key, host);
                }

                std::shared_ptr<CopytradingTraderPlaceOrderResponse> CopytradingTraderPlaceOrder(const string &contract_code, const string &price,
                                                                              const string &amount,
                                                                              const string &margin_mode,
int order_price_type, int order_direction, int lever, const string &tp_trigger_price, const string &sl_trigger_price)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/place_order";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"price\":\"" << price << "\""
                            << ",\"amount\":\"" << amount << "\""
                            << ",\"margin_mode\":\"" << margin_mode << "\""
                            << ",\"order_price_type\":\"" << order_price_type << "\""
                            << ",\"order_direction\":\"" << order_direction << "\""
                            << ",\"lever\":\"" << lever << "\""
                            << ",\"tp_trigger_price\":\"" << tp_trigger_price << "\""
                            << ",\"sl_trigger_price\":" << sl_trigger_price;
                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<CopytradingTraderPlaceOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<CopytradingTraderQueryContractLeverResponse> CopytradingTraderQueryContractLever(
const string &contract_code, const string &margin_mode)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/query_contract_lever";
                    // option
                    stringstream option;
                    if (margin_account != "") {
                        option << "&margin_account=" << margin_account;
                    }
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
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderQueryContractLeverResponse>(url);
                    return result;
                }

                std::shared_ptr<CopytradingTraderUpdatedContractLeverResponse> CopytradingTraderUpdatedContractLever(const string &contract_code, int lever,
                                                                                              const string &margin_mode)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/updated_contract_lever";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"margin_mode\":\"" << margin_mode << "\""
                            << ",\"lever\":" << lever;
                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<CopytradingTraderUpdatedContractLeverResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<CopytradingTraderCloseOrderResponse> CopytradingTraderCloseOrder(const string &sub_position_id)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/close_order";

                    // option
                    stringstream content;
                    content << ",\"sub_position_id\":" << sub_position_id;
                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<CopytradingTraderCloseOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<CopytradingTraderCloseAllPositionResponse> CopytradingTraderCloseAllPosition(const string &contract_code, const string &margin_mode, const string &position_side)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/close_all_position";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"margin_mode\":\"" << margin_mode << "\""
                            << ",\"position_side\":" << position_side;
                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<CopytradingTraderCloseAllPositionResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<CopytradingTraderAddMarginResponse> CopytradingTraderAddMargin(const string &contract_code, const string &amount, const string &position_side, int type)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/add_margin";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\""
                            << ",\"margin_mode\":\"" << margin_mode << "\""
                            << ",\"type\":\"" << type << "\""
                            << ",\"position_side\":" << position_side;
                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<CopytradingTraderAddMarginResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<CopytradingTraderPositionListResponse> CopytradingTraderPositionList()
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/position_list";
                    // option
                    stringstream option;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderPositionListResponse>(url);
                    return result;
                }

                std::shared_ptr<CopytradingTraderAccountTransferResponse> CopytradingTraderAccountTransfer(const string &amount, int type, const string &currency)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/account_transfer";

                    // option
                    stringstream content;
                    content << ",\"amount\":\"" << amount << "\""
                            << ",\"type\":\"" << type << "\""
                            << ",\"currency\":" << currency;
                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<CopytradingTraderAccountTransferResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<CopytradingTraderCurrentPositionsResponse> CopytradingTraderCurrentPositions(
                const string &contract_code, long start_time, long end_time, const string &direct, long from_id, long limit)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/current_positions";
                    // option
                    stringstream option;
                    if (contract_code != "") {
                        option << "&contract_code=" << contract_code;
                    }
                    option << "&start_time=" << start_time;
                    option << "&end_time=" << end_time;
                    option << "&direct=" << direct;
                    option << "&from_id=" << from_id;
                    option << "&limit=" << limit;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderCurrentPositionsResponse>(url);
                    return result;
                }

                std::shared_ptr<CopytradingTraderPositionPositionsResponse> CopytradingTraderPositionPositions(
                                const string &contract_code, long start_time, long end_time, const string &direct, long from_id, long limit)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/position_positions";
                    // option
                    stringstream option;
                    if (contract_code != "") {
                        option << "&contract_code=" << contract_code;
                    }
                    option << "&start_time=" << start_time;
                    option << "&end_time=" << end_time;
                    option << "&direct=" << direct;
                    option << "&from_id=" << from_id;
                    option << "&limit=" << limit;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderPositionPositionsResponse>(url);
                    return result;
                }

                std::shared_ptr<CopytradingTraderTpslOrderResponse> CopytradingTraderTpslOrder(const string &sub_position_id, const string &tp_trigger_price, const string &sl_trigger_price)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/tpsl_order";

                    // option
                    stringstream content;
                    content << ",\"sub_position_id\":\"" << sub_position_id << "\""
                            << ",\"tp_trigger_price\":\"" << tp_trigger_price << "\""
                            << ",\"sl_trigger_price\":" << sl_trigger_price;
                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<CopytradingTraderTpslOrderResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<CopytradingTraderQueryContractResponse> CopytradingTraderQueryContract()
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/query_contract";
                    // option
                    stringstream option;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderQueryContractResponse>(url);
                    return result;
                }

                std::shared_ptr<CopytradingTraderOrderTotalDetailResponse> CopytradingTraderOrderTotalDetail()
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/order_total_detail";
                    // option
                    stringstream option;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderOrderTotalDetailResponse>(url);
                    return result;
                }

                std::shared_ptr<CopytradingTraderProfitHistoryDetailsResponse> CopytradingTraderProfitHistoryDetails(
                                               long start_time, long end_time, const string &direct, long from_id, long limit)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/profit_history_details";
                    // option
                    stringstream option;
                    option << "&start_time=" << start_time;
                    option << "&end_time=" << end_time;
                    option << "&direct=" << direct;
                    option << "&from_id=" << from_id;
                    option << "&limit=" << limit;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderProfitHistoryDetailsResponse>(url);
                    return result;
                }

                std::shared_ptr<CopytradingTraderTotalProfitHistoryResponse> CopytradingTraderTotalProfitHistory()
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/total_profit_history";
                    // option
                    stringstream option;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderTotalProfitHistoryResponse>(url);
                    return result;
                }

                std::shared_ptr<CopytradingTraderQueryFollowersResponse> CopytradingTraderQueryFollowers(
                                                               long start_time, long end_time, const string &direct, long from_id, long limit)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/query_followers";
                    // option
                    stringstream option;
                    option << "&start_time=" << start_time;
                    option << "&end_time=" << end_time;
                    option << "&direct=" << direct;
                    option << "&from_id=" << from_id;
                    option << "&limit=" << limit;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderQueryFollowersResponse>(url);
                    return result;
                }

                std::shared_ptr<CopytradingTraderRemoveFollowerResponse> CopytradingTraderRemoveFollower(const string &follower_uid)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/remove_follower";

                    // option
                    stringstream content;
                    content << ",\"follower_uid\":" << follower_uid;
                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<CopytradingTraderRemoveFollowerResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<CopytradingTraderOpenOrdersResponse> CopytradingTraderOpenOrders(
                                                                               const string &contract_code)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/open_orders";
                    // option
                    stringstream option;
                    option << "&contract_code=" << contract_code;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderOpenOrdersResponse>(url);
                    return result;
                }

                std::shared_ptr<CopytradingTraderTpslOpenOrdersResponse> CopytradingTraderTpslOpenOrders(
                                                                                               const string &contract_code)
                {
                    // path
                    stringstream path;
                    path << "/copytrading/trader/tpsl_open_orders";
                    // option
                    stringstream option;
                    option << "&contract_code=" << contract_code;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderTpslOpenOrdersResponse>(url);
                    return result;
                }
            }
        }
    }
}