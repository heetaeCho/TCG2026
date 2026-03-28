#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_725 : public ::testing::Test {
protected:
    ConfigData makeDefaultData() {
        ConfigData data;
        return data;
    }
};

// Test default construction values
TEST_F(ConfigTest_725, DefaultConfig_ListTestsIsFalse_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_725, DefaultConfig_ListTagsIsFalse_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_725, DefaultConfig_ListReportersIsFalse_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_725, DefaultConfig_ListListenersIsFalse_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_725, DefaultConfig_ShowSuccessfulTestsIsFalse_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_725, DefaultConfig_AllowThrowsIsTrue_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    // noThrow defaults to false, so allowThrows should be true
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_725, DefaultConfig_ShowHelpIsFalse_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_725, DefaultConfig_ShowInvisiblesIsFalse_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_725, DefaultConfig_SkipBenchmarksIsFalse_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_725, DefaultConfig_BenchmarkNoAnalysisIsFalse_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_725, DefaultConfig_AbortAfterIsNegativeOne_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_725, DefaultConfig_ShardCountIsOne_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_725, DefaultConfig_ShardIndexIsZero_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_725, DefaultConfig_BenchmarkSamplesIs100_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_725, DefaultConfig_BenchmarkConfidenceInterval_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_725, DefaultConfig_BenchmarkResamples_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_725, DefaultConfig_BenchmarkWarmupTime_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_725, DefaultConfig_VerbosityIsNormal_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_725, DefaultConfig_ShowDurationsIsDefault_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_725, DefaultConfig_MinDurationIsNegativeOne_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_725, DefaultConfig_RunOrderIsDeclared_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_725, DefaultConfig_DefaultColourMode_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_725, DefaultConfig_ZeroTestsCountAsSuccessIsFalse_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_725, DefaultConfig_HasTestFiltersIsFalse_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_725, DefaultConfig_GetTestsOrTagsIsEmpty_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_725, DefaultConfig_GetSectionsToRunIsEmpty_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// Test setting specific values
TEST_F(ConfigTest_725, SetListTestsTrue_725) {
    ConfigData data = makeDefaultData();
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_725, SetListTagsTrue_725) {
    ConfigData data = makeDefaultData();
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_725, SetListReportersTrue_725) {
    ConfigData data = makeDefaultData();
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_725, SetListListenersTrue_725) {
    ConfigData data = makeDefaultData();
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_725, SetShowSuccessfulTestsTrue_725) {
    ConfigData data = makeDefaultData();
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_725, SetNoThrowTrue_AllowThrowsReturnsFalse_725) {
    ConfigData data = makeDefaultData();
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_725, SetShowHelpTrue_725) {
    ConfigData data = makeDefaultData();
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_725, SetShowInvisiblesTrue_725) {
    ConfigData data = makeDefaultData();
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_725, SetSkipBenchmarksTrue_725) {
    ConfigData data = makeDefaultData();
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_725, SetBenchmarkNoAnalysisTrue_725) {
    ConfigData data = makeDefaultData();
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_725, SetAllowZeroTestsTrue_725) {
    ConfigData data = makeDefaultData();
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_725, SetAbortAfterToPositiveValue_725) {
    ConfigData data = makeDefaultData();
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_725, SetAbortAfterToZero_725) {
    ConfigData data = makeDefaultData();
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_725, SetShardCount_725) {
    ConfigData data = makeDefaultData();
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_725, SetShardIndex_725) {
    ConfigData data = makeDefaultData();
    data.shardCount = 4;
    data.shardIndex = 3;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 3u);
}

