#pragma once

#include <future>
#include <sstream>

#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/linear_swap/restful/response/account/GetBalanceValuationResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetBalanceValuationResponse GetBalanceValuationResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetAccountInfoResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetAccountInfoResponse GetAccountInfoResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetPositionInfoResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetPositionInfoResponse GetPositionInfoResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetAccountPositionResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetAccountPositionResponse GetAccountPositionResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetAccountPositionSingleResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetAccountPositionSingleResponse GetAccountPositionSingleResponse;

#include "huobi_futures/linear_swap/restful/response/account/SetSubAuthResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::SetSubAuthResponse SetSubAuthResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetSubAccountListResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetSubAccountListResponse GetSubAccountListResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetSubAccountInfoListResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetSubAccountInfoListResponse GetSubAccountInfoListResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetFinancialRecordResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetFinancialRecordResponse GetFinancialRecordResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetFinancialRecordExactResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetFinancialRecordExactResponse GetFinancialRecordExactResponse;

#include "huobi_futures/linear_swap/restful/response/account/IsolatedGetUserSettlementRecordsResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::IsolatedGetUserSettlementRecordsResponse IsolatedGetUserSettlementRecordsResponse;

#include "huobi_futures/linear_swap/restful/response/account/CrossGetUserSettlementRecordsResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::CrossGetUserSettlementRecordsResponse CrossGetUserSettlementRecordsResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetAvailableLevelRateResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetAvailableLevelRateResponse GetAvailableLevelRateResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetOrderLimitResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetOrderLimitResponse GetOrderLimitResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetFeeResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetFeeResponse GetFeeResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetTransferLimitResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetTransferLimitResponse GetTransferLimitResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetPositionLimitResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetPositionLimitResponse GetPositionLimitResponse;

#include "huobi_futures/linear_swap/restful/response/account/MasterSubTransferResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::MasterSubTransferResponse MasterSubTransferResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetMasterSubTransferRecordResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetMasterSubTransferRecordResponse GetMasterSubTransferRecordResponse;

#include "huobi_futures/linear_swap/restful/response/account/TransferInnerRecordResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::TransferInnerRecordResponse TransferInnerRecordResponse;

#include "huobi_futures/linear_swap/restful/response/account/GetApiTradingStatusResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::GetApiTradingStatusResponse GetApiTradingStatusResponse;

#include "huobi_futures/linear_swap/restful/response/account/SwapCrossLeverPositionLimitResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::SwapCrossLeverPositionLimitResponse SwapCrossLeverPositionLimitResponse;

#include "huobi_futures/linear_swap/restful/response/account/SwapCrossSubAccountInfoResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::SwapCrossSubAccountInfoResponse SwapCrossSubAccountInfoResponse;

#include "huobi_futures/linear_swap/restful/response/account/SwapFinancialRecordResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::SwapFinancialRecordResponse SwapFinancialRecordResponse;

#include "huobi_futures/linear_swap/restful/response/account/SwapLeverPositionLimitResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::SwapLeverPositionLimitResponse SwapLeverPositionLimitResponse;

#include "huobi_futures/linear_swap/restful/response/account/SwapSubAuthListResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::SwapSubAuthListResponse SwapSubAuthListResponse;

#include "huobi_futures/linear_swap/restful/response/account/SwapAccountBalanceResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::SwapAccountBalanceResponse SwapAccountBalanceResponse;

