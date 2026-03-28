#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/exceptions.h"

// Test with a non-empty key
TEST(InvalidNodeWithKeyTest_89, NonEmptyKeyReturnsFormattedMessage_89) {
    std::string key = "foo";
    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);
    EXPECT_EQ(result, "invalid node; first invalid key: \"foo\"");
}

// Test with an empty key returns INVALID_NODE constant
TEST(InvalidNodeWithKeyTest_89, EmptyKeyReturnsInvalidNodeMessage_89) {
    std::string key = "";
    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);
    EXPECT_EQ(result, YAML::ErrorMsg::INVALID_NODE);
}

// Test with a key containing spaces
TEST(InvalidNodeWithKeyTest_89, KeyWithSpacesReturnsFormattedMessage_89) {
    std::string key = "my key";
    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);
    EXPECT_EQ(result, "invalid node; first invalid key: \"my key\"");
}

// Test with a key containing special characters
TEST(InvalidNodeWithKeyTest_89, KeyWithSpecialCharsReturnsFormattedMessage_89) {
    std::string key = "key!@#$%^&*()";
    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);
    EXPECT_EQ(result, "invalid node; first invalid key: \"key!@#$%^&*()\"");
}

// Test with a key containing quotes
TEST(InvalidNodeWithKeyTest_89, KeyWithQuotesReturnsFormattedMessage_89) {
    std::string key = "key\"with\"quotes";
    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);
    EXPECT_EQ(result, "invalid node; first invalid key: \"key\"with\"quotes\"");
}

// Test with a single character key
TEST(InvalidNodeWithKeyTest_89, SingleCharKeyReturnsFormattedMessage_89) {
    std::string key = "x";
    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);
    EXPECT_EQ(result, "invalid node; first invalid key: \"x\"");
}

// Test with a very long key
TEST(InvalidNodeWithKeyTest_89, VeryLongKeyReturnsFormattedMessage_89) {
    std::string key(1000, 'a');
    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);
    std::string expected = "invalid node; first invalid key: \"" + key + "\"";
    EXPECT_EQ(result, expected);
}

// Test with a key containing newlines
TEST(InvalidNodeWithKeyTest_89, KeyWithNewlinesReturnsFormattedMessage_89) {
    std::string key = "line1\nline2";
    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);
    EXPECT_EQ(result, "invalid node; first invalid key: \"line1\nline2\"");
}

// Test with a key containing null characters embedded
TEST(InvalidNodeWithKeyTest_89, KeyWithEmbeddedNullReturnsFormattedMessage_89) {
    std::string key("ab\0cd", 5);
    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);
    std::string expected = std::string("invalid node; first invalid key: \"") + key + "\"";
    EXPECT_EQ(result, expected);
}

// Test with a numeric key
TEST(InvalidNodeWithKeyTest_89, NumericKeyReturnsFormattedMessage_89) {
    std::string key = "12345";
    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);
    EXPECT_EQ(result, "invalid node; first invalid key: \"12345\"");
}

// Verify INVALID_NODE constant value
TEST(InvalidNodeWithKeyTest_89, InvalidNodeConstantHasExpectedValue_89) {
    std::string expected = "invalid node; this may result from using a map iterator as a sequence iterator, or vice-versa";
    EXPECT_EQ(std::string(YAML::ErrorMsg::INVALID_NODE), expected);
}

// Test with a key containing tab characters
TEST(InvalidNodeWithKeyTest_89, KeyWithTabReturnsFormattedMessage_89) {
    std::string key = "key\twith\ttabs";
    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);
    EXPECT_EQ(result, "invalid node; first invalid key: \"key\twith\ttabs\"");
}

// Test with unicode-like content in key
TEST(InvalidNodeWithKeyTest_89, KeyWithUTF8ContentReturnsFormattedMessage_89) {
    std::string key = "\xC3\xA9\xC3\xA8"; // é è in UTF-8
    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);
    std::string expected = "invalid node; first invalid key: \"" + key + "\"";
    EXPECT_EQ(result, expected);
}
