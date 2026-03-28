#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_734 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// --- Default values tests ---

TEST_F(ConfigTest_734, DefaultListTestsIsFalse_734) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_734, DefaultListTagsIsFalse_734) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_734, DefaultListReportersIsFalse_734) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_734, DefaultListListenersIsFalse_734) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_734, DefaultShowHelpIsFalse_734) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_734, DefaultAllowThrowsIsTrue_734) {
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_734, DefaultIncludeSuccessfulResultsIsFalse_734) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_734, DefaultWarnAboutMissingAssertionsIsFalse_734) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_734, DefaultWarnAboutUnmatchedTestSpecsIsFalse_734) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_734, DefaultZeroTestsCountAsSuccessIsFalse_734) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_734, DefaultShowDurationsIsDefaultForReporter_734) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_734, DefaultMinDurationIsNegativeOne_734) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_734, DefaultRunOrderIsDeclared_734) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_734, DefaultShardCountIsOne_734) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_734, DefaultShardIndexIsZero_734) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_734, DefaultColourModeIsPlatformDefault_734) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_734, DefaultAbortAfterIsNegativeOne_734) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_734, DefaultShowInvisiblesIsFalse_734) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_734, DefaultVerbosityIsNormal_734) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_734, DefaultSkipBenchmarksIsFalse_734) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_734, DefaultBenchmarkNoAnalysisIsFalse_734) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_734, DefaultBenchmarkSamplesIs100_734) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_734, DefaultBenchmarkConfidenceInterval_734) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_734, DefaultBenchmarkResamplesIs100000_734) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_734, DefaultBenchmarkWarmupTimeIs100ms_734) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_734, DefaultShouldDebugBreakIsFalse_734) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}

TEST_F(ConfigTest_734, DefaultHasTestFiltersIsFalse_734) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_734, DefaultTestsOrTagsIsEmpty_734) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_734, DefaultSectionsToRunIsEmpty_734) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// --- Custom values tests ---

TEST_F(ConfigTest_734, ListTestsSetToTrue_734) {
    defaultData.listTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_734, ListTagsSetToTrue_734) {
    defaultData.listTags = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_734, ListReportersSetToTrue_734) {
    defaultData.listReporters = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_734, ListListenersSetToTrue_734) {
    defaultData.listListeners = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_734, ShowHelpSetToTrue_734) {
    defaultData.showHelp = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_734, NoThrowDisablesAllowThrows_734) {
    defaultData.noThrow = true;
    Config config(defaultData);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_734, ShowSuccessfulTestsEnablesIncludeSuccessfulResults_734) {
    defaultData.showSuccessfulTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_734, AllowZeroTestsEnablesZeroTestsCountAsSuccess_734) {
    defaultData.allowZeroTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_734, ShowInvisiblesSetToTrue_734) {
    defaultData.showInvisibles = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_734, VerbositySetToHigh_734) {
    defaultData.verbosity = Verbosity::High;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_734, VerbositySetToQuiet_734) {
    defaultData.verbosity = Verbosity::Quiet;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_734, SkipBenchmarksSetToTrue_734) {
    defaultData.skipBenchmarks = true;
    Config config(defaultData);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_734, BenchmarkNoAnalysisSetToTrue_734) {
    defaultData.benchmarkNoAnalysis = true;
    Config config(defaultData);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_734, CustomBenchmarkSamples_734) {
    defaultData.benchmarkSamples = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_734, CustomBenchmarkConfidenceInterval_734) {
    defaultData.benchmarkConfidenceInterval = 0.99;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_734, CustomBenchmarkResamples_734) {
    defaultData.benchmarkResamples = 200000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 200000u);
}

TEST_F(ConfigTest_734, CustomBenchmarkWarmupTime_734) {
    defaultData.benchmarkWarmupTime = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

TEST_F(ConfigTest_734, CustomAbortAfter_734) {
    defaultData.abortAfter = 5;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_734, AbortAfterZero_734) {
    defaultData.abortAfter = 0;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_734, CustomShardCount_734) {
    defaultData.shardCount = 4;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_734, CustomShardIndex_734) {
    defaultData.shardIndex = 3;
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 3u);
}

TEST_F(ConfigTest_734, CustomRngSeed_734) {
    defaultData.rngSeed = 42;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 42u);
}

