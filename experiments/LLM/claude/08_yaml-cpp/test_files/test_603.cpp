#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/convert.h"
#include "yaml-cpp/node/node.h"

// Test fixture for YAML Node convert tests
class YamlConvertTest_603 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Tests for _Null decode
// ============================================================

TEST_F(YamlConvertTest_603, DecodeNullNode_ReturnsTrue_603) {
    YAML::Node node = YAML::Load("~");
    _Null nullValue;
    EXPECT_TRUE(YAML::convert<_Null>::decode(node, nullValue));
}

TEST_F(YamlConvertTest_603, DecodeExplicitNull_ReturnsTrue_603) {
    YAML::Node node = YAML::Load("null");
    _Null nullValue;
    EXPECT_TRUE(YAML::convert<_Null>::decode(node, nullValue));
}

TEST_F(YamlConvertTest_603, DecodeNullUpperCase_ReturnsTrue_603) {
    YAML::Node node = YAML::Load("Null");
    _Null nullValue;
    EXPECT_TRUE(YAML::convert<_Null>::decode(node, nullValue));
}

TEST_F(YamlConvertTest_603, DecodeNULLAllCaps_ReturnsTrue_603) {
    YAML::Node node = YAML::Load("NULL");
    _Null nullValue;
    EXPECT_TRUE(YAML::convert<_Null>::decode(node, nullValue));
}

TEST_F(YamlConvertTest_603, DecodeNonNullString_ReturnsFalse_603) {
    YAML::Node node = YAML::Load("hello");
    _Null nullValue;
    EXPECT_FALSE(YAML::convert<_Null>::decode(node, nullValue));
}

TEST_F(YamlConvertTest_603, DecodeNonNullInteger_ReturnsFalse_603) {
    YAML::Node node = YAML::Load("42");
    _Null nullValue;
    EXPECT_FALSE(YAML::convert<_Null>::decode(node, nullValue));
}

TEST_F(YamlConvertTest_603, DecodeSequenceNode_ReturnsFalse_603) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    _Null nullValue;
    EXPECT_FALSE(YAML::convert<_Null>::decode(node, nullValue));
}

TEST_F(YamlConvertTest_603, DecodeMapNode_ReturnsFalse_603) {
    YAML::Node node = YAML::Load("{key: value}");
    _Null nullValue;
    EXPECT_FALSE(YAML::convert<_Null>::decode(node, nullValue));
}

TEST_F(YamlConvertTest_603, DecodeEmptyString_ReturnsFalse_603) {
    YAML::Node node = YAML::Load("\"\"");
    _Null nullValue;
    EXPECT_FALSE(YAML::convert<_Null>::decode(node, nullValue));
}

TEST_F(YamlConvertTest_603, DecodeBoolean_ReturnsFalse_603) {
    YAML::Node node = YAML::Load("true");
    _Null nullValue;
    EXPECT_FALSE(YAML::convert<_Null>::decode(node, nullValue));
}

TEST_F(YamlConvertTest_603, DecodeFloat_ReturnsFalse_603) {
    YAML::Node node = YAML::Load("3.14");
    _Null nullValue;
    EXPECT_FALSE(YAML::convert<_Null>::decode(node, nullValue));
}

TEST_F(YamlConvertTest_603, DecodeUndefinedNode_ReturnsFalse_603) {
    YAML::Node node;
    _Null nullValue;
    EXPECT_FALSE(YAML::convert<_Null>::decode(node, nullValue));
}

// ============================================================
// Tests for standard type conversions via convert
// ============================================================

TEST_F(YamlConvertTest_603, DecodeStringFromNode_603) {
    YAML::Node node = YAML::Load("hello");
    std::string result;
    EXPECT_TRUE(YAML::convert<std::string>::decode(node, result));
    EXPECT_EQ("hello", result);
}

TEST_F(YamlConvertTest_603, DecodeIntFromNode_603) {
    YAML::Node node = YAML::Load("42");
    int result;
    EXPECT_TRUE(YAML::convert<int>::decode(node, result));
    EXPECT_EQ(42, result);
}

TEST_F(YamlConvertTest_603, DecodeDoubleFromNode_603) {
    YAML::Node node = YAML::Load("3.14");
    double result;
    EXPECT_TRUE(YAML::convert<double>::decode(node, result));
    EXPECT_NEAR(3.14, result, 0.001);
}

TEST_F(YamlConvertTest_603, DecodeBoolTrueFromNode_603) {
    YAML::Node node = YAML::Load("true");
    bool result;
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(YamlConvertTest_603, DecodeBoolFalseFromNode_603) {
    YAML::Node node = YAML::Load("false");
    bool result;
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

TEST_F(YamlConvertTest_603, DecodeIntFromInvalidString_ReturnsFalse_603) {
    YAML::Node node = YAML::Load("not_a_number");
    int result;
    EXPECT_FALSE(YAML::convert<int>::decode(node, result));
}

TEST_F(YamlConvertTest_603, DecodeNegativeInt_603) {
    YAML::Node node = YAML::Load("-100");
    int result;
    EXPECT_TRUE(YAML::convert<int>::decode(node, result));
    EXPECT_EQ(-100, result);
}

TEST_F(YamlConvertTest_603, DecodeZeroInt_603) {
    YAML::Node node = YAML::Load("0");
    int result;
    EXPECT_TRUE(YAML::convert<int>::decode(node, result));
    EXPECT_EQ(0, result);
}

TEST_F(YamlConvertTest_603, DecodeEmptyNodeAsNull_603) {
    YAML::Node node = YAML::Load("");
    _Null nullValue;
    EXPECT_TRUE(YAML::convert<_Null>::decode(node, nullValue));
}

TEST_F(YamlConvertTest_603, NodeAsNullViaTemplate_603) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST_F(YamlConvertTest_603, NodeIsNotNullForScalar_603) {
    YAML::Node node = YAML::Load("value");
    EXPECT_FALSE(node.IsNull());
}

TEST_F(YamlConvertTest_603, DecodeUnsignedInt_603) {
    YAML::Node node = YAML::Load("255");
    unsigned int result;
    EXPECT_TRUE(YAML::convert<unsigned int>::decode(node, result));
    EXPECT_EQ(255u, result);
}

TEST_F(YamlConvertTest_603, DecodeLongLong_603) {
    YAML::Node node = YAML::Load("9999999999");
    long long result;
    EXPECT_TRUE(YAML::convert<long long>::decode(node, result));
    EXPECT_EQ(9999999999LL, result);
}

TEST_F(YamlConvertTest_603, DecodeFloat_ValidValue_603) {
    YAML::Node node = YAML::Load("1.5");
    float result;
    EXPECT_TRUE(YAML::convert<float>::decode(node, result));
    EXPECT_NEAR(1.5f, result, 0.001f);
}
