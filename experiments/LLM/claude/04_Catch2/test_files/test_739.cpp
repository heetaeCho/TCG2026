#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_739 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// ============ Default values tests ============

TEST_F(ConfigTest_739, DefaultVerbosity_739) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_739, DefaultListTests_739) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_739, DefaultListTags_739) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_739, DefaultListReporters_739) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_739, DefaultListListeners_739) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_739, DefaultShowHelp_739) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_739, DefaultAllowThrows_739) {
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_739, DefaultIncludeSuccessfulResults_739) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_739, DefaultWarnAboutMissingAssertions_739) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_739, DefaultShowDurations_739) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_739, DefaultMinDuration_739) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_739, DefaultRunOrder_739) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_739, DefaultShardCount_739) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_739, DefaultShardIndex_739) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_739, DefaultColourMode_739) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_739, DefaultAbortAfter_739) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_739, DefaultShowInvisibles_739) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_739, DefaultSkipBenchmarks_739) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_739, DefaultBenchmarkNoAnalysis_739) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_739, DefaultBenchmarkSamples_739) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_739, DefaultBenchmarkConfidenceInterval_739) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_739, DefaultBenchmarkResamples_739) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_739, DefaultBenchmarkWarmupTime_739) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_739, DefaultHasTestFilters_739) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_739, DefaultZeroTestsCountAsSuccess_739) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_739, DefaultGetTestsOrTagsEmpty_739) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_739, DefaultGetSectionsToRunEmpty_739) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// ============ Custom values tests ============

TEST_F(ConfigTest_739, CustomVerbosityHigh_739) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_739, CustomVerbosityQuiet_739) {
    ConfigData data;
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_739, CustomListTestsTrue_739) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_739, CustomListTagsTrue_739) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_739, CustomListReportersTrue_739) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_739, CustomListListenersTrue_739) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_739, CustomShowHelpTrue_739) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_739, CustomNoThrowDisablesAllowThrows_739) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_739, CustomShowSuccessfulTests_739) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_739, CustomShowInvisiblesTrue_739) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_739, CustomAbortAfterPositive_739) {
    ConfigData data;
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_739, CustomAbortAfterZero_739) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_739, CustomRunOrderRandomize_739) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_739, CustomShardCount_739) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_739, CustomShardIndex_739) {
    ConfigData data;
    data.shardIndex = 3;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 3u);
}

TEST_F(ConfigTest_739, CustomSkipBenchmarks_739) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_739, CustomBenchmarkNoAnalysis_739) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_739, CustomBenchmarkSamples_739) {
    ConfigData data;
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_739, CustomBenchmarkConfidenceInterval_739) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_739, CustomBenchmarkResamples_739) {
    ConfigData data;
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

TEST_F(ConfigTest_739, CustomBenchmarkWarmupTime_739) {
    ConfigData data;
    data.benchmarkWarmupTime = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

TEST_F(ConfigTest_739, CustomShowDurationsAlways_739) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_739, CustomShowDurationsNever_739) {
    ConfigData data;
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_739, CustomMinDuration_739) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_739, CustomAllowZeroTests_739) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_739, CustomProcessName_739) {
    ConfigData data;
    data.processName = "myTestProcess";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

TEST_F(ConfigTest_739, CustomProcessNameEmpty_739) {
    ConfigData data;
    data.processName = "";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_739, CustomColourModeAnsi_739) {
    ConfigData data;
    data.defaultColourMode = ColourMode::ANSI;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_739, CustomColourModeNone_739) {
    ConfigData data;
    data.defaultColourMode = ColourMode::None;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::None);
}

TEST_F(ConfigTest_739, CustomRngSeed_739) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

TEST_F(ConfigTest_739, CustomTestsOrTags_739) {
    ConfigData data;
    data.testsOrTags = {"[tag1]", "testName"};
    Config config(data);
    auto const& testsOrTags = config.getTestsOrTags();
    ASSERT_EQ(testsOrTags.size(), 2u);
    EXPECT_EQ(testsOrTags[0], "[tag1]");
    EXPECT_EQ(testsOrTags[1], "testName");
}

