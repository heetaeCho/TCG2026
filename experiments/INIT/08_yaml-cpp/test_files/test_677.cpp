// File: ./TestProjects/yaml-cpp/test/tag_test.cpp

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "tag.h"
#include "token.h"

namespace {

YAML::Token MakeTokenWithTagData(int tag_type_data,
                                const std::string& value = std::string(),
                                const std::vector<std::string>& params = {}) {
  // The Tag ctor only observes: token.data, token.value, token.params.
  // We construct a Token using a "dummy" token type + mark (whatever 0 means),
  // then populate the observed fields.
  YAML::Token token(static_cast<YAML::Token::TYPE>(0), YAML::Mark());
  token.data = tag_type_data;
  token.value = value;
  token.params = params;
  return token;
}

}  // namespace

TEST(TagTest_677, VerbatimCopiesValueAndLeavesHandleEmpty_677) {
  const std::string kValue = "!<tag:example.com,2000:app/foo>";
  YAML::Token token = MakeTokenWithTagData(static_cast<int>(YAML::Tag::VERBATIM), kValue);

  YAML::Tag tag(token);

  EXPECT_EQ(tag.type, YAML::Tag::VERBATIM);
  EXPECT_TRUE(tag.handle.empty());
  EXPECT_EQ(tag.value, kValue);
}

TEST(TagTest_677, PrimaryHandleCopiesValueAndLeavesHandleEmpty_677) {
  const std::string kValue = "!foo";
  YAML::Token token =
      MakeTokenWithTagData(static_cast<int>(YAML::Tag::PRIMARY_HANDLE), kValue);

  YAML::Tag tag(token);

  EXPECT_EQ(tag.type, YAML::Tag::PRIMARY_HANDLE);
  EXPECT_TRUE(tag.handle.empty());
  EXPECT_EQ(tag.value, kValue);
}

TEST(TagTest_677, SecondaryHandleCopiesValueAndLeavesHandleEmpty_677) {
  const std::string kValue = "!!map";
  YAML::Token token =
      MakeTokenWithTagData(static_cast<int>(YAML::Tag::SECONDARY_HANDLE), kValue);

  YAML::Tag tag(token);

  EXPECT_EQ(tag.type, YAML::Tag::SECONDARY_HANDLE);
  EXPECT_TRUE(tag.handle.empty());
  EXPECT_EQ(tag.value, kValue);
}

TEST(TagTest_677, NamedHandleCopiesHandleFromValueAndValueFromFirstParam_677) {
  const std::string kHandle = "!h!";
  const std::string kResolved = "foo";
  YAML::Token token = MakeTokenWithTagData(static_cast<int>(YAML::Tag::NAMED_HANDLE),
                                          kHandle,
                                          {kResolved});

  YAML::Tag tag(token);

  EXPECT_EQ(tag.type, YAML::Tag::NAMED_HANDLE);
  EXPECT_EQ(tag.handle, kHandle);
  EXPECT_EQ(tag.value, kResolved);
}

TEST(TagTest_677, NamedHandleIgnoresAdditionalParamsBeyondFirst_677) {
  YAML::Token token = MakeTokenWithTagData(static_cast<int>(YAML::Tag::NAMED_HANDLE),
                                          "!h!",
                                          {"first", "second", "third"});

  YAML::Tag tag(token);

  EXPECT_EQ(tag.type, YAML::Tag::NAMED_HANDLE);
  EXPECT_EQ(tag.handle, "!h!");
  EXPECT_EQ(tag.value, "first");
}

TEST(TagTest_677, NonSpecificLeavesHandleAndValueEmpty_677) {
  // Provide non-empty inputs; NON_SPECIFIC should ignore them per ctor switch.
  YAML::Token token = MakeTokenWithTagData(static_cast<int>(YAML::Tag::NON_SPECIFIC),
                                          "!ignored",
                                          {"also_ignored"});

  YAML::Tag tag(token);

  EXPECT_EQ(tag.type, YAML::Tag::NON_SPECIFIC);
  EXPECT_TRUE(tag.handle.empty());
  EXPECT_TRUE(tag.value.empty());
}

TEST(TagTest_677, BoundaryEmptyStringsArePreservedForValueCopyingKinds_677) {
  YAML::Token token1 = MakeTokenWithTagData(static_cast<int>(YAML::Tag::VERBATIM), "");
  YAML::Tag tag1(token1);
  EXPECT_EQ(tag1.type, YAML::Tag::VERBATIM);
  EXPECT_TRUE(tag1.handle.empty());
  EXPECT_TRUE(tag1.value.empty());

  YAML::Token token2 = MakeTokenWithTagData(static_cast<int>(YAML::Tag::PRIMARY_HANDLE), "");
  YAML::Tag tag2(token2);
  EXPECT_EQ(tag2.type, YAML::Tag::PRIMARY_HANDLE);
  EXPECT_TRUE(tag2.handle.empty());
  EXPECT_TRUE(tag2.value.empty());
}

#if GTEST_HAS_DEATH_TEST
#ifndef NDEBUG
TEST(TagTest_677, InvalidTypeTriggersAssertDeath_677) {
  YAML::Token token = MakeTokenWithTagData(/*tag_type_data=*/999, "x", {"y"});

  // Implementation uses assert(false) in the default case, so expect a debug death.
  ASSERT_DEATH({ YAML::Tag tag(token); }, "");
}
#endif  // NDEBUG
#endif  // GTEST_HAS_DEATH_TEST