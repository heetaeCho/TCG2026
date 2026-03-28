#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest_742 : public ::testing::Test {

protected:

    ConfigData data;

    Config config;



    void SetUp() override {

        data.benchmarkSamples = 100; // Default value

        config = Config(data);

    }

};



TEST_F(ConfigTest_742, BenchmarkSamples_DefaultValue_742) {

    EXPECT_EQ(config.benchmarkSamples(), 100u);

}



TEST_F(ConfigTest_742, BenchmarkSamples_CustomValue_742) {

    data.benchmarkSamples = 50;

    config = Config(data);

    EXPECT_EQ(config.benchmarkSamples(), 50u);

}



TEST_F(ConfigTest_742, ListTests_DefaultValue_742) {

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_742, ListTags_DefaultValue_742) {

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_742, ListReporters_DefaultValue_742) {

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_742, ListListeners_DefaultValue_742) {

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_742, ShowHelp_DefaultValue_742) {

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_742, AllowThrows_DefaultValue_742) {

    EXPECT_FALSE(config.allowThrows());

}



TEST_F(ConfigTest_742, IncludeSuccessfulResults_DefaultValue_742) {

    EXPECT_TRUE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_742, WarnAboutMissingAssertions_DefaultValue_742) {

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_742, WarnAboutUnmatchedTestSpecs_DefaultValue_742) {

    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_742, ZeroTestsCountAsSuccess_DefaultValue_742) {

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_742, ShowDurations_DefaultValue_742) {

    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);

}



TEST_F(ConfigTest_742, MinDuration_DefaultValue_742) {

    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);

}



TEST_F(ConfigTest_742, RunOrder_DefaultValue_742) {

    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);

}



TEST_F(ConfigTest_742, RngSeed_DefaultValue_742) {

    EXPECT_NE(config.rngSeed(), 0u); // Assuming it's not zero

}



TEST_F(ConfigTest_742, ShardCount_DefaultValue_742) {

    EXPECT_EQ(config.shardCount(), 1u);

}



TEST_F(ConfigTest_742, ShardIndex_DefaultValue_742) {

    EXPECT_EQ(config.shardIndex(), 0u);

}



TEST_F(ConfigTest_742, DefaultColourMode_DefaultValue_742) {

    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);

}



TEST_F(ConfigTest_742, ShouldDebugBreak_DefaultValue_742) {

    EXPECT_FALSE(config.shouldDebugBreak());

}



TEST_F(ConfigTest_742, AbortAfter_DefaultValue_742) {

    EXPECT_EQ(config.abortAfter(), -1);

}



TEST_F(ConfigTest_742, ShowInvisibles_DefaultValue_742) {

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_742, Verbosity_DefaultValue_742) {

    EXPECT_EQ(config.verbosity(), Verbosity::Normal);

}



TEST_F(ConfigTest_742, SkipBenchmarks_DefaultValue_742) {

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_742, BenchmarkNoAnalysis_DefaultValue_742) {

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_742, BenchmarkConfidenceInterval_DefaultValue_742) {

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);

}



TEST_F(ConfigTest_742, BenchmarkResamples_DefaultValue_742) {

    EXPECT_EQ(config.benchmarkResamples(), 100000u);

}



TEST_F(ConfigTest_742, BenchmarkWarmupTime_DefaultValue_742) {

    EXPECT_EQ(config.benchmarkWarmupTime().count(), 100);

}
