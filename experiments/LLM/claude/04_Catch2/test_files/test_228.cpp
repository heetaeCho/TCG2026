#include <gtest/gtest.h>
#include "catch2/matchers/catch_matchers_string.hpp"

using namespace Catch::Matchers;

// Helper to check if a matcher matches a given string
// The Catch2 StringMatcherBase has a match() method that takes a std::string
// and returns bool.

// ===== StartsWith Tests =====

TEST(StartsWithMatcherTest_228, MatchesWhenStringStartsWithPrefix_228) {
    auto matcher = StartsWith("Hello");
    EXPECT_TRUE(matcher.match("Hello World"));
}

TEST(StartsWithMatcherTest_228, MatchesExactString_228) {
    auto matcher = StartsWith("Hello");
    EXPECT_TRUE(matcher.match("Hello"));
}

TEST(StartsWithMatcherTest_228, DoesNotMatchWhenPrefixAbsent_228) {
    auto matcher = StartsWith("Hello");
    EXPECT_FALSE(matcher.match("World Hello"));
}

TEST(StartsWithMatcherTest_228, DoesNotMatchWhenStringIsShorterThanPrefix_228) {
    auto matcher = StartsWith("Hello World");
    EXPECT_FALSE(matcher.match("Hello"));
}

TEST(StartsWithMatcherTest_228, EmptyPrefixMatchesAnyString_228) {
    auto matcher = StartsWith("");
    EXPECT_TRUE(matcher.match("anything"));
}

TEST(StartsWithMatcherTest_228, EmptyPrefixMatchesEmptyString_228) {
    auto matcher = StartsWith("");
    EXPECT_TRUE(matcher.match(""));
}

TEST(StartsWithMatcherTest_228, EmptyStringDoesNotMatchNonEmptyPrefix_228) {
    auto matcher = StartsWith("Hello");
    EXPECT_FALSE(matcher.match(""));
}

TEST(StartsWithMatcherTest_228, CaseSensitiveByDefault_228) {
    auto matcher = StartsWith("Hello");
    EXPECT_FALSE(matcher.match("hello World"));
}

TEST(StartsWithMatcherTest_228, CaseSensitiveExplicit_228) {
    auto matcher = StartsWith("Hello", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(matcher.match("hello World"));
    EXPECT_TRUE(matcher.match("Hello World"));
}

TEST(StartsWithMatcherTest_228, CaseInsensitiveMatches_228) {
    auto matcher = StartsWith("hello", Catch::CaseSensitive::No);
    EXPECT_TRUE(matcher.match("HELLO World"));
}

TEST(StartsWithMatcherTest_228, CaseInsensitiveMatchesMixedCase_228) {
    auto matcher = StartsWith("HeLLo", Catch::CaseSensitive::No);
    EXPECT_TRUE(matcher.match("hElLo World"));
}

TEST(StartsWithMatcherTest_228, CaseInsensitiveDoesNotMatchDifferentString_228) {
    auto matcher = StartsWith("Hello", Catch::CaseSensitive::No);
    EXPECT_FALSE(matcher.match("World"));
}

TEST(StartsWithMatcherTest_228, SingleCharacterPrefix_228) {
    auto matcher = StartsWith("H");
    EXPECT_TRUE(matcher.match("Hello"));
    EXPECT_FALSE(matcher.match("ello"));
}

TEST(StartsWithMatcherTest_228, SpecialCharactersInPrefix_228) {
    auto matcher = StartsWith("Hello\n");
    EXPECT_TRUE(matcher.match("Hello\nWorld"));
    EXPECT_FALSE(matcher.match("Hello World"));
}

TEST(StartsWithMatcherTest_228, SpacesInPrefix_228) {
    auto matcher = StartsWith("  ");
    EXPECT_TRUE(matcher.match("  Hello"));
    EXPECT_FALSE(matcher.match("Hello"));
}

TEST(StartsWithMatcherTest_228, DescriptionIsNotEmpty_228) {
    auto matcher = StartsWith("Hello");
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

TEST(StartsWithMatcherTest_228, CaseInsensitiveEmptyPrefix_228) {
    auto matcher = StartsWith("", Catch::CaseSensitive::No);
    EXPECT_TRUE(matcher.match("anything"));
    EXPECT_TRUE(matcher.match(""));
}

TEST(StartsWithMatcherTest_228, ExactMatchCaseInsensitive_228) {
    auto matcher = StartsWith("HELLO", Catch::CaseSensitive::No);
    EXPECT_TRUE(matcher.match("hello"));
}

TEST(StartsWithMatcherTest_228, LongStringPrefix_228) {
    std::string longPrefix(1000, 'a');
    auto matcher = StartsWith(longPrefix);
    std::string matchingStr = longPrefix + "extra";
    EXPECT_TRUE(matcher.match(matchingStr));
    
    std::string shortStr(999, 'a');
    EXPECT_FALSE(matcher.match(shortStr));
}

TEST(StartsWithMatcherTest_228, UnicodeBasicTest_228) {
    auto matcher = StartsWith("café");
    EXPECT_TRUE(matcher.match("café latte"));
    EXPECT_FALSE(matcher.match("Café latte"));
}
