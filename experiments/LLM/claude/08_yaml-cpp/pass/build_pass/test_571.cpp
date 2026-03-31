#include <gtest/gtest.h>
#include <string>
#include <sstream>

// Include the header under test
#include "yaml-cpp/node/impl.h"
#include "yaml-cpp/yaml.h"

// Test ID: 571

// Test key_to_string with integer key
TEST(KeyToStringTest_571, IntegerKey_571) {
  std::string result = YAML::key_to_string(42);
  EXPECT_EQ(result, "42");
}

// Test key_to_string with negative integer key
TEST(KeyToStringTest_571, NegativeIntegerKey_571) {
  std::string result = YAML::key_to_string(-10);
  EXPECT_EQ(result, "-10");
}

// Test key_to_string with zero
TEST(KeyToStringTest_571, ZeroKey_571) {
  std::string result = YAML::key_to_string(0);
  EXPECT_EQ(result, "0");
}

// Test key_to_string with string key
TEST(KeyToStringTest_571, StringKey_571) {
  std::string key = "hello";
  std::string result = YAML::key_to_string(key);
  EXPECT_EQ(result, "hello");
}

// Test key_to_string with empty string key
TEST(KeyToStringTest_571, EmptyStringKey_571) {
  std::string key = "";
  std::string result = YAML::key_to_string(key);
  EXPECT_EQ(result, "");
}

// Test key_to_string with const char* key
TEST(KeyToStringTest_571, CStringKey_571) {
  const char* key = "world";
  std::string result = YAML::key_to_string(key);
  EXPECT_EQ(result, "world");
}

// Test key_to_string with double key
TEST(KeyToStringTest_571, DoubleKey_571) {
  double key = 3.14;
  std::string result = YAML::key_to_string(key);
  // Verify it produces a non-empty string representation
  EXPECT_FALSE(result.empty());
  // Verify the string contains "3.14" (at least starts with it)
  EXPECT_NE(result.find("3.14"), std::string::npos);
}

// Test key_to_string with float key
TEST(KeyToStringTest_571, FloatKey_571) {
  float key = 2.5f;
  std::string result = YAML::key_to_string(key);
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("2.5"), std::string::npos);
}

// Test key_to_string with char key
TEST(KeyToStringTest_571, CharKey_571) {
  char key = 'A';
  std::string result = YAML::key_to_string(key);
  EXPECT_EQ(result, "A");
}

// Test key_to_string with unsigned int key
TEST(KeyToStringTest_571, UnsignedIntKey_571) {
  unsigned int key = 100u;
  std::string result = YAML::key_to_string(key);
  EXPECT_EQ(result, "100");
}

// Test key_to_string with long key
TEST(KeyToStringTest_571, LongKey_571) {
  long key = 1234567890L;
  std::string result = YAML::key_to_string(key);
  EXPECT_EQ(result, "1234567890");
}

// Test key_to_string with bool key
TEST(KeyToStringTest_571, BoolTrueKey_571) {
  bool key = true;
  std::string result = YAML::key_to_string(key);
  EXPECT_FALSE(result.empty());
}

// Test key_to_string with bool false key
TEST(KeyToStringTest_571, BoolFalseKey_571) {
  bool key = false;
  std::string result = YAML::key_to_string(key);
  EXPECT_FALSE(result.empty());
}

// Test key_to_string with large integer boundary
TEST(KeyToStringTest_571, LargeIntegerKey_571) {
  long long key = 9223372036854775807LL; // LLONG_MAX
  std::string result = YAML::key_to_string(key);
  EXPECT_EQ(result, "9223372036854775807");
}

// Test key_to_string with string containing spaces
TEST(KeyToStringTest_571, StringWithSpacesKey_571) {
  std::string key = "hello world";
  std::string result = YAML::key_to_string(key);
  EXPECT_EQ(result, "hello world");
}

// Test key_to_string with string containing special characters
TEST(KeyToStringTest_571, StringWithSpecialCharsKey_571) {
  std::string key = "key:value";
  std::string result = YAML::key_to_string(key);
  EXPECT_EQ(result, "key:value");
}

// Test key_to_string with short key
TEST(KeyToStringTest_571, ShortKey_571) {
  short key = 32767; // SHORT_MAX
  std::string result = YAML::key_to_string(key);
  EXPECT_EQ(result, "32767");
}

// Test key_to_string with negative short key
TEST(KeyToStringTest_571, NegativeShortKey_571) {
  short key = -32768; // SHORT_MIN
  std::string result = YAML::key_to_string(key);
  EXPECT_EQ(result, "-32768");
}

// Test YAML Node operations that use key_to_string implicitly
TEST(NodeKeyAccess_571, IntKeyAccess_571) {
  YAML::Node node;
  node[1] = "one";
  node[2] = "two";
  EXPECT_EQ(node[1].as<std::string>(), "one");
  EXPECT_EQ(node[2].as<std::string>(), "two");
}

TEST(NodeKeyAccess_571, StringKeyAccess_571) {
  YAML::Node node;
  node["key1"] = "value1";
  node["key2"] = "value2";
  EXPECT_EQ(node["key1"].as<std::string>(), "value1");
  EXPECT_EQ(node["key2"].as<std::string>(), "value2");
}

TEST(NodeKeyAccess_571, MixedKeyAccess_571) {
  YAML::Node node;
  node["name"] = "test";
  node[42] = "answer";
  EXPECT_EQ(node["name"].as<std::string>(), "test");
  EXPECT_EQ(node[42].as<std::string>(), "answer");
}
