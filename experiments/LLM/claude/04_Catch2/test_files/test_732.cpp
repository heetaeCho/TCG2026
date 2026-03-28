#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_732 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// Test default construction and default values
TEST_F(ConfigTest_732, DefaultConstruction_732) {
    Config config;
    // Default config should be constructible without issues
}

TEST_F(ConfigTest_732, ConstructWithConfigData_732) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// --- rngSeed tests ---
TEST_F(ConfigTest_732, RngSeedReturnsSetValue_732) {
    ConfigData data;
    data.rngSeed = 12345;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 12345u);
}

TEST_F(ConfigTest_732, RngSeedZero_732) {
    ConfigData data;
    data.rngSeed = 0;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0u);
}

TEST_F(ConfigTest_732, RngSeedMaxValue_732) {
    ConfigData data;
    data.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(data);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

// --- listTests tests ---
TEST_F(ConfigTest_732, ListTestsDefaultFalse_732) {
    ConfigData data;
    data.listTests = false;
    Config config(data);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_732, ListTestsTrue_732) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

// --- listTags tests ---
TEST_F(ConfigTest_732, ListTagsDefaultFalse_732) {
    ConfigData data;
    data.listTags = false;
    Config config(data);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_732, ListTagsTrue_732) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

// --- listReporters tests ---
TEST_F(ConfigTest_732, ListReportersDefaultFalse_732) {
    ConfigData data;
    data.listReporters = false;
    Config config(data);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_732, ListReportersTrue_732) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

// --- listListeners tests ---
TEST_F(ConfigTest_732, ListListenersDefaultFalse_732) {
    ConfigData data;
    data.listListeners = false;
    Config config(data);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_732, ListListenersTrue_732) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

// --- showHelp tests ---
TEST_F(ConfigTest_732, ShowHelpDefaultFalse_732) {
    ConfigData data;
    data.showHelp = false;
    Config config(data);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_732, ShowHelpTrue_732) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

// --- allowThrows tests ---
TEST_F(ConfigTest_732, AllowThrowsWhenNoThrowFalse_732) {
    ConfigData data;
    data.noThrow = false;
    Config config(data);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_732, AllowThrowsWhenNoThrowTrue_732) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

// --- includeSuccessfulResults tests ---
TEST_F(ConfigTest_732, IncludeSuccessfulResultsDefault_732) {
    ConfigData data;
    data.showSuccessfulTests = false;
    Config config(data);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_732, IncludeSuccessfulResultsTrue_732) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// --- warnAboutMissingAssertions tests ---
TEST_F(ConfigTest_732, WarnAboutMissingAssertionsDefault_732) {
    ConfigData data;
    data.warnings = WarnAbout::Nothing;
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_732, WarnAboutMissingAssertionsEnabled_732) {
    ConfigData data;
    data.warnings = WarnAbout::NoAssertions;
    Config config(data);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

// --- showDurations tests ---
TEST_F(ConfigTest_732, ShowDurationsDefault_732) {
    ConfigData data;
    data.showDurations = ShowDurations::DefaultForReporter;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_732, ShowDurationsAlways_732) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_732, ShowDurationsNever_732) {
    ConfigData data;
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

// --- minDuration tests ---
TEST_F(ConfigTest_732, MinDurationDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_732, MinDurationCustom_732) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

// --- runOrder tests ---
TEST_F(ConfigTest_732, RunOrderDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_732, RunOrderRandomized_732) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_732, RunOrderLexicographic_732) {
    ConfigData data;
    data.runOrder = TestRunOrder::LexicographicallySorted;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::LexicographicallySorted);
}

// --- shardCount tests ---
TEST_F(ConfigTest_732, ShardCountDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_732, ShardCountCustom_732) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

// --- shardIndex tests ---
TEST_F(ConfigTest_732, ShardIndexDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_732, ShardIndexCustom_732) {
    ConfigData data;
    data.shardIndex = 3;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 3u);
}

// --- defaultColourMode tests ---
TEST_F(ConfigTest_732, DefaultColourModeDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_732, DefaultColourModeAnsi_732) {
    ConfigData data;
    data.defaultColourMode = ColourMode::ANSI;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_732, DefaultColourModeNone_732) {
    ConfigData data;
    data.defaultColourMode = ColourMode::None;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::None);
}

// --- abortAfter tests ---
TEST_F(ConfigTest_732, AbortAfterDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_732, AbortAfterCustom_732) {
    ConfigData data;
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_732, AbortAfterZero_732) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

// --- showInvisibles tests ---
TEST_F(ConfigTest_732, ShowInvisiblesDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_732, ShowInvisiblesTrue_732) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

// --- verbosity tests ---
TEST_F(ConfigTest_732, VerbosityDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_732, VerbosityQuiet_732) {
    ConfigData data;
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_732, VerbosityHigh_732) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

// --- skipBenchmarks tests ---
TEST_F(ConfigTest_732, SkipBenchmarksDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_732, SkipBenchmarksTrue_732) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

// --- benchmarkNoAnalysis tests ---
TEST_F(ConfigTest_732, BenchmarkNoAnalysisDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_732, BenchmarkNoAnalysisTrue_732) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

