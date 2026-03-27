#include <gtest/gtest.h>

#include <yaml-cpp/node/convert.h>



class YamlConvertTest_603 : public ::testing::Test {

protected:

    YAML::Node node;

};



TEST_F(YamlConvertTest_603, DecodeNullNode_ReturnsTrue_603) {

    node = YAML::Load("null");

    _Null nullValue;

    EXPECT_TRUE(YAML::decode(node, nullValue));

}



TEST_F(YamlConvertTest_603, DecodeNonEmptyNode_ReturnsFalse_603) {

    node = YAML::Load("value");

    _Null nullValue;

    EXPECT_FALSE(YAML::decode(node, nullValue));

}



TEST_F(YamlConvertTest_603, DecodeEmptyScalar_ReturnsTrue_603) {

    node = YAML::Node();

    _Null nullValue;

    EXPECT_TRUE(YAML::decode(node, nullValue));

}
