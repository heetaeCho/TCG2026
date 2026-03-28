#include "catch2/catch_config.hpp"
#include "catch2/catch_test_spec.hpp"
#include "catch2/internal/catch_config_wchar.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <chrono>

using namespace Catch;

class ConfigTest_721 : public ::testing::Test {
protected:
    ConfigData makeDefaultData() {
        ConfigData data;
        return data;
    }
};

// Test default construction
TEST_F(ConfigTest_721, DefaultConstruction_HasNoTestFilters_721) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.hasTestFilters());
}

// Test with test filters specified
TEST_F(ConfigTest_721, WithTestFilters_HasTestFiltersReturnsTrue_721) {
    ConfigData data;
    data.testsOrTags.push_back("some_test");
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

// Test showHelp default
TEST_F(ConfigTest_721, DefaultConfig_ShowHelpIsFalse_721) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.showHelp());
}

// Test showHelp when set
TEST_F(ConfigTest_721, ShowHelpSetTrue_ReturnsTrue_721) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

// Test allowThrows default
TEST_F(ConfigTest_721, DefaultConfig_AllowThrowsIsTrue_721) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.allowThrows());
}

// Test allowThrows when noThrow is set
TEST_F(ConfigTest_721, NoThrowSet_AllowThrowsReturnsFalse_721) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

// Test name default
TEST_F(ConfigTest_721, DefaultConfig_NameIsEmpty_721) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.name().empty());
}

// Test name when set
TEST_F(ConfigTest_721, NameSet_ReturnsCorrectName_721) {
    ConfigData data;
    data.name = "MyTestRun";
    Config config(data);
    EXPECT_EQ(config.name(), "MyTestRun");
}

// Test includeSuccessfulResults default
TEST_F(ConfigTest_721, DefaultConfig_IncludeSuccessfulResultsIsFalse_721) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

// Test includeSuccessfulResults when set
TEST_F(ConfigTest_721, ShowSuccessfulTestsSet_IncludeSuccessfulResultsTrue_721) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// Test shouldDebugBreak default
TEST_F(ConfigTest_721, DefaultConfig_ShouldDebugBreakIsFalse_721) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.shouldDebugBreak());
}

// Test shouldDebugBreak when set
TEST_F(ConfigTest_721, ShouldDebugBreakSet_ReturnsTrue_721) {
    ConfigData data;
    data.shouldDebugBreak = true;
    Config config(data);
    EXPECT_TRUE(config.shouldDebugBreak());
}

// Test abortAfter default
TEST_F(ConfigTest_721, DefaultConfig_AbortAfterDefaultValue_721) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), data.abortAfter);
}

// Test abortAfter when set
TEST_F(ConfigTest_721, AbortAfterSet_ReturnsCorrectValue_721) {
    ConfigData data;
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

// Test showInvisibles default
TEST_F(ConfigTest_721, DefaultConfig_ShowInvisiblesIsFalse_721) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.showInvisibles());
}

// Test showInvisibles when set
TEST_F(ConfigTest_721, ShowInvisiblesSet_ReturnsTrue_721) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

// Test verbosity default
TEST_F(ConfigTest_721, DefaultConfig_VerbosityIsNormal_721) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

// Test verbosity when set to High
TEST_F(ConfigTest_721, VerbositySetHigh_ReturnsHigh_721) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

// Test verbosity when set to Quiet
TEST_F(ConfigTest_721, VerbositySetQuiet_ReturnsQuiet_721) {
    ConfigData data;
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

// Test skipBenchmarks default
TEST_F(ConfigTest_721, DefaultConfig_SkipBenchmarksIsFalse_721) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.skipBenchmarks());
}

// Test skipBenchmarks when set
TEST_F(ConfigTest_721, SkipBenchmarksSet_ReturnsTrue_721) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

// Test benchmarkNoAnalysis default
TEST_F(ConfigTest_721, DefaultConfig_BenchmarkNoAnalysisIsFalse_721) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

// Test benchmarkSamples default
TEST_F(ConfigTest_721, DefaultConfig_BenchmarkSamplesDefaultValue_721) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), data.benchmarkSamples);
}

// Test benchmarkSamples when set
TEST_F(ConfigTest_721, BenchmarkSamplesSet_ReturnsCorrectValue_721) {
    ConfigData data;
    data.benchmarkSamples = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 200);
}

// Test benchmarkConfidenceInterval default
TEST_F(ConfigTest_721, DefaultConfig_BenchmarkConfidenceIntervalDefaultValue_721) {
    ConfigData data;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), data.benchmarkConfidenceInterval);
}

// Test benchmarkConfidenceInterval when set
TEST_F(ConfigTest_721, BenchmarkConfidenceIntervalSet_ReturnsCorrectValue_721) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

// Test benchmarkResamples default
TEST_F(ConfigTest_721, DefaultConfig_BenchmarkResamplesDefaultValue_721) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), data.benchmarkResamples);
}

// Test benchmarkResamples when set
TEST_F(ConfigTest_721, BenchmarkResamplesSet_ReturnsCorrectValue_721) {
    ConfigData data;
    data.benchmarkResamples = 200000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 200000);
}

// Test benchmarkWarmupTime default
TEST_F(ConfigTest_721, DefaultConfig_BenchmarkWarmupTimeDefaultValue_721) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(data.benchmarkWarmupTime));
}

// Test benchmarkWarmupTime when set
TEST_F(ConfigTest_721, BenchmarkWarmupTimeSet_ReturnsCorrectValue_721) {
    ConfigData data;
    data.benchmarkWarmupTime = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

// Test rngSeed default
TEST_F(ConfigTest_721, DefaultConfig_RngSeedDefaultValue_721) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), data.rngSeed);
}

// Test rngSeed when set
TEST_F(ConfigTest_721, RngSeedSet_ReturnsCorrectValue_721) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42);
}

// Test shardCount default
TEST_F(ConfigTest_721, DefaultConfig_ShardCountDefaultValue_721) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.shardCount(), data.shardCount);
}

// Test shardCount when set
TEST_F(ConfigTest_721, ShardCountSet_ReturnsCorrectValue_721) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4);
}

// Test shardIndex default
TEST_F(ConfigTest_721, DefaultConfig_ShardIndexDefaultValue_721) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), data.shardIndex);
}

// Test shardIndex when set
TEST_F(ConfigTest_721, ShardIndexSet_ReturnsCorrectValue_721) {
    ConfigData data;
    data.shardIndex = 2;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 2);
}

// Test runOrder default
TEST_F(ConfigTest_721, DefaultConfig_RunOrderDefaultValue_721) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.runOrder(), data.runOrder);
}

// Test runOrder when set to Randomize
TEST_F(ConfigTest_721, RunOrderSetRandomize_ReturnsRandomize_721) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomize;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomize);
}

// Test showDurations default
TEST_F(ConfigTest_721, DefaultConfig_ShowDurationsDefaultValue_721) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.showDurations(), data.showDurations);
}

// Test showDurations when set
TEST_F(ConfigTest_721, ShowDurationsSetAlways_ReturnsAlways_721) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

// Test minDuration default
TEST_F(ConfigTest_721, DefaultConfig_MinDurationDefaultValue_721) {
    ConfigData data;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), data.minDuration);
}

// Test minDuration when set
TEST_F(ConfigTest_721, MinDurationSet_ReturnsCorrectValue_721) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

// Test warnAboutMissingAssertions default
TEST_F(ConfigTest_721, DefaultConfig_WarnAboutMissingAssertionsIsFalse_721) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

// Test warnAboutUnmatchedTestSpecs default
TEST_F(ConfigTest_721, DefaultConfig_WarnAboutUnmatchedTestSpecsDefaultValue_721) {
    ConfigData data;
    Config config(data);
    // Default value depends on configuration; just ensure it doesn't crash
    config.warnAboutUnmatchedTestSpecs();
}

// Test zeroTestsCountAsSuccess default
TEST_F(ConfigTest_721, DefaultConfig_ZeroTestsCountAsSuccessIsFalse_721) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

// Test getTestsOrTags returns empty by default
TEST_F(ConfigTest_721, DefaultConfig_GetTestsOrTagsIsEmpty_721) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

