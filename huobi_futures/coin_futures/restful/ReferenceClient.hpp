#pragma once

#include <future>
#include <sstream>
using std::stringstream;

#include "huobi_futures/url_base/PublicUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/coin_futures/restful/response/reference/ContractAdjustFactorResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractAdjustFactorResponse ContractAdjustFactorResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractApiStateResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractApiStateResponse ContractApiStateResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractContractInfoResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractContractInfoResponse ContractContractInfoResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractDeliveryPriceResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractDeliveryPriceResponse ContractDeliveryPriceResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractEliteAccountRatioResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractEliteAccountRatioResponse ContractEliteAccountRatioResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractElitePositionRatioResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractElitePositionRatioResponse ContractElitePositionRatioResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractEstimatedSettlementPriceResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractEstimatedSettlementPriceResponse ContractEstimatedSettlementPriceResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractHisOpenInterestResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractHisOpenInterestResponse ContractHisOpenInterestResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractIndexResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractIndexResponse ContractIndexResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractInsuranceFundResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractInsuranceFundResponse ContractInsuranceFundResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractLadderMarginResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractLadderMarginResponse ContractLadderMarginResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractLiquidationOrdersResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractLiquidationOrdersResponse ContractLiquidationOrdersResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractOpenInterestResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractOpenInterestResponse ContractOpenInterestResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractPriceLimitResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractPriceLimitResponse ContractPriceLimitResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractQueryElementsResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractQueryElementsResponse ContractQueryElementsResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractRiskInfoResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractRiskInfoResponse ContractRiskInfoResponse;

#include "huobi_futures/coin_futures/restful/response/reference/ContractSettlementRecordsResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_reference::ContractSettlementRecordsResponse ContractSettlementRecordsResponse;


namespace huobi_futures
{
    namespace coin_futures
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

                std::shared_ptr<ContractRiskInfoResponse> ContractRiskInfo(const string &symbol = "")
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_risk_info";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "symbol=" << symbol;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<ContractRiskInfoResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractInsuranceFundResponse> ContractInsuranceFund(const string &symbol = "")
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_insurance_fund";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "symbol=" << symbol;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<ContractInsuranceFundResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractAdjustFactorResponse> ContractAdjustFactor(const string &symbol = "")
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_adjustfactor";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "symbol=" << symbol;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<ContractAdjustFactorResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractHisOpenInterestResponse> ContractHisOpenInterest(const string &symbol, const string &contract_type,
                                                                                         const string &period, int size, int amount_type)
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_his_open_interest";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "&symbol=" << symbol;
                    }
                    if (contract_type != "")
                    {
                        option << "&contract_type=" << contract_type;
                    }
                    if (period != "")
                    {
                        option << "&period=" << period;
                    }
                    if (size != 0)
                    {
                        option << "&size=" << size;
                    }
                    if (amount_type != 0)
                    {
                        option << "&amount_type=" << amount_type;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<ContractHisOpenInterestResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractLadderMarginResponse> ContractLadderMargin(const string &symbol)
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_ladder_margin";

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

                    auto result = url_base::HttpRequest::Instance().Get<ContractLadderMarginResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractEliteAccountRatioResponse> ContractEliteAccountRatio(const string &symbol, const string &period)
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_elite_account_ratio";

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
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<ContractEliteAccountRatioResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractElitePositionRatioResponse> ContractElitePositionRatio(const string &symbol, const string &period)
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_elite_position_ratio";

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
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<ContractElitePositionRatioResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractLiquidationOrdersResponse> ContractLiquidationOrders(const string &symbol, const string &direct,
                                                                                             int trade_type, long start_time,
                                                                                             long end_time, long from_id)
                {
                    // location
                    stringstream location;
                    location << "/api/v3/contract_liquidation_orders";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "&symbol=" << symbol;
                    }
                    if (direct != "")
                    {
                        option << "&direct=" << direct;
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
                    if (from_id != 0)
                    {
                        option << "&from_id=" << from_id;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<ContractLiquidationOrdersResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractSettlementRecordsResponse> ContractSettlementRecords(const string &symbol, long start_time,
                                                                                             long end_time, int page_index, int page_size)
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_settlement_records";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "&symbol=" << symbol;
                    }
                    if (start_time != 0)
                    {
                        option << "&start_time=" << start_time;
                    }
                    if (end_time != 0)
                    {
                        option << "&end_time=" << end_time;
                    }
                    if (page_index != 0)
                    {
                        option << "&page_index=" << page_index;
                    }
                    if (page_size != 0)
                    {
                        option << "&page_size=" << page_size;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<ContractSettlementRecordsResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractPriceLimitResponse> ContractPriceLimit(const string &symbol,
                                                                                      const string &contract_type,
                                                                                      const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_price_limit";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "&symbol=" << symbol;
                    }
                    if (contract_type != "")
                    {
                        option << "&contract_type=" << contract_type;
                    }
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<ContractPriceLimitResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractOpenInterestResponse> ContractOpenInterest(const string &symbol,
                                                                               const string &contract_type,
                                                                               const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_open_interest";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "&symbol=" << symbol;
                    }
                    if (contract_type != "")
                    {
                        option << "&contract_type=" << contract_type;
                    }
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<ContractOpenInterestResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractDeliveryPriceResponse> ContractDeliveryPrice(const string &symbol)
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_delivery_price";

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

                    auto result = url_base::HttpRequest::Instance().Get<ContractDeliveryPriceResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractEstimatedSettlementPriceResponse> ContractEstimatedSettlementPrice(const string &symbol)
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_estimated_settlement_price";

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

                    auto result = url_base::HttpRequest::Instance().Get<ContractEstimatedSettlementPriceResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractApiStateResponse> ContractApiState(const string &symbol)
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_api_state";

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

                    auto result = url_base::HttpRequest::Instance().Get<ContractApiStateResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractContractInfoResponse> ContractContractInfo(const string &symbol, const string &contract_type, const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_contract_info";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "&symbol=" << symbol;
                    }
                    if (contract_type != "")
                    {
                        option << "&contract_type=" << contract_type;
                    }
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<ContractContractInfoResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractIndexResponse> ContractIndex(const string &symbol)
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_index";

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

                    auto result = url_base::HttpRequest::Instance().Get<ContractIndexResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractQueryElementsResponse> ContractQueryElements(const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_query_elements";

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

                    auto result = url_base::HttpRequest::Instance().Get<ContractQueryElementsResponse>(url);
                    return result;
                }

                std::shared_ptr<ContractQueryElementsResponse> ContractQueryElements(const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/api/v1/contract_query_elements";

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

                    auto result = url_base::HttpRequest::Instance().Get<ContractQueryElementsResponse>(url);
                    return result;
                }

            private:
                std::shared_ptr<url_base::PublicUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures