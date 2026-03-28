#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_726 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// --- Default ConfigData Tests ---

TEST_F(ConfigTest_726, DefaultListTestsIsFalse_726) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_726, DefaultListTagsIsFalse_726) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_726, DefaultListReportersIsFalse_726) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_726, DefaultListListenersIsFalse_726) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_726, DefaultShowHelpIsFalse_726) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_726, DefaultAllowThrowsIsTrue_726) {
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_726, DefaultIncludeSuccessfulResultsIsFalse_726) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_726, DefaultWarnAboutMissingAssertionsIsFalse_726) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_726, DefaultWarnAboutUnmatchedTestSpecsIsFalse_726) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_726, DefaultZeroTestsCountAsSuccessIsFalse_726) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_726, DefaultShowDurationsIsDefaultForReporter_726) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_726, DefaultMinDurationIsNegativeOne_726) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_726, DefaultRunOrderIsDeclared_726) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_726, DefaultShardCountIsOne_726) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_726, DefaultShardIndexIsZero_726) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_726, DefaultColourModeIsPlatformDefault_726) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_726, DefaultAbortAfterIsNegativeOne_726) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_726, DefaultShowInvisiblesIsFalse_726) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_726, DefaultVerbosityIsNormal_726) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_726, DefaultSkipBenchmarksIsFalse_726) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_726, DefaultBenchmarkNoAnalysisIsFalse_726) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_726, DefaultBenchmarkSamplesIs100_726) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_726, DefaultBenchmarkConfidenceInterval_726) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_726, DefaultBenchmarkResamplesIs100000_726) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_726, DefaultBenchmarkWarmupTimeIs100ms_726) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_726, DefaultHasTestFiltersIsFalse_726) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_726, DefaultGetTestsOrTagsIsEmpty_726) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_726, DefaultGetSectionsToRunIsEmpty_726) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

TEST_F(ConfigTest_726, DefaultShouldDebugBreakIsFalse_726) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}

// --- Custom ConfigData Tests ---

TEST_F(ConfigTest_726, ListTestsSetToTrue_726) {
    defaultData.listTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_726, ListTagsSetToTrue_726) {
    defaultData.listTags = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_726, ListReportersSetToTrue_726) {
    defaultData.listReporters = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_726, ListListenersSetToTrue_726) {
    defaultData.listListeners = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_726, ShowHelpSetToTrue_726) {
    defaultData.showHelp = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_726, NoThrowDisablesAllowThrows_726) {
    defaultData.noThrow = true;
    Config config(defaultData);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_726, ShowSuccessfulTestsEnablesIncludeSuccessfulResults_726) {
    defaultData.showSuccessfulTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_726, WarnAboutNoAssertionsEnabled_726) {
    defaultData.warnings = WarnAbout::NoAssertions;
    Config config(defaultData);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_726, WarnAboutUnmatchedTestSpecEnabled_726) {
    defaultData.warnings = WarnAbout::UnmatchedTestSpec;
    Config config(defaultData);
    EXPECT_TRUE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_726, WarnAboutBothWarningsEnabled_726) {
    defaultData.warnings = static_cast<WarnAbout::What>(
        WarnAbout::NoAssertions | WarnAbout::UnmatchedTestSpec);
    Config config(defaultData);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
    EXPECT_TRUE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_726, AllowZeroTestsEnablesZeroTestsCountAsSuccess_726) {
    defaultData.allowZeroTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_726, ShowInvisiblesSetToTrue_726) {
    defaultData.showInvisibles = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_726, VerbositySetToHigh_726) {
    defaultData.verbosity = Verbosity::High;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_726, VerbositySetToQuiet_726) {
    defaultData.verbosity = Verbosity::Quiet;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_726, SkipBenchmarksSetToTrue_726) {
    defaultData.skipBenchmarks = true;
    Config config(defaultData);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_726, BenchmarkNoAnalysisSetToTrue_726) {
    defaultData.benchmarkNoAnalysis = true;
    Config config(defaultData);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_726, CustomBenchmarkSamples_726) {
    defaultData.benchmarkSamples = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_726, CustomBenchmarkConfidenceInterval_726) {
    defaultData.benchmarkConfidenceInterval = 0.99;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_726, CustomBenchmarkResamples_726) {
    defaultData.benchmarkResamples = 50000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

TEST_F(ConfigTest_726, CustomBenchmarkWarmupTime_726) {
    defaultData.benchmarkWarmupTime = 200;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

TEST_F(ConfigTest_726, CustomAbortAfter_726) {
    defaultData.abortAfter = 5;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_726, AbortAfterZero_726) {
    defaultData.abortAfter = 0;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_726, CustomShardCount_726) {
    defaultData.shardCount = 4;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_726, CustomShardIndex_726) {
    defaultData.shardIndex = 2;
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 2u);
}

TEST_F(ConfigTest_726, CustomRunOrderRandomize_726) {
    defaultData.runOrder = TestRunOrder::Randomized;
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_726, CustomRngSeed_726) {
    defaultData.rngSeed = 42;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 42u);
}

