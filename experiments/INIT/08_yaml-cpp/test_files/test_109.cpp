// TEST_ID: 109
// File: regeximpl_test_109.cpp

#include <gtest/gtest.h>

#include <string>
#include <vector>

// Prefer local includes matching the prompt file layout.
#include "regex_yaml.h"
#include "regeximpl.h"

namespace {

template <typename F>
bool Throws(F&& f) {
  try {
    f();
    return false;
  } catch (...) {
    return true;
  }
}

class RegExMatchesStringTest_109 : public ::testing::Test {
 protected:
  static std::vector<YAML::RegEx> MakeRegexes() {
    // Only use constructors that don't require unknown types (e.g., REGEX_OP).
    return {
        YAML::RegEx(),          // default
        YAML::RegEx('a'),       // single char
        YAML::RegEx('a', 'z'),  // range
        YAML::RegEx('\0'),      // edge: NUL char
    };
  }

  static std::vector<std::string> MakeStrings() {
    std::vector<std::string> cases;
    cases.emplace_back("");          // empty
    cases.emplace_back("a");         // single
    cases.emplace_back("abc");       // small
    cases.emplace_back("Z");         // non-lower
    cases.emplace_back("aZ9_");      // mixed
    cases.emplace_back(" ");         // whitespace
    cases.emplace_back("\n\t\r");    // control chars
    cases.emplace_back("0123456789");
    cases.emplace_back(std::string(256, 'a'));     // medium
    cases.emplace_back(std::string(10000, 'b'));   // large
    // Embedded NUL: "a\0b"
    cases.emplace_back(std::string({'a', '\0', 'b'}));
    return cases;
  }
};

}  // namespace

TEST_F(RegExMatchesStringTest_109, MatchesAgreesWithMatchPredicate_109) {
  const auto regexes = MakeRegexes();
  const auto inputs = MakeStrings();

  for (const auto& ex : regexes) {
    for (const auto& s : inputs) {
      const bool match_throws = Throws([&] { (void)ex.Match(s); });
      const bool matches_throws = Throws([&] { (void)ex.Matches(s); });

      // Observable error behavior through the interface: Matches() calls Match(),
      // so if Match throws for an input, Matches should also throw.
      EXPECT_EQ(matches_throws, match_throws) << "input size=" << s.size();

      if (!match_throws) {
        const int r = ex.Match(s);
        const bool expected = (r >= 0);
        EXPECT_EQ(ex.Matches(s), expected) << "Match() returned " << r << " for input size=" << s.size();
      }
    }
  }
}

TEST_F(RegExMatchesStringTest_109, WorksOnConstObject_109) {
  const YAML::RegEx ex('x');
  const std::string s = "xyz";

  const bool match_throws = Throws([&] { (void)ex.Match(s); });
  const bool matches_throws = Throws([&] { (void)ex.Matches(s); });
  EXPECT_EQ(matches_throws, match_throws);

  if (!match_throws) {
    EXPECT_EQ(ex.Matches(s), ex.Match(s) >= 0);
  }
}

TEST_F(RegExMatchesStringTest_109, EmptyStringBoundaryAgreesWithMatch_109) {
  const std::string empty;
  for (const auto& ex : MakeRegexes()) {
    const bool match_throws = Throws([&] { (void)ex.Match(empty); });
    const bool matches_throws = Throws([&] { (void)ex.Matches(empty); });
    EXPECT_EQ(matches_throws, match_throws);

    if (!match_throws) {
      EXPECT_EQ(ex.Matches(empty), ex.Match(empty) >= 0);
    }
  }
}

TEST_F(RegExMatchesStringTest_109, EmbeddedNullBoundaryAgreesWithMatch_109) {
  const std::string with_null = std::string({'a', '\0', 'b', '\0', 'c'});
  for (const auto& ex : MakeRegexes()) {
    const bool match_throws = Throws([&] { (void)ex.Match(with_null); });
    const bool matches_throws = Throws([&] { (void)ex.Matches(with_null); });
    EXPECT_EQ(matches_throws, match_throws);

    if (!match_throws) {
      EXPECT_EQ(ex.Matches(with_null), ex.Match(with_null) >= 0);
    }
  }
}

TEST_F(RegExMatchesStringTest_109, VeryLongStringBoundaryAgreesWithMatch_109) {
  const std::string long_s(50000, 'a');
  for (const auto& ex : MakeRegexes()) {
    const bool match_throws = Throws([&] { (void)ex.Match(long_s); });
    const bool matches_throws = Throws([&] { (void)ex.Matches(long_s); });
    EXPECT_EQ(matches_throws, match_throws);

    if (!match_throws) {
      EXPECT_EQ(ex.Matches(long_s), ex.Match(long_s) >= 0);
    }
  }
}
