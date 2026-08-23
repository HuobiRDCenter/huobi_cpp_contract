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

// V5 market 接口（公开，无需 key）。
// 注：MarketClient 中 GetFundingRate/GetPriceLimit/GetOpenInterest 等存在 v3/V5 重载，
// 歧义方法暂跳过，只测无歧义的 V5 方法。

TEST(V5Market, GetMarketRiskLimit)
{
    init_config();
    MarketClient client;
    auto result = client.GetMarketRiskLimit("SPX500-USDT", "", "", 0);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->code.value_or(0), 200);
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