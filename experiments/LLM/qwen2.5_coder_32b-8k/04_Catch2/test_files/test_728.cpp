#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest : public ::testing::Test {

protected:

    ConfigData data;

    Config config;



    void SetUp() override {

        data.allowZeroTests = false;

        config = Config(data);

    }

};



TEST_F(ConfigTest_728, ZeroTestsCountAsSuccess_DefaultFalse_728) {

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_728, ZeroTestsCountAsSuccess_SetTrue_728) {

    data.allowZeroTests = true;

    Config configWithTrue(data);

    EXPECT_TRUE(configWithTrue.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_728, ListTests_DefaultFalse_728) {

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_728, ListTags_DefaultFalse_728) {

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_728, ListReporters_DefaultFalse_728) {

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_728, ListListeners_DefaultFalse_728) {

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_728, ShowHelp_DefaultFalse_728) {

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_728, AllowThrows_DefaultTrue_728) {

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_728, IncludeSuccessfulResults_DefaultFalse_728) {

    EXPECT_FALSE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_728, WarnAboutMissingAssertions_DefaultFalse_728) {

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_728, WarnAboutUnmatchedTestSpecs_DefaultFalse_728) {

    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_728, ShowDurations_DefaultDefaultForReporter_728) {

    EXPECT_EQ(ShowDurations::DefaultForReporter, config.showDurations());

}



TEST_F(ConfigTest_728, MinDuration_DefaultNegativeOne_728) {

    EXPECT_DOUBLE_EQ(-1.0, config.minDuration());

}



TEST_F(ConfigTest_728, RunOrder_DefaultDeclared_728) {

    EXPECT_EQ(TestRunOrder::Declared, config.runOrder());

}



TEST_F(ConfigTest_728, ShardCount_DefaultOne_728) {

    EXPECT_EQ(1u, config.shardCount());

}



TEST_F(ConfigTest_728, ShardIndex_DefaultZero_728) {

    EXPECT_EQ(0u, config.shardIndex());

}



TEST_F(ConfigTest_728, DefaultColourMode_DefaultPlatformDefault_728) {

    EXPECT_EQ(ColourMode::PlatformDefault, config.defaultColourMode());

}



TEST_F(ConfigTest_728, ShouldDebugBreak_DefaultFalse_728) {

    EXPECT_FALSE(config.shouldDebugBreak());

}



TEST_F(ConfigTest_728, AbortAfter_DefaultNegativeOne_728) {

    EXPECT_EQ(-1, config.abortAfter());

}



TEST_F(ConfigTest_728, ShowInvisibles_DefaultFalse_728) {

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_728, Verbosity_DefaultNormal_728) {

    EXPECT_EQ(Verbosity::Normal, config.verbosity());

}



TEST_F(ConfigTest_728, SkipBenchmarks_DefaultFalse_728) {

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_728, BenchmarkNoAnalysis_DefaultFalse_728) {

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_728, BenchmarkSamples_DefaultOneHundred_728) {

    EXPECT_EQ(100u, config.benchmarkSamples());

}



TEST_F(ConfigTest_728, BenchmarkConfidenceInterval_Default95Percent_728) {

    EXPECT_DOUBLE_EQ(0.94999999999999996, config.benchmarkConfidenceInterval());

}



TEST_F(ConfigTest_728, BenchmarkResamples_DefaultOneHundredThousand_728) {

    EXPECT_EQ(100000u, config.benchmarkResamples());

}



TEST_F(ConfigTest_728, BenchmarkWarmupTime_DefaultOneHundredMilliseconds_728) {

    EXPECT_EQ(std::chrono::milliseconds(100), config.benchmarkWarmupTime());

}
