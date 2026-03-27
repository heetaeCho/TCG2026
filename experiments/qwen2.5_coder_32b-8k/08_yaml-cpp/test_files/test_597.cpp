#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"

#include "yaml-cpp/node/node.h"



class ConvertTest_597 : public ::testing::Test {

protected:

    YAML::Node node;

};



TEST_F(ConvertTest_597, EncodeNullPointer_ReturnsEmptyNode_597) {

    node = YAML::encode(static_cast<const char*>(nullptr));

    EXPECT_TRUE(node.IsNull());

}



TEST_F(ConvertTest_597, EncodeEmptyString_ReturnsEmptyScalarNode_597) {

    node = YAML::encode("");

    EXPECT_FALSE(node.IsNull());

    EXPECT_TRUE(node.IsScalar());

    EXPECT_EQ(node.as<std::string>(), "");

}



TEST_F(ConvertTest_597, EncodeNormalString_ReturnsCorrectScalarNode_597) {

    const char* testString = "testString";

    node = YAML::encode(testString);

    EXPECT_FALSE(node.IsNull());

    EXPECT_TRUE(node.IsScalar());

    EXPECT_EQ(node.as<std::string>(), testString);

}



TEST_F(ConvertTest_597, EncodeLongString_ReturnsCorrectScalarNode_597) {

    const char* longString = "This is a longer string to ensure that the encoding handles various lengths correctly.";

    node = YAML::encode(longString);

    EXPECT_FALSE(node.IsNull());

    EXPECT_TRUE(node.IsScalar());

    EXPECT_EQ(node.as<std::string>(), longString);

}
