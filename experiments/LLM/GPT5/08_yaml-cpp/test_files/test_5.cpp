// File: ./TestProjects/yaml-cpp/test/tag_translate_test_5.cpp

#include <stdexcept>
#include <string>

#include "gtest/gtest.h"

// These headers live under ./TestProjects/yaml-cpp/src/
#include "directives.h"
#include "tag.h"
#include "token.h"

namespace {

class TagTranslateTest_5 : public ::testing::Test {
protected:
  static YAML::Tag MakeTag(YAML::Tag::TYPE type,
                          const std::string& handle,
                          const std::string& value) {
    YAML::Token token{};
    token.data = static_cast<int>(type);

    YAML::Tag tag(token);
    // Fields are public; set explicitly to avoid relying on constructor side effects.
    tag.type = type;
    tag.handle = handle;
    tag.value = value;
    return tag;
  }
};

TEST_F(TagTranslateTest_5, VerbatimReturnsValueUnchanged_5) {
  const YAML::Directives directives{};
  const YAML::Tag tag = MakeTag(YAML::Tag::VERBATIM, /*handle=*/"", /*value=*/"tag:example");

  EXPECT_EQ(tag.Translate(directives), "tag:example");
}

TEST_F(TagTranslateTest_5, PrimaryHandleUsesTranslatedBangPrefix_5) {
  const YAML::Directives directives{};
  const YAML::Tag tag = MakeTag(YAML::Tag::PRIMARY_HANDLE, /*handle=*/"", /*value=*/"foo");

  const std::string expected_prefix = directives.TranslateTagHandle("!");
  EXPECT_EQ(tag.Translate(directives), expected_prefix + "foo");
}

TEST_F(TagTranslateTest_5, SecondaryHandleUsesTranslatedDoubleBangPrefix_5) {
  const YAML::Directives directives{};
  const YAML::Tag tag = MakeTag(YAML::Tag::SECONDARY_HANDLE, /*handle=*/"", /*value=*/"bar");

  const std::string expected_prefix = directives.TranslateTagHandle("!!");
  EXPECT_EQ(tag.Translate(directives), expected_prefix + "bar");
}

TEST_F(TagTranslateTest_5, NamedHandleUsesTranslatedCustomHandlePrefix_5) {
  const YAML::Directives directives{};
  const YAML::Tag tag = MakeTag(YAML::Tag::NAMED_HANDLE, /*handle=*/"h", /*value=*/"baz");

  const std::string expected_prefix = directives.TranslateTagHandle("!h!");
  EXPECT_EQ(tag.Translate(directives), expected_prefix + "baz");
}

TEST_F(TagTranslateTest_5, NonSpecificAlwaysReturnsSingleBang_5) {
  const YAML::Directives directives{};
  const YAML::Tag tag = MakeTag(YAML::Tag::NON_SPECIFIC, /*handle=*/"ignored", /*value=*/"ignored");

  EXPECT_EQ(tag.Translate(directives), "!");
}

TEST_F(TagTranslateTest_5, PrimaryHandleWithEmptyValueReturnsOnlyPrefix_5) {
  const YAML::Directives directives{};
  const YAML::Tag tag = MakeTag(YAML::Tag::PRIMARY_HANDLE, /*handle=*/"", /*value=*/"");

  const std::string expected_prefix = directives.TranslateTagHandle("!");
  EXPECT_EQ(tag.Translate(directives), expected_prefix);
}

TEST_F(TagTranslateTest_5, InvalidTypeDiesInDebugOrThrowsInRelease_5) {
  const YAML::Directives directives{};

  YAML::Token token{};
  token.data = 999;  // intentionally invalid
  YAML::Tag tag(token);
  tag.type = static_cast<YAML::Tag::TYPE>(999);
  tag.handle = "h";
  tag.value = "v";

#ifndef NDEBUG
  // In debug builds, the implementation asserts(false) in the default case.
  EXPECT_DEATH({ (void)tag.Translate(directives); }, "");
#else
  // In release builds, the code path should throw after the switch.
  EXPECT_THROW({ (void)tag.Translate(directives); }, std::runtime_error);
#endif
}

}  // namespace
