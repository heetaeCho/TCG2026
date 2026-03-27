// TEST_ID: 17
#include <gtest/gtest.h>

#include <string>

// LocalTag is defined here; it also provides YAML::_Tag (or includes the header that does).
#include "yaml-cpp/emittermanip.h"

namespace {

class LocalTagTest_17 : public ::testing::Test {};

TEST_F(LocalTagTest_17, CreatesNamedHandleTagFromStrings_17) {
  const std::string prefix = "!";
  const std::string content = "foo";

  EXPECT_NO_THROW({
    const YAML::_Tag tag = YAML::LocalTag(prefix, content);
    const YAML::_Tag expected(prefix, content, YAML::_Tag::Type::NamedHandle);
    EXPECT_EQ(tag, expected);
  });
}

TEST_F(LocalTagTest_17, AcceptsTemporaryStringsAndMatchesExpected_17) {
  const YAML::_Tag tag = YAML::LocalTag(std::string("!!"), std::string("map"));
  const YAML::_Tag expected("!!", "map", YAML::_Tag::Type::NamedHandle);
  EXPECT_EQ(tag, expected);
}

TEST_F(LocalTagTest_17, HandlesEmptyPrefixAndEmptyContent_17) {
  const std::string prefix;
  const std::string content;

  const YAML::_Tag tag = YAML::LocalTag(prefix, content);
  const YAML::_Tag expected(prefix, content, YAML::_Tag::Type::NamedHandle);
  EXPECT_EQ(tag, expected);
}

TEST_F(LocalTagTest_17, PreservesSpecialCharactersInInputs_17) {
  const std::string prefix = "!h!";
  const std::string content = "a:b#c\nd\t\"e\"";

  const YAML::_Tag tag = YAML::LocalTag(prefix, content);
  const YAML::_Tag expected(prefix, content, YAML::_Tag::Type::NamedHandle);
  EXPECT_EQ(tag, expected);
}

TEST_F(LocalTagTest_17, PreservesEmbeddedNullBytes_17) {
  const std::string prefix = std::string("!\0p", 3);
  const std::string content = std::string("a\0b", 3);

  const YAML::_Tag tag = YAML::LocalTag(prefix, content);
  const YAML::_Tag expected(prefix, content, YAML::_Tag::Type::NamedHandle);
  EXPECT_EQ(tag, expected);
}

TEST_F(LocalTagTest_17, DifferentInputsProduceDifferentTags_17) {
  const YAML::_Tag a = YAML::LocalTag("!", "foo");
  const YAML::_Tag b = YAML::LocalTag("!", "bar");
  const YAML::_Tag c = YAML::LocalTag("!!", "foo");

  EXPECT_NE(a, b);
  EXPECT_NE(a, c);
}

}  // namespace
