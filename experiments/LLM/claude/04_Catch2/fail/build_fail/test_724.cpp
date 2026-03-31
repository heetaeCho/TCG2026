#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_724 : public ::testing::Test {
protected:
    ConfigData defaultData;
};

// ===== name() tests =====

TEST_F(ConfigTest_724, NameReturnsProcessNameWhenNameIsEmpty_724) {
    ConfigData data;
    data.processName = "myProcess";
    data.name = "";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("myProcess"));
}

TEST_F(ConfigTest_724, NameReturnsNameWhenNameIsSet_724) {
    ConfigData data;
    data.processName = "myProcess";
    data.name = "myTestName";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef("myTestName"));
}

TEST_F(ConfigTest_724, NameReturnEmptyWhenBothEmpty_724) {
    ConfigData data;
    data.processName = "";
    data.name = "";
    Config config(data);
    EXPECT_EQ(config.name(), StringRef(""));
}

// ===== listTests() tests =====

TEST_F(ConfigTest_724, ListTestsDefaultFalse_724) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_724, ListTestsTrueWhenSet_724) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

// ===== listTags() tests =====

TEST_F(ConfigTest_724, ListTagsDefaultFalse_724) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_724, ListTagsTrueWhenSet_724) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

// ===== listReporters() tests =====

TEST_F(ConfigTest_724, ListReportersDefaultFalse_724) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_724, ListReportersTrueWhenSet_724) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

// ===== listListeners() tests =====

TEST_F(ConfigTest_724, ListListenersDefaultFalse_724) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_724, ListListenersTrueWhenSet_724) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

// ===== showHelp() tests =====

TEST_F(ConfigTest_724, ShowHelpDefaultFalse_724) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_724, ShowHelpTrueWhenSet_724) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

// ===== allowThrows() tests =====

TEST_F(ConfigTest_724, AllowThrowsDefaultTrue_724) {
    ConfigData data;
    Config config(data);
    // noThrow defaults to false, so allowThrows should be true
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_724, AllowThrowsFalseWhenNoThrowSet_724) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

// ===== includeSuccessfulResults() tests =====

TEST_F(ConfigTest_724, IncludeSuccessfulResultsDefaultFalse_724) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_724, IncludeSuccessfulResultsTrueWhenSet_724) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// ===== warnAboutMissingAssertions() tests =====

TEST_F(ConfigTest_724, WarnAboutMissingAssertionsDefaultFalse_724) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

// ===== zeroTestsCountAsSuccess() tests =====

TEST_F(ConfigTest_724, ZeroTestsCountAsSuccessDefaultFalse_724) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_724, ZeroTestsCountAsSuccessTrueWhenSet_724) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

// ===== abortAfter() tests =====

TEST_F(ConfigTest_724, AbortAfterDefaultNegativeOne_724) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_724, AbortAfterReturnsSetValue_724) {
    ConfigData data;
    data.abortAfter = 5;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 5);
}

// ===== showDurations() tests =====

TEST_F(ConfigTest_724, ShowDurationsDefault_724) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

// ===== minDuration() tests =====

TEST_F(ConfigTest_724, MinDurationDefault_724) {
    ConfigData data;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_724, MinDurationReturnsSetValue_724) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

// ===== runOrder() tests =====

TEST_F(ConfigTest_724, RunOrderDefaultDeclared_724) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_724, RunOrderRandomized_724) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

// ===== rngSeed() tests =====

TEST_F(ConfigTest_724, RngSeedReturnsSetValue_724) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// ===== shardCount() tests =====

TEST_F(ConfigTest_724, ShardCountDefaultOne_724) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_724, ShardCountReturnsSetValue_724) {
    ConfigData data;
    data.shardCount = 4;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 4u);
}

// ===== shardIndex() tests =====

TEST_F(ConfigTest_724, ShardIndexDefaultZero_724) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_724, ShardIndexReturnsSetValue_724) {
    ConfigData data;
    data.shardIndex = 3;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 3u);
}

// ===== defaultColourMode() tests =====

TEST_F(ConfigTest_724, DefaultColourModeDefault_724) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

// ===== showInvisibles() tests =====

TEST_F(ConfigTest_724, ShowInvisiblesDefaultFalse_724) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_724, ShowInvisiblesTrueWhenSet_724) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

// ===== verbosity() tests =====

TEST_F(ConfigTest_724, VerbosityDefaultNormal_724) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_724, VerbosityReturnsSetValue_724) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

// ===== skipBenchmarks() tests =====

TEST_F(ConfigTest_724, SkipBenchmarksDefaultFalse_724) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_724, SkipBenchmarksTrueWhenSet_724) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

// ===== benchmarkNoAnalysis() tests =====

TEST_F(ConfigTest_724, BenchmarkNoAnalysisDefaultFalse_724) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_724, BenchmarkNoAnalysisTrueWhenSet_724) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

// ===== benchmarkSamples() tests =====

TEST_F(ConfigTest_724, BenchmarkSamplesDefault100_724) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_724, BenchmarkSamplesReturnsSetValue_724) {
    ConfigData data;
    data.benchmarkSamples = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 500u);
}

// ===== benchmarkConfidenceInterval() tests =====

TEST_F(ConfigTest_724, BenchmarkConfidenceIntervalDefault_724) {
    ConfigData data;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_724, BenchmarkConfidenceIntervalReturnsSetValue_724) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

// ===== benchmarkResamples() tests =====

TEST_F(ConfigTest_724, BenchmarkResamplesDefault100000_724) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_724, BenchmarkResamplesReturnsSetValue_724) {
    ConfigData data;
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

// ===== benchmarkWarmupTime() tests =====

TEST_F(ConfigTest_724, BenchmarkWarmupTimeDefault_724) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_724, BenchmarkWarmupTimeReturnsSetValue_724) {
    ConfigData data;
    data.benchmarkWarmupTime = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(200));
}

// ===== getTestsOrTags() tests =====

TEST_F(ConfigTest_724, GetTestsOrTagsDefaultEmpty_724) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

TEST_F(ConfigTest_724, GetTestsOrTagsReturnsSetValues_724) {
    ConfigData data;
    data.testsOrTags = {"test1", "[tag1]"};
    Config config(data);
    const auto& result = config.getTestsOrTags();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "test1");
    EXPECT_EQ(result[1], "[tag1]");
}

// ===== getSectionsToRun() tests =====

TEST_F(ConfigTest_724, GetSectionsToRunDefaultEmpty_724) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

TEST_F(ConfigTest_724, GetSectionsToRunReturnsSetValues_724) {
    ConfigData data;
    data.sectionsToRun = {"section1", "section2"};
    Config config(data);
    const auto& result = config.getSectionsToRun();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "section1");
    EXPECT_EQ(result[1], "section2");
}

// ===== hasTestFilters() tests =====

TEST_F(ConfigTest_724, HasTestFiltersDefaultFalse_724) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.hasTestFilters());
}

TEST_F(ConfigTest_724, HasTestFiltersTrueWhenTestsOrTagsSet_724) {
    ConfigData data;
    data.testsOrTags = {"someFilter"};
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

// ===== Default construction tests =====

TEST_F(ConfigTest_724, DefaultConstructionWorks_724) {
    Config config;
    // Should not crash, default values should be sane
    EXPECT_FALSE(config.listTests());
    EXPECT_FALSE(config.listTags());
    EXPECT_FALSE(config.showHelp());
}

// ===== Boundary: abortAfter zero =====

TEST_F(ConfigTest_724, AbortAfterZero_724) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

// ===== Boundary: shardCount and shardIndex =====

TEST_F(ConfigTest_724, ShardCountBoundaryLargeValue_724) {
    ConfigData data;
    data.shardCount = 1000;
    data.shardIndex = 999;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 1000u);
    EXPECT_EQ(config.shardIndex(), 999u);
}

// ===== Boundary: benchmarkSamples zero =====

TEST_F(ConfigTest_724, BenchmarkSamplesZero_724) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

// ===== Boundary: minDuration zero =====

TEST_F(ConfigTest_724, MinDurationZero_724) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

// ===== Verbosity low =====

TEST_F(ConfigTest_724, VerbosityQuiet_724) {
    ConfigData data;
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}
