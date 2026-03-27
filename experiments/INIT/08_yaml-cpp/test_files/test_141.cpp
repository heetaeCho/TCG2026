// TEST_ID: 141
// File: ./TestProjects/yaml-cpp/test/exp_uri_test_141.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/exp.h"
#include "TestProjects/yaml-cpp/src/regex_yaml.h"

namespace {

class UriExpTest_141 : public ::testing::Test {};

// URI() returns a const reference to a (likely static) RegEx object.
// Verify it is stable across calls (same instance).
TEST_F(UriExpTest_141, ReturnsSameInstance_141) {
  const YAML::RegEx* a = &YAML::Exp::URI();
  const YAML::RegEx* b = &YAML::Exp::URI();
  EXPECT_EQ(a, b);
}

// URI() should match typical "word" characters via Word() component.
// We keep this conservative: alphanumerics are the safest assumption for "word".
TEST_F(UriExpTest_141, MatchesAlnumSingleCharacter_141) {
  const auto& uri = YAML::Exp::URI();

  EXPECT_TRUE(uri.Matches('a'));
  EXPECT_TRUE(uri.Matches('Z'));
  EXPECT_TRUE(uri.Matches('0'));

  EXPECT_TRUE(uri.Matches(std::string("a")));
  EXPECT_TRUE(uri.Matches(std::string("Z")));
  EXPECT_TRUE(uri.Matches(std::string("0")));
}

// URI() explicitly ORs in a set of allowed single characters.
// Verify each of these characters matches as a single-character string.
TEST_F(UriExpTest_141, MatchesExplicitAllowedSingleCharacters_141) {
  const auto& uri = YAML::Exp::URI();
  const std::string allowed = "#;/?:@&=+$,_.!~*'()[]";

  for (char ch : allowed) {
    EXPECT_TRUE(uri.Matches(ch)) << "Expected URI() to match char: '" << ch << "'";
    EXPECT_TRUE(uri.Matches(std::string(1, ch)))
        << "Expected URI() to match one-char string: '" << ch << "'";
  }
}

// URI() includes a percent-encoding sequence: '%' + Hex() + Hex().
// That implies '%' alone should NOT match, while "%2F" (etc.) should match as a unit.
TEST_F(UriExpTest_141, PercentEncodingTripletMatchesButPercentAloneDoesNot_141) {
  const auto& uri = YAML::Exp::URI();

  EXPECT_FALSE(uri.Matches('%'));
  EXPECT_FALSE(uri.Matches(std::string("%")));

  EXPECT_TRUE(uri.Matches(std::string("%00")));
  EXPECT_TRUE(uri.Matches(std::string("%2F")));
  EXPECT_TRUE(uri.Matches(std::string("%7e")));  // if Hex() allows lower-case
  EXPECT_TRUE(uri.Matches(std::string("%7E")));  // if Hex() allows upper-case
}

// Boundary / error-observable cases: incomplete or invalid percent-encoding should not match.
// Also, empty input should not match and should be handled safely.
TEST_F(UriExpTest_141, DoesNotMatchInvalidOrIncompletePercentEncoding_141) {
  const auto& uri = YAML::Exp::URI();

  EXPECT_FALSE(uri.Matches(std::string("")));
  EXPECT_FALSE(uri.Matches(std::string("%2")));
  EXPECT_FALSE(uri.Matches(std::string("%G0")));
  EXPECT_FALSE(uri.Matches(std::string("%0G")));
  EXPECT_FALSE(uri.Matches(std::string("%%0")));
  EXPECT_FALSE(uri.Matches(std::string("% 0")));
}

// Match(...) is observable through the public interface.
// Without assuming full semantics, we can still assert:
// - For a valid single-character match, Match should return > 0.
// - For a valid percent triplet match, Match should return > 0 (often 3).
// - For clearly invalid strings, Match should return <= 0.
TEST_F(UriExpTest_141, MatchReportsPositiveForValidInputsAndNonPositiveForInvalid_141) {
  const auto& uri = YAML::Exp::URI();

  const int m1 = uri.Match(std::string("a"));
  EXPECT_GT(m1, 0);

  const int m2 = uri.Match(std::string("#"));
  EXPECT_GT(m2, 0);

  const int m3 = uri.Match(std::string("%2F"));
  EXPECT_GT(m3, 0);

  const int inv1 = uri.Match(std::string(""));
  EXPECT_LE(inv1, 0);

  const int inv2 = uri.Match(std::string("%"));
  EXPECT_LE(inv2, 0);

  const int inv3 = uri.Match(std::string("%2"));
  EXPECT_LE(inv3, 0);
}

// If URI() is intended to match a single URI "unit" (one char OR a %HH triplet),
// then multi-unit strings should not fully match via Matches(string).
// This is a behavioral check that remains safe because it only asserts non-match.
TEST_F(UriExpTest_141, DoesNotFullyMatchMultipleUnitsInSingleString_141) {
  const auto& uri = YAML::Exp::URI();

  // Two allowed units concatenated.
  EXPECT_FALSE(uri.Matches(std::string("ab")));
  EXPECT_FALSE(uri.Matches(std::string("a#")));

  // Percent triplet + another unit.
  EXPECT_FALSE(uri.Matches(std::string("%2Fa")));
  EXPECT_FALSE(uri.Matches(std::string("a%2F")));
}

}  // namespace
