// File: test/emittermanip_test_19.cpp
#include <gtest/gtest.h>

#include <string>
#include <type_traits>

#include "yaml-cpp/emittermanip.h"

namespace {

TEST(EmitterManipTest_19, CommentReturns_CommentType_19) {
  using Ret = decltype(YAML::Comment(std::string("x")));
  EXPECT_TRUE((std::is_same<Ret, YAML::_Comment>::value));
}

TEST(EmitterManipTest_19, CommentWithEmptyStringPreservesContent_19) {
  const YAML::_Comment c = YAML::Comment(std::string{});
  EXPECT_EQ(c.content, "");
}

TEST(EmitterManipTest_19, CommentWithNonEmptyStringPreservesContent_19) {
  const std::string s = "hello";
  const YAML::_Comment c = YAML::Comment(s);
  EXPECT_EQ(c.content, s);
}

TEST(EmitterManipTest_19, CommentWithUnicodePreservesContent_19) {
  const std::string s = u8"안녕하세요 🌱 YAML";
  const YAML::_Comment c = YAML::Comment(s);
  EXPECT_EQ(c.content, s);
}

TEST(EmitterManipTest_19, CommentWithLargeStringPreservesContent_19) {
  const std::string s(1 << 16, 'a');  // 65536 chars
  const YAML::_Comment c = YAML::Comment(s);
  EXPECT_EQ(c.content.size(), s.size());
  EXPECT_EQ(c.content, s);
}

TEST(EmitterManipTest_19, CommentDoesNotThrowForTypicalInputs_19) {
  EXPECT_NO_THROW((void)YAML::Comment(std::string("x")));
  EXPECT_NO_THROW((void)YAML::Comment(std::string{}));
  EXPECT_NO_THROW((void)YAML::Comment(std::string(1024, 'b')));
}

}  // namespace
