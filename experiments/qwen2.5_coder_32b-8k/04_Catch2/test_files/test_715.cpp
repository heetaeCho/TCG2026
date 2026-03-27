#include <gtest/gtest.h>

#include "catch_config.hpp"



using namespace Catch;



class ConfigTest_715 : public ::testing::Test {

protected:

    ConfigData data;

    Config config;



    void SetUp() override {

        data.listListeners = false;

        config = Config(data);

    }

};



TEST_F(ConfigTest_715, ListListeners_DefaultValue_715) {

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_715, ListListeners_SetTrue_ReturnsTrue_715) {

    data.listListeners = true;

    config = Config(data);

    EXPECT_TRUE(config.listListeners());

}



TEST_F(ConfigTest_715, GetReporterSpecs_Default_ReturnsEmpty_715) {

    EXPECT_TRUE(config.getReporterSpecs().empty());

}



TEST_F(ConfigTest_715, GetProcessedReporterSpecs_Default_ReturnsEmpty_715) {

    EXPECT_TRUE(config.getProcessedReporterSpecs().empty());

}



TEST_F(ConfigTest_715, GetTestsOrTags_Default_ReturnsEmpty_715) {

    EXPECT_TRUE(config.getTestsOrTags().empty());

}



TEST_F(ConfigTest_715, GetSectionsToRun_Default_ReturnsEmpty_715) {

    EXPECT_TRUE(config.getSectionsToRun().empty());

}



TEST_F(ConfigTest_715, ShowHelp_DefaultValue_ReturnsFalse_715) {

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_715, AllowThrows_DefaultValue_ReturnsTrue_715) {

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_715, Name_DefaultValue_ReturnsEmptyString_715) {

    EXPECT_EQ(config.name(), StringRef(""));

}



TEST_F(ConfigTest_715, IncludeSuccessfulResults_DefaultValue_ReturnsFalse_715) {

    EXPECT_FALSE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_715, WarnAboutMissingAssertions_DefaultValue_ReturnsFalse_715) {

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_715, WarnAboutUnmatchedTestSpecs_DefaultValue_ReturnsFalse_715) {

    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_715, ZeroTestsCountAsSuccess_DefaultValue_ReturnsFalse_715) {

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_715, ShowDurations_DefaultValue_ReturnsDefaultForReporter_715) {

    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);

}



TEST_F(ConfigTest_715, MinDuration_DefaultValue_ReturnsMinusOne_715) {

    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);

}



TEST_F(ConfigTest_715, RunOrder_DefaultValue_ReturnsDeclared_715) {

    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);

}



TEST_F(ConfigTest_715, RngSeed_DefaultValue_ReturnsGeneratedSeed_715) {

    EXPECT_NE(config.rngSeed(), 0u); // Assuming a non-zero seed is generated

}



TEST_F(ConfigTest_715, ShardCount_DefaultValue_ReturnsOne_715) {

    EXPECT_EQ(config.shardCount(), 1u);

}



TEST_F(ConfigTest_715, ShardIndex_DefaultValue_ReturnsZero_715) {

    EXPECT_EQ(config.shardIndex(), 0u);

}



TEST_F(ConfigTest_715, DefaultColourMode_DefaultValue_ReturnsPlatformDefault_715) {

    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);

}



TEST_F(ConfigTest_715, ShouldDebugBreak_DefaultValue_ReturnsFalse_715) {

    EXPECT_FALSE(config.shouldDebugBreak());

}



TEST_F(ConfigTest_715, AbortAfter_DefaultValue_ReturnsMinusOne_715) {

    EXPECT_EQ(config.abortAfter(), -1);

}



TEST_F(ConfigTest_715, ShowInvisibles_DefaultValue_ReturnsFalse_715) {

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_715, Verbosity_DefaultValue_ReturnsNormal_715) {

    EXPECT_EQ(config.verbosity(), Verbosity::Normal);

}



TEST_F(ConfigTest_715, SkipBenchmarks_DefaultValue_ReturnsFalse_715) {

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_715, BenchmarkNoAnalysis_DefaultValue_ReturnsFalse_715) {

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_715, BenchmarkSamples_DefaultValue_ReturnsHundred_715) {

    EXPECT_EQ(config.benchmarkSamples(), 100u);

}



TEST_F(ConfigTest_715, BenchmarkConfidenceInterval_DefaultValue_ReturnsApproxNinetyFivePercent_715) {

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.94999999999999996);

}



TEST_F(ConfigTest_715, BenchmarkResamples_DefaultValue_ReturnsHundredThousand_715) {

    EXPECT_EQ(config.benchmarkResamples(), 100000u);

}



TEST_F(ConfigTest_715, BenchmarkWarmupTime_DefaultValue_ReturnsHundredMilliseconds_715) {

    EXPECT_EQ(config.benchmarkWarmupTime().count(), 100);

}
