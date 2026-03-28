// File: test_exceptions_86.cpp
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/exceptions.h"

namespace {

class ErrorMsgTest_86 : public ::testing::Test {};

TEST_F(ErrorMsgTest_86, BadSubscriptWithKey_AppendsKeyWithQuotes_86) {
  const std::string key = "abc";
  const std::string msg = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);

  const std::string expected =
      std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"abc\")";
  EXPECT_EQ(msg, expected);
}

TEST_F(ErrorMsgTest_86, BadSubscriptWithKey_EmptyKey_86) {
  const std::string key;
  const std::string msg = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);

  const std::string expected =
      std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"\")";
  EXPECT_EQ(msg, expected);
}

TEST_F(ErrorMsgTest_86, BadSubscriptWithKey_KeyContainsSpaces_86) {
  const std::string key = "hello world";
  const std::string msg = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);

  const std::string expected =
      std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"hello world\")";
  EXPECT_EQ(msg, expected);
}

TEST_F(ErrorMsgTest_86, BadSubscriptWithKey_KeyContainsQuotes_PreservesContent_86) {
  const std::string key = "a\"b\"c";
  const std::string msg = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);

  // Observable behavior: returned message includes the key content as-provided,
  // wrapped in quotes in the message.
  const std::string expected =
      std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"a\"b\"c\")";
  EXPECT_EQ(msg, expected);
}

TEST_F(ErrorMsgTest_86, BadSubscriptWithKey_KeyContainsNewlines_PreservesContent_86) {
  const std::string key = std::string("line1\nline2");
  const std::string msg = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);

  const std::string expected =
      std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"line1\nline2\")";
  EXPECT_EQ(msg, expected);
}

TEST_F(ErrorMsgTest_86, BadSubscriptWithKey_UnicodeKey_86) {
  const std::string key = u8"키-値-😊";
  const std::string msg = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);

  const std::string expected =
      std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"" + key + "\")";
  EXPECT_EQ(msg, expected);
}

TEST_F(ErrorMsgTest_86, BadSubscriptWithKey_LargeKey_DoesNotThrowAndFormats_86) {
  const std::string key(4096, 'x');

  EXPECT_NO_THROW({
    const std::string msg = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    const std::string expected =
        std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"" + key + "\")";
    EXPECT_EQ(msg, expected);
  });
}

}  // namespace
