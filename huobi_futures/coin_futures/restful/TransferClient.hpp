#pragma once

#include <future>
#include <sstream>

#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"

#include "huobi_futures/coin_futures/restful/response/transfer/FuturesTransferResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_transfer::FuturesTransferResponse FuturesTransferResponse;

#include "huobi_futures/coin_futures/restful/response/transfer/TransferResponse.hpp"
typedef huobi_futures::coin_futures::restful::response_transfer::TransferResponse TransferResponse;


namespace huobi_futures
{
    namespace coin_futures
    {
        namespace restful
        {
            class TransferClient
            {

            public:
                TransferClient(const string &access_key, const string &secret_key, const string &host = "api.huobi.pro")
                {
                    pb = std::make_shared<url_base::PrivateUrlBuilder>(access_key, secret_key, host);
                }

                std::shared_ptr<TransferResponse> Transfer(const string &from, const string &to, const string &currency,
                                                           float amount, const string &margin_account)
                {
                    // path
                    stringstream path;
                    path << "/v2/account/transfer";

                    // option
                    stringstream content;
                    content << ",\"from\":\"" << from << "\""
                            << ",\"to\":\"" << to << "\""
                            << ",\"currency\":\"" << currency << "\""
                            << ",\"amount\":" << amount
                            << ",\"margin-account\":\"" << margin_account << "\"";

                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<TransferResponse>(url, data.str());
                    return result;
                }

                std::shared_ptr<FuturesTransferResponse> FuturesTransfer(const string &currency, const string &type, float amount)
                {
                    // path
                    stringstream path;
                    path << "/v1/futures/transfer";

                    // option
                    stringstream content;
                    content << ",\"currency\":\"" << currency << "\""
                            << ",\"type\":\"" << type << "\""
                            << ",\"amount\":" << amount;

                    // data
                    stringstream data;
                    if (!content.str().empty())
                    {
                        data << "{" << content.str().substr(1) << "}";
                    }

                    // url
                    string url = pb->Build("POST", path.str());

                    // post
                    auto result = url_base::HttpRequest::Instance().Post<TransferResponse>(url, data.str());
                    return result;
                }

            private:
                std::shared_ptr<url_base::PrivateUrlBuilder> pb;
            };
        } // namespace restful
    }     // namespace linear_swap
} // namespace huobi_futures
