#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_717 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// --- Default ConfigData values ---

TEST_F(ConfigTest_717, DefaultConstruction_ListTestsIsFalse_717) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_717, DefaultConstruction_ListTagsIsFalse_717) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_717, DefaultConstruction_ListReportersIsFalse_717) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_717, DefaultConstruction_ListListenersIsFalse_717) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_717, DefaultConstruction_ShowHelpIsFalse_717) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_717, DefaultConstruction_AllowThrowsIsTrue_717) {
    // noThrow defaults to false, so allowThrows should be true
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_717, DefaultConstruction_IncludeSuccessfulResultsIsFalse_717) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_717, DefaultConstruction_ShowInvisiblesIsFalse_717) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_717, DefaultConstruction_SkipBenchmarksIsFalse_717) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_717, DefaultConstruction_BenchmarkNoAnalysisIsFalse_717) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_717, DefaultConstruction_AbortAfterIsNegativeOne_717) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_717, DefaultConstruction_ShardCountIsOne_717) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_717, DefaultConstruction_ShardIndexIsZero_717) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_717, DefaultConstruction_BenchmarkSamplesIs100_717) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_717, DefaultConstruction_BenchmarkConfidenceInterval_717) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_717, DefaultConstruction_BenchmarkResamplesIs100000_717) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_717, DefaultConstruction_BenchmarkWarmupTime_717) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_717, DefaultConstruction_VerbosityIsNormal_717) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_717, DefaultConstruction_RunOrderIsDeclared_717) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_717, DefaultConstruction_DefaultColourModeIsPlatformDefault_717) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

TEST_F(ConfigTest_717, DefaultConstruction_MinDurationIsNegativeOne_717) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_717, DefaultConstruction_ShowDurationsIsDefault_717) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_717, DefaultConstruction_ZeroTestsCountAsSuccessIsFalse_717) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_717, DefaultConstruction_WarnAboutMissingAssertionsIsFalse_717) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_717, DefaultConstruction_WarnAboutUnmatchedTestSpecsIsFalse_717) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

TEST_F(ConfigTest_717, DefaultConstruction_HasTestFiltersIsFalse_717) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_717, DefaultConstruction_GetTestsOrTagsIsEmpty_717) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_717, DefaultConstruction_GetSectionsToRunIsEmpty_717) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// --- Custom ConfigData values ---

TEST_F(ConfigTest_717, CustomData_ListTestsTrue_717) {
    defaultData.listTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTests());
}

TEST_F(ConfigTest_717, CustomData_ListTagsTrue_717) {
    defaultData.listTags = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listTags());
}

TEST_F(ConfigTest_717, CustomData_ListReportersTrue_717) {
    defaultData.listReporters = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listReporters());
}

TEST_F(ConfigTest_717, CustomData_ListListenersTrue_717) {
    defaultData.listListeners = true;
    Config config(defaultData);
    EXPECT_TRUE(config.listListeners());
}

TEST_F(ConfigTest_717, CustomData_ShowHelpTrue_717) {
    defaultData.showHelp = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showHelp());
}

TEST_F(ConfigTest_717, CustomData_NoThrowTrue_AllowThrowsFalse_717) {
    defaultData.noThrow = true;
    Config config(defaultData);
    EXPECT_FALSE(config.allowThrows());
}

TEST_F(ConfigTest_717, CustomData_ShowSuccessfulTestsTrue_717) {
    defaultData.showSuccessfulTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_717, CustomData_ShowInvisiblesTrue_717) {
    defaultData.showInvisibles = true;
    Config config(defaultData);
    EXPECT_TRUE(config.showInvisibles());
}

TEST_F(ConfigTest_717, CustomData_SkipBenchmarksTrue_717) {
    defaultData.skipBenchmarks = true;
    Config config(defaultData);
    EXPECT_TRUE(config.skipBenchmarks());
}

