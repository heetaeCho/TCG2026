#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/catch_config.hpp"



using namespace Catch;



TEST_F(ConfigTest_736, ShouldDebugBreak_ReturnsFalseByDefault_736) {

    Config config;

    EXPECT_FALSE(config.shouldDebugBreak());

}



TEST_F(ConfigTest_736, ShouldDebugBreak_ReturnsTrueWhenSet_736) {

    ConfigData data;

    data.shouldDebugBreak = true;

    Config config(data);

    EXPECT_TRUE(config.shouldDebugBreak());

}



TEST_F(ConfigTest_736, ListTests_ReturnsFalseByDefault_736) {

    Config config;

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_736, ListTags_ReturnsFalseByDefault_736) {

    Config config;

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_736, ListReporters_ReturnsFalseByDefault_736) {

    Config config;

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_736, ListListeners_ReturnsFalseByDefault_736) {

    Config config;

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_736, ShowHelp_ReturnsFalseByDefault_736) {

    Config config;

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_736, AllowThrows_ReturnsTrueByDefault_736) {

    Config config;

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_736, IncludeSuccessfulResults_ReturnsFalseByDefault_736) {

    Config config;

    EXPECT_FALSE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_736, WarnAboutMissingAssertions_ReturnsFalseByDefault_736) {

    Config config;

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_736, WarnAboutUnmatchedTestSpecs_ReturnsFalseByDefault_736) {

    Config config;

    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_736, ZeroTestsCountAsSuccess_ReturnsFalseByDefault_736) {

    Config config;

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_736, SkipBenchmarks_ReturnsFalseByDefault_736) {

    Config config;

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_736, BenchmarkNoAnalysis_ReturnsFalseByDefault_736) {

    Config config;

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_736, GetTestsOrTags_ReturnsEmptyVectorByDefault_736) {

    Config config;

    EXPECT_TRUE(config.getTestsOrTags().empty());

}



TEST_F(ConfigTest_736, GetSectionsToRun_ReturnsEmptyVectorByDefault_736) {

    Config config;

    EXPECT_TRUE(config.getSectionsToRun().empty());

}



TEST_F(ConfigTest_736, GetReporterSpecs_ReturnsEmptyVectorByDefault_736) {

    Config config;

    EXPECT_TRUE(config.getReporterSpecs().empty());

}



TEST_F(ConfigTest_736, GetProcessedReporterSpecs_ReturnsEmptyVectorByDefault_736) {

    Config config;

    EXPECT_TRUE(config.getProcessedReporterSpecs().empty());

}
