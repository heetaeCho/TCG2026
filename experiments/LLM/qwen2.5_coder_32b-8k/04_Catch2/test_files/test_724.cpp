#include <gtest/gtest.h>

#include "catch_config.hpp"



using namespace Catch;



class ConfigTest : public ::testing::Test {

protected:

    ConfigData createConfigData() {

        ConfigData data;

        data.name = "test_name";

        data.processName = "process_name";

        return data;

    }

};



TEST_F(ConfigTest_724, NameReturnsProvidedName_724) {

    ConfigData data = createConfigData();

    Config config(data);

    EXPECT_EQ(config.name(), StringRef("test_name"));

}



TEST_F(ConfigTest_724, NameReturnsProcessNameWhenNameEmpty_724) {

    ConfigData data;

    data.name = "";

    data.processName = "process_name";

    Config config(data);

    EXPECT_EQ(config.name(), StringRef("process_name"));

}



TEST_F(ConfigTest_724, ListTestsReturnsFalseByDefault_724) {

    Config config(createConfigData());

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_724, ListTagsReturnsFalseByDefault_724) {

    Config config(createConfigData());

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_724, ListReportersReturnsFalseByDefault_724) {

    Config config(createConfigData());

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_724, ListListenersReturnsFalseByDefault_724) {

    Config config(createConfigData());

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_724, ShowHelpReturnsFalseByDefault_724) {

    Config config(createConfigData());

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_724, AllowThrowsReturnsTrueByDefault_724) {

    Config config(createConfigData());

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_724, IncludeSuccessfulResultsReturnsFalseByDefault_724) {

    Config config(createConfigData());

    EXPECT_FALSE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_724, WarnAboutMissingAssertionsReturnsFalseByDefault_724) {

    Config config(createConfigData());

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_724, WarnAboutUnmatchedTestSpecsReturnsFalseByDefault_724) {

    Config config(createConfigData());

    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_724, ZeroTestsCountAsSuccessReturnsFalseByDefault_724) {

    Config config(createConfigData());

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_724, ShowDurationsReturnsDefaultForReporterByDefault_724) {

    Config config(createConfigData());

    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);

}



TEST_F(ConfigTest_724, MinDurationReturnsNegativeOneByDefault_724) {

    Config config(createConfigData());

    EXPECT_DOUBLE_EQ(config.minDuration(), -1);

}



TEST_F(ConfigTest_724, RunOrderReturnsDeclaredByDefault_724) {

    Config config(createConfigData());

    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);

}



TEST_F(ConfigTest_724, RngSeedIsGeneratedByDefault_724) {

    Config config(createConfigData());

    EXPECT_NE(config.rngSeed(), 0);

}



TEST_F(ConfigTest_724, ShardCountReturnsOneByDefault_724) {

    Config config(createConfigData());

    EXPECT_EQ(config.shardCount(), 1);

}



TEST_F(ConfigTest_724, ShardIndexReturnsZeroByDefault_724) {

    Config config(createConfigData());

    EXPECT_EQ(config.shardIndex(), 0);

}



TEST_F(ConfigTest_724, DefaultColourModeReturnsPlatformDefaultByDefault_724) {

    Config config(createConfigData());

    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);

}



TEST_F(ConfigTest_724, ShouldDebugBreakReturnsFalseByDefault_724) {

    Config config(createConfigData());

    EXPECT_FALSE(config.shouldDebugBreak());

}



TEST_F(ConfigTest_724, AbortAfterReturnsNegativeOneByDefault_724) {

    Config config(createConfigData());

    EXPECT_EQ(config.abortAfter(), -1);

}



TEST_F(ConfigTest_724, ShowInvisiblesReturnsFalseByDefault_724) {

    Config config(createConfigData());

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_724, VerbosityReturnsNormalByDefault_724) {

    Config config(createConfigData());

    EXPECT_EQ(config.verbosity(), Verbosity::Normal);

}



TEST_F(ConfigTest_724, SkipBenchmarksReturnsFalseByDefault_724) {

    Config config(createConfigData());

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_724, BenchmarkNoAnalysisReturnsFalseByDefault_724) {

    Config config(createConfigData());

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_724, BenchmarkSamplesReturnsHundredByDefault_724) {

    Config config(createConfigData());

    EXPECT_EQ(config.benchmarkSamples(), 100);

}



TEST_F(ConfigTest_724, BenchmarkConfidenceIntervalReturnsCorrectValue_724) {

    Config config(createConfigData());

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);

}



TEST_F(ConfigTest_724, BenchmarkResamplesReturnsHundredThousandByDefault_724) {

    Config config(createConfigData());

    EXPECT_EQ(config.benchmarkResamples(), 100000);

}



TEST_F(ConfigTest_724, BenchmarkWarmupTimeReturnsOneHundredMillisecondsByDefault_724) {

    Config config(createConfigData());

    EXPECT_EQ(config.benchmarkWarmupTime().count(), 100);

}
