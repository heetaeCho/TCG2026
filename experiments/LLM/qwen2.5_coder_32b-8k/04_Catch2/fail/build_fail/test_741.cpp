#include <gtest/gtest.h>

#include "catch_config.hpp"



using namespace Catch;



class ConfigTest : public ::testing::Test {

protected:

    ConfigData data;

    Config config;



    void SetUp() override {

        // Initialize default data for testing

        data.benchmarkNoAnalysis = false;

        config = Config(data);

    }

};



TEST_F(ConfigTest_741, BenchmarkNoAnalysis_DefaultValue_741) {

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_741, BenchmarkNoAnalysis_SetToTrue_741) {

    data.benchmarkNoAnalysis = true;

    config = Config(data);

    EXPECT_TRUE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_741, GetReporterSpecs_EmptyByDefault_741) {

    EXPECT_TRUE(config.getReporterSpecs().empty());

}



TEST_F(ConfigTest_741, GetProcessedReporterSpecs_EmptyByDefault_741) {

    EXPECT_TRUE(config.getProcessedReporterSpecs().empty());

}



TEST_F(ConfigTest_741, GetTestsOrTags_EmptyByDefault_741) {

    EXPECT_TRUE(config.getTestsOrTags().empty());

}



TEST_F(ConfigTest_741, GetSectionsToRun_EmptyByDefault_741) {

    EXPECT_TRUE(config.getSectionsToRun().empty());

}



TEST_F(ConfigTest_741, HasTestFilters_FalseByDefault_741) {

    EXPECT_FALSE(config.hasTestFilters());

}



TEST_F(ConfigTest_741, ShowHelp_FalseByDefault_741) {

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_741, AllowThrows_TrueByDefault_741) {

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_741, Name_DefaultValue_741) {

    EXPECT_EQ(config.name(), "");

}



TEST_F(ConfigTest_741, IncludeSuccessfulResults_FalseByDefault_741) {

    EXPECT_FALSE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_741, WarnAboutMissingAssertions_FalseByDefault_741) {

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_741, WarnAboutUnmatchedTestSpecs_FalseByDefault_741) {

    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_741, ZeroTestsCountAsSuccess_FalseByDefault_741) {

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_741, ShowDurations_DefaultValue_741) {

    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);

}



TEST_F(ConfigTest_741, MinDuration_NegativeOneByDefault_741) {

    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);

}



TEST_F(ConfigTest_741, RunOrder_DefaultValue_741) {

    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);

}



TEST_F(ConfigTest_741, RngSeed_NotZeroByDefault_741) {

    EXPECT_NE(config.rngSeed(), 0u);

}



TEST_F(ConfigTest_741, ShardCount_OneByDefault_741) {

    EXPECT_EQ(config.shardCount(), 1u);

}



TEST_F(ConfigTest_741, ShardIndex_ZeroByDefault_741) {

    EXPECT_EQ(config.shardIndex(), 0u);

}



TEST_F(ConfigTest_741, DefaultColourMode_DefaultValue_741) {

    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);

}



TEST_F(ConfigTest_741, ShouldDebugBreak_FalseByDefault_741) {

    EXPECT_FALSE(config.shouldDebugBreak());

}



TEST_F(ConfigTest_741, AbortAfter_NegativeOneByDefault_741) {

    EXPECT_EQ(config.abortAfter(), -1);

}



TEST_F(ConfigTest_741, ShowInvisibles_FalseByDefault_741) {

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_741, Verbosity_NormalByDefault_741) {

    EXPECT_EQ(config.verbosity(), Verbosity::Normal);

}



TEST_F(ConfigTest_741, SkipBenchmarks_FalseByDefault_741) {

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_741, BenchmarkSamples_HundredByDefault_741) {

    EXPECT_EQ(config.benchmarkSamples(), 100u);

}



TEST_F(ConfigTest_741, BenchmarkConfidenceInterval_DefaultValue_741) {

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);

}



TEST_F(ConfigTest_741, BenchmarkResamples_HundredThousandByDefault_741) {

    EXPECT_EQ(config.benchmarkResamples(), 100000u);

}



TEST_F(ConfigTest_741, BenchmarkWarmupTime_OneHundredMillisecondsByDefault_741) {

    EXPECT_EQ(config.benchmarkWarmupTime().count(), 100);

}
