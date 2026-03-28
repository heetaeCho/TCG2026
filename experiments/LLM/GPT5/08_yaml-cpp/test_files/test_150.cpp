// File: ./TestProjects/yaml-cpp/test/exp_escbreak_test_150.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/exp.h"
#include "TestProjects/yaml-cpp/src/regex_yaml.h"

namespace {

class EscBreakTest_150 : public ::testing::Test {};

TEST_F(EscBreakTest_150, ReturnsSameStaticInstance_150) {
  const YAML::RegEx* p1 = &YAML::Exp::EscBreak();
  const YAML::RegEx* p2 = &YAML::Exp::EscBreak();
  const YAML::RegEx* p3 = &YAML::Exp::EscBreak();

  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p2, p3);
}

TEST_F(EscBreakTest_150, MatchesEquivalentToBackslashThenBreak_Composition_150) {
  const YAML::RegEx& under_test = YAML::Exp::EscBreak();
  const YAML::RegEx expected = YAML::RegEx('\\') + YAML::Exp::Break();

  const std::string samples[] = {
      "",           // empty
      "\\",         // only backslash
      "x",          // no backslash
      "x\\",        // backslash not first
      "\\\n",       // common break candidate
      "\\\r",       // common break candidate
      "\\ ",        // space after backslash
      "\\a",        // arbitrary char after backslash
      "\\0",        // digit after backslash
      "\\\t",       // tab after backslash
      "x\\\n",      // prefix char before backslash
      "\\\ntrail",  // longer
  };

  for (const auto& s : samples) {
    EXPECT_EQ(under_test.Matches(s), expected.Matches(s)) << "input: [" << s << "]";
  }
}

TEST_F(EscBreakTest_150, MatchLengthEquivalentToBackslashThenBreak_Composition_150) {
  const YAML::RegEx& under_test = YAML::Exp::EscBreak();
  const YAML::RegEx expected = YAML::RegEx('\\') + YAML::Exp::Break();

  const std::string samples[] = {
      "",
      "\\",
      "x",
      "x\\",
      "\\\n",
      "\\\r",
      "\\ ",
      "\\a",
      "\\0",
      "\\\t",
      "x\\\n",
      "\\\ntrail",
  };

  for (const auto& s : samples) {
    EXPECT_EQ(under_test.Match(s), expected.Match(s)) << "input: [" << s << "]";
  }
}

TEST_F(EscBreakTest_150, DoesNotMatchStringsWithoutLeadingBackslash_WhenComparedToComposition_150) {
  const YAML::RegEx& under_test = YAML::Exp::EscBreak();
  const YAML::RegEx expected = YAML::RegEx('\\') + YAML::Exp::Break();

  const std::string samples[] = {
      "a",
      "abc",
      " \n",
      "\n",
      "\r",
      "x\\\n",
      "x\\\r",
      "x\\",
  };

  for (const auto& s : samples) {
    EXPECT_EQ(under_test.Matches(s), expected.Matches(s)) << "input: [" << s << "]";
  }
}

}  // namespace
