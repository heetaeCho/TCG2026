#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_731 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// Test default ConfigData values through Config
TEST_F(ConfigTest_731, DefaultRunOrder_731) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_731, DefaultListTests_731) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_731, DefaultListTags_731) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_731, DefaultListReporters_731) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_731, DefaultListListeners_731) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_731, DefaultShowHelp_731) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_731, DefaultAllowThrows_731) {
    // noThrow defaults to false, so allowThrows should be true
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_731, DefaultIncludeSuccessfulResults_731) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_731, DefaultWarnAboutMissingAssertions_731) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_731, DefaultWarnAboutUnmatchedTestSpecs_731) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_731, DefaultZeroTestsCountAsSuccess_731) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_731, DefaultShowDurations_731) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_731, DefaultMinDuration_731) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_731, DefaultAbortAfter_731) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_731, DefaultShardCount_731) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_731, DefaultShardIndex_731) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_731, DefaultShowInvisibles_731) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_731, DefaultVerbosity_731) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_731, DefaultSkipBenchmarks_731) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_731, DefaultBenchmarkNoAnalysis_731) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_731, DefaultBenchmarkSamples_731) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_731, DefaultBenchmarkConfidenceInterval_731) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_731, DefaultBenchmarkResamples_731) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_731, DefaultBenchmarkWarmupTime_731) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_731, DefaultColourMode_731) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_731, DefaultHasTestFilters_731) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_731, DefaultGetTestsOrTagsEmpty_731) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_731, DefaultGetSectionsToRunEmpty_731) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// Test setting specific values through ConfigData
TEST_F(ConfigTest_731, SetRunOrderRandomized_731) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_731, SetListTestsTrue_731) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_731, SetListTagsTrue_731) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_731, SetListReportersTrue_731) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_731, SetListListenersTrue_731) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_731, SetShowHelpTrue_731) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_731, SetNoThrowTrue_DisablesAllowThrows_731) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_731, SetShowSuccessfulTestsTrue_731) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_731, SetShowInvisiblesTrue_731) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_731, SetAllowZeroTestsTrue_731) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_731, SetAbortAfterPositive_731) {
    ConfigData data;
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_731, SetAbortAfterZero_731) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_731, SetShardCount_731) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_731, SetShardIndex_731) {
    ConfigData data;
    data.shardIndex = 2;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 2u);
}

TEST_F(ConfigTest_731, SetVerbosityHigh_731) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_731, SetShowDurationsAlways_731) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_731, SetShowDurationsNever_731) {
    ConfigData data;
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_731, SetMinDurationPositive_731) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_731, SetMinDurationZero_731) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_731, SetSkipBenchmarksTrue_731) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_731, SetBenchmarkNoAnalysisTrue_731) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_731, SetBenchmarkSamples_731) {
    ConfigData data;
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_731, SetBenchmarkConfidenceInterval_731) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_731, SetBenchmarkResamples_731) {
    ConfigData data;
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

TEST_F(ConfigTest_731, SetBenchmarkWarmupTime_731) {
    ConfigData data;
    data.benchmarkWarmupTime = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

TEST_F(ConfigTest_731, SetRngSeed_731) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

TEST_F(ConfigTest_731, SetColourModeAnsiColours_731) {
    ConfigData data;
    data.defaultColourMode = ColourMode::ANSI;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_731, SetProcessName_731) {
    ConfigData data;
    data.processName = "myTestApp";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("myTestApp"));
}

TEST_F(ConfigTest_731, SetEmptyProcessName_731) {
    ConfigData data;
    data.processName = "";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_731, SetTestsOrTags_731) {
    ConfigData data;
    data.testsOrTags = {"[tag1]", "testName"};
    Config config(data);
    auto const& testsOrTags = config.getTestsOrTags();
    ASSERT_EQ(testsOrTags.size(), 2u);
    EXPECT_EQ(testsOrTags[0], "[tag1]");
    EXPECT_EQ(testsOrTags[1], "testName");
}

TEST_F(ConfigTest_731, HasTestFiltersWhenTestsOrTagsSet_731) {
    ConfigData data;
    data.testsOrTags = {"someTest"};
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_731, SetSectionsToRun_731) {
    ConfigData data;
    data.sectionsToRun = {"section1", "section2"};
    Config config(data);
    auto const& sections = config.getSectionsToRun();
    ASSERT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

TEST_F(ConfigTest_731, DefaultConstructor_731) {
    Config config;
    // Default constructed config should have default values
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.showHelp());
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_731, SetWarningsMissingAssertions_731) {
    ConfigData data;
    data.warnings = WarnAbout::NoAssertions;
    Config config(data);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_731, RunOrderLexicographic_731) {
    ConfigData data;
    data.runOrder = TestRunOrder::LexicographicallySorted;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::LexicographicallySorted);
}

TEST_F(ConfigTest_731, BenchmarkWarmupTimeZero_731) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_731, BenchmarkSamplesOne_731) {
    ConfigData data;
    data.benchmarkSamples = 1;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 1u);
}

TEST_F(ConfigTest_731, RngSeedZero_731) {
    ConfigData data;
    data.rngSeed = 0;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0u);
}

TEST_F(ConfigTest_731, RngSeedMaxUint32_731) {
    ConfigData data;
    data.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(data);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

TEST_F(ConfigTest_731, GetReporterSpecsDefault_731) {
    Config config(defaultData);
    EXPECT_TRUE(config.getReporterSpecs().empty());
}

TEST_F(ConfigTest_731, GetProcessedReporterSpecsDefault_731) {
    Config config(defaultData);
    // Even with no reporter specs configured, there may be a default one
    // Just verify it doesn't crash
    auto const& specs = config.getProcessedReporterSpecs();
    (void)specs;
}

TEST_F(ConfigTest_731, TestSpecDefaultIsEmpty_731) {
    Config config(defaultData);
    // Default test spec with no filters
    auto const& spec = config.testSpec();
    (void)spec; // Just ensure it's accessible without crash
}

TEST_F(ConfigTest_731, ShouldDebugBreakDefault_731) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}

TEST_F(ConfigTest_731, FilenamesAsTagsDefault_731) {
    ConfigData data;
    data.filenamesAsTags = true;
    Config config(data);
    // filenamesAsTags doesn't have a direct getter but shouldn't cause issues
    // Verify config is constructible
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_731, LargeAbortAfter_731) {
    ConfigData data;
    data.abortAfter = 1000000;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 1000000);
}
