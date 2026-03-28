// File: tests/wildcard_pattern_tests_1082.cpp

#include <gtest/gtest.h>

#include "catch2/internal/catch_wildcard_pattern.hpp"

// If CaseSensitive lives in Catch namespace as in Catch2:
//   enum class CaseSensitive { Yes, No };
// we assume it's available via the included header above.

using Catch::WildcardPattern;

class WildcardPatternTest_1082 : public ::testing::Test {};

// ---------------------------
// Exact (no wildcard) matches
// ---------------------------

TEST_F(WildcardPatternTest_1082, ExactMatch_CaseSensitive_1082) {
    WildcardPattern pat("Hello", Catch::CaseSensitive::Yes);

    EXPECT_TRUE(pat.matches("Hello"));
    EXPECT_FALSE(pat.matches("hello"));   // differs in case
    EXPECT_FALSE(pat.matches("Hello!"));  // extra chars
    EXPECT_FALSE(pat.matches(" Hel lo")); // whitespace difference
}

TEST_F(WildcardPatternTest_1082, ExactMatch_CaseInsensitive_1082) {
    WildcardPattern pat("Hello", Catch::CaseSensitive::No);

    EXPECT_TRUE(pat.matches("Hello"));
    EXPECT_TRUE(pat.matches("hello"));    // case-insensitive
    EXPECT_FALSE(pat.matches("Hello!"));  // extra chars not allowed
    EXPECT_FALSE(pat.matches("Hel lo"));  // different content
}

// ---------------------------
// Single-sided wildcard cases
// ---------------------------

TEST_F(WildcardPatternTest_1082, WildcardAtEnd_PrefixMatch_1082) {
    WildcardPattern pat("He*", Catch::CaseSensitive::Yes);

    EXPECT_TRUE(pat.matches("He"));
    EXPECT_TRUE(pat.matches("Hello"));
    EXPECT_TRUE(pat.matches("He123"));
    EXPECT_FALSE(pat.matches("he"));      // case difference
    EXPECT_FALSE(pat.matches("AHe"));     // not a prefix
}

TEST_F(WildcardPatternTest_1082, WildcardAtStart_SuffixMatch_1082) {
    WildcardPattern pat("*lo", Catch::CaseSensitive::Yes);

    EXPECT_TRUE(pat.matches("lo"));
    EXPECT_TRUE(pat.matches("Hello"));
    EXPECT_TRUE(pat.matches("YOLO"));
    EXPECT_FALSE(pat.matches("Lo"));      // case difference
    EXPECT_FALSE(pat.matches("lo!"));     // not a suffix
}

// ---------------------------
// Wildcards on both sides
// ---------------------------

TEST_F(WildcardPatternTest_1082, WildcardAtBothEnds_SubstringMatch_1082) {
    WildcardPattern pat("*ell*", Catch::CaseSensitive::Yes);

    EXPECT_TRUE(pat.matches("Hello"));
    EXPECT_TRUE(pat.matches("Well, well"));
    EXPECT_FALSE(pat.matches("ELLE"));    // case difference
    EXPECT_FALSE(pat.matches("he l l"));  // different content
}

TEST_F(WildcardPatternTest_1082, WildcardAtBothEnds_CaseInsensitive_1082) {
    WildcardPattern pat("*ELL*", Catch::CaseSensitive::No);

    EXPECT_TRUE(pat.matches("Hello"));
    EXPECT_TRUE(pat.matches("yELLow"));
    EXPECT_FALSE(pat.matches("hel l o")); // content does not contain contiguous "ell"
}

// ---------------------------
// Boundary & corner cases
// ---------------------------

TEST_F(WildcardPatternTest_1082, EmptyPattern_ExactEmptyOnly_1082) {
    WildcardPattern pat("", Catch::CaseSensitive::Yes);

    EXPECT_TRUE(pat.matches(""));   // exact empty
    EXPECT_FALSE(pat.matches("a")); // any non-empty should not match
    EXPECT_FALSE(pat.matches(" ")); // whitespace is not empty
}

TEST_F(WildcardPatternTest_1082, PatternOnlyWildcard_StarMatchesAnything_1082) {
    // Based on the observable interface, a pattern with a single '*'
    // should match any string (typical wildcard semantics).
    WildcardPattern pat("*", Catch::CaseSensitive::Yes);

    EXPECT_TRUE(pat.matches(""));
    EXPECT_TRUE(pat.matches("a"));
    EXPECT_TRUE(pat.matches("Hello"));
    EXPECT_TRUE(pat.matches("HELLO world"));
}

TEST_F(WildcardPatternTest_1082, PatternWithLeadingAndTrailingWildcards_MinimalCore_1082) {
    WildcardPattern pat("*a*", Catch::CaseSensitive::No);

    EXPECT_TRUE(pat.matches("a"));
    EXPECT_TRUE(pat.matches("A"));
    EXPECT_TRUE(pat.matches("cat"));
    EXPECT_TRUE(pat.matches("CAtapult"));
    EXPECT_FALSE(pat.matches(""));        // empty has no 'a'
}

// ---------------------------
// Negative / mismatch cases
// ---------------------------

TEST_F(WildcardPatternTest_1082, NoMatchCases_1082) {
    {
        WildcardPattern pat("he*", Catch::CaseSensitive::Yes);
        EXPECT_FALSE(pat.matches("ah"));      // not a prefix
        EXPECT_FALSE(pat.matches("HE"));      // case mismatch
        EXPECT_FALSE(pat.matches("h"));       // too short
    }
    {
        WildcardPattern pat("*lo", Catch::CaseSensitive::No);
        EXPECT_FALSE(pat.matches("l o"));     // not contiguous
        EXPECT_FALSE(pat.matches("lol "));    // suffix mismatch
    }
    {
        WildcardPattern pat("hello", Catch::CaseSensitive::No);
        EXPECT_FALSE(pat.matches("hell"));    // shorter
        EXPECT_FALSE(pat.matches("helloo"));  // longer
    }
}
