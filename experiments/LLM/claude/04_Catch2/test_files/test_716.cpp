#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_716 : public ::testing::Test {
protected:
    ConfigData makeDefaultData() {
        ConfigData data;
        return data;
    }
};

// Test default construction and default values
TEST_F(ConfigTest_716, DefaultConfigData_ListTestsIsFalse_716) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_716, DefaultConfigData_ListTagsIsFalse_716) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_716, DefaultConfigData_ListReportersIsFalse_716) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_716, DefaultConfigData_ListListenersIsFalse_716) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_716, DefaultConfigData_ShowHelpIsFalse_716) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_716, DefaultConfigData_AllowThrowsIsTrue_716) {
    // noThrow defaults to false, so allowThrows should be true
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_716, DefaultConfigData_IncludeSuccessfulResultsIsFalse_716) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_716, DefaultConfigData_ShowInvisiblesIsFalse_716) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_716, DefaultConfigData_VerbosityIsNormal_716) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_716, DefaultConfigData_AbortAfterIsNegativeOne_716) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_716, DefaultConfigData_ShardCountIsOne_716) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_716, DefaultConfigData_ShardIndexIsZero_716) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_716, DefaultConfigData_SkipBenchmarksIsFalse_716) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_716, DefaultConfigData_BenchmarkNoAnalysisIsFalse_716) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_716, DefaultConfigData_BenchmarkSamplesIs100_716) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_716, DefaultConfigData_BenchmarkConfidenceInterval_716) {
    ConfigData data;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_716, DefaultConfigData_BenchmarkResamplesIs100000_716) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_716, DefaultConfigData_BenchmarkWarmupTime_716) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_716, DefaultConfigData_RunOrderIsDeclared_716) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_716, DefaultConfigData_DefaultColourMode_716) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_716, DefaultConfigData_MinDurationIsNegativeOne_716) {
    ConfigData data;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_716, DefaultConfigData_ShowDurationsIsDefault_716) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_716, DefaultConfigData_ZeroTestsCountAsSuccessIsFalse_716) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

// Test setting various ConfigData fields

TEST_F(ConfigTest_716, SetListTestsTrue_716) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_716, SetListTagsTrue_716) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_716, SetListReportersTrue_716) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_716, SetListListenersTrue_716) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_716, SetShowHelpTrue_716) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_716, SetNoThrowTrue_AllowThrowsReturnsFalse_716) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_716, SetShowSuccessfulTestsTrue_716) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_716, SetShowInvisiblesTrue_716) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_716, SetVerbosityHigh_716) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_716, SetAbortAfterValue_716) {
    ConfigData data;
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_716, SetSkipBenchmarksTrue_716) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_716, SetBenchmarkNoAnalysisTrue_716) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_716, SetBenchmarkSamples_716) {
    ConfigData data;
    data.benchmarkSamples = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 200u);
}

TEST_F(ConfigTest_716, SetBenchmarkConfidenceInterval_716) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_716, SetBenchmarkResamples_716) {
    ConfigData data;
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

TEST_F(ConfigTest_716, SetBenchmarkWarmupTime_716) {
    ConfigData data;
    data.benchmarkWarmupTime = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

TEST_F(ConfigTest_716, SetRunOrderRandomize_716) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_716, SetShardCount_716) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_716, SetShardIndex_716) {
    ConfigData data;
    data.shardIndex = 2;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 2u);
}

TEST_F(ConfigTest_716, SetAllowZeroTestsTrue_716) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_716, SetMinDuration_716) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

// Test getTestsOrTags

TEST_F(ConfigTest_716, GetTestsOrTags_EmptyByDefault_716) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_716, GetTestsOrTags_ReturnsConfiguredValues_716) {
    ConfigData data;
    data.testsOrTags.push_back("test1");
    data.testsOrTags.push_back("[tag1]");
    Config config(data);
    auto const& result = config.getTestsOrTags();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "test1");
    EXPECT_EQ(result[1], "[tag1]");
}

TEST_F(ConfigTest_716, GetTestsOrTags_SingleEntry_716) {
    ConfigData data;
    data.testsOrTags.push_back("singleTest");
    Config config(data);
    auto const& result = config.getTestsOrTags();
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], "singleTest");
}

// Test getSectionsToRun

TEST_F(ConfigTest_716, GetSectionsToRun_EmptyByDefault_716) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

