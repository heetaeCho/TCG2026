#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_729 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// Test default construction values
TEST_F(ConfigTest_729, DefaultConstruction_ListTestsIsFalse_729) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_729, DefaultConstruction_ListTagsIsFalse_729) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_729, DefaultConstruction_ListReportersIsFalse_729) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_729, DefaultConstruction_ListListenersIsFalse_729) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_729, DefaultConstruction_ShowHelpIsFalse_729) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_729, DefaultConstruction_AllowThrowsIsTrue_729) {
    // noThrow defaults to false, so allowThrows should return true
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_729, DefaultConstruction_IncludeSuccessfulResultsIsFalse_729) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_729, DefaultConstruction_ShowDurationsIsDefault_729) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_729, DefaultConstruction_MinDurationIsNegativeOne_729) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_729, DefaultConstruction_RunOrderIsDeclared_729) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_729, DefaultConstruction_ShardCountIsOne_729) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_729, DefaultConstruction_ShardIndexIsZero_729) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_729, DefaultConstruction_DefaultColourModeIsPlatformDefault_729) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_729, DefaultConstruction_AbortAfterIsNegativeOne_729) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_729, DefaultConstruction_ShowInvisiblesIsFalse_729) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_729, DefaultConstruction_VerbosityIsNormal_729) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_729, DefaultConstruction_SkipBenchmarksIsFalse_729) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_729, DefaultConstruction_BenchmarkNoAnalysisIsFalse_729) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_729, DefaultConstruction_BenchmarkSamplesIs100_729) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_729, DefaultConstruction_BenchmarkConfidenceInterval_729) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_729, DefaultConstruction_BenchmarkResamplesIs100000_729) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_729, DefaultConstruction_BenchmarkWarmupTimeIs100_729) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_729, DefaultConstruction_WarnAboutMissingAssertionsIsFalse_729) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_729, DefaultConstruction_WarnAboutUnmatchedTestSpecsIsFalse_729) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_729, DefaultConstruction_ZeroTestsCountAsSuccessIsFalse_729) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_729, DefaultConstruction_HasTestFiltersIsFalse_729) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_729, DefaultConstruction_GetTestsOrTagsIsEmpty_729) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_729, DefaultConstruction_GetSectionsToRunIsEmpty_729) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// Test setting listTests to true
TEST_F(ConfigTest_729, ListTestsSetToTrue_729) {
    defaultData.listTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTests());
}

// Test setting listTags to true
TEST_F(ConfigTest_729, ListTagsSetToTrue_729) {
    defaultData.listTags = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTags());
}

// Test setting listReporters to true
TEST_F(ConfigTest_729, ListReportersSetToTrue_729) {
    defaultData.listReporters = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listReporters());
}

// Test setting listListeners to true
TEST_F(ConfigTest_729, ListListenersSetToTrue_729) {
    defaultData.listListeners = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listListeners());
}

// Test noThrow = true means allowThrows = false
TEST_F(ConfigTest_729, NoThrowTrue_AllowThrowsFalse_729) {
    defaultData.noThrow = true;
    Config config(defaultData);
    EXPECT_FALSE(config.allowThrows());
}

// Test showSuccessfulTests
TEST_F(ConfigTest_729, ShowSuccessfulTestsTrue_IncludeSuccessfulResultsTrue_729) {
    defaultData.showSuccessfulTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// Test showHelp
TEST_F(ConfigTest_729, ShowHelpSetToTrue_729) {
    defaultData.showHelp = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showHelp());
}

// Test showInvisibles
TEST_F(ConfigTest_729, ShowInvisiblesSetToTrue_729) {
    defaultData.showInvisibles = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showInvisibles());
}

