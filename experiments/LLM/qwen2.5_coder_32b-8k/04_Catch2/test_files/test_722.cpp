#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest_722 : public ::testing::Test {

protected:

    ConfigData data;

    Config config;



    void SetUp() override {

        data.showHelp = false;

        config = Config(data);

    }

};



TEST_F(ConfigTest_722, ShowHelpReturnsFalseByDefault_722) {

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_722, ShowHelpReturnsTrueWhenSetToTrue_722) {

    data.showHelp = true;

    Config configWithHelp(data);

    EXPECT_TRUE(configWithHelp.showHelp());

}



TEST_F(ConfigTest_722, ListTestsReturnsFalseByDefault_722) {

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_722, ListTagsReturnsFalseByDefault_722) {

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_722, ListReportersReturnsFalseByDefault_722) {

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_722, ListListenersReturnsFalseByDefault_722) {

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_722, GetReporterSpecsReturnsEmptyVectorByDefault_722) {

    EXPECT_TRUE(config.getReporterSpecs().empty());

}



TEST_F(ConfigTest_722, GetProcessedReporterSpecsReturnsEmptyVectorByDefault_722) {

    EXPECT_TRUE(config.getProcessedReporterSpecs().empty());

}



TEST_F(ConfigTest_722, GetTestsOrTagsReturnsEmptyVectorByDefault_722) {

    EXPECT_TRUE(config.getTestsOrTags().empty());

}



TEST_F(ConfigTest_722, GetSectionsToRunReturnsEmptyVectorByDefault_722) {

    EXPECT_TRUE(config.getSectionsToRun().empty());

}



TEST_F(ConfigTest_722, HasTestFiltersReturnsFalseByDefault_722) {

    EXPECT_FALSE(config.hasTestFilters());

}



TEST_F(ConfigTest_722, AllowThrowsReturnsTrueByDefault_722) {

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_722, IncludeSuccessfulResultsReturnsFalseByDefault_722) {

    EXPECT_FALSE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_722, WarnAboutMissingAssertionsReturnsFalseByDefault_722) {

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_722, WarnAboutUnmatchedTestSpecsReturnsFalseByDefault_722) {

    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_722, ZeroTestsCountAsSuccessReturnsFalseByDefault_722) {

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_722, ShowDurationsReturnsDefaultForReporterByDefault_722) {

    EXPECT_EQ(ShowDurations::DefaultForReporter, config.showDurations());

}



TEST_F(ConfigTest_722, MinDurationReturnsNegativeOneByDefault_722) {

    EXPECT_DOUBLE_EQ(-1.0, config.minDuration());

}



TEST_F(ConfigTest_722, RunOrderReturnsDeclaredByDefault_722) {

    EXPECT_EQ(TestRunOrder::Declared, config.runOrder());

}



TEST_F(ConfigTest_722, ShardCountReturnsOneByDefault_722) {

    EXPECT_EQ(1u, config.shardCount());

}



TEST_F(ConfigTest_722, ShardIndexReturnsZeroByDefault_722) {

    EXPECT_EQ(0u, config.shardIndex());

}



TEST_F(ConfigTest_722, DefaultColourModeReturnsPlatformDefaultByDefault_722) {

    EXPECT_EQ(ColourMode::PlatformDefault, config.defaultColourMode());

}



TEST_F(ConfigTest_722, ShouldDebugBreakReturnsFalseByDefault_722) {

    EXPECT_FALSE(config.shouldDebugBreak());

}



TEST_F(ConfigTest_722, AbortAfterReturnsNegativeOneByDefault_722) {

    EXPECT_EQ(-1, config.abortAfter());

}



TEST_F(ConfigTest_722, ShowInvisiblesReturnsFalseByDefault_722) {

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_722, VerbosityReturnsNormalByDefault_722) {

    EXPECT_EQ(Verbosity::Normal, config.verbosity());

}



TEST_F(ConfigTest_722, SkipBenchmarksReturnsFalseByDefault_722) {

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_722, BenchmarkNoAnalysisReturnsFalseByDefault_722) {

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_722, BenchmarkSamplesReturnsHundredByDefault_722) {

    EXPECT_EQ(100u, config.benchmarkSamples());

}



TEST_F(ConfigTest_722, BenchmarkConfidenceIntervalReturnsExpectedValueByDefault_722) {

    EXPECT_DOUBLE_EQ(0.94999999999999996, config.benchmarkConfidenceInterval());

}



TEST_F(ConfigTest_722, BenchmarkResamplesReturnsHundredThousandByDefault_722) {

    EXPECT_EQ(100000u, config.benchmarkResamples());

}



TEST_F(ConfigTest_722, BenchmarkWarmupTimeReturnsOneHundredMillisecondsByDefault_722) {

    EXPECT_EQ(std::chrono::milliseconds::rep{100}, config.benchmarkWarmupTime().count());

}
