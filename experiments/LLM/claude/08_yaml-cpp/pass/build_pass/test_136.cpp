#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test fixture for ValueInJSONFlow tests
class ValueInJSONFlowTest_136 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that ValueInJSONFlow returns a RegEx that matches ':'
TEST_F(ValueInJSONFlowTest_136, MatchesColon_136) {
  const RegEx& re = Exp::ValueInJSONFlow();
  EXPECT_TRUE(re.Matches(':'));
}

// Test that ValueInJSONFlow does not match other characters
TEST_F(ValueInJSONFlowTest_136, DoesNotMatchNonColon_136) {
  const RegEx& re = Exp::ValueInJSONFlow();
  EXPECT_FALSE(re.Matches('a'));
  EXPECT_FALSE(re.Matches(' '));
  EXPECT_FALSE(re.Matches('\0'));
  EXPECT_FALSE(re.Matches(';'));
  EXPECT_FALSE(re.Matches('-'));
  EXPECT_FALSE(re.Matches('\n'));
  EXPECT_FALSE(re.Matches('\t'));
}

// Test that ValueInJSONFlow matches a string containing only ':'
TEST_F(ValueInJSONFlowTest_136, MatchesColonString_136) {
  const RegEx& re = Exp::ValueInJSONFlow();
  EXPECT_TRUE(re.Matches(std::string(":")));
}

// Test that ValueInJSONFlow does not match a string with more than ':'
TEST_F(ValueInJSONFlowTest_136, DoesNotMatchLongerString_136) {
  const RegEx& re = Exp::ValueInJSONFlow();
  EXPECT_FALSE(re.Matches(std::string("::")));
  EXPECT_FALSE(re.Matches(std::string(":a")));
}

// Test that ValueInJSONFlow does not match an empty string
TEST_F(ValueInJSONFlowTest_136, DoesNotMatchEmptyString_136) {
  const RegEx& re = Exp::ValueInJSONFlow();
  EXPECT_FALSE(re.Matches(std::string("")));
}

// Test that ValueInJSONFlow does not match strings not starting with ':'
TEST_F(ValueInJSONFlowTest_136, DoesNotMatchNonColonString_136) {
  const RegEx& re = Exp::ValueInJSONFlow();
  EXPECT_FALSE(re.Matches(std::string("a")));
  EXPECT_FALSE(re.Matches(std::string("abc")));
  EXPECT_FALSE(re.Matches(std::string(" ")));
}

// Test Match returns 1 for string starting with ':'
TEST_F(ValueInJSONFlowTest_136, MatchReturnsOneForColon_136) {
  const RegEx& re = Exp::ValueInJSONFlow();
  EXPECT_EQ(1, re.Match(std::string(":")));
}

// Test Match returns 1 for string starting with ':' followed by more chars
TEST_F(ValueInJSONFlowTest_136, MatchReturnsOneForColonFollowedByChars_136) {
  const RegEx& re = Exp::ValueInJSONFlow();
  EXPECT_EQ(1, re.Match(std::string(":value")));
}

// Test Match returns -1 for non-matching strings
TEST_F(ValueInJSONFlowTest_136, MatchReturnsNegativeForNonMatch_136) {
  const RegEx& re = Exp::ValueInJSONFlow();
  EXPECT_EQ(-1, re.Match(std::string("a")));
  EXPECT_EQ(-1, re.Match(std::string("")));
}

// Test that ValueInJSONFlow returns the same static reference on multiple calls
TEST_F(ValueInJSONFlowTest_136, ReturnsSameReference_136) {
  const RegEx& re1 = Exp::ValueInJSONFlow();
  const RegEx& re2 = Exp::ValueInJSONFlow();
  EXPECT_EQ(&re1, &re2);
}

// Test that ValueInJSONFlow does not match various special characters
TEST_F(ValueInJSONFlowTest_136, DoesNotMatchSpecialChars_136) {
  const RegEx& re = Exp::ValueInJSONFlow();
  EXPECT_FALSE(re.Matches('{'));
  EXPECT_FALSE(re.Matches('}'));
  EXPECT_FALSE(re.Matches('['));
  EXPECT_FALSE(re.Matches(']'));
  EXPECT_FALSE(re.Matches(','));
  EXPECT_FALSE(re.Matches('#'));
  EXPECT_FALSE(re.Matches('|'));
  EXPECT_FALSE(re.Matches('>'));
  EXPECT_FALSE(re.Matches('&'));
  EXPECT_FALSE(re.Matches('*'));
  EXPECT_FALSE(re.Matches('!'));
  EXPECT_FALSE(re.Matches('%'));
  EXPECT_FALSE(re.Matches('@'));
  EXPECT_FALSE(re.Matches('`'));
}

// Test digits and letters don't match
TEST_F(ValueInJSONFlowTest_136, DoesNotMatchDigitsAndLetters_136) {
  const RegEx& re = Exp::ValueInJSONFlow();
  for (char c = '0'; c <= '9'; ++c) {
    EXPECT_FALSE(re.Matches(c)) << "Should not match digit: " << c;
  }
  for (char c = 'A'; c <= 'Z'; ++c) {
    EXPECT_FALSE(re.Matches(c)) << "Should not match letter: " << c;
  }
  for (char c = 'a'; c <= 'z'; ++c) {
    EXPECT_FALSE(re.Matches(c)) << "Should not match letter: " << c;
  }
}

}  // namespace
}  // namespace YAML
