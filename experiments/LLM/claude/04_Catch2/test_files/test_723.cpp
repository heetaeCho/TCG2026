#include "catch2/catch_config.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace Catch;

class ConfigTest_723 : public ::testing::Test {
protected:
    ConfigData makeDefaultData() {
        ConfigData data;
        return data;
    }
};

// ==================== allowThrows ====================

TEST_F(ConfigTest_723, AllowThrowsDefaultIsTrue_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_723, AllowThrowsReturnsFalseWhenNoThrowIsTrue_723) {
    ConfigData data = makeDefaultData();
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_723, AllowThrowsReturnsTrueWhenNoThrowIsFalse_723) {
    ConfigData data = makeDefaultData();
    data.noThrow = false;
    Config config(data);
    EXPECT_TRUE(config.allowThrows());
}

// ==================== listTests ====================

TEST_F(ConfigTest_723, ListTestsDefaultIsFalse_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_723, ListTestsReturnsTrueWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

// ==================== listTags ====================

TEST_F(ConfigTest_723, ListTagsDefaultIsFalse_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_723, ListTagsReturnsTrueWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

// ==================== listReporters ====================

TEST_F(ConfigTest_723, ListReportersDefaultIsFalse_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_723, ListReportersReturnsTrueWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

// ==================== listListeners ====================

TEST_F(ConfigTest_723, ListListenersDefaultIsFalse_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_723, ListListenersReturnsTrueWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

// ==================== showHelp ====================

TEST_F(ConfigTest_723, ShowHelpDefaultIsFalse_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_723, ShowHelpReturnsTrueWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

// ==================== includeSuccessfulResults ====================

TEST_F(ConfigTest_723, IncludeSuccessfulResultsDefaultIsFalse_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_723, IncludeSuccessfulResultsReturnsTrueWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// ==================== warnAboutMissingAssertions ====================

TEST_F(ConfigTest_723, WarnAboutMissingAssertionsDefaultIsFalse_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_723, WarnAboutMissingAssertionsReturnsTrueWhenWarningsSet_723) {
    ConfigData data = makeDefaultData();
    data.warnings = static_cast<WarnAbout::What>(
        data.warnings | WarnAbout::NoAssertions);
    Config config(data);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

// ==================== warnAboutUnmatchedTestSpecs ====================

TEST_F(ConfigTest_723, WarnAboutUnmatchedTestSpecsDefaultIsFalse_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_723, WarnAboutUnmatchedTestSpecsReturnsTrueWhenWarningsSet_723) {
    ConfigData data = makeDefaultData();
    data.warnings = static_cast<WarnAbout::What>(
        data.warnings | WarnAbout::UnmatchedTestSpec);
    Config config(data);
    EXPECT_TRUE(config.warnAboutUnmatchedTestSpecs());
}

// ==================== zeroTestsCountAsSuccess ====================

TEST_F(ConfigTest_723, ZeroTestsCountAsSuccessDefaultIsFalse_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_723, ZeroTestsCountAsSuccessReturnsTrueWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

// ==================== showInvisibles ====================

TEST_F(ConfigTest_723, ShowInvisiblesDefaultIsFalse_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_723, ShowInvisiblesReturnsTrueWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

// ==================== showDurations ====================

TEST_F(ConfigTest_723, ShowDurationsDefaultIsDefaultForReporter_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_723, ShowDurationsReturnsAlwaysWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_723, ShowDurationsReturnsNeverWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

// ==================== minDuration ====================

TEST_F(ConfigTest_723, MinDurationDefaultIsNegativeOne_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_723, MinDurationReturnsSetValue_723) {
    ConfigData data = makeDefaultData();
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

// ==================== runOrder ====================

TEST_F(ConfigTest_723, RunOrderDefaultIsDeclared_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_723, RunOrderReturnsRandomizedWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_723, RunOrderReturnsLexicographicallySortedWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.runOrder = TestRunOrder::LexicographicallySorted;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::LexicographicallySorted);
}

// ==================== rngSeed ====================

TEST_F(ConfigTest_723, RngSeedReturnsSetValue_723) {
    ConfigData data = makeDefaultData();
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// ==================== shardCount ====================

TEST_F(ConfigTest_723, ShardCountDefaultIsOne_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_723, ShardCountReturnsSetValue_723) {
    ConfigData data = makeDefaultData();
    data.shardCount = 5;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 5u);
}

// ==================== shardIndex ====================

TEST_F(ConfigTest_723, ShardIndexDefaultIsZero_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_723, ShardIndexReturnsSetValue_723) {
    ConfigData data = makeDefaultData();
    data.shardIndex = 3;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 3u);
}

// ==================== defaultColourMode ====================

TEST_F(ConfigTest_723, DefaultColourModeDefaultIsPlatformDefault_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_723, DefaultColourModeReturnsAnsiWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.defaultColourMode = ColourMode::ANSI;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_723, DefaultColourModeReturnsNoneWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.defaultColourMode = ColourMode::None;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::None);
}

// ==================== abortAfter ====================

TEST_F(ConfigTest_723, AbortAfterDefaultIsNegativeOne_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_723, AbortAfterReturnsSetValue_723) {
    ConfigData data = makeDefaultData();
    data.abortAfter = 3;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 3);
}

TEST_F(ConfigTest_723, AbortAfterReturnsZero_723) {
    ConfigData data = makeDefaultData();
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

// ==================== verbosity ====================

TEST_F(ConfigTest_723, VerbosityDefaultIsNormal_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_723, VerbosityReturnsQuietWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_723, VerbosityReturnsHighWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

// ==================== skipBenchmarks ====================

TEST_F(ConfigTest_723, SkipBenchmarksDefaultIsFalse_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_723, SkipBenchmarksReturnsTrueWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

// ==================== benchmarkNoAnalysis ====================

TEST_F(ConfigTest_723, BenchmarkNoAnalysisDefaultIsFalse_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_723, BenchmarkNoAnalysisReturnsTrueWhenSet_723) {
    ConfigData data = makeDefaultData();
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

// ==================== benchmarkSamples ====================

TEST_F(ConfigTest_723, BenchmarkSamplesDefaultIs100_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_723, BenchmarkSamplesReturnsSetValue_723) {
    ConfigData data = makeDefaultData();
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

// ==================== benchmarkConfidenceInterval ====================

TEST_F(ConfigTest_723, BenchmarkConfidenceIntervalDefaultIs095_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_723, BenchmarkConfidenceIntervalReturnsSetValue_723) {
    ConfigData data = makeDefaultData();
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

// ==================== benchmarkResamples ====================

TEST_F(ConfigTest_723, BenchmarkResamplesDefaultIs100000_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_723, BenchmarkResamplesReturnsSetValue_723) {
    ConfigData data = makeDefaultData();
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

// ==================== benchmarkWarmupTime ====================

TEST_F(ConfigTest_723, BenchmarkWarmupTimeDefaultIs100ms_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_723, BenchmarkWarmupTimeReturnsSetValue_723) {
    ConfigData data = makeDefaultData();
    data.benchmarkWarmupTime = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

// ==================== name ====================

TEST_F(ConfigTest_723, NameReturnsProcessName_723) {
    ConfigData data = makeDefaultData();
    data.processName = "my_test_process";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("my_test_process"));
}

TEST_F(ConfigTest_723, NameReturnsEmptyWhenProcessNameEmpty_723) {
    ConfigData data = makeDefaultData();
    data.processName = "";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef(""));
}

// ==================== getTestsOrTags ====================

TEST_F(ConfigTest_723, GetTestsOrTagsDefaultIsEmpty_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_723, GetTestsOrTagsReturnsSetValues_723) {
    ConfigData data = makeDefaultData();
    data.testsOrTags = {"test1", "[tag1]", "test2"};
    Config config(data);
    const auto& result = config.getTestsOrTags();
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "test1");
    EXPECT_EQ(result[1], "[tag1]");
    EXPECT_EQ(result[2], "test2");
}

// ==================== getSectionsToRun ====================

TEST_F(ConfigTest_723, GetSectionsToRunDefaultIsEmpty_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

TEST_F(ConfigTest_723, GetSectionsToRunReturnsSetValues_723) {
    ConfigData data = makeDefaultData();
    data.sectionsToRun = {"section1", "section2"};
    Config config(data);
    const auto& result = config.getSectionsToRun();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "section1");
    EXPECT_EQ(result[1], "section2");
}

// ==================== hasTestFilters ====================

TEST_F(ConfigTest_723, HasTestFiltersDefaultIsFalse_723) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_723, HasTestFiltersReturnsTrueWhenTestsOrTagsProvided_723) {
    ConfigData data = makeDefaultData();
    data.testsOrTags = {"someTest"};
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

// ==================== Default construction ====================

TEST_F(ConfigTest_723, DefaultConstructedConfigHasExpectedDefaults_723) {
    Config config;
    EXPECT_TRUE(config.allowThrows());
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.listTags());
    EXPECT_FALSE(config.listReporters());
    EXPECT_FALSE(config.listListeners());
    EXPECT_FALSE(config.showHelp());
    EXPECT_FALSE(config.showInvisibles());
    EXPECT_FALSE(config.includeSuccessfulResults());
    EXPECT_FALSE(config.skipBenchmarks());
    EXPECT_FALSE(config.benchmarkNoAnalysis());
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
    EXPECT_EQ(config.abortAfter(), -1);
    EXPECT_EQ(config.shardCount(), 1u);
    EXPECT_EQ(config.shardIndex(), 0u);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

// ==================== Boundary: shardCount zero ====================

TEST_F(ConfigTest_723, ShardCountZero_723) {
    ConfigData data = makeDefaultData();
    data.shardCount = 0;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 0u);
}

// ==================== Boundary: abortAfter zero ====================

TEST_F(ConfigTest_723, AbortAfterZeroValue_723) {
    ConfigData data = makeDefaultData();
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

// ==================== Boundary: benchmarkSamples zero ====================

TEST_F(ConfigTest_723, BenchmarkSamplesZero_723) {
    ConfigData data = makeDefaultData();
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

// ==================== Boundary: benchmarkWarmupTime zero ====================

TEST_F(ConfigTest_723, BenchmarkWarmupTimeZero_723) {
    ConfigData data = makeDefaultData();
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

// ==================== Boundary: minDuration zero ====================

TEST_F(ConfigTest_723, MinDurationZero_723) {
    ConfigData data = makeDefaultData();
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

// ==================== Boundary: benchmarkConfidenceInterval extremes ====================

TEST_F(ConfigTest_723, BenchmarkConfidenceIntervalZero_723) {
    ConfigData data = makeDefaultData();
    data.benchmarkConfidenceInterval = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_723, BenchmarkConfidenceIntervalOne_723) {
    ConfigData data = makeDefaultData();
    data.benchmarkConfidenceInterval = 1.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

// ==================== Multiple flags set at once ====================

TEST_F(ConfigTest_723, MultipleFlagsSetSimultaneously_723) {
    ConfigData data = makeDefaultData();
    data.noThrow = true;
    data.showHelp = true;
    data.showSuccessfulTests = true;
    data.showInvisibles = true;
    data.skipBenchmarks = true;
    data.benchmarkNoAnalysis = true;
    data.allowZeroTests = true;
    data.listTests = true;
    data.listTags = true;

    Config config(data);

    EXPECT_FALSE(config.allowThrows());
    EXPECT_TRUE(config.showHelp());
    EXPECT_TRUE(config.includeSuccessfulResults());
    EXPECT_TRUE(config.showInvisibles());
    EXPECT_TRUE(config.skipBenchmarks());
    EXPECT_TRUE(config.benchmarkNoAnalysis());
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
    EXPECT_TRUE(config.listTests());
    EXPECT_TRUE(config.listTags());
}
