#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest : public ::testing::Test {

protected:

    ConfigData configData;

    Config* config;



    void SetUp() override {

        config = new Config(configData);

    }



    void TearDown() override {

        delete config;

    }

};



TEST_F(ConfigTest_720, DefaultConstructorInitializesCorrectly_720) {

    Config defaultConfig;

    // Assuming default constructor initializes without errors

}



TEST_F(ConfigTest_720, ParameterizedConstructorSetsData_720) {

    EXPECT_EQ(&config->testSpec(), &configData.testSpec);

    // Assuming testSpec is correctly set from configData

}



TEST_F(ConfigTest_720, ListTestsReturnsFalseByDefault_720) {

    EXPECT_FALSE(config->listTests());

}



TEST_F(ConfigTest_720, ListTagsReturnsFalseByDefault_720) {

    EXPECT_FALSE(config->listTags());

}



TEST_F(ConfigTest_720, ListReportersReturnsFalseByDefault_720) {

    EXPECT_FALSE(config->listReporters());

}



TEST_F(ConfigTest_720, ListListenersReturnsFalseByDefault_720) {

    EXPECT_FALSE(config->listListeners());

}



TEST_F(ConfigTest_720, HasTestFiltersReturnsFalseByDefault_720) {

    EXPECT_FALSE(config->hasTestFilters());

}



TEST_F(ConfigTest_720, ShowHelpReturnsFalseByDefault_720) {

    EXPECT_FALSE(config->showHelp());

}



TEST_F(ConfigTest_720, AllowThrowsReturnsTrueByDefault_720) {

    EXPECT_TRUE(config->allowThrows());

}



TEST_F(ConfigTest_720, IncludeSuccessfulResultsReturnsTrueByDefault_720) {

    EXPECT_TRUE(config->includeSuccessfulResults());

}



TEST_F(ConfigTest_720, WarnAboutMissingAssertionsReturnsFalseByDefault_720) {

    EXPECT_FALSE(config->warnAboutMissingAssertions());

}



TEST_F(ConfigTest_720, WarnAboutUnmatchedTestSpecsReturnsFalseByDefault_720) {

    EXPECT_FALSE(config->warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_720, ZeroTestsCountAsSuccessReturnsTrueByDefault_720) {

    EXPECT_TRUE(config->zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_720, ShowDurationsReturnsNeverByDefault_720) {

    EXPECT_EQ(ShowDurations::Never, config->showDurations());

}



TEST_F(ConfigTest_720, MinDurationReturnsZeroByDefault_720) {

    EXPECT_DOUBLE_EQ(0.0, config->minDuration());

}



TEST_F(ConfigTest_720, RunOrderReturnsLexicographicalByDefault_720) {

    EXPECT_EQ(TestRunOrder::Lexicographically, config->runOrder());

}



TEST_F(ConfigTest_720, RngSeedReturnsNonZeroByDefault_720) {

    EXPECT_NE(0u, config->rngSeed());

}



TEST_F(ConfigTest_720, ShardCountReturnsOneByDefault_720) {

    EXPECT_EQ(1u, config->shardCount());

}



TEST_F(ConfigTest_720, ShardIndexReturnsZeroByDefault_720) {

    EXPECT_EQ(0u, config->shardIndex());

}



TEST_F(ConfigTest_720, DefaultColourModeReturnsAutoByDefault_720) {

    EXPECT_EQ(ColourMode::Auto, config->defaultColourMode());

}



TEST_F(ConfigTest_720, ShouldDebugBreakReturnsFalseByDefault_720) {

    EXPECT_FALSE(config->shouldDebugBreak());

}



TEST_F(ConfigTest_720, AbortAfterReturnsMinusOneByDefault_720) {

    EXPECT_EQ(-1, config->abortAfter());

}



TEST_F(ConfigTest_720, ShowInvisiblesReturnsFalseByDefault_720) {

    EXPECT_FALSE(config->showInvisibles());

}



TEST_F(ConfigTest_720, VerbosityReturnsNormalByDefault_720) {

    EXPECT_EQ(Verbosity::Normal, config->verbosity());

}



TEST_F(ConfigTest_720, SkipBenchmarksReturnsFalseByDefault_720) {

    EXPECT_FALSE(config->skipBenchmarks());

}



TEST_F(ConfigTest_720, BenchmarkNoAnalysisReturnsFalseByDefault_720) {

    EXPECT_FALSE(config->benchmarkNoAnalysis());

}



TEST_F(ConfigTest_720, BenchmarkSamplesReturns100ByDefault_720) {

    EXPECT_EQ(100u, config->benchmarkSamples());

}



TEST_F(ConfigTest_720, BenchmarkConfidenceIntervalReturns95ByDefault_720) {

    EXPECT_DOUBLE_EQ(0.95, config->benchmarkConfidenceInterval());

}



TEST_F(ConfigTest_720, BenchmarkResamplesReturns100000ByDefault_720) {

    EXPECT_EQ(100000u, config->benchmarkResamples());

}



TEST_F(ConfigTest_720, BenchmarkWarmupTimeReturns1SecondByDefault_720) {

    EXPECT_EQ(std::chrono::milliseconds(1000), config->benchmarkWarmupTime());

}
