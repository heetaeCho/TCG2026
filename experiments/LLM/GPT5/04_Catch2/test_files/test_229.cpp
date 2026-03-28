// File: tests/matchers/regex/Matches_tests_229.cpp

#include <gtest/gtest.h>
#include <string>

// Catch2 public headers for string/regex matchers and CaseSensitive
#include <catch2/matchers/catch_matchers_string.hpp>

using Catch::Matchers::Matches;
using Catch::CaseSensitive;

namespace {

TEST(MatchesRegex_229, CaseSensitive_PositiveMatch_229) {
    // Normal operation: pattern should match when case matches exactly.
    auto m = Matches("a*b", CaseSensitive::Yes);
    EXPECT_TRUE(m.match("aaab"));
    EXPECT_TRUE(m.match("b"));
    EXPECT_FALSE(m.match("aaac"));   // different trailing char
}

TEST(MatchesRegex_229, CaseSensitive_NegativeOnDifferentCase_229) {
    // Boundary/negative: with CaseSensitive::Yes, differing case should fail.
    auto m = Matches("abc", CaseSensitive::Yes);
    EXPECT_TRUE(m.match("abc"));
    EXPECT_FALSE(m.match("Abc"));
    EXPECT_FALSE(m.match("ABC"));
}

TEST(MatchesRegex_229, CaseInsensitive_AllowsDifferentCase_229) {
    // Case-insensitive behavior: same pattern should match regardless of case.
    auto m = Matches("ab+c", CaseSensitive::No);
    EXPECT_TRUE(m.match("abbbc"));
    EXPECT_TRUE(m.match("AbBbC"));
    EXPECT_TRUE(m.match("ABBC"));
    EXPECT_FALSE(m.match("ac"));       // still must respect the pattern itself
}

TEST(MatchesRegex_229, EmptyPattern_ConstructsAndMatchesEmptyString_229) {
    // Boundary: empty regex should be constructible.
    // Observable behavior: commonly matches the empty string.
    auto m = Matches("", CaseSensitive::Yes);
    EXPECT_TRUE(m.match(""));      // empty input
    // Do NOT assert broader behavior on non-empty strings to avoid relying on specifics.
}

TEST(MatchesRegex_229, InvalidRegex_ThrowsAtConstruction_229) {
    // Exceptional case: invalid regex should surface as an exception on construction.
    // std::regex_error is the standard observable exception for bad patterns.
    EXPECT_THROW({
        auto m = Matches("(", CaseSensitive::Yes);
        (void)m; // silence unused warning if construction somehow succeeds
    }, std::regex_error);
}

} // namespace
