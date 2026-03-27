// emittermanip_localtag_test.cpp
//
// Unit tests for yaml-cpp/emittermanip.h (LocalTag)
//
// NOTE:
// - Treat implementation as a black box.
// - Tests validate only observable behavior via the public interface.

#include <gtest/gtest.h>

#include <string>

// The function under test is declared inline here.
#include "yaml-cpp/emittermanip.h"

namespace {

class LocalTagTest_16 : public ::testing::Test {};

TEST_F(LocalTagTest_16, ReturnsTagWithProvidedContent_16) {
  const std::string content = "my_tag_suffix";
  const YAML::_Tag tag = YAML::LocalTag(content);

  const YAML::_Tag expected("", content, YAML::_Tag::Type::PrimaryHandle);
  EXPECT_EQ(tag, expected);
}

TEST_F(LocalTagTest_16, EmptyContentIsPreserved_16) {
  const std::string content;
  const YAML::_Tag tag = YAML::LocalTag(content);

  const YAML::_Tag expected("", "", YAML::_Tag::Type::PrimaryHandle);
  EXPECT_EQ(tag, expected);
}

TEST_F(LocalTagTest_16, ContentWithSpecialCharactersIsPreserved_16) {
  const std::string content = "a/b:c?d&e#f[g] (h)\n\t\u00E9";
  const YAML::_Tag tag = YAML::LocalTag(content);

  const YAML::_Tag expected("", content, YAML::_Tag::Type::PrimaryHandle);
  EXPECT_EQ(tag, expected);
}

TEST_F(LocalTagTest_16, TwoCallsWithSameContentProduceEqualTags_16) {
  const std::string content = "repeatable";
  const YAML::_Tag a = YAML::LocalTag(content);
  const YAML::_Tag b = YAML::LocalTag(content);

  EXPECT_EQ(a, b);
}

TEST_F(LocalTagTest_16, DifferentContentProducesDifferentTags_16) {
  const YAML::_Tag a = YAML::LocalTag("one");
  const YAML::_Tag b = YAML::LocalTag("two");

  EXPECT_NE(a, b);
}

TEST_F(LocalTagTest_16, TagDoesNotAliasInputStringBuffer_16) {
  std::string content = "original";
  const YAML::_Tag tag = YAML::LocalTag(content);

  // Mutate the input after creating the tag; the tag should still equal the
  // value created from the original content.
  content = "mutated";

  const YAML::_Tag expected("", "original", YAML::_Tag::Type::PrimaryHandle);
  EXPECT_EQ(tag, expected);
}

TEST_F(LocalTagTest_16, VeryLargeContentIsHandled_16) {
  const std::string content(10000, 'x');
  const YAML::_Tag tag = YAML::LocalTag(content);

  const YAML::_Tag expected("", content, YAML::_Tag::Type::PrimaryHandle);
  EXPECT_EQ(tag, expected);
}

}  // namespace
