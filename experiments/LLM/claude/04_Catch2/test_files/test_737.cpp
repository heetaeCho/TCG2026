#include "catch2/catch_config.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace Catch;

class ConfigTest_737 : public ::testing::Test {
protected:
    ConfigData makeDefaultData() {
        ConfigData data;
        return data;
    }
};

// ==================== Default Construction Tests ====================

TEST_F(ConfigTest_737, DefaultConfig_AbortAfterIsNegativeOne_737) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_737, DefaultConfig_ListTestsIsFalse_737) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_737, DefaultConfig_ListTagsIsFalse_737) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_737, DefaultConfig_ListReportersIsFalse_737) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_737, DefaultConfig_ListListenersIsFalse_737) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_737, DefaultConfig_ShowHelpIsFalse_737) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_737, DefaultConfig_AllowThrowsIsTrue_737) {
    // noThrow defaults to false, so allowThrows should be true
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_737, DefaultConfig_IncludeSuccessfulResultsIsFalse_737) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_737, DefaultConfig_ShowInvisiblesIsFalse_737) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_737, DefaultConfig_VerbosityIsNormal_737) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_737, DefaultConfig_ShardCountIsOne_737) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_737, DefaultConfig_ShardIndexIsZero_737) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_737, DefaultConfig_SkipBenchmarksIsFalse_737) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_737, DefaultConfig_BenchmarkNoAnalysisIsFalse_737) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_737, DefaultConfig_BenchmarkSamplesIs100_737) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_737, DefaultConfig_BenchmarkConfidenceInterval_737) {
    ConfigData data;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_737, DefaultConfig_BenchmarkResamplesIs100000_737) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_737, DefaultConfig_BenchmarkWarmupTimeIs100ms_737) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_737, DefaultConfig_ShowDurationsIsDefault_737) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_737, DefaultConfig_MinDurationIsNegativeOne_737) {
    ConfigData data;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_737, DefaultConfig_RunOrderIsDeclared_737) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_737, DefaultConfig_DefaultColourModeIsPlatformDefault_737) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_737, DefaultConfig_HasTestFiltersIsFalse_737) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_737, DefaultConfig_ZeroTestsCountAsSuccessIsFalse_737) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_737, DefaultConfig_WarnAboutMissingAssertionsIsFalse_737) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_737, DefaultConfig_WarnAboutUnmatchedTestSpecsIsFalse_737) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_737, DefaultConfig_GetTestsOrTagsIsEmpty_737) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_737, DefaultConfig_GetSectionsToRunIsEmpty_737) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// ==================== Custom Configuration Tests ====================

TEST_F(ConfigTest_737, CustomAbortAfter_737) {
    ConfigData data;
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_737, CustomAbortAfterZero_737) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_737, CustomListTestsTrue_737) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_737, CustomListTagsTrue_737) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_737, CustomListReportersTrue_737) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_737, CustomListListenersTrue_737) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_737, CustomShowHelpTrue_737) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_737, CustomNoThrowTrue_AllowThrowsFalse_737) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_737, CustomShowSuccessfulTestsTrue_737) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_737, CustomShowInvisiblesTrue_737) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_737, CustomVerbosityHigh_737) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_737, CustomVerbosityQuiet_737) {
    ConfigData data;
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_737, CustomShardCount_737) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_737, CustomShardIndex_737) {
    ConfigData data;
    data.shardIndex = 3;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 3u);
}

