#include <gtest/gtest.h>

#include "huobi_futures/linear_swap/restful/AccountClient.hpp"
typedef huobi_futures::linear_swap::restful::AccountClient AccountClient;
#include "huobi_futures/linear_swap/restful/MarketClient.hpp"
typedef huobi_futures::linear_swap::restful::MarketClient MarketClient;
#include "huobi_futures/utils/convert.hpp"

#include "config.hpp"

// V5 account 接口（私有，需 key）。无 key 时 code 非 200 属预期，不 fail。
// 实测口径：带真实 key 打 HTX 生产 API，断言 code==200 + data 必填字段非空。

TEST(V5Account, GetContractAccountBalance)
{
    extern map<string, string> config;
    init_config();
    AccountClient client(config["AccessKey"], config["SecretKey"]);
    auto result = client.SwapAccountBalance();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->code.value_or(0), 200);
    ASSERT_TRUE(result->data.has_value());
    EXPECT_FALSE(result->data->state.empty());
    EXPECT_FALSE(result->data->equity.empty());
}

TEST(V5Account, GetAssetMode)
{
    extern map<string, string> config;
    init_config();
    AccountClient client(config["AccessKey"], config["SecretKey"]);
    auto result = client.GetAssetMode();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->code.value_or(0), 200);
}

TEST(V5Account, GetFeeDeductionCurrency)
{
    extern map<string, string> config;
    init_config();
    AccountClient client(config["AccessKey"], config["SecretKey"]);
    auto result = client.GetFeeDeductionCurrency();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->code.value_or(0), 200);
}

TEST(V5Account, GetAccountBills)
{
    extern map<string, string> config;
    init_config();
    AccountClient client(config["AccessKey"], config["SecretKey"]);
    // bills 带参 GET，业务参数进签名
    auto result = client.SwapGetAccountBills("SPX500-USDT", "isolated", "", "", "", 0, 0, "");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->code.value_or(0), 200);
}

// #2 POST /v5/account/asset_mode - 设置资产模式（Java 权威：asset_mode=1）
// 幂等设当前值：统一账户下有持仓/挂单时报 1421，data=null（接口可达+签名正确即视为通过）
TEST(V5Account, SetAssetMode)
{
    extern map<string, string> config;
    init_config();
    AccountClient client(config["AccessKey"], config["SecretKey"]);
    // 查当前模式，幂等设同值
    auto cur = client.GetAssetMode();
    ASSERT_NE(cur, nullptr);
    ASSERT_EQ(cur->code.value_or(0), 200);
    ASSERT_TRUE(cur->data != nullptr);
    int mode = cur->data->asset_mode;
    auto result = client.SetAssetMode(mode);
    ASSERT_NE(result, nullptr);
    int code = result->code.value_or(0);
    // 200=成功，1421=有持仓/挂单不许改，6010=已为该模式。三者任一即接口可达+签名正确
    EXPECT_TRUE(code == 200 || code == 1421 || code == 6010) << "code=" << code << " msg=" << result->message.value_or("");
}

// #4 POST /v5/account/fee_deduction_currency - 设置手续费抵扣币种（Java 权威：fee_option=1, "htx"）
TEST(V5Account, SetFeeDeductionCurrency)
{
    extern map<string, string> config;
    init_config();
    AccountClient client(config["AccessKey"], config["SecretKey"]);
    auto result = client.FeeDeductionCurrency(1, "htx");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->code.value_or(0), 200);
    ASSERT_TRUE(result->data.has_value());
    EXPECT_EQ(result->data->fee_option, 1);
    EXPECT_EQ(result->data->deduction_currency, "htx");
}

// V5 market 接口（公开，无需 key）。
// 注：MarketClient 中 GetFundingRate/GetPriceLimit/GetOpenInterest 等存在 v3/V5 重载，
// 歧义方法暂跳过，只测无歧义的 V5 方法。

TEST(V5Market, GetMarketRiskLimit)
{
    init_config();
    MarketClient client;
    auto result = client.GetMarketRiskLimit("SPX500-USDT", "", "", "");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->code.value_or(0), 200);
    ASSERT_TRUE(result->data.has_value());
    EXPECT_FALSE(result->data->empty());
}

TEST(V5Market, GetAssetsDeductionCurrency)
{
    init_config();
    MarketClient client;
    auto result = client.GetAssetsDeductionCurrency();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->code.value_or(0), 200);
}

TEST(V5Market, GetMultiAssetsMarginList)
{
    init_config();
    MarketClient client;
    auto result = client.GetMultiAssetsMarginList();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->code.value_or(0), 200);
}

