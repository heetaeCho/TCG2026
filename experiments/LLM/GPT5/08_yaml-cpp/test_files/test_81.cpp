// File: yaml-cpp/test/exceptions_test_81.cpp

#include <gtest/gtest.h>

#include <string>

#include <yaml-cpp/exceptions.h>

namespace {

struct NonNumericKeyType_81 {
  int payload = 0;
};

}  // namespace

TEST(ExceptionsTest_81, KeyNotFoundWithKey_StdStringReturnsKeyNotFound_81) {
  const std::string key = "missing_key";
  EXPECT_NO_THROW({
    const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    EXPECT_EQ(msg, YAML::ErrorMsg::KEY_NOT_FOUND);
  });
}

TEST(ExceptionsTest_81, KeyNotFoundWithKey_EmptyStringReturnsKeyNotFound_81) {
  const std::string key;
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(msg, YAML::ErrorMsg::KEY_NOT_FOUND);
}

TEST(ExceptionsTest_81, KeyNotFoundWithKey_LongStringReturnsKeyNotFound_81) {
  const std::string key(10'000, 'x');
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(msg, YAML::ErrorMsg::KEY_NOT_FOUND);
}

TEST(ExceptionsTest_81, KeyNotFoundWithKey_SpecialCharsReturnsKeyNotFound_81) {
  const std::string key = "spéçïål:\n\t[]{}!@#$%^&*()_+-=,./<>?";
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(msg, YAML::ErrorMsg::KEY_NOT_FOUND);
}

TEST(ExceptionsTest_81, KeyNotFoundWithKey_CustomNonNumericTypeReturnsKeyNotFound_81) {
  const NonNumericKeyType_81 key{123};
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(msg, YAML::ErrorMsg::KEY_NOT_FOUND);
}

TEST(ExceptionsTest_81, KeyNotFoundWithKey_ReturnValueIsStableAcrossDifferentKeys_81) {
  const std::string key1 = "a";
  const std::string key2 = "b";
  const std::string msg1 = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key1);
  const std::string msg2 = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key2);

  EXPECT_EQ(msg1, YAML::ErrorMsg::KEY_NOT_FOUND);
  EXPECT_EQ(msg2, YAML::ErrorMsg::KEY_NOT_FOUND);
  EXPECT_EQ(msg1, msg2);
}