TEST_F(ConfigTest_737, CustomSkipBenchmarksTrue_737) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_737, CustomBenchmarkNoAnalysisTrue_737) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_737, CustomBenchmarkSamples_737) {
    ConfigData data;
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_737, CustomBenchmarkConfidenceInterval_737) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_737, CustomBenchmarkResamples_737) {
    ConfigData data;
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

TEST_F(ConfigTest_737, CustomBenchmarkWarmupTime_737) {
    ConfigData data;
    data.benchmarkWarmupTime = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

TEST_F(ConfigTest_737, CustomShowDurationsAlways_737) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_737, CustomShowDurationsNever_737) {
    ConfigData data;
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_737, CustomMinDuration_737) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_737, CustomRunOrderRandomized_737) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_737, CustomDefaultColourModeAnsiColours_737) {
    ConfigData data;
    data.defaultColourMode = ColourMode::ANSI;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_737, CustomAllowZeroTestsTrue_737) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_737, CustomProcessName_737) {
    ConfigData data;
    data.processName = "myTestProcess";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

TEST_F(ConfigTest_737, EmptyProcessName_737) {
    ConfigData data;
    data.processName = "";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_737, CustomTestsOrTags_737) {
    ConfigData data;
    data.testsOrTags = {"[tag1]", "testName"};
    Config config(data);
    const auto& testsOrTags = config.getTestsOrTags();
    ASSERT_EQ(testsOrTags.size(), 2u);
    EXPECT_EQ(testsOrTags[0], "[tag1]");
    EXPECT_EQ(testsOrTags[1], "testName");
}

TEST_F(ConfigTest_737, CustomTestsOrTags_HasTestFilters_737) {
    ConfigData data;
    data.testsOrTags = {"someTest"};
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_737, CustomSectionsToRun_737) {
    ConfigData data;
    data.sectionsToRun = {"section1", "section2"};
    Config config(data);
    const auto& sections = config.getSectionsToRun();
    ASSERT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

TEST_F(ConfigTest_737, CustomRngSeed_737) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// ==================== Boundary Condition Tests ====================

TEST_F(ConfigTest_737, AbortAfterMaxInt_737) {
    ConfigData data;
    data.abortAfter = std::numeric_limits<int>::max();
    Config config(data);
    EXPECT_EQ(config.abortAfter(), std::numeric_limits<int>::max());
}

TEST_F(ConfigTest_737, AbortAfterLargeNegative_737) {
    ConfigData data;
    data.abortAfter = std::numeric_limits<int>::min();
    Config config(data);
    EXPECT_EQ(config.abortAfter(), std::numeric_limits<int>::min());
}

TEST_F(ConfigTest_737, ShardCountMax_737) {
    ConfigData data;
    data.shardCount = std::numeric_limits<unsigned int>::max();
    Config config(data);
    EXPECT_EQ(config.shardCount(), std::numeric_limits<unsigned int>::max());
}

TEST_F(ConfigTest_737, BenchmarkSamplesZero_737) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

TEST_F(ConfigTest_737, BenchmarkConfidenceIntervalZero_737) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_737, BenchmarkConfidenceIntervalOne_737) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 1.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

TEST_F(ConfigTest_737, BenchmarkWarmupTimeZero_737) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_737, MinDurationZero_737) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_737, RngSeedZero_737) {
    ConfigData data;
    data.rngSeed = 0;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0u);
}

TEST_F(ConfigTest_737, RngSeedMax_737) {
    ConfigData data;
    data.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(data);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

// ==================== Multiple Fields Set Tests ====================

TEST_F(ConfigTest_737, MultipleFieldsSet_737) {
    ConfigData data;
    data.abortAfter = 3;
    data.showHelp = true;
    data.noThrow = true;
    data.showInvisibles = true;
    data.verbosity = Verbosity::High;
    data.shardCount = 2;
    data.shardIndex = 1;
    data.processName = "multiTest";

    Config config(data);

    EXPECT_EQ(config.abortAfter(), 3);
    EXPECT_TRUE(config.showHelp());
    EXPECT_FALSE(config.allowThrows());
    EXPECT_TRUE(config.showInvisibles());
    EXPECT_EQ(config.verbosity(), Verbosity::High);
    EXPECT_EQ(config.shardCount(), 2u);
    EXPECT_EQ(config.shardIndex(), 1u);
    EXPECT_EQ(config.name(), StringRef("multiTest"));
}

TEST_F(ConfigTest_737, EmptyTestsOrTagsNoFilters_737) {
    ConfigData data;
    data.testsOrTags = {};
    Config config(data);
    EXPECT_FALSE(config.hasTestFilters());
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_737, GetReporterSpecs_EmptyByDefault_737) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.getReporterSpecs().empty());
}

TEST_F(ConfigTest_737, ShouldDebugBreakDefaultFalse_737) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.shouldDebugBreak());
}
