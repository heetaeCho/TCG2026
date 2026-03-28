#include "catch2/catch_config.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <chrono>

using namespace Catch;

class ConfigTest_738 : public ::testing::Test {
protected:
    ConfigData makeDefaultData() {
        ConfigData data;
        return data;
    }
};

// ==================== Default Values Tests ====================

TEST_F(ConfigTest_738, DefaultListTests_738) {
    Config config(makeDefaultData());
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_738, DefaultListTags_738) {
    Config config(makeDefaultData());
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_738, DefaultListReporters_738) {
    Config config(makeDefaultData());
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_738, DefaultListListeners_738) {
    Config config(makeDefaultData());
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_738, DefaultShowHelp_738) {
    Config config(makeDefaultData());
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_738, DefaultShowInvisibles_738) {
    Config config(makeDefaultData());
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_738, DefaultIncludeSuccessfulResults_738) {
    Config config(makeDefaultData());
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_738, DefaultAllowThrows_738) {
    // noThrow defaults to false, so allowThrows should be true
    Config config(makeDefaultData());
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_738, DefaultAbortAfter_738) {
    Config config(makeDefaultData());
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_738, DefaultShardCount_738) {
    Config config(makeDefaultData());
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_738, DefaultShardIndex_738) {
    Config config(makeDefaultData());
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_738, DefaultSkipBenchmarks_738) {
    Config config(makeDefaultData());
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_738, DefaultBenchmarkNoAnalysis_738) {
    Config config(makeDefaultData());
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_738, DefaultBenchmarkSamples_738) {
    Config config(makeDefaultData());
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_738, DefaultBenchmarkConfidenceInterval_738) {
    Config config(makeDefaultData());
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_738, DefaultBenchmarkResamples_738) {
    Config config(makeDefaultData());
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_738, DefaultBenchmarkWarmupTime_738) {
    Config config(makeDefaultData());
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_738, DefaultVerbosity_738) {
    Config config(makeDefaultData());
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_738, DefaultShowDurations_738) {
    Config config(makeDefaultData());
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_738, DefaultMinDuration_738) {
    Config config(makeDefaultData());
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_738, DefaultRunOrder_738) {
    Config config(makeDefaultData());
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_738, DefaultColourMode_738) {
    Config config(makeDefaultData());
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_738, DefaultZeroTestsCountAsSuccess_738) {
    Config config(makeDefaultData());
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_738, DefaultHasTestFilters_738) {
    Config config(makeDefaultData());
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_738, DefaultGetTestsOrTagsEmpty_738) {
    Config config(makeDefaultData());
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_738, DefaultGetSectionsToRunEmpty_738) {
    Config config(makeDefaultData());
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// ==================== Setting Values Tests ====================

TEST_F(ConfigTest_738, SetListTestsTrue_738) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_738, SetListTagsTrue_738) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_738, SetListReportersTrue_738) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_738, SetListListenersTrue_738) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_738, SetShowHelpTrue_738) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_738, SetShowInvisiblesTrue_738) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_738, SetShowSuccessfulTestsTrue_738) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_738, SetNoThrowTrue_738) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_738, SetAbortAfterPositive_738) {
    ConfigData data;
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_738, SetAbortAfterZero_738) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_738, SetShardCount_738) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_738, SetShardIndex_738) {
    ConfigData data;
    data.shardIndex = 3;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 3u);
}

TEST_F(ConfigTest_738, SetSkipBenchmarksTrue_738) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_738, SetBenchmarkNoAnalysisTrue_738) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_738, SetBenchmarkSamples_738) {
    ConfigData data;
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_738, SetBenchmarkConfidenceInterval_738) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_738, SetBenchmarkResamples_738) {
    ConfigData data;
    data.benchmarkResamples = 200000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 200000u);
}

TEST_F(ConfigTest_738, SetBenchmarkWarmupTime_738) {
    ConfigData data;
    data.benchmarkWarmupTime = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

TEST_F(ConfigTest_738, SetVerbosityHigh_738) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_738, SetVerbosityQuiet_738) {
    ConfigData data;
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_738, SetShowDurationsAlways_738) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_738, SetShowDurationsNever_738) {
    ConfigData data;
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_738, SetMinDuration_738) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_738, SetRunOrderRandomize_738) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_738, SetRngSeed_738) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

TEST_F(ConfigTest_738, SetAllowZeroTestsTrue_738) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_738, SetProcessName_738) {
    ConfigData data;
    data.processName = "myTestProcess";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

TEST_F(ConfigTest_738, SetEmptyProcessName_738) {
    ConfigData data;
    data.processName = "";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef(""));
}

