#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_744 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// Test default construction values
TEST_F(ConfigTest_744, DefaultListTests_744) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_744, DefaultListTags_744) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_744, DefaultListReporters_744) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_744, DefaultListListeners_744) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_744, DefaultShowHelp_744) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_744, DefaultAllowThrows_744) {
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_744, DefaultIncludeSuccessfulResults_744) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_744, DefaultShowInvisibles_744) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_744, DefaultAbortAfter_744) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_744, DefaultShardCount_744) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_744, DefaultShardIndex_744) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_744, DefaultSkipBenchmarks_744) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_744, DefaultBenchmarkNoAnalysis_744) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_744, DefaultBenchmarkSamples_744) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_744, DefaultBenchmarkConfidenceInterval_744) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_744, DefaultBenchmarkResamples_744) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_744, DefaultBenchmarkWarmupTime_744) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_744, DefaultVerbosity_744) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_744, DefaultShowDurations_744) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_744, DefaultMinDuration_744) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_744, DefaultRunOrder_744) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_744, DefaultColourMode_744) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_744, DefaultZeroTestsCountAsSuccess_744) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_744, DefaultHasTestFilters_744) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_744, DefaultGetTestsOrTagsEmpty_744) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_744, DefaultGetSectionsToRunEmpty_744) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// Tests with custom ConfigData values
TEST_F(ConfigTest_744, ListTestsTrue_744) {
    defaultData.listTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_744, ListTagsTrue_744) {
    defaultData.listTags = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_744, ListReportersTrue_744) {
    defaultData.listReporters = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_744, ListListenersTrue_744) {
    defaultData.listListeners = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_744, ShowHelpTrue_744) {
    defaultData.showHelp = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_744, NoThrowDisablesAllowThrows_744) {
    defaultData.noThrow = true;
    Config config(defaultData);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_744, ShowSuccessfulTestsEnablesIncludeSuccessfulResults_744) {
    defaultData.showSuccessfulTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_744, ShowInvisiblesTrue_744) {
    defaultData.showInvisibles = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_744, CustomAbortAfter_744) {
    defaultData.abortAfter = 5;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_744, CustomShardCount_744) {
    defaultData.shardCount = 4;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_744, CustomShardIndex_744) {
    defaultData.shardIndex = 3;
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 3u);
}

TEST_F(ConfigTest_744, SkipBenchmarksTrue_744) {
    defaultData.skipBenchmarks = true;
    Config config(defaultData);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_744, BenchmarkNoAnalysisTrue_744) {
    defaultData.benchmarkNoAnalysis = true;
    Config config(defaultData);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_744, CustomBenchmarkSamples_744) {
    defaultData.benchmarkSamples = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_744, CustomBenchmarkConfidenceInterval_744) {
    defaultData.benchmarkConfidenceInterval = 0.99;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_744, CustomBenchmarkResamples_744) {
    defaultData.benchmarkResamples = 200000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 200000u);
}

