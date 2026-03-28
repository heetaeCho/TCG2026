#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <string_view>

// Test normal encoding of a simple string_view
TEST(YAMLConvertStringView_600, EncodeSimpleString_600) {
    std::string_view sv = "hello";
    YAML::Node node = YAML::Node(std::string(sv));
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test encoding of an empty string_view
TEST(YAMLConvertStringView_600, EncodeEmptyStringView_600) {
    std::string_view sv = "";
    YAML::Node node = YAML::Node(std::string(sv));
    EXPECT_EQ(node.as<std::string>(), "");
}

// Test encoding of a string_view with spaces
TEST(YAMLConvertStringView_600, EncodeStringViewWithSpaces_600) {
    std::string_view sv = "hello world";
    YAML::Node node = YAML::Node(std::string(sv));
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

// Test encoding of a string_view with special characters
TEST(YAMLConvertStringView_600, EncodeStringViewWithSpecialChars_600) {
    std::string_view sv = "key: value\nnewline";
    YAML::Node node = YAML::Node(std::string(sv));
    EXPECT_EQ(node.as<std::string>(), "key: value\nnewline");
}

// Test encoding of a string_view that is a substring
TEST(YAMLConvertStringView_600, EncodeSubstringView_600) {
    std::string original = "hello world";
    std::string_view sv = std::string_view(original).substr(0, 5);
    YAML::Node node = YAML::Node(std::string(sv));
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test encoding of a single character string_view
TEST(YAMLConvertStringView_600, EncodeSingleCharStringView_600) {
    std::string_view sv = "a";
    YAML::Node node = YAML::Node(std::string(sv));
    EXPECT_EQ(node.as<std::string>(), "a");
}

// Test that the node created is a scalar
TEST(YAMLConvertStringView_600, EncodeCreatesScalarNode_600) {
    std::string_view sv = "test";
    YAML::Node node = YAML::Node(std::string(sv));
    EXPECT_TRUE(node.IsScalar());
}

// Test encoding a string_view with null characters embedded
TEST(YAMLConvertStringView_600, EncodeStringViewWithEmbeddedNull_600) {
    std::string str_with_null("hello\0world", 11);
    std::string_view sv(str_with_null.data(), str_with_null.size());
    YAML::Node node = YAML::Node(std::string(sv));
    EXPECT_EQ(node.as<std::string>().size(), 11u);
}

// Test encoding a long string_view
TEST(YAMLConvertStringView_600, EncodeLongStringView_600) {
    std::string long_str(10000, 'x');
    std::string_view sv = long_str;
    YAML::Node node = YAML::Node(std::string(sv));
    EXPECT_EQ(node.as<std::string>().size(), 10000u);
    EXPECT_EQ(node.as<std::string>(), long_str);
}

// Test encoding a string_view with unicode-like content
TEST(YAMLConvertStringView_600, EncodeStringViewWithUnicode_600) {
    std::string_view sv = u8"日本語テスト";
    YAML::Node node = YAML::Node(std::string(sv));
    EXPECT_EQ(node.as<std::string>(), std::string(sv));
}

// Test that the node is defined after encoding
TEST(YAMLConvertStringView_600, EncodeResultIsDefined_600) {
    std::string_view sv = "defined";
    YAML::Node node = YAML::Node(std::string(sv));
    EXPECT_TRUE(node.IsDefined());
}

// Test using convert directly if available
TEST(YAMLConvertStringView_600, ConvertStringRoundTrip_600) {
    std::string original = "roundtrip";
    YAML::Node node = YAML::Node(original);
    std::string result;
    EXPECT_TRUE(YAML::convert<std::string>::decode(node, result));
    EXPECT_EQ(result, original);
}

// Test encoding a string_view with tabs and whitespace
TEST(YAMLConvertStringView_600, EncodeStringViewWithTabsAndWhitespace_600) {
    std::string_view sv = "\t  \n\r";
    YAML::Node node = YAML::Node(std::string(sv));
    EXPECT_EQ(node.as<std::string>(), std::string(sv));
}
