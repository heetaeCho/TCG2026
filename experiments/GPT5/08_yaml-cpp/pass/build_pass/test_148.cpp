// File: ./TestProjects/yaml-cpp/test/exp_scanscalarend_test_148.cpp

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "exp.h"          // YAML::Exp::ScanScalarEnd + building blocks
#include "regex_yaml.h"   // YAML::RegEx

namespace {

class ScanScalarEndTest_148 : public ::testing::Test {
 protected:
  static const YAML::RegEx& Actual() { return YAML::Exp::ScanScalarEnd(); }

  // Build the expected regex using the same public interface as production code.
  static YAML::RegEx Expected() {
    return YAML::Exp::EndScalar() | (YAML::Exp::BlankOrBreak() + YAML::Exp::Comment());
  }

  static std::vector<std::string> SampleStrings() {
    return {
        "",        "a",       "abc",
        " ",       "\t",      "\n",
        "#",       "##",      "#comment",
        " #",      "\t#",     "\n#",
        "a#",      "a #",     "a#b",
        ":",       ",",       "-",
        "[]",      "{}",      "0",
    };
  }

  static std::vector<char> SampleChars() {
    return {
        '\0', 'a', 'Z', '0',
        ' ', '\t', '\n', '\r',
        '#', ':', ',', '-',
        '[', ']', '{', '}',
    };
  }
};

}  // namespace

TEST_F(ScanScalarEndTest_148, ReturnsSameInstance_148) {
  const YAML::RegEx* p1 = &YAML::Exp::ScanScalarEnd();
  const YAML::RegEx* p2 = &YAML::Exp::ScanScalarEnd();
  EXPECT_EQ(p1, p2);
}

TEST_F(ScanScalarEndTest_148, MatchesCharSameAsComposedExpression_148) {
  const YAML::RegEx& actual = Actual();
  const YAML::RegEx expected = Expected();

  for (char ch : SampleChars()) {
    SCOPED_TRACE(::testing::Message() << "ch=" << static_cast<int>(static_cast<unsigned char>(ch)));
    EXPECT_EQ(actual.Matches(ch), expected.Matches(ch));
  }
}

TEST_F(ScanScalarEndTest_148, MatchesStringSameAsComposedExpression_148) {
  const YAML::RegEx& actual = Actual();
  const YAML::RegEx expected = Expected();

  for (const auto& s : SampleStrings()) {
    SCOPED_TRACE(::testing::Message() << "s=\"" << s << "\"");
    EXPECT_EQ(actual.Matches(s), expected.Matches(s));
  }
}

TEST_F(ScanScalarEndTest_148, MatchLengthSameAsComposedExpression_148) {
  const YAML::RegEx& actual = Actual();
  const YAML::RegEx expected = Expected();

  for (const auto& s : SampleStrings()) {
    SCOPED_TRACE(::testing::Message() << "s=\"" << s << "\"");
    EXPECT_EQ(actual.Match(s), expected.Match(s));
  }
}

TEST_F(ScanScalarEndTest_148, DoesNotThrowOnCommonInputs_148) {
  const YAML::RegEx& actual = Actual();

  for (const auto& s : SampleStrings()) {
    SCOPED_TRACE(::testing::Message() << "s=\"" << s << "\"");
    EXPECT_NO_THROW((void)actual.Matches(s));
    EXPECT_NO_THROW((void)actual.Match(s));
  }

  for (char ch : SampleChars()) {
    SCOPED_TRACE(::testing::Message() << "ch=" << static_cast<int>(static_cast<unsigned char>(ch)));
    EXPECT_NO_THROW((void)actual.Matches(ch));
  }
}

TEST_F(ScanScalarEndTest_148, HandlesVeryLongStringConsistentlyWithComposedExpression_148) {
  const YAML::RegEx& actual = Actual();
  const YAML::RegEx expected = Expected();

  std::string long_input(4096, 'a');
  long_input.push_back('#');
  long_input.append(" trailing");

  EXPECT_EQ(actual.Matches(long_input), expected.Matches(long_input));
  EXPECT_EQ(actual.Match(long_input), expected.Match(long_input));
}