TEST_F(ConfigTest_744, CustomBenchmarkWarmupTime_744) {
    defaultData.benchmarkWarmupTime = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

TEST_F(ConfigTest_744, CustomVerbosity_744) {
    defaultData.verbosity = Verbosity::High;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_744, CustomShowDurations_744) {
    defaultData.showDurations = ShowDurations::Always;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_744, CustomMinDuration_744) {
    defaultData.minDuration = 0.5;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_744, CustomRunOrder_744) {
    defaultData.runOrder = TestRunOrder::Randomized;
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_744, CustomColourMode_744) {
    defaultData.defaultColourMode = ColourMode::ANSI;
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_744, AllowZeroTestsTrue_744) {
    defaultData.allowZeroTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_744, CustomProcessName_744) {
    defaultData.processName = "TestProcess";
    Config config(defaultData);
    EXPECT_EQ(config.name(), "TestProcess");
}

TEST_F(ConfigTest_744, EmptyProcessName_744) {
    defaultData.processName = "";
    Config config(defaultData);
    EXPECT_EQ(config.name(), "");
}

TEST_F(ConfigTest_744, TestsOrTagsPopulated_744) {
    defaultData.testsOrTags = {"[tag1]", "testName"};
    Config config(defaultData);
    EXPECT_EQ(config.getTestsOrTags().size(), 2u);
    EXPECT_EQ(config.getTestsOrTags()[0], "[tag1]");
    EXPECT_EQ(config.getTestsOrTags()[1], "testName");
}

TEST_F(ConfigTest_744, HasTestFiltersWhenTestsOrTagsNotEmpty_744) {
    defaultData.testsOrTags = {"someTest"};
    Config config(defaultData);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_744, SectionsToRunPopulated_744) {
    defaultData.sectionsToRun = {"section1", "section2"};
    Config config(defaultData);
    EXPECT_EQ(config.getSectionsToRun().size(), 2u);
    EXPECT_EQ(config.getSectionsToRun()[0], "section1");
    EXPECT_EQ(config.getSectionsToRun()[1], "section2");
}

TEST_F(ConfigTest_744, WarnAboutMissingAssertionsDefault_744) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_744, WarnAboutUnmatchedTestSpecsDefault_744) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_744, CustomRngSeed_744) {
    defaultData.rngSeed = 42;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// Boundary tests
TEST_F(ConfigTest_744, AbortAfterZero_744) {
    defaultData.abortAfter = 0;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_744, BenchmarkSamplesZero_744) {
    defaultData.benchmarkSamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

TEST_F(ConfigTest_744, BenchmarkResamplesZero_744) {
    defaultData.benchmarkResamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

TEST_F(ConfigTest_744, BenchmarkWarmupTimeZero_744) {
    defaultData.benchmarkWarmupTime = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_744, BenchmarkConfidenceIntervalZero_744) {
    defaultData.benchmarkConfidenceInterval = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_744, BenchmarkConfidenceIntervalOne_744) {
    defaultData.benchmarkConfidenceInterval = 1.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

TEST_F(ConfigTest_744, MinDurationZero_744) {
    defaultData.minDuration = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_744, ShardCountLargeValue_744) {
    defaultData.shardCount = 1000;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1000u);
}

TEST_F(ConfigTest_744, ShardIndexLargeValue_744) {
    defaultData.shardIndex = 999;
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 999u);
}

TEST_F(ConfigTest_744, RngSeedMaxValue_744) {
    defaultData.rngSeed = UINT32_MAX;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), UINT32_MAX);
}

TEST_F(ConfigTest_744, VerbosityQuiet_744) {
    defaultData.verbosity = Verbosity::Quiet;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_744, ShowDurationsNever_744) {
    defaultData.showDurations = ShowDurations::Never;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_744, RunOrderLexicographic_744) {
    defaultData.runOrder = TestRunOrder::LexicographicallySorted;
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::LexicographicallySorted);
}

TEST_F(ConfigTest_744, DefaultConstructor_744) {
    Config config;
    // Default constructed config should have default ConfigData values
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.listTags());
    EXPECT_EQ(config.benchmarkSamples(), 100u);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_744, GetReporterSpecsDefault_744) {
    Config config(defaultData);
    // With default data, reporter specs should be empty
    EXPECT_TRUE(config.getReporterSpecs().empty());
}

TEST_F(ConfigTest_744, TestSpecDefault_744) {
    Config config(defaultData);
    // With no tests or tags, testSpec should exist but match nothing specific
    const TestSpec& spec = config.testSpec();
    // Just verify it's accessible without crashing
    (void)spec;
}

TEST_F(ConfigTest_744, ShouldDebugBreakDefault_744) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}

TEST_F(ConfigTest_744, BenchmarkResamplesLargeValue_744) {
    defaultData.benchmarkResamples = 1000000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 1000000u);
}

TEST_F(ConfigTest_744, BenchmarkSamplesLargeValue_744) {
    defaultData.benchmarkSamples = 10000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 10000u);
}

TEST_F(ConfigTest_744, BenchmarkWarmupTimeLargeValue_744) {
    defaultData.benchmarkWarmupTime = 10000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(10000));
}
