#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



class ConfigTest : public ::testing::Test {

protected:

    Catch::ConfigData default_data;

    std::unique_ptr<Catch::Config> config;



    void SetUp() override {

        config = std::make_unique<Catch::Config>(default_data);

    }

};



TEST_F(ConfigTest_733, DefaultShardCountIsOne_733) {

    EXPECT_EQ(config->shardCount(), 1u);

}



TEST_F(ConfigTest_733, ShardCountReturnsSetValue_733) {

    default_data.shardCount = 4;

    config = std::make_unique<Catch::Config>(default_data);

    EXPECT_EQ(config->shardCount(), 4u);

}



TEST_F(ConfigTest_733, ListTestsDefaultIsFalse_733) {

    EXPECT_FALSE(config->listTests());

}



TEST_F(ConfigTest_733, ListTagsDefaultIsFalse_733) {

    EXPECT_FALSE(config->listTags());

}



TEST_F(ConfigTest_733, ListReportersDefaultIsFalse_733) {

    EXPECT_FALSE(config->listReporters());

}



TEST_F(ConfigTest_733, ListListenersDefaultIsFalse_733) {

    EXPECT_FALSE(config->listListeners());

}



TEST_F(ConfigTest_733, ShowHelpDefaultIsFalse_733) {

    EXPECT_FALSE(config->showHelp());

}



TEST_F(ConfigTest_733, AllowThrowsDefaultIsTrue_733) {

    EXPECT_TRUE(config->allowThrows());

}



TEST_F(ConfigTest_733, IncludeSuccessfulResultsDefaultIsTrue_733) {

    EXPECT_TRUE(config->includeSuccessfulResults());

}



TEST_F(ConfigTest_733, WarnAboutMissingAssertionsDefaultIsFalse_733) {

    EXPECT_FALSE(config->warnAboutMissingAssertions());

}



TEST_F(ConfigTest_733, WarnAboutUnmatchedTestSpecsDefaultIsFalse_733) {

    EXPECT_FALSE(config->warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_733, ZeroTestsCountAsSuccessDefaultIsTrue_733) {

    EXPECT_TRUE(config->zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_733, ShowDurationsDefaultIsDefaultForReporter_733) {

    EXPECT_EQ(config->showDurations(), Catch::ShowDurations::DefaultForReporter);

}



TEST_F(ConfigTest_733, MinDurationDefaultIsNegativeOne_733) {

    EXPECT_DOUBLE_EQ(config->minDuration(), -1.0);

}



TEST_F(ConfigTest_733, RunOrderDefaultIsDeclared_733) {

    EXPECT_EQ(config->runOrder(), Catch::TestRunOrder::Declared);

}



TEST_F(ConfigTest_733, DefaultColourModeDefaultIsPlatformDefault_733) {

    EXPECT_EQ(config->defaultColourMode(), Catch::ColourMode::PlatformDefault);

}



TEST_F(ConfigTest_733, ShouldDebugBreakDefaultIsFalse_733) {

    EXPECT_FALSE(config->shouldDebugBreak());

}



TEST_F(ConfigTest_733, AbortAfterDefaultIsNegativeOne_733) {

    EXPECT_EQ(config->abortAfter(), -1);

}



TEST_F(ConfigTest_733, ShowInvisiblesDefaultIsFalse_733) {

    EXPECT_FALSE(config->showInvisibles());

}



TEST_F(ConfigTest_733, VerbosityDefaultIsNormal_733) {

    EXPECT_EQ(config->verbosity(), Catch::Verbosity::Normal);

}



TEST_F(ConfigTest_733, SkipBenchmarksDefaultIsFalse_733) {

    EXPECT_FALSE(config->skipBenchmarks());

}



TEST_F(ConfigTest_733, BenchmarkNoAnalysisDefaultIsFalse_733) {

    EXPECT_FALSE(config->benchmarkNoAnalysis());

}



TEST_F(ConfigTest_733, BenchmarkSamplesDefaultIsHundred_733) {

    EXPECT_EQ(config->benchmarkSamples(), 100u);

}



TEST_F(ConfigTest_733, BenchmarkConfidenceIntervalDefaultIsApprox95Percent_733) {

    EXPECT_DOUBLE_EQ(config->benchmarkConfidenceInterval(), 0.94999999999999996);

}



TEST_F(ConfigTest_733, BenchmarkResamplesDefaultIsHundredThousand_733) {

    EXPECT_EQ(config->benchmarkResamples(), 100000u);

}



TEST_F(ConfigTest_733, BenchmarkWarmupTimeDefaultIsOneHundredMilliseconds_733) {

    EXPECT_EQ(config->benchmarkWarmupTime().count(), 100);

}
