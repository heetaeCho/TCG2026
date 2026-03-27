#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



class CatchConfigTest : public ::testing::Test {

protected:

    Catch::ConfigData configData;

    Catch::Config* config;



    void SetUp() override {

        config = new Catch::Config(configData);

    }



    void TearDown() override {

        delete config;

    }

};



TEST_F(CatchConfigTest_725, IncludeSuccessfulResults_Default_725) {

    EXPECT_FALSE(config->includeSuccessfulResults());

}



TEST_F(CatchConfigTest_725, IncludeSuccessfulResults_SetTrue_725) {

    configData.showSuccessfulTests = true;

    Catch::Config configWithTrue(configData);

    EXPECT_TRUE(configWithTrue.includeSuccessfulResults());

}



TEST_F(CatchConfigTest_725, ListTests_Default_725) {

    EXPECT_FALSE(config->listTests());

}



TEST_F(CatchConfigTest_725, ListTests_SetTrue_725) {

    configData.listTests = true;

    Catch::Config configWithTrue(configData);

    EXPECT_TRUE(configWithTrue.listTests());

}



TEST_F(CatchConfigTest_725, ListTags_Default_725) {

    EXPECT_FALSE(config->listTags());

}



TEST_F(CatchConfigTest_725, ListTags_SetTrue_725) {

    configData.listTags = true;

    Catch::Config configWithTrue(configData);

    EXPECT_TRUE(configWithTrue.listTags());

}



TEST_F(CatchConfigTest_725, ListReporters_Default_725) {

    EXPECT_FALSE(config->listReporters());

}



TEST_F(CatchConfigTest_725, ListReporters_SetTrue_725) {

    configData.listReporters = true;

    Catch::Config configWithTrue(configData);

    EXPECT_TRUE(configWithTrue.listReporters());

}



TEST_F(CatchConfigTest_725, ListListeners_Default_725) {

    EXPECT_FALSE(config->listListeners());

}



TEST_F(CatchConfigTest_725, ListListeners_SetTrue_725) {

    configData.listListeners = true;

    Catch::Config configWithTrue(configData);

    EXPECT_TRUE(configWithTrue.listListeners());

}



TEST_F(CatchConfigTest_725, ShowHelp_Default_725) {

    EXPECT_FALSE(config->showHelp());

}



TEST_F(CatchConfigTest_725, ShowHelp_SetTrue_725) {

    configData.showHelp = true;

    Catch::Config configWithTrue(configData);

    EXPECT_TRUE(configWithTrue.showHelp());

}



TEST_F(CatchConfigTest_725, AllowThrows_Default_725) {

    EXPECT_FALSE(config->allowThrows());

}



TEST_F(CatchConfigTest_725, AllowThrows_SetTrue_725) {

    configData.noThrow = false;

    Catch::Config configWithTrue(configData);

    EXPECT_TRUE(configWithTrue.allowThrows());

}



TEST_F(CatchConfigTest_725, GetTestsOrTags_Default_725) {

    EXPECT_TRUE(config->getTestsOrTags().empty());

}



TEST_F(CatchConfigTest_725, GetSectionsToRun_Default_725) {

    EXPECT_TRUE(config->getSectionsToRun().empty());

}



TEST_F(CatchConfigTest_725, HasTestFilters_Default_725) {

    EXPECT_FALSE(config->hasTestFilters());

}



TEST_F(CatchConfigTest_725, ShowInvisibles_Default_725) {

    EXPECT_FALSE(config->showInvisibles());

}



TEST_F(CatchConfigTest_725, ShowInvisibles_SetTrue_725) {

    configData.showInvisibles = true;

    Catch::Config configWithTrue(configData);

    EXPECT_TRUE(configWithTrue.showInvisibles());

}



TEST_F(CatchConfigTest_725, SkipBenchmarks_Default_725) {

    EXPECT_FALSE(config->skipBenchmarks());

}



TEST_F(CatchConfigTest_725, SkipBenchmarks_SetTrue_725) {

    configData.skipBenchmarks = true;

    Catch::Config configWithTrue(configData);

    EXPECT_TRUE(configWithTrue.skipBenchmarks());

}



TEST_F(CatchConfigTest_725, BenchmarkNoAnalysis_Default_725) {

    EXPECT_FALSE(config->benchmarkNoAnalysis());

}



TEST_F(CatchConfigTest_725, BenchmarkNoAnalysis_SetTrue_725) {

    configData.benchmarkNoAnalysis = true;

    Catch::Config configWithTrue(configData);

    EXPECT_TRUE(configWithTrue.benchmarkNoAnalysis());

}



TEST_F(CatchConfigTest_725, ShardCount_Default_725) {

    EXPECT_EQ(1u, config->shardCount());

}



TEST_F(CatchConfigTest_725, ShardIndex_Default_725) {

    EXPECT_EQ(0u, config->shardIndex());

}