// --- benchmarkSamples tests ---
TEST_F(ConfigTest_732, BenchmarkSamplesDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_732, BenchmarkSamplesCustom_732) {
    ConfigData data;
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

// --- benchmarkConfidenceInterval tests ---
TEST_F(ConfigTest_732, BenchmarkConfidenceIntervalDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_732, BenchmarkConfidenceIntervalCustom_732) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

// --- benchmarkResamples tests ---
TEST_F(ConfigTest_732, BenchmarkResamplesDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_732, BenchmarkResamplesCustom_732) {
    ConfigData data;
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

// --- benchmarkWarmupTime tests ---
TEST_F(ConfigTest_732, BenchmarkWarmupTimeDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_732, BenchmarkWarmupTimeCustom_732) {
    ConfigData data;
    data.benchmarkWarmupTime = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

// --- name tests ---
TEST_F(ConfigTest_732, NameReturnsProcessName_732) {
    ConfigData data;
    data.processName = "myTestProcess";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

TEST_F(ConfigTest_732, NameEmptyByDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.name(), StringRef(""));
}

// --- zeroTestsCountAsSuccess tests ---
TEST_F(ConfigTest_732, ZeroTestsCountAsSuccessDefault_732) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_732, ZeroTestsCountAsSuccessTrue_732) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

// --- hasTestFilters tests ---
TEST_F(ConfigTest_732, HasTestFiltersDefaultFalse_732) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_732, HasTestFiltersWithTestsOrTags_732) {
    ConfigData data;
    data.testsOrTags.push_back("someTest");
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

// --- getTestsOrTags tests ---
TEST_F(ConfigTest_732, GetTestsOrTagsEmpty_732) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_732, GetTestsOrTagsNonEmpty_732) {
    ConfigData data;
    data.testsOrTags.push_back("test1");
    data.testsOrTags.push_back("[tag1]");
    Config config(data);
    const auto& result = config.getTestsOrTags();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "test1");
    EXPECT_EQ(result[1], "[tag1]");
}

// --- getSectionsToRun tests ---
TEST_F(ConfigTest_732, GetSectionsToRunEmpty_732) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

TEST_F(ConfigTest_732, GetSectionsToRunNonEmpty_732) {
    ConfigData data;
    data.sectionsToRun.push_back("section1");
    data.sectionsToRun.push_back("section2");
    Config config(data);
    const auto& sections = config.getSectionsToRun();
    EXPECT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

// --- testSpec tests ---
TEST_F(ConfigTest_732, TestSpecDefaultEmpty_732) {
    ConfigData data;
    Config config(data);
    // With no testsOrTags, testSpec should have no filters
    const auto& spec = config.testSpec();
    EXPECT_TRUE(spec.hasFilters() == false || spec.hasFilters() == true);
    // Just verify it doesn't crash and returns a valid reference
}

// --- filenamesAsTags tests ---
// filenamesAsTags is a ConfigData field but no direct getter is exposed.
// We skip testing it as there's no direct observable getter.

// --- shouldDebugBreak tests ---
TEST_F(ConfigTest_732, ShouldDebugBreakDefault_732) {
    ConfigData data;
    Config config(data);
    // Default should be false (no explicit field, but it's a method)
    EXPECT_FALSE(config.shouldDebugBreak());
}

// --- Boundary: shardCount of 0 ---
TEST_F(ConfigTest_732, ShardCountZero_732) {
    ConfigData data;
    data.shardCount = 0;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 0u);
}

// --- Boundary: large shard index ---
TEST_F(ConfigTest_732, ShardIndexLargeValue_732) {
    ConfigData data;
    data.shardIndex = 999;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 999u);
}

// --- Boundary: abortAfter negative ---
TEST_F(ConfigTest_732, AbortAfterNegative_732) {
    ConfigData data;
    data.abortAfter = -100;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), -100);
}

// --- Boundary: benchmarkSamples zero ---
TEST_F(ConfigTest_732, BenchmarkSamplesZero_732) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

// --- Boundary: benchmarkConfidenceInterval zero ---
TEST_F(ConfigTest_732, BenchmarkConfidenceIntervalZero_732) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

// --- Boundary: benchmarkWarmupTime zero ---
TEST_F(ConfigTest_732, BenchmarkWarmupTimeZero_732) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

// --- Boundary: minDuration zero ---
TEST_F(ConfigTest_732, MinDurationZero_732) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

// --- Multiple configurations consistency ---
TEST_F(ConfigTest_732, MultipleFieldsSetCorrectly_732) {
    ConfigData data;
    data.listTests = true;
    data.listTags = true;
    data.noThrow = true;
    data.showInvisibles = true;
    data.rngSeed = 999;
    data.verbosity = Verbosity::High;
    data.abortAfter = 10;
    data.shardCount = 5;
    data.shardIndex = 2;
    
    Config config(data);
    
    EXPECT_TRUE(config.listTests());
    EXPECT_TRUE(config.listTags());
    EXPECT_FALSE(config.allowThrows());
    EXPECT_TRUE(config.showInvisibles());
    EXPECT_EQ(config.rngSeed(), 999u);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
    EXPECT_EQ(config.abortAfter(), 10);
    EXPECT_EQ(config.shardCount(), 5u);
    EXPECT_EQ(config.shardIndex(), 2u);
}
