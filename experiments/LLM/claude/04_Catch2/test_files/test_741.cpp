#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_741 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// --- Default ConfigData tests ---

TEST_F(ConfigTest_741, DefaultListTests_741) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_741, DefaultListTags_741) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_741, DefaultListReporters_741) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_741, DefaultListListeners_741) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_741, DefaultShowHelp_741) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_741, DefaultAllowThrows_741) {
    Config config(defaultData);
    // noThrow defaults to false, so allowThrows should be true
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_741, DefaultIncludeSuccessfulResults_741) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_741, DefaultShowInvisibles_741) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_741, DefaultSkipBenchmarks_741) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_741, DefaultBenchmarkNoAnalysis_741) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_741, DefaultBenchmarkSamples_741) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_741, DefaultBenchmarkConfidenceInterval_741) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_741, DefaultBenchmarkResamples_741) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_741, DefaultBenchmarkWarmupTime_741) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_741, DefaultVerbosity_741) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_741, DefaultShowDurations_741) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_741, DefaultMinDuration_741) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_741, DefaultRunOrder_741) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_741, DefaultShardCount_741) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_741, DefaultShardIndex_741) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_741, DefaultColourMode_741) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_741, DefaultAbortAfter_741) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_741, DefaultZeroTestsCountAsSuccess_741) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_741, DefaultHasTestFilters_741) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_741, DefaultGetTestsOrTagsEmpty_741) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_741, DefaultGetSectionsToRunEmpty_741) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// --- Custom ConfigData tests ---

TEST_F(ConfigTest_741, ListTestsSetTrue_741) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_741, ListTagsSetTrue_741) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_741, ListReportersSetTrue_741) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_741, ListListenersSetTrue_741) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_741, ShowHelpSetTrue_741) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_741, NoThrowDisablesAllowThrows_741) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_741, ShowSuccessfulTestsEnablesIncludeSuccessfulResults_741) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_741, ShowInvisiblesSetTrue_741) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_741, SkipBenchmarksSetTrue_741) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_741, BenchmarkNoAnalysisSetTrue_741) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_741, CustomBenchmarkSamples_741) {
    ConfigData data;
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_741, CustomBenchmarkConfidenceInterval_741) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_741, CustomBenchmarkResamples_741) {
    ConfigData data;
    data.benchmarkResamples = 200000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 200000u);
}

TEST_F(ConfigTest_741, CustomBenchmarkWarmupTime_741) {
    ConfigData data;
    data.benchmarkWarmupTime = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

TEST_F(ConfigTest_741, CustomVerbosityHigh_741) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_741, CustomRunOrderRandomize_741) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_741, CustomRngSeed_741) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

TEST_F(ConfigTest_741, CustomShardCount_741) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_741, CustomShardIndex_741) {
    ConfigData data;
    data.shardIndex = 2;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 2u);
}

TEST_F(ConfigTest_741, CustomAbortAfter_741) {
    ConfigData data;
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_741, AbortAfterZero_741) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_741, AllowZeroTestsSetTrue_741) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_741, CustomShowDurationsAlways_741) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_741, CustomShowDurationsNever_741) {
    ConfigData data;
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_741, CustomMinDuration_741) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_741, ProcessNameAsName_741) {
    ConfigData data;
    data.processName = "myTestProcess";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

TEST_F(ConfigTest_741, EmptyProcessName_741) {
    ConfigData data;
    data.processName = "";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_741, TestsOrTagsNonEmpty_741) {
    ConfigData data;
    data.testsOrTags = {"test1", "test2", "[tag1]"};
    Config config(data);
    auto const& testsOrTags = config.getTestsOrTags();
    EXPECT_EQ(testsOrTags.size(), 3u);
    EXPECT_EQ(testsOrTags[0], "test1");
    EXPECT_EQ(testsOrTags[1], "test2");
    EXPECT_EQ(testsOrTags[2], "[tag1]");
}

TEST_F(ConfigTest_741, HasTestFiltersWhenTestsOrTagsProvided_741) {
    ConfigData data;
    data.testsOrTags = {"someTest"};
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_741, SectionsToRunNonEmpty_741) {
    ConfigData data;
    data.sectionsToRun = {"section1", "section2"};
    Config config(data);
    auto const& sections = config.getSectionsToRun();
    EXPECT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

TEST_F(ConfigTest_741, WarnAboutMissingAssertionsDefault_741) {
    ConfigData data;
    data.warnings = WarnAbout::Nothing;
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_741, WarnAboutMissingAssertionsEnabled_741) {
    ConfigData data;
    data.warnings = WarnAbout::NoAssertions;
    Config config(data);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_741, DefaultConstructor_741) {
    Config config;
    // Default constructed config should have default values
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.showHelp());
    EXPECT_FALSE(config.skipBenchmarks());
}

// Boundary tests

TEST_F(ConfigTest_741, BenchmarkSamplesZero_741) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

TEST_F(ConfigTest_741, BenchmarkResamplesZero_741) {
    ConfigData data;
    data.benchmarkResamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

TEST_F(ConfigTest_741, BenchmarkWarmupTimeZero_741) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_741, BenchmarkConfidenceIntervalZero_741) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_741, BenchmarkConfidenceIntervalOne_741) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 1.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

TEST_F(ConfigTest_741, MinDurationZero_741) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_741, RngSeedMaxValue_741) {
    ConfigData data;
    data.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(data);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

TEST_F(ConfigTest_741, ShardCountMax_741) {
    ConfigData data;
    data.shardCount = std::numeric_limits<unsigned int>::max();
    Config config(data);
    EXPECT_EQ(config.shardCount(), std::numeric_limits<unsigned int>::max());
}

TEST_F(ConfigTest_741, ColourModeAnsi_741) {
    ConfigData data;
    data.defaultColourMode = ColourMode::ANSI;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_741, ColourModeNone_741) {
    ConfigData data;
    data.defaultColourMode = ColourMode::None;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::None);
}

TEST_F(ConfigTest_741, LargeAbortAfterValue_741) {
    ConfigData data;
    data.abortAfter = 1000000;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 1000000);
}
