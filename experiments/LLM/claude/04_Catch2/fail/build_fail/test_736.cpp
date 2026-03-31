#include "catch2/catch_config.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace Catch;

class ConfigTest_736 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// ===== Default ConfigData Tests =====

TEST_F(ConfigTest_736, DefaultConfig_ShouldDebugBreakIsFalse_736) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}

TEST_F(ConfigTest_736, DefaultConfig_ListTestsIsFalse_736) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_736, DefaultConfig_ListTagsIsFalse_736) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_736, DefaultConfig_ListReportersIsFalse_736) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_736, DefaultConfig_ListListenersIsFalse_736) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_736, DefaultConfig_ShowHelpIsFalse_736) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_736, DefaultConfig_AllowThrowsIsTrue_736) {
    // noThrow defaults to false, so allowThrows should be true
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_736, DefaultConfig_IncludeSuccessfulResultsIsFalse_736) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_736, DefaultConfig_WarnAboutMissingAssertionsIsFalse_736) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_736, DefaultConfig_ZeroTestsCountAsSuccessIsFalse_736) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_736, DefaultConfig_ShowDurationsIsDefault_736) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_736, DefaultConfig_MinDurationIsNegativeOne_736) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_736, DefaultConfig_RunOrderIsDeclared_736) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_736, DefaultConfig_ShardCountIsOne_736) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_736, DefaultConfig_ShardIndexIsZero_736) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_736, DefaultConfig_DefaultColourModeIsPlatformDefault_736) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_736, DefaultConfig_AbortAfterIsNegativeOne_736) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_736, DefaultConfig_ShowInvisiblesIsFalse_736) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_736, DefaultConfig_VerbosityIsNormal_736) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_736, DefaultConfig_SkipBenchmarksIsFalse_736) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_736, DefaultConfig_BenchmarkNoAnalysisIsFalse_736) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_736, DefaultConfig_BenchmarkSamplesIs100_736) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_736, DefaultConfig_BenchmarkConfidenceIntervalIsDefault_736) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_736, DefaultConfig_BenchmarkResamplesIs100000_736) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_736, DefaultConfig_BenchmarkWarmupTimeIs100ms_736) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_736, DefaultConfig_HasTestFiltersIsFalse_736) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_736, DefaultConfig_GetTestsOrTagsIsEmpty_736) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_736, DefaultConfig_GetSectionsToRunIsEmpty_736) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// ===== Custom ConfigData Tests =====

TEST_F(ConfigTest_736, CustomConfig_ShouldDebugBreakTrue_736) {
    ConfigData data;
    data.shouldDebugBreak = true;
    Config config(data);
    EXPECT_TRUE(config.shouldDebugBreak());
}

TEST_F(ConfigTest_736, CustomConfig_ListTestsTrue_736) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_736, CustomConfig_ListTagsTrue_736) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_736, CustomConfig_ListReportersTrue_736) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_736, CustomConfig_ListListenersTrue_736) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_736, CustomConfig_ShowHelpTrue_736) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_736, CustomConfig_NoThrowDisablesAllowThrows_736) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_736, CustomConfig_ShowSuccessfulTestsTrue_736) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_736, CustomConfig_AllowZeroTestsTrue_736) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_736, CustomConfig_AbortAfterCustomValue_736) {
    ConfigData data;
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_736, CustomConfig_ShowInvisiblesTrue_736) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_736, CustomConfig_VerbosityHigh_736) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_736, CustomConfig_VerbosityQuiet_736) {
    ConfigData data;
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_736, CustomConfig_SkipBenchmarksTrue_736) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_736, CustomConfig_BenchmarkNoAnalysisTrue_736) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_736, CustomConfig_BenchmarkSamples_736) {
    ConfigData data;
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_736, CustomConfig_BenchmarkConfidenceInterval_736) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_736, CustomConfig_BenchmarkResamples_736) {
    ConfigData data;
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

TEST_F(ConfigTest_736, CustomConfig_BenchmarkWarmupTime_736) {
    ConfigData data;
    data.benchmarkWarmupTime = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

TEST_F(ConfigTest_736, CustomConfig_ShowDurationsAlways_736) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_736, CustomConfig_ShowDurationsNever_736) {
    ConfigData data;
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_736, CustomConfig_MinDuration_736) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_736, CustomConfig_RunOrderRandomized_736) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_736, CustomConfig_RngSeed_736) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

