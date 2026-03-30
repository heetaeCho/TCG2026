// TEST_ID: 115
// File: ./TestProjects/yaml-cpp/test/exp_test.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <string>
#include <vector>

#include "exp.h"
#include "regex_yaml.h"

namespace {

static_assert(std::is_same_v<decltype(YAML::Exp::Empty()), const YAML::RegEx&>,
              "YAML::Exp::Empty() must return const YAML::RegEx&");

class ExpEmptyTest_115 : public ::testing::Test {};

TEST_F(ExpEmptyTest_115, ReturnsSameInstanceAcrossCalls_115) {
  const YAML::RegEx* first = &YAML::Exp::Empty();
  const YAML::RegEx* second = &YAML::Exp::Empty();
  const YAML::RegEx* third = &YAML::Exp::Empty();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(ExpEmptyTest_115, BehavesLikeDefaultConstructedRegEx_ForChars_115) {
  const YAML::RegEx& empty = YAML::Exp::Empty();
  YAML::RegEx def;  // Default-constructed RegEx

  const std::vector<char> chars = {
      '\0', 'a', 'Z', '0', '\n', '\t', ' ', '-', '_', static_cast<char>(0x7F)};

  for (char ch : chars) {
    EXPECT_EQ(empty.Matches(ch), def.Matches(ch)) << "Mismatch for char int("
                                                  << static_cast<int>(static_cast<unsigned char>(ch)) << ")";
  }
}

TEST_F(ExpEmptyTest_115, BehavesLikeDefaultConstructedRegEx_ForStrings_115) {
  const YAML::RegEx& empty = YAML::Exp::Empty();
  YAML::RegEx def;  // Default-constructed RegEx

  const std::vector<std::string> strings = {
      "",
      "a",
      "abc",
      " ",
      "\n",
      "\t",
      "0",
      "A0_",
      std::string(1, '\0'),
      std::string("a\0b", 3),
  };

  for (const auto& s : strings) {
    EXPECT_EQ(empty.Matches(s), def.Matches(s)) << "Mismatch for string size=" << s.size();
    EXPECT_EQ(empty.Match(s), def.Match(s)) << "Mismatch for Match() on string size=" << s.size();
  }
}

TEST_F(ExpEmptyTest_115, CanBeUsedWithoutThrowing_115) {
  const YAML::RegEx& empty = YAML::Exp::Empty();

  // We don't assume specific semantics; we only assert the public calls are usable.
  EXPECT_NO_THROW((void)empty.Matches(""));
  EXPECT_NO_THROW((void)empty.Matches('x'));
  EXPECT_NO_THROW((void)empty.Match(""));
  EXPECT_NO_THROW((void)empty.Match("xyz"));
}

}  // namespace
