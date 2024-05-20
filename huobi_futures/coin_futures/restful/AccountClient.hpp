#pragma once

#include <future>
#include <sstream>

#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/coin_futures/restful/response/account/ContractAccountInfoResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractAccountInfoResponse ContractAccountInfoResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractAccountPositionInfoResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractAccountPositionInfoResponse ContractAccountPositionInfoResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractApiTradingStatusResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractApiTradingStatusResponse ContractApiTradingStatusResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractAvailableLevelRateResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractAvailableLevelRateResponse ContractAvailableLevelRateResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractBalanceValuationResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractBalanceValuationResponse ContractBalanceValuationResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractFeeResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractFeeResponse ContractFeeResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractFinancialRecordResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractFinancialRecordResponse ContractFinancialRecordResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractMasterSubTransferRecordResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractMasterSubTransferRecordResponse ContractMasterSubTransferRecordResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractMasterSubTransferResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractMasterSubTransferResponse ContractMasterSubTransferResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractOrderLimitResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractOrderLimitResponse ContractOrderLimitResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractPositionInfoResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractPositionInfoResponse ContractPositionInfoResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractPositionLimitResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractPositionLimitResponse ContractPositionLimitResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractSubAccountInfoListResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractSubAccountInfoListResponse ContractSubAccountInfoListResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractSubAccountInfoResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractSubAccountInfoResponse ContractSubAccountInfoResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractSubAccountListResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractSubAccountListResponse ContractSubAccountListResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractSubAuthResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractSubAuthResponse ContractSubAuthResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractSubPositionInfoResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractSubPositionInfoResponse ContractSubPositionInfoResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractTransferLimitResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractTransferLimitResponse ContractTransferLimitResponse;

#include "huobi_futures/coin_futures/restful/response/account/ContractUserSettlementRecordsResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_account::ContractUserSettlementRecordsResponse ContractUserSettlementRecordsResponse;


namespace huobi_futures
{
    namespace coin_futures
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

                std::shared_ptr<ContractBalanceValuationResponse> ContractBalanceValuation(const string &valuation_asset = "")
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_balance_valuation";

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
                    auto result = url_base::HttpRequest::Instance().Post<ContractBalanceValuationResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractAccountInfoResponse> ContractAccountInfo(const string &symbol = "")
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_account_info";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractAccountInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractPositionInfoResponse> ContractPositionInfo(const string &symbol = "")
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_position_info";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractPositionInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractSubAuthResponse> ContractSubAuth(const string &sub_uid = "", int sub_auth)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_sub_auth";

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
                    auto result = url_base::HttpRequest::Instance().Post<ContractSubAuthResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractSubAccountListResponse> ContractSubAccountList(const string &symbol = "", const string &direct = "",
                                                                                       long from_id)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_sub_account_list";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractSubAccountListResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractSubAccountInfoListResponse> ContractSubAccountInfoList(const string &symbol = "",
                                                                                               int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_sub_account_info_list";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractSubAccountInfoListResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractSubAccountInfoResponse> ContractSubAccountInfo(const string &symbol = "",
                                                                                       long sub_uid)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_sub_account_info";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractSubAccountInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractSubPositionInfoResponse> ContractSubPositionInfo(const string &symbol = "",
                                                                                       long sub_uid)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_sub_position_info";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractSubPositionInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractFinancialRecordResponse> ContractFinancialRecord(long start_time, long end_time, const string &direct,
                                                                                         long from_id, const string &type, const string &symbol)
                {
                    // path
                    stringstream path;
                    path << "/api/v3/contract_financial_record";

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
                    auto result = url_base::HttpRequest::Instance().Post<ContractFinancialRecordResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractFinancialRecordResponse> ContractFinancialRecordExact(long start_time, long end_time, const string &direct,
                                                                                         long from_id, const string &type, const string &symbol)
                {
                    // path
                    stringstream path;
                    path << "/api/v3/contract_financial_record_exact";

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
                    auto result = url_base::HttpRequest::Instance().Post<ContractFinancialRecordResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractUserSettlementRecordsResponse> ContractUserSettlementRecords(const string &symbol,
                                                                                                     long start_time, long end_time,
                                                                                                     int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_user_settlement_records";

                    // option
                    stringstream content;
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractUserSettlementRecordsResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractOrderLimitResponse> ContractOrderLimit(const string &symbol, const string &order_price_type)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_order_limit";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractOrderLimitResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractFeeResponse> ContractFee(const string &symbol)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_fee";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractFeeResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractTransferLimitResponse> ContractTransferLimit(const string &symbol)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_transfer_limit";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractTransferLimitResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractPositionLimitResponse> ContractPositionLimit(const string &symbol)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_position_limit";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractPositionLimitResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractAccountPositionInfoResponse> ContractAccountPositionInfo(const string &symbol)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_account_position_info";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractAccountPositionInfoResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractMasterSubTransferResponse> ContractMasterSubTransfer(const string &symbol, const string &type,
                                                                                             long sub_uid, float amount, long client_order_id)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_master_sub_transfer";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractMasterSubTransferResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractMasterSubTransferRecordResponse> ContractMasterSubTransferRecord(const string &symbol, const string &transfer_type,
                                                                                                         int create_date, int page_index, int page_size)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_master_sub_transfer_record";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractMasterSubTransferRecordResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractApiTradingStatusResponse> ContractApiTradingStatus()
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_api_trading_status";

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
                    auto result = url_base::HttpRequest::Instance().Post<ContractApiTradingStatusResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<ContractAvailableLevelRateResponse> ContractAvailableLevelRate(const string &symbol)
                {
                    // path
                    stringstream path;
                    path << "/api/v1/contract_available_level_rate";

                    // option
                    stringstream content;
                    if (symbol != "")
                    {
                        content << ",\"symbol\":\"" << symbol << "\"";
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
                    auto result = url_base::HttpRequest::Instance().Post<ContractAvailableLevelRateResponse>(url, data.str());
                    return result;
                }

            private:
                std::shared_ptr<url_base::PrivateUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures
