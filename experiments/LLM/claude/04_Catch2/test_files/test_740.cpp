#include "catch2/catch_config.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <chrono>

using namespace Catch;

class ConfigTest_740 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// ==================== Default Values Tests ====================

TEST_F(ConfigTest_740, DefaultSkipBenchmarks_740) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_740, DefaultListTests_740) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_740, DefaultListTags_740) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_740, DefaultListReporters_740) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_740, DefaultListListeners_740) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_740, DefaultShowHelp_740) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_740, DefaultAllowThrows_740) {
    Config config(defaultData);
    // noThrow defaults to false, so allowThrows should return true
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_740, DefaultIncludeSuccessfulResults_740) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_740, DefaultShowInvisibles_740) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_740, DefaultVerbosity_740) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_740, DefaultAbortAfter_740) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_740, DefaultShardCount_740) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_740, DefaultShardIndex_740) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_740, DefaultBenchmarkNoAnalysis_740) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_740, DefaultBenchmarkSamples_740) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_740, DefaultBenchmarkConfidenceInterval_740) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_740, DefaultBenchmarkResamples_740) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_740, DefaultBenchmarkWarmupTime_740) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_740, DefaultShowDurations_740) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_740, DefaultMinDuration_740) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_740, DefaultRunOrder_740) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_740, DefaultColourMode_740) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_740, DefaultZeroTestsCountAsSuccess_740) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_740, DefaultHasTestFilters_740) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_740, DefaultGetTestsOrTagsIsEmpty_740) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_740, DefaultGetSectionsToRunIsEmpty_740) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// ==================== Modified ConfigData Tests ====================

TEST_F(ConfigTest_740, SkipBenchmarksTrue_740) {
    defaultData.skipBenchmarks = true;
    Config config(defaultData);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_740, ListTestsTrue_740) {
    defaultData.listTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_740, ListTagsTrue_740) {
    defaultData.listTags = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_740, ListReportersTrue_740) {
    defaultData.listReporters = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_740, ListListenersTrue_740) {
    defaultData.listListeners = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_740, ShowHelpTrue_740) {
    defaultData.showHelp = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_740, NoThrowDisablesAllowThrows_740) {
    defaultData.noThrow = true;
    Config config(defaultData);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_740, ShowSuccessfulTestsTrue_740) {
    defaultData.showSuccessfulTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_740, ShowInvisiblesTrue_740) {
    defaultData.showInvisibles = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_740, VerbosityHigh_740) {
    defaultData.verbosity = Verbosity::High;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_740, VerbosityQuiet_740) {
    defaultData.verbosity = Verbosity::Quiet;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_740, AbortAfterPositive_740) {
    defaultData.abortAfter = 5;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_740, AbortAfterZero_740) {
    defaultData.abortAfter = 0;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_740, ShardCountMultiple_740) {
    defaultData.shardCount = 4;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_740, ShardIndexNonZero_740) {
    defaultData.shardCount = 4;
    defaultData.shardIndex = 3;
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 3u);
}

TEST_F(ConfigTest_740, BenchmarkNoAnalysisTrue_740) {
    defaultData.benchmarkNoAnalysis = true;
    Config config(defaultData);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_740, BenchmarkSamplesCustom_740) {
    defaultData.benchmarkSamples = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_740, BenchmarkConfidenceIntervalCustom_740) {
    defaultData.benchmarkConfidenceInterval = 0.99;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_740, BenchmarkResamplesCustom_740) {
    defaultData.benchmarkResamples = 50000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

TEST_F(ConfigTest_740, BenchmarkWarmupTimeCustom_740) {
    defaultData.benchmarkWarmupTime = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

TEST_F(ConfigTest_740, ShowDurationsAlways_740) {
    defaultData.showDurations = ShowDurations::Always;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_740, ShowDurationsNever_740) {
    defaultData.showDurations = ShowDurations::Never;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_740, MinDurationPositive_740) {
    defaultData.minDuration = 0.5;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_740, MinDurationZero_740) {
    defaultData.minDuration = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_740, RunOrderRandomize_740) {
    defaultData.runOrder = TestRunOrder::Randomized;
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_740, ColourModeAnsiEscape_740) {
    defaultData.defaultColourMode = ColourMode::ANSI;
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_740, ColourModeNone_740) {
    defaultData.defaultColourMode = ColourMode::None;
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::None);
}

TEST_F(ConfigTest_740, AllowZeroTestsTrue_740) {
    defaultData.allowZeroTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_740, RngSeedCustom_740) {
    defaultData.rngSeed = 42;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 42u);
}