TEST_F(ConfigTest_726, CustomMinDuration_726) {
    defaultData.minDuration = 0.5;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_726, MinDurationZero_726) {
    defaultData.minDuration = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_726, ShowDurationsAlways_726) {
    defaultData.showDurations = ShowDurations::Always;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_726, ShowDurationsNever_726) {
    defaultData.showDurations = ShowDurations::Never;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_726, ProcessNameReflectedInName_726) {
    defaultData.processName = "MyTestProcess";
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef("MyTestProcess"));
}

TEST_F(ConfigTest_726, EmptyProcessNameReflectedInName_726) {
    defaultData.processName = "";
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_726, TestsOrTagsReflectedCorrectly_726) {
    defaultData.testsOrTags = {"[unit]", "TestFoo"};
    Config config(defaultData);
    auto const& tags = config.getTestsOrTags();
    ASSERT_EQ(tags.size(), 2u);
    EXPECT_EQ(tags[0], "[unit]");
    EXPECT_EQ(tags[1], "TestFoo");
}

TEST_F(ConfigTest_726, HasTestFiltersWhenTestsOrTagsSet_726) {
    defaultData.testsOrTags = {"SomeTest"};
    Config config(defaultData);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_726, SectionsToRunReflectedCorrectly_726) {
    defaultData.sectionsToRun = {"Section1", "Section2"};
    Config config(defaultData);
    auto const& sections = config.getSectionsToRun();
    ASSERT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "Section1");
    EXPECT_EQ(sections[1], "Section2");
}

TEST_F(ConfigTest_726, FilenamesAsTagsSetToTrue_726) {
    defaultData.filenamesAsTags = true;
    Config config(defaultData);
    // filenamesAsTags doesn't have a direct getter but should not cause issues
    // We verify the config is constructible with this setting
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_726, DefaultConstructorCreatesValidConfig_726) {
    Config config;
    // Default constructed config should have sane defaults
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.showHelp());
    EXPECT_TRUE(config.allowThrows());
}

// --- Boundary Tests ---

TEST_F(ConfigTest_726, BenchmarkSamplesZero_726) {
    defaultData.benchmarkSamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

TEST_F(ConfigTest_726, BenchmarkResamplesZero_726) {
    defaultData.benchmarkResamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

TEST_F(ConfigTest_726, BenchmarkWarmupTimeZero_726) {
    defaultData.benchmarkWarmupTime = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_726, BenchmarkConfidenceIntervalZero_726) {
    defaultData.benchmarkConfidenceInterval = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_726, BenchmarkConfidenceIntervalOne_726) {
    defaultData.benchmarkConfidenceInterval = 1.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

TEST_F(ConfigTest_726, RngSeedMaxValue_726) {
    defaultData.rngSeed = UINT32_MAX;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), UINT32_MAX);
}

TEST_F(ConfigTest_726, RngSeedZero_726) {
    defaultData.rngSeed = 0;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 0u);
}

TEST_F(ConfigTest_726, LargeAbortAfterValue_726) {
    defaultData.abortAfter = 1000000;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 1000000);
}

TEST_F(ConfigTest_726, WarningsNothingMeansNoWarnings_726) {
    defaultData.warnings = WarnAbout::Nothing;
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}
