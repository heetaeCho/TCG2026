#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/exceptions.h"

// Test normal operation with a simple key
TEST(KeyNotFoundWithKeyTest_83, NormalKey_83) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("mykey");
    EXPECT_EQ(result, "key not found: mykey");
}

// Test with an empty key string
TEST(KeyNotFoundWithKeyTest_83, EmptyKey_83) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("");
    EXPECT_EQ(result, "key not found: ");
}

// Test with a key containing spaces
TEST(KeyNotFoundWithKeyTest_83, KeyWithSpaces_83) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("my key with spaces");
    EXPECT_EQ(result, "key not found: my key with spaces");
}

// Test with a key containing special characters
TEST(KeyNotFoundWithKeyTest_83, KeyWithSpecialCharacters_83) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("key!@#$%^&*()");
    EXPECT_EQ(result, "key not found: key!@#$%^&*()");
}

// Test with a single character key
TEST(KeyNotFoundWithKeyTest_83, SingleCharKey_83) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("x");
    EXPECT_EQ(result, "key not found: x");
}

// Test with numeric string key
TEST(KeyNotFoundWithKeyTest_83, NumericKey_83) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("12345");
    EXPECT_EQ(result, "key not found: 12345");
}

// Test that the result starts with KEY_NOT_FOUND constant
TEST(KeyNotFoundWithKeyTest_83, StartsWithKeyNotFound_83) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("test");
    EXPECT_EQ(result.substr(0, std::string(YAML::ErrorMsg::KEY_NOT_FOUND).size()),
              YAML::ErrorMsg::KEY_NOT_FOUND);
}

// Test with a key containing newline characters
TEST(KeyNotFoundWithKeyTest_83, KeyWithNewline_83) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("line1\nline2");
    EXPECT_EQ(result, "key not found: line1\nline2");
}

// Test with a key containing null-terminated string boundary (long key)
TEST(KeyNotFoundWithKeyTest_83, LongKey_83) {
    std::string longKey(1000, 'a');
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(longKey.c_str());
    std::string expected = std::string("key not found: ") + longKey;
    EXPECT_EQ(result, expected);
}

// Test that KEY_NOT_FOUND global constant has the expected value
TEST(KeyNotFoundConstantTest_83, ConstantValue_83) {
    EXPECT_STREQ(YAML::ErrorMsg::KEY_NOT_FOUND, "key not found");
}

// Test with a key containing tab characters
TEST(KeyNotFoundWithKeyTest_83, KeyWithTab_83) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("key\twith\ttabs");
    EXPECT_EQ(result, "key not found: key\twith\ttabs");
}

// Test format: colon and space separator between message and key
TEST(KeyNotFoundWithKeyTest_83, FormatContainsColonSpace_83) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY("testkey");
    std::string separator = ": ";
    size_t pos = result.find(separator);
    EXPECT_NE(pos, std::string::npos);
    EXPECT_EQ(result.substr(pos + separator.size()), "testkey");
}
