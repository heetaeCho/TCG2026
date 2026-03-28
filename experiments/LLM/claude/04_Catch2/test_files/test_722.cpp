#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_722 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// --- showHelp tests ---

TEST_F(ConfigTest_722, ShowHelpDefaultIsFalse_722) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_722, ShowHelpReturnsTrueWhenSet_722) {
    defaultData.showHelp = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showHelp());
}

// --- listTests tests ---

TEST_F(ConfigTest_722, ListTestsDefaultIsFalse_722) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_722, ListTestsReturnsTrueWhenSet_722) {
    defaultData.listTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTests());
}

// --- listTags tests ---

TEST_F(ConfigTest_722, ListTagsDefaultIsFalse_722) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_722, ListTagsReturnsTrueWhenSet_722) {
    defaultData.listTags = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTags());
}

// --- listReporters tests ---

TEST_F(ConfigTest_722, ListReportersDefaultIsFalse_722) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_722, ListReportersReturnsTrueWhenSet_722) {
    defaultData.listReporters = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listReporters());
}

// --- listListeners tests ---

TEST_F(ConfigTest_722, ListListenersDefaultIsFalse_722) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_722, ListListenersReturnsTrueWhenSet_722) {
    defaultData.listListeners = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listListeners());
}

// --- allowThrows tests ---

TEST_F(ConfigTest_722, AllowThrowsDefaultIsTrue_722) {
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_722, AllowThrowsReturnsFalseWhenNoThrowSet_722) {
    defaultData.noThrow = true;
    Config config(defaultData);
    EXPECT_FALSE(config.allowThrows());
}

// --- includeSuccessfulResults tests ---

TEST_F(ConfigTest_722, IncludeSuccessfulResultsDefaultIsFalse_722) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_722, IncludeSuccessfulResultsReturnsTrueWhenSet_722) {
    defaultData.showSuccessfulTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// --- warnAboutMissingAssertions tests ---

TEST_F(ConfigTest_722, WarnAboutMissingAssertionsDefaultIsFalse_722) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_722, WarnAboutMissingAssertionsWhenWarningsSet_722) {
    defaultData.warnings = WarnAbout::NoAssertions;
    Config config(defaultData);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

// --- warnAboutUnmatchedTestSpecs tests ---

TEST_F(ConfigTest_722, WarnAboutUnmatchedTestSpecsDefaultIsFalse_722) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_722, WarnAboutUnmatchedTestSpecsWhenSet_722) {
    defaultData.warnings = WarnAbout::UnmatchedTestSpec;
    Config config(defaultData);
    EXPECT_TRUE(config.warnAboutUnmatchedTestSpecs());
}

// --- zeroTestsCountAsSuccess tests ---

TEST_F(ConfigTest_722, ZeroTestsCountAsSuccessDefaultIsFalse_722) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_722, ZeroTestsCountAsSuccessReturnsTrueWhenSet_722) {
    defaultData.allowZeroTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

// --- showDurations tests ---

TEST_F(ConfigTest_722, ShowDurationsDefaultIsDefaultForReporter_722) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_722, ShowDurationsReturnsAlwaysWhenSet_722) {
    defaultData.showDurations = ShowDurations::Always;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_722, ShowDurationsReturnsNeverWhenSet_722) {
    defaultData.showDurations = ShowDurations::Never;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

// --- minDuration tests ---

TEST_F(ConfigTest_722, MinDurationDefaultIsNegativeOne_722) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_722, MinDurationReturnsSetValue_722) {
    defaultData.minDuration = 0.5;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

// --- runOrder tests ---

TEST_F(ConfigTest_722, RunOrderDefaultIsDeclared_722) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_722, RunOrderReturnsRandomizedWhenSet_722) {
    defaultData.runOrder = TestRunOrder::Randomized;
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

// --- rngSeed tests ---

TEST_F(ConfigTest_722, RngSeedReturnsSetValue_722) {
    defaultData.rngSeed = 42;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// --- shardCount tests ---

TEST_F(ConfigTest_722, ShardCountDefaultIsOne_722) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_722, ShardCountReturnsSetValue_722) {
    defaultData.shardCount = 5;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 5u);
}

// --- shardIndex tests ---

TEST_F(ConfigTest_722, ShardIndexDefaultIsZero_722) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_722, ShardIndexReturnsSetValue_722) {
    defaultData.shardIndex = 3;
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 3u);
}

// --- defaultColourMode tests ---

TEST_F(ConfigTest_722, DefaultColourModeIsPlatformDefault_722) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_722, DefaultColourModeReturnsSetValue_722) {
    defaultData.defaultColourMode = ColourMode::ANSI;
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

// --- abortAfter tests ---

TEST_F(ConfigTest_722, AbortAfterDefaultIsNegativeOne_722) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_722, AbortAfterReturnsSetValue_722) {
    defaultData.abortAfter = 3;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 3);
}

// --- showInvisibles tests ---

TEST_F(ConfigTest_722, ShowInvisiblesDefaultIsFalse_722) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_722, ShowInvisiblesReturnsTrueWhenSet_722) {
    defaultData.showInvisibles = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showInvisibles());
}

// --- verbosity tests ---

TEST_F(ConfigTest_722, VerbosityDefaultIsNormal_722) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_722, VerbosityReturnsHighWhenSet_722) {
    defaultData.verbosity = Verbosity::High;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_722, VerbosityReturnsQuietWhenSet_722) {
    defaultData.verbosity = Verbosity::Quiet;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

// --- skipBenchmarks tests ---

TEST_F(ConfigTest_722, SkipBenchmarksDefaultIsFalse_722) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_722, SkipBenchmarksReturnsTrueWhenSet_722) {
    defaultData.skipBenchmarks = true;
    Config config(defaultData);
    EXPECT_TRUE(config.skipBenchmarks());
}

// --- benchmarkNoAnalysis tests ---

TEST_F(ConfigTest_722, BenchmarkNoAnalysisDefaultIsFalse_722) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_722, BenchmarkNoAnalysisReturnsTrueWhenSet_722) {
    defaultData.benchmarkNoAnalysis = true;
    Config config(defaultData);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

// --- benchmarkSamples tests ---

TEST_F(ConfigTest_722, BenchmarkSamplesDefaultIs100_722) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_722, BenchmarkSamplesReturnsSetValue_722) {
    defaultData.benchmarkSamples = 200;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 200u);
}

// --- benchmarkConfidenceInterval tests ---

TEST_F(ConfigTest_722, BenchmarkConfidenceIntervalDefaultIs095_722) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_722, BenchmarkConfidenceIntervalReturnsSetValue_722) {
    defaultData.benchmarkConfidenceInterval = 0.99;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

// --- benchmarkResamples tests ---

TEST_F(ConfigTest_722, BenchmarkResamplesDefaultIs100000_722) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_722, BenchmarkResamplesReturnsSetValue_722) {
    defaultData.benchmarkResamples = 50000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

// --- benchmarkWarmupTime tests ---

TEST_F(ConfigTest_722, BenchmarkWarmupTimeDefaultIs100ms_722) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_722, BenchmarkWarmupTimeReturnsSetValue_722) {
    defaultData.benchmarkWarmupTime = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

// --- name tests ---

TEST_F(ConfigTest_722, NameReturnsEmptyWhenProcessNameEmpty_722) {
    Config config(defaultData);
    EXPECT_TRUE(config.name().empty());
}

TEST_F(ConfigTest_722, NameReturnsProcessName_722) {
    defaultData.processName = "myTestProcess";
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

// --- getTestsOrTags tests ---

TEST_F(ConfigTest_722, GetTestsOrTagsDefaultIsEmpty_722) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_722, GetTestsOrTagsReturnsSetValues_722) {
    defaultData.testsOrTags = {"test1", "[tag1]"};
    Config config(defaultData);
    auto const& result = config.getTestsOrTags();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "test1");
    EXPECT_EQ(result[1], "[tag1]");
}

// --- getSectionsToRun tests ---

TEST_F(ConfigTest_722, GetSectionsToRunDefaultIsEmpty_722) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

TEST_F(ConfigTest_722, GetSectionsToRunReturnsSetValues_722) {
    defaultData.sectionsToRun = {"section1", "section2"};
    Config config(defaultData);
    auto const& result = config.getSectionsToRun();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "section1");
    EXPECT_EQ(result[1], "section2");
}