// Test showDurations set to Always
TEST_F(ConfigTest_729, ShowDurationsSetToAlways_729) {
    defaultData.showDurations = ShowDurations::Always;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

// Test showDurations set to Never
TEST_F(ConfigTest_729, ShowDurationsSetToNever_729) {
    defaultData.showDurations = ShowDurations::Never;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

// Test minDuration
TEST_F(ConfigTest_729, MinDurationSetToPositive_729) {
    defaultData.minDuration = 0.5;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_729, MinDurationSetToZero_729) {
    defaultData.minDuration = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

// Test runOrder
TEST_F(ConfigTest_729, RunOrderSetToRandomize_729) {
    defaultData.runOrder = TestRunOrder::Randomized;
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

// Test rngSeed
TEST_F(ConfigTest_729, RngSeedSetToSpecificValue_729) {
    defaultData.rngSeed = 42;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// Test shardCount
TEST_F(ConfigTest_729, ShardCountSetToFive_729) {
    defaultData.shardCount = 5;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 5u);
}

// Test shardIndex
TEST_F(ConfigTest_729, ShardIndexSetToThree_729) {
    defaultData.shardIndex = 3;
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 3u);
}

// Test abortAfter
TEST_F(ConfigTest_729, AbortAfterSetToFive_729) {
    defaultData.abortAfter = 5;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_729, AbortAfterSetToZero_729) {
    defaultData.abortAfter = 0;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 0);
}

// Test verbosity
TEST_F(ConfigTest_729, VerbositySetToQuiet_729) {
    defaultData.verbosity = Verbosity::Quiet;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_729, VerbositySetToHigh_729) {
    defaultData.verbosity = Verbosity::High;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

// Test skipBenchmarks
TEST_F(ConfigTest_729, SkipBenchmarksSetToTrue_729) {
    defaultData.skipBenchmarks = true;
    Config config(defaultData);
    EXPECT_TRUE(config.skipBenchmarks());
}

// Test benchmarkNoAnalysis
TEST_F(ConfigTest_729, BenchmarkNoAnalysisSetToTrue_729) {
    defaultData.benchmarkNoAnalysis = true;
    Config config(defaultData);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

// Test benchmarkSamples
TEST_F(ConfigTest_729, BenchmarkSamplesSetToCustom_729) {
    defaultData.benchmarkSamples = 200;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 200u);
}

// Test benchmarkConfidenceInterval
TEST_F(ConfigTest_729, BenchmarkConfidenceIntervalSetToCustom_729) {
    defaultData.benchmarkConfidenceInterval = 0.99;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

// Test benchmarkResamples
TEST_F(ConfigTest_729, BenchmarkResamplesSetToCustom_729) {
    defaultData.benchmarkResamples = 50000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

// Test benchmarkWarmupTime
TEST_F(ConfigTest_729, BenchmarkWarmupTimeSetToCustom_729) {
    defaultData.benchmarkWarmupTime = 200;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

// Test allowZeroTests
TEST_F(ConfigTest_729, AllowZeroTestsSetToTrue_729) {
    defaultData.allowZeroTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

// Test defaultColourMode
TEST_F(ConfigTest_729, DefaultColourModeSetToAnsi_729) {
    defaultData.defaultColourMode = ColourMode::ANSI;
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

// Test processName via name()
TEST_F(ConfigTest_729, ProcessNameSetToCustom_729) {
    defaultData.processName = "myTestProcess";
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

TEST_F(ConfigTest_729, ProcessNameEmpty_729) {
    defaultData.processName = "";
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef(""));
}

// Test testsOrTags with filters
TEST_F(ConfigTest_729, TestsOrTagsWithEntries_729) {
    defaultData.testsOrTags = {"[tag1]", "testName"};
    Config config(defaultData);
    auto const& testsOrTags = config.getTestsOrTags();
    EXPECT_EQ(testsOrTags.size(), 2u);
    EXPECT_EQ(testsOrTags[0], "[tag1]");
    EXPECT_EQ(testsOrTags[1], "testName");
}

// Test hasTestFilters when testsOrTags is not empty
TEST_F(ConfigTest_729, HasTestFiltersWhenTestsOrTagsProvided_729) {
    defaultData.testsOrTags = {"someTest"};
    Config config(defaultData);
    EXPECT_TRUE(config.hasTestFilters());
}

// Test sectionsToRun
TEST_F(ConfigTest_729, SectionsToRunWithEntries_729) {
    defaultData.sectionsToRun = {"section1", "section2"};
    Config config(defaultData);
    auto const& sections = config.getSectionsToRun();
    EXPECT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

// Boundary: shardCount = 1 and shardIndex = 0 (minimum valid shard configuration)
TEST_F(ConfigTest_729, MinimumShardConfiguration_729) {
    defaultData.shardCount = 1;
    defaultData.shardIndex = 0;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
    EXPECT_EQ(config.shardIndex(), 0u);
}

// Boundary: benchmarkSamples = 0
TEST_F(ConfigTest_729, BenchmarkSamplesZero_729) {
    defaultData.benchmarkSamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

// Boundary: benchmarkWarmupTime = 0
TEST_F(ConfigTest_729, BenchmarkWarmupTimeZero_729) {
    defaultData.benchmarkWarmupTime = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

// Boundary: rngSeed = 0
TEST_F(ConfigTest_729, RngSeedZero_729) {
    defaultData.rngSeed = 0;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 0u);
}

// Boundary: rngSeed = max uint32
TEST_F(ConfigTest_729, RngSeedMaxValue_729) {
    defaultData.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

// Boundary: benchmarkConfidenceInterval = 0
TEST_F(ConfigTest_729, BenchmarkConfidenceIntervalZero_729) {
    defaultData.benchmarkConfidenceInterval = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

// Boundary: benchmarkConfidenceInterval = 1.0
TEST_F(ConfigTest_729, BenchmarkConfidenceIntervalOne_729) {
    defaultData.benchmarkConfidenceInterval = 1.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

// Test multiple settings combined
TEST_F(ConfigTest_729, MultipleCombinedSettings_729) {
    defaultData.listTests = true;
    defaultData.showHelp = true;
    defaultData.noThrow = true;
    defaultData.showInvisibles = true;
    defaultData.verbosity = Verbosity::High;
    defaultData.abortAfter = 3;
    defaultData.processName = "combined";
    Config config(defaultData);
    
    EXPECT_TRUE(config.listTests());
    EXPECT_TRUE(config.showHelp());
    EXPECT_FALSE(config.allowThrows());
    EXPECT_TRUE(config.showInvisibles());
    EXPECT_EQ(config.verbosity(), Verbosity::High);
    EXPECT_EQ(config.abortAfter(), 3);
    EXPECT_EQ(config.name(), StringRef("combined"));
}
