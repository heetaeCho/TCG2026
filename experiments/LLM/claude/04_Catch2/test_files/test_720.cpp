#include "catch2/catch_config.hpp"
#include "catch2/catch_test_spec.hpp"
#include "catch2/internal/catch_test_spec_parser.hpp"
#include <gtest/gtest.h>
#include <chrono>
#include <string>
#include <vector>

using namespace Catch;

class ConfigTest_720 : public ::testing::Test {
protected:
    ConfigData makeDefaultData() {
        ConfigData data;
        return data;
    }
};

// Test default construction with default ConfigData
TEST_F(ConfigTest_720, DefaultConstruction_720) {
    ConfigData data;
    Config config(data);
    // Should not throw and should be constructible
    SUCCEED();
}

// Test listTests returns expected default value
TEST_F(ConfigTest_720, ListTestsDefaultFalse_720) {
    ConfigData data;
    data.listTests = false;
    Config config(data);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_720, ListTestsTrue_720) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

// Test listTags returns expected default value
TEST_F(ConfigTest_720, ListTagsDefaultFalse_720) {
    ConfigData data;
    data.listTags = false;
    Config config(data);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_720, ListTagsTrue_720) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

// Test listReporters returns expected default value
TEST_F(ConfigTest_720, ListReportersDefaultFalse_720) {
    ConfigData data;
    data.listReporters = false;
    Config config(data);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_720, ListReportersTrue_720) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

// Test listListeners
TEST_F(ConfigTest_720, ListListenersDefaultFalse_720) {
    ConfigData data;
    data.listListeners = false;
    Config config(data);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_720, ListListenersTrue_720) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

// Test showHelp
TEST_F(ConfigTest_720, ShowHelpDefaultFalse_720) {
    ConfigData data;
    data.showHelp = false;
    Config config(data);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_720, ShowHelpTrue_720) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

// Test allowThrows
TEST_F(ConfigTest_720, AllowThrowsDefault_720) {
    ConfigData data;
    Config config(data);
    // Default should allow throws
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_720, AllowThrowsFalse_720) {
    ConfigData data;
    data.allowThrows = false;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

// Test name
TEST_F(ConfigTest_720, NameDefault_720) {
    ConfigData data;
    Config config(data);
    // Default name should be empty
    EXPECT_TRUE(config.name().empty());
}

TEST_F(ConfigTest_720, NameSet_720) {
    ConfigData data;
    data.name = "MyTestRun";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("MyTestRun"));
}

// Test includeSuccessfulResults
TEST_F(ConfigTest_720, IncludeSuccessfulResultsDefaultFalse_720) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_720, IncludeSuccessfulResultsTrue_720) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// Test warnAboutMissingAssertions
TEST_F(ConfigTest_720, WarnAboutMissingAssertionsDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

// Test warnAboutUnmatchedTestSpecs
TEST_F(ConfigTest_720, WarnAboutUnmatchedTestSpecsDefault_720) {
    ConfigData data;
    Config config(data);
    // Default should be true
    EXPECT_TRUE(config.warnAboutUnmatchedTestSpecs());
}

// Test zeroTestsCountAsSuccess
TEST_F(ConfigTest_720, ZeroTestsCountAsSuccessDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

// Test showDurations
TEST_F(ConfigTest_720, ShowDurationsDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_720, ShowDurationsAlways_720) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_720, ShowDurationsNever_720) {
    ConfigData data;
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

// Test minDuration
TEST_F(ConfigTest_720, MinDurationDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_720, MinDurationSet_720) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

// Test runOrder
TEST_F(ConfigTest_720, RunOrderDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_720, RunOrderRandomized_720) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

// Test rngSeed
TEST_F(ConfigTest_720, RngSeedDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0u);
}

TEST_F(ConfigTest_720, RngSeedSet_720) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// Test shardCount
TEST_F(ConfigTest_720, ShardCountDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_720, ShardCountSet_720) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

// Test shardIndex
TEST_F(ConfigTest_720, ShardIndexDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_720, ShardIndexSet_720) {
    ConfigData data;
    data.shardIndex = 2;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 2u);
}

// Test shouldDebugBreak
TEST_F(ConfigTest_720, ShouldDebugBreakDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.shouldDebugBreak());
}

TEST_F(ConfigTest_720, ShouldDebugBreakTrue_720) {
    ConfigData data;
    data.shouldDebugBreak = true;
    Config config(data);
    EXPECT_TRUE(config.shouldDebugBreak());
}

// Test abortAfter
TEST_F(ConfigTest_720, AbortAfterDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_720, AbortAfterSet_720) {
    ConfigData data;
    data.abortAfter = 3;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 3);
}

// Test showInvisibles
TEST_F(ConfigTest_720, ShowInvisiblesDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_720, ShowInvisiblesTrue_720) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

