#include <gtest/gtest.h>
#include <string>
#include "catch2/matchers/catch_matchers_string.hpp"

using namespace Catch::Matchers;

class StartsWithMatcherTest_221 : public ::testing::Test {
protected:
    // Helper to create case-sensitive StartsWithMatcher
    StartsWithMatcher createCaseSensitive(const std::string& str) {
        return StartsWithMatcher(CasedString(str, CaseSensitive::Yes));
    }

    // Helper to create case-insensitive StartsWithMatcher
    StartsWithMatcher createCaseInsensitive(const std::string& str) {
        return StartsWithMatcher(CasedString(str, CaseSensitive::No));
    }
};

// Normal operation tests - case sensitive

TEST_F(StartsWithMatcherTest_221, MatchesExactPrefix_CaseSensitive_221) {
    auto matcher = createCaseSensitive("Hello");
    EXPECT_TRUE(matcher.match("Hello World"));
}

TEST_F(StartsWithMatcherTest_221, MatchesExactString_CaseSensitive_221) {
    auto matcher = createCaseSensitive("Hello");
    EXPECT_TRUE(matcher.match("Hello"));
}

TEST_F(StartsWithMatcherTest_221, DoesNotMatchDifferentPrefix_CaseSensitive_221) {
    auto matcher = createCaseSensitive("Hello");
    EXPECT_FALSE(matcher.match("World Hello"));
}

TEST_F(StartsWithMatcherTest_221, DoesNotMatchWrongCase_CaseSensitive_221) {
    auto matcher = createCaseSensitive("Hello");
    EXPECT_FALSE(matcher.match("hello World"));
}

TEST_F(StartsWithMatcherTest_221, DoesNotMatchSubstringInMiddle_CaseSensitive_221) {
    auto matcher = createCaseSensitive("World");
    EXPECT_FALSE(matcher.match("Hello World"));
}

// Normal operation tests - case insensitive

TEST_F(StartsWithMatcherTest_221, MatchesExactPrefix_CaseInsensitive_221) {
    auto matcher = createCaseInsensitive("Hello");
    EXPECT_TRUE(matcher.match("Hello World"));
}

TEST_F(StartsWithMatcherTest_221, MatchesDifferentCase_CaseInsensitive_221) {
    auto matcher = createCaseInsensitive("hello");
    EXPECT_TRUE(matcher.match("HELLO World"));
}

TEST_F(StartsWithMatcherTest_221, MatchesMixedCase_CaseInsensitive_221) {
    auto matcher = createCaseInsensitive("HeLLo");
    EXPECT_TRUE(matcher.match("hElLo World"));
}

TEST_F(StartsWithMatcherTest_221, DoesNotMatchDifferentPrefix_CaseInsensitive_221) {
    auto matcher = createCaseInsensitive("Hello");
    EXPECT_FALSE(matcher.match("World Hello"));
}

// Boundary conditions

TEST_F(StartsWithMatcherTest_221, EmptyPrefixMatchesAnything_221) {
    auto matcher = createCaseSensitive("");
    EXPECT_TRUE(matcher.match("Hello"));
}

TEST_F(StartsWithMatcherTest_221, EmptyPrefixMatchesEmptyString_221) {
    auto matcher = createCaseSensitive("");
    EXPECT_TRUE(matcher.match(""));
}

TEST_F(StartsWithMatcherTest_221, NonEmptyPrefixDoesNotMatchEmptyString_221) {
    auto matcher = createCaseSensitive("Hello");
    EXPECT_FALSE(matcher.match(""));
}

TEST_F(StartsWithMatcherTest_221, PrefixLongerThanSource_CaseSensitive_221) {
    auto matcher = createCaseSensitive("Hello World!");
    EXPECT_FALSE(matcher.match("Hello"));
}

TEST_F(StartsWithMatcherTest_221, PrefixLongerThanSource_CaseInsensitive_221) {
    auto matcher = createCaseInsensitive("Hello World!");
    EXPECT_FALSE(matcher.match("Hello"));
}

