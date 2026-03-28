#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_743 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// ===== Default ConfigData values =====

TEST_F(ConfigTest_743, DefaultBenchmarkConfidenceInterval_743) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_743, DefaultListTests_743) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_743, DefaultListTags_743) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_743, DefaultListReporters_743) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_743, DefaultListListeners_743) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_743, DefaultShowHelp_743) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_743, DefaultAllowThrows_743) {
    Config config(defaultData);
    // noThrow defaults to false, so allowThrows should be true
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_743, DefaultIncludeSuccessfulResults_743) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_743, DefaultWarnAboutMissingAssertions_743) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_743, DefaultShowInvisibles_743) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_743, DefaultVerbosity_743) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_743, DefaultAbortAfter_743) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_743, DefaultShardCount_743) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_743, DefaultShardIndex_743) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_743, DefaultSkipBenchmarks_743) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_743, DefaultBenchmarkNoAnalysis_743) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_743, DefaultBenchmarkSamples_743) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_743, DefaultBenchmarkResamples_743) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_743, DefaultBenchmarkWarmupTime_743) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_743, DefaultRunOrder_743) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_743, DefaultShowDurations_743) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_743, DefaultMinDuration_743) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_743, DefaultColourMode_743) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_743, DefaultZeroTestsCountAsSuccess_743) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_743, DefaultHasTestFilters_743) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_743, DefaultGetTestsOrTagsEmpty_743) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_743, DefaultGetSectionsToRunEmpty_743) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// ===== Custom ConfigData values =====

TEST_F(ConfigTest_743, CustomListTests_743) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_743, CustomListTags_743) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_743, CustomListReporters_743) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_743, CustomListListeners_743) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_743, CustomShowHelp_743) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_743, CustomNoThrowDisablesAllowThrows_743) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_743, CustomShowSuccessfulTests_743) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_743, CustomShowInvisibles_743) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_743, CustomVerbosityHigh_743) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_743, CustomVerbosityQuiet_743) {
    ConfigData data;
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_743, CustomAbortAfter_743) {
    ConfigData data;
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_743, CustomAbortAfterZero_743) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_743, CustomShardCount_743) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_743, CustomShardIndex_743) {
    ConfigData data;
    data.shardIndex = 3;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 3u);
}

TEST_F(ConfigTest_743, CustomSkipBenchmarks_743) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_743, CustomBenchmarkNoAnalysis_743) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_743, CustomBenchmarkSamples_743) {
    ConfigData data;
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_743, CustomBenchmarkConfidenceInterval_743) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_743, CustomBenchmarkResamples_743) {
    ConfigData data;
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

TEST_F(ConfigTest_743, CustomBenchmarkWarmupTime_743) {
    ConfigData data;
    data.benchmarkWarmupTime = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

TEST_F(ConfigTest_743, CustomRunOrderRandomize_743) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_743, CustomShowDurationsAlways_743) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_743, CustomShowDurationsNever_743) {
    ConfigData data;
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_743, CustomMinDuration_743) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_743, CustomRngSeed_743) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

TEST_F(ConfigTest_743, CustomAllowZeroTests_743) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_743, CustomProcessName_743) {
    ConfigData data;
    data.processName = "myTestProcess";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

TEST_F(ConfigTest_743, EmptyProcessName_743) {
    ConfigData data;
    data.processName = "";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_743, CustomTestsOrTags_743) {
    ConfigData data;
    data.testsOrTags = {"test1", "[tag1]"};
    Config config(data);
    auto const& testsOrTags = config.getTestsOrTags();
    EXPECT_EQ(testsOrTags.size(), 2u);
    EXPECT_EQ(testsOrTags[0], "test1");
    EXPECT_EQ(testsOrTags[1], "[tag1]");
}

TEST_F(ConfigTest_743, HasTestFiltersWithTestsOrTags_743) {
    ConfigData data;
    data.testsOrTags = {"someTest"};
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_743, CustomSectionsToRun_743) {
    ConfigData data;
    data.sectionsToRun = {"section1", "section2"};
    Config config(data);
    auto const& sections = config.getSectionsToRun();
    EXPECT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

TEST_F(ConfigTest_743, CustomFilenamesAsTags_743) {
    ConfigData data;
    data.filenamesAsTags = true;
    Config config(data);
    // filenamesAsTags doesn't have a direct getter, but the config should construct without error
    // We can verify other properties still work
    EXPECT_FALSE(config.listTests());
}

// ===== Boundary conditions =====

TEST_F(ConfigTest_743, BenchmarkConfidenceIntervalZero_743) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_743, BenchmarkConfidenceIntervalOne_743) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 1.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

TEST_F(ConfigTest_743, BenchmarkSamplesZero_743) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

TEST_F(ConfigTest_743, BenchmarkResamplesZero_743) {
    ConfigData data;
    data.benchmarkResamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

TEST_F(ConfigTest_743, BenchmarkWarmupTimeZero_743) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_743, MinDurationZero_743) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_743, RngSeedMaxValue_743) {
    ConfigData data;
    data.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(data);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

TEST_F(ConfigTest_743, RngSeedZero_743) {
    ConfigData data;
    data.rngSeed = 0;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0u);
}

TEST_F(ConfigTest_743, LargeAbortAfter_743) {
    ConfigData data;
    data.abortAfter = std::numeric_limits<int>::max();
    Config config(data);
    EXPECT_EQ(config.abortAfter(), std::numeric_limits<int>::max());
}

// ===== Warning flags =====

TEST_F(ConfigTest_743, WarnAboutMissingAssertionsDefault_743) {
    ConfigData data;
    data.warnings = WarnAbout::Nothing;
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_743, WarnAboutMissingAssertionsEnabled_743) {
    ConfigData data;
    data.warnings = WarnAbout::NoAssertions;
    Config config(data);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

// ===== Default constructor =====

TEST_F(ConfigTest_743, DefaultConstructor_743) {
    Config config;
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.showHelp());
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

// ===== Copy of ConfigData =====

TEST_F(ConfigTest_743, ConfigStoresDataCopy_743) {
    ConfigData data;
    data.benchmarkSamples = 250;
    data.processName = "testProc";
    Config config(data);
    
    // Modify original data - config should not be affected
    data.benchmarkSamples = 999;
    data.processName = "modified";
    
    EXPECT_EQ(config.benchmarkSamples(), 250u);
    EXPECT_EQ(config.name(), StringRef("testProc"));
}
