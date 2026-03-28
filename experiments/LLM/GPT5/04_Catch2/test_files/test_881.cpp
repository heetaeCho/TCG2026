// File: tests/coverage_helper_starts_with_test_881.cpp

#include <gtest/gtest.h>
#include <string>

// Forward-declare the function under test. Make sure to link with
// Catch2/tools/misc/coverage-helper.cpp when building the tests.
bool starts_with(std::string const& str, std::string const& pref);

// ---------- Normal operation ----------

TEST(CoverageHelperStartsWithTest_881, ReturnsTrueWhenPrefixMatchesStart_881) {
    EXPECT_TRUE(starts_with("Catch2", "Cat"));
    EXPECT_TRUE(starts_with("hello", "h"));
    EXPECT_TRUE(starts_with("abc", "abc"));  // exact match
}

TEST(CoverageHelperStartsWithTest_881, ReturnsFalseWhenPrefixDoesNotMatchStart_881) {
    EXPECT_FALSE(starts_with("Catch2", "atch"));
    EXPECT_FALSE(starts_with("hello", "e"));
    EXPECT_FALSE(starts_with("abc", "bc"));
}

// ---------- Boundary conditions ----------

TEST(CoverageHelperStartsWithTest_881, EmptyPrefixReturnsTrue_881) {
    EXPECT_TRUE(starts_with("anything", ""));
    EXPECT_TRUE(starts_with("", ""));  // both empty
}

TEST(CoverageHelperStartsWithTest_881, NonEmptyPrefixAgainstEmptyStringReturnsFalse_881) {
    EXPECT_FALSE(starts_with("", "a"));
}

TEST(CoverageHelperStartsWithTest_881, PrefixLongerThanStringReturnsFalse_881) {
    EXPECT_FALSE(starts_with("ab", "abc"));
    EXPECT_FALSE(starts_with("a", "aaaa"));
}

// ---------- Case sensitivity & special characters ----------

TEST(CoverageHelperStartsWithTest_881, CaseSensitivity_881) {
    EXPECT_TRUE(starts_with("Hello", "He"));
    EXPECT_FALSE(starts_with("Hello", "he"));  // case-sensitive
}

TEST(CoverageHelperStartsWithTest_881, HandlesWhitespace_881) {
    EXPECT_TRUE(starts_with("  indented", "  "));
    EXPECT_FALSE(starts_with("  indented", " "));
}

TEST(CoverageHelperStartsWithTest_881, HandlesPunctuation_881) {
    EXPECT_TRUE(starts_with("[]{}()<>", "[]"));
    EXPECT_FALSE(starts_with("[]{}()<>", "{}"));
}

// ---------- Multibyte / UTF-8 bytes (treated as opaque bytes by std::string) ----------

TEST(CoverageHelperStartsWithTest_881, HandlesUtf8Sequences_881) {
    // "안녕" (Korean) is multibyte in UTF-8; std::string matches byte sequences.
    std::string s = u8"안녕 Catch2";
    EXPECT_TRUE(starts_with(s, u8"안"));
    EXPECT_TRUE(starts_with(s, u8"안녕"));
    EXPECT_FALSE(starts_with(s, u8"녕")); // not at start
}
