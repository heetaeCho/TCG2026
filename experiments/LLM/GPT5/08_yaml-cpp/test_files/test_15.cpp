// TEST_ID: 15
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/emittermanip.h"

namespace {

TEST(VerbatimTagTest_15, ConstructsVerbatimTagWithEmptyPrefix_15) {
  const auto tag = YAML::VerbatimTag("hello");

  EXPECT_EQ(tag.prefix, "");
  EXPECT_EQ(tag.content, "hello");
  EXPECT_EQ(tag.type, YAML::_Tag::Type::Verbatim);
}

TEST(VerbatimTagTest_15, HandlesEmptyContent_15) {
  const auto tag = YAML::VerbatimTag(std::string{});

  EXPECT_EQ(tag.prefix, "");
  EXPECT_EQ(tag.content, "");
  EXPECT_EQ(tag.type, YAML::_Tag::Type::Verbatim);
}

TEST(VerbatimTagTest_15, PreservesWhitespaceAndPunctuation_15) {
  const std::string content = "  spaced\tcontent\nwith:punctuation!  ";
  const auto tag = YAML::VerbatimTag(content);

  EXPECT_EQ(tag.prefix, "");
  EXPECT_EQ(tag.content, content);
  EXPECT_EQ(tag.type, YAML::_Tag::Type::Verbatim);
}

TEST(VerbatimTagTest_15, PreservesUtf8Bytes_15) {
  // Treat as UTF-8 bytes; std::string stores bytes, so this validates no mutation.
  const std::string content = u8"테스트-✓-タグ";
  const auto tag = YAML::VerbatimTag(content);

  EXPECT_EQ(tag.prefix, "");
  EXPECT_EQ(tag.content, content);
  EXPECT_EQ(tag.type, YAML::_Tag::Type::Verbatim);
}

TEST(VerbatimTagTest_15, SupportsLargeContent_15) {
  const std::string content(10000, 'x');
  const auto tag = YAML::VerbatimTag(content);

  EXPECT_EQ(tag.prefix, "");
  EXPECT_EQ(tag.content.size(), content.size());
  EXPECT_EQ(tag.content, content);
  EXPECT_EQ(tag.type, YAML::_Tag::Type::Verbatim);
}

TEST(VerbatimTagTest_15, ReturnedObjectIsIndependentOfInputLifetime_15) {
  YAML::_Tag tag("", "", YAML::_Tag::Type::Verbatim);
  {
    std::string content = "temporary";
    tag = YAML::VerbatimTag(content);
    // Mutate original string after creating tag; tag should remain unchanged.
    content.assign("changed");
  }

  EXPECT_EQ(tag.prefix, "");
  EXPECT_EQ(tag.content, "temporary");
  EXPECT_EQ(tag.type, YAML::_Tag::Type::Verbatim);
}

TEST(VerbatimTagTest_15, MultipleCallsWithSameContentProduceEquivalentTags_15) {
  const std::string content = "same";
  const auto a = YAML::VerbatimTag(content);
  const auto b = YAML::VerbatimTag(content);

  EXPECT_EQ(a.prefix, b.prefix);
  EXPECT_EQ(a.content, b.content);
  EXPECT_EQ(a.type, b.type);

  EXPECT_EQ(a.prefix, "");
  EXPECT_EQ(a.content, content);
  EXPECT_EQ(a.type, YAML::_Tag::Type::Verbatim);
}

TEST(VerbatimTagTest_15, DoesNotThrowForTypicalInputs_15) {
  EXPECT_NO_THROW((void)YAML::VerbatimTag("ok"));
  EXPECT_NO_THROW((void)YAML::VerbatimTag(std::string{}));
  EXPECT_NO_THROW((void)YAML::VerbatimTag(std::string(1024, 'a')));
}

}  // namespace
