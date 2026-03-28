#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"

#include <string_view>



class EncodeTest_600 : public ::testing::Test {

protected:

    YAML::Node result;

};



TEST_F(EncodeTest_600, NormalOperation_StringViewToNode_600) {

    std::string_view input = "test_string";

    result = YAML::encode(input);

    EXPECT_EQ(result.as<std::string>(), "test_string");

}



TEST_F(EncodeTest_600, EmptyStringView_600) {

    std::string_view input = "";

    result = YAML::encode(input);

    EXPECT_EQ(result.as<std::string>(), "");

}



TEST_F(EncodeTest_600, StringViewWithSpaces_600) {

    std::string_view input = "test string with spaces";

    result = YAML::encode(input);

    EXPECT_EQ(result.as<std::string>(), "test string with spaces");

}



TEST_F(EncodeTest_600, LongStringView_600) {

    std::string long_string(1024, 'a');

    std::string_view input(long_string);

    result = YAML::encode(input);

    EXPECT_EQ(result.as<std::string>(), long_string);

}