TEST_F(ConfigTest_725, SetBenchmarkSamples_725) {
    ConfigData data = makeDefaultData();
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_725, SetBenchmarkConfidenceInterval_725) {
    ConfigData data = makeDefaultData();
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_725, SetBenchmarkResamples_725) {
    ConfigData data = makeDefaultData();
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

TEST_F(ConfigTest_725, SetBenchmarkWarmupTime_725) {
    ConfigData data = makeDefaultData();
    data.benchmarkWarmupTime = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

TEST_F(ConfigTest_725, SetVerbosityHigh_725) {
    ConfigData data = makeDefaultData();
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_725, SetVerbosityQuiet_725) {
    ConfigData data = makeDefaultData();
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_725, SetShowDurationsAlways_725) {
    ConfigData data = makeDefaultData();
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_725, SetShowDurationsNever_725) {
    ConfigData data = makeDefaultData();
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_725, SetMinDurationPositive_725) {
    ConfigData data = makeDefaultData();
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_725, SetRunOrderRandomized_725) {
    ConfigData data = makeDefaultData();
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_725, SetRngSeed_725) {
    ConfigData data = makeDefaultData();
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

TEST_F(ConfigTest_725, SetProcessName_725) {
    ConfigData data = makeDefaultData();
    data.processName = "test_process";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("test_process"));
}

TEST_F(ConfigTest_725, EmptyProcessName_725) {
    ConfigData data = makeDefaultData();
    data.processName = "";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_725, SetTestsOrTags_HasTestFilters_725) {
    ConfigData data = makeDefaultData();
    data.testsOrTags.push_back("test1");
    data.testsOrTags.push_back("[tag1]");
    Config config(data);
    auto const& testsOrTags = config.getTestsOrTags();
    EXPECT_EQ(testsOrTags.size(), 2u);
    EXPECT_EQ(testsOrTags[0], "test1");
    EXPECT_EQ(testsOrTags[1], "[tag1]");
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_725, SetSectionsToRun_725) {
    ConfigData data = makeDefaultData();
    data.sectionsToRun.push_back("section1");
    data.sectionsToRun.push_back("section2");
    Config config(data);
    auto const& sections = config.getSectionsToRun();
    EXPECT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

TEST_F(ConfigTest_725, WarnAboutMissingAssertions_DefaultIsFalse_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_725, WarnAboutUnmatchedTestSpecs_DefaultIsFalse_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_725, ShouldDebugBreak_DefaultIsFalse_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.shouldDebugBreak());
}

// Boundary tests
TEST_F(ConfigTest_725, BenchmarkSamplesZero_725) {
    ConfigData data = makeDefaultData();
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

TEST_F(ConfigTest_725, BenchmarkResamplesZero_725) {
    ConfigData data = makeDefaultData();
    data.benchmarkResamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

TEST_F(ConfigTest_725, BenchmarkWarmupTimeZero_725) {
    ConfigData data = makeDefaultData();
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_725, MinDurationZero_725) {
    ConfigData data = makeDefaultData();
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_725, RngSeedMaxValue_725) {
    ConfigData data = makeDefaultData();
    data.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(data);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

TEST_F(ConfigTest_725, RngSeedZero_725) {
    ConfigData data = makeDefaultData();
    data.rngSeed = 0;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0u);
}

TEST_F(ConfigTest_725, LargeAbortAfterValue_725) {
    ConfigData data = makeDefaultData();
    data.abortAfter = 1000000;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 1000000);
}

TEST_F(ConfigTest_725, TestSpecReturnsSomething_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    // Just verify testSpec() doesn't crash and returns a reference
    auto const& spec = config.testSpec();
    (void)spec;
}

TEST_F(ConfigTest_725, GetReporterSpecsDefault_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    auto const& specs = config.getReporterSpecs();
    // Default should have no reporter specifications set by user
    // (though implementation may add defaults)
    (void)specs;
}

TEST_F(ConfigTest_725, GetProcessedReporterSpecsDefault_725) {
    ConfigData data = makeDefaultData();
    Config config(data);
    auto const& processed = config.getProcessedReporterSpecs();
    (void)processed;
}

TEST_F(ConfigTest_725, ColourModeAnsiEscape_725) {
    ConfigData data = makeDefaultData();
    data.defaultColourMode = ColourMode::ANSI;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_725, ColourModeNone_725) {
    ConfigData data = makeDefaultData();
    data.defaultColourMode = ColourMode::None;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::None);
}
