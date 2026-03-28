// File: test/exceptions_test_89.cpp

#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/exceptions.h"

namespace {

TEST(ErrorMsgTest_89, EmptyKeyReturnsInvalidNode_89) {
  const std::string out = YAML::ErrorMsg::INVALID_NODE_WITH_KEY("");
  EXPECT_EQ(out, std::string(YAML::ErrorMsg::INVALID_NODE));
}

TEST(ErrorMsgTest_89, NonEmptyKeyFormatsMessageWithKey_89) {
  const std::string key = "abc";
  const std::string out = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);

  const std::string expected = "invalid node; first invalid key: \"" + key + "\"";
  EXPECT_EQ(out, expected);
}

TEST(ErrorMsgTest_89, KeyWithWhitespaceIsPreserved_89) {
  const std::string key = "  a b\tc  ";
  const std::string out = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);

  const std::string expected = "invalid node; first invalid key: \"" + key + "\"";
  EXPECT_EQ(out, expected);
}

TEST(ErrorMsgTest_89, KeyContainingQuotesIsIncludedVerbatim_89) {
  const std::string key = "k\"ey";
  const std::string out = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);

  // The interface returns a string; verify the key is embedded as-is between the wrapping quotes.
  const std::string expected = "invalid node; first invalid key: \"" + key + "\"";
  EXPECT_EQ(out, expected);
}

TEST(ErrorMsgTest_89, VeryLongKeyIsHandled_89) {
  const std::string key(10'000, 'x');
  const std::string out = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);

  const std::string expected_prefix = "invalid node; first invalid key: \"";
  ASSERT_GE(out.size(), expected_prefix.size() + key.size() + 1u);
  EXPECT_EQ(out.substr(0, expected_prefix.size()), expected_prefix);
  EXPECT_EQ(out.substr(expected_prefix.size(), key.size()), key);
  EXPECT_EQ(out.back(), '"');
}

TEST(ErrorMsgTest_89, DoesNotThrowForTypicalInputs_89) {
  EXPECT_NO_THROW((void)YAML::ErrorMsg::INVALID_NODE_WITH_KEY(""));
  EXPECT_NO_THROW((void)YAML::ErrorMsg::INVALID_NODE_WITH_KEY("key"));
  EXPECT_NO_THROW((void)YAML::ErrorMsg::INVALID_NODE_WITH_KEY(std::string(1024, 'z')));
}

}  // namespace
