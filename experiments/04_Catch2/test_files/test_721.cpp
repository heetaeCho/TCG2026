#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest : public ::testing::Test {

protected:

    Config config;

};



TEST_F(ConfigTest_721, HasTestFilters_DefaultValue_False_721) {

    EXPECT_FALSE(config.hasTestFilters());

}



TEST_F(ConfigTest_721, ListTests_DefaultValue_False_721) {

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_721, ListTags_DefaultValue_False_721) {

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_721, ListReporters_DefaultValue_False_721) {

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_721, ListListeners_DefaultValue_False_721) {

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_721, ShowHelp_DefaultValue_False_721) {

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_721, AllowThrows_DefaultValue_True_721) {

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_721, IncludeSuccessfulResults_DefaultValue_True_721) {

    EXPECT_TRUE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_721, WarnAboutMissingAssertions_DefaultValue_True_721) {

    EXPECT_TRUE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_721, WarnAboutUnmatchedTestSpecs_DefaultValue_True_721) {

    EXPECT_TRUE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_721, ZeroTestsCountAsSuccess_DefaultValue_False_721) {

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_721, ShowDurations_DefaultValue_Shortest_721) {

    EXPECT_EQ(config.showDurations(), ShowDurations::Shortest);

}



TEST_F(ConfigTest_721, MinDuration_DefaultValue_Zero_721) {

    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);

}



TEST_F(ConfigTest_721, RunOrder_DefaultValue_Lexicographical_721) {

    EXPECT_EQ(config.runOrder(), TestRunOrder::Lexicographical);

}



TEST_F(ConfigTest_721, RngSeed_DefaultValue_Zero_721) {

    EXPECT_EQ(config.rngSeed(), 0u);

}



TEST_F(ConfigTest_721, ShardCount_DefaultValue_One_721) {

    EXPECT_EQ(config.shardCount(), 1u);

}



TEST_F(ConfigTest_721, ShardIndex_DefaultValue_Zero_721) {

    EXPECT_EQ(config.shardIndex(), 0u);

}



TEST_F(ConfigTest_721, DefaultColourMode_DefaultValue_Auto_721) {

    EXPECT_EQ(config.defaultColourMode(), ColourMode::Auto);

}



TEST_F(ConfigTest_721, ShouldDebugBreak_DefaultValue_False_721) {

    EXPECT_FALSE(config.shouldDebugBreak());

}



TEST_F(ConfigTest_721, AbortAfter_DefaultValue_Zero_721) {

    EXPECT_EQ(config.abortAfter(), 0);

}



TEST_F(ConfigTest_721, ShowInvisibles_DefaultValue_False_721) {

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_721, Verbosity_DefaultValue_Normal_721) {

    EXPECT_EQ(config.verbosity(), Verbosity::Normal);

}



TEST_F(ConfigTest_721, SkipBenchmarks_DefaultValue_False_721) {

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_721, BenchmarkNoAnalysis_DefaultValue_False_721) {

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_721, BenchmarkSamples_DefaultValue_100_721) {

    EXPECT_EQ(config.benchmarkSamples(), 100u);

}



TEST_F(ConfigTest_721, BenchmarkConfidenceInterval_DefaultValue_95_721) {

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);

}



TEST_F(ConfigTest_721, BenchmarkResamples_DefaultValue_100000_721) {

    EXPECT_EQ(config.benchmarkResamples(), 100000u);

}



TEST_F(ConfigTest_721, BenchmarkWarmupTime_DefaultValue_500ms_721) {

    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));

}
