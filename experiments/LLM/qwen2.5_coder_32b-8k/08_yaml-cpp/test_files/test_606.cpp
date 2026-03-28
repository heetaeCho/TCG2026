#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"



class YamlConvertTest_606 : public ::testing::Test {

protected:

    // Additional setup if necessary can go here

};



TEST_F(YamlConvertTest_606, EncodeTrue_ReturnsNodeWithTrueString_606) {

    YAML::Node result = YAML::encode(true);

    EXPECT_EQ(result.as<std::string>(), "true");

}



TEST_F(YamlConvertTest_606, EncodeFalse_ReturnsNodeWithFalseString_606) {

    YAML::Node result = YAML::encode(false);

    EXPECT_EQ(result.as<std::string>(), "false");

}