TEST_F(ConfigTest_736, CustomConfig_ShardCount_736) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_736, CustomConfig_ShardIndex_736) {
    ConfigData data;
    data.shardIndex = 2;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 2u);
}

TEST_F(ConfigTest_736, CustomConfig_ProcessName_736) {
    ConfigData data;
    data.processName = "my_test_process";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("my_test_process"));
}

TEST_F(ConfigTest_736, CustomConfig_EmptyProcessName_736) {
    ConfigData data;
    data.processName = "";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_736, CustomConfig_TestsOrTags_736) {
    ConfigData data;
    data.testsOrTags = {"[tag1]", "test_name"};
    Config config(data);
    const auto& testsOrTags = config.getTestsOrTags();
    EXPECT_EQ(testsOrTags.size(), 2u);
    EXPECT_EQ(testsOrTags[0], "[tag1]");
    EXPECT_EQ(testsOrTags[1], "test_name");
}

TEST_F(ConfigTest_736, CustomConfig_HasTestFiltersWhenTestsOrTagsProvided_736) {
    ConfigData data;
    data.testsOrTags = {"some_test"};
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_736, CustomConfig_SectionsToRun_736) {
    ConfigData data;
    data.sectionsToRun = {"section1", "section2"};
    Config config(data);
    const auto& sections = config.getSectionsToRun();
    EXPECT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

// ===== Boundary Tests =====

TEST_F(ConfigTest_736, BoundaryConfig_AbortAfterZero_736) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_736, BoundaryConfig_AbortAfterMaxInt_736) {
    ConfigData data;
    data.abortAfter = std::numeric_limits<int>::max();
    Config config(data);
    EXPECT_EQ(config.abortAfter(), std::numeric_limits<int>::max());
}

TEST_F(ConfigTest_736, BoundaryConfig_BenchmarkSamplesZero_736) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

TEST_F(ConfigTest_736, BoundaryConfig_BenchmarkResamplesZero_736) {
    ConfigData data;
    data.benchmarkResamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

TEST_F(ConfigTest_736, BoundaryConfig_BenchmarkWarmupTimeZero_736) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_736, BoundaryConfig_MinDurationZero_736) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_736, BoundaryConfig_BenchmarkConfidenceIntervalZero_736) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_736, BoundaryConfig_BenchmarkConfidenceIntervalOne_736) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 1.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

TEST_F(ConfigTest_736, BoundaryConfig_RngSeedZero_736) {
    ConfigData data;
    data.rngSeed = 0;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0u);
}

TEST_F(ConfigTest_736, BoundaryConfig_RngSeedMax_736) {
    ConfigData data;
    data.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(data);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

TEST_F(ConfigTest_736, BoundaryConfig_EmptyTestsOrTags_736) {
    ConfigData data;
    data.testsOrTags = {};
    Config config(data);
    EXPECT_TRUE(config.getTestsOrTags().empty());
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_736, BoundaryConfig_EmptySectionsToRun_736) {
    ConfigData data;
    data.sectionsToRun = {};
    Config config(data);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// ===== Warning Tests =====

TEST_F(ConfigTest_736, CustomConfig_WarningsNothing_736) {
    ConfigData data;
    data.warnings = WarnAbout::Nothing;
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

// ===== Multiple Config Instances =====

TEST_F(ConfigTest_736, MultipleConfigs_IndependentState_736) {
    ConfigData data1;
    data1.shouldDebugBreak = true;
    data1.abortAfter = 10;

    ConfigData data2;
    data2.shouldDebugBreak = false;
    data2.abortAfter = 5;

    Config config1(data1);
    Config config2(data2);

    EXPECT_TRUE(config1.shouldDebugBreak());
    EXPECT_FALSE(config2.shouldDebugBreak());
    EXPECT_EQ(config1.abortAfter(), 10);
    EXPECT_EQ(config2.abortAfter(), 5);
}

// ===== ColourMode Tests =====

TEST_F(ConfigTest_736, CustomConfig_ColourModeAnsi_736) {
    ConfigData data;
    data.defaultColourMode = ColourMode::ANSI;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_736, CustomConfig_ColourModeNone_736) {
    ConfigData data;
    data.defaultColourMode = ColourMode::None;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::None);
}
