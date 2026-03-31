#include "catch2/catch_config.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <chrono>

using namespace Catch;

class ConfigTest_713 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// --- listTests ---

TEST_F(ConfigTest_713, ListTestsDefaultFalse_713) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_713, ListTestsSetTrue_713) {
    defaultData.listTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTests());
}

// --- listTags ---

TEST_F(ConfigTest_713, ListTagsDefaultFalse_713) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_713, ListTagsSetTrue_713) {
    defaultData.listTags = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTags());
}

// --- listReporters ---

TEST_F(ConfigTest_713, ListReportersDefaultFalse_713) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_713, ListReportersSetTrue_713) {
    defaultData.listReporters = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listReporters());
}

// --- listListeners ---

TEST_F(ConfigTest_713, ListListenersDefaultFalse_713) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_713, ListListenersSetTrue_713) {
    defaultData.listListeners = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listListeners());
}

// --- showHelp ---

TEST_F(ConfigTest_713, ShowHelpDefaultFalse_713) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_713, ShowHelpSetTrue_713) {
    defaultData.showHelp = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showHelp());
}

// --- allowThrows ---

TEST_F(ConfigTest_713, AllowThrowsDefaultTrue_713) {
    // noThrow defaults to false, so allowThrows should be true
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_713, AllowThrowsFalseWhenNoThrowTrue_713) {
    defaultData.noThrow = true;
    Config config(defaultData);
    EXPECT_FALSE(config.allowThrows());
}

// --- includeSuccessfulResults ---

TEST_F(ConfigTest_713, IncludeSuccessfulResultsDefaultFalse_713) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_713, IncludeSuccessfulResultsSetTrue_713) {
    defaultData.showSuccessfulTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// --- showInvisibles ---

TEST_F(ConfigTest_713, ShowInvisiblesDefaultFalse_713) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_713, ShowInvisiblesSetTrue_713) {
    defaultData.showInvisibles = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showInvisibles());
}

// --- abortAfter ---

TEST_F(ConfigTest_713, AbortAfterDefault_713) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_713, AbortAfterSetValue_713) {
    defaultData.abortAfter = 5;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_713, AbortAfterZero_713) {
    defaultData.abortAfter = 0;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 0);
}

// --- shardCount ---

TEST_F(ConfigTest_713, ShardCountDefault_713) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_713, ShardCountSetValue_713) {
    defaultData.shardCount = 4;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 4u);
}

// --- shardIndex ---

TEST_F(ConfigTest_713, ShardIndexDefault_713) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_713, ShardIndexSetValue_713) {
    defaultData.shardIndex = 3;
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 3u);
}

// --- skipBenchmarks ---

TEST_F(ConfigTest_713, SkipBenchmarksDefaultFalse_713) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_713, SkipBenchmarksSetTrue_713) {
    defaultData.skipBenchmarks = true;
    Config config(defaultData);
    EXPECT_TRUE(config.skipBenchmarks());
}

// --- benchmarkNoAnalysis ---

TEST_F(ConfigTest_713, BenchmarkNoAnalysisDefaultFalse_713) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_713, BenchmarkNoAnalysisSetTrue_713) {
    defaultData.benchmarkNoAnalysis = true;
    Config config(defaultData);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

// --- benchmarkSamples ---

TEST_F(ConfigTest_713, BenchmarkSamplesDefault_713) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_713, BenchmarkSamplesSetValue_713) {
    defaultData.benchmarkSamples = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

// --- benchmarkConfidenceInterval ---

TEST_F(ConfigTest_713, BenchmarkConfidenceIntervalDefault_713) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_713, BenchmarkConfidenceIntervalSetValue_713) {
    defaultData.benchmarkConfidenceInterval = 0.99;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

// --- benchmarkResamples ---

TEST_F(ConfigTest_713, BenchmarkResamplesDefault_713) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_713, BenchmarkResamplesSetValue_713) {
    defaultData.benchmarkResamples = 50000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

// --- benchmarkWarmupTime ---

TEST_F(ConfigTest_713, BenchmarkWarmupTimeDefault_713) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_713, BenchmarkWarmupTimeSetValue_713) {
    defaultData.benchmarkWarmupTime = 200;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

// --- verbosity ---

TEST_F(ConfigTest_713, VerbosityDefault_713) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_713, VerbositySetHigh_713) {
    defaultData.verbosity = Verbosity::High;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_713, VerbositySetQuiet_713) {
    defaultData.verbosity = Verbosity::Quiet;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

// --- showDurations ---

TEST_F(ConfigTest_713, ShowDurationsDefault_713) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_713, ShowDurationsSetAlways_713) {
    defaultData.showDurations = ShowDurations::Always;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_713, ShowDurationsSetNever_713) {
    defaultData.showDurations = ShowDurations::Never;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

// --- minDuration ---

TEST_F(ConfigTest_713, MinDurationDefault_713) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_713, MinDurationSetValue_713) {
    defaultData.minDuration = 0.5;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

// --- runOrder ---

TEST_F(ConfigTest_713, RunOrderDefault_713) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_713, RunOrderSetRandomized_713) {
    defaultData.runOrder = TestRunOrder::Randomized;
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

// --- defaultColourMode ---

TEST_F(ConfigTest_713, DefaultColourModeDefault_713) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

// --- rngSeed ---

TEST_F(ConfigTest_713, RngSeedSetValue_713) {
    defaultData.rngSeed = 42;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// --- name ---

TEST_F(ConfigTest_713, NameFromProcessName_713) {
    defaultData.processName = "myTestProcess";
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

TEST_F(ConfigTest_713, NameEmptyByDefault_713) {
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef(""));
}

// --- warnAboutMissingAssertions ---

TEST_F(ConfigTest_713, WarnAboutMissingAssertionsDefault_713) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_713, WarnAboutMissingAssertionsEnabled_713) {
    defaultData.warnings = WarnAbout::NoAssertions;
    Config config(defaultData);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

// --- zeroTestsCountAsSuccess ---

TEST_F(ConfigTest_713, ZeroTestsCountAsSuccessDefault_713) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_713, ZeroTestsCountAsSuccessSetTrue_713) {
    defaultData.allowZeroTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

// --- getTestsOrTags ---

TEST_F(ConfigTest_713, GetTestsOrTagsEmpty_713) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_713, GetTestsOrTagsWithValues_713) {
    defaultData.testsOrTags = {"[tag1]", "testA"};
    Config config(defaultData);
    auto const& result = config.getTestsOrTags();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "[tag1]");
    EXPECT_EQ(result[1], "testA");
}

