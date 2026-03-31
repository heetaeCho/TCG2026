#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_735 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// Test default construction and default values
TEST_F(ConfigTest_735, DefaultConstruction_HasDefaultValues_735) {
    Config config;
    // Default ConfigData values should be reflected
}

TEST_F(ConfigTest_735, ListTestsDefaultFalse_735) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_735, ListTestsSetTrue_735) {
    defaultData.listTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_735, ListTagsDefaultFalse_735) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_735, ListTagsSetTrue_735) {
    defaultData.listTags = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_735, ListReportersDefaultFalse_735) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_735, ListReportersSetTrue_735) {
    defaultData.listReporters = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_735, ListListenersDefaultFalse_735) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_735, ListListenersSetTrue_735) {
    defaultData.listListeners = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_735, ShowHelpDefaultFalse_735) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_735, ShowHelpSetTrue_735) {
    defaultData.showHelp = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_735, AllowThrowsDefaultTrue_735) {
    // noThrow defaults to false, so allowThrows should be true
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_735, AllowThrowsFalseWhenNoThrowTrue_735) {
    defaultData.noThrow = true;
    Config config(defaultData);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_735, IncludeSuccessfulResultsDefaultFalse_735) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_735, IncludeSuccessfulResultsSetTrue_735) {
    defaultData.showSuccessfulTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_735, WarnAboutMissingAssertionsDefaultFalse_735) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_735, WarnAboutMissingAssertionsWhenSet_735) {
    defaultData.warnings = WarnAbout::NoAssertions;
    Config config(defaultData);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_735, ZeroTestsCountAsSuccessDefaultFalse_735) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_735, ZeroTestsCountAsSuccessSetTrue_735) {
    defaultData.allowZeroTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_735, ShowDurationsDefault_735) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_735, ShowDurationsSetAlways_735) {
    defaultData.showDurations = ShowDurations::Always;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_735, ShowDurationsSetNever_735) {
    defaultData.showDurations = ShowDurations::Never;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_735, MinDurationDefault_735) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_735, MinDurationCustomValue_735) {
    defaultData.minDuration = 0.5;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_735, RunOrderDefaultDeclared_735) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_735, RunOrderSetRandomized_735) {
    defaultData.runOrder = TestRunOrder::Randomized;
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_735, DefaultColourModeDefault_735) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_735, DefaultColourModeSetAnsiColours_735) {
    defaultData.defaultColourMode = ColourMode::ANSI;
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_735, DefaultColourModeSetNone_735) {
    defaultData.defaultColourMode = ColourMode::None;
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::None);
}

TEST_F(ConfigTest_735, AbortAfterDefault_735) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_735, AbortAfterCustomValue_735) {
    defaultData.abortAfter = 5;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_735, AbortAfterZero_735) {
    defaultData.abortAfter = 0;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_735, ShowInvisiblesDefaultFalse_735) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_735, ShowInvisiblesSetTrue_735) {
    defaultData.showInvisibles = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_735, VerbosityDefaultNormal_735) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_735, VerbositySetQuiet_735) {
    defaultData.verbosity = Verbosity::Quiet;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_735, VerbositySetHigh_735) {
    defaultData.verbosity = Verbosity::High;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_735, SkipBenchmarksDefaultFalse_735) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_735, SkipBenchmarksSetTrue_735) {
    defaultData.skipBenchmarks = true;
    Config config(defaultData);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_735, BenchmarkNoAnalysisDefaultFalse_735) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_735, BenchmarkNoAnalysisSetTrue_735) {
    defaultData.benchmarkNoAnalysis = true;
    Config config(defaultData);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_735, BenchmarkSamplesDefault100_735) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_735, BenchmarkSamplesCustomValue_735) {
    defaultData.benchmarkSamples = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_735, BenchmarkConfidenceIntervalDefault_735) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_735, BenchmarkConfidenceIntervalCustom_735) {
    defaultData.benchmarkConfidenceInterval = 0.99;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_735, BenchmarkResamplesDefault100000_735) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_735, BenchmarkResamplesCustomValue_735) {
    defaultData.benchmarkResamples = 50000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

TEST_F(ConfigTest_735, BenchmarkWarmupTimeDefault100ms_735) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_735, BenchmarkWarmupTimeCustomValue_735) {
    defaultData.benchmarkWarmupTime = 200;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

TEST_F(ConfigTest_735, ShardCountDefault1_735) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_735, ShardCountCustomValue_735) {
    defaultData.shardCount = 4;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_735, ShardIndexDefault0_735) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_735, ShardIndexCustomValue_735) {
    defaultData.shardIndex = 2;
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 2u);
}

