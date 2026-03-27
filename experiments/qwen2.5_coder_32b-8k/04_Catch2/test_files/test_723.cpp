#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest : public ::testing::Test {

protected:

    ConfigData data;

    Config config;



    void SetUp() override {

        // Initialize default configuration data for tests

        data.noThrow = false;

        config = Config(data);

    }

};



TEST_F(ConfigTest_723, AllowThrows_ReturnsTrueWhenNoThrowIsFalse_723) {

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_723, AllowThrows_ReturnsFalseWhenNoThrowIsTrue_723) {

    data.noThrow = true;

    Config configWithNoThrow(data);

    EXPECT_FALSE(configWithNoThrow.allowThrows());

}



TEST_F(ConfigTest_723, ListTests_ReturnsDefaultConfigValue_723) {

    EXPECT_EQ(config.listTests(), false);

}



TEST_F(ConfigTest_723, ListTags_ReturnsDefaultConfigValue_723) {

    EXPECT_EQ(config.listTags(), false);

}



TEST_F(ConfigTest_723, ListReporters_ReturnsDefaultConfigValue_723) {

    EXPECT_EQ(config.listReporters(), false);

}



TEST_F(ConfigTest_723, ListListeners_ReturnsDefaultConfigValue_723) {

    EXPECT_EQ(config.listListeners(), false);

}



TEST_F(ConfigTest_723, ShowHelp_ReturnsDefaultConfigValue_723) {

    EXPECT_EQ(config.showHelp(), false);

}



TEST_F(ConfigTest_723, AllowThrows_DefaultConstructor_723) {

    Config defaultConfig;

    EXPECT_TRUE(defaultConfig.allowThrows());

}