// --- getSectionsToRun ---

TEST_F(ConfigTest_713, GetSectionsToRunEmpty_713) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

TEST_F(ConfigTest_713, GetSectionsToRunWithValues_713) {
    defaultData.sectionsToRun = {"sectionA", "sectionB"};
    Config config(defaultData);
    auto const& result = config.getSectionsToRun();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "sectionA");
    EXPECT_EQ(result[1], "sectionB");
}

// --- hasTestFilters ---

TEST_F(ConfigTest_713, HasTestFiltersDefaultFalse_713) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_713, HasTestFiltersWithTestSpec_713) {
    defaultData.testsOrTags = {"someTest"};
    Config config(defaultData);
    EXPECT_TRUE(config.hasTestFilters());
}

// --- shouldDebugBreak ---

TEST_F(ConfigTest_713, ShouldDebugBreakDefaultFalse_713) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}

// --- Default constructed Config ---

TEST_F(ConfigTest_713, DefaultConstructedConfig_713) {
    Config config;
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.listTags());
    EXPECT_FALSE(config.listReporters());
    EXPECT_FALSE(config.listListeners());
    EXPECT_FALSE(config.showHelp());
    EXPECT_TRUE(config.allowThrows());
    EXPECT_FALSE(config.includeSuccessfulResults());
    EXPECT_FALSE(config.showInvisibles());
    EXPECT_FALSE(config.skipBenchmarks());
    EXPECT_FALSE(config.benchmarkNoAnalysis());
    EXPECT_EQ(config.benchmarkSamples(), 100u);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
    EXPECT_EQ(config.abortAfter(), -1);
    EXPECT_EQ(config.shardCount(), 1u);
    EXPECT_EQ(config.shardIndex(), 0u);
}

// --- Multiple fields set simultaneously ---

TEST_F(ConfigTest_713, MultipleFieldsSetSimultaneously_713) {
    defaultData.listTests = true;
    defaultData.listTags = true;
    defaultData.noThrow = true;
    defaultData.showSuccessfulTests = true;
    defaultData.abortAfter = 10;
    defaultData.shardCount = 3;
    defaultData.shardIndex = 1;
    defaultData.verbosity = Verbosity::High;
    defaultData.benchmarkSamples = 200;
    
    Config config(defaultData);
    
    EXPECT_TRUE(config.listTests());
    EXPECT_TRUE(config.listTags());
    EXPECT_FALSE(config.allowThrows());
    EXPECT_TRUE(config.includeSuccessfulResults());
    EXPECT_EQ(config.abortAfter(), 10);
    EXPECT_EQ(config.shardCount(), 3u);
    EXPECT_EQ(config.shardIndex(), 1u);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
    EXPECT_EQ(config.benchmarkSamples(), 200u);
}

// --- Boundary: benchmarkConfidenceInterval edge values ---

TEST_F(ConfigTest_713, BenchmarkConfidenceIntervalZero_713) {
    defaultData.benchmarkConfidenceInterval = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_713, BenchmarkConfidenceIntervalOne_713) {
    defaultData.benchmarkConfidenceInterval = 1.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

// --- Boundary: benchmarkWarmupTime zero ---

TEST_F(ConfigTest_713, BenchmarkWarmupTimeZero_713) {
    defaultData.benchmarkWarmupTime = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

// --- Boundary: abortAfter large value ---

TEST_F(ConfigTest_713, AbortAfterLargeValue_713) {
    defaultData.abortAfter = 999999;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 999999);
}

// --- Boundary: minDuration zero ---

TEST_F(ConfigTest_713, MinDurationZero_713) {
    defaultData.minDuration = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}
