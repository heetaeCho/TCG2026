#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_745 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// ============ Default Values Tests ============

TEST_F(ConfigTest_745, DefaultListTestsIsFalse_745) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_745, DefaultListTagsIsFalse_745) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_745, DefaultListReportersIsFalse_745) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_745, DefaultListListenersIsFalse_745) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_745, DefaultShowHelpIsFalse_745) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_745, DefaultAllowThrowsIsTrue_745) {
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_745, DefaultIncludeSuccessfulResultsIsFalse_745) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_745, DefaultWarnAboutMissingAssertionsIsFalse_745) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_745, DefaultWarnAboutUnmatchedTestSpecsIsFalse_745) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_745, DefaultZeroTestsCountAsSuccessIsFalse_745) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_745, DefaultShowDurationsIsDefaultForReporter_745) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_745, DefaultMinDurationIsNegativeOne_745) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_745, DefaultRunOrderIsDeclared_745) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_745, DefaultShardCountIsOne_745) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_745, DefaultShardIndexIsZero_745) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_745, DefaultColourModeIsPlatformDefault_745) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_745, DefaultAbortAfterIsNegativeOne_745) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_745, DefaultShowInvisiblesIsFalse_745) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_745, DefaultVerbosityIsNormal_745) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_745, DefaultSkipBenchmarksIsFalse_745) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_745, DefaultBenchmarkNoAnalysisIsFalse_745) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_745, DefaultBenchmarkSamplesIs100_745) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_745, DefaultBenchmarkConfidenceIntervalIs095_745) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_745, DefaultBenchmarkResamplesIs100000_745) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_745, DefaultBenchmarkWarmupTimeIs100ms_745) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_745, DefaultHasTestFiltersIsFalse_745) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_745, DefaultGetTestsOrTagsIsEmpty_745) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_745, DefaultGetSectionsToRunIsEmpty_745) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// ============ Custom Values Tests ============

TEST_F(ConfigTest_745, ListTestsReturnsTrue_745) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_745, ListTagsReturnsTrue_745) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_745, ListReportersReturnsTrue_745) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_745, ListListenersReturnsTrue_745) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_745, ShowHelpReturnsTrue_745) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_745, NoThrowDisablesAllowThrows_745) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_745, ShowSuccessfulTestsEnablesIncludeSuccessfulResults_745) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_745, AllowZeroTestsEnablesZeroTestsCountAsSuccess_745) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_745, ShowInvisiblesReturnsTrue_745) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_745, SkipBenchmarksReturnsTrue_745) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_745, BenchmarkNoAnalysisReturnsTrue_745) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_745, CustomAbortAfterValue_745) {
    ConfigData data;
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_745, CustomBenchmarkSamples_745) {
    ConfigData data;
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_745, CustomBenchmarkConfidenceInterval_745) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_745, CustomBenchmarkResamples_745) {
    ConfigData data;
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

TEST_F(ConfigTest_745, CustomBenchmarkWarmupTime_745) {
    ConfigData data;
    data.benchmarkWarmupTime = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

TEST_F(ConfigTest_745, CustomVerbosityHigh_745) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_745, CustomVerbosityQuiet_745) {
    ConfigData data;
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_745, CustomRunOrderRandomized_745) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_745, CustomShardCount_745) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_745, CustomShardIndex_745) {
    ConfigData data;
    data.shardIndex = 2;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 2u);
}

TEST_F(ConfigTest_745, CustomMinDuration_745) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_745, CustomShowDurationsAlways_745) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_745, CustomShowDurationsNever_745) {
    ConfigData data;
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_745, CustomProcessName_745) {
    ConfigData data;
    data.processName = "my_test_process";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("my_test_process"));
}

TEST_F(ConfigTest_745, EmptyProcessNameReturnsEmpty_745) {
    ConfigData data;
    data.processName = "";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_745, TestsOrTagsSetsHasTestFilters_745) {
    ConfigData data;
    data.testsOrTags.push_back("some_test");
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_745, TestsOrTagsAreReturned_745) {
    ConfigData data;
    data.testsOrTags.push_back("test1");
    data.testsOrTags.push_back("test2");
    Config config(data);
    auto const& result = config.getTestsOrTags();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "test1");
    EXPECT_EQ(result[1], "test2");
}

TEST_F(ConfigTest_745, SectionsToRunAreReturned_745) {
    ConfigData data;
    data.sectionsToRun.push_back("section1");
    data.sectionsToRun.push_back("section2");
    Config config(data);
    auto const& result = config.getSectionsToRun();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "section1");
    EXPECT_EQ(result[1], "section2");
}

// ============ Boundary Tests ============

TEST_F(ConfigTest_745, BenchmarkWarmupTimeZero_745) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_745, BenchmarkSamplesZero_745) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

TEST_F(ConfigTest_745, BenchmarkResamplesZero_745) {
    ConfigData data;
    data.benchmarkResamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

TEST_F(ConfigTest_745, AbortAfterZero_745) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_745, MinDurationZero_745) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_745, BenchmarkConfidenceIntervalZero_745) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_745, BenchmarkConfidenceIntervalOne_745) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 1.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

TEST_F(ConfigTest_745, LargeBenchmarkWarmupTime_745) {
    ConfigData data;
    data.benchmarkWarmupTime = 10000;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(10000));
}

TEST_F(ConfigTest_745, CustomRngSeed_745) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

TEST_F(ConfigTest_745, RngSeedMaxValue_745) {
    ConfigData data;
    data.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(data);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

TEST_F(ConfigTest_745, ColourModeAnsiColours_745) {
    ConfigData data;
    data.defaultColourMode = ColourMode::ANSI;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_745, ColourModeNone_745) {
    ConfigData data;
    data.defaultColourMode = ColourMode::None;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::None);
}

// ============ Warning Configuration Tests ============

TEST_F(ConfigTest_745, WarnAboutMissingAssertionsWhenSet_745) {
    ConfigData data;
    data.warnings = WarnAbout::NoAssertions;
    Config config(data);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_745, DefaultShouldDebugBreakIsFalse_745) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}

// ============ Copy of ConfigData Test ============

TEST_F(ConfigTest_745, ConfigPreservesMultipleSettings_745) {
    ConfigData data;
    data.listTests = true;
    data.showHelp = true;
    data.noThrow = true;
    data.showInvisibles = true;
    data.skipBenchmarks = true;
    data.abortAfter = 10;
    data.benchmarkSamples = 200;
    data.benchmarkWarmupTime = 250;
    data.verbosity = Verbosity::High;
    
    Config config(data);
    
    EXPECT_TRUE(config.listTests());
    EXPECT_TRUE(config.showHelp());
    EXPECT_FALSE(config.allowThrows());
    EXPECT_TRUE(config.showInvisibles());
    EXPECT_TRUE(config.skipBenchmarks());
    EXPECT_EQ(config.abortAfter(), 10);
    EXPECT_EQ(config.benchmarkSamples(), 200u);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(250));
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}
