#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_727 : public ::testing::Test {
protected:
    ConfigData makeDefaultData() {
        ConfigData data;
        return data;
    }
};

// --- Default ConfigData Tests ---

TEST_F(ConfigTest_727, DefaultListTests_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_727, DefaultListTags_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_727, DefaultListReporters_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_727, DefaultListListeners_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_727, DefaultShowHelp_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_727, DefaultAllowThrows_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    // noThrow defaults to false, so allowThrows should be true
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_727, DefaultIncludeSuccessfulResults_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_727, DefaultWarnAboutMissingAssertions_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_727, DefaultWarnAboutUnmatchedTestSpecs_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_727, DefaultZeroTestsCountAsSuccess_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_727, DefaultShowDurations_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_727, DefaultMinDuration_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_727, DefaultRunOrder_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_727, DefaultShardCount_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_727, DefaultShardIndex_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_727, DefaultColourMode_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_727, DefaultAbortAfter_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_727, DefaultShowInvisibles_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_727, DefaultVerbosity_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_727, DefaultSkipBenchmarks_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_727, DefaultBenchmarkNoAnalysis_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_727, DefaultBenchmarkSamples_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_727, DefaultBenchmarkConfidenceInterval_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_727, DefaultBenchmarkResamples_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_727, DefaultBenchmarkWarmupTime_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_727, DefaultHasTestFilters_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_727, DefaultGetTestsOrTagsEmpty_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_727, DefaultGetSectionsToRunEmpty_727) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// --- Non-default ConfigData Tests ---

TEST_F(ConfigTest_727, ListTestsTrue_727) {
    ConfigData data = makeDefaultData();
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_727, ListTagsTrue_727) {
    ConfigData data = makeDefaultData();
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_727, ListReportersTrue_727) {
    ConfigData data = makeDefaultData();
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_727, ListListenersTrue_727) {
    ConfigData data = makeDefaultData();
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_727, ShowHelpTrue_727) {
    ConfigData data = makeDefaultData();
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_727, NoThrowDisablesAllowThrows_727) {
    ConfigData data = makeDefaultData();
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_727, ShowSuccessfulTestsEnablesIncludeSuccessfulResults_727) {
    ConfigData data = makeDefaultData();
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_727, WarnAboutNoAssertions_727) {
    ConfigData data = makeDefaultData();
    data.warnings = WarnAbout::NoAssertions;
    Config config(data);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_727, WarnAboutUnmatchedTestSpec_727) {
    ConfigData data = makeDefaultData();
    data.warnings = WarnAbout::UnmatchedTestSpec;
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
    EXPECT_TRUE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_727, WarnAboutBothFlags_727) {
    ConfigData data = makeDefaultData();
    data.warnings = static_cast<WarnAbout::What>(WarnAbout::NoAssertions | WarnAbout::UnmatchedTestSpec);
    Config config(data);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
    EXPECT_TRUE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_727, AllowZeroTestsTrue_727) {
    ConfigData data = makeDefaultData();
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_727, ShowDurationsAlways_727) {
    ConfigData data = makeDefaultData();
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_727, ShowDurationsNever_727) {
    ConfigData data = makeDefaultData();
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_727, MinDurationCustom_727) {
    ConfigData data = makeDefaultData();
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_727, RunOrderRandomized_727) {
    ConfigData data = makeDefaultData();
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_727, CustomRngSeed_727) {
    ConfigData data = makeDefaultData();
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

TEST_F(ConfigTest_727, CustomShardCount_727) {
    ConfigData data = makeDefaultData();
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_727, CustomShardIndex_727) {
    ConfigData data = makeDefaultData();
    data.shardIndex = 3;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 3u);
}

