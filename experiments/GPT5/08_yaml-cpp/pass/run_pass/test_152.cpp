// TEST_ID: 152
#include <gtest/gtest.h>

#include "exp.h"          // YAML::Exp::Chomp(), YAML::Exp::Digit(), YAML::Exp::ChompIndicator()
#include "regex_yaml.h"   // YAML::RegEx

#include <string>
#include <vector>

namespace {

std::vector<char> CollectMatchingChars(const YAML::RegEx& ex) {
  std::vector<char> out;
  // Scan a safe, common ASCII range to discover what the regex accepts.
  for (int i = 0; i <= 127; ++i) {
    const char ch = static_cast<char>(i);
    if (ex.Matches(ch)) out.push_back(ch);
  }
  return out;
}

char PickAnyOrFail(const std::vector<char>& v, const char* what) {
  EXPECT_FALSE(v.empty()) << "Expected at least one matching character for " << what;
  return v.empty() ? '\0' : v.front();
}

}  // namespace

class ChompTest_152 : public ::testing::Test {
 protected:
  static std::vector<char> Digits() { return CollectMatchingChars(YAML::Exp::Digit()); }
  static std::vector<char> ChompIndicators() { return CollectMatchingChars(YAML::Exp::ChompIndicator()); }
};

TEST_F(ChompTest_152, ReturnsStableReference_152) {
  const YAML::RegEx* a = &YAML::Exp::Chomp();
  const YAML::RegEx* b = &YAML::Exp::Chomp();
  EXPECT_EQ(a, b) << "Chomp() should return the same static RegEx instance by reference.";
}

TEST_F(ChompTest_152, MatchesSingleDigit_152) {
  const auto digits = Digits();
  const char d = PickAnyOrFail(digits, "Digit()");
  ASSERT_NE(d, '\0');

  const std::string s(1, d);
  EXPECT_TRUE(YAML::Exp::Chomp().Matches(s));
}

TEST_F(ChompTest_152, MatchesSingleChompIndicator_152) {
  const auto chomps = ChompIndicators();
  const char c = PickAnyOrFail(chomps, "ChompIndicator()");
  ASSERT_NE(c, '\0');

  const std::string s(1, c);
  EXPECT_TRUE(YAML::Exp::Chomp().Matches(s));
}

TEST_F(ChompTest_152, MatchesDigitThenChompIndicator_152) {
  const auto digits = Digits();
  const auto chomps = ChompIndicators();
  const char d = PickAnyOrFail(digits, "Digit()");
  const char c = PickAnyOrFail(chomps, "ChompIndicator()");
  ASSERT_NE(d, '\0');
  ASSERT_NE(c, '\0');

  std::string s;
  s.push_back(d);
  s.push_back(c);

  EXPECT_TRUE(YAML::Exp::Chomp().Matches(s));
}

TEST_F(ChompTest_152, MatchesChompIndicatorThenDigit_152) {
  const auto digits = Digits();
  const auto chomps = ChompIndicators();
  const char d = PickAnyOrFail(digits, "Digit()");
  const char c = PickAnyOrFail(chomps, "ChompIndicator()");
  ASSERT_NE(d, '\0');
  ASSERT_NE(c, '\0');

  std::string s;
  s.push_back(c);
  s.push_back(d);

  EXPECT_TRUE(YAML::Exp::Chomp().Matches(s));
}

TEST_F(ChompTest_152, DoesNotMatchEmptyString_152) {
  EXPECT_FALSE(YAML::Exp::Chomp().Matches(std::string()));
}

TEST_F(ChompTest_152, DoesNotMatchTwoDigits_152) {
  const auto digits = Digits();
  const char d = PickAnyOrFail(digits, "Digit()");
  ASSERT_NE(d, '\0');

  std::string s;
  s.push_back(d);
  s.push_back(d);

  EXPECT_FALSE(YAML::Exp::Chomp().Matches(s));
}

TEST_F(ChompTest_152, DoesNotMatchTwoChompIndicators_152) {
  const auto chomps = ChompIndicators();
  const char c = PickAnyOrFail(chomps, "ChompIndicator()");
  ASSERT_NE(c, '\0');

  std::string s;
  s.push_back(c);
  s.push_back(c);

  EXPECT_FALSE(YAML::Exp::Chomp().Matches(s));
}

TEST_F(ChompTest_152, DoesNotThrowOnNonPrintableBytes_152) {
  // Error/exceptional case: ensure API is robust with odd inputs.
  const auto digits = Digits();
  const char d = PickAnyOrFail(digits, "Digit()");
  ASSERT_NE(d, '\0');

  std::string s;
  s.push_back(d);
  s.push_back('\0');  // embedded NUL

  EXPECT_NO_THROW({
    (void)YAML::Exp::Chomp().Matches(s);
    (void)YAML::Exp::Chomp().Match(s);
  });
}
