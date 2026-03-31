#include <gtest/gtest.h>
#include <string>
#include "catch2/matchers/catch_matchers_string.hpp"

using namespace Catch::Matchers;

class EndsWithMatcherTest_222 : public ::testing::Test {
protected:
    // Helper to create case-sensitive EndsWithMatcher
    EndsWithMatcher makeCaseSensitive(const std::string& suffix) {
        return EndsWithMatcher(CasedString(suffix, CaseSensitive::Yes));
    }

    // Helper to create case-insensitive EndsWithMatcher
    EndsWithMatcher makeCaseInsensitive(const std::string& suffix) {
        return EndsWithMatcher(CasedString(suffix, CaseSensitive::No));
    }
};

// ===== Normal operation tests =====

TEST_F(EndsWithMatcherTest_222, MatchesWhenStringEndsWithSuffix_222) {
    auto matcher = makeCaseSensitive("world");
    EXPECT_TRUE(matcher.match("hello world"));
}

TEST_F(EndsWithMatcherTest_222, DoesNotMatchWhenStringDoesNotEndWithSuffix_222) {
    auto matcher = makeCaseSensitive("world");
    EXPECT_FALSE(matcher.match("hello earth"));
}

TEST_F(EndsWithMatcherTest_222, MatchesExactString_222) {
    auto matcher = makeCaseSensitive("hello");
    EXPECT_TRUE(matcher.match("hello"));
}

TEST_F(EndsWithMatcherTest_222, DoesNotMatchWhenSuffixAppearsInMiddle_222) {
    auto matcher = makeCaseSensitive("world");
    EXPECT_FALSE(matcher.match("world hello"));
}

TEST_F(EndsWithMatcherTest_222, MatchesSingleCharacterSuffix_222) {
    auto matcher = makeCaseSensitive("d");
    EXPECT_TRUE(matcher.match("world"));
}

TEST_F(EndsWithMatcherTest_222, DoesNotMatchSingleCharacterSuffix_222) {
    auto matcher = makeCaseSensitive("x");
    EXPECT_FALSE(matcher.match("world"));
}

// ===== Case sensitivity tests =====

TEST_F(EndsWithMatcherTest_222, CaseSensitiveDoesNotMatchDifferentCase_222) {
    auto matcher = makeCaseSensitive("WORLD");
    EXPECT_FALSE(matcher.match("hello world"));
}

TEST_F(EndsWithMatcherTest_222, CaseInsensitiveMatchesDifferentCase_222) {
    auto matcher = makeCaseInsensitive("WORLD");
    EXPECT_TRUE(matcher.match("hello world"));
}

TEST_F(EndsWithMatcherTest_222, CaseInsensitiveMatchesMixedCase_222) {
    auto matcher = makeCaseInsensitive("WoRlD");
    EXPECT_TRUE(matcher.match("hello WORLD"));
}

TEST_F(EndsWithMatcherTest_222, CaseInsensitiveDoesNotMatchDifferentString_222) {
    auto matcher = makeCaseInsensitive("EARTH");
    EXPECT_FALSE(matcher.match("hello world"));
}

TEST_F(EndsWithMatcherTest_222, CaseInsensitiveExactMatch_222) {
    auto matcher = makeCaseInsensitive("HELLO");
    EXPECT_TRUE(matcher.match("hello"));
}

// ===== Boundary condition tests =====

TEST_F(EndsWithMatcherTest_222, EmptySuffixMatchesAnyString_222) {
    auto matcher = makeCaseSensitive("");
    EXPECT_TRUE(matcher.match("hello"));
}

TEST_F(EndsWithMatcherTest_222, EmptySuffixMatchesEmptyString_222) {
    auto matcher = makeCaseSensitive("");
    EXPECT_TRUE(matcher.match(""));
}

TEST_F(EndsWithMatcherTest_222, EmptySourceDoesNotMatchNonEmptySuffix_222) {
    auto matcher = makeCaseSensitive("hello");
    EXPECT_FALSE(matcher.match(""));
}

TEST_F(EndsWithMatcherTest_222, SuffixLongerThanSourceDoesNotMatch_222) {
    auto matcher = makeCaseSensitive("very long suffix");
    EXPECT_FALSE(matcher.match("short"));
}

TEST_F(EndsWithMatcherTest_222, MatchesWithWhitespace_222) {
    auto matcher = makeCaseSensitive(" ");
    EXPECT_TRUE(matcher.match("hello "));
}

TEST_F(EndsWithMatcherTest_222, DoesNotMatchWithTrailingWhitespace_222) {
    auto matcher = makeCaseSensitive("hello");
    EXPECT_FALSE(matcher.match("hello "));
}

TEST_F(EndsWithMatcherTest_222, MatchesWithSpecialCharacters_222) {
    auto matcher = makeCaseSensitive("!!!");
    EXPECT_TRUE(matcher.match("hello!!!"));
}

TEST_F(EndsWithMatcherTest_222, MatchesWithNewline_222) {
    auto matcher = makeCaseSensitive("\n");
    EXPECT_TRUE(matcher.match("hello\n"));
}

// ===== Describe tests =====

TEST_F(EndsWithMatcherTest_222, DescribeContainsEndsWith_222) {
    auto matcher = makeCaseSensitive("world");
    std::string description = matcher.describe();
    EXPECT_NE(description.find("ends with"), std::string::npos);
}

TEST_F(EndsWithMatcherTest_222, DescribeContainsSuffix_222) {
    auto matcher = makeCaseSensitive("world");
    std::string description = matcher.describe();
    EXPECT_NE(description.find("world"), std::string::npos);
}

TEST_F(EndsWithMatcherTest_222, CaseInsensitiveDescribeDiffersFromCaseSensitive_222) {
    auto caseSensitive = makeCaseSensitive("world");
    auto caseInsensitive = makeCaseInsensitive("world");
    // Case insensitive description should include some indication of case insensitivity
    std::string descCS = caseSensitive.describe();
    std::string descCI = caseInsensitive.describe();
    EXPECT_NE(descCS, descCI);
}

// ===== Additional edge case tests =====

TEST_F(EndsWithMatcherTest_222, RepeatedSuffixMatches_222) {
    auto matcher = makeCaseSensitive("aa");
    EXPECT_TRUE(matcher.match("aaaa"));
}

TEST_F(EndsWithMatcherTest_222, PartialSuffixOverlapDoesNotMatch_222) {
    auto matcher = makeCaseSensitive("abc");
    EXPECT_FALSE(matcher.match("xyzab"));
}

TEST_F(EndsWithMatcherTest_222, NumericSuffixMatches_222) {
    auto matcher = makeCaseSensitive("123");
    EXPECT_TRUE(matcher.match("test123"));
}

TEST_F(EndsWithMatcherTest_222, NumericSuffixDoesNotMatch_222) {
    auto matcher = makeCaseSensitive("124");
    EXPECT_FALSE(matcher.match("test123"));
}

TEST_F(EndsWithMatcherTest_222, CaseInsensitiveEmptyStrings_222) {
    auto matcher = makeCaseInsensitive("");
    EXPECT_TRUE(matcher.match(""));
}

TEST_F(EndsWithMatcherTest_222, LongStringEndsWith_222) {
    std::string longStr(10000, 'a');
    longStr += "suffix";
    auto matcher = makeCaseSensitive("suffix");
    EXPECT_TRUE(matcher.match(longStr));
}

TEST_F(EndsWithMatcherTest_222, LongStringDoesNotEndWith_222) {
    std::string longStr(10000, 'a');
    auto matcher = makeCaseSensitive("suffix");
    EXPECT_FALSE(matcher.match(longStr));
}
