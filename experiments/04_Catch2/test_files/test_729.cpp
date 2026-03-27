#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest_729 : public ::testing::Test {

protected:

    ConfigData data;

    Config config;



    void SetUp() override {

        // Initialize default values for ConfigData if needed

        config = Config(data);

    }

};



TEST_F(ConfigTest_729, ShowDurationsDefault_729) {

    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);

}



TEST_F(ConfigTest_729, ListTestsFalseByDefault_729) {

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_729, ListTagsFalseByDefault_729) {

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_729, ListReportersFalseByDefault_729) {

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_729, ListListenersFalseByDefault_729) {

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_729, ShowHelpFalseByDefault_729) {

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_729, AllowThrowsTrueByDefault_729) {

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_729, IncludeSuccessfulResultsFalseByDefault_729) {

    EXPECT_FALSE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_729, WarnAboutMissingAssertionsFalseByDefault_729) {

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_729, WarnAboutUnmatchedTestSpecsFalseByDefault_729) {

    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_729, ZeroTestsCountAsSuccessFalseByDefault_729) {

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_729, MinDurationNegativeOneByDefault_729) {

    EXPECT_EQ(config.minDuration(), -1);

}



TEST_F(ConfigTest_729, ShardCountOneByDefault_729) {

    EXPECT_EQ(config.shardCount(), 1);

}



TEST_F(ConfigTest_729, ShardIndexZeroByDefault_729) {

    EXPECT_EQ(config.shardIndex(), 0);

}



TEST_F(ConfigTest_729, AbortAfterNegativeOneByDefault_729) {

    EXPECT_EQ(config.abortAfter(), -1);

}



TEST_F(ConfigTest_729, ShowInvisiblesFalseByDefault_729) {

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_729, SkipBenchmarksFalseByDefault_729) {

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_729, BenchmarkNoAnalysisFalseByDefault_729) {

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_729, BenchmarkSamplesHundredByDefault_729) {

    EXPECT_EQ(config.benchmarkSamples(), 100);

}



TEST_F(ConfigTest_729, BenchmarkConfidenceIntervalNinetyFivePercent_729) {

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);

}



TEST_F(ConfigTest_729, BenchmarkResamplesHundredThousandByDefault_729) {

    EXPECT_EQ(config.benchmarkResamples(), 100000);

}



TEST_F(ConfigTest_729, BenchmarkWarmupTimeOneHundredMilliseconds_729) {

    EXPECT_EQ(config.benchmarkWarmupTime().count(), 100);

}
