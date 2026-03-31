#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_728 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// --- zeroTestsCountAsSuccess ---

TEST_F(ConfigTest_728, ZeroTestsCountAsSuccess_DefaultFalse_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_728, ZeroTestsCountAsSuccess_WhenTrue_728) {
    defaultData.allowZeroTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

// --- listTests ---

TEST_F(ConfigTest_728, ListTests_DefaultFalse_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_728, ListTests_WhenTrue_728) {
    defaultData.listTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTests());
}

// --- listTags ---

TEST_F(ConfigTest_728, ListTags_DefaultFalse_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_728, ListTags_WhenTrue_728) {
    defaultData.listTags = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTags());
}

// --- listReporters ---

TEST_F(ConfigTest_728, ListReporters_DefaultFalse_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_728, ListReporters_WhenTrue_728) {
    defaultData.listReporters = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listReporters());
}

// --- listListeners ---

TEST_F(ConfigTest_728, ListListeners_DefaultFalse_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_728, ListListeners_WhenTrue_728) {
    defaultData.listListeners = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listListeners());
}

// --- showHelp ---

TEST_F(ConfigTest_728, ShowHelp_DefaultFalse_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_728, ShowHelp_WhenTrue_728) {
    defaultData.showHelp = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showHelp());
}

// --- allowThrows ---

TEST_F(ConfigTest_728, AllowThrows_DefaultTrue_728) {
    // noThrow defaults to false, so allowThrows should be true
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_728, AllowThrows_WhenNoThrowTrue_728) {
    defaultData.noThrow = true;
    Config config(defaultData);
    EXPECT_FALSE(config.allowThrows());
}

// --- includeSuccessfulResults ---

TEST_F(ConfigTest_728, IncludeSuccessfulResults_DefaultFalse_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_728, IncludeSuccessfulResults_WhenTrue_728) {
    defaultData.showSuccessfulTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// --- showInvisibles ---

TEST_F(ConfigTest_728, ShowInvisibles_DefaultFalse_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_728, ShowInvisibles_WhenTrue_728) {
    defaultData.showInvisibles = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showInvisibles());
}

// --- showDurations ---

TEST_F(ConfigTest_728, ShowDurations_Default_728) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_728, ShowDurations_Always_728) {
    defaultData.showDurations = ShowDurations::Always;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_728, ShowDurations_Never_728) {
    defaultData.showDurations = ShowDurations::Never;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

// --- minDuration ---

TEST_F(ConfigTest_728, MinDuration_Default_728) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_728, MinDuration_CustomValue_728) {
    defaultData.minDuration = 0.5;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

// --- runOrder ---

TEST_F(ConfigTest_728, RunOrder_Default_728) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_728, RunOrder_Randomized_728) {
    defaultData.runOrder = TestRunOrder::Randomized;
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

// --- rngSeed ---

TEST_F(ConfigTest_728, RngSeed_CustomValue_728) {
    defaultData.rngSeed = 42;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// --- shardCount ---

TEST_F(ConfigTest_728, ShardCount_Default_728) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_728, ShardCount_CustomValue_728) {
    defaultData.shardCount = 5;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 5u);
}

// --- shardIndex ---

TEST_F(ConfigTest_728, ShardIndex_Default_728) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_728, ShardIndex_CustomValue_728) {
    defaultData.shardIndex = 3;
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 3u);
}

// --- abortAfter ---

TEST_F(ConfigTest_728, AbortAfter_Default_728) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_728, AbortAfter_CustomValue_728) {
    defaultData.abortAfter = 5;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 5);
}

// --- defaultColourMode ---