// Test verbosity
TEST_F(ConfigTest_720, VerbosityDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_720, VerbosityHigh_720) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_720, VerbosityQuiet_720) {
    ConfigData data;
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

// Test skipBenchmarks
TEST_F(ConfigTest_720, SkipBenchmarksDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_720, SkipBenchmarksTrue_720) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

// Test benchmarkNoAnalysis
TEST_F(ConfigTest_720, BenchmarkNoAnalysisDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_720, BenchmarkNoAnalysisTrue_720) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

// Test benchmarkSamples
TEST_F(ConfigTest_720, BenchmarkSamplesDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_720, BenchmarkSamplesSet_720) {
    ConfigData data;
    data.benchmarkSamples = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 200u);
}

// Test benchmarkConfidenceInterval
TEST_F(ConfigTest_720, BenchmarkConfidenceIntervalDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_720, BenchmarkConfidenceIntervalSet_720) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

// Test benchmarkResamples
TEST_F(ConfigTest_720, BenchmarkResamplesDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_720, BenchmarkResamplesSet_720) {
    ConfigData data;
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

// Test benchmarkWarmupTime
TEST_F(ConfigTest_720, BenchmarkWarmupTimeDefault_720) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_720, BenchmarkWarmupTimeSet_720) {
    ConfigData data;
    data.benchmarkWarmupTime = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

// Test getTestsOrTags
TEST_F(ConfigTest_720, GetTestsOrTagsEmpty_720) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_720, GetTestsOrTagsWithFilters_720) {
    ConfigData data;
    data.testsOrTags.push_back("TestA");
    data.testsOrTags.push_back("[tagB]");
    Config config(data);
    auto const& result = config.getTestsOrTags();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "TestA");
    EXPECT_EQ(result[1], "[tagB]");
}

// Test getSectionsToRun
TEST_F(ConfigTest_720, GetSectionsToRunEmpty_720) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

TEST_F(ConfigTest_720, GetSectionsToRunWithSections_720) {
    ConfigData data;
    data.sectionsToRun.push_back("SectionA");
    data.sectionsToRun.push_back("SectionB");
    Config config(data);
    auto const& sections = config.getSectionsToRun();
    EXPECT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "SectionA");
    EXPECT_EQ(sections[1], "SectionB");
}

// Test hasTestFilters
TEST_F(ConfigTest_720, HasTestFiltersDefaultFalse_720) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_720, HasTestFiltersWithTestSpec_720) {
    ConfigData data;
    data.testsOrTags.push_back("SomeTest");
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

// Test testSpec returns a valid reference
TEST_F(ConfigTest_720, TestSpecReturnsValidReference_720) {
    ConfigData data;
    Config config(data);
    TestSpec const& spec = config.testSpec();
    // With no filters, the test spec should have no filters
    EXPECT_TRUE(spec.hasFilters() == false);
}

TEST_F(ConfigTest_720, TestSpecWithFilters_720) {
    ConfigData data;
    data.testsOrTags.push_back("SomeTestName");
    Config config(data);
    TestSpec const& spec = config.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

// Test defaultColourMode
TEST_F(ConfigTest_720, DefaultColourModeDefault_720) {
    ConfigData data;
    Config config(data);
    // Default should be PlatformDefault
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

// Test getReporterSpecs
TEST_F(ConfigTest_720, GetReporterSpecsDefault_720) {
    ConfigData data;
    Config config(data);
    auto const& specs = config.getReporterSpecs();
    // Default should have at least one reporter spec (console reporter)
    EXPECT_GE(specs.size(), 1u);
}

// Test getProcessedReporterSpecs
TEST_F(ConfigTest_720, GetProcessedReporterSpecsDefault_720) {
    ConfigData data;
    Config config(data);
    auto const& pSpecs = config.getProcessedReporterSpecs();
    EXPECT_GE(pSpecs.size(), 1u);
}

// Test boundary: abortAfter with zero
TEST_F(ConfigTest_720, AbortAfterZero_720) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

// Test boundary: rngSeed max value
TEST_F(ConfigTest_720, RngSeedMaxValue_720) {
    ConfigData data;
    data.rngSeed = 0xFFFFFFFF;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0xFFFFFFFF);
}

// Test boundary: benchmarkSamples zero
TEST_F(ConfigTest_720, BenchmarkSamplesZero_720) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

// Test boundary: minDuration zero
TEST_F(ConfigTest_720, MinDurationZero_720) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

// Test boundary: benchmarkConfidenceInterval boundary
TEST_F(ConfigTest_720, BenchmarkConfidenceIntervalZero_720) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

// Test boundary: benchmarkWarmupTime zero
TEST_F(ConfigTest_720, BenchmarkWarmupTimeZero_720) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

// Test that empty name returns empty StringRef
TEST_F(ConfigTest_720, EmptyNameReturnsEmpty_720) {
    ConfigData data;
    data.name = "";
    Config config(data);
    EXPECT_TRUE(config.name().empty());
}

// Test multiple test filters
TEST_F(ConfigTest_720, MultipleTestFilters_720) {
    ConfigData data;
    data.testsOrTags.push_back("Test1");
    data.testsOrTags.push_back("Test2");
    data.testsOrTags.push_back("[tag1]");
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
    EXPECT_EQ(config.getTestsOrTags().size(), 3u);
}