TEST_F(ConfigTest_716, GetSectionsToRun_ReturnsConfiguredValues_716) {
    ConfigData data;
    data.sectionsToRun.push_back("section1");
    data.sectionsToRun.push_back("section2");
    Config config(data);
    auto const& result = config.getSectionsToRun();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "section1");
    EXPECT_EQ(result[1], "section2");
}

// Test hasTestFilters

TEST_F(ConfigTest_716, HasTestFilters_FalseWhenNoTestsOrTags_716) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_716, HasTestFilters_TrueWhenTestsOrTagsSet_716) {
    ConfigData data;
    data.testsOrTags.push_back("someTest");
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

// Test name

TEST_F(ConfigTest_716, Name_EmptyWhenNoProcessName_716) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.name().empty());
}

TEST_F(ConfigTest_716, Name_ReturnsProcessName_716) {
    ConfigData data;
    data.processName = "myApp";
    Config config(data);
    EXPECT_EQ(config.name(), "myApp");
}

// Test rngSeed

TEST_F(ConfigTest_716, RngSeed_ReturnsConfiguredValue_716) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// Test warnings

TEST_F(ConfigTest_716, WarnAboutMissingAssertions_DefaultIsFalse_716) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_716, WarnAboutUnmatchedTestSpecs_DefaultIsFalse_716) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

// Test shouldDebugBreak

TEST_F(ConfigTest_716, ShouldDebugBreak_DefaultIsFalse_716) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.shouldDebugBreak());
}

// Test with multiple testsOrTags entries

TEST_F(ConfigTest_716, GetTestsOrTags_MultipleEntries_716) {
    ConfigData data;
    data.testsOrTags.push_back("test1");
    data.testsOrTags.push_back("test2");
    data.testsOrTags.push_back("[tag1]");
    data.testsOrTags.push_back("[tag2]");
    Config config(data);
    auto const& result = config.getTestsOrTags();
    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], "test1");
    EXPECT_EQ(result[1], "test2");
    EXPECT_EQ(result[2], "[tag1]");
    EXPECT_EQ(result[3], "[tag2]");
}

// Test boundary: abortAfter = 0

TEST_F(ConfigTest_716, AbortAfterZero_716) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

// Test boundary: minDuration = 0

TEST_F(ConfigTest_716, MinDurationZero_716) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

// Test boundary: benchmarkSamples = 0

TEST_F(ConfigTest_716, BenchmarkSamplesZero_716) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

// Test boundary: benchmarkWarmupTime = 0

TEST_F(ConfigTest_716, BenchmarkWarmupTimeZero_716) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

// Test ColourMode set to specific value

TEST_F(ConfigTest_716, SetColourModeAnsi_716) {
    ConfigData data;
    data.defaultColourMode = ColourMode::ANSI;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

// Test ShowDurations set to Always

TEST_F(ConfigTest_716, SetShowDurationsAlways_716) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

// Test ShowDurations set to Never

TEST_F(ConfigTest_716, SetShowDurationsNever_716) {
    ConfigData data;
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

// Test testSpec returns a valid reference

TEST_F(ConfigTest_716, TestSpec_ReturnsValidReference_716) {
    ConfigData data;
    Config config(data);
    // Just verify we can call testSpec without crashing
    auto const& spec = config.testSpec();
    // With no test filters, the spec should match everything or be empty
    (void)spec;
}

// Test getReporterSpecs

TEST_F(ConfigTest_716, GetReporterSpecs_EmptyByDefault_716) {
    ConfigData data;
    Config config(data);
    // reporterSpecifications is empty by default
    auto const& specs = config.getReporterSpecs();
    EXPECT_TRUE(specs.empty());
}

// Test Verbosity::Quiet

TEST_F(ConfigTest_716, SetVerbosityQuiet_716) {
    ConfigData data;
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

// Test large shard values

TEST_F(ConfigTest_716, LargeShardCount_716) {
    ConfigData data;
    data.shardCount = 1000;
    data.shardIndex = 999;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 1000u);
    EXPECT_EQ(config.shardIndex(), 999u);
}

// Test rngSeed boundary

TEST_F(ConfigTest_716, RngSeedMaxValue_716) {
    ConfigData data;
    data.rngSeed = UINT32_MAX;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), UINT32_MAX);
}

TEST_F(ConfigTest_716, RngSeedZero_716) {
    ConfigData data;
    data.rngSeed = 0;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0u);
}