TEST_F(ConfigTest_728, DefaultColourMode_Default_728) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_728, DefaultColourMode_AnsiColours_728) {
    defaultData.defaultColourMode = ColourMode::ANSI;
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

// --- verbosity ---

TEST_F(ConfigTest_728, Verbosity_Default_728) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_728, Verbosity_Quiet_728) {
    defaultData.verbosity = Verbosity::Quiet;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_728, Verbosity_High_728) {
    defaultData.verbosity = Verbosity::High;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

// --- skipBenchmarks ---

TEST_F(ConfigTest_728, SkipBenchmarks_DefaultFalse_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_728, SkipBenchmarks_WhenTrue_728) {
    defaultData.skipBenchmarks = true;
    Config config(defaultData);
    EXPECT_TRUE(config.skipBenchmarks());
}

// --- benchmarkNoAnalysis ---

TEST_F(ConfigTest_728, BenchmarkNoAnalysis_DefaultFalse_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_728, BenchmarkNoAnalysis_WhenTrue_728) {
    defaultData.benchmarkNoAnalysis = true;
    Config config(defaultData);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

// --- benchmarkSamples ---

TEST_F(ConfigTest_728, BenchmarkSamples_Default_728) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_728, BenchmarkSamples_CustomValue_728) {
    defaultData.benchmarkSamples = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

// --- benchmarkConfidenceInterval ---

TEST_F(ConfigTest_728, BenchmarkConfidenceInterval_Default_728) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_728, BenchmarkConfidenceInterval_CustomValue_728) {
    defaultData.benchmarkConfidenceInterval = 0.99;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

// --- benchmarkResamples ---

TEST_F(ConfigTest_728, BenchmarkResamples_Default_728) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_728, BenchmarkResamples_CustomValue_728) {
    defaultData.benchmarkResamples = 50000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

// --- benchmarkWarmupTime ---

TEST_F(ConfigTest_728, BenchmarkWarmupTime_Default_728) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_728, BenchmarkWarmupTime_CustomValue_728) {
    defaultData.benchmarkWarmupTime = 200;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

// --- name ---

TEST_F(ConfigTest_728, Name_DefaultEmpty_728) {
    Config config(defaultData);
    EXPECT_TRUE(config.name().empty());
}

TEST_F(ConfigTest_728, Name_CustomProcessName_728) {
    defaultData.processName = "myTestProcess";
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

// --- getTestsOrTags ---

TEST_F(ConfigTest_728, GetTestsOrTags_DefaultEmpty_728) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_728, GetTestsOrTags_WithValues_728) {
    defaultData.testsOrTags = {"test1", "[tag1]"};
    Config config(defaultData);
    auto const& testsOrTags = config.getTestsOrTags();
    ASSERT_EQ(testsOrTags.size(), 2u);
    EXPECT_EQ(testsOrTags[0], "test1");
    EXPECT_EQ(testsOrTags[1], "[tag1]");
}

// --- getSectionsToRun ---

TEST_F(ConfigTest_728, GetSectionsToRun_DefaultEmpty_728) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

TEST_F(ConfigTest_728, GetSectionsToRun_WithValues_728) {
    defaultData.sectionsToRun = {"section1", "section2"};
    Config config(defaultData);
    auto const& sections = config.getSectionsToRun();
    ASSERT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

// --- hasTestFilters ---

TEST_F(ConfigTest_728, HasTestFilters_DefaultFalse_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_728, HasTestFilters_WhenTestsOrTagsProvided_728) {
    defaultData.testsOrTags = {"someTest"};
    Config config(defaultData);
    EXPECT_TRUE(config.hasTestFilters());
}

// --- warnAboutMissingAssertions ---

TEST_F(ConfigTest_728, WarnAboutMissingAssertions_DefaultFalse_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_728, WarnAboutMissingAssertions_WhenWarningSet_728) {
    defaultData.warnings = WarnAbout::NoAssertions;
    Config config(defaultData);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

// --- warnAboutUnmatchedTestSpecs ---

TEST_F(ConfigTest_728, WarnAboutUnmatchedTestSpecs_DefaultFalse_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_728, WarnAboutUnmatchedTestSpecs_WhenWarningSet_728) {
    defaultData.warnings = WarnAbout::UnmatchedTestSpec;
    Config config(defaultData);
    EXPECT_TRUE(config.warnAboutUnmatchedTestSpecs());
}

// --- Default constructed Config ---

TEST_F(ConfigTest_728, DefaultConstructor_728) {
    Config config;
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.listTags());
    EXPECT_FALSE(config.showHelp());
    EXPECT_TRUE(config.allowThrows());
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

// --- Boundary: abortAfter zero ---

TEST_F(ConfigTest_728, AbortAfter_Zero_728) {
    defaultData.abortAfter = 0;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 0);
}

// --- Boundary: shardCount of 1 with shardIndex of 0 ---

TEST_F(ConfigTest_728, ShardCountOneShardIndexZero_728) {
    defaultData.shardCount = 1;
    defaultData.shardIndex = 0;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
    EXPECT_EQ(config.shardIndex(), 0u);
}

// --- Boundary: benchmarkSamples zero ---

TEST_F(ConfigTest_728, BenchmarkSamples_Zero_728) {
    defaultData.benchmarkSamples = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

// --- Boundary: benchmarkWarmupTime zero ---

TEST_F(ConfigTest_728, BenchmarkWarmupTime_Zero_728) {
    defaultData.benchmarkWarmupTime = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

// --- Boundary: minDuration zero ---

TEST_F(ConfigTest_728, MinDuration_Zero_728) {
    defaultData.minDuration = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

// --- benchmarkConfidenceInterval boundary ---

TEST_F(ConfigTest_728, BenchmarkConfidenceInterval_Zero_728) {
    defaultData.benchmarkConfidenceInterval = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_728, BenchmarkConfidenceInterval_One_728) {
    defaultData.benchmarkConfidenceInterval = 1.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}

// --- testSpec ---

TEST_F(ConfigTest_728, TestSpec_DefaultIsEmpty_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.testSpec().hasFilters());
}

// --- shouldDebugBreak ---

TEST_F(ConfigTest_728, ShouldDebugBreak_Default_728) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}
