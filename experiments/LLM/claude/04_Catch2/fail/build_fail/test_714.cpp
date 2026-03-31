#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_714 : public ::testing::Test {
protected:
    ConfigData makeDefaultData() {
        return ConfigData{};
    }
};

// ===== listTests =====
TEST_F(ConfigTest_714, ListTestsDefaultFalse_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_714, ListTestsSetTrue_714) {
    ConfigData data = makeDefaultData();
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

// ===== listTags =====
TEST_F(ConfigTest_714, ListTagsDefaultFalse_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_714, ListTagsSetTrue_714) {
    ConfigData data = makeDefaultData();
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

// ===== listReporters =====
TEST_F(ConfigTest_714, ListReportersDefaultFalse_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_714, ListReportersSetTrue_714) {
    ConfigData data = makeDefaultData();
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

// ===== listListeners =====
TEST_F(ConfigTest_714, ListListenersDefaultFalse_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_714, ListListenersSetTrue_714) {
    ConfigData data = makeDefaultData();
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

// ===== showHelp =====
TEST_F(ConfigTest_714, ShowHelpDefaultFalse_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_714, ShowHelpSetTrue_714) {
    ConfigData data = makeDefaultData();
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

// ===== allowThrows =====
TEST_F(ConfigTest_714, AllowThrowsDefaultTrue_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    // noThrow defaults to false, so allowThrows should be true
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_714, AllowThrowsFalseWhenNoThrowTrue_714) {
    ConfigData data = makeDefaultData();
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

// ===== includeSuccessfulResults =====
TEST_F(ConfigTest_714, IncludeSuccessfulResultsDefaultFalse_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_714, IncludeSuccessfulResultsSetTrue_714) {
    ConfigData data = makeDefaultData();
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// ===== showInvisibles =====
TEST_F(ConfigTest_714, ShowInvisiblesDefaultFalse_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_714, ShowInvisiblesSetTrue_714) {
    ConfigData data = makeDefaultData();
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

// ===== abortAfter =====
TEST_F(ConfigTest_714, AbortAfterDefault_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_714, AbortAfterCustomValue_714) {
    ConfigData data = makeDefaultData();
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

TEST_F(ConfigTest_714, AbortAfterZero_714) {
    ConfigData data = makeDefaultData();
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

// ===== rngSeed =====
TEST_F(ConfigTest_714, RngSeedCustomValue_714) {
    ConfigData data = makeDefaultData();
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// ===== shardCount =====
TEST_F(ConfigTest_714, ShardCountDefault_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_714, ShardCountCustomValue_714) {
    ConfigData data = makeDefaultData();
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

// ===== shardIndex =====
TEST_F(ConfigTest_714, ShardIndexDefault_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_714, ShardIndexCustomValue_714) {
    ConfigData data = makeDefaultData();
    data.shardIndex = 3;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 3u);
}

// ===== skipBenchmarks =====
TEST_F(ConfigTest_714, SkipBenchmarksDefaultFalse_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_714, SkipBenchmarksSetTrue_714) {
    ConfigData data = makeDefaultData();
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

// ===== benchmarkNoAnalysis =====
TEST_F(ConfigTest_714, BenchmarkNoAnalysisDefaultFalse_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_714, BenchmarkNoAnalysisSetTrue_714) {
    ConfigData data = makeDefaultData();
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

// ===== benchmarkSamples =====
TEST_F(ConfigTest_714, BenchmarkSamplesDefault_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_714, BenchmarkSamplesCustomValue_714) {
    ConfigData data = makeDefaultData();
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

// ===== benchmarkConfidenceInterval =====
TEST_F(ConfigTest_714, BenchmarkConfidenceIntervalDefault_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_714, BenchmarkConfidenceIntervalCustomValue_714) {
    ConfigData data = makeDefaultData();
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

// ===== benchmarkResamples =====
TEST_F(ConfigTest_714, BenchmarkResamplesDefault_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_714, BenchmarkResamplesCustomValue_714) {
    ConfigData data = makeDefaultData();
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

// ===== benchmarkWarmupTime =====
TEST_F(ConfigTest_714, BenchmarkWarmupTimeDefault_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime().count(), 100);
}

TEST_F(ConfigTest_714, BenchmarkWarmupTimeCustomValue_714) {
    ConfigData data = makeDefaultData();
    data.benchmarkWarmupTime = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime().count(), 200);
}

// ===== verbosity =====
TEST_F(ConfigTest_714, VerbosityDefault_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_714, VerbosityHigh_714) {
    ConfigData data = makeDefaultData();
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

TEST_F(ConfigTest_714, VerbosityQuiet_714) {
    ConfigData data = makeDefaultData();
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

// ===== showDurations =====
TEST_F(ConfigTest_714, ShowDurationsDefault_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

TEST_F(ConfigTest_714, ShowDurationsAlways_714) {
    ConfigData data = makeDefaultData();
    data.showDurations = ShowDurations::Always;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Always);
}

TEST_F(ConfigTest_714, ShowDurationsNever_714) {
    ConfigData data = makeDefaultData();
    data.showDurations = ShowDurations::Never;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::Never);
}

// ===== minDuration =====
TEST_F(ConfigTest_714, MinDurationDefault_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_714, MinDurationCustomValue_714) {
    ConfigData data = makeDefaultData();
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

// ===== runOrder =====
TEST_F(ConfigTest_714, RunOrderDefault_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_714, RunOrderRandomized_714) {
    ConfigData data = makeDefaultData();
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

// ===== defaultColourMode =====
TEST_F(ConfigTest_714, DefaultColourModeDefault_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

// ===== zeroTestsCountAsSuccess =====
TEST_F(ConfigTest_714, ZeroTestsCountAsSuccessDefaultFalse_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_714, ZeroTestsCountAsSuccessSetTrue_714) {
    ConfigData data = makeDefaultData();
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

// ===== warnAboutMissingAssertions =====
TEST_F(ConfigTest_714, WarnAboutMissingAssertionsDefault_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

TEST_F(ConfigTest_714, WarnAboutMissingAssertionsEnabled_714) {
    ConfigData data = makeDefaultData();
    data.warnings = static_cast<WarnAbout::What>(
        data.warnings | WarnAbout::NoAssertions);
    Config config(data);
    EXPECT_TRUE(config.warnAboutMissingAssertions());
}

// ===== warnAboutUnmatchedTestSpecs =====
TEST_F(ConfigTest_714, WarnAboutUnmatchedTestSpecsDefault_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    // Default warnings is Nothing, so this should be false
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

// ===== name =====
TEST_F(ConfigTest_714, NameDefaultEmpty_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    // processName defaults to empty
    EXPECT_TRUE(config.name().empty());
}

TEST_F(ConfigTest_714, NameSetProcessName_714) {
    ConfigData data = makeDefaultData();
    data.processName = "MyTestProcess";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("MyTestProcess"));
}

// ===== hasTestFilters =====
TEST_F(ConfigTest_714, HasTestFiltersDefaultFalse_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_714, HasTestFiltersWithTestsOrTags_714) {
    ConfigData data = makeDefaultData();
    data.testsOrTags.push_back("some_test");
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

// ===== getTestsOrTags =====
TEST_F(ConfigTest_714, GetTestsOrTagsDefaultEmpty_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_714, GetTestsOrTagsWithValues_714) {
    ConfigData data = makeDefaultData();
    data.testsOrTags.push_back("test1");
    data.testsOrTags.push_back("[tag1]");
    Config config(data);
    auto const& result = config.getTestsOrTags();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "test1");
    EXPECT_EQ(result[1], "[tag1]");
}

// ===== getSectionsToRun =====
TEST_F(ConfigTest_714, GetSectionsToRunDefaultEmpty_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

TEST_F(ConfigTest_714, GetSectionsToRunWithValues_714) {
    ConfigData data = makeDefaultData();
    data.sectionsToRun.push_back("Section1");
    data.sectionsToRun.push_back("Section2");
    Config config(data);
    auto const& sections = config.getSectionsToRun();
    EXPECT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "Section1");
    EXPECT_EQ(sections[1], "Section2");
}

// ===== shouldDebugBreak =====
TEST_F(ConfigTest_714, ShouldDebugBreakDefaultFalse_714) {
    ConfigData data = makeDefaultData();
    Config config(data);
    EXPECT_FALSE(config.shouldDebugBreak());
}

// ===== libIdentify via filenamesAsTags =====
TEST_F(ConfigTest_714, FilenamesAsTagsDefault_714) {
    ConfigData data = makeDefaultData();
    EXPECT_FALSE(data.filenamesAsTags);
}

TEST_F(ConfigTest_714, LibIdentifyDefault_714) {
    ConfigData data = makeDefaultData();
    EXPECT_FALSE(data.libIdentify);
}

// ===== Default constructed Config =====
TEST_F(ConfigTest_714, DefaultConstructedConfig_714) {
    Config config;
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.listTags());
    EXPECT_FALSE(config.listReporters());
    EXPECT_FALSE(config.listListeners());
    EXPECT_FALSE(config.showHelp());
    EXPECT_TRUE(config.allowThrows());
    EXPECT_FALSE(config.includeSuccessfulResults());
    EXPECT_FALSE(config.showInvisibles());
    EXPECT_FALSE(config.skipBenchmarks());
    EXPECT_FALSE(config.benchmarkNoAnalysis());
    EXPECT_EQ(config.benchmarkSamples(), 100u);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
    EXPECT_EQ(config.abortAfter(), -1);
    EXPECT_EQ(config.shardCount(), 1u);
    EXPECT_EQ(config.shardIndex(), 0u);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

// ===== Multiple boolean flags set simultaneously =====
TEST_F(ConfigTest_714, MultipleFlags_714) {
    ConfigData data = makeDefaultData();
    data.listTests = true;
    data.listTags = true;
    data.listReporters = true;
    data.listListeners = true;
    data.showHelp = true;
    data.noThrow = true;
    data.showSuccessfulTests = true;
    data.showInvisibles = true;
    data.skipBenchmarks = true;
    data.allowZeroTests = true;
    Config config(data);

    EXPECT_TRUE(config.listTests());
    EXPECT_TRUE(config.listTags());
    EXPECT_TRUE(config.listReporters());
    EXPECT_TRUE(config.listListeners());
    EXPECT_TRUE(config.showHelp());
    EXPECT_FALSE(config.allowThrows());
    EXPECT_TRUE(config.includeSuccessfulResults());
    EXPECT_TRUE(config.showInvisibles());
    EXPECT_TRUE(config.skipBenchmarks());
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

// ===== Boundary: benchmarkSamples zero =====
TEST_F(ConfigTest_714, BenchmarkSamplesZero_714) {
    ConfigData data = makeDefaultData();
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

// ===== Boundary: benchmarkWarmupTime zero =====
TEST_F(ConfigTest_714, BenchmarkWarmupTimeZero_714) {
    ConfigData data = makeDefaultData();
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime().count(), 0);
}

// ===== Boundary: minDuration zero =====
TEST_F(ConfigTest_714, MinDurationZero_714) {
    ConfigData data = makeDefaultData();
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

// ===== Boundary: abortAfter large value =====
TEST_F(ConfigTest_714, AbortAfterLargeValue_714) {
    ConfigData data = makeDefaultData();
    data.abortAfter = 999999;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 999999);
}

// ===== Boundary: rngSeed max =====
TEST_F(ConfigTest_714, RngSeedMaxValue_714) {
    ConfigData data = makeDefaultData();
    data.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(data);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

// ===== Boundary: rngSeed zero =====
TEST_F(ConfigTest_714, RngSeedZero_714) {
    ConfigData data = makeDefaultData();
    data.rngSeed = 0;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0u);
}

// ===== Boundary: benchmarkConfidenceInterval zero =====
TEST_F(ConfigTest_714, BenchmarkConfidenceIntervalZero_714) {
    ConfigData data = makeDefaultData();
    data.benchmarkConfidenceInterval = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);
}

// ===== Boundary: benchmarkConfidenceInterval one =====
TEST_F(ConfigTest_714, BenchmarkConfidenceIntervalOne_714) {
    ConfigData data = makeDefaultData();
    data.benchmarkConfidenceInterval = 1.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);
}