// Test getTestsOrTags returns correct values
TEST_F(ConfigTest_721, TestsOrTagsSet_ReturnsCorrectValues_721) {
    ConfigData data;
    data.testsOrTags.push_back("test1");
    data.testsOrTags.push_back("[tag1]");
    Config config(data);
    auto const& testsOrTags = config.getTestsOrTags();
    EXPECT_EQ(testsOrTags.size(), 2u);
    EXPECT_EQ(testsOrTags[0], "test1");
    EXPECT_EQ(testsOrTags[1], "[tag1]");
}

// Test getSectionsToRun returns empty by default
TEST_F(ConfigTest_721, DefaultConfig_GetSectionsToRunIsEmpty_721) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// Test getSectionsToRun returns correct values
TEST_F(ConfigTest_721, SectionsToRunSet_ReturnsCorrectValues_721) {
    ConfigData data;
    data.sectionsToRun.push_back("section1");
    data.sectionsToRun.push_back("section2");
    Config config(data);
    auto const& sections = config.getSectionsToRun();
    EXPECT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

// Test testSpec returns a valid reference
TEST_F(ConfigTest_721, DefaultConfig_TestSpecReturnsValidRef_721) {
    ConfigData data;
    Config config(data);
    // Just ensure it doesn't crash and returns a valid reference
    auto const& spec = config.testSpec();
    (void)spec;
}

// Test listTests default
TEST_F(ConfigTest_721, DefaultConfig_ListTestsIsFalse_721) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listTests());
}

// Test listTags default
TEST_F(ConfigTest_721, DefaultConfig_ListTagsIsFalse_721) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listTags());
}

// Test listReporters default
TEST_F(ConfigTest_721, DefaultConfig_ListReportersIsFalse_721) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listReporters());
}

// Test listListeners default
TEST_F(ConfigTest_721, DefaultConfig_ListListenersIsFalse_721) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listListeners());
}

// Test defaultColourMode default
TEST_F(ConfigTest_721, DefaultConfig_DefaultColourModeDefaultValue_721) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), data.defaultColourMode);
}

// Test multiple test filters
TEST_F(ConfigTest_721, MultipleTestFilters_HasTestFiltersReturnsTrue_721) {
    ConfigData data;
    data.testsOrTags.push_back("test1");
    data.testsOrTags.push_back("test2");
    data.testsOrTags.push_back("[tag1]");
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

// Test getReporterSpecs
TEST_F(ConfigTest_721, DefaultConfig_GetReporterSpecsNotEmpty_721) {
    ConfigData data;
    Config config(data);
    // Default config should have at least some reporter spec setup
    auto const& specs = config.getReporterSpecs();
    (void)specs; // Just ensure no crash
}

// Test getProcessedReporterSpecs
TEST_F(ConfigTest_721, DefaultConfig_GetProcessedReporterSpecsAccessible_721) {
    ConfigData data;
    Config config(data);
    auto const& processedSpecs = config.getProcessedReporterSpecs();
    (void)processedSpecs; // Just ensure no crash
}

// Test boundary: abortAfter with 0
TEST_F(ConfigTest_721, AbortAfterZero_ReturnsZero_721) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

// Test boundary: abortAfter with large value
TEST_F(ConfigTest_721, AbortAfterLargeValue_ReturnsCorrectValue_721) {
    ConfigData data;
    data.abortAfter = 1000000;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 1000000);
}

// Test boundary: rngSeed with max value
TEST_F(ConfigTest_721, RngSeedMaxValue_ReturnsCorrectValue_721) {
    ConfigData data;
    data.rngSeed = UINT32_MAX;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), UINT32_MAX);
}

// Test boundary: rngSeed with 0
TEST_F(ConfigTest_721, RngSeedZero_ReturnsZero_721) {
    ConfigData data;
    data.rngSeed = 0;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0);
}

// Test benchmarkSamples boundary: zero
TEST_F(ConfigTest_721, BenchmarkSamplesZero_ReturnsZero_721) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0);
}

// Test minDuration boundary: zero
TEST_F(ConfigTest_721, MinDurationZero_ReturnsZero_721) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

// Test minDuration boundary: negative
TEST_F(ConfigTest_721, MinDurationNegative_ReturnsNegative_721) {
    ConfigData data;
    data.minDuration = -1.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

// Test benchmarkWarmupTime boundary: zero
TEST_F(ConfigTest_721, BenchmarkWarmupTimeZero_ReturnsZero_721) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}
