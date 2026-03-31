#include <gtest/gtest.h>
#include "catch2/internal/catch_wildcard_pattern.hpp"

using namespace Catch;

// Test fixture for WildcardPattern tests
class WildcardPatternTest_1082 : public ::testing::Test {
protected:
};

// ==================== Exact Match Tests ====================

TEST_F(WildcardPatternTest_1082, ExactMatchCaseSensitive_1082) {
    WildcardPattern pattern("Hello", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("Hello"));
}

TEST_F(WildcardPatternTest_1082, ExactMatchCaseSensitiveFails_1082) {
    WildcardPattern pattern("Hello", CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("hello"));
}

TEST_F(WildcardPatternTest_1082, ExactMatchCaseInsensitive_1082) {
    WildcardPattern pattern("Hello", CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("hello"));
}

TEST_F(WildcardPatternTest_1082, ExactMatchCaseInsensitiveMixed_1082) {
    WildcardPattern pattern("Hello", CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("HELLO"));
}

TEST_F(WildcardPatternTest_1082, ExactMatchNoMatchDifferentString_1082) {
    WildcardPattern pattern("Hello", CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("World"));
}

// ==================== Wildcard at Start Tests ====================

TEST_F(WildcardPatternTest_1082, WildcardAtStartMatches_1082) {
    WildcardPattern pattern("*World", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("Hello World"));
}

TEST_F(WildcardPatternTest_1082, WildcardAtStartMatchesExact_1082) {
    WildcardPattern pattern("*World", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("World"));
}

TEST_F(WildcardPatternTest_1082, WildcardAtStartDoesNotMatch_1082) {
    WildcardPattern pattern("*World", CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("Hello"));
}

TEST_F(WildcardPatternTest_1082, WildcardAtStartCaseInsensitive_1082) {
    WildcardPattern pattern("*world", CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("Hello WORLD"));
}

TEST_F(WildcardPatternTest_1082, WildcardAtStartCaseSensitiveFails_1082) {
    WildcardPattern pattern("*World", CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("Hello world"));
}

// ==================== Wildcard at End Tests ====================

TEST_F(WildcardPatternTest_1082, WildcardAtEndMatches_1082) {
    WildcardPattern pattern("Hello*", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("Hello World"));
}

TEST_F(WildcardPatternTest_1082, WildcardAtEndMatchesExact_1082) {
    WildcardPattern pattern("Hello*", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("Hello"));
}

TEST_F(WildcardPatternTest_1082, WildcardAtEndDoesNotMatch_1082) {
    WildcardPattern pattern("Hello*", CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("World"));
}

TEST_F(WildcardPatternTest_1082, WildcardAtEndCaseInsensitive_1082) {
    WildcardPattern pattern("hello*", CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("HELLO World"));
}

TEST_F(WildcardPatternTest_1082, WildcardAtEndCaseSensitiveFails_1082) {
    WildcardPattern pattern("Hello*", CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("hello World"));
}

// ==================== Wildcard at Both Ends Tests ====================

TEST_F(WildcardPatternTest_1082, WildcardAtBothEndsMatchesContains_1082) {
    WildcardPattern pattern("*ello*", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("Hello World"));
}

TEST_F(WildcardPatternTest_1082, WildcardAtBothEndsMatchesExact_1082) {
    WildcardPattern pattern("*ello*", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("ello"));
}

TEST_F(WildcardPatternTest_1082, WildcardAtBothEndsDoesNotMatch_1082) {
    WildcardPattern pattern("*xyz*", CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("Hello World"));
}

TEST_F(WildcardPatternTest_1082, WildcardAtBothEndsCaseInsensitive_1082) {
    WildcardPattern pattern("*ELLO*", CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("Hello World"));
}

TEST_F(WildcardPatternTest_1082, WildcardAtBothEndsCaseSensitiveFails_1082) {
    WildcardPattern pattern("*ELLO*", CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("Hello World"));
}

// ==================== Empty and Boundary Tests ====================

TEST_F(WildcardPatternTest_1082, EmptyPatternMatchesEmptyString_1082) {
    WildcardPattern pattern("", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches(""));
}

TEST_F(WildcardPatternTest_1082, EmptyPatternDoesNotMatchNonEmpty_1082) {
    WildcardPattern pattern("", CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("something"));
}

TEST_F(WildcardPatternTest_1082, WildcardOnlyMatchesAnything_1082) {
    WildcardPattern pattern("*", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("anything"));
}

TEST_F(WildcardPatternTest_1082, WildcardOnlyMatchesEmpty_1082) {
    WildcardPattern pattern("*", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches(""));
}

TEST_F(WildcardPatternTest_1082, DoubleWildcardMatchesAnything_1082) {
    WildcardPattern pattern("**", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("anything"));
}

TEST_F(WildcardPatternTest_1082, DoubleWildcardMatchesEmpty_1082) {
    WildcardPattern pattern("**", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches(""));
}

TEST_F(WildcardPatternTest_1082, EmptyStringMatchesEmptyPattern_1082) {
    WildcardPattern pattern("", CaseSensitive::No);
    EXPECT_TRUE(pattern.matches(""));
}

// ==================== Single Character Tests ====================

TEST_F(WildcardPatternTest_1082, SingleCharPattern_1082) {
    WildcardPattern pattern("a", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("a"));
    EXPECT_FALSE(pattern.matches("b"));
    EXPECT_FALSE(pattern.matches("ab"));
}

TEST_F(WildcardPatternTest_1082, SingleCharPatternCaseInsensitive_1082) {
    WildcardPattern pattern("a", CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("A"));
    EXPECT_TRUE(pattern.matches("a"));
}

// ==================== Pattern with Spaces and Special Chars ====================

TEST_F(WildcardPatternTest_1082, PatternWithSpaces_1082) {
    WildcardPattern pattern("*hello world*", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("say hello world now"));
}

TEST_F(WildcardPatternTest_1082, PatternWithSpecialChars_1082) {
    WildcardPattern pattern("test[0]*", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("test[0] passed"));
}

// ==================== Substring Not at End for WildcardAtStart ====================

TEST_F(WildcardPatternTest_1082, WildcardAtStartMiddleOccurrenceOnly_1082) {
    WildcardPattern pattern("*abc", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("xyzabc"));
    EXPECT_FALSE(pattern.matches("xyzabcdef"));
}

// ==================== Substring Not at Start for WildcardAtEnd ====================

TEST_F(WildcardPatternTest_1082, WildcardAtEndMiddleOccurrenceOnly_1082) {
    WildcardPattern pattern("abc*", CaseSensitive::Yes);
    EXPECT_TRUE(pattern.matches("abcdef"));
    EXPECT_FALSE(pattern.matches("xyzabcdef"));
}

// ==================== Partial Match Tests ====================

TEST_F(WildcardPatternTest_1082, ExactPatternLongerThanString_1082) {
    WildcardPattern pattern("HelloWorld", CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("Hello"));
}

TEST_F(WildcardPatternTest_1082, ExactPatternShorterThanString_1082) {
    WildcardPattern pattern("Hello", CaseSensitive::Yes);
    EXPECT_FALSE(pattern.matches("HelloWorld"));
}

// ==================== Case Sensitivity Edge Cases ====================

TEST_F(WildcardPatternTest_1082, CaseInsensitiveWildcardAtStart_1082) {
    WildcardPattern pattern("*ABC", CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("xyzabc"));
    EXPECT_TRUE(pattern.matches("xyzABC"));
    EXPECT_TRUE(pattern.matches("abc"));
}

TEST_F(WildcardPatternTest_1082, CaseInsensitiveWildcardAtEnd_1082) {
    WildcardPattern pattern("ABC*", CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("abcxyz"));
    EXPECT_TRUE(pattern.matches("ABCxyz"));
    EXPECT_TRUE(pattern.matches("abc"));
}

TEST_F(WildcardPatternTest_1082, CaseInsensitiveWildcardAtBothEnds_1082) {
    WildcardPattern pattern("*ABC*", CaseSensitive::No);
    EXPECT_TRUE(pattern.matches("xyzabcxyz"));
    EXPECT_TRUE(pattern.matches("abc"));
    EXPECT_TRUE(pattern.matches("ABC"));
}
