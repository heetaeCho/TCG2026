#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest_718 : public ::testing::Test {

protected:

    ConfigData testData;

    Config config;



    void SetUp() override {

        testData.reporterSpecifications = {{}};

        config = Config(testData);

    }

};



TEST_F(ConfigTest_718, GetReporterSpecs_ReturnsCorrectValue_718) {

    EXPECT_EQ(config.getReporterSpecs(), testData.reporterSpecifications);

}



TEST_F(ConfigTest_718, ListTests_ReturnsFalseByDefault_718) {

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_718, ListTags_ReturnsFalseByDefault_718) {

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_718, ListReporters_ReturnsFalseByDefault_718) {

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_718, ListListeners_ReturnsFalseByDefault_718) {

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_718, ShowHelp_ReturnsFalseByDefault_718) {

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_718, AllowThrows_ReturnsTrueByDefault_718) {

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_718, IncludeSuccessfulResults_ReturnsFalseByDefault_718) {

    EXPECT_FALSE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_718, WarnAboutMissingAssertions_ReturnsFalseByDefault_718) {

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_718, WarnAboutUnmatchedTestSpecs_ReturnsFalseByDefault_718) {

    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_718, ZeroTestsCountAsSuccess_ReturnsFalseByDefault_718) {

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_718, SkipBenchmarks_ReturnsFalseByDefault_718) {

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_718, BenchmarkNoAnalysis_ReturnsFalseByDefault_718) {

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_718, GetTestsOrTags_ReturnsEmptyVectorByDefault_718) {

    EXPECT_TRUE(config.getTestsOrTags().empty());

}



TEST_F(ConfigTest_718, GetSectionsToRun_ReturnsEmptyVectorByDefault_718) {

    EXPECT_TRUE(config.getSectionsToRun().empty());

}