TEST_F(ConfigTest_727, AbortAfterCustom_727) {
    ConfigData data = makeDefaultData();
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_727, ShowInvisiblesTrue_727) {
    ConfigData data = makeDefaultData();
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_727, VerbosityHigh_727) {
    ConfigData data = makeDefaultData();
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_727, VerbosityQuiet_727) {
    ConfigData data = makeDefaultData();
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_727, SkipBenchmarksTrue_727) {
    ConfigData data = makeDefaultData();
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_727, BenchmarkNoAnalysisTrue_727) {
    ConfigData data = makeDefaultData();
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_727, CustomBenchmarkSamples_727) {
    ConfigData data = makeDefaultData();
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_727, CustomBenchmarkConfidenceInterval_727) {
    ConfigData data = makeDefaultData();
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_727, CustomBenchmarkResamples_727) {
    ConfigData data = makeDefaultData();
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

TEST_F(ConfigTest_727, CustomBenchmarkWarmupTime_727) {
    ConfigData data = makeDefaultData();
    data.benchmarkWarmupTime = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

TEST_F(ConfigTest_727, ProcessNameReflectedInName_727) {
    ConfigData data = makeDefaultData();
    data.processName = "myTestProcess";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

TEST_F(ConfigTest_727, EmptyProcessNameReturnsEmpty_727) {
    ConfigData data = makeDefaultData();
    data.processName = "";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_727, TestsOrTagsNonEmpty_727) {
    ConfigData data = makeDefaultData();
    data.testsOrTags = {"testA", "testB"};
    Config config(data);
    auto const& result = config.getTestsOrTags();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "testA");
    EXPECT_EQ(result[1], "testB");
}

TEST_F(ConfigTest_727, HasTestFiltersWhenTestsOrTagsProvided_727) {
    ConfigData data = makeDefaultData();
    data.testsOrTags = {"someFilter"};
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_727, SectionsToRunNonEmpty_727) {
    ConfigData data = makeDefaultData();
    data.sectionsToRun = {"section1", "section2"};
    Config config(data);
    auto const& result = config.getSectionsToRun();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "section1");
    EXPECT_EQ(result[1], "section2");
}

TEST_F(ConfigTest_727, FilenamesAsTagsTrue_727) {
    ConfigData data = makeDefaultData();
    data.filenamesAsTags = true;
    Config config(data);
    // filenamesAsTags is not directly exposed via a getter in the interface,
    // but it shouldn't cause construction issues
    // We just verify the config can be constructed without issues
    EXPECT_FALSE(config.showHelp()); // Sanity check
}

TEST_F(ConfigTest_727, DefaultConstructor_727) {
    Config config;
    // Default constructed config should have sensible defaults
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.listTags());
    EXPECT_FALSE(config.showHelp());
    EXPECT_TRUE(config.allowThrows());
    EXPECT_FALSE(config.hasTestFilters());
}

// --- Boundary Tests ---

TEST_F(ConfigTest_727, AbortAfterZero_727) {
    ConfigData data = makeDefaultData();
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_727, BenchmarkSamplesZero_727) {
    ConfigData data = makeDefaultData();
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

TEST_F(ConfigTest_727, BenchmarkResamplesZero_727) {
    ConfigData data = makeDefaultData();
    data.benchmarkResamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

TEST_F(ConfigTest_727, BenchmarkWarmupTimeZero_727) {
    ConfigData data = makeDefaultData();
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_727, MinDurationZero_727) {
    ConfigData data = makeDefaultData();
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_727, BenchmarkConfidenceIntervalZero_727) {
    ConfigData data = makeDefaultData();
    data.benchmarkConfidenceInterval = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_727, RngSeedZero_727) {
    ConfigData data = makeDefaultData();
    data.rngSeed = 0;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0u);
}

TEST_F(ConfigTest_727, RngSeedMax_727) {
    ConfigData data = makeDefaultData();
    data.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(data);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

TEST_F(ConfigTest_727, WarningsNothingFlag_727) {
    ConfigData data = makeDefaultData();
    data.warnings = WarnAbout::Nothing;
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_727, ColourModeAnsi_727) {
    ConfigData data = makeDefaultData();
    data.defaultColourMode = ColourMode::ANSI;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_727, ColourModeNone_727) {
    ConfigData data = makeDefaultData();
    data.defaultColourMode = ColourMode::None;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::None);
}