// ==================== Tests with test filters ====================

TEST_F(ConfigTest_738, HasTestFiltersWhenTestsOrTagsProvided_738) {
    ConfigData data;
    data.testsOrTags.push_back("testA");
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_738, GetTestsOrTagsReturnsProvidedValues_738) {
    ConfigData data;
    data.testsOrTags.push_back("testA");
    data.testsOrTags.push_back("testB");
    Config config(data);
    const auto& tests = config.getTestsOrTags();
    ASSERT_EQ(tests.size(), 2u);
    EXPECT_EQ(tests[0], "testA");
    EXPECT_EQ(tests[1], "testB");
}

TEST_F(ConfigTest_738, GetSectionsToRunReturnsProvidedValues_738) {
    ConfigData data;
    data.sectionsToRun.push_back("sectionA");
    data.sectionsToRun.push_back("sectionB");
    Config config(data);
    const auto& sections = config.getSectionsToRun();
    ASSERT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "sectionA");
    EXPECT_EQ(sections[1], "sectionB");
}

// ==================== Warnings Tests ====================

TEST_F(ConfigTest_738, DefaultWarnAboutMissingAssertionsFalse_738) {
    Config config(makeDefaultData());
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_738, DefaultWarnAboutUnmatchedTestSpecsFalse_738) {
    Config config(makeDefaultData());
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_738, WarnAboutMissingAssertionsWhenSet_738) {
    ConfigData data;
    data.warnings = WarnAbout::NoAssertions;
    Config config(data);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_738, WarnAboutUnmatchedTestSpecsWhenSet_738) {
    ConfigData data;
    data.warnings = WarnAbout::UnmatchedTestSpec;
    Config config(data);
    EXPECT_TRUE(config.warnAboutUnmatchedTestSpecs());
}

// ==================== Boundary condition tests ====================

TEST_F(ConfigTest_738, BenchmarkSamplesZero_738) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

TEST_F(ConfigTest_738, BenchmarkResamplesZero_738) {
    ConfigData data;
    data.benchmarkResamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

TEST_F(ConfigTest_738, BenchmarkWarmupTimeZero_738) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_738, MinDurationZero_738) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_738, BenchmarkConfidenceIntervalZero_738) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_738, BenchmarkConfidenceIntervalOne_738) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 1.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

TEST_F(ConfigTest_738, LargeRngSeed_738) {
    ConfigData data;
    data.rngSeed = 0xFFFFFFFF;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0xFFFFFFFF);
}

TEST_F(ConfigTest_738, RngSeedZero_738) {
    ConfigData data;
    data.rngSeed = 0;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0u);
}

// ==================== Default constructed Config test ====================

TEST_F(ConfigTest_738, DefaultConstructedConfig_738) {
    Config config;
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.listTags());
    EXPECT_FALSE(config.showHelp());
    EXPECT_FALSE(config.showInvisibles());
    EXPECT_FALSE(config.skipBenchmarks());
    EXPECT_TRUE(config.allowThrows());
}

// ==================== FilenamesAsTags (observable through testSpec) ====================

TEST_F(ConfigTest_738, SetFilenamesAsTagsTrue_738) {
    ConfigData data;
    data.filenamesAsTags = true;
    // We can only verify it constructs without error
    Config config(data);
    // filenamesAsTags is not directly queryable, but config should still be valid
    EXPECT_FALSE(config.hasTestFilters());
}

// ==================== Multiple boolean flags combined ====================

TEST_F(ConfigTest_738, MultipleFlagsSet_738) {
    ConfigData data;
    data.listTests = true;
    data.listTags = true;
    data.showHelp = true;
    data.showInvisibles = true;
    data.noThrow = true;
    data.skipBenchmarks = true;
    data.benchmarkNoAnalysis = true;
    data.allowZeroTests = true;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
    EXPECT_TRUE(config.listTags());
    EXPECT_TRUE(config.showHelp());
    EXPECT_TRUE(config.showInvisibles());
    EXPECT_FALSE(config.allowThrows());
    EXPECT_TRUE(config.skipBenchmarks());
    EXPECT_TRUE(config.benchmarkNoAnalysis());
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// ==================== ColourMode tests ====================

TEST_F(ConfigTest_738, SetColourModeAnsiEscape_738) {
    ConfigData data;
    data.defaultColourMode = ColourMode::ANSI;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_738, SetColourModeNone_738) {
    ConfigData data;
    data.defaultColourMode = ColourMode::None;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::None);
}
