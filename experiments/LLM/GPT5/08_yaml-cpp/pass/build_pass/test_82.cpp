// exceptions_test_82.cpp
#include <gtest/gtest.h>

#include <string>
#include <sstream>

// The production header under test.
#include "yaml-cpp/exceptions.h"

namespace {

TEST(ErrorMsgTest_82, KeyNotFoundWithKey_AppendsColonSpaceAndKey_82) {
  const std::string key = "abc";
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);

  EXPECT_EQ(msg, std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": " + key);
}

TEST(ErrorMsgTest_82, KeyNotFoundWithKey_EmptyKeyStillAppendsDelimiter_82) {
  const std::string key = "";
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);

  EXPECT_EQ(msg, std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": ");
}

TEST(ErrorMsgTest_82, KeyNotFoundWithKey_KeyWithWhitespaceIsPreserved_82) {
  const std::string key = "  spaced key  ";
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);

  EXPECT_EQ(msg, std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": " + key);
}

TEST(ErrorMsgTest_82, KeyNotFoundWithKey_KeyWithNewlineIsPreserved_82) {
  const std::string key = "line1\nline2";
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);

  EXPECT_EQ(msg, std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": " + key);
}

TEST(ErrorMsgTest_82, KeyNotFoundWithKey_KeyWithNullCharIsPreservedInLengthAndContent_82) {
  // std::string can contain '\0' inside; verify behavior via exact equality and size.
  const std::string key = std::string("ab\0cd", 5);
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);

  const std::string expected = std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": " + key;
  EXPECT_EQ(msg, expected);
  EXPECT_EQ(msg.size(), expected.size());
  // Ensure the embedded null is at the expected position (prefix + ": " is 2 chars after prefix).
  const std::string prefix = std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": ";
  ASSERT_GE(msg.size(), prefix.size() + key.size());
  EXPECT_EQ(msg[prefix.size() + 2], '\0');  // "ab\0cd": null at index 2 within key
}

TEST(ErrorMsgTest_82, KeyNotFoundWithKey_LargeKeyDoesNotThrow_82) {
  // Observable error case: should not throw for large input.
  const std::string key(1 << 20, 'x');  // 1 MiB
  EXPECT_NO_THROW({
    const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    EXPECT_EQ(msg.size(),
              std::string(YAML::ErrorMsg::KEY_NOT_FOUND).size() + 2 + key.size());
  });
}

TEST(ErrorMsgTest_82, KeyNotFoundWithKey_ReturnsIndependentStringFromInputLifetime_82) {
  std::string msg;
  {
    std::string key = "temp";
    msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    key.assign("mutated");
  }
  // Result should remain the original composed message.
  EXPECT_EQ(msg, std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": " + "temp");
}

TEST(ErrorMsgTest_82, KeyNotFoundWithKey_IdempotentForSameInput_82) {
  const std::string key = "same";
  const std::string msg1 = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  const std::string msg2 = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);

  EXPECT_EQ(msg1, msg2);
}

}  // namespace
