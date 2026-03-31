#include "catch2/catch_config.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace Catch;

class ConfigTest_733 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// Test default construction values
TEST_F(ConfigTest_733, DefaultShardCount_733) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_733, DefaultShardIndex_733) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_733, DefaultListTests_733) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_733, DefaultListTags_733) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_733, DefaultListReporters_733) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_733, DefaultListListeners_733) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_733, DefaultShowHelp_733) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_733, DefaultAllowThrows_733) {
    Config config(defaultData);
    // noThrow defaults to false, so allowThrows should be true
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_733, DefaultIncludeSuccessfulResults_733) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_733, DefaultWarnAboutMissingAssertions_733) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_733, DefaultWarnAboutUnmatchedTestSpecs_733) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_733, DefaultZeroTestsCountAsSuccess_733) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_733, DefaultShowDurations_733) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_733, DefaultMinDuration_733) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_733, DefaultRunOrder_733) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_733, DefaultColourMode_733) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_733, DefaultAbortAfter_733) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_733, DefaultShowInvisibles_733) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_733, DefaultVerbosity_733) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_733, DefaultSkipBenchmarks_733) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_733, DefaultBenchmarkNoAnalysis_733) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_733, DefaultBenchmarkSamples_733) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_733, DefaultBenchmarkConfidenceInterval_733) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_733, DefaultBenchmarkResamples_733) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_733, DefaultBenchmarkWarmupTime_733) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_733, DefaultHasTestFilters_733) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_733, DefaultGetTestsOrTagsEmpty_733) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_733, DefaultGetSectionsToRunEmpty_733) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

TEST_F(ConfigTest_733, DefaultShouldDebugBreak_733) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}

// Test custom values through ConfigData
TEST_F(ConfigTest_733, CustomShardCount_733) {
    ConfigData data;
    data.shardCount = 5;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 5u);
}

TEST_F(ConfigTest_733, CustomShardIndex_733) {
    ConfigData data;
    data.shardIndex = 3;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 3u);
}

TEST_F(ConfigTest_733, CustomListTests_733) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_733, CustomListTags_733) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_733, CustomListReporters_733) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_733, CustomListListeners_733) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_733, CustomShowHelp_733) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_733, CustomNoThrow_733) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_733, CustomShowSuccessfulTests_733) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_733, CustomAllowZeroTests_733) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_733, CustomShowDurations_733) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_733, CustomMinDuration_733) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_733, CustomRunOrder_733) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_733, CustomAbortAfter_733) {
    ConfigData data;
    data.abortAfter = 3;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 3);
}

TEST_F(ConfigTest_733, CustomShowInvisibles_733) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_733, CustomVerbosity_733) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_733, CustomSkipBenchmarks_733) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_733, CustomBenchmarkNoAnalysis_733) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_733, CustomBenchmarkSamples_733) {
    ConfigData data;
    data.benchmarkSamples = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 200u);
}

TEST_F(ConfigTest_733, CustomBenchmarkConfidenceInterval_733) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_733, CustomBenchmarkResamples_733) {
    ConfigData data;
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

TEST_F(ConfigTest_733, CustomBenchmarkWarmupTime_733) {
    ConfigData data;
    data.benchmarkWarmupTime = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

TEST_F(ConfigTest_733, CustomProcessName_733) {
    ConfigData data;
    data.processName = "myTestProcess";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

TEST_F(ConfigTest_733, CustomTestsOrTags_733) {
    ConfigData data;
    data.testsOrTags = {"test1", "[tag1]"};
    Config config(data);
    auto const& testsOrTags = config.getTestsOrTags();
    EXPECT_EQ(testsOrTags.size(), 2u);
    EXPECT_EQ(testsOrTags[0], "test1");
    EXPECT_EQ(testsOrTags[1], "[tag1]");
}

TEST_F(ConfigTest_733, CustomSectionsToRun_733) {
    ConfigData data;
    data.sectionsToRun = {"section1", "section2"};
    Config config(data);
    auto const& sections = config.getSectionsToRun();
    EXPECT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

TEST_F(ConfigTest_733, HasTestFiltersWithTestSpecs_733) {
    ConfigData data;
    data.testsOrTags = {"someTest"};
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_733, ColourModeAnsiAlways_733) {
    ConfigData data;
    data.defaultColourMode = ColourMode::ANSI;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

// Boundary tests
TEST_F(ConfigTest_733, ShardCountZero_733) {
    ConfigData data;
    data.shardCount = 0;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 0u);
}

TEST_F(ConfigTest_733, ShardCountMax_733) {
    ConfigData data;
    data.shardCount = std::numeric_limits<unsigned int>::max();
    Config config(data);
    EXPECT_EQ(config.shardCount(), std::numeric_limits<unsigned int>::max());
}

TEST_F(ConfigTest_733, ShardIndexMax_733) {
    ConfigData data;
    data.shardIndex = std::numeric_limits<unsigned int>::max();
    Config config(data);
    EXPECT_EQ(config.shardIndex(), std::numeric_limits<unsigned int>::max());
}

TEST_F(ConfigTest_733, AbortAfterZero_733) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_733, MinDurationZero_733) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_733, BenchmarkSamplesZero_733) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

TEST_F(ConfigTest_733, BenchmarkResamplesZero_733) {
    ConfigData data;
    data.benchmarkResamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

TEST_F(ConfigTest_733, BenchmarkWarmupTimeZero_733) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_733, EmptyProcessName_733) {
    ConfigData data;
    data.processName = "";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_733, VerbosityQuiet_733) {
    ConfigData data;
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_733, ShowDurationsNever_733) {
    ConfigData data;
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_733, RunOrderLexicographic_733) {
    ConfigData data;
    data.runOrder = TestRunOrder::LexicographicallySorted;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::LexicographicallySorted);
}

TEST_F(ConfigTest_733, BenchmarkConfidenceIntervalZero_733) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_733, BenchmarkConfidenceIntervalOne_733) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 1.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

// Test that Config can be destroyed properly (basic lifetime test)
TEST_F(ConfigTest_733, ConfigDestructionNoLeak_733) {
    ConfigData data;
    data.processName = "test";
    data.testsOrTags = {"a", "b", "c"};
    auto config = std::make_unique<Config>(data);
    EXPECT_NO_THROW(config.reset());
}

// Test const correctness - methods should be callable on const Config
TEST_F(ConfigTest_733, ConstConfigAccess_733) {
    ConfigData data;
    data.shardCount = 7;
    data.processName = "constTest";
    const Config config(data);
    EXPECT_EQ(config.shardCount(), 7u);
    EXPECT_EQ(config.name(), StringRef("constTest"));
    EXPECT_FALSE(config.listTests());
}
