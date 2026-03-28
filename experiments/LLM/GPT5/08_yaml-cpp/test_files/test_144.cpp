// File: ./TestProjects/yaml-cpp/test/exp_plain_scalar_in_flow_test.cpp

#include <gtest/gtest.h>

#include "exp.h"          // YAML::Exp::PlainScalarInFlow
#include "regex_yaml.h"   // YAML::RegEx

namespace {

class PlainScalarInFlowTest_144 : public ::testing::Test {
protected:
  const YAML::RegEx& Re() const { return YAML::Exp::PlainScalarInFlow(); }
};

TEST_F(PlainScalarInFlowTest_144, ReturnsStableSingletonReference_144) {
  const YAML::RegEx* a = &YAML::Exp::PlainScalarInFlow();
  const YAML::RegEx* b = &YAML::Exp::PlainScalarInFlow();
  const YAML::RegEx* c = &Re();

  EXPECT_EQ(a, b);
  EXPECT_EQ(a, c);
}

TEST_F(PlainScalarInFlowTest_144, AcceptsTypicalNonSpecialCharacters_144) {
  EXPECT_TRUE(Re().Matches('a'));
  EXPECT_TRUE(Re().Matches('Z'));
  EXPECT_TRUE(Re().Matches('0'));
  EXPECT_TRUE(Re().Matches('_'));
}

TEST_F(PlainScalarInFlowTest_144, RejectsBlankAndBreakCharacters_144) {
  // These are representative blanks/breaks; the concrete definition is internal.
  EXPECT_FALSE(Re().Matches(' '));
  EXPECT_FALSE(Re().Matches('\t'));
  EXPECT_FALSE(Re().Matches('\n'));
  EXPECT_FALSE(Re().Matches('\r'));
}

TEST_F(PlainScalarInFlowTest_144, RejectsFlowIndicatorAndSpecialCharacters_144) {
  const char disallowed[] = {
      '?', ',', '[', ']', '{', '}', '#', '&', '*', '!', '|', '>', '\'', '"',
      '%', '@', '`',
  };

  for (char ch : disallowed) {
    SCOPED_TRACE(::testing::Message() << "ch='" << ch << "'");
    EXPECT_FALSE(Re().Matches(ch));
  }
}

TEST_F(PlainScalarInFlowTest_144, RejectsDashColonFollowedByBlankOrEnd_144) {
  // Observable behavior via the public interface: these should not be allowed.
  EXPECT_FALSE(Re().Matches(std::string("-:")));
  EXPECT_FALSE(Re().Matches(std::string("-: ")));
  EXPECT_FALSE(Re().Matches(std::string("-:\t")));
}

TEST_F(PlainScalarInFlowTest_144, AllowsDashColonWhenNotFollowedByBlank_144) {
  // Contrast case: "-:" followed by a non-blank should be allowed.
  EXPECT_TRUE(Re().Matches(std::string("-:a")));
  EXPECT_TRUE(Re().Matches(std::string("-:0")));
  EXPECT_TRUE(Re().Matches(std::string("-:_")));
}

}  // namespace