TEST(V5Market, GetFundingRateHistory)
{
    init_config();
    MarketClient client;
    auto result = client.GetFundingRateHistory("SPX500-USDT", "", "", 0, 0, "");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->code.value_or(0), 200);
}

TEST(V5Market, GetSettlementHistory)
{
    init_config();
    MarketClient client;
    auto result = client.GetSettlementHistory("SPX500-USDT", "", "", "", "", 0);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->code.value_or(0), 200);
}

// #30 GET /v5/market/funding_rate - 查询资金费率（Java 权威：BTC-USDT，data 为数组）
TEST(V5Market, GetMarketFundingRate)
{
    init_config();
    MarketClient client;
    auto result = client.GetMarketFundingRate("BTC-USDT");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->code.value_or(0), 200);
    ASSERT_TRUE(result->data.has_value());
    ASSERT_FALSE(result->data->empty());
    EXPECT_FALSE(result->data->at(0).funding_rate.value_or("").empty());
}

// #32 GET /v5/market/open_interest - 查询持仓总量（data 单对象）
TEST(V5Market, GetOpenInterest)
{
    init_config();
    MarketClient client;
    // GetOpenInterest 有 v3/V5 重载歧义，static_cast 选 V5(单参) 重载
    auto result = (std::shared_ptr<GetMarketOpenInterestResponse>(MarketClient::*)(const string &))
        &MarketClient::GetOpenInterest;
    auto r = (client.*result)("BTC-USDT");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    ASSERT_TRUE(r->data.has_value());
    EXPECT_FALSE(r->data->contract_code.value_or("").empty());
}

// #33 GET /v5/market/price_limit - 查询价格限制（data 数组）
TEST(V5Market, GetPriceLimit)
{
    init_config();
    MarketClient client;
    auto mfp = (std::shared_ptr<GetMarketPriceLimitResponse>(MarketClient::*)(const string &))
        &MarketClient::GetPriceLimit;
    auto r = (client.*mfp)("BTC-USDT");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    ASSERT_TRUE(r->data.has_value());
    ASSERT_FALSE(r->data->empty());
    EXPECT_FALSE(r->data->at(0).high_limit.value_or("").empty());
}

// #34 GET /v5/market/liquidation_orders - 查询强平订单（data 可为 null，已改 unique_ptr）
TEST(V5Market, GetLiquidationOrders)
{
    init_config();
    MarketClient client;
    auto mfp = (std::shared_ptr<GetMarketLiquidationOrdersResponse>(MarketClient::*)(const string &, const string &, const string &, const string &, const string &, int64_t, int32_t))
        &MarketClient::GetLiquidationOrders;
    auto r = (client.*mfp)("BTC-USDT", "", "", "", "", 0, 0);
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    // data 可能为 null（无强平），unique_ptr 不为空即有数据
    if (r->data)
    {
        ASSERT_FALSE(r->data->empty());
        EXPECT_FALSE(r->data->at(0).contract_code.value_or("").empty());
    }
}

// #36 GET /v5/market/elite_account_ratio - 精英账户多空比（Java 权威：BTC-USDT, period=5min）
TEST(V5Market, GetEliteAccountRatio)
{
    init_config();
    MarketClient client;
    auto result = client.GetMarketEliteAccountRatio("BTC-USDT", "5min");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->code.value_or(0), 200);
    ASSERT_TRUE(result->data.has_value());
    ASSERT_FALSE(result->data->empty());
    EXPECT_FALSE(result->data->at(0).buy_ratio.value_or("").empty());
}

// #37 GET /v5/market/elite_position_ratio - 精英持仓多空比
TEST(V5Market, GetElitePositionRatio)
{
    init_config();
    MarketClient client;
    auto result = client.GetMarketElitePositionRatio("BTC-USDT", "5min");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->code.value_or(0), 200);
    ASSERT_TRUE(result->data.has_value());
    ASSERT_FALSE(result->data->empty());
    EXPECT_FALSE(result->data->at(0).buy_ratio.value_or("").empty());
}

// #38 GET /v5/market/estimated_settlement_price - 预估结算价（data 数组）
TEST(V5Market, GetEstimatedSettlementPrice)
{
    init_config();
    MarketClient client;
    auto mfp = (std::shared_ptr<GetMarketEstimatedSettlementPriceResponse>(MarketClient::*)(const string &))
        &MarketClient::GetEstimatedSettlementPrice;
    auto r = (client.*mfp)("BTC-USDT");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    ASSERT_TRUE(r->data.has_value());
    ASSERT_FALSE(r->data->empty());
    // estimated_settlement_price 仅在结算临近时有值，平时可空，不强断言
    EXPECT_FALSE(r->data->at(0).contract_code.value_or("").empty());
}