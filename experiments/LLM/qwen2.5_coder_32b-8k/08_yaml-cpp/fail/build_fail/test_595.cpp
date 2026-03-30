#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"



class EncodeTest_595 : public ::testing::Test {

protected:

    YAML::Node node;

};



TEST_F(EncodeTest_595, PutEmptyString_ReturnsValidNode_595) {

    node = YAML::encode("");

    EXPECT_FALSE(node.IsNull());

}



TEST_F(EncodeTest_595, PutNonEmptyString_ReturnsValidNode_595) {

    node = YAML::encode("test");

    EXPECT_FALSE(node.IsNull());

}



TEST_F(EncodeTest_595, PutLongString_ReturnsValidNode_595) {

    std::string long_string(1024, 'a'); // 1KB string

    node = YAML::encode(long_string);

    EXPECT_FALSE(node.IsNull());

}



TEST_F(EncodeTest_595, EncodeConsistentWithInput_595) {

    std::string input = "Hello, World!";

    node = YAML::encode(input);

    EXPECT_EQ(node.as<std::string>(), input);

}