TEST_F(StartsWithMatcherTest_221, SingleCharacterPrefix_Matches_221) {
    auto matcher = createCaseSensitive("H");
    EXPECT_TRUE(matcher.match("Hello"));
}

TEST_F(StartsWithMatcherTest_221, SingleCharacterPrefix_DoesNotMatch_221) {
    auto matcher = createCaseSensitive("W");
    EXPECT_FALSE(matcher.match("Hello"));
}

TEST_F(StartsWithMatcherTest_221, SingleCharacterSource_Matches_221) {
    auto matcher = createCaseSensitive("H");
    EXPECT_TRUE(matcher.match("H"));
}

TEST_F(StartsWithMatcherTest_221, SingleCharacterSource_DoesNotMatch_221) {
    auto matcher = createCaseSensitive("H");
    EXPECT_FALSE(matcher.match("W"));
}

// Special characters

TEST_F(StartsWithMatcherTest_221, MatchesWithSpaces_221) {
    auto matcher = createCaseSensitive("Hello ");
    EXPECT_TRUE(matcher.match("Hello World"));
}

TEST_F(StartsWithMatcherTest_221, MatchesWithSpecialCharacters_221) {
    auto matcher = createCaseSensitive("Hello!");
    EXPECT_TRUE(matcher.match("Hello! World"));
}

TEST_F(StartsWithMatcherTest_221, MatchesWithNewline_221) {
    auto matcher = createCaseSensitive("Hello\n");
    EXPECT_TRUE(matcher.match("Hello\nWorld"));
}

TEST_F(StartsWithMatcherTest_221, MatchesWithTab_221) {
    auto matcher = createCaseSensitive("Hello\t");
    EXPECT_TRUE(matcher.match("Hello\tWorld"));
}

// Describe method test

TEST_F(StartsWithMatcherTest_221, DescribeContainsStartsWith_221) {
    auto matcher = createCaseSensitive("Hello");
    std::string description = matcher.describe();
    EXPECT_NE(description.find("starts with"), std::string::npos);
}

TEST_F(StartsWithMatcherTest_221, DescribeContainsPattern_221) {
    auto matcher = createCaseSensitive("Hello");
    std::string description = matcher.describe();
    EXPECT_NE(description.find("Hello"), std::string::npos);
}

// Case insensitive boundary

TEST_F(StartsWithMatcherTest_221, EmptyPrefixMatchesAnything_CaseInsensitive_221) {
    auto matcher = createCaseInsensitive("");
    EXPECT_TRUE(matcher.match("Hello"));
}

TEST_F(StartsWithMatcherTest_221, EmptyPrefixMatchesEmptyString_CaseInsensitive_221) {
    auto matcher = createCaseInsensitive("");
    EXPECT_TRUE(matcher.match(""));
}

TEST_F(StartsWithMatcherTest_221, FullStringMatch_CaseSensitive_221) {
    auto matcher = createCaseSensitive("Hello World");
    EXPECT_TRUE(matcher.match("Hello World"));
}

TEST_F(StartsWithMatcherTest_221, FullStringMatch_CaseInsensitive_221) {
    auto matcher = createCaseInsensitive("hello world");
    EXPECT_TRUE(matcher.match("HELLO WORLD"));
}

TEST_F(StartsWithMatcherTest_221, AlmostMatching_OffByOne_221) {
    auto matcher = createCaseSensitive("Hellp");
    EXPECT_FALSE(matcher.match("Hello World"));
}

TEST_F(StartsWithMatcherTest_221, NumericPrefix_221) {
    auto matcher = createCaseSensitive("123");
    EXPECT_TRUE(matcher.match("12345"));
}

TEST_F(StartsWithMatcherTest_221, NumericPrefixNoMatch_221) {
    auto matcher = createCaseSensitive("124");
    EXPECT_FALSE(matcher.match("12345"));
}
