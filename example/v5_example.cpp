// V5 接口最小示例。
//   - 公开行情接口无需 key，可直接运行；
//   - 账户/交易接口需要环境变量：export HTX_ACCESS_KEY=xxx HTX_SECRET_KEY=xxx
// 完整接口清单见 docs/v5-interface-list.md。
#include <cstdlib>
#include <iostream>

#include "huobi_futures/linear_swap/restful/AccountClient.hpp"
#include "huobi_futures/linear_swap/restful/MarketClient.hpp"
#include "huobi_futures/linear_swap/restful/OrderClient.hpp"

using huobi_futures::linear_swap::restful::AccountClient;
using huobi_futures::linear_swap::restful::MarketClient;
using huobi_futures::linear_swap::restful::OrderClient;

int main()
{
    // ---------- 公开行情：无需 key ----------
    MarketClient market;

    // GET /v5/market/price_limit（V5 market 方法统一带 Market 前缀，避免与 v3 重载歧义）
    auto priceLimit = market.GetMarketPriceLimit("BTC-USDT");
    if (priceLimit && priceLimit->code.value_or(0) == 200 &&
        priceLimit->data.has_value() && !priceLimit->data->empty())
    {
        std::cout << "[market] BTC-USDT high_limit=" << priceLimit->data->at(0).high_limit.value_or("")
                  << " low_limit=" << priceLimit->data->at(0).low_limit.value_or("") << std::endl;
    }
    else
    {
        std::cout << "[market] price_limit failed" << std::endl;
    }

    // GET /v5/market/risk/limit
    auto risk = market.GetMarketRiskLimit("BTC-USDT");
    if (risk && risk->code.value_or(0) == 200 && risk->data.has_value())
    {
        std::cout << "[market] risk/limit rows=" << risk->data->size() << std::endl;
    }

    // ---------- 私有接口：需要 key ----------
    const char *ak = std::getenv("HTX_ACCESS_KEY");
    const char *sk = std::getenv("HTX_SECRET_KEY");
    if (!ak || !sk)
    {
        std::cout << "[private] skip: HTX_ACCESS_KEY / HTX_SECRET_KEY not set" << std::endl;
        return 0;
    }

    // GET /v5/account/balance
    AccountClient account(ak, sk);
    auto balance = account.SwapAccountBalance();
    if (balance && balance->code.value_or(0) == 200 && balance->data.has_value())
    {
        std::cout << "[account] state=" << balance->data->state
                  << " equity=" << balance->data->equity << std::endl;
    }
    else
    {
        std::cout << "[account] balance failed, code=" << balance->code.value_or(0) << std::endl;
    }

    // GET /v5/trade/order/opens
    OrderClient trade(ak, sk);
    auto opens = trade.TradeOrderOpens("BTC-USDT", "cross");
    if (opens && opens->code.value_or(0) == 200)
    {
        std::cout << "[trade] open orders=" << (opens->data.has_value() ? opens->data->size() : 0) << std::endl;
    }

    return 0;
}
