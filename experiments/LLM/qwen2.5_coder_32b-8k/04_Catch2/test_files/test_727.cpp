#include <gtest/gtest.h>

#include "catch_config.hpp"

#include "catch_interfaces_config.hpp"



using namespace Catch;



class ConfigTest : public ::testing::Test {

protected:

    ConfigData defaultConfigData;

    Config* config;



    void SetUp() override {

        defaultConfigData.warnings = WarnAbout::Nothing;

        config = new Config(defaultConfigData);

    }



    void TearDown() override {

        delete config;

    }

};



TEST_F(ConfigTest_727, DefaultConstructorInitializesCorrectly_727) {

    Config configDefault;

    EXPECT_EQ(configDefault.warnAboutUnmatchedTestSpecs(), false);

}



TEST_F(ConfigTest_727, WarnAboutUnmatchedTestSpecs_ReturnsFalseWhenNotSet_727) {

    EXPECT_EQ(config->warnAboutUnmatchedTestSpecs(), false);

}



TEST_F(ConfigTest_727, WarnAboutUnmatchedTestSpecs_ReturnsTrueWhenSet_727) {

    defaultConfigData.warnings = WarnAbout::UnmatchedTestSpec;

    Config configWithWarning(defaultConfigData);

    EXPECT_EQ(configWithWarning.warnAboutUnmatchedTestSpecs(), true);

}



TEST_F(ConfigTest_727, ListTests_DefaultIsFalse_727) {

    EXPECT_EQ(config->listTests(), false);

}



TEST_F(ConfigTest_727, ListTags_DefaultIsFalse_727) {

    EXPECT_EQ(config->listTags(), false);

}



TEST_F(ConfigTest_727, ListReporters_DefaultIsFalse_727) {

    EXPECT_EQ(config->listReporters(), false);

}



TEST_F(ConfigTest_727, ListListeners_DefaultIsFalse_727) {

    EXPECT_EQ(config->listListeners(), false);

}



TEST_F(ConfigTest_727, ShowHelp_DefaultIsFalse_727) {

    EXPECT_EQ(config->showHelp(), false);

}



TEST_F(ConfigTest_727, AllowThrows_DefaultIsTrue_727) {

    EXPECT_EQ(config->allowThrows(), true);

}



TEST_F(ConfigTest_727, IncludeSuccessfulResults_DefaultIsFalse_727) {

    EXPECT_EQ(config->includeSuccessfulResults(), false);

}



TEST_F(ConfigTest_727, WarnAboutMissingAssertions_DefaultIsFalse_727) {

    EXPECT_EQ(config->warnAboutMissingAssertions(), false);

}



TEST_F(ConfigTest_727, ZeroTestsCountAsSuccess_DefaultIsFalse_727) {

    EXPECT_EQ(config->zeroTestsCountAsSuccess(), false);

}



TEST_F(ConfigTest_727, ShowDurations_DefaultIsDefaultForReporter_727) {

    EXPECT_EQ(config->showDurations(), ShowDurations::DefaultForReporter);

}



TEST_F(ConfigTest_727, MinDuration_DefaultIsNegativeOne_727) {

    EXPECT_EQ(config->minDuration(), -1.0);

}



TEST_F(ConfigTest_727, RunOrder_DefaultIsDeclared_727) {

    EXPECT_EQ(config->runOrder(), TestRunOrder::Declared);

}



TEST_F(ConfigTest_727, ShardCount_DefaultIsOne_727) {

    EXPECT_EQ(config->shardCount(), 1u);

}



TEST_F(ConfigTest_727, ShardIndex_DefaultIsZero_727) {

    EXPECT_EQ(config->shardIndex(), 0u);

}



TEST_F(ConfigTest_727, DefaultColourMode_DefaultIsPlatformDefault_727) {

    EXPECT_EQ(config->defaultColourMode(), ColourMode::PlatformDefault);

}



TEST_F(ConfigTest_727, ShouldDebugBreak_DefaultIsFalse_727) {

    EXPECT_EQ(config->shouldDebugBreak(), false);

}



TEST_F(ConfigTest_727, AbortAfter_DefaultIsNegativeOne_727) {

    EXPECT_EQ(config->abortAfter(), -1);

}



TEST_F(ConfigTest_727, ShowInvisibles_DefaultIsFalse_727) {

    EXPECT_EQ(config->showInvisibles(), false);

}



TEST_F(ConfigTest_727, Verbosity_DefaultIsNormal_727) {

    EXPECT_EQ(config->verbosity(), Verbosity::Normal);

}



TEST_F(ConfigTest_727, SkipBenchmarks_DefaultIsFalse_727) {

    EXPECT_EQ(config->skipBenchmarks(), false);

}



TEST_F(ConfigTest_727, BenchmarkNoAnalysis_DefaultIsFalse_727) {

    EXPECT_EQ(config->benchmarkNoAnalysis(), false);

}



TEST_F(ConfigTest_727, BenchmarkSamples_DefaultIsHundred_727) {

    EXPECT_EQ(config->benchmarkSamples(), 100u);

}



TEST_F(ConfigTest_727, BenchmarkConfidenceInterval_DefaultIsApproximately95Percent_727) {

    EXPECT_NEAR(config->benchmarkConfidenceInterval(), 0.95, 0.001);

}



TEST_F(ConfigTest_727, BenchmarkResamples_DefaultIsHundredThousand_727) {

    EXPECT_EQ(config->benchmarkResamples(), 100000u);

}



TEST_F(ConfigTest_727, BenchmarkWarmupTime_DefaultIsHundredMilliseconds_727) {

    EXPECT_EQ(config->benchmarkWarmupTime().count(), 100);

}
