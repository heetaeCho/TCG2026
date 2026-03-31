#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/exceptions.h"

// Test normal operation with a simple key string
TEST(KeyNotFoundWithKeyTest_82, ReturnsFormattedStringWithSimpleKey_82) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("mykey");
    EXPECT_EQ(result, "key not found: mykey");
}

// Test with an empty key string
TEST(KeyNotFoundWithKeyTest_82, ReturnsFormattedStringWithEmptyKey_82) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("");
    EXPECT_EQ(result, "key not found: ");
}

// Test with a key containing spaces
TEST(KeyNotFoundWithKeyTest_82, ReturnsFormattedStringWithSpacesInKey_82) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("my key with spaces");
    EXPECT_EQ(result, "key not found: my key with spaces");
}

// Test with a key containing special characters
TEST(KeyNotFoundWithKeyTest_82, ReturnsFormattedStringWithSpecialCharacters_82) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("key!@#$%^&*()");
    EXPECT_EQ(result, "key not found: key!@#$%^&*()");
}

// Test with a numeric key string
TEST(KeyNotFoundWithKeyTest_82, ReturnsFormattedStringWithNumericKey_82) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("12345");
    EXPECT_EQ(result, "key not found: 12345");
}

// Test with a very long key string
TEST(KeyNotFoundWithKeyTest_82, ReturnsFormattedStringWithLongKey_82) {
    std::string longKey(1000, 'a');
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(longKey);
    std::string expected = "key not found: " + longKey;
    EXPECT_EQ(result, expected);
}

// Test with a key containing newline characters
TEST(KeyNotFoundWithKeyTest_82, ReturnsFormattedStringWithNewlineInKey_82) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("line1\nline2");
    EXPECT_EQ(result, "key not found: line1\nline2");
}

// Test with a key containing tab characters
TEST(KeyNotFoundWithKeyTest_82, ReturnsFormattedStringWithTabInKey_82) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("key\twith\ttabs");
    EXPECT_EQ(result, "key not found: key\twith\ttabs");
}

// Test that the result starts with the KEY_NOT_FOUND constant
TEST(KeyNotFoundWithKeyTest_82, ResultStartsWithKeyNotFoundConstant_82) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("somekey");
    EXPECT_EQ(result.substr(0, strlen(YAML::ErrorMsg::KEY_NOT_FOUND)), 
              std::string(YAML::ErrorMsg::KEY_NOT_FOUND));
}

// Test that the KEY_NOT_FOUND constant has the expected value
TEST(KeyNotFoundWithKeyTest_82, KeyNotFoundConstantValue_82) {
    EXPECT_STREQ(YAML::ErrorMsg::KEY_NOT_FOUND, "key not found");
}

// Test with a key containing colon and space (potential format collision)
TEST(KeyNotFoundWithKeyTest_82, ReturnsFormattedStringWithColonSpaceInKey_82) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("key: value");
    EXPECT_EQ(result, "key not found: key: value");
}

// Test with a single character key
TEST(KeyNotFoundWithKeyTest_82, ReturnsFormattedStringWithSingleCharKey_82) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("x");
    EXPECT_EQ(result, "key not found: x");
}

// Test with unicode-like characters in key
TEST(KeyNotFoundWithKeyTest_82, ReturnsFormattedStringWithUnicodeKey_82) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("ключ");
    EXPECT_EQ(result, "key not found: ключ");
}

// Test that result contains the separator ": " between the message and key
TEST(KeyNotFoundWithKeyTest_82, ContainsSeparatorBetweenMessageAndKey_82) {
    std::string key = "testkey";
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    std::string separator = ": ";
    size_t pos = result.find(separator);
    EXPECT_NE(pos, std::string::npos);
    EXPECT_EQ(result.substr(pos + separator.size()), key);
}
