#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test fixture for YAML Node convert tests
class YamlConvertTest_598 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test encoding a simple string literal
TEST_F(YamlConvertTest_598, EncodeSimpleString_598) {
    YAML::Node node = YAML::Node("hello");
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test encoding an empty string
TEST_F(YamlConvertTest_598, EncodeEmptyString_598) {
    YAML::Node node = YAML::Node("");
    EXPECT_EQ(node.as<std::string>(), "");
}

// Test encoding a string with special characters
TEST_F(YamlConvertTest_598, EncodeSpecialCharacters_598) {
    YAML::Node node = YAML::Node("hello\nworld");
    EXPECT_EQ(node.as<std::string>(), "hello\nworld");
}

// Test encoding a string with spaces
TEST_F(YamlConvertTest_598, EncodeStringWithSpaces_598) {
    YAML::Node node = YAML::Node("hello world");
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

// Test encoding a single character string
TEST_F(YamlConvertTest_598, EncodeSingleChar_598) {
    YAML::Node node = YAML::Node("a");
    EXPECT_EQ(node.as<std::string>(), "a");
}

// Test that the node is defined after encoding
TEST_F(YamlConvertTest_598, NodeIsDefinedAfterEncode_598) {
    YAML::Node node = YAML::Node("test");
    EXPECT_TRUE(node.IsDefined());
}

// Test that the node is a scalar after encoding a string
TEST_F(YamlConvertTest_598, NodeIsScalarAfterEncode_598) {
    YAML::Node node = YAML::Node("test");
    EXPECT_TRUE(node.IsScalar());
}

// Test encoding a string with numeric content
TEST_F(YamlConvertTest_598, EncodeNumericString_598) {
    YAML::Node node = YAML::Node("12345");
    EXPECT_EQ(node.as<std::string>(), "12345");
}

// Test encoding a string with tab characters
TEST_F(YamlConvertTest_598, EncodeStringWithTabs_598) {
    YAML::Node node = YAML::Node("col1\tcol2");
    EXPECT_EQ(node.as<std::string>(), "col1\tcol2");
}

// Test encoding a long string
TEST_F(YamlConvertTest_598, EncodeLongString_598) {
    std::string longStr(1000, 'x');
    YAML::Node node = YAML::Node(longStr.c_str());
    EXPECT_EQ(node.as<std::string>(), longStr);
}

// Test encoding integer values
TEST_F(YamlConvertTest_598, EncodeInteger_598) {
    YAML::Node node = YAML::Node(42);
    EXPECT_EQ(node.as<int>(), 42);
}

// Test encoding negative integer
TEST_F(YamlConvertTest_598, EncodeNegativeInteger_598) {
    YAML::Node node = YAML::Node(-100);
    EXPECT_EQ(node.as<int>(), -100);
}

// Test encoding zero
TEST_F(YamlConvertTest_598, EncodeZero_598) {
    YAML::Node node = YAML::Node(0);
    EXPECT_EQ(node.as<int>(), 0);
}

// Test encoding double values
TEST_F(YamlConvertTest_598, EncodeDouble_598) {
    YAML::Node node = YAML::Node(3.14);
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

// Test encoding boolean true
TEST_F(YamlConvertTest_598, EncodeBoolTrue_598) {
    YAML::Node node = YAML::Node(true);
    EXPECT_TRUE(node.as<bool>());
}

// Test encoding boolean false
TEST_F(YamlConvertTest_598, EncodeBoolFalse_598) {
    YAML::Node node = YAML::Node(false);
    EXPECT_FALSE(node.as<bool>());
}

// Test converting string to node and back
TEST_F(YamlConvertTest_598, RoundTripString_598) {
    std::string original = "round trip test";
    YAML::Node node;
    node = original;
    std::string result = node.as<std::string>();
    EXPECT_EQ(result, original);
}

// Test that node type is not null after encoding
TEST_F(YamlConvertTest_598, NodeNotNullAfterEncode_598) {
    YAML::Node node = YAML::Node("something");
    EXPECT_FALSE(node.IsNull());
}

// Test encoding a string with YAML special characters
TEST_F(YamlConvertTest_598, EncodeYamlSpecialChars_598) {
    YAML::Node node = YAML::Node("key: value");
    EXPECT_EQ(node.as<std::string>(), "key: value");
}

// Test encoding unicode-like content (ASCII representation)
TEST_F(YamlConvertTest_598, EncodeStringWithBrackets_598) {
    YAML::Node node = YAML::Node("[1, 2, 3]");
    EXPECT_EQ(node.as<std::string>(), "[1, 2, 3]");
}
