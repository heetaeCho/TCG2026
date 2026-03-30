#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest : public ::testing::Test {

protected:

    ConfigData data;

    Config* config;



    void SetUp() override {

        config = new Config(data);

    }



    void TearDown() override {

        delete config;

    }

};



TEST_F(ConfigTest_734, ShardIndex_DefaultValue_734) {

    EXPECT_EQ(config->shardIndex(), 0);

}



TEST_F(ConfigTest_734, ShardIndex_CustomValue_734) {

    data.shardIndex = 2;

    Config customConfig(data);

    EXPECT_EQ(customConfig.shardIndex(), 2);

}



TEST_F(ConfigTest_734, ListTests_DefaultValue_734) {

    EXPECT_FALSE(config->listTests());

}



TEST_F(ConfigTest_734, ListTags_DefaultValue_734) {

    EXPECT_FALSE(config->listTags());

}



TEST_F(ConfigTest_734, ListReporters_DefaultValue_734) {

    EXPECT_FALSE(config->listReporters());

}



TEST_F(ConfigTest_734, ListListeners_DefaultValue_734) {

    EXPECT_FALSE(config->listListeners());

}



TEST_F(ConfigTest_734, ShowHelp_DefaultValue_734) {

    EXPECT_FALSE(config->showHelp());

}



TEST_F(ConfigTest_734, AllowThrows_DefaultValue_734) {

    EXPECT_TRUE(config->allowThrows());

}



TEST_F(ConfigTest_734, IncludeSuccessfulResults_DefaultValue_734) {

    EXPECT_FALSE(config->includeSuccessfulResults());

}



TEST_F(ConfigTest_734, WarnAboutMissingAssertions_DefaultValue_734) {

    EXPECT_FALSE(config->warnAboutMissingAssertions());

}



TEST_F(ConfigTest_734, WarnAboutUnmatchedTestSpecs_DefaultValue_734) {

    EXPECT_FALSE(config->warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_734, ZeroTestsCountAsSuccess_DefaultValue_734) {

    EXPECT_FALSE(config->zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_734, SkipBenchmarks_DefaultValue_734) {

    EXPECT_FALSE(config->skipBenchmarks());

}



TEST_F(ConfigTest_734, BenchmarkNoAnalysis_DefaultValue_734) {

    EXPECT_FALSE(config->benchmarkNoAnalysis());

}



TEST_F(ConfigTest_734, ShardCount_DefaultValue_734) {

    EXPECT_EQ(config->shardCount(), 1);

}



TEST_F(ConfigTest_734, RngSeed_NotZero_734) {

    EXPECT_NE(config->rngSeed(), 0);

}



TEST_F(ConfigTest_734, BenchmarkConfidenceInterval_DefaultValue_734) {

    EXPECT_DOUBLE_EQ(config->benchmarkConfidenceInterval(), 0.95);

}



TEST_F(ConfigTest_734, BenchmarkResamples_DefaultValue_734) {

    EXPECT_EQ(config->benchmarkResamples(), 100000);

}



TEST_F(ConfigTest_734, BenchmarkWarmupTime_DefaultValue_734) {

    EXPECT_EQ(config->benchmarkWarmupTime().count(), 100);

}



TEST_F(ConfigTest_734, Verbosity_DefaultValue_734) {

    EXPECT_EQ(config->verbosity(), Verbosity::Normal);

}
