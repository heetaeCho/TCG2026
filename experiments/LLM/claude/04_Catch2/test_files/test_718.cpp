#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_718 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// Test default construction and default values
TEST_F(ConfigTest_718, DefaultConstruction_718) {
    Config config;
    // Just verify it can be default constructed without crashing
}

TEST_F(ConfigTest_718, ConstructionWithData_718) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

// listTests
TEST_F(ConfigTest_718, ListTestsDefaultFalse_718) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_718, ListTestsTrue_718) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

// listTags
TEST_F(ConfigTest_718, ListTagsDefaultFalse_718) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_718, ListTagsTrue_718) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

// listReporters
TEST_F(ConfigTest_718, ListReportersDefaultFalse_718) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_718, ListReportersTrue_718) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

// listListeners
TEST_F(ConfigTest_718, ListListenersDefaultFalse_718) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_718, ListListenersTrue_718) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

// showHelp
TEST_F(ConfigTest_718, ShowHelpDefaultFalse_718) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_718, ShowHelpTrue_718) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

// allowThrows (inverse of noThrow)
TEST_F(ConfigTest_718, AllowThrowsDefaultTrue_718) {
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_718, AllowThrowsFalseWhenNoThrowTrue_718) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

// includeSuccessfulResults
TEST_F(ConfigTest_718, IncludeSuccessfulResultsDefaultFalse_718) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_718, IncludeSuccessfulResultsTrue_718) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// warnAboutMissingAssertions
TEST_F(ConfigTest_718, WarnAboutMissingAssertionsDefaultFalse_718) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

// zeroTestsCountAsSuccess
TEST_F(ConfigTest_718, ZeroTestsCountAsSuccessDefaultFalse_718) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_718, ZeroTestsCountAsSuccessTrue_718) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

// showDurations
TEST_F(ConfigTest_718, ShowDurationsDefault_718) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

// minDuration
TEST_F(ConfigTest_718, MinDurationDefault_718) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_718, MinDurationCustom_718) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

// runOrder
TEST_F(ConfigTest_718, RunOrderDefault_718) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_718, RunOrderRandomize_718) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

// rngSeed
TEST_F(ConfigTest_718, RngSeedCustom_718) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// shardCount
TEST_F(ConfigTest_718, ShardCountDefault_718) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_718, ShardCountCustom_718) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

// shardIndex
TEST_F(ConfigTest_718, ShardIndexDefault_718) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_718, ShardIndexCustom_718) {
    ConfigData data;
    data.shardIndex = 2;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 2u);
}

// defaultColourMode
TEST_F(ConfigTest_718, DefaultColourModeDefault_718) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

// abortAfter
TEST_F(ConfigTest_718, AbortAfterDefault_718) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_718, AbortAfterCustom_718) {
    ConfigData data;
    data.abortAfter = 3;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 3);
}

// showInvisibles
TEST_F(ConfigTest_718, ShowInvisiblesDefaultFalse_718) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_718, ShowInvisiblesTrue_718) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

// verbosity
TEST_F(ConfigTest_718, VerbosityDefault_718) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_718, VerbosityHigh_718) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

// skipBenchmarks
TEST_F(ConfigTest_718, SkipBenchmarksDefaultFalse_718) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_718, SkipBenchmarksTrue_718) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

// benchmarkNoAnalysis
TEST_F(ConfigTest_718, BenchmarkNoAnalysisDefaultFalse_718) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_718, BenchmarkNoAnalysisTrue_718) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

// benchmarkSamples
TEST_F(ConfigTest_718, BenchmarkSamplesDefault_718) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_718, BenchmarkSamplesCustom_718) {
    ConfigData data;
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

// benchmarkConfidenceInterval
TEST_F(ConfigTest_718, BenchmarkConfidenceIntervalDefault_718) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_718, BenchmarkConfidenceIntervalCustom_718) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

// benchmarkResamples
TEST_F(ConfigTest_718, BenchmarkResamplesDefault_718) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_718, BenchmarkResamplesCustom_718) {
    ConfigData data;
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

// benchmarkWarmupTime
TEST_F(ConfigTest_718, BenchmarkWarmupTimeDefault_718) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime().count(), 100);
}

