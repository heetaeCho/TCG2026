#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test fixture for YAML Node convert tests
class YamlConvertTest_597 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test encoding a simple string
TEST_F(YamlConvertTest_597, EncodeSimpleString_597) {
    const char* input = "hello";
    YAML::Node node = YAML::Node(input);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test encoding an empty string
TEST_F(YamlConvertTest_597, EncodeEmptyString_597) {
    const char* input = "";
    YAML::Node node = YAML::Node(input);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "");
}

// Test encoding a string with spaces
TEST_F(YamlConvertTest_597, EncodeStringWithSpaces_597) {
    const char* input = "hello world";
    YAML::Node node = YAML::Node(input);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

// Test encoding a string with special characters
TEST_F(YamlConvertTest_597, EncodeStringWithSpecialChars_597) {
    const char* input = "key: value";
    YAML::Node node = YAML::Node(input);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "key: value");
}

// Test encoding a string with newline characters
TEST_F(YamlConvertTest_597, EncodeStringWithNewlines_597) {
    const char* input = "line1\nline2";
    YAML::Node node = YAML::Node(input);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "line1\nline2");
}

// Test encoding a numeric string
TEST_F(YamlConvertTest_597, EncodeNumericString_597) {
    const char* input = "12345";
    YAML::Node node = YAML::Node(input);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "12345");
}

// Test that the node is a scalar
TEST_F(YamlConvertTest_597, EncodeProducesScalarNode_597) {
    const char* input = "test";
    YAML::Node node = YAML::Node(input);
    EXPECT_TRUE(node.IsScalar());
}

// Test encoding a single character string
TEST_F(YamlConvertTest_597, EncodeSingleCharString_597) {
    const char* input = "a";
    YAML::Node node = YAML::Node(input);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "a");
}

// Test encoding a string with tab character
TEST_F(YamlConvertTest_597, EncodeStringWithTab_597) {
    const char* input = "col1\tcol2";
    YAML::Node node = YAML::Node(input);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "col1\tcol2");
}

// Test encoding a string with YAML special characters like brackets
TEST_F(YamlConvertTest_597, EncodeStringWithBrackets_597) {
    const char* input = "[item1, item2]";
    YAML::Node node = YAML::Node(input);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "[item1, item2]");
}

// Test encoding a long string
TEST_F(YamlConvertTest_597, EncodeLongString_597) {
    std::string longStr(1000, 'x');
    YAML::Node node = YAML::Node(longStr.c_str());
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), longStr);
}

// Test that node is not null after encoding
TEST_F(YamlConvertTest_597, EncodeNodeIsNotNull_597) {
    const char* input = "value";
    YAML::Node node = YAML::Node(input);
    EXPECT_FALSE(node.IsNull());
}

// Test convert round-trip with std::string
TEST_F(YamlConvertTest_597, ConvertStringRoundTrip_597) {
    std::string original = "round_trip_test";
    YAML::Node node;
    node = original;
    std::string result = node.as<std::string>();
    EXPECT_EQ(result, original);
}

// Test convert with bool
TEST_F(YamlConvertTest_597, ConvertBoolTrue_597) {
    YAML::Node node;
    node = true;
    EXPECT_TRUE(node.as<bool>());
}

// Test convert with bool false
TEST_F(YamlConvertTest_597, ConvertBoolFalse_597) {
    YAML::Node node;
    node = false;
    EXPECT_FALSE(node.as<bool>());
}

// Test convert with int
TEST_F(YamlConvertTest_597, ConvertInt_597) {
    YAML::Node node;
    node = 42;
    EXPECT_EQ(node.as<int>(), 42);
}

// Test convert with double
TEST_F(YamlConvertTest_597, ConvertDouble_597) {
    YAML::Node node;
    node = 3.14;
    EXPECT_DOUBLE_EQ(node.as<double>(), 3.14);
}

// Test convert with negative int
TEST_F(YamlConvertTest_597, ConvertNegativeInt_597) {
    YAML::Node node;
    node = -100;
    EXPECT_EQ(node.as<int>(), -100);
}

// Test convert with zero
TEST_F(YamlConvertTest_597, ConvertZero_597) {
    YAML::Node node;
    node = 0;
    EXPECT_EQ(node.as<int>(), 0);
}

// Test that encoding a string with null byte terminates at null
TEST_F(YamlConvertTest_597, EncodeStringWithEmbeddedContent_597) {
    const char* input = "abc";
    YAML::Node node = YAML::Node(input);
    EXPECT_EQ(node.as<std::string>().size(), 3u);
}

// Test conversion failure for incompatible types
TEST_F(YamlConvertTest_597, ConvertIncompatibleTypeThrows_597) {
    YAML::Node node;
    node = "not_a_number";
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}
