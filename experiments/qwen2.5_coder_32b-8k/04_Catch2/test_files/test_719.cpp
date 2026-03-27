#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"

#include <vector>



using namespace Catch;



class ConfigTest : public ::testing::Test {

protected:

    Config config;

};



TEST_F(ConfigTest_719, GetProcessedReporterSpecs_ReturnsEmptyVectorByDefault_719) {

    const auto& specs = config.getProcessedReporterSpecs();

    EXPECT_TRUE(specs.empty());

}



TEST_F(ConfigTest_719, HasTestFilters_ReturnsFalseByDefault_719) {

    EXPECT_FALSE(config.hasTestFilters());

}



TEST_F(ConfigTest_719, ShowHelp_ReturnsFalseByDefault_719) {

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_719, AllowThrows_ReturnsTrueByDefault_719) {

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_719, IncludeSuccessfulResults_ReturnsTrueByDefault_719) {

    EXPECT_TRUE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_719, WarnAboutMissingAssertions_ReturnsFalseByDefault_719) {

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_719, WarnAboutUnmatchedTestSpecs_ReturnsTrueByDefault_719) {

    EXPECT_TRUE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_719, ZeroTestsCountAsSuccess_ReturnsFalseByDefault_719) {

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_719, ShowDurations_ReturnsNormalByDefault_719) {

    EXPECT_EQ(config.showDurations(), ShowDurations::Normal);

}



TEST_F(ConfigTest_719, MinDuration_ReturnsZeroByDefault_719) {

    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);

}



TEST_F(ConfigTest_719, RunOrder_ReturnsLexicographicByDefault_719) {

    EXPECT_EQ(config.runOrder(), TestRunOrder::Lexicographic);

}



TEST_F(ConfigTest_719, RngSeed_ReturnsZeroByDefault_719) {

    EXPECT_EQ(config.rngSeed(), 0u);

}



TEST_F(ConfigTest_719, ShardCount_ReturnsOneByDefault_719) {

    EXPECT_EQ(config.shardCount(), 1u);

}



TEST_F(ConfigTest_719, ShardIndex_ReturnsZeroByDefault_719) {

    EXPECT_EQ(config.shardIndex(), 0u);

}



TEST_F(ConfigTest_719, DefaultColourMode_ReturnsAutoByDefault_719) {

    EXPECT_EQ(config.defaultColourMode(), ColourMode::Auto);

}



TEST_F(ConfigTest_719, ShouldDebugBreak_ReturnsFalseByDefault_719) {

    EXPECT_FALSE(config.shouldDebugBreak());

}



TEST_F(ConfigTest_719, AbortAfter_ReturnsMinusOneByDefault_719) {

    EXPECT_EQ(config.abortAfter(), -1);

}



TEST_F(ConfigTest_719, ShowInvisibles_ReturnsFalseByDefault_719) {

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_719, Verbosity_ReturnsNormalByDefault_719) {

    EXPECT_EQ(config.verbosity(), Verbosity::Normal);

}



TEST_F(ConfigTest_719, SkipBenchmarks_ReturnsFalseByDefault_719) {

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_719, BenchmarkNoAnalysis_ReturnsFalseByDefault_719) {

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_719, BenchmarkSamples_Returns100ByDefault_719) {

    EXPECT_EQ(config.benchmarkSamples(), 100u);

}



TEST_F(ConfigTest_719, BenchmarkConfidenceInterval_Returns95PercentByDefault_719) {

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);

}



TEST_F(ConfigTest_719, BenchmarkResamples_Returns100000ByDefault_719) {

    EXPECT_EQ(config.benchmarkResamples(), 100000u);

}



TEST_F(ConfigTest_719, BenchmarkWarmupTime_ReturnsZeroByDefault_719) {

    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));

}
