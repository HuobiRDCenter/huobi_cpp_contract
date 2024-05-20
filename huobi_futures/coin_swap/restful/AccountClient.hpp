#pragma once

#include <future>
#include <sstream>

#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/coin_swap/restful/response/account/SwapAccountInfoResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapAccountInfoResponse SwapAccountInfoResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapAccountPositionInfoResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapAccountPositionInfoResponse SwapAccountPositionInfoResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapApiTradingStatusResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapApiTradingStatusResponse SwapApiTradingStatusResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapAvailableLevelRateResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapAvailableLevelRateResponse SwapAvailableLevelRateResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapBalanceValuationResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapBalanceValuationResponse SwapBalanceValuationResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapFeeResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapFeeResponse SwapFeeResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapFinancialRecordV3Response.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapFinancialRecordV3Response SwapFinancialRecordV3Response;

#include "huobi_futures/coin_swap/restful/response/account/ContractMasterSubTransferRecordResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::ContractMasterSubTransferRecordResponse ContractMasterSubTransferRecordResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapMasterSubTransferResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapMasterSubTransferResponse SwapMasterSubTransferResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapOrderLimitResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapOrderLimitResponse SwapOrderLimitResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapPositionInfoResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapPositionInfoResponse SwapPositionInfoResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapPositionLimitResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapPositionLimitResponse SwapPositionLimitResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapSubAccountInfoListResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapSubAccountInfoListResponse SwapSubAccountInfoListResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapSubAccountInfoResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapSubAccountInfoResponse SwapSubAccountInfoResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapSubAccountListResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapSubAccountListResponse SwapSubAccountListResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapSubAuthListResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapSubAuthListResponse SwapSubAuthListResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapSubAuthResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapSubAuthResponse SwapSubAuthResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapSubPositionInfoResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapSubPositionInfoResponse SwapSubPositionInfoResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapTransferLimitResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapTransferLimitResponse SwapTransferLimitResponse;

#include "huobi_futures/coin_swap/restful/response/account/SwapUserSettlementRecordsResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_account::SwapUserSettlementRecordsResponse SwapUserSettlementRecordsResponse;


namespace huobi_futures
{
    namespace coin_swap
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

                std::shared_ptr<SwapBalanceValuationResponse> SwapBalanceValuation(const string &valuation_asset = "")
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_balance_valuation";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapBalanceValuationResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapAccountInfoResponse> SwapAccountInfo(const string &contract_code = "")
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_account_info";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapAccountInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapPositionInfoResponse> SwapPositionInfo(const string &contract_code = "")
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_position_info";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapPositionInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapSubAuthResponse> SwapSubAuth(const string &sub_uid = "", int sub_auth)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_sub_auth";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
                    }
                    if (sub_auth != 0)
                    {
                        content << ",\"sub_auth\":" << symbol;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapSubAuthResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapSubAuthListResponse> SwapSubAuthList(const string &sub_uid = "", const string &direct = "",
                                                                                       long start_time, long end_time, long from_id)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_sub_auth_list";

                    // option
                    stringstream content;
                    if (sub_uid != "")
                    {
                        content << ",\"sub_uid\":\"" << sub_uid << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapSubAuthListResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapSubAccountListResponse> SwapSubAccountList(const string &contract_code = "", const string &direct = "",
                                                                         long from_id)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_sub_account_list";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapSubAccountListResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapSubAccountInfoListResponse> SwapSubAccountInfoList(const string &contract_code = "",
                                                                                               int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_sub_account_info_list";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapSubAccountInfoListResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapSubAccountInfoResponse> SwapSubAccountInfo(const string &contract_code = "",
                                                                                       long sub_uid)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_sub_account_info";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapSubAccountInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapSubPositionInfoResponse> SwapSubPositionInfo(const string &contract_code = "",
                                                                                       long sub_uid)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_sub_position_info";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapSubPositionInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapFinancialRecordV3Response> SwapFinancialRecord(long start_time, long end_time, const string &direct,
                                                                                         long from_id, const string &type, const string &symbol)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v3/swap_financial_record";

                    // option
                    stringstream content;
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
                    }
                    if (type != "")
                    {
                        content << ",\"type\":\"" << type << "\"";
                    }
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapFinancialRecordV3Response>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapFinancialRecordV3Response> SwapFinancialRecordExact(long start_time, long end_time, const string &direct,
                                                                                         long from_id, const string &type, const string &contract)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v3/swap_financial_record_exact";

                    // option
                    stringstream content;
                    if (direct != "")
                    {
                        content << ",\"direct\":\"" << direct << "\"";
                    }
                    if (type != "")
                    {
                        content << ",\"type\":\"" << type << "\"";
                    }
                    if (contract != "")
                    {
                        content << ",\"contract\":\"" << contract << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapFinancialRecordV3Response>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapUserSettlementRecordsResponse> SwapUserSettlementRecords(const string &contract_code,
                                                                                                     long start_time, long end_time,
                                                                                                     int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_user_settlement_records";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapUserSettlementRecordsResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapOrderLimitResponse> SwapOrderLimit(const string &contract_code, const string &order_price_type)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_order_limit";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (order_price_type != "")
                    {
                        content << ",\"order_price_type\":\"" << order_price_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapOrderLimitResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapFeeResponse> SwapFee(const string &contract_code)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_fee";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapFeeResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapTransferLimitResponse> SwapTransferLimit(const string &contract_code)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_transfer_limit";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapTransferLimitResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapPositionLimitResponse> SwapPositionLimit(const string &contract_code)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_position_limit";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapPositionLimitResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapAccountPositionInfoResponse> SwapAccountPositionInfo(const string &contract_code)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_account_position_info";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapAccountPositionInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapMasterSubTransferResponse> SwapMasterSubTransfer(const string &contract_code, const string &type,
                                                                                             long sub_uid, float amount, long client_order_id)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_master_sub_transfer";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (type != "")
                    {
                        content << ",\"type\":\"" << type << "\"";
                    }
                    if (sub_uid != 0)
                    {
                        content << ",\"sub_uid\":" << sub_uid;
                    }
                    if (amount != 0.0)
                    {
                        content << ",\"amount\":" << amount;
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapMasterSubTransferResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapMasterSubTransferRecordResponse> SwapMasterSubTransferRecord(const string &contract_code, const string &transfer_type,
                                                                                                         int create_date, int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_master_sub_transfer_record";

                    // option
                    stringstream content;
                    if (contract_code != "")
                    {
                        content << ",\"contract_code\":\"" << contract_code << "\"";
                    }
                    if (transfer_type != "")
                    {
                        content << ",\"transfer_type\":\"" << transfer_type << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<SwapMasterSubTransferRecordResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapApiTradingStatusResponse> SwapApiTradingStatus()
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_api_trading_status";

                    // option
                    stringstream content;

                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("GET", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<SwapApiTradingStatus>(url, data.str());
                    return result;
                }

                std::shared_ptr<SwapAvailableLevelRateResponse> SwapAvailableLevelRate(const string &contract_code)
                {
                    // path
                    stringstream path;
                    path << "/swap-api/v1/swap_available_level_rate";

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
                    auto result = url_base::HttpRequest::Instance().Post<SwapAvailableLevelRateResponse>(url, data.str());
                    return result;
                }

            private:
                std::shared_ptr<url_base::PrivateUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures
