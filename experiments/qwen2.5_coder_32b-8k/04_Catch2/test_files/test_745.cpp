#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"

#include <chrono>



using namespace Catch;



TEST_F(ConfigTest_745, BenchmarkWarmupTime_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));

}



TEST_F(ConfigTest_745, ListTests_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_745, ListTags_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_745, ListReporters_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_745, ListListeners_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_745, ShowHelp_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_745, AllowThrows_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_FALSE(config.allowThrows());

}



TEST_F(ConfigTest_745, ShowInvisibles_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_745, SkipBenchmarks_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_745, BenchmarkNoAnalysis_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_745, GetTestsOrTags_EmptyByDefault_745) {

    ConfigData data;

    Config config(data);

    EXPECT_TRUE(config.getTestsOrTags().empty());

}



TEST_F(ConfigTest_745, GetSectionsToRun_EmptyByDefault_745) {

    ConfigData data;

    Config config(data);

    EXPECT_TRUE(config.getSectionsToRun().empty());

}



TEST_F(ConfigTest_745, GetReporterSpecs_EmptyByDefault_745) {

    ConfigData data;

    Config config(data);

    EXPECT_TRUE(config.getReporterSpecs().empty());

}



TEST_F(ConfigTest_745, GetProcessedReporterSpecs_EmptyByDefault_745) {

    ConfigData data;

    Config config(data);

    EXPECT_TRUE(config.getProcessedReporterSpecs().empty());

}



TEST_F(ConfigTest_745, HasTestFilters_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_FALSE(config.hasTestFilters());

}



TEST_F(ConfigTest_745, MinDuration_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);

}



TEST_F(ConfigTest_745, ShardCount_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_EQ(config.shardCount(), 1u);

}



TEST_F(ConfigTest_745, ShardIndex_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_EQ(config.shardIndex(), 0u);

}



TEST_F(ConfigTest_745, AbortAfter_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_EQ(config.abortAfter(), -1);

}



TEST_F(ConfigTest_745, BenchmarkSamples_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_EQ(config.benchmarkSamples(), 100u);

}



TEST_F(ConfigTest_745, BenchmarkConfidenceInterval_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);

}



TEST_F(ConfigTest_745, BenchmarkResamples_DefaultValue_745) {

    ConfigData data;

    Config config(data);

    EXPECT_EQ(config.benchmarkResamples(), 100000u);

}
