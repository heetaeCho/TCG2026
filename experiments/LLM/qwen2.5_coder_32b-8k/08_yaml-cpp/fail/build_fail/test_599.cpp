#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"



class EncodeTest_599 : public ::testing::Test {

protected:

    using Node = YAML::Node;

};



TEST_F(EncodeTest_599, PutNullPointer_ReturnsEmptyNode_599) {

    Node node = YAML::encode(nullptr);

    EXPECT_TRUE(node.IsNull());

}



TEST_F(EncodeTest_599, PutEmptyString_ReturnsEmptyStringNode_599) {

    const char* emptyString = "";

    Node node = YAML::encode(emptyString);

    EXPECT_STREQ(node.as<std::string>().c_str(), "");

}



TEST_F(EncodeTest_599, PutNormalString_ReturnsCorrectNode_599) {

    const char* testString = "Hello, World!";

    Node node = YAML::encode(testString);

    EXPECT_STREQ(node.as<std::string>().c_str(), "Hello, World!");

}



TEST_F(EncodeTest_599, PutLongString_ReturnsCorrectNode_599) {

    const char* longString = "This is a longer string to test the encoding functionality of YAML::encode.";

    Node node = YAML::encode(longString);

    EXPECT_STREQ(node.as<std::string>().c_str(), longString);

}
