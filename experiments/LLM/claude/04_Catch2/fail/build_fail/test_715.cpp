#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_715 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// ==================== Default values tests ====================

TEST_F(ConfigTest_715, DefaultListTests_715) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_715, DefaultListTags_715) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_715, DefaultListReporters_715) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_715, DefaultListListeners_715) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_715, DefaultShowHelp_715) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_715, DefaultAllowThrows_715) {
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_715, DefaultIncludeSuccessfulResults_715) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_715, DefaultWarnAboutMissingAssertions_715) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_715, DefaultShowInvisibles_715) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_715, DefaultVerbosity_715) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_715, DefaultAbortAfter_715) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_715, DefaultShardCount_715) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_715, DefaultShardIndex_715) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_715, DefaultSkipBenchmarks_715) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_715, DefaultBenchmarkNoAnalysis_715) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_715, DefaultBenchmarkSamples_715) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_715, DefaultBenchmarkConfidenceInterval_715) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_715, DefaultBenchmarkResamples_715) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_715, DefaultBenchmarkWarmupTime_715) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_715, DefaultShowDurations_715) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_715, DefaultMinDuration_715) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_715, DefaultRunOrder_715) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_715, DefaultColourMode_715) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_715, DefaultZeroTestsCountAsSuccess_715) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_715, DefaultHasTestFilters_715) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_715, DefaultGetTestsOrTagsEmpty_715) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_715, DefaultGetSectionsToRunEmpty_715) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// ==================== Setting non-default values ====================

TEST_F(ConfigTest_715, ListTestsSetTrue_715) {
    defaultData.listTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_715, ListTagsSetTrue_715) {
    defaultData.listTags = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_715, ListReportersSetTrue_715) {
    defaultData.listReporters = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_715, ListListenersSetTrue_715) {
    defaultData.listListeners = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_715, ShowHelpSetTrue_715) {
    defaultData.showHelp = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_715, NoThrowDisablesAllowThrows_715) {
    defaultData.noThrow = true;
    Config config(defaultData);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_715, ShowSuccessfulTestsEnabled_715) {
    defaultData.showSuccessfulTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_715, ShowInvisiblesSetTrue_715) {
    defaultData.showInvisibles = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_715, VerbositySetHigh_715) {
    defaultData.verbosity = Verbosity::High;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_715, VerbositySetQuiet_715) {
    defaultData.verbosity = Verbosity::Quiet;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_715, AbortAfterSetToPositive_715) {
    defaultData.abortAfter = 5;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_715, AbortAfterSetToZero_715) {
    defaultData.abortAfter = 0;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_715, ShardCountSetTo4_715) {
    defaultData.shardCount = 4;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_715, ShardIndexSetTo3_715) {
    defaultData.shardIndex = 3;
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 3u);
}

TEST_F(ConfigTest_715, SkipBenchmarksSetTrue_715) {
    defaultData.skipBenchmarks = true;
    Config config(defaultData);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_715, BenchmarkNoAnalysisSetTrue_715) {
    defaultData.benchmarkNoAnalysis = true;
    Config config(defaultData);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_715, BenchmarkSamplesSetTo200_715) {
    defaultData.benchmarkSamples = 200;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 200u);
}

