#pragma once

#include <future>
#include <sstream>
using std::stringstream;

#include "huobi_futures/url_base/PublicUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/linear_swap/restful/response/reference/GetHeartbeatResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_reference::GetHeartbeatResponse GetHeartbeatResponse;

#include "huobi_futures/linear_swap/restful/response/reference/GetSwapBatchFundingRateResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_reference::GetSwapBatchFundingRateResponse GetSwapBatchFundingRateResponse;

#include "huobi_futures/linear_swap/restful/response/reference/GetSwapLiquidationOrdersResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_reference::GetSwapLiquidationOrdersResponse GetSwapLiquidationOrdersResponse;

#include "huobi_futures/linear_swap/restful/response/reference/GetSwapQueryElementsResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_reference::GetSwapQueryElementsResponse GetSwapQueryElementsResponse;

#include "huobi_futures/linear_swap/restful/response/reference/GetTimestampResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_reference::GetTimestampResponse GetTimestampResponse;

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            class ReferenceClient
            {

            public:
                ReferenceClient(const string &host = utils::DEFAULT_HOST)
                {
                    pb = std::make_shared<url_base::PublicUrlBuilder>(host);
                }

                std::shared_ptr<GetSwapBatchFundingRateResponse> GetSwapBatchFundingRate(const string &contract_code = "")
                {
                    // location
                    stringstream location;
                    location << "/linear-swap-api/v1/swap_batch_funding_rate";

                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "contract_code=" << contract_code;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<GetSwapBatchFundingRateResponse>(url);
                    return result;
                }

                std::shared_ptr<GetSwapLiquidationOrdersResponse> GetSwapLiquidationOrders(const string &contract = "",
                                                                                           const string &pair = "",
                                                                                           int trade_type, long start_time,
                                                                                           long end_time, const string &direct = "",
                                                                                           long from_id)
                {
                    // location
                    stringstream location;
                    location << "/linear-swap-api/v3/swap_liquidation_orders";

                    // option
                    stringstream option;
                    if (contract != "")
                    {
                        option << "contract=" << contract;
                    }
                    if (pair != "")
                    {
                        option << "&pair=" << pair;
                    }
                    if (trade_type != 0)
                    {
                        option << "&trade_type=" << trade_type;
                    }
                    if (start_time != 0)
                    {
                        option << "&start_time=" << start_time;
                    }
                    if (end_time != 0)
                    {
                        option << "&end_time=" << end_time;
                    }
                    if (direct != "")
                    {
                        option << "&direct=" << direct;
                    }
                    if (from_id != 0)
                    {
                        option << "&from_id=" << from_id;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<GetSwapLiquidationOrdersResponse>(url);
                    return result;
                }

                std::shared_ptr<GetSwapQueryElementsResponse> GetSwapQueryElements(const string &contract_code = "")
                {
                    // location
                    stringstream location;
                    location << "/linear-swap-api/v1/swap_query_elements";

                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "contract_code=" << contract_code;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<GetSwapQueryElementsResponse>(url);
                    return result;
                }

                std::shared_ptr<GetTimestampResponse> GetTimestamp()
                {
                    // location
                    stringstream location;
                    location << "/v1/timestamp";

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<GetTimestampResponse>(url);
                    return result;
                }

                std::shared_ptr<GetHeartbeatResponse> GetHeartbeat()
                {
                    // location
                    stringstream location;
                    location << "/heartbeat/";

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<GetHeartbeatResponse>(url);
                    return result;
                }

            private:
                std::shared_ptr<url_base::PublicUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures