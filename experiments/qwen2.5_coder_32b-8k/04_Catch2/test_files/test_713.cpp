#include <gtest/gtest.h>

#include <catch2/catch_config.hpp>



using namespace Catch;



class ConfigTest : public ::testing::Test {

protected:

    ConfigData data;

    Config config;



    void SetUp() override {

        // Initialize default data and config for each test case

        data = ConfigData();

        config = Config(data);

    }

};



TEST_F(ConfigTest_713, ListTagsReturnsFalseByDefault_713) {

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_713, ListTagsReturnsTrueWhenSet_713) {

    data.listTags = true;

    config = Config(data);

    EXPECT_TRUE(config.listTags());

}



TEST_F(ConfigTest_713, ListTestsReturnsFalseByDefault_713) {

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_713, ListTestsReturnsTrueWhenSet_713) {

    data.listTests = true;

    config = Config(data);

    EXPECT_TRUE(config.listTests());

}



TEST_F(ConfigTest_713, ListReportersReturnsFalseByDefault_713) {

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_713, ListReportersReturnsTrueWhenSet_713) {

    data.listReporters = true;

    config = Config(data);

    EXPECT_TRUE(config.listReporters());

}



TEST_F(ConfigTest_713, ListListenersReturnsFalseByDefault_713) {

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_713, ListListenersReturnsTrueWhenSet_713) {

    data.listListeners = true;

    config = Config(data);

    EXPECT_TRUE(config.listListeners());

}



TEST_F(ConfigTest_713, ShowHelpReturnsFalseByDefault_713) {

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_713, ShowHelpReturnsTrueWhenSet_713) {

    data.showHelp = true;

    config = Config(data);

    EXPECT_TRUE(config.showHelp());

}



TEST_F(ConfigTest_713, AllowThrowsReturnsFalseByDefault_713) {

    EXPECT_FALSE(config.allowThrows());

}



TEST_F(ConfigTest_713, AllowThrowsReturnsTrueWhenSet_713) {

    data.noThrow = false;

    config = Config(data);

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_713, ShowInvisiblesReturnsFalseByDefault_713) {

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_713, ShowInvisiblesReturnsTrueWhenSet_713) {

    data.showInvisibles = true;

    config = Config(data);

    EXPECT_TRUE(config.showInvisibles());

}



TEST_F(ConfigTest_713, GetReporterSpecsReturnsEmptyByDefault_713) {

    EXPECT_TRUE(config.getReporterSpecs().empty());

}



TEST_F(ConfigTest_713, GetProcessedReporterSpecsReturnsEmptyByDefault_713) {

    EXPECT_TRUE(config.getProcessedReporterSpecs().empty());

}



TEST_F(ConfigTest_713, GetTestsOrTagsReturnsEmptyByDefault_713) {

    EXPECT_TRUE(config.getTestsOrTags().empty());

}



TEST_F(ConfigTest_713, GetSectionsToRunReturnsEmptyByDefault_713) {

    EXPECT_TRUE(config.getSectionsToRun().empty());

}
