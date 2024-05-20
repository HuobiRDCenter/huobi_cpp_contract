#pragma once

#include <future>
#include <sstream>
using std::stringstream;

#include "huobi_futures/url_base/PublicUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/coin_futures/restful/response/market/MarketDepthResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_market::MarketDepthResponse MarketDepthResponse;

#include "huobi_futures/coin_futures/restful/response/market/MarketHistoryBasisResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_market::MarketHistoryBasisResponse MarketHistoryBasisResponse;

#include "huobi_futures/coin_futures/restful/response/market/MarketHistoryTradeResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_market::MarketHistoryTradeResponse MarketHistoryTradeResponse;

#include "huobi_futures/coin_futures/restful/response/market/MarketKlineResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_market::MarketKlineResponse MarketKlineResponse;

#include "huobi_futures/coin_futures/restful/response/market/MarketTradeResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_market::MarketTradeResponse MarketTradeResponse;


namespace huobi_futures
{
    namespace coin_futures
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

                std::shared_ptr<MarketDepthResponse> MarketDepth(const string &symbol = "",
                                                                         const string &type = "")
                {
                    // location
                    stringstream location;
                    location << "/market/depth";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "&symbol=" << symbol;
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

                    auto result = url_base::HttpRequest::Instance().Get<MarketDepthResponse>(url);
                    return result;
                }

                std::shared_ptr<MarketDepthResponse> MarketBbo(const string &symbol = "")
                {
                    // location
                    stringstream location;
                    location << "/market/bbo";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "&symbol=" << symbol;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<MarketDepthResponse>(url);
                    return result;
                }

                std::shared_ptr<MarketKlineResponse> MarketKline(const string &symbol = "", const string &period = "",
                                                                 int size, long from, long to)
                {
                    // location
                    stringstream location;
                    location << "/market/history/kline";

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

                    auto result = url_base::HttpRequest::Instance().Get<MarketKlineResponse>(url);
                    return result;
                }

                std::shared_ptr<MarketKlineResponse> MarkPriceKline(const string &symbol = "", const string &period = "",
                                                                 int size)
                {
                    // location
                    stringstream location;
                    location << "/index/market/history/mark_price_kline";

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
                    if (size != 0)
                    {
                        option << "&size=" << size;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<MarketKlineResponse>(url);
                    return result;
                }

                std::shared_ptr<MarketKlineResponse> DetailMerged(const string &symbol = "")
                {
                    // location
                    stringstream location;
                    location << "/market/detail/merged";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "&symbol=" << symbol;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<MarketKlineResponse>(url);
                    return result;
                }

                std::shared_ptr<MarketKlineResponse> DetailBatchMerged(const string &symbol = "")
                {
                    // location
                    stringstream location;
                    location << "/v2/market/detail/batch_merged";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "&symbol=" << symbol;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<MarketKlineResponse>(url);
                    return result;
                }

                std::shared_ptr<MarketTradeResponse> MarketTrade(const string &symbol = "")
                {
                    // location
                    stringstream location;
                    location << "/market/trade";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "&symbol=" << symbol;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<MarketTradeResponse>(url);
                    return result;
                }

                std::shared_ptr<MarketHistoryTradeResponse> MarketHistoryTrade(const string &symbol = "", int size)
                {
                    // location
                    stringstream location;
                    location << "/market/history/trade";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "&symbol=" << symbol;
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

                    auto result = url_base::HttpRequest::Instance().Get<MarketHistoryTradeResponse>(url);
                    return result;
                }

                std::shared_ptr<MarketKlineResponse> MarketHistoryIndex(const string &symbol = "",const string &period = "", int size)
                {
                    // location
                    stringstream location;
                    location << "/index/market/history/index";

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
                    if (size != 0)
                    {
                        option << "&size=" << size;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<MarketKlineResponse>(url);
                    return result;
                }

                std::shared_ptr<MarketHistoryBasisResponse> MarketHistoryBasis(const string &symbol = "", const string &period = "",
                                                                               const string &basis_price_type = "", int size)
                {
                    // location
                    stringstream location;
                    location << "/index/market/history/basis";

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

                    auto result = url_base::HttpRequest::Instance().Get<MarketHistoryBasisResponse>(url);
                    return result;
                }

            private:
                std::shared_ptr<url_base::PublicUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures
