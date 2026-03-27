#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest_726 : public ::testing::Test {

protected:

    ConfigData configData;

    Config* config;



    void SetUp() override {

        config = new Config(configData);

    }



    void TearDown() override {

        delete config;

    }

};



TEST_F(ConfigTest_726, WarnAboutMissingAssertions_ReturnsFalseByDefault_726) {

    EXPECT_FALSE(config->warnAboutMissingAssertions());

}



TEST_F(ConfigTest_726, SetWarningsToNoAssertions_WarnAboutMissingAssertionsReturnsTrue_726) {

    configData.warnings = WarnAbout::What::NoAssertions;

    Config configWithWarnings(configData);

    EXPECT_TRUE(configWithWarnings.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_726, ListTests_ReturnsFalseByDefault_726) {

    EXPECT_FALSE(config->listTests());

}



TEST_F(ConfigTest_726, SetListTestsToTrue_ListTestsReturnsTrue_726) {

    configData.listTests = true;

    Config configWithListTests(configData);

    EXPECT_TRUE(configWithListTests.listTests());

}



TEST_F(ConfigTest_726, ListTags_ReturnsFalseByDefault_726) {

    EXPECT_FALSE(config->listTags());

}



TEST_F(ConfigTest_726, SetListTagsToTrue_ListTagsReturnsTrue_726) {

    configData.listTags = true;

    Config configWithListTags(configData);

    EXPECT_TRUE(configWithListTags.listTags());

}



TEST_F(ConfigTest_726, ListReporters_ReturnsFalseByDefault_726) {

    EXPECT_FALSE(config->listReporters());

}



TEST_F(ConfigTest_726, SetListReportersToTrue_ListReportersReturnsTrue_726) {

    configData.listReporters = true;

    Config configWithListReporters(configData);

    EXPECT_TRUE(configWithListReporters.listReporters());

}



TEST_F(ConfigTest_726, ListListeners_ReturnsFalseByDefault_726) {

    EXPECT_FALSE(config->listListeners());

}



TEST_F(ConfigTest_726, SetListListenersToTrue_ListListenersReturnsTrue_726) {

    configData.listListeners = true;

    Config configWithListListeners(configData);

    EXPECT_TRUE(configWithListListeners.listListeners());

}



TEST_F(ConfigTest_726, ShowHelp_ReturnsFalseByDefault_726) {

    EXPECT_FALSE(config->showHelp());

}



TEST_F(ConfigTest_726, SetShowHelpToTrue_ShowHelpReturnsTrue_726) {

    configData.showHelp = true;

    Config configWithShowHelp(configData);

    EXPECT_TRUE(configWithShowHelp.showHelp());

}



TEST_F(ConfigTest_726, AllowThrows_ReturnsFalseByDefault_726) {

    EXPECT_FALSE(config->allowThrows());

}



TEST_F(ConfigTest_726, SetNoThrowToFalse_AllowThrowsReturnsTrue_726) {

    configData.noThrow = false;

    Config configWithAllowThrows(configData);

    EXPECT_TRUE(configWithAllowThrows.allowThrows());

}



TEST_F(ConfigTest_726, ShowInvisibles_ReturnsFalseByDefault_726) {

    EXPECT_FALSE(config->showInvisibles());

}



TEST_F(ConfigTest_726, SetShowInvisiblesToTrue_ShowInvisiblesReturnsTrue_726) {

    configData.showInvisibles = true;

    Config configWithShowInvisibles(configData);

    EXPECT_TRUE(configWithShowInvisibles.showInvisibles());

}
