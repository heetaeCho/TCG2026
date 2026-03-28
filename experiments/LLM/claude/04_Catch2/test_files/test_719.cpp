#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"
#include "catch2/catch_test_spec.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"

#include <vector>
#include <string>
#include <chrono>

using namespace Catch;

class ConfigTest_719 : public ::testing::Test {
protected:
    ConfigData defaultData;
    
    void SetUp() override {
        // defaultData is default-constructed
    }
};

// Test default construction
TEST_F(ConfigTest_719, DefaultConstruction_719) {
    Config config;
    // Should not crash; basic construction works
}

TEST_F(ConfigTest_719, ConstructionWithDefaultConfigData_719) {
    Config config(defaultData);
    // Should construct without issues
}

// Test listTests with default config data
TEST_F(ConfigTest_719, ListTestsDefaultFalse_719) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTests());
}

// Test listTags with default config data
TEST_F(ConfigTest_719, ListTagsDefaultFalse_719) {
    Config config(defaultData);
    EXPECT_FALSE(config.listTags());
}

// Test listReporters with default config data
TEST_F(ConfigTest_719, ListReportersDefaultFalse_719) {
    Config config(defaultData);
    EXPECT_FALSE(config.listReporters());
}

// Test listListeners with default config data
TEST_F(ConfigTest_719, ListListenersDefaultFalse_719) {
    Config config(defaultData);
    EXPECT_FALSE(config.listListeners());
}

// Test showHelp with default config data
TEST_F(ConfigTest_719, ShowHelpDefaultFalse_719) {
    Config config(defaultData);
    EXPECT_FALSE(config.showHelp());
}

// Test allowThrows with default config data
TEST_F(ConfigTest_719, AllowThrowsDefaultTrue_719) {
    Config config(defaultData);
    EXPECT_TRUE(config.allowThrows());
}

// Test setting allowThrows to false via noThrow
TEST_F(ConfigTest_719, AllowThrowsWhenNoThrowSet_719) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

// Test name with default config data
TEST_F(ConfigTest_719, NameDefaultEmpty_719) {
    Config config(defaultData);
    EXPECT_TRUE(config.name().empty());
}

// Test name with custom name
TEST_F(ConfigTest_719, NameWithCustomValue_719) {
    ConfigData data;
    data.name = "MyTestRun";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("MyTestRun"));
}