TEST_F(ConfigTest_717, CustomData_BenchmarkNoAnalysisTrue_717) {
    defaultData.benchmarkNoAnalysis = true;
    Config config(defaultData);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_717, CustomData_AbortAfterCustomValue_717) {
    defaultData.abortAfter = 5;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_717, CustomData_ShardCountCustomValue_717) {
    defaultData.shardCount = 4;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 4u);
}

TEST_F(ConfigTest_717, CustomData_ShardIndexCustomValue_717) {
    defaultData.shardIndex = 2;
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 2u);
}

TEST_F(ConfigTest_717, CustomData_BenchmarkSamplesCustomValue_717) {
    defaultData.benchmarkSamples = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

TEST_F(ConfigTest_717, CustomData_BenchmarkConfidenceIntervalCustomValue_717) {
    defaultData.benchmarkConfidenceInterval = 0.99;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

TEST_F(ConfigTest_717, CustomData_BenchmarkResamplesCustomValue_717) {
    defaultData.benchmarkResamples = 200000;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 200000u);
}

TEST_F(ConfigTest_717, CustomData_BenchmarkWarmupTimeCustomValue_717) {
    defaultData.benchmarkWarmupTime = 500;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

TEST_F(ConfigTest_717, CustomData_VerbosityHigh_717) {
    defaultData.verbosity = Verbosity::High;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_717, CustomData_VerbosityQuiet_717) {
    defaultData.verbosity = Verbosity::Quiet;
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

TEST_F(ConfigTest_717, CustomData_RunOrderRandomize_717) {
    defaultData.runOrder = TestRunOrder::Randomized;
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

TEST_F(ConfigTest_717, CustomData_MinDurationCustomValue_717) {
    defaultData.minDuration = 0.5;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

TEST_F(ConfigTest_717, CustomData_ShowDurationsAlways_717) {
    defaultData.showDurations = ShowDurations::Always;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_717, CustomData_ShowDurationsNever_717) {
    defaultData.showDurations = ShowDurations::Never;
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

TEST_F(ConfigTest_717, CustomData_AllowZeroTestsTrue_717) {
    defaultData.allowZeroTests = true;
    Config config(defaultData);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_717, CustomData_ProcessName_717) {
    defaultData.processName = "myTestProcess";
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef("myTestProcess"));
}

TEST_F(ConfigTest_717, CustomData_ProcessNameEmpty_717) {
    defaultData.processName = "";
    Config config(defaultData);
    EXPECT_EQ(config.name(), StringRef(""));
}

TEST_F(ConfigTest_717, CustomData_RngSeedCustomValue_717) {
    defaultData.rngSeed = 42;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// --- Sections and Tests/Tags ---

TEST_F(ConfigTest_717, CustomData_SectionsToRunSingleSection_717) {
    defaultData.sectionsToRun = {"section1"};
    Config config(defaultData);
    auto const& sections = config.getSectionsToRun();
    ASSERT_EQ(sections.size(), 1u);
    EXPECT_EQ(sections[0], "section1");
}

TEST_F(ConfigTest_717, CustomData_SectionsToRunMultipleSections_717) {
    defaultData.sectionsToRun = {"section1", "section2", "section3"};
    Config config(defaultData);
    auto const& sections = config.getSectionsToRun();
    ASSERT_EQ(sections.size(), 3u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
    EXPECT_EQ(sections[2], "section3");
}

TEST_F(ConfigTest_717, CustomData_TestsOrTagsSingleEntry_717) {
    defaultData.testsOrTags = {"[tag1]"};
    Config config(defaultData);
    auto const& testsOrTags = config.getTestsOrTags();
    ASSERT_EQ(testsOrTags.size(), 1u);
    EXPECT_EQ(testsOrTags[0], "[tag1]");
}

TEST_F(ConfigTest_717, CustomData_TestsOrTagsMultipleEntries_717) {
    defaultData.testsOrTags = {"test1", "[tag1]", "test2"};
    Config config(defaultData);
    auto const& testsOrTags = config.getTestsOrTags();
    ASSERT_EQ(testsOrTags.size(), 3u);
    EXPECT_EQ(testsOrTags[0], "test1");
    EXPECT_EQ(testsOrTags[1], "[tag1]");
    EXPECT_EQ(testsOrTags[2], "test2");
}

TEST_F(ConfigTest_717, CustomData_TestsOrTagsNonEmpty_HasTestFilters_717) {
    defaultData.testsOrTags = {"someTest"};
    Config config(defaultData);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_717, CustomData_TestSpecNotNull_717) {
    Config config(defaultData);
    // Just verify we can call testSpec without crashing
    auto const& spec = config.testSpec();
    (void)spec;
}

// --- Boundary conditions ---

TEST_F(ConfigTest_717, BoundaryCondition_AbortAfterZero_717) {
    defaultData.abortAfter = 0;
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), 0);
}

TEST_F(ConfigTest_717, BoundaryCondition_MinDurationZero_717) {
    defaultData.minDuration = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

TEST_F(ConfigTest_717, BoundaryCondition_BenchmarkSamplesOne_717) {
    defaultData.benchmarkSamples = 1;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 1u);
}

TEST_F(ConfigTest_717, BoundaryCondition_BenchmarkWarmupTimeZero_717) {
    defaultData.benchmarkWarmupTime = 0;
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

TEST_F(ConfigTest_717, BoundaryCondition_BenchmarkConfidenceIntervalZero_717) {
    defaultData.benchmarkConfidenceInterval = 0.0;
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

TEST_F(ConfigTest_717, BoundaryCondition_RngSeedZero_717) {
    defaultData.rngSeed = 0;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 0u);
}

TEST_F(ConfigTest_717, BoundaryCondition_RngSeedMax_717) {
    defaultData.rngSeed = UINT32_MAX;
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), UINT32_MAX);
}

TEST_F(ConfigTest_717, BoundaryCondition_EmptyProcessName_717) {
    defaultData.processName = "";
    Config config(defaultData);
    EXPECT_TRUE(config.name().empty());
}

TEST_F(ConfigTest_717, BoundaryCondition_LargeShardCount_717) {
    defaultData.shardCount = 1000;
    defaultData.shardIndex = 999;
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1000u);
    EXPECT_EQ(config.shardIndex(), 999u);
}

// --- ColourMode ---

TEST_F(ConfigTest_717, CustomData_ColourModeAnsi_717) {
    defaultData.defaultColourMode = ColourMode::ANSI;
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

TEST_F(ConfigTest_717, CustomData_ColourModeNone_717) {
    defaultData.defaultColourMode = ColourMode::None;
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::None);
}

// --- Reporter specs ---

TEST_F(ConfigTest_717, DefaultConstruction_GetReporterSpecsEmpty_717) {
    Config config(defaultData);
    // With no reporter specs set, the returned vector should still be valid
    auto const& specs = config.getReporterSpecs();
    // Default may or may not be empty depending on implementation, but it shouldn't crash
    (void)specs;
}

TEST_F(ConfigTest_717, DefaultConstruction_GetProcessedReporterSpecsValid_717) {
    Config config(defaultData);
    auto const& processed = config.getProcessedReporterSpecs();
    (void)processed;
}

// --- Multiple configs from same ConfigData ---

TEST_F(ConfigTest_717, MultipleConfigsFromSameData_717) {
    defaultData.abortAfter = 3;
    defaultData.showHelp = true;
    defaultData.processName = "test";
    
    Config config1(defaultData);
    Config config2(defaultData);
    
    EXPECT_EQ(config1.abortAfter(), config2.abortAfter());
    EXPECT_EQ(config1.showHelp(), config2.showHelp());
    EXPECT_EQ(config1.name(), config2.name());
}

// --- ShouldDebugBreak default ---

TEST_F(ConfigTest_717, DefaultConstruction_ShouldDebugBreakIsFalse_717) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}
