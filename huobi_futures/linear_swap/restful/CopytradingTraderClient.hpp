#pragma once

#include <future>
#include <sstream>
#include <vector>

#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

// 引入响应结果
#include "huobi_futures/linear_swap/restful/response/copytradingtrader/CopytradingTraderInstrumentsResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_copytradingtrader::CopytradingTraderInstrumentsResponse CopytradingTraderInstrumentsResponse;

#include "huobi_futures/linear_swap/restful/response/copytradingtrader/CopytradingTraderStatisticsResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_copytradingtrader::CopytradingTraderStatisticsResponse CopytradingTraderStatisticsResponse;

#include "huobi_futures/linear_swap/restful/response/copytradingtrader/CopytradingTraderProfitSharingHistoryResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_copytradingtrader::CopytradingTraderProfitSharingHistoryResponse CopytradingTraderProfitSharingHistoryResponse;

#include "huobi_futures/linear_swap/restful/response/copytradingtrader/CopytradingTraderProfitSharingHistorySummaryResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_copytradingtrader::CopytradingTraderProfitSharingHistorySummaryResponse CopytradingTraderProfitSharingHistorySummaryResponse;

#include "huobi_futures/linear_swap/restful/response/copytradingtrader/CopytradingTraderUnrealizedProfitSharingSummaryResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_copytradingtrader::CopytradingTraderUnrealizedProfitSharingSummaryResponse CopytradingTraderUnrealizedProfitSharingSummaryResponse;

#include "huobi_futures/linear_swap/restful/response/copytradingtrader/CopytradingTraderFollowersResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_copytradingtrader::CopytradingTraderFollowersResponse CopytradingTraderFollowersResponse;

#include "huobi_futures/linear_swap/restful/response/copytradingtrader/CopytradingTraderDeleteFollowerResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_copytradingtrader::CopytradingTraderDeleteFollowerResponse CopytradingTraderDeleteFollowerResponse;

#include "huobi_futures/linear_swap/restful/response/copytradingtrader/CopytradingTraderTransferResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_copytradingtrader::CopytradingTraderTransferResponse CopytradingTraderTransferResponse;

#include "huobi_futures/linear_swap/restful/response/copytradingtrader/CopytradingTraderFollowerSettingsResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_copytradingtrader::CopytradingTraderFollowerSettingsResponse CopytradingTraderFollowerSettingsResponse;

#include "huobi_futures/linear_swap/restful/response/copytradingtrader/CopytradingTraderConfigResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_copytradingtrader::CopytradingTraderConfigResponse CopytradingTraderConfigResponse;

