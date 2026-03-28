#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/exceptions.h"

// Test normal operation with a typical key string
TEST(BAD_SUBSCRIPT_WITH_KEY_Test_86, NormalKey_86) {
  std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("mykey");
  EXPECT_EQ(result, "operator[] call on a scalar (key: \"mykey\")");
}

// Test with an empty key string
TEST(BAD_SUBSCRIPT_WITH_KEY_Test_86, EmptyKey_86) {
  std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("");
  EXPECT_EQ(result, "operator[] call on a scalar (key: \"\")");
}

// Test with a key containing spaces
TEST(BAD_SUBSCRIPT_WITH_KEY_Test_86, KeyWithSpaces_86) {
  std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("my key with spaces");
  EXPECT_EQ(result, "operator[] call on a scalar (key: \"my key with spaces\")");
}

// Test with a key containing special characters
TEST(BAD_SUBSCRIPT_WITH_KEY_Test_86, KeyWithSpecialCharacters_86) {
  std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("key!@#$%^&*()");
  EXPECT_EQ(result, "operator[] call on a scalar (key: \"key!@#$%^&*()\")");
}

// Test with a key containing quotes
TEST(BAD_SUBSCRIPT_WITH_KEY_Test_86, KeyWithQuotes_86) {
  std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("key\"with\"quotes");
  EXPECT_EQ(result, "operator[] call on a scalar (key: \"key\"with\"quotes\")");
}

// Test with a numeric string key
TEST(BAD_SUBSCRIPT_WITH_KEY_Test_86, NumericKey_86) {
  std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("12345");
  EXPECT_EQ(result, "operator[] call on a scalar (key: \"12345\")");
}

// Test with a very long key
TEST(BAD_SUBSCRIPT_WITH_KEY_Test_86, VeryLongKey_86) {
  std::string longKey(1000, 'x');
  std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(longKey);
  std::string expected = std::string("operator[] call on a scalar (key: \"") + longKey + "\")";
  EXPECT_EQ(result, expected);
}

// Test with a key containing newline characters
TEST(BAD_SUBSCRIPT_WITH_KEY_Test_86, KeyWithNewlines_86) {
  std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("line1\nline2");
  EXPECT_EQ(result, "operator[] call on a scalar (key: \"line1\nline2\")");
}

// Test with a key containing tab characters
TEST(BAD_SUBSCRIPT_WITH_KEY_Test_86, KeyWithTabs_86) {
  std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("col1\tcol2");
  EXPECT_EQ(result, "operator[] call on a scalar (key: \"col1\tcol2\")");
}

// Test with a key containing null character embedded in string
TEST(BAD_SUBSCRIPT_WITH_KEY_Test_86, KeyWithNullChar_86) {
  std::string keyWithNull("before");
  keyWithNull += '\0';
  keyWithNull += "after";
  std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(keyWithNull);
  // The result should contain the portion before null since stringstream may stop at null
  EXPECT_FALSE(result.empty());
  // At minimum, should start with BAD_SUBSCRIPT message
  EXPECT_NE(result.find("operator[] call on a scalar"), std::string::npos);
}

// Test that the BAD_SUBSCRIPT constant is correct
TEST(BAD_SUBSCRIPT_Test_86, ConstantValue_86) {
  EXPECT_STREQ(YAML::ErrorMsg::BAD_SUBSCRIPT, "operator[] call on a scalar");
}

// Test that the result contains the BAD_SUBSCRIPT prefix
TEST(BAD_SUBSCRIPT_WITH_KEY_Test_86, ContainsBadSubscriptPrefix_86) {
  std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("test");
  EXPECT_EQ(result.substr(0, strlen(YAML::ErrorMsg::BAD_SUBSCRIPT)),
            std::string(YAML::ErrorMsg::BAD_SUBSCRIPT));
}

// Test with a single character key
TEST(BAD_SUBSCRIPT_WITH_KEY_Test_86, SingleCharKey_86) {
  std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("a");
  EXPECT_EQ(result, "operator[] call on a scalar (key: \"a\")");
}

// Test with unicode-like characters
TEST(BAD_SUBSCRIPT_WITH_KEY_Test_86, KeyWithUnicodeChars_86) {
  std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("café");
  EXPECT_EQ(result, "operator[] call on a scalar (key: \"café\")");
}
