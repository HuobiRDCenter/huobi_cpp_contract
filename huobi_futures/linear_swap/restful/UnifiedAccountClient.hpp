#pragma once

#include <future>
#include <sstream>
#include <vector>

#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/linear_swap/restful/response/unified_account/FixPositionMarginChangeRecordResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_unified_account::FixPositionMarginChangeRecordResponse FixPositionMarginChangeRecordResponse;

#include "huobi_futures/linear_swap/restful/response/unified_account/FixPositionMarginChangeResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_unified_account::FixPositionMarginChangeResponse FixPositionMarginChangeResponse;

#include "huobi_futures/linear_swap/restful/response/unified_account/GetSwapUnifiedAccountTypeResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_unified_account::GetSwapUnifiedAccountTypeResponse GetSwapUnifiedAccountTypeResponse;

#include "huobi_futures/linear_swap/restful/response/unified_account/LinearSwapFeeSwitchResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_unified_account::LinearSwapFeeSwitchResponse LinearSwapFeeSwitchResponse;

#include "huobi_futures/linear_swap/restful/response/unified_account/LinearSwapOverViewAccountInfoResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_unified_account::LinearSwapOverViewAccountInfoResponse LinearSwapOverViewAccountInfoResponse;

#include "huobi_futures/linear_swap/restful/response/unified_account/SwapSwitchAccountTypeResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_unified_account::SwapSwitchAccountTypeResponse SwapSwitchAccountTypeResponse;

#include "huobi_futures/linear_swap/restful/response/unified_account/SwapUnifiedAccountTypeResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_unified_account::SwapUnifiedAccountTypeResponse SwapUnifiedAccountTypeResponse;

#include "huobi_futures/linear_swap/restful/response/unified_account/UnifiedAccountInfoResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_unified_account::UnifiedAccountInfoResponse UnifiedAccountInfoResponse;

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            class UnifiedAccountClient
            {

            public:
                UnifiedAccountClient(const string &access_key, const string &secret_key, const string &host = utils::DEFAULT_HOST)
                {
                    pb = std::make_shared<url_base::PrivateUrlBuilder>(access_key, secret_key, host);
                }

                std::shared_ptr<GetSwapUnifiedAccountTypeResponse> GetSwapUnifiedAccountType()
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/swap_unified_account_type";

                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<GetSwapUnifiedAccountTypeResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapSwitchAccountTypeResponse> SwapSwitchAccountType(int account_type)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/swap_switch_account_type";

                    // option
                    stringstream content;
                    if (account_type != 0)
                    {
                        content << ",\"account_type\":" << account_type;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapSwitchAccountTypeResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<UnifiedAccountInfoResponse> UnifiedAccountInfo(const string &contract_code)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/unified_account_info";
                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }

                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<UnifiedAccountInfoResponse>(url);
                    return result;
                }

                std::shared_ptr<LinearSwapOverViewAccountInfoResponse> LinearSwapOverViewAccountInfo(const string &trade_partition)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/linear_swap_overview_account_info";
                    // option
                    stringstream option;
                    if (trade_partition != "")
                    {
                        option << "&trade_partition=" << trade_partition;
                    }
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }

                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<LinearSwapOverViewAccountInfoResponse>(url);
                    return result;
                }

                std::shared_ptr<LinearSwapFeeSwitchResponse> LinearSwapFeeSwitch(int fee_option, const string &deduction_currency)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/linear_swap_fee_switch";

                    // option
                    stringstream content;
                    if (fee_option != 0)
                    {
                        content << ",\"fee_option\":" << fee_option;
                    }
                    if (deduction_currency != "")
                    {
                        content << ",\"deduction_currency\":\"" << deduction_currency << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<LinearSwapFeeSwitchResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<FixPositionMarginChangeResponse> FixPositionMarginChange(const string &asset,
                                                                                         const string &contract_code,
                                                                                         double amount, int type, int direction, long clientOrderId)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/fix_position_margin_change";

                    // option
                    stringstream content;
                    if (asset != "")
                    {
                        content << ",\"asset\":\"" << asset << "\"";
                    }
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (amount != 0)
                    {
                        content << ",\"amount\":" << amount;
                    }
                    if (type != 0)
                    {
                        content << ",\"type\":" << type;
                    }
                    if (direction != 0)
                    {
                        content << ",\"direction\":" << direction;
                    }
                    if (clientOrderId != 0)
                    {
                        content << ",\"clientOrderId\":" << clientOrderId;
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
                    auto result = url_base::HttpRequest::Instance().Post<FixPositionMarginChangeResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<FixPositionMarginChangeRecordResponse> FixPositionMarginChangeRecord(const string &asset,
                                                                                                     const string &contract_code,
                                                                                                     const string &direct,
                                                                                                     long start_time, long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/fix_position_margin_change_record";
                    // option
                    stringstream option;
                    if (asset != "")
                    {
                        option << "&asset=" << asset;
                    }
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (direct != "")
                    {
                        option << "&direct=" << direct;
                    }
                    if (start_time != 0)
                    {
                        option << "&start_time=" << start_time;
                    }
                    if (end_time != 0)
                    {
                        option << "&end_time=" << end_time;
                    }
                    if (from_id != 0)
                    {
                        option << "&from_id=" << from_id;
                    }
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }

                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<FixPositionMarginChangeRecordResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapUnifiedAccountTypeResponse> SwapUnifiedAccountType()
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/swap_unified_account_type";

                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<SwapUnifiedAccountTypeResponse>(url);
                    return result;
                }
            private:
                std::shared_ptr<url_base::PrivateUrlBuilder> pb;
            };

            std::shared_ptr<SwapUnifiedAccountTypeResponse> SwapSwitchAccountType(int account_type)
            {
                // path
                stringstream path;
                path << "/linear-swap-api/v3/swap_switch_account_type";

                // option
                stringstream content;
                if (account_type != 0)
                {
                    content << ",\"account_type\":" << account_type;
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
                auto result = url_base::HttpRequest::Instance().Post<SwapUnifiedAccountTypeResponse>(url, data.str());
                return result;
            }
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures
