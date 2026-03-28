#include <gtest/gtest.h>
#include "catch2/internal/catch_wildcard_pattern.hpp"

// Test fixture for WildcardPattern tests
class WildcardPatternTest_561 : public ::testing::Test {
protected:
};

// ============================================================
// Tests with CaseSensitive::Yes
// ============================================================

// No wildcard - exact match
TEST_F(WildcardPatternTest_561, ExactMatch_CaseSensitive_561) {
    Catch::WildcardPattern pattern("hello", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("hello"));
}

TEST_F(WildcardPatternTest_561, ExactMatch_CaseSensitive_NoMatch_561) {
    Catch::WildcardPattern pattern("hello", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("world"));
}

TEST_F(WildcardPatternTest_561, ExactMatch_CaseSensitive_DifferentCase_561) {
    Catch::WildcardPattern pattern("Hello", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("hello"));
}

TEST_F(WildcardPatternTest_561, ExactMatch_CaseSensitive_SubstringNoMatch_561) {
    Catch::WildcardPattern pattern("hello", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("hello world"));
}

// Wildcard at start - pattern starts with *
TEST_F(WildcardPatternTest_561, WildcardAtStart_Matches_561) {
    Catch::WildcardPattern pattern("*world", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("hello world"));
}

TEST_F(WildcardPatternTest_561, WildcardAtStart_ExactSuffix_561) {
    Catch::WildcardPattern pattern("*world", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("world"));
}

TEST_F(WildcardPatternTest_561, WildcardAtStart_NoMatch_561) {
    Catch::WildcardPattern pattern("*world", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("hello"));
}

TEST_F(WildcardPatternTest_561, WildcardAtStart_CaseSensitive_NoMatch_561) {
    Catch::WildcardPattern pattern("*World", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("hello world"));
}

// Wildcard at end - pattern ends with *
TEST_F(WildcardPatternTest_561, WildcardAtEnd_Matches_561) {
    Catch::WildcardPattern pattern("hello*", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("hello world"));
}

TEST_F(WildcardPatternTest_561, WildcardAtEnd_ExactPrefix_561) {
    Catch::WildcardPattern pattern("hello*", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("hello"));
}

TEST_F(WildcardPatternTest_561, WildcardAtEnd_NoMatch_561) {
    Catch::WildcardPattern pattern("hello*", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("world"));
}

TEST_F(WildcardPatternTest_561, WildcardAtEnd_CaseSensitive_NoMatch_561) {
    Catch::WildcardPattern pattern("Hello*", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("hello world"));
}

// Wildcard at both ends - pattern starts and ends with *
TEST_F(WildcardPatternTest_561, WildcardAtBothEnds_Matches_561) {
    Catch::WildcardPattern pattern("*llo wor*", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("hello world"));
}

TEST_F(WildcardPatternTest_561, WildcardAtBothEnds_ContainsSubstring_561) {
    Catch::WildcardPattern pattern("*ello*", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("hello world"));
}

TEST_F(WildcardPatternTest_561, WildcardAtBothEnds_ExactMatch_561) {
    Catch::WildcardPattern pattern("*hello*", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("hello"));
}

TEST_F(WildcardPatternTest_561, WildcardAtBothEnds_NoMatch_561) {
    Catch::WildcardPattern pattern("*xyz*", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("hello world"));
}

TEST_F(WildcardPatternTest_561, WildcardAtBothEnds_CaseSensitive_NoMatch_561) {
    Catch::WildcardPattern pattern("*HELLO*", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("hello world"));
}

// ============================================================
// Tests with CaseSensitive::No
// ============================================================

TEST_F(WildcardPatternTest_561, ExactMatch_CaseInsensitive_561) {
    Catch::WildcardPattern pattern("Hello", Catch::CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("hello"));
}

TEST_F(WildcardPatternTest_561, ExactMatch_CaseInsensitive_UpperCase_561) {
    Catch::WildcardPattern pattern("hello", Catch::CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("HELLO"));
}

TEST_F(WildcardPatternTest_561, ExactMatch_CaseInsensitive_NoMatch_561) {
    Catch::WildcardPattern pattern("hello", Catch::CaseSensitive::No);
    EXPECT_FALSE(pattern.matches("world"));
}

TEST_F(WildcardPatternTest_561, WildcardAtStart_CaseInsensitive_561) {
    Catch::WildcardPattern pattern("*WORLD", Catch::CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("hello world"));
}

TEST_F(WildcardPatternTest_561, WildcardAtEnd_CaseInsensitive_561) {
    Catch::WildcardPattern pattern("HELLO*", Catch::CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("hello world"));
}

TEST_F(WildcardPatternTest_561, WildcardAtBothEnds_CaseInsensitive_561) {
    Catch::WildcardPattern pattern("*ELLO*", Catch::CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("hello world"));
}

// ============================================================
// Boundary / Edge cases
// ============================================================

TEST_F(WildcardPatternTest_561, EmptyPattern_MatchesEmptyString_561) {
    Catch::WildcardPattern pattern("", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches(""));
}

TEST_F(WildcardPatternTest_561, EmptyPattern_DoesNotMatchNonEmpty_561) {
    Catch::WildcardPattern pattern("", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("hello"));
}

TEST_F(WildcardPatternTest_561, WildcardOnly_MatchesAnything_561) {
    Catch::WildcardPattern pattern("*", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches(""));
    EXPECT_TRUE(pattern.matches("anything"));
    EXPECT_TRUE(pattern.matches("hello world"));
}

TEST_F(WildcardPatternTest_561, DoubleWildcard_MatchesAnything_561) {
    // Pattern is "**" which should have wildcard at both ends with empty pattern
    Catch::WildcardPattern pattern("**", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches(""));
    EXPECT_TRUE(pattern.matches("anything"));
}

TEST_F(WildcardPatternTest_561, WildcardAtStart_EmptyString_561) {
    Catch::WildcardPattern pattern("*hello", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches(""));
}

TEST_F(WildcardPatternTest_561, WildcardAtEnd_EmptyString_561) {
    Catch::WildcardPattern pattern("hello*", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches(""));
}

TEST_F(WildcardPatternTest_561, WildcardAtBothEnds_EmptyString_561) {
    Catch::WildcardPattern pattern("*hello*", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches(""));
}

TEST_F(WildcardPatternTest_561, SingleCharPattern_561) {
    Catch::WildcardPattern pattern("a", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("a"));
    EXPECT_FALSE(pattern.matches("b"));
    EXPECT_FALSE(pattern.matches("ab"));
}

TEST_F(WildcardPatternTest_561, WildcardAtStart_SingleChar_561) {
    Catch::WildcardPattern pattern("*a", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("a"));
    EXPECT_TRUE(pattern.matches("ba"));
    EXPECT_FALSE(pattern.matches("ab"));
}

TEST_F(WildcardPatternTest_561, WildcardAtEnd_SingleChar_561) {
    Catch::WildcardPattern pattern("a*", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("a"));
    EXPECT_TRUE(pattern.matches("ab"));
    EXPECT_FALSE(pattern.matches("ba"));
}

TEST_F(WildcardPatternTest_561, WildcardAtBothEnds_SingleChar_561) {
    Catch::WildcardPattern pattern("*a*", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("a"));
    EXPECT_TRUE(pattern.matches("ab"));
    EXPECT_TRUE(pattern.matches("ba"));
    EXPECT_TRUE(pattern.matches("bab"));
    EXPECT_FALSE(pattern.matches("b"));
}

// Test that partial matches don't work for exact pattern
TEST_F(WildcardPatternTest_561, NoWildcard_PartialMatch_561) {
    Catch::WildcardPattern pattern("hello world", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("hello"));
    EXPECT_FALSE(pattern.matches("world"));
    EXPECT_TRUE(pattern.matches("hello world"));
}

// Test with special characters in pattern (no wildcard)
TEST_F(WildcardPatternTest_561, SpecialCharacters_561) {
    Catch::WildcardPattern pattern("[test]", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("[test]"));
    EXPECT_FALSE(pattern.matches("test"));
}

// Test with spaces
TEST_F(WildcardPatternTest_561, PatternWithSpaces_561) {
    Catch::WildcardPattern pattern("*hello world*", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("hello world"));
    EXPECT_TRUE(pattern.matches("say hello world now"));
    EXPECT_FALSE(pattern.matches("helloworld"));
}

// Test long strings
TEST_F(WildcardPatternTest_561, LongString_WildcardAtBothEnds_561) {
    std::string longStr(1000, 'a');
    longStr += "needle";
    longStr += std::string(1000, 'b');
    Catch::WildcardPattern pattern("*needle*", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches(longStr));
}

TEST_F(WildcardPatternTest_561, LongString_WildcardAtBothEnds_NotFound_561) {
    std::string longStr(1000, 'a');
    Catch::WildcardPattern pattern("*needle*", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches(longStr));
}

// MixedCase with case insensitive
TEST_F(WildcardPatternTest_561, MixedCase_CaseInsensitive_WildcardBothEnds_561) {
    Catch::WildcardPattern pattern("*HeLLo WoRLd*", Catch::CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("say HELLO WORLD now"));
    EXPECT_TRUE(pattern.matches("hello world"));
}

// Verify string that equals pattern after wildcard removal
TEST_F(WildcardPatternTest_561, WildcardAtStart_ExactAfterRemoval_561) {
    Catch::WildcardPattern pattern("*test", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("test"));
    EXPECT_TRUE(pattern.matches("mytest"));
    EXPECT_FALSE(pattern.matches("testing"));
}

TEST_F(WildcardPatternTest_561, WildcardAtEnd_ExactAfterRemoval_561) {
    Catch::WildcardPattern pattern("test*", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("test"));
    EXPECT_TRUE(pattern.matches("testing"));
    EXPECT_FALSE(pattern.matches("mytest"));
}
