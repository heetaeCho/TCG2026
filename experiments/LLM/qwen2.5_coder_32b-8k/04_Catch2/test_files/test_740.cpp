#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest_740 : public ::testing::Test {

protected:

    ConfigData configData;

    Config config;



    void SetUp() override {

        configData.skipBenchmarks = false; // Default value

        config = Config(configData);

    }

};



TEST_F(ConfigTest_740, SkipBenchmarks_DefaultValue_740) {

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_740, SkipBenchmarks_SetTrue_740) {

    configData.skipBenchmarks = true;

    config = Config(configData);

    EXPECT_TRUE(config.skipBenchmarks());

}



TEST_F(ConfigTest_740, SkipBenchmarks_SetFalse_740) {

    configData.skipBenchmarks = false;

    config = Config(configData);

    EXPECT_FALSE(config.skipBenchmarks());

}
