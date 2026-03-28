// File: test/exceptions_test_83.cpp

#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/exceptions.h"

namespace {

class ErrorMsgTest_83 : public ::testing::Test {};

TEST_F(ErrorMsgTest_83, KeyNotFoundWithKey_FormatsMessageWithProvidedKey_83) {
  const char* key = "alpha";
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);

  const std::string expected =
      std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": " + key;
  EXPECT_EQ(msg, expected);
}

TEST_F(ErrorMsgTest_83, KeyNotFoundWithKey_AllowsEmptyKey_83) {
  const char* key = "";
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);

  const std::string expected =
      std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": ";
  EXPECT_EQ(msg, expected);
}

TEST_F(ErrorMsgTest_83, KeyNotFoundWithKey_PreservesSpecialCharacters_83) {
  const char* key = "a/b:c d\t[]{}()!@#$%^&*-=+_.,?~";
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);

  const std::string expected =
      std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": " + key;
  EXPECT_EQ(msg, expected);
}

TEST_F(ErrorMsgTest_83, KeyNotFoundWithKey_DoesNotTruncateLongKey_83) {
  const std::string long_key(10'000, 'k');
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(long_key.c_str());

  const std::string expected =
      std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": " + long_key;
  EXPECT_EQ(msg, expected);
}

TEST_F(ErrorMsgTest_83, KeyNotFoundWithKey_ReturnsIndependentStringsAcrossCalls_83) {
  const std::string key1 = "first";
  const std::string key2 = "second";

  const std::string msg1 = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key1.c_str());
  const std::string msg2 = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key2.c_str());

  const std::string expected1 =
      std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": " + key1;
  const std::string expected2 =
      std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": " + key2;

  EXPECT_EQ(msg1, expected1);
  EXPECT_EQ(msg2, expected2);
  EXPECT_NE(msg1, msg2);
}

}  // namespace