#include "huobi_futures/linear_swap/restful/response/account/SwapMultiAssetsMarginResponse.hpp"
typedef huobi_futures::linear_swap::restful::response_account::SwapMultiAssetsMarginResponse SwapMultiAssetsMarginResponse;

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace restful
        {
            class AccountClient
            {

            public:
                AccountClient(const string &access_key, const string &secret_key, const string &host = utils::DEFAULT_HOST)
                {
                    pb = std::make_shared<url_base::PrivateUrlBuilder>(access_key, secret_key, host);
                }

                std::shared_ptr<GetBalanceValuationResponse> GetBalanceValuation(const string &valuation_asset = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_balance_valuation";

                    // option
                    stringstream content;
                    if (valuation_asset != "")
                    {
                        content << ",\"valuation_asset\":\"" << valuation_asset << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetBalanceValuationResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetAccountInfoResponse> IsolatedGetAccountInfo(const string &contract_code = "", int sub_uid = 0)
                {
                    // path
                    stringstream path;
                    if (sub_uid == 0)
                    {
                        path << "/linear-swap-api/v1/swap_account_info";
                    }
                    else
                    {
                        path << "/linear-swap-api/v1/swap_sub_account_info";
                    }

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (sub_uid != 0)
                    {
                        content << ",\"sub_uid\":" << sub_uid;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetAccountInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetAccountInfoResponse> CrossGetAccountInfo(const string &margin_account = "USDT", int sub_uid = 0)
                {
                    // path
                    stringstream path;
                    if (sub_uid == 0)
                    {
                        path << "/linear-swap-api/v1/swap_cross_account_info";
                    }
                    else
                    {
                        path << "/linear-swap-api/v1/swap_sub_account_info";
                    }

                    // option
                    stringstream content;
                    if (margin_account != "")
                    {
                        content << ",\"margin_account\":\"" << margin_account << "\"";
                    }
                    if (sub_uid != 0)
                    {
                        content << ",\"sub_uid\":" << sub_uid;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetAccountInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetPositionInfoResponse> IsolatedGetPositionInfo(const string &contract_code = "", int sub_uid = 0)
                {
                    // path
                    stringstream path;
                    if (sub_uid == 0)
                    {
                        path << "/linear-swap-api/v1/swap_position_info";
                    }
                    else
                    {
                        path << "/linear-swap-api/v1/swap_sub_position_info";
                    }

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (sub_uid != 0)
                    {
                        content << ",\"sub_uid\":" << sub_uid;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetPositionInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetPositionInfoResponse> CrossGetPositionInfo(const string &contract_code = "",
                                                                              const string &pair = "",
                                                                              const string &contract_type = "",
                                                                              int sub_uid = 0)
                {
                    // path
                    stringstream path;
                    if (sub_uid == 0)
                    {
                        path << "/linear-swap-api/v1/swap_cross_position_info";
                    }
                    else
                    {
                        path << "/linear-swap-api/v1/swap_cross_sub_position_info";
                    }

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
                    }
                    if (sub_uid != 0)
                    {
                        content << ",\"sub_uid\":" << sub_uid;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetPositionInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetAccountPositionResponse> IsolatedGetAccountPosition(const string &contract_code)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_account_position_info";

                    // option
                    stringstream content;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetAccountPositionResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetAccountPositionSingleResponse> CrossGetAccountPosition(const string &margin_account)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_account_position_info";

                    // option
                    stringstream content;
                    if (margin_account != "")
                    {
                        content << ",\"margin_account\":\"" << margin_account << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetAccountPositionSingleResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SetSubAuthResponse> SetSubAuth(const string &sub_uid, int sub_auth)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_sub_auth";

                    // option
                    stringstream content;
                    content << ",\"sub_uid\":\"" << sub_uid << "\"";
                    content << ",\"sub_auth\":" << sub_auth;

                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<SetSubAuthResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetSubAccountListResponse> IsolatedGetSubAccountList(const string &contract_code = "",
                                                                                     const string &direct = "",
                                                                                     long from_id = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_sub_account_list";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetSubAccountListResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetSubAccountListResponse> CrossGetSubAccountList(const string &margin_account = "",
                                                                                  const string &direct = "",
                                                                                  long from_id = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_sub_account_list";

                    // option
                    stringstream content;
                    if (margin_account != "")
                    {
                        content << ",\"margin_account\":\"" << margin_account << "\"";
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
                    }
                    if (from_id != "")
                    {
                        content << ",\"from_id\":\"" << from_id << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetSubAccountListResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetSubAccountInfoListResponse> IsolatedGetSubAccountInfoList(const string &contract_code = "",
                                                                                             int page_index = 0, int page_size = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_sub_account_info_list";

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

                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<GetSubAccountInfoListResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetSubAccountInfoListResponse> CrossGetSubAccountInfoList(const string &margin_account = "",
                                                                                          int page_index = 0, int page_size = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_sub_account_info_list";

                    // option
                    stringstream content;
                    if (margin_account != "")
                    {
                        content << ",\"margin_account\":\"" << margin_account << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetSubAccountInfoListResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetFinancialRecordResponse> GetFinancialRecord(const string &margin_account, const string &contract_code = "",
                                                                               const string &type = "", int create_date = 0,
                                                                               int page_index = 0, int page_size = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_financial_record";

                    // option
                    stringstream content;
                    content << ",\"margin_account\":\"" << margin_account << "\"";
                    if (margin_account != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (type != "")
                    {
                        content << ",\"type\":\"" << type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetFinancialRecordResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetFinancialRecordExactResponse> GetFinancialRecordExact(const string &margin_account, const string &contract_code = "",
                                                                                         const string &type = "", long start_time = 0, long end_time = 0,
                                                                                         long from_id = 0, int size = 0, const string &direct = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_financial_record_exact";

                    // option
                    stringstream content;
                    content << ",\"margin_account\":\"" << margin_account << "\"";
                    if (margin_account != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (type != "")
                    {
                        content << ",\"type\":\"" << type << "\"";
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
                    if (size != 0)
                    {
                        content << ",\"size\":" << size;
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetFinancialRecordExactResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<IsolatedGetUserSettlementRecordsResponse> IsolatedGetUserSettlementRecords(const string &contract_code,
                                                                                                           long start_time = 0, long end_time = 0,
                                                                                                           int page_index = 0, int page_size = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_user_settlement_records";

                    // option
                    stringstream content;
                    content << ",\"contract_code\":\"" << contract_code << "\"";
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
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
                    auto result = url_base::HttpRequest::Instance().Post<IsolatedGetUserSettlementRecordsResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<CrossGetUserSettlementRecordsResponse> CrossGetUserSettlementRecords(const string &margin_account,
                                                                                                     long start_time = 0, long end_time = 0,
                                                                                                     int page_index = 0, int page_size = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_user_settlement_records";

                    // option
                    stringstream content;
                    content << ",\"margin_account\":\"" << margin_account << "\"";
                    if (start_time != 0)
                    {
                        content << ",\"start_time\":" << start_time;
                    }
                    if (end_time != 0)
                    {
                        content << ",\"end_time\":" << end_time;
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
                    auto result = url_base::HttpRequest::Instance().Post<CrossGetUserSettlementRecordsResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetAvailableLevelRateResponse> IsolatedGetAvailableLevelRate(const string &contract_code = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_available_level_rate";

                    // option
                    stringstream content;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetAvailableLevelRateResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetAvailableLevelRateResponse> CrossGetAvailableLevelRate(const string &contract_code = "",
                                                                                          const string &pair = "",
                                                                                          const string &contract_type = "",
                                                                                          const string &business_type = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_available_level_rate";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
                    }
                    if (business_type != "")
                    {
                        content << ",\"business_type\":\"" << business_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetAvailableLevelRateResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetOrderLimitResponse> GetOrderLimit(const string &order_price_type, const string &contract_code = "",
                                                                     const string &pair, const string &contract_type,
                                                                     const string &business_type)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_order_limit";

                    // option
                    stringstream content;
                    content << ",\"order_price_type\":\"" << order_price_type << "\"";
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
                    }
                    if (business_type != "")
                    {
                        content << ",\"business_type\":\"" << business_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetOrderLimitResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetFeeResponse> GetFee(const string &contract_code = "", const string &pair,
                                                       const string &contract_type, const string &business_type)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_fee";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
                    }
                    if (business_type != "")
                    {
                        content << ",\"business_type\":\"" << business_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetFeeResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetTransferLimitResponse> IsolatedGetTransferLimit(const string &contract_code = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_transfer_limit";

                    // option
                    stringstream content;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetTransferLimitResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetTransferLimitResponse> CrossGetTransferLimit(const string &margin_account = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_transfer_limit";

                    // option
                    stringstream content;
                    if (margin_account != "")
                    {
                        content << ",\"margin_account\":\"" << margin_account << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetTransferLimitResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetPositionLimitResponse> IsolatedGetPositionLimit(const string &contract_code = "")
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_position_limit";

                    // option
                    stringstream content;
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
                    auto result = url_base::HttpRequest::Instance().Post<GetPositionLimitResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetPositionLimitResponse> CrossGetPositionLimit(const string &contract_code = "", const string &pair,
                                                                                const string &contract_type, const string &business_type)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_position_limit";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
                    }
                    if (business_type != "")
                    {
                        content << ",\"business_type\":\"" << business_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetPositionLimitResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<MasterSubTransferResponse> MasterSubTransfer(const string &sub_uid, const string &asset,
                                                                             const string &from_margin_account, const string &to_margin_account,
                                                                             float amount, const string &type, long client_order_id)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_master_sub_transfer";

                    // option
                    stringstream content;
                    content << ",\"sub_uid\":\"" << sub_uid << "\""
                            << ",\"asset\":\"" << asset << "\"";
                    content << ",\"from_margin_account\":\"" << from_margin_account << "\""
                            << ",\"to_margin_account\":\"" << to_margin_account << "\"";
                    content << ",\"amount\":" << amount << ",\"type\":\"" << type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<MasterSubTransferResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetMasterSubTransferRecordResponse> GetMasterSubTransferRecord(const string &margin_account, int create_date,
                                                                                               const string &transfer_type = "",
                                                                                               int page_index = 0, int page_size = 0)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_master_sub_transfer_record";

                    // option
                    stringstream content;
                    content << ",\"margin_account\":\"" << margin_account << "\""
                            << ",\"create_date\":" << create_date;
                    if (transfer_type != "")
                    {
                        content << ",\"transfer_type\":\"" << transfer_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<GetMasterSubTransferRecordResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<TransferInnerRecordResponse> TransferInner(const string &asset,
                                                                           const string &from_margin_account, const string &to_margin_account,
                                                                           float amount, long client_order_id)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_transfer_inner";

                    // option
                    stringstream content;
                    content << ",\"asset\":\"" << asset << "\"";
                    content << ",\"from_margin_account\":\"" << from_margin_account << "\""
                            << ",\"to_margin_account\":\"" << to_margin_account << "\"";
                    content << ",\"amount\":" << amount;
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
                    auto result = url_base::HttpRequest::Instance().Post<TransferInnerRecordResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<GetApiTradingStatusResponse> GetApiTradingStatus()
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_api_trading_status";

                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<GetApiTradingStatusResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapCrossSubAccountInfoResponse> SwapCrossSubAccountInfo(const string &margin_account, long sub_uid)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_sub_account_info";

                    // option
                    stringstream content;
                    content << ",\"sub_uid\":" << sub_uid;
                    if (margin_account != "")
                    {
                        content << ",\"margin_account\":\"" << margin_account << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapCrossSubAccountInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapFinancialRecordResponse> SwapFinancialRecord(const string &contract, const string &mar_acct,
                                                                                 const string &type, long start_time,
                                                                                 long end_time, const string &direct,
                                                                                 long from_id)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/swap_financial_record";

                    // option
                    stringstream content;
                    if (contract != "")
                    {
                        content << ",\"contract\":\"" << contract << "\"";
                    }
                    if (mar_acct != "")
                    {
                        content << ",\"mar_acct\":\"" << mar_acct << "\"";
                    }
                    if (type != "")
                    {
                        content << ",\"type\":\"" << type << "\"";
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapFinancialRecordResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapFinancialRecordResponse> SwapFinancialRecord(const string &contract, const string &mar_acct,
                                                                                 const string &type, long start_time,
                                                                                 long end_time, const string &direct,
                                                                                 long from_id)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v3/swap_financial_record";

                    // option
                    stringstream content;
                    if (contract != "")
                    {
                        content << ",\"contract\":\"" << contract << "\"";
                    }
                    if (mar_acct != "")
                    {
                        content << ",\"mar_acct\":\"" << mar_acct << "\"";
                    }
                    if (type != "")
                    {
                        content << ",\"type\":\"" << type << "\"";
                    }
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapFinancialRecordResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapLeverPositionLimitResponse> SwapLeverPositionLimit(const string &contract_code, int lever_rate)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_lever_position_limit";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (lever_rate != 0)
                    {
                        content << ",\"lever_rate\":" << lever_rate;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapLeverPositionLimitResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapCrossLeverPositionLimitResponse> SwapCrossLeverPositionLimit(const string &business_type,
                                                                                                 const string &contract_type,
                                                                                                 const string &pair,
                                                                                                 const string &contract_code,
                                                                                                 int lever_rate)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_cross_lever_position_limit";

                    // option
                    stringstream content;
                    if (business_type != "")
                    {
                        content << ",\"business_type\":\"" << business_type << "\"";
                    }
                    if (contract_type != "")
                    {
                        content << ",\"contract_type\":\"" << contract_type << "\"";
                    }
                    if (pair != "")
                    {
                        content << ",\"pair\":\"" << pair << "\"";
                    }

                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (lever_rate != 0)
                    {
                        content << ",\"lever_rate\":" << lever_rate;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapCrossLeverPositionLimitResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapSubAuthListResponse> SwapSubAuthList(const string &sub_uid,
                                                                         const string &direct,
                                                                         long start_time,
                                                                         long end_time,
                                                                         long from_id)
                {
                    // path
                    stringstream path;
                    path << "/linear-swap-api/v1/swap_sub_auth_list";
                    // option
                    stringstream option;
                    if (sub_uid != "") {
                        option << "&sub_uid=" << sub_uid;
                    }
                    if (direct != "") {
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
                    auto result = url_base::HttpRequest::Instance().Get<SwapSubAuthListResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapAccountBalanceResponse> SwapAccountBalance()
                {
                    // path
                    stringstream path;
                    path << "/v5/account/balance";
                    // option
                    stringstream option;

                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<SwapAccountBalanceResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapMultiAssetsMarginResponse> SwapMultiAssetsMargin(int assets_mode)
                {
                    // path
                    stringstream path;
                    path << "/v5/account/multi_assets_margin";

                    // option
                    stringstream content;
                    if (assets_mode != "")
                    {
                        content << ",\"assets_mode\":\"" << assets_mode << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapMultiAssetsMarginResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<InviteeRebateAllRebateDetailResponse> InviteeRebateAllRebateDetail(const string &direct,
                                                                                         const string &fromId,
                                                                                         long limit)
                {
                    // path
                    stringstream path;
                    path << "/v2/invitee/rebate/all_rebate/detail";
                    // option
                    stringstream option;
                    if (direct != "") {
                        option << "&direct=" << direct;
                    }
                    if (fromId != "") {
                        option << "&fromId=" << fromId;
                    }
                    if (limit != 0)
                    {
                        option << "&limit=" << limit;
                    }
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<InviteeRebateAllRebateDetailResponse>(url);
                    return result;
                }

                std::shared_ptr<InviteeRebateBatcherRebateDetailResponse> InviteeRebateBatcherRebateDetail(const string &inviteeUidList)
                {
                    // path
                    stringstream path;
                    path << "/v2/invitee/rebate/batcher_rebate/detail";
                    // option
                    stringstream option;
                    if (inviteeUidList != "") {
                        option << "&inviteeUidList=" << inviteeUidList;
                    }
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<InviteeRebateBatcherRebateDetailResponse>(url);
                    return result;
                }

                std::shared_ptr<FeeDeductionCurrencyResponse> FeeDeductionCurrency(const string &deduction_currency, int fee_option)
                {
                    // path
                    stringstream path;
                    path << "/v5/account/fee_deduction_currency";
                    // option
                    stringstream option;
                    if (deduction_currency != "") {
                        option << "&deduction_currency=" << deduction_currency;
                    }
                    option << "&fee_option=" << fee_option;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<FeeDeductionCurrencyResponse>(url);
                    return result;
                }

                std::shared_ptr<QueryEarnProjectListResponse> QueryEarnProjectList(const string &currency, int pageNum, int pageSize)
                {
                    // path
                    stringstream path;
                    path << "/v1/earn/project/queryEarnProjectList";
                    // option
                    stringstream option;
                    if (currency != "") {
                        option << "&currency=" << currency;
                    }
                    option << "&pageNum=" << pageNum;
                    option << "&pageSize=" << pageSize;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<QueryEarnProjectListResponse>(url);
                    return result;
                }

                std::shared_ptr<EarnOrderDemandAddResponse> EarnOrderDemandAdd(int id, int amount, string requestId)
                {
                    // path
                    stringstream path;
                    path << "/v1/earn/order/demand/add";
                    // option
                    stringstream option;
                    if (requestId != "") {
                        option << "&requestId=" << requestId;
                    }
                    option << "&id=" << id;
                    option << "&amount=" << amount;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<EarnOrderDemandAddResponse>(url);
                    return result;
                }

                std::shared_ptr<EarnOrderDemandRedeemOrderResponse> EarnOrderDemandRedeemOrder(int orderId, int amount, string requestId)
                {
                    // path
                    stringstream path;
                    path << "/v1/earn/order/demand/redeem-order";
                    // option
                    stringstream option;
                    if (requestId != "") {
                        option << "&requestId=" << requestId;
                    }
                    option << "&orderId=" << orderId;
                    option << "&amount=" << amount;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<EarnOrderDemandRedeemOrderResponse>(url);
                    return result;
                }

                std::shared_ptr<EarnOrderUserAssetsListResponse> EarnOrderUserAssetsList(const string &currency, int pageNum, int pageSize, int projectType)
                {
                    // path
                    stringstream path;
                    path << "/v1/earn/order/user/assets/list";
                    // option
                    stringstream option;
                    if (currency != "") {
                        option << "&currency=" << currency;
                    }
                    option << "&pageNum=" << pageNum;
                    option << "&pageSize=" << pageSize;
                    option << "&projectType=" << projectType;
                    if (!option.str().empty())
                    {
                        path << "?" << option.str();
                    }
                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Get<EarnOrderUserAssetsListResponse>(url);
                    return result;
                }

            private:
                std::shared_ptr<url_base::PrivateUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures
