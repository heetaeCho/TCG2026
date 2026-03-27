#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

using YAML::RegEx;

class RegExMatchesTest_111 : public ::testing::Test {
protected:
  RegEx defaultRegex;
  RegEx literalA{'a'};
};

/**
 * Normal operation:
 * Matches(Source) must return true iff Match(Source) >= 0
 */
TEST_F(RegExMatchesTest_111, MatchesConsistentWithMatchResult_111) {
  const std::string input = "a";

  bool matchesResult = literalA.Matches(input);
  int matchResult = literalA.Match(input);

  EXPECT_EQ(matchesResult, matchResult >= 0);
}

/**
 * Boundary condition:
 * Empty string input must still obey Matches == (Match >= 0)
 */
TEST_F(RegExMatchesTest_111, MatchesWithEmptyStringIsConsistent_111) {
  const std::string empty;

  bool matchesResult = defaultRegex.Matches(empty);
  int matchResult = defaultRegex.Match(empty);

  EXPECT_EQ(matchesResult, matchResult >= 0);
}

/**
 * Boundary condition:
 * Non-matching input must still obey Matches == (Match >= 0)
 */
TEST_F(RegExMatchesTest_111, MatchesWithNonMatchingStringIsConsistent_111) {
  const std::string input = "z";

  bool matchesResult = literalA.Matches(input);
  int matchResult = literalA.Match(input);

  EXPECT_EQ(matchesResult, matchResult >= 0);
}

/**
 * Normal operation:
 * Multiple invocations should be stable and consistent
 */
TEST_F(RegExMatchesTest_111, MatchesIsStableAcrossCalls_111) {
  const std::string input = "a";

  bool first = literalA.Matches(input);
  bool second = literalA.Matches(input);

  EXPECT_EQ(first, second);
}

/**
 * Error-adjacent / compile-time constraint (documented behavior):
 *
 * The following is intentionally NOT compiled:
 *
 *   literalA.Matches("a");
 *
 * Because Matches<const char*> is forbidden by static_assert.
 *
 * This constraint is verified by the type system and cannot be
 * tested at runtime.
 */