TEST_F(ConfigTest_734, RunOrderRandomized_734) {
    defaultData.runOrder = TestRunOrder::Randomized;
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_734, ShowDurationsAlways_734) {
    defaultData.showDurations = ShowDurations::Always;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_734, ShowDurationsNever_734) {
    defaultData.showDurations = ShowDurations::Never;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_734, CustomMinDuration_734) {
    defaultData.minDuration = 0.5;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_734, MinDurationZero_734) {
    defaultData.minDuration = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_734, CustomProcessName_734) {
    defaultData.processName = "MyTestProcess";
    Config config(defaultData);
    EXPECT_EQ(config.name(), "MyTestProcess");
}

TEST_F(ConfigTest_734, EmptyProcessName_734) {
    defaultData.processName = "";
    Config config(defaultData);
    EXPECT_EQ(config.name(), "");
}

TEST_F(ConfigTest_734, TestsOrTagsWithEntries_734) {
    defaultData.testsOrTags = {"test1", "test2", "[tag1]"};
    Config config(defaultData);
    auto const& result = config.getTestsOrTags();
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "test1");
    EXPECT_EQ(result[1], "test2");
    EXPECT_EQ(result[2], "[tag1]");
}

TEST_F(ConfigTest_734, SectionsToRunWithEntries_734) {
    defaultData.sectionsToRun = {"section1", "section2"};
    Config config(defaultData);
    auto const& result = config.getSectionsToRun();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "section1");
    EXPECT_EQ(result[1], "section2");
}

TEST_F(ConfigTest_734, HasTestFiltersWhenTestsOrTagsProvided_734) {
    defaultData.testsOrTags = {"someTest"};
    Config config(defaultData);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_734, HasTestFiltersWhenTestsOrTagsEmpty_734) {
    defaultData.testsOrTags = {};
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_734, ColourModeAnsiEscape_734) {
    defaultData.defaultColourMode = ColourMode::ANSI;
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_734, ColourModeNone_734) {
    defaultData.defaultColourMode = ColourMode::None;
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::None);
}

// --- Boundary conditions ---

TEST_F(ConfigTest_734, ShardIndexMaxValue_734) {
    defaultData.shardIndex = std::numeric_limits<unsigned int>::max();
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), std::numeric_limits<unsigned int>::max());
}

TEST_F(ConfigTest_734, ShardCountMaxValue_734) {
    defaultData.shardCount = std::numeric_limits<unsigned int>::max();
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), std::numeric_limits<unsigned int>::max());
}

TEST_F(ConfigTest_734, BenchmarkSamplesZero_734) {
    defaultData.benchmarkSamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

TEST_F(ConfigTest_734, BenchmarkResamplesZero_734) {
    defaultData.benchmarkResamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

TEST_F(ConfigTest_734, BenchmarkWarmupTimeZero_734) {
    defaultData.benchmarkWarmupTime = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_734, BenchmarkConfidenceIntervalZero_734) {
    defaultData.benchmarkConfidenceInterval = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_734, BenchmarkConfidenceIntervalOne_734) {
    defaultData.benchmarkConfidenceInterval = 1.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

TEST_F(ConfigTest_734, RngSeedZero_734) {
    defaultData.rngSeed = 0;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 0u);
}

TEST_F(ConfigTest_734, RngSeedMaxValue_734) {
    defaultData.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

// --- Default constructor test ---

TEST_F(ConfigTest_734, DefaultConstructorCreatesValidConfig_734) {
    Config config;
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.listTags());
    EXPECT_EQ(config.shardIndex(), 0u);
    EXPECT_EQ(config.shardCount(), 1u);
}

// --- Multiple configurations combined ---

TEST_F(ConfigTest_734, MultipleSettingsCombined_734) {
    defaultData.listTests = true;
    defaultData.showHelp = true;
    defaultData.noThrow = true;
    defaultData.showSuccessfulTests = true;
    defaultData.abortAfter = 10;
    defaultData.shardCount = 8;
    defaultData.shardIndex = 5;
    defaultData.verbosity = Verbosity::High;
    defaultData.processName = "CombinedTest";

    Config config(defaultData);

    EXPECT_TRUE(config.listTests());
    EXPECT_TRUE(config.showHelp());
    EXPECT_FALSE(config.allowThrows());
    EXPECT_TRUE(config.includeSuccessfulResults());
    EXPECT_EQ(config.abortAfter(), 10);
    EXPECT_EQ(config.shardCount(), 8u);
    EXPECT_EQ(config.shardIndex(), 5u);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
    EXPECT_EQ(config.name(), "CombinedTest");
}