TEST_F(ConfigTest_740, ProcessNameSetsName_740) {
    defaultData.processName = "myTestProcess";
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

TEST_F(ConfigTest_740, ProcessNameEmpty_740) {
    defaultData.processName = "";
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_740, TestsOrTagsPopulated_740) {
    defaultData.testsOrTags = {"test1", "test2", "[tag1]"};
    Config config(defaultData);
    auto const& result = config.getTestsOrTags();
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "test1");
    EXPECT_EQ(result[1], "test2");
    EXPECT_EQ(result[2], "[tag1]");
}

TEST_F(ConfigTest_740, HasTestFiltersWhenTestsOrTagsProvided_740) {
    defaultData.testsOrTags = {"someTest"};
    Config config(defaultData);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_740, SectionsToRunPopulated_740) {
    defaultData.sectionsToRun = {"section1", "section2"};
    Config config(defaultData);
    auto const& result = config.getSectionsToRun();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "section1");
    EXPECT_EQ(result[1], "section2");
}

TEST_F(ConfigTest_740, WarnAboutMissingAssertionsDefault_740) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_740, WarnAboutUnmatchedTestSpecsDefault_740) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_740, WarnAboutMissingAssertionsEnabled_740) {
    defaultData.warnings = WarnAbout::NoAssertions;
    Config config(defaultData);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_740, ShouldDebugBreakDefault_740) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}

// ==================== Boundary Tests ====================

TEST_F(ConfigTest_740, BenchmarkSamplesZero_740) {
    defaultData.benchmarkSamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

TEST_F(ConfigTest_740, BenchmarkResamplesZero_740) {
    defaultData.benchmarkResamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

TEST_F(ConfigTest_740, BenchmarkWarmupTimeZero_740) {
    defaultData.benchmarkWarmupTime = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_740, BenchmarkConfidenceIntervalZero_740) {
    defaultData.benchmarkConfidenceInterval = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_740, BenchmarkConfidenceIntervalOne_740) {
    defaultData.benchmarkConfidenceInterval = 1.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

TEST_F(ConfigTest_740, RngSeedZero_740) {
    defaultData.rngSeed = 0;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 0u);
}

TEST_F(ConfigTest_740, RngSeedMaxUint32_740) {
    defaultData.rngSeed = 0xFFFFFFFF;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 0xFFFFFFFFu);
}

TEST_F(ConfigTest_740, ShardCountOne_740) {
    defaultData.shardCount = 1;
    defaultData.shardIndex = 0;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_740, LargeAbortAfterValue_740) {
    defaultData.abortAfter = 1000000;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 1000000);
}

// ==================== Default Constructor Test ====================

TEST_F(ConfigTest_740, DefaultConstructor_740) {
    Config config;
    // Should have all default values
    EXPECT_FALSE(config.skipBenchmarks());
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.showHelp());
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

// ==================== Copy from ConfigData Test ====================

TEST_F(ConfigTest_740, MultipleFieldsSetSimultaneously_740) {
    defaultData.skipBenchmarks = true;
    defaultData.benchmarkNoAnalysis = true;
    defaultData.showSuccessfulTests = true;
    defaultData.noThrow = true;
    defaultData.showInvisibles = true;
    defaultData.verbosity = Verbosity::High;
    defaultData.abortAfter = 3;
    
    Config config(defaultData);
    
    EXPECT_TRUE(config.skipBenchmarks());
    EXPECT_TRUE(config.benchmarkNoAnalysis());
    EXPECT_TRUE(config.includeSuccessfulResults());
    EXPECT_FALSE(config.allowThrows());
    EXPECT_TRUE(config.showInvisibles());
    EXPECT_EQ(config.verbosity(), Verbosity::High);
    EXPECT_EQ(config.abortAfter(), 3);
}