TEST_F(ConfigTest_718, BenchmarkWarmupTimeCustom_718) {
    ConfigData data;
    data.benchmarkWarmupTime = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime().count(), 500);
}

// getTestsOrTags
TEST_F(ConfigTest_718, GetTestsOrTagsEmpty_718) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_718, GetTestsOrTagsWithValues_718) {
    ConfigData data;
    data.testsOrTags = {"test1", "[tag1]", "test2"};
    Config config(data);
    auto const& result = config.getTestsOrTags();
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "test1");
    EXPECT_EQ(result[1], "[tag1]");
    EXPECT_EQ(result[2], "test2");
}

// getSectionsToRun
TEST_F(ConfigTest_718, GetSectionsToRunEmpty_718) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

TEST_F(ConfigTest_718, GetSectionsToRunWithValues_718) {
    ConfigData data;
    data.sectionsToRun = {"section1", "section2"};
    Config config(data);
    auto const& result = config.getSectionsToRun();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "section1");
    EXPECT_EQ(result[1], "section2");
}

// getReporterSpecs
TEST_F(ConfigTest_718, GetReporterSpecsEmpty_718) {
    Config config(defaultData);
    // With default data, reporterSpecifications is empty
    auto const& specs = config.getReporterSpecs();
    EXPECT_TRUE(specs.empty());
}

// hasTestFilters
TEST_F(ConfigTest_718, HasTestFiltersDefaultFalse_718) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_718, HasTestFiltersWithTestsOrTags_718) {
    ConfigData data;
    data.testsOrTags = {"someTest"};
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

// name
TEST_F(ConfigTest_718, NameFromProcessName_718) {
    ConfigData data;
    data.processName = "myTestProcess";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

TEST_F(ConfigTest_718, NameEmptyByDefault_718) {
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef(""));
}

// testSpec
TEST_F(ConfigTest_718, TestSpecDefault_718) {
    Config config(defaultData);
    // Just verify it returns a valid reference and doesn't crash
    auto const& spec = config.testSpec();
    (void)spec;
}

// shouldDebugBreak
TEST_F(ConfigTest_718, ShouldDebugBreakDefault_718) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}

// Multiple settings at once
TEST_F(ConfigTest_718, MultipleSettingsCombined_718) {
    ConfigData data;
    data.listTests = true;
    data.listTags = true;
    data.noThrow = true;
    data.showInvisibles = true;
    data.verbosity = Verbosity::High;
    data.abortAfter = 5;
    data.shardCount = 3;
    data.shardIndex = 1;
    Config config(data);

    EXPECT_TRUE(config.listTests());
    EXPECT_TRUE(config.listTags());
    EXPECT_FALSE(config.allowThrows());
    EXPECT_TRUE(config.showInvisibles());
    EXPECT_EQ(config.verbosity(), Verbosity::High);
    EXPECT_EQ(config.abortAfter(), 5);
    EXPECT_EQ(config.shardCount(), 3u);
    EXPECT_EQ(config.shardIndex(), 1u);
}

// Boundary: abortAfter = 0
TEST_F(ConfigTest_718, AbortAfterZero_718) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

// Boundary: shardCount = 0
TEST_F(ConfigTest_718, ShardCountZero_718) {
    ConfigData data;
    data.shardCount = 0;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 0u);
}

// Boundary: benchmarkSamples = 0
TEST_F(ConfigTest_718, BenchmarkSamplesZero_718) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

// Boundary: minDuration = 0
TEST_F(ConfigTest_718, MinDurationZero_718) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

// Boundary: benchmarkWarmupTime = 0
TEST_F(ConfigTest_718, BenchmarkWarmupTimeZero_718) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime().count(), 0);
}

// getProcessedReporterSpecs - just test it returns a valid reference
TEST_F(ConfigTest_718, GetProcessedReporterSpecsDefault_718) {
    Config config(defaultData);
    auto const& processed = config.getProcessedReporterSpecs();
    // Default should have at least some processing done; just verify no crash
    (void)processed;
}