// Test includeSuccessfulResults default
TEST_F(ConfigTest_719, IncludeSuccessfulResultsDefaultFalse_719) {
    Config config(defaultData);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

// Test includeSuccessfulResults when set
TEST_F(ConfigTest_719, IncludeSuccessfulResultsWhenSet_719) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// Test warnAboutMissingAssertions default
TEST_F(ConfigTest_719, WarnAboutMissingAssertionsDefault_719) {
    Config config(defaultData);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

// Test warnAboutUnmatchedTestSpecs default
TEST_F(ConfigTest_719, WarnAboutUnmatchedTestSpecsDefault_719) {
    Config config(defaultData);
    EXPECT_TRUE(config.warnAboutUnmatchedTestSpecs());
}

// Test zeroTestsCountAsSuccess default
TEST_F(ConfigTest_719, ZeroTestsCountAsSuccessDefault_719) {
    Config config(defaultData);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

// Test showDurations default
TEST_F(ConfigTest_719, ShowDurationsDefault_719) {
    Config config(defaultData);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

// Test minDuration default
TEST_F(ConfigTest_719, MinDurationDefault_719) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

// Test runOrder default
TEST_F(ConfigTest_719, RunOrderDefault_719) {
    Config config(defaultData);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

// Test rngSeed default
TEST_F(ConfigTest_719, RngSeedDefault_719) {
    Config config(defaultData);
    EXPECT_EQ(config.rngSeed(), 0u);
}

// Test rngSeed with custom value
TEST_F(ConfigTest_719, RngSeedCustomValue_719) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// Test shardCount default
TEST_F(ConfigTest_719, ShardCountDefault_719) {
    Config config(defaultData);
    EXPECT_EQ(config.shardCount(), 1u);
}

// Test shardIndex default
TEST_F(ConfigTest_719, ShardIndexDefault_719) {
    Config config(defaultData);
    EXPECT_EQ(config.shardIndex(), 0u);
}

// Test shardCount with custom value
TEST_F(ConfigTest_719, ShardCountCustom_719) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

// Test shardIndex with custom value
TEST_F(ConfigTest_719, ShardIndexCustom_719) {
    ConfigData data;
    data.shardIndex = 2;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 2u);
}

// Test defaultColourMode default
TEST_F(ConfigTest_719, DefaultColourModeDefault_719) {
    Config config(defaultData);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

// Test shouldDebugBreak default
TEST_F(ConfigTest_719, ShouldDebugBreakDefault_719) {
    Config config(defaultData);
    EXPECT_FALSE(config.shouldDebugBreak());
}

// Test shouldDebugBreak when set
TEST_F(ConfigTest_719, ShouldDebugBreakWhenSet_719) {
    ConfigData data;
    data.shouldDebugBreak = true;
    Config config(data);
    EXPECT_TRUE(config.shouldDebugBreak());
}

// Test abortAfter default
TEST_F(ConfigTest_719, AbortAfterDefault_719) {
    Config config(defaultData);
    EXPECT_EQ(config.abortAfter(), -1);
}

// Test abortAfter with custom value
TEST_F(ConfigTest_719, AbortAfterCustom_719) {
    ConfigData data;
    data.abortAfter = 3;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 3);
}

// Test showInvisibles default
TEST_F(ConfigTest_719, ShowInvisiblesDefault_719) {
    Config config(defaultData);
    EXPECT_FALSE(config.showInvisibles());
}

// Test showInvisibles when set
TEST_F(ConfigTest_719, ShowInvisiblesWhenSet_719) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

// Test verbosity default
TEST_F(ConfigTest_719, VerbosityDefault_719) {
    Config config(defaultData);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

// Test verbosity with custom value
TEST_F(ConfigTest_719, VerbosityHigh_719) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

// Test skipBenchmarks default
TEST_F(ConfigTest_719, SkipBenchmarksDefault_719) {
    Config config(defaultData);
    EXPECT_FALSE(config.skipBenchmarks());
}

// Test skipBenchmarks when set
TEST_F(ConfigTest_719, SkipBenchmarksWhenSet_719) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

// Test benchmarkNoAnalysis default
TEST_F(ConfigTest_719, BenchmarkNoAnalysisDefault_719) {
    Config config(defaultData);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

// Test benchmarkSamples default
TEST_F(ConfigTest_719, BenchmarkSamplesDefault_719) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

// Test benchmarkSamples with custom value
TEST_F(ConfigTest_719, BenchmarkSamplesCustom_719) {
    ConfigData data;
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

// Test benchmarkConfidenceInterval default
TEST_F(ConfigTest_719, BenchmarkConfidenceIntervalDefault_719) {
    Config config(defaultData);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

// Test benchmarkConfidenceInterval with custom value
TEST_F(ConfigTest_719, BenchmarkConfidenceIntervalCustom_719) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

// Test benchmarkResamples default
TEST_F(ConfigTest_719, BenchmarkResamplesDefault_719) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

// Test benchmarkResamples with custom value
TEST_F(ConfigTest_719, BenchmarkResamplesCustom_719) {
    ConfigData data;
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

// Test benchmarkWarmupTime default
TEST_F(ConfigTest_719, BenchmarkWarmupTimeDefault_719) {
    Config config(defaultData);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

// Test benchmarkWarmupTime with custom value
TEST_F(ConfigTest_719, BenchmarkWarmupTimeCustom_719) {
    ConfigData data;
    data.benchmarkWarmupTime = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

// Test getTestsOrTags with default (empty)
TEST_F(ConfigTest_719, GetTestsOrTagsDefaultEmpty_719) {
    Config config(defaultData);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

// Test getTestsOrTags with custom values
TEST_F(ConfigTest_719, GetTestsOrTagsWithValues_719) {
    ConfigData data;
    data.testsOrTags = {"test1", "[tag1]"};
    Config config(data);
    auto const& testsOrTags = config.getTestsOrTags();
    EXPECT_EQ(testsOrTags.size(), 2u);
    EXPECT_EQ(testsOrTags[0], "test1");
    EXPECT_EQ(testsOrTags[1], "[tag1]");
}

// Test getSectionsToRun default
TEST_F(ConfigTest_719, GetSectionsToRunDefaultEmpty_719) {
    Config config(defaultData);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// Test getSectionsToRun with custom values
TEST_F(ConfigTest_719, GetSectionsToRunWithValues_719) {
    ConfigData data;
    data.sectionsToRun = {"section1", "section2"};
    Config config(data);
    auto const& sections = config.getSectionsToRun();
    EXPECT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "section1");
    EXPECT_EQ(sections[1], "section2");
}

// Test hasTestFilters with no filters
TEST_F(ConfigTest_719, HasTestFiltersDefaultFalse_719) {
    Config config(defaultData);
    EXPECT_FALSE(config.hasTestFilters());
}

// Test hasTestFilters with filters
TEST_F(ConfigTest_719, HasTestFiltersWhenTestsSpecified_719) {
    ConfigData data;
    data.testsOrTags = {"some_test"};
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

// Test testSpec returns a valid reference
TEST_F(ConfigTest_719, TestSpecReturnsReference_719) {
    Config config(defaultData);
    auto const& spec = config.testSpec();
    // Default test spec should match everything (no filters applied)
    EXPECT_TRUE(spec.hasFilters() == false);
}

// Test getProcessedReporterSpecs returns a reference
TEST_F(ConfigTest_719, GetProcessedReporterSpecsReturnsReference_719) {
    Config config(defaultData);
    auto const& specs = config.getProcessedReporterSpecs();
    // Default should have at least one reporter spec (the default reporter)
    // or could be empty depending on defaults; just verify it doesn't crash
    (void)specs;
}

// Test getReporterSpecs returns a reference
TEST_F(ConfigTest_719, GetReporterSpecsReturnsReference_719) {
    Config config(defaultData);
    auto const& specs = config.getReporterSpecs();
    (void)specs;
}

// Test runOrder with randomize
TEST_F(ConfigTest_719, RunOrderRandomize_719) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

// Test showDurations always
TEST_F(ConfigTest_719, ShowDurationsAlways_719) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

// Test showDurations never
TEST_F(ConfigTest_719, ShowDurationsNever_719) {
    ConfigData data;
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

// Test minDuration with custom value
TEST_F(ConfigTest_719, MinDurationCustom_719) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

// Test colourMode with ANSI
TEST_F(ConfigTest_719, ColourModeAnsi_719) {
    ConfigData data;
    data.defaultColourMode = ColourMode::ANSI;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::ANSI);
}

// Test colourMode with None
TEST_F(ConfigTest_719, ColourModeNone_719) {
    ConfigData data;
    data.defaultColourMode = ColourMode::None;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::None);
}

// Test warnAboutMissingAssertions when set
TEST_F(ConfigTest_719, WarnAboutMissingAssertionsWhenSet_719) {
    ConfigData data;
    data.warnings = static_cast<WarnAbout::What>(WarnAbout::NoAssertions);
    Config config(data);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

// Test verbosity quiet
TEST_F(ConfigTest_719, VerbosityQuiet_719) {
    ConfigData data;
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

// Test listTests when set
TEST_F(ConfigTest_719, ListTestsWhenSet_719) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

// Test listTags when set
TEST_F(ConfigTest_719, ListTagsWhenSet_719) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

// Test listReporters when set
TEST_F(ConfigTest_719, ListReportersWhenSet_719) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

// Test listListeners when set
TEST_F(ConfigTest_719, ListListenersWhenSet_719) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

// Test showHelp when set
TEST_F(ConfigTest_719, ShowHelpWhenSet_719) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

// Test benchmarkNoAnalysis when set
TEST_F(ConfigTest_719, BenchmarkNoAnalysisWhenSet_719) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

// Test boundary: abortAfter = 0
TEST_F(ConfigTest_719, AbortAfterZero_719) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

// Test boundary: benchmarkSamples = 0
TEST_F(ConfigTest_719, BenchmarkSamplesZero_719) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

// Test boundary: benchmarkResamples = 0
TEST_F(ConfigTest_719, BenchmarkResamplesZero_719) {
    ConfigData data;
    data.benchmarkResamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 0u);
}

// Test boundary: benchmarkWarmupTime = 0
TEST_F(ConfigTest_719, BenchmarkWarmupTimeZero_719) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

// Test boundary: empty name
TEST_F(ConfigTest_719, EmptyName_719) {
    ConfigData data;
    data.name = "";
    Config config(data);
    EXPECT_TRUE(config.name().empty());
}

// Test boundary: large rng seed
TEST_F(ConfigTest_719, LargeRngSeed_719) {
    ConfigData data;
    data.rngSeed = UINT32_MAX;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), UINT32_MAX);
}

// Test that getProcessedReporterSpecs and getReporterSpecs return consistent size
TEST_F(ConfigTest_719, ProcessedAndRawReporterSpecsSameSize_719) {
    Config config(defaultData);
    auto const& rawSpecs = config.getReporterSpecs();
    auto const& processedSpecs = config.getProcessedReporterSpecs();
    EXPECT_EQ(rawSpecs.size(), processedSpecs.size());
}

// Test zeroTestsCountAsSuccess when set
TEST_F(ConfigTest_719, ZeroTestsCountAsSuccessWhenSet_719) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}
