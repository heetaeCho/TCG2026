#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test encoding boolean true
TEST(YamlBoolEncodeTest_606, EncodeTrueReturnsNodeWithTrueString_606) {
    YAML::Node node = YAML::convert<bool>::encode(true);
    EXPECT_EQ(node.as<std::string>(), "true");
}

// Test encoding boolean false
TEST(YamlBoolEncodeTest_606, EncodeFalseReturnsNodeWithFalseString_606) {
    YAML::Node node = YAML::convert<bool>::encode(false);
    EXPECT_EQ(node.as<std::string>(), "false");
}

// Test that encoded true node is defined
TEST(YamlBoolEncodeTest_606, EncodeTrueNodeIsDefined_606) {
    YAML::Node node = YAML::convert<bool>::encode(true);
    EXPECT_TRUE(node.IsDefined());
}

// Test that encoded false node is defined
TEST(YamlBoolEncodeTest_606, EncodeFalseNodeIsDefined_606) {
    YAML::Node node = YAML::convert<bool>::encode(false);
    EXPECT_TRUE(node.IsDefined());
}

// Test that encoded true node is a scalar
TEST(YamlBoolEncodeTest_606, EncodeTrueNodeIsScalar_606) {
    YAML::Node node = YAML::convert<bool>::encode(true);
    EXPECT_TRUE(node.IsScalar());
}

// Test that encoded false node is a scalar
TEST(YamlBoolEncodeTest_606, EncodeFalseNodeIsScalar_606) {
    YAML::Node node = YAML::convert<bool>::encode(false);
    EXPECT_TRUE(node.IsScalar());
}

// Test round-trip: encode true then decode back to bool
TEST(YamlBoolRoundTripTest_606, EncodeTrueThenDecodeBackToBool_606) {
    YAML::Node node = YAML::convert<bool>::encode(true);
    bool result = false;
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

// Test round-trip: encode false then decode back to bool
TEST(YamlBoolRoundTripTest_606, EncodeFalseThenDecodeBackToBool_606) {
    YAML::Node node = YAML::convert<bool>::encode(false);
    bool result = true;
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

// Test that true and false encode to different values
TEST(YamlBoolEncodeTest_606, TrueAndFalseEncodeToDifferentValues_606) {
    YAML::Node trueNode = YAML::convert<bool>::encode(true);
    YAML::Node falseNode = YAML::convert<bool>::encode(false);
    EXPECT_NE(trueNode.as<std::string>(), falseNode.as<std::string>());
}

// Test decoding "true" string to bool
TEST(YamlBoolDecodeTest_606, DecodeStringTrueToBool_606) {
    YAML::Node node = YAML::Node("true");
    bool result = false;
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

// Test decoding "false" string to bool
TEST(YamlBoolDecodeTest_606, DecodeStringFalseToBool_606) {
    YAML::Node node = YAML::Node("false");
    bool result = true;
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

// Test scalar value of encoded true
TEST(YamlBoolEncodeTest_606, EncodeTrueScalarValueIsTrueString_606) {
    YAML::Node node = YAML::convert<bool>::encode(true);
    EXPECT_EQ(node.Scalar(), "true");
}

// Test scalar value of encoded false
TEST(YamlBoolEncodeTest_606, EncodeFalseScalarValueIsFalseString_606) {
    YAML::Node node = YAML::convert<bool>::encode(false);
    EXPECT_EQ(node.Scalar(), "false");
}

// Test that encoding does not produce null node
TEST(YamlBoolEncodeTest_606, EncodeTrueIsNotNull_606) {
    YAML::Node node = YAML::convert<bool>::encode(true);
    EXPECT_FALSE(node.IsNull());
}

TEST(YamlBoolEncodeTest_606, EncodeFalseIsNotNull_606) {
    YAML::Node node = YAML::convert<bool>::encode(false);
    EXPECT_FALSE(node.IsNull());
}

// Test that node is not a sequence or map
TEST(YamlBoolEncodeTest_606, EncodeTrueIsNotSequence_606) {
    YAML::Node node = YAML::convert<bool>::encode(true);
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(YamlBoolEncodeTest_606, EncodeFalseIsNotSequence_606) {
    YAML::Node node = YAML::convert<bool>::encode(false);
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

// Test multiple encode calls produce consistent results
TEST(YamlBoolEncodeTest_606, MultipleEncodeCallsProduceConsistentResults_606) {
    YAML::Node node1 = YAML::convert<bool>::encode(true);
    YAML::Node node2 = YAML::convert<bool>::encode(true);
    EXPECT_EQ(node1.as<std::string>(), node2.as<std::string>());

    YAML::Node node3 = YAML::convert<bool>::encode(false);
    YAML::Node node4 = YAML::convert<bool>::encode(false);
    EXPECT_EQ(node3.as<std::string>(), node4.as<std::string>());
}
