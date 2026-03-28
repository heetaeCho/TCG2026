#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_712 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// --- listTests ---

TEST_F(ConfigTest_712, ListTestsDefaultFalse_712) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_712, ListTestsTrueWhenSet_712) {
    defaultData.listTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTests());
}

// --- listTags ---

TEST_F(ConfigTest_712, ListTagsDefaultFalse_712) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_712, ListTagsTrueWhenSet_712) {
    defaultData.listTags = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTags());
}

// --- listReporters ---

TEST_F(ConfigTest_712, ListReportersDefaultFalse_712) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_712, ListReportersTrueWhenSet_712) {
    defaultData.listReporters = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listReporters());
}

// --- listListeners ---

TEST_F(ConfigTest_712, ListListenersDefaultFalse_712) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_712, ListListenersTrueWhenSet_712) {
    defaultData.listListeners = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listListeners());
}

// --- showHelp ---

TEST_F(ConfigTest_712, ShowHelpDefaultFalse_712) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_712, ShowHelpTrueWhenSet_712) {
    defaultData.showHelp = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showHelp());
}

// --- allowThrows ---

TEST_F(ConfigTest_712, AllowThrowsDefaultTrue_712) {
    // noThrow defaults to false, so allowThrows should be true
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_712, AllowThrowsFalseWhenNoThrowSet_712) {
    defaultData.noThrow = true;
    Config config(defaultData);
    EXPECT_FALSE(config.allowThrows());
}

// --- includeSuccessfulResults ---

TEST_F(ConfigTest_712, IncludeSuccessfulResultsDefaultFalse_712) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_712, IncludeSuccessfulResultsTrueWhenSet_712) {
    defaultData.showSuccessfulTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// --- showInvisibles ---

TEST_F(ConfigTest_712, ShowInvisiblesDefaultFalse_712) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_712, ShowInvisiblesTrueWhenSet_712) {
    defaultData.showInvisibles = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showInvisibles());
}

// --- abortAfter ---

TEST_F(ConfigTest_712, AbortAfterDefault_712) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_712, AbortAfterCustomValue_712) {
    defaultData.abortAfter = 5;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_712, AbortAfterZero_712) {
    defaultData.abortAfter = 0;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 0);
}

// --- shardCount ---

TEST_F(ConfigTest_712, ShardCountDefault_712) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_712, ShardCountCustom_712) {
    defaultData.shardCount = 4;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 4u);
}

// --- shardIndex ---

TEST_F(ConfigTest_712, ShardIndexDefault_712) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_712, ShardIndexCustom_712) {
    defaultData.shardIndex = 3;
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 3u);
}

// --- verbosity ---

TEST_F(ConfigTest_712, VerbosityDefaultNormal_712) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_712, VerbosityHighWhenSet_712) {
    defaultData.verbosity = Verbosity::High;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_712, VerbosityQuietWhenSet_712) {
    defaultData.verbosity = Verbosity::Quiet;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

// --- showDurations ---

TEST_F(ConfigTest_712, ShowDurationsDefault_712) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_712, ShowDurationsAlwaysWhenSet_712) {
    defaultData.showDurations = ShowDurations::Always;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_712, ShowDurationsNeverWhenSet_712) {
    defaultData.showDurations = ShowDurations::Never;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

// --- minDuration ---

TEST_F(ConfigTest_712, MinDurationDefault_712) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_712, MinDurationCustom_712) {
    defaultData.minDuration = 0.5;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

// --- runOrder ---

TEST_F(ConfigTest_712, RunOrderDefaultDeclared_712) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_712, RunOrderRandomized_712) {
    defaultData.runOrder = TestRunOrder::Randomized;
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

// --- rngSeed ---

TEST_F(ConfigTest_712, RngSeedCustom_712) {
    defaultData.rngSeed = 42;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// --- defaultColourMode ---

TEST_F(ConfigTest_712, DefaultColourModeDefault_712) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_712, DefaultColourModeAnsiWhenSet_712) {
    defaultData.defaultColourMode = ColourMode::ANSI;
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

// --- skipBenchmarks ---

TEST_F(ConfigTest_712, SkipBenchmarksDefaultFalse_712) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_712, SkipBenchmarksTrueWhenSet_712) {
    defaultData.skipBenchmarks = true;
    Config config(defaultData);
    EXPECT_TRUE(config.skipBenchmarks());
}

// --- benchmarkNoAnalysis ---

TEST_F(ConfigTest_712, BenchmarkNoAnalysisDefaultFalse_712) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_712, BenchmarkNoAnalysisTrueWhenSet_712) {
    defaultData.benchmarkNoAnalysis = true;
    Config config(defaultData);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

// --- benchmarkSamples ---

TEST_F(ConfigTest_712, BenchmarkSamplesDefault_712) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_712, BenchmarkSamplesCustom_712) {
    defaultData.benchmarkSamples = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

// --- benchmarkConfidenceInterval ---

TEST_F(ConfigTest_712, BenchmarkConfidenceIntervalDefault_712) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_712, BenchmarkConfidenceIntervalCustom_712) {
    defaultData.benchmarkConfidenceInterval = 0.99;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

// --- benchmarkResamples ---

TEST_F(ConfigTest_712, BenchmarkResamplesDefault_712) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_712, BenchmarkResamplesCustom_712) {
    defaultData.benchmarkResamples = 50000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

// --- benchmarkWarmupTime ---

TEST_F(ConfigTest_712, BenchmarkWarmupTimeDefault_712) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_712, BenchmarkWarmupTimeCustom_712) {
    defaultData.benchmarkWarmupTime = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

// --- name ---

TEST_F(ConfigTest_712, NameEmptyByDefault_712) {
    Config config(defaultData);
    EXPECT_TRUE(config.name().empty());
}

TEST_F(ConfigTest_712, NameReturnsProcessName_712) {
    defaultData.processName = "myTestProcess";
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

// --- getTestsOrTags ---

TEST_F(ConfigTest_712, GetTestsOrTagsEmptyByDefault_712) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_712, GetTestsOrTagsReturnsValues_712) {
    defaultData.testsOrTags = {"test1", "[tag1]"};
    Config config(defaultData);
    auto const& result = config.getTestsOrTags();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "test1");
    EXPECT_EQ(result[1], "[tag1]");
}