TEST_F(ConfigTest_739, HasTestFiltersWhenTestsOrTagsProvided_739) {
    ConfigData data;
    data.testsOrTags = {"someTest"};
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_739, CustomSectionsToRun_739) {
    ConfigData data;
    data.sectionsToRun = {"section1", "section2"};
    Config config(data);
    auto const& sections = config.getSectionsToRun();
    ASSERT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

TEST_F(ConfigTest_739, WarnAboutMissingAssertionsWhenWarningSet_739) {
    ConfigData data;
    data.warnings = WarnAbout::NoAssertions;
    Config config(data);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_739, WarnAboutMissingAssertionsFalseByDefault_739) {
    ConfigData data;
    data.warnings = WarnAbout::Nothing;
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

// ============ Boundary tests ============

TEST_F(ConfigTest_739, BoundaryAbortAfterMaxInt_739) {
    ConfigData data;
    data.abortAfter = std::numeric_limits<int>::max();
    Config config(data);
    EXPECT_EQ(config.abortAfter(), std::numeric_limits<int>::max());
}

TEST_F(ConfigTest_739, BoundaryShardCountOne_739) {
    ConfigData data;
    data.shardCount = 1;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_739, BoundaryBenchmarkSamplesOne_739) {
    ConfigData data;
    data.benchmarkSamples = 1;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 1u);
}

TEST_F(ConfigTest_739, BoundaryMinDurationZero_739) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_739, BoundaryBenchmarkWarmupTimeZero_739) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_739, BoundaryRngSeedZero_739) {
    ConfigData data;
    data.rngSeed = 0;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0u);
}

TEST_F(ConfigTest_739, BoundaryRngSeedMax_739) {
    ConfigData data;
    data.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(data);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

TEST_F(ConfigTest_739, BoundaryBenchmarkConfidenceIntervalZero_739) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_739, BoundaryBenchmarkConfidenceIntervalOne_739) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 1.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

// ============ Default constructor test ============

TEST_F(ConfigTest_739, DefaultConstructor_739) {
    Config config;
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.showHelp());
    EXPECT_EQ(config.abortAfter(), -1);
}

// ============ Copy of ConfigData test ============

TEST_F(ConfigTest_739, ConfigDataCopySemantics_739) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    data.abortAfter = 10;
    data.showHelp = true;
    data.processName = "testProc";
    
    Config config(data);
    
    // Modifying original data should not affect config
    data.verbosity = Verbosity::Quiet;
    data.abortAfter = 20;
    
    EXPECT_EQ(config.verbosity(), Verbosity::High);
    EXPECT_EQ(config.abortAfter(), 10);
    EXPECT_TRUE(config.showHelp());
    EXPECT_EQ(config.name(), StringRef("testProc"));
}

// ============ Multiple settings combined ============

TEST_F(ConfigTest_739, MultipleSettingsCombined_739) {
    ConfigData data;
    data.listTests = true;
    data.listTags = true;
    data.showHelp = true;
    data.noThrow = true;
    data.showSuccessfulTests = true;
    data.showInvisibles = true;
    data.skipBenchmarks = true;
    data.benchmarkNoAnalysis = true;
    data.allowZeroTests = true;
    data.verbosity = Verbosity::High;
    data.abortAfter = 3;
    data.shardCount = 8;
    data.shardIndex = 5;
    
    Config config(data);
    
    EXPECT_TRUE(config.listTests());
    EXPECT_TRUE(config.listTags());
    EXPECT_TRUE(config.showHelp());
    EXPECT_FALSE(config.allowThrows());
    EXPECT_TRUE(config.includeSuccessfulResults());
    EXPECT_TRUE(config.showInvisibles());
    EXPECT_TRUE(config.skipBenchmarks());
    EXPECT_TRUE(config.benchmarkNoAnalysis());
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
    EXPECT_EQ(config.verbosity(), Verbosity::High);
    EXPECT_EQ(config.abortAfter(), 3);
    EXPECT_EQ(config.shardCount(), 8u);
    EXPECT_EQ(config.shardIndex(), 5u);
}