TEST_F(ConfigTest_715, BenchmarkConfidenceIntervalSetTo99_715) {
    defaultData.benchmarkConfidenceInterval = 0.99;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_715, BenchmarkResamplesSetTo50000_715) {
    defaultData.benchmarkResamples = 50000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

TEST_F(ConfigTest_715, BenchmarkWarmupTimeSetTo500_715) {
    defaultData.benchmarkWarmupTime = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

TEST_F(ConfigTest_715, ShowDurationsAlways_715) {
    defaultData.showDurations = ShowDurations::Always;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_715, ShowDurationsNever_715) {
    defaultData.showDurations = ShowDurations::Never;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_715, MinDurationSetToPositive_715) {
    defaultData.minDuration = 0.5;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_715, RunOrderRandomized_715) {
    defaultData.runOrder = TestRunOrder::Randomized;
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_715, RngSeedSpecificValue_715) {
    defaultData.rngSeed = 42;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 42u);
}

TEST_F(ConfigTest_715, AllowZeroTestsSetTrue_715) {
    defaultData.allowZeroTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_715, ProcessNameReturned_715) {
    defaultData.processName = "myTestProcess";
    Config config(defaultData);
    EXPECT_EQ(config.name(), "myTestProcess"_catch_sr);
}

TEST_F(ConfigTest_715, ProcessNameEmpty_715) {
    defaultData.processName = "";
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_715, TestsOrTagsWithFilters_715) {
    defaultData.testsOrTags = {"[tag1]", "testName"};
    Config config(defaultData);
    auto const& testsOrTags = config.getTestsOrTags();
    EXPECT_EQ(testsOrTags.size(), 2u);
    EXPECT_EQ(testsOrTags[0], "[tag1]");
    EXPECT_EQ(testsOrTags[1], "testName");
}

TEST_F(ConfigTest_715, HasTestFiltersWhenTestsOrTagsSet_715) {
    defaultData.testsOrTags = {"someTest"};
    Config config(defaultData);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_715, SectionsToRunWithValues_715) {
    defaultData.sectionsToRun = {"section1", "section2"};
    Config config(defaultData);
    auto const& sections = config.getSectionsToRun();
    EXPECT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

// ==================== Boundary conditions ====================

TEST_F(ConfigTest_715, BenchmarkSamplesSetToZero_715) {
    defaultData.benchmarkSamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

TEST_F(ConfigTest_715, BenchmarkResamplesSetToZero_715) {
    defaultData.benchmarkResamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

TEST_F(ConfigTest_715, BenchmarkWarmupTimeSetToZero_715) {
    defaultData.benchmarkWarmupTime = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_715, MinDurationSetToZero_715) {
    defaultData.minDuration = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_715, BenchmarkConfidenceIntervalSetToZero_715) {
    defaultData.benchmarkConfidenceInterval = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_715, RngSeedMaxValue_715) {
    defaultData.rngSeed = UINT32_MAX;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), UINT32_MAX);
}

TEST_F(ConfigTest_715, RngSeedZero_715) {
    defaultData.rngSeed = 0;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 0u);
}

TEST_F(ConfigTest_715, AbortAfterLargeValue_715) {
    defaultData.abortAfter = 1000000;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 1000000);
}

TEST_F(ConfigTest_715, DefaultConstructor_715) {
    Config config;
    // Default constructed config should have default ConfigData values
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.listTags());
    EXPECT_FALSE(config.showHelp());
}

// ==================== WarnAbout tests ====================

TEST_F(ConfigTest_715, WarnAboutMissingAssertionsEnabled_715) {
    defaultData.warnings = WarnAbout::NoAssertions;
    Config config(defaultData);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_715, WarnAboutNothingDisablesMissingAssertions_715) {
    defaultData.warnings = WarnAbout::Nothing;
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

// ==================== Multiple settings combined ====================

TEST_F(ConfigTest_715, MultipleSettingsCombined_715) {
    defaultData.listTests = true;
    defaultData.listTags = true;
    defaultData.showHelp = true;
    defaultData.noThrow = true;
    defaultData.verbosity = Verbosity::High;
    defaultData.abortAfter = 3;
    defaultData.skipBenchmarks = true;
    
    Config config(defaultData);
    
    EXPECT_TRUE(config.listTests());
    EXPECT_TRUE(config.listTags());
    EXPECT_TRUE(config.showHelp());
    EXPECT_FALSE(config.allowThrows());
    EXPECT_EQ(config.verbosity(), Verbosity::High);
    EXPECT_EQ(config.abortAfter(), 3);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_715, GetReporterSpecsDefault_715) {
    Config config(defaultData);
    EXPECT_TRUE(config.getReporterSpecs().empty());
}

TEST_F(ConfigTest_715, GetProcessedReporterSpecsDefault_715) {
    Config config(defaultData);
    // Processed reporter specs should be available (may or may not be empty depending on defaults)
    // Just ensure no crash on access
    auto const& specs = config.getProcessedReporterSpecs();
    (void)specs;
}