// --- getSectionsToRun ---

TEST_F(ConfigTest_712, GetSectionsToRunEmptyByDefault_712) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

TEST_F(ConfigTest_712, GetSectionsToRunReturnsValues_712) {
    defaultData.sectionsToRun = {"section1", "section2"};
    Config config(defaultData);
    auto const& result = config.getSectionsToRun();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "section1");
    EXPECT_EQ(result[1], "section2");
}

// --- hasTestFilters ---

TEST_F(ConfigTest_712, HasTestFiltersDefaultFalse_712) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_712, HasTestFiltersTrueWhenTestsOrTagsSet_712) {
    defaultData.testsOrTags = {"someTest"};
    Config config(defaultData);
    EXPECT_TRUE(config.hasTestFilters());
}

// --- warnAboutMissingAssertions ---

TEST_F(ConfigTest_712, WarnAboutMissingAssertionsDefaultFalse_712) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_712, WarnAboutMissingAssertionsTrueWhenSet_712) {
    defaultData.warnings = WarnAbout::NoAssertions;
    Config config(defaultData);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

// --- zeroTestsCountAsSuccess ---

TEST_F(ConfigTest_712, ZeroTestsCountAsSuccessDefaultFalse_712) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_712, ZeroTestsCountAsSuccessTrueWhenSet_712) {
    defaultData.allowZeroTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

// --- Default constructed Config ---

TEST_F(ConfigTest_712, DefaultConstructedConfigHasDefaults_712) {
    Config config;
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.listTags());
    EXPECT_FALSE(config.showHelp());
    EXPECT_TRUE(config.allowThrows());
    EXPECT_FALSE(config.skipBenchmarks());
    EXPECT_EQ(config.shardCount(), 1u);
    EXPECT_EQ(config.shardIndex(), 0u);
    EXPECT_EQ(config.abortAfter(), -1);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

// --- Boundary: shardCount = 0 ---

TEST_F(ConfigTest_712, ShardCountZero_712) {
    defaultData.shardCount = 0;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 0u);
}

// --- Boundary: benchmarkSamples = 0 ---

TEST_F(ConfigTest_712, BenchmarkSamplesZero_712) {
    defaultData.benchmarkSamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

// --- Boundary: benchmarkWarmupTime = 0 ---

TEST_F(ConfigTest_712, BenchmarkWarmupTimeZero_712) {
    defaultData.benchmarkWarmupTime = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

// --- Boundary: minDuration = 0 ---

TEST_F(ConfigTest_712, MinDurationZero_712) {
    defaultData.minDuration = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

// --- Boundary: benchmarkConfidenceInterval edge values ---

TEST_F(ConfigTest_712, BenchmarkConfidenceIntervalZero_712) {
    defaultData.benchmarkConfidenceInterval = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_712, BenchmarkConfidenceIntervalOne_712) {
    defaultData.benchmarkConfidenceInterval = 1.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

// --- Multiple flags set simultaneously ---

TEST_F(ConfigTest_712, MultipleFlagsSetSimultaneously_712) {
    defaultData.listTests = true;
    defaultData.listTags = true;
    defaultData.listReporters = true;
    defaultData.listListeners = true;
    defaultData.showHelp = true;
    defaultData.noThrow = true;
    defaultData.showSuccessfulTests = true;
    defaultData.showInvisibles = true;
    defaultData.skipBenchmarks = true;
    defaultData.benchmarkNoAnalysis = true;
    defaultData.allowZeroTests = true;

    Config config(defaultData);

    EXPECT_TRUE(config.listTests());
    EXPECT_TRUE(config.listTags());
    EXPECT_TRUE(config.listReporters());
    EXPECT_TRUE(config.listListeners());
    EXPECT_TRUE(config.showHelp());
    EXPECT_FALSE(config.allowThrows());
    EXPECT_TRUE(config.includeSuccessfulResults());
    EXPECT_TRUE(config.showInvisibles());
    EXPECT_TRUE(config.skipBenchmarks());
    EXPECT_TRUE(config.benchmarkNoAnalysis());
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}
