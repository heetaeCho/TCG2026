#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/exceptions.h"

// Test ID: 81

// Test that KEY_NOT_FOUND_WITH_KEY returns KEY_NOT_FOUND for non-numeric types
TEST(KeyNotFoundWithKeyTest_81, ReturnsKeyNotFoundForStringType_81) {
  std::string key = "some_key";
  std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(result, YAML::ErrorMsg::KEY_NOT_FOUND);
}

TEST(KeyNotFoundWithKeyTest_81, ReturnsKeyNotFoundForConstCharPtr_81) {
  const char* key = "another_key";
  std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(result, YAML::ErrorMsg::KEY_NOT_FOUND);
}

TEST(KeyNotFoundWithKeyTest_81, ReturnsKeyNotFoundForEmptyString_81) {
  std::string key = "";
  std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(result, YAML::ErrorMsg::KEY_NOT_FOUND);
}

TEST(KeyNotFoundWithKeyTest_81, ReturnTypeIsString_81) {
  std::string key = "test";
  auto result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_FALSE(result.empty());
}

TEST(KeyNotFoundWithKeyTest_81, ReturnsConsistentResultForSameInput_81) {
  std::string key = "repeated_key";
  std::string result1 = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  std::string result2 = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(result1, result2);
}

TEST(KeyNotFoundWithKeyTest_81, ReturnsConsistentResultForDifferentNonNumericInputs_81) {
  std::string key1 = "key_a";
  std::string key2 = "key_b";
  std::string result1 = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key1);
  std::string result2 = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key2);
  // Both should return the same KEY_NOT_FOUND message since the non-numeric
  // overload doesn't use the key value
  EXPECT_EQ(result1, result2);
}

// Test with a custom non-numeric struct
struct CustomNonNumericType {
  std::string name;
};

TEST(KeyNotFoundWithKeyTest_81, ReturnsKeyNotFoundForCustomNonNumericType_81) {
  CustomNonNumericType key{"custom"};
  std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(result, YAML::ErrorMsg::KEY_NOT_FOUND);
}

TEST(KeyNotFoundWithKeyTest_81, ReturnsNonEmptyString_81) {
  std::string key = "test_key";
  std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_GT(result.size(), 0u);
}

TEST(KeyNotFoundWithKeyTest_81, ResultMatchesKeyNotFoundConstant_81) {
  const char* key = "xyz";
  std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  std::string expected = YAML::ErrorMsg::KEY_NOT_FOUND;
  EXPECT_EQ(result, expected);
}

// Test with a boolean type (bool is considered numeric in many trait systems,
// but this depends on the is_numeric implementation; we test with a clearly non-numeric type)
struct AnotherNonNumeric {};

TEST(KeyNotFoundWithKeyTest_81, WorksWithAnotherNonNumericType_81) {
  AnotherNonNumeric key;
  std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(result, YAML::ErrorMsg::KEY_NOT_FOUND);
}