TEST_F(ConfigTest_735, NameReturnsProcessName_735) {
    defaultData.processName = "myTestProcess";
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

TEST_F(ConfigTest_735, NameEmptyByDefault_735) {
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_735, HasTestFiltersDefaultFalse_735) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_735, HasTestFiltersWhenTestsOrTagsProvided_735) {
    defaultData.testsOrTags.push_back("someTest");
    Config config(defaultData);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_735, GetTestsOrTagsEmpty_735) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_735, GetTestsOrTagsWithValues_735) {
    defaultData.testsOrTags.push_back("test1");
    defaultData.testsOrTags.push_back("test2");
    Config config(defaultData);
    auto const& testsOrTags = config.getTestsOrTags();
    ASSERT_EQ(testsOrTags.size(), 2u);
    EXPECT_EQ(testsOrTags[0], "test1");
    EXPECT_EQ(testsOrTags[1], "test2");
}

TEST_F(ConfigTest_735, GetSectionsToRunEmpty_735) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

TEST_F(ConfigTest_735, GetSectionsToRunWithValues_735) {
    defaultData.sectionsToRun.push_back("section1");
    defaultData.sectionsToRun.push_back("section2");
    Config config(defaultData);
    auto const& sections = config.getSectionsToRun();
    ASSERT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

TEST_F(ConfigTest_735, ShouldDebugBreakDefaultFalse_735) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}

TEST_F(ConfigTest_735, RngSeedReturnsConfiguredValue_735) {
    defaultData.rngSeed = 42;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 42u);
}

TEST_F(ConfigTest_735, FilenamesAsTagsDefault_735) {
    // filenamesAsTags defaults to false - not directly queryable through public API,
    // but it affects test spec processing
    Config config(defaultData);
    // Just verify construction succeeds
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_735, TestSpecDefaultEmpty_735) {
    Config config(defaultData);
    // With no tests or tags, testSpec should match nothing specific
    auto const& spec = config.testSpec();
    EXPECT_TRUE(spec.hasFilters() == false);
}

TEST_F(ConfigTest_735, GetReporterSpecsEmpty_735) {
    Config config(defaultData);
    // By default, no reporter specs are added in ConfigData
    // But the config may add a default one. Just verify it doesn't crash.
    auto const& specs = config.getReporterSpecs();
    // Specs may or may not be empty depending on defaults
    (void)specs;
}

TEST_F(ConfigTest_735, GetProcessedReporterSpecsNoThrow_735) {
    Config config(defaultData);
    auto const& processed = config.getProcessedReporterSpecs();
    // Just verify it returns without throwing
    (void)processed;
}

// Boundary: shardCount = 0 (potentially invalid but testing interface behavior)
TEST_F(ConfigTest_735, ShardCountZero_735) {
    defaultData.shardCount = 0;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 0u);
}

// Boundary: benchmarkSamples = 0
TEST_F(ConfigTest_735, BenchmarkSamplesZero_735) {
    defaultData.benchmarkSamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

// Boundary: benchmarkResamples = 0
TEST_F(ConfigTest_735, BenchmarkResamplesZero_735) {
    defaultData.benchmarkResamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

// Boundary: benchmarkWarmupTime = 0
TEST_F(ConfigTest_735, BenchmarkWarmupTimeZero_735) {
    defaultData.benchmarkWarmupTime = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

// Boundary: minDuration = 0
TEST_F(ConfigTest_735, MinDurationZero_735) {
    defaultData.minDuration = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

// Boundary: abortAfter = 1 (minimum meaningful value)
TEST_F(ConfigTest_735, AbortAfterOne_735) {
    defaultData.abortAfter = 1;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 1);
}

// Boundary: large abortAfter
TEST_F(ConfigTest_735, AbortAfterLargeValue_735) {
    defaultData.abortAfter = 1000000;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 1000000);
}

// Test that benchmarkConfidenceInterval boundary values work
TEST_F(ConfigTest_735, BenchmarkConfidenceIntervalZero_735) {
    defaultData.benchmarkConfidenceInterval = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_735, BenchmarkConfidenceIntervalOne_735) {
    defaultData.benchmarkConfidenceInterval = 1.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

// Test WarnAboutUnmatchedTestSpecs default
TEST_F(ConfigTest_735, WarnAboutUnmatchedTestSpecsDefaultFalse_735) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}
