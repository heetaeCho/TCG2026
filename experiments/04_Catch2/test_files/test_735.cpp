#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest_735 : public ::testing::Test {

protected:

    ConfigData data;

    Config config;



    void SetUp() override {

        // Initialize default values for the test

        data.defaultColourMode = ColourMode::PlatformDefault;

        config = Config(data);

    }

};



TEST_F(ConfigTest_735, DefaultColourMode_ReturnsCorrectValue_735) {

    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);

}



TEST_F(ConfigTest_735, ListTests_Default_ReturnsFalse_735) {

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_735, ListTags_Default_ReturnsFalse_735) {

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_735, ListReporters_Default_ReturnsFalse_735) {

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_735, ListListeners_Default_ReturnsFalse_735) {

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_735, ShowHelp_Default_ReturnsFalse_735) {

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_735, AllowThrows_Default_ReturnsTrue_735) {

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_735, IncludeSuccessfulResults_Default_ReturnsFalse_735) {

    EXPECT_FALSE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_735, WarnAboutMissingAssertions_Default_ReturnsFalse_735) {

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_735, WarnAboutUnmatchedTestSpecs_Default_ReturnsFalse_735) {

    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_735, ZeroTestsCountAsSuccess_Default_ReturnsFalse_735) {

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_735, ShowDurations_Default_ReturnsDefaultForReporter_735) {

    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);

}



TEST_F(ConfigTest_735, MinDuration_Default_ReturnsMinusOne_735) {

    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);

}



TEST_F(ConfigTest_735, RunOrder_Default_ReturnsDeclared_735) {

    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);

}



TEST_F(ConfigTest_735, AbortAfter_Default_ReturnsMinusOne_735) {

    EXPECT_EQ(config.abortAfter(), -1);

}



TEST_F(ConfigTest_735, ShowInvisibles_Default_ReturnsFalse_735) {

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_735, Verbosity_Default_ReturnsNormal_735) {

    EXPECT_EQ(config.verbosity(), Verbosity::Normal);

}



TEST_F(ConfigTest_735, SkipBenchmarks_Default_ReturnsFalse_735) {

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_735, BenchmarkNoAnalysis_Default_ReturnsFalse_735) {

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_735, BenchmarkSamples_Default_Returns100_735) {

    EXPECT_EQ(config.benchmarkSamples(), 100u);

}



TEST_F(ConfigTest_735, BenchmarkConfidenceInterval_Default_Returns0_95_735) {

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.94999999999999996);

}



TEST_F(ConfigTest_735, BenchmarkResamples_Default_Returns100000_735) {

    EXPECT_EQ(config.benchmarkResamples(), 100000u);

}



TEST_F(ConfigTest_735, BenchmarkWarmupTime_Default_Returns100_735) {

    EXPECT_EQ(config.benchmarkWarmupTime().count(), 100);

}



TEST_F(ConfigTest_735, ShardCount_Default_ReturnsOne_735) {

    EXPECT_EQ(config.shardCount(), 1u);

}



TEST_F(ConfigTest_735, ShardIndex_Default_ReturnsZero_735) {

    EXPECT_EQ(config.shardIndex(), 0u);

}