#include "huobi_futures/linear_swap/restful/response/copytradingtrader/CopytradingTraderApikeyResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_copytradingtrader::CopytradingTraderApikeyResponse CopytradingTraderApikeyResponse;

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            class CopytradingTraderClient
            {
            public:
                CopytradingTraderClient(const string &access_key, const string &secret_key, const string &host = utils::DEFAULT_HOST)
                {
                    pb = std::make_shared<url_base::PrivateUrlBuilder>(access_key, secret_key, host);
                }

                // GET请求 - 查询交易员支持的合约信息
                std::shared_ptr<CopytradingTraderInstrumentsResponse> QueryTraderInstruments(const string &instType)
                {
                    // path
                    stringstream path;
                    path << "/api/v6/copyTrading/trader/instruments";

                    // option
                    stringstream option;
                    if (instType != "")
                    {
                        option << "&instType=" << instType;
                    }

                    if (!option.str().empty())
                    {
                        path << "?" << option.str().substr(1);
                    }

                    // url
                    string url = pb->Build("GET", path.str());

                    // get
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderInstrumentsResponse>(url);
                    return result;
                }

                // GET请求 - 查询交易员数据统计
                std::shared_ptr<CopytradingTraderStatisticsResponse> QueryTraderStatistics(const string &instType)
                {
                    // path
                    stringstream path;
                    path << "/api/v6/copyTrading/trader/statistics";

                    // option
                    stringstream option;
                    if (instType != "")
                    {
                        option << "&instType=" << instType;
                    }

                    if (!option.str().empty())
                    {
                        path << "?" << option.str().substr(1);
                    }

                    // url
                    string url = pb->Build("GET", path.str());

                    // get
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderStatisticsResponse>(url);
                    return result;
                }

                // GET请求 - 查询交易员分润历史
                std::shared_ptr<CopytradingTraderProfitSharingHistoryResponse> QueryTraderProfitSharingHistory(
                    const string &instId, const string &instType, const string &begin, const string &end, 
                    const string &after, const string &before, int32_t limit)
                {
                    // path
                    stringstream path;
                    path << "/api/v6/copyTrading/trader/profit-sharing-history";

                    // option
                    stringstream option;
                    if (instId != "")
                    {
                        option << "&instId=" << instId;
                    }
                    if (instType != "")
                    {
                        option << "&instType=" << instType;
                    }
                    if (begin != "")
                    {
                        option << "&begin=" << begin;
                    }
                    if (end != "")
                    {
                        option << "&end=" << end;
                    }
                    if (after != "")
                    {
                        option << "&after=" << after;
                    }
                    if (before != "")
                    {
                        option << "&before=" << before;
                    }
                    if (limit != 0)
                    {
                        option << "&limit=" << limit;
                    }

                    if (!option.str().empty())
                    {
                        path << "?" << option.str().substr(1);
                    }

                    // url
                    string url = pb->Build("GET", path.str());

                    // get
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderProfitSharingHistoryResponse>(url);
                    return result;
                }

                // GET请求 - 查询交易员分润历史汇总
                std::shared_ptr<CopytradingTraderProfitSharingHistorySummaryResponse> QueryTraderProfitSharingHistorySummary(const string &instType)
                {
                    // path
                    stringstream path;
                    path << "/api/v6/copyTrading/trader/profit-sharing-history-summary";

                    // option
                    stringstream option;
                    if (instType != "")
                    {
                        option << "&instType=" << instType;
                    }

                    if (!option.str().empty())
                    {
                        path << "?" << option.str().substr(1);
                    }

                    // url
                    string url = pb->Build("GET", path.str());

                    // get
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderProfitSharingHistorySummaryResponse>(url);
                    return result;
                }

                // GET请求 - 查询交易员待分润汇总
                std::shared_ptr<CopytradingTraderUnrealizedProfitSharingSummaryResponse> QueryTraderUnrealizedProfitSharingSummary(
                    const string &instType, const string &ccy)
                {
                    // path
                    stringstream path;
                    path << "/api/v6/copyTrading/trader/unrealized-profit-sharing-summary";

                    // option
                    stringstream option;
                    if (instType != "")
                    {
                        option << "&instType=" << instType;
                    }
                    if (ccy != "")
                    {
                        option << "&ccy=" << ccy;
                    }

                    if (!option.str().empty())
                    {
                        path << "?" << option.str().substr(1);
                    }

                    // url
                    string url = pb->Build("GET", path.str());

                    // get
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderUnrealizedProfitSharingSummaryResponse>(url);
                    return result;
                }

                // GET请求 - 查询跟随者列表
                std::shared_ptr<CopytradingTraderFollowersResponse> QueryTraderFollowers(
                    const string &instType, const string &begin, const string &end, 
                    const string &after, const string &before, int32_t limit)
                {
                    // path
                    stringstream path;
                    path << "/api/v6/copyTrading/trader/followers";

                    // option
                    stringstream option;
                    if (instType != "")
                    {
                        option << "&instType=" << instType;
                    }
                    if (begin != "")
                    {
                        option << "&begin=" << begin;
                    }
                    if (end != "")
                    {
                        option << "&end=" << end;
                    }
                    if (after != "")
                    {
                        option << "&after=" << after;
                    }
                    if (before != "")
                    {
                        option << "&before=" << before;
                    }
                    if (limit != 0)
                    {
                        option << "&limit=" << limit;
                    }

                    if (!option.str().empty())
                    {
                        path << "?" << option.str().substr(1);
                    }

                    // url
                    string url = pb->Build("GET", path.str());

                    // get
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderFollowersResponse>(url);
                    return result;
                }

                // POST请求 - 删除跟随者
                std::shared_ptr<CopytradingTraderDeleteFollowerResponse> DeleteTraderFollower(
                    const string &instType, const string &followerUids)
                {
                    // path
                    stringstream path;
                    path << "/api/v6/copyTrading/trader/follower";

                    // option
                    stringstream content;
                    if (instType != "")
                    {
                        content << ",\"instType\":\"" << instType << "\"";
                    }
                    if (followerUids != "")
                    {
                        content << ",\"followerUids\":\"" << followerUids << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<CopytradingTraderDeleteFollowerResponse>(url, data.str());
                    return result;
                }

                // POST请求 - 交易员资金划转
                std::shared_ptr<CopytradingTraderTransferResponse> TraderTransfer(
                    const string &amt, const string &from, const string &to, const string &ccy)
                {
                    // path
                    stringstream path;
                    path << "/api/v6/copyTrading/trader/transfer";

                    // option
                    stringstream content;
                    if (amt != "")
                    {
                        content << ",\"amt\":\"" << amt << "\"";
                    }
                    if (from != "")
                    {
                        content << ",\"from\":\"" << from << "\"";
                    }
                    if (to != "")
                    {
                        content << ",\"to\":\"" << to << "\"";
                    }
                    if (ccy != "")
                    {
                        content << ",\"ccy\":\"" << ccy << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<CopytradingTraderTransferResponse>(url, data.str());
                    return result;
                }

                // POST请求 - 交易员跟单设置
                std::shared_ptr<CopytradingTraderFollowerSettingsResponse> TraderFollowerSettings(
                    const string &instType, bool enable, const string &profitSharingRatio, const string &maxFollowers)
                {
                    // path
                    stringstream path;
                    path << "/api/v6/copyTrading/trader/follower-settings";

                    // option
                    stringstream content;
                    if (instType != "")
                    {
                        content << ",\"instType\":\"" << instType << "\"";
                    }
                    content << ",\"enable\":\"" << (enable ? "true" : "false") << "\"";
                    if (profitSharingRatio != "")
                    {
                        content << ",\"profitSharingRatio\":\"" << profitSharingRatio << "\"";
                    }
                    if (maxFollowers != "")
                    {
                        content << ",\"maxFollowers\":\"" << maxFollowers << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<CopytradingTraderFollowerSettingsResponse>(url, data.str());
                    return result;
                }

                // GET请求 - 查询交易员配置
                std::shared_ptr<CopytradingTraderConfigResponse> TraderConfig(const string &instType)
                {
                    // path
                    stringstream path;
                    path << "/api/v6/copyTrading/trader/config";

                    // option
                    stringstream option;
                    if (instType != "")
                    {
                        option << "&instType=" << instType;
                    }

                    if (!option.str().empty())
                    {
                        path << "?" << option.str().substr(1);
                    }

                    // url
                    string url = pb->Build("GET", path.str());

                    // get
                    auto result = url_base::HttpRequest::Instance().Get<CopytradingTraderConfigResponse>(url);
                    return result;
                }

                // POST请求 - 交易员APIkey管理
                std::shared_ptr<CopytradingTraderApikeyResponse> TraderApikey(const string &instType)
                {
                    // path
                    stringstream path;
                    path << "/api/v6/copyTrading/trader/apikey";

                    // option
                    stringstream content;
                    if (instType != "")
                    {
                        content << ",\"instType\":\"" << instType << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<CopytradingTraderApikeyResponse>(url, data.str());
                    return result;
                }

            private:
                std::shared_ptr<url_base::PrivateUrlBuilder> pb;
            };
        }
    }
}