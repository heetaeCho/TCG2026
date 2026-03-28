#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"

#include <vector>

#include <string>



using namespace Catch;



TEST_F(ConfigTest_739, VerbosityReturnsDefault_739) {

    Config config;

    EXPECT_EQ(config.verbosity(), Verbosity::Normal);

}



TEST_F(ConfigTest_739, VerbosityReflectsConfigData_739) {

    ConfigData data;

    data.verbosity = Verbosity::Quiet;

    Config config(data);

    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);

}



TEST_F(ConfigTest_739, ListTestsDefaultsToFalse_739) {

    Config config;

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_739, ListTagsDefaultsToFalse_739) {

    Config config;

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_739, ListReportersDefaultsToFalse_739) {

    Config config;

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_739, ListListenersDefaultsToFalse_739) {

    Config config;

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_739, ShowHelpDefaultsToFalse_739) {

    Config config;

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_739, AllowThrowsDefaultsToTrue_739) {

    Config config;

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_739, IncludeSuccessfulResultsDefaultsToFalse_739) {

    Config config;

    EXPECT_FALSE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_739, WarnAboutMissingAssertionsDefaultsToFalse_739) {

    Config config;

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_739, WarnAboutUnmatchedTestSpecsDefaultsToFalse_739) {

    Config config;

    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_739, ZeroTestsCountAsSuccessDefaultsToFalse_739) {

    Config config;

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_739, ShowDurationsDefaultsToDefaultForReporter_739) {

    Config config;

    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);

}



TEST_F(ConfigTest_739, MinDurationDefaultsToNegativeOne_739) {

    Config config;

    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);

}



TEST_F(ConfigTest_739, RunOrderDefaultsToDeclared_739) {

    Config config;

    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);

}



TEST_F(ConfigTest_739, DefaultColourModeDefaultsToPlatformDefault_739) {

    Config config;

    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);

}



TEST_F(ConfigTest_739, ShouldDebugBreakDefaultsToFalse_739) {

    Config config;

    EXPECT_FALSE(config.shouldDebugBreak());

}



TEST_F(ConfigTest_739, AbortAfterDefaultsToNegativeOne_739) {

    Config config;

    EXPECT_EQ(config.abortAfter(), -1);

}



TEST_F(ConfigTest_739, ShowInvisiblesDefaultsToFalse_739) {

    Config config;

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_739, SkipBenchmarksDefaultsToFalse_739) {

    Config config;

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_739, BenchmarkNoAnalysisDefaultsToFalse_739) {

    Config config;

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_739, BenchmarkSamplesDefaultsToOneHundred_739) {

    Config config;

    EXPECT_EQ(config.benchmarkSamples(), 100);

}



TEST_F(ConfigTest_739, BenchmarkConfidenceIntervalDefaultsToSpecificValue_739) {

    Config config;

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.94999999999999996);

}



TEST_F(ConfigTest_739, BenchmarkResamplesDefaultsToOneHundredThousand_739) {

    Config config;

    EXPECT_EQ(config.benchmarkResamples(), 100000);

}



TEST_F(ConfigTest_739, BenchmarkWarmupTimeDefaultsToOneHundredMilliseconds_739) {

    Config config;

    EXPECT_EQ(config.benchmarkWarmupTime().count(), 100);

}



TEST_F(ConfigTest_739, GetReporterSpecsReturnsEmptyVectorByDefault_739) {

    Config config;

    EXPECT_TRUE(config.getReporterSpecs().empty());

}



TEST_F(ConfigTest_739, GetProcessedReporterSpecsReturnsEmptyVectorByDefault_739) {

    Config config;

    EXPECT_TRUE(config.getProcessedReporterSpecs().empty());

}



TEST_F(ConfigTest_739, GetTestsOrTagsReturnsEmptyVectorByDefault_739) {

    Config config;

    EXPECT_TRUE(config.getTestsOrTags().empty());

}



TEST_F(ConfigTest_739, GetSectionsToRunReturnsEmptyVectorByDefault_739) {

    Config config;

    EXPECT_TRUE(config.getSectionsToRun().empty());

}