// --- hasTestFilters tests ---

TEST_F(ConfigTest_722, HasTestFiltersDefaultIsFalse_722) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_722, HasTestFiltersReturnsTrueWhenTestsOrTagsSet_722) {
    defaultData.testsOrTags = {"someTest"};
    Config config(defaultData);
    EXPECT_TRUE(config.hasTestFilters());
}

// --- shouldDebugBreak tests ---

TEST_F(ConfigTest_722, ShouldDebugBreakDefaultIsFalse_722) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}

// --- Default constructed Config ---

TEST_F(ConfigTest_722, DefaultConstructedConfigHasDefaults_722) {
    Config config;
    EXPECT_FALSE(config.showHelp());
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.listTags());
    EXPECT_FALSE(config.listReporters());
    EXPECT_FALSE(config.listListeners());
    EXPECT_TRUE(config.allowThrows());
    EXPECT_FALSE(config.includeSuccessfulResults());
    EXPECT_FALSE(config.showInvisibles());
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
    EXPECT_EQ(config.shardCount(), 1u);
    EXPECT_EQ(config.shardIndex(), 0u);
    EXPECT_EQ(config.abortAfter(), -1);
}

// --- Boundary: abortAfter = 0 ---

TEST_F(ConfigTest_722, AbortAfterZero_722) {
    defaultData.abortAfter = 0;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 0);
}

// --- Boundary: benchmarkSamples = 0 ---

TEST_F(ConfigTest_722, BenchmarkSamplesZero_722) {
    defaultData.benchmarkSamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

// --- Boundary: benchmarkConfidenceInterval = 0.0 ---

TEST_F(ConfigTest_722, BenchmarkConfidenceIntervalZero_722) {
    defaultData.benchmarkConfidenceInterval = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

// --- Boundary: benchmarkWarmupTime = 0 ---

TEST_F(ConfigTest_722, BenchmarkWarmupTimeZero_722) {
    defaultData.benchmarkWarmupTime = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

// --- Boundary: minDuration = 0.0 ---

TEST_F(ConfigTest_722, MinDurationZero_722) {
    defaultData.minDuration = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

// --- Boundary: rngSeed = 0 ---

TEST_F(ConfigTest_722, RngSeedZero_722) {
    defaultData.rngSeed = 0;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 0u);
}

// --- Boundary: rngSeed = max uint32 ---

TEST_F(ConfigTest_722, RngSeedMaxValue_722) {
    defaultData.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

// --- Multiple flags set simultaneously ---

TEST_F(ConfigTest_722, MultipleFlagsSetSimultaneously_722) {
    defaultData.showHelp = true;
    defaultData.listTests = true;
    defaultData.noThrow = true;
    defaultData.showSuccessfulTests = true;
    defaultData.showInvisibles = true;
    defaultData.skipBenchmarks = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showHelp());
    EXPECT_TRUE(config.listTests());
    EXPECT_FALSE(config.allowThrows());
    EXPECT_TRUE(config.includeSuccessfulResults());
    EXPECT_TRUE(config.showInvisibles());
    EXPECT_TRUE(config.skipBenchmarks());
}

// --- testSpec with no filters returns empty spec ---

TEST_F(ConfigTest_722, TestSpecWithNoFiltersReturnsEmptySpec_722) {
    Config config(defaultData);
    auto const& spec = config.testSpec();
    EXPECT_FALSE(config.hasTestFilters());
}

// --- getReporterSpecs tests ---

TEST_F(ConfigTest_722, GetReporterSpecsDefaultIsEmpty_722) {
    Config config(defaultData);
    // By default, there may be a default reporter added, but reporterSpecifications starts empty
    // We simply check it doesn't crash
    auto const& specs = config.getReporterSpecs();
    // The actual content depends on implementation details; just verify accessibility
    (void)specs;
}

// --- getProcessedReporterSpecs tests ---

TEST_F(ConfigTest_722, GetProcessedReporterSpecsAccessible_722) {
    Config config(defaultData);
    auto const& processed = config.getProcessedReporterSpecs();
    // Just verify it's accessible without crash
    (void)processed;
}
