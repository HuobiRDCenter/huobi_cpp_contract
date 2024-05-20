#pragma once

#include <future>
#include <sstream>
using std::stringstream;

#include "huobi_futures/url_base/PublicUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/coin_swap/restful/response/reference/SwapAdjustFactorResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapAdjustFactorResponse SwapAdjustFactorResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapApiStateResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapApiStateResponse SwapApiStateResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapFundingRateResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapFundingRateResponse SwapFundingRateResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapContractInfoResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapContractInfoResponse SwapContractInfoResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapEliteAccountRatioResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapEliteAccountRatioResponse SwapEliteAccountRatioResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapElitePositionRatioResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapElitePositionRatioResponse SwapElitePositionRatioResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapEstimatedSettlementPriceResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapEstimatedSettlementPriceResponse SwapEstimatedSettlementPriceResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapFundingRateResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapFundingRateResponse SwapFundingRateResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapHisOpenInterestResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapHisOpenInterestResponse SwapHisOpenInterestResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapHistoricalFundingRateResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapHistoricalFundingRateResponse SwapHistoricalFundingRateResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapIndexResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapIndexResponse SwapIndexResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapInsuranceFundResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapInsuranceFundResponse SwapInsuranceFundResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapLadderMarginResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapLadderMarginResponse SwapLadderMarginResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapLiquidationOrdersResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapLiquidationOrdersResponse SwapLiquidationOrdersResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapOpenInterestResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapOpenInterestResponse SwapOpenInterestResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapPriceLimitResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapPriceLimitResponse SwapPriceLimitResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapQueryElementsResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapQueryElementsResponse SwapQueryElementsResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapRiskInfoResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapRiskInfoResponse SwapRiskInfoResponse;

#include "huobi_futures/coin_swap/restful/response/reference/SwapSettlementRecordsResponse.hpp"
typedef huobi_futures::coin_swap::restful::response_reference::SwapSettlementRecordsResponse SwapSettlementRecordsResponse;


namespace huobi_futures
{
    namespace coin_swap
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

                std::shared_ptr<SwapRiskInfoResponse> SwapRiskInfo(const string &contract_code = "")
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_risk_info";

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

                    auto result = url_base::HttpRequest::Instance().Get<SwapRiskInfoResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapInsuranceFundResponse> SwapInsuranceFund(const string &contract_code = "", int page_index, int page_size)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_insurance_fund";

                    // option
                    stringstream option;
                    if (symbol != "")
                    {
                        option << "&symbol=" << symbol;
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

                    auto result = url_base::HttpRequest::Instance().Get<SwapInsuranceFundResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapAdjustFactorResponse> SwapAdjustFactor(const string &contract_code = "")
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_adjustfactor";

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

                    auto result = url_base::HttpRequest::Instance().Get<SwapAdjustFactorResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapHisOpenInterestResponse> SwapHisOpenInterest(const string &contract_code,
                                                                                         const string &period, int size, int amount_type)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_his_open_interest";

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
                    if (amount_type != 0)
                    {
                        option << "&amount_type=" << amount_type;
                    }
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<SwapHisOpenInterestResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapLadderMarginResponse> SwapLadderMargin(const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_ladder_margin";

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

                    auto result = url_base::HttpRequest::Instance().Get<SwapLadderMarginResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapEliteAccountRatioResponse> SwapEliteAccountRatio(const string &contract_code, const string &period)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_elite_account_ratio";

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
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<SwapEliteAccountRatioResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapElitePositionRatioResponse> SwapElitePositionRatio(const string &contract_code, const string &period)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_elite_position_ratio";

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
                    if (!option.str().empty())
                    {
                        location << "?" << option.str();
                    }

                    string url = pb->Build(location.str());

                    auto result = url_base::HttpRequest::Instance().Get<SwapElitePositionRatioResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapLiquidationOrdersResponse> SwapLiquidationOrders(const string &contract, const string &direct,
                                                                                             int trade_type, long start_time,
                                                                                             long end_time, long from_id)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v3/swap_liquidation_orders";

                    // option
                    stringstream option;
                    if (contract != "")
                    {
                        option << "&contract=" << contract;
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

                    auto result = url_base::HttpRequest::Instance().Get<SwapLiquidationOrdersResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapSettlementRecordsResponse> SwapSettlementRecords(const string &contract_code, long start_time,
                                                                                             long end_time, int page_index, int page_size)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_settlement_records";

                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
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

                    auto result = url_base::HttpRequest::Instance().Get<SwapSettlementRecordsResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapPriceLimitResponse> SwapPriceLimit(const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_price_limit";

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

                    auto result = url_base::HttpRequest::Instance().Get<SwapPriceLimitResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapOpenInterestResponse> SwapOpenInterest(const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_open_interest";

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

                    auto result = url_base::HttpRequest::Instance().Get<SwapOpenInterestResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapEstimatedSettlementPriceResponse> SwapEstimatedSettlementPrice(const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_estimated_settlement_price";

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

                    auto result = url_base::HttpRequest::Instance().Get<SwapEstimatedSettlementPriceResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapApiStateResponse> SwapApiState(const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_api_state";

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

                    auto result = url_base::HttpRequest::Instance().Get<SwapApiStateResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapContractInfoResponse> SwapContractInfo(const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_contract_info";

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

                    auto result = url_base::HttpRequest::Instance().Get<SwapContractInfoResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapIndexResponse> SwapIndex(const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_index";

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

                    auto result = url_base::HttpRequest::Instance().Get<SwapIndexResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapQueryElementsResponse> SwapQueryElements(const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_query_elements";

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

                    auto result = url_base::HttpRequest::Instance().Get<SwapQueryElementsResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapFundingRateResponse> SwapFundingRate(const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_funding_rate";

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

                    auto result = url_base::HttpRequest::Instance().Get<SwapFundingRateResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapBatchFundingRateResponse> SwapBatchFundingRate(const string &contract_code)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_batch_funding_rate";

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

                    auto result = url_base::HttpRequest::Instance().Get<SwapBatchFundingRateResponse>(url);
                    return result;
                }

                std::shared_ptr<SwapHistoricalFundingRateResponse> SwapHistoricalFundingRate(const string &contract_code, int page_index, int page_size)
                {
                    // location
                    stringstream location;
                    location << "/swap-api/v1/swap_historical_funding_rate";

                    // option
                    stringstream option;
                    if (contract_code != "")
                    {
                        option << "&contract_code=" << contract_code;
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

                    auto result = url_base::HttpRequest::Instance().Get<SwapHistoricalFundingRateResponse>(url);
                    return result;
                }

            private:
                std::shared_ptr<url_base::PublicUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures