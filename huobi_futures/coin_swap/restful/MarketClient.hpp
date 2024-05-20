#pragma once

#include <future>
#include <sstream>
using std::stringstream;

#include "huobi_futures/url_base/PublicUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/coin_swap/restful/response/market/SwapMarketDepthResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_market::SwapMarketDepthResponse SwapMarketDepthResponse;

#include "huobi_futures/coin_swap/restful/response/market/SwapMarketHistoryBasisResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_market::SwapMarketHistoryBasisResponse SwapMarketHistoryBasisResponse;

#include "huobi_futures/coin_swap/restful/response/market/SwapMarketHistoryTradeResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_market::SwapMarketHistoryTradeResponse SwapMarketHistoryTradeResponse;

#include "huobi_futures/coin_swap/restful/response/market/SwapMarketKlineResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_market::SwapMarketKlineResponse SwapMarketKlineResponse;

#include "huobi_futures/coin_swap/restful/response/market/SwapMarketTradeResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_market::SwapMarketTradeResponse SwapMarketTradeResponse;


namespace huobi_futures
{
    namespace coin_swap
    {
        namespace restful
        {
            class MarketClient
            {

            public:
                MarketClient(const string &host = utils::DEFAULT_HOST)
                {
                    pb = std::make_shared<url_base::PublicUrlBuilder>(host);
                }

                std::shared_ptr<SwapMarketDepthResponse> SwapMarketDepth(const string &contract_code = "",
                                                                         const string &type = "")
                {
                    // location
                    stringstream location;
                    location << "/swap-ex/market/depth";

                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (type != "")
                    {
                        option << "&type=" << type;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<SwapMarketDepthResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapMarketDepthResponse> SwapMarketBbo(const string &contract_code = "")
                {
                    // location
                    stringstream location;
                    location << "/swap-ex/market/bbo";

                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<SwapMarketDepthResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapMarketKlineResponse> SwapMarketKline(const string &contract_code = "", const string &period = "",
                                                                 int size, long from, long to)
                {
                    // location
                    stringstream location;
                    location << "/swap-ex/market/history/kline";

                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (period != "")
                    {
                        option << "&period=" << period;
                    }
                    if (size != 0)
                    {
                        option << "&size=" << size;
                    }
                    if (from != 0)
                    {
                        option << "&from=" << from;
                    }
                    if (to != 0)
                    {
                        option << "&to=" << to;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<SwapMarketKlineResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapMarketKlineResponse> SwapMarkPriceKline(const string &contract_code = "", const string &period = "",
                                                                 int size)
                {
                    // location
                    stringstream location;
                    location << "/index/market/history/swap_mark_price_kline";

                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (period != "")
                    {
                        option << "&period=" << period;
                    }
                    if (size != 0)
                    {
                        option << "&size=" << size;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<SwapMarketKlineResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapMarketKlineResponse> SwapDetailMerged(const string &contract_code = "")
                {
                    // location
                    stringstream location;
                    location << "/swap-ex/market/detail/merged";

                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<SwapMarketKlineResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapMarketKlineResponse> SwapDetailBatchMerged(const string &contract_code = "")
                {
                    // location
                    stringstream location;
                    location << "/v2/swap-ex/market/detail/batch_merged";

                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<SwapMarketKlineResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapMarketTradeResponse> SwapMarketTrade(const string &contract_code = "")
                {
                    // location
                    stringstream location;
                    location << "/swap-ex/market/trade";

                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<SwapMarketTradeResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapMarketHistoryTradeResponse> SwapMarketHistoryTrade(const string &contract_code = "", int size)
                {
                    // location
                    stringstream location;
                    location << "/swap-ex/market/history/trade";

                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (size != 0)
                    {
                        option << "&size=" << size;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<SwapMarketHistoryTradeResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapMarketHistoryBasisResponse> SwapMarketHistoryBasis(const string &symbol = "", const string &period = "",
                                                                               const string &basis_price_type = "", int size)
                {
                    // location
                    stringstream location;
                    location << "/index/market/history/swap_basis";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "&symbol=" << symbol;
                    }
                    if (period != "")
                    {
                        option << "&period=" << period;
                    }
                    if (basis_price_type != "")
                    {
                        option << "&basis_price_type=" << basis_price_type;
                    }
                    if (size != 0)
                    {
                        option << "&size=" << size;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<SwapMarketHistoryBasisResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapMarketKlineResponse> SwapPremiumIndexKline(const string &contract_code = "", const string &period = "",
                                                                               int size)
                {
                    // location
                    stringstream location;
                    location << "/index/market/history/swap_premium_index_kline";

                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (period != "")
                    {
                        option << "&period=" << period;
                    }
                    if (size != 0)
                    {
                        option << "&size=" << size;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<SwapMarketKlineResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapMarketKlineResponse> SwapEstimatedRateKline(const string &contract_code = "", const string &period = "",
                                                                               int size)
                {
                    // location
                    stringstream location;
                    location << "/index/market/history/swap_estimated_rate_kline";

                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (period != "")
                    {
                        option << "&period=" << period;
                    }
                    if (size != 0)
                    {
                        option << "&size=" << size;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<SwapMarketKlineResponse>(url);
                    return result;
                }

            private:
                std::shared_ptr<url_base::PublicUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures
