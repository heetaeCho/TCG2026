#include <gtest/gtest.h>
#include <string>
#include "catch2/matchers/catch_matchers_string.hpp"

using namespace Catch::Matchers;

class StringContainsMatcherTest_220 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(StringContainsMatcherTest_220, MatchesWhenSourceContainsSubstring_220) {
    CasedString comparator("hello", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("say hello world"));
}

TEST_F(StringContainsMatcherTest_220, MatchesExactString_220) {
    CasedString comparator("hello", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("hello"));
}

TEST_F(StringContainsMatcherTest_220, DoesNotMatchWhenSubstringAbsent_220) {
    CasedString comparator("hello", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("goodbye world"));
}

TEST_F(StringContainsMatcherTest_220, MatchesSubstringAtBeginning_220) {
    CasedString comparator("hello", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("hello world"));
}

TEST_F(StringContainsMatcherTest_220, MatchesSubstringAtEnd_220) {
    CasedString comparator("world", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("hello world"));
}

TEST_F(StringContainsMatcherTest_220, MatchesSubstringInMiddle_220) {
    CasedString comparator("lo wo", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("hello world"));
}

// Case sensitivity tests

TEST_F(StringContainsMatcherTest_220, CaseSensitiveDoesNotMatchDifferentCase_220) {
    CasedString comparator("Hello", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("hello world"));
}

TEST_F(StringContainsMatcherTest_220, CaseSensitiveMatchesSameCase_220) {
    CasedString comparator("Hello", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("Hello world"));
}

TEST_F(StringContainsMatcherTest_220, CaseInsensitiveMatchesDifferentCase_220) {
    CasedString comparator("hello", CaseSensitive::No);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("HELLO WORLD"));
}

TEST_F(StringContainsMatcherTest_220, CaseInsensitiveMatchesMixedCase_220) {
    CasedString comparator("HeLLo", CaseSensitive::No);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("hello world"));
}

TEST_F(StringContainsMatcherTest_220, CaseInsensitiveMatchesUpperInSource_220) {
    CasedString comparator("hello", CaseSensitive::No);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("say HELLO there"));
}

// Boundary condition tests

TEST_F(StringContainsMatcherTest_220, EmptySubstringMatchesAnyString_220) {
    CasedString comparator("", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("hello world"));
}

TEST_F(StringContainsMatcherTest_220, EmptySubstringMatchesEmptyString_220) {
    CasedString comparator("", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match(""));
}

TEST_F(StringContainsMatcherTest_220, NonEmptySubstringDoesNotMatchEmptySource_220) {
    CasedString comparator("hello", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match(""));
}

TEST_F(StringContainsMatcherTest_220, SubstringLongerThanSourceDoesNotMatch_220) {
    CasedString comparator("hello world!", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("hello"));
}

TEST_F(StringContainsMatcherTest_220, SingleCharacterMatch_220) {
    CasedString comparator("a", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("a"));
}

TEST_F(StringContainsMatcherTest_220, SingleCharacterNoMatch_220) {
    CasedString comparator("a", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("b"));
}

TEST_F(StringContainsMatcherTest_220, SingleCharacterCaseInsensitiveMatch_220) {
    CasedString comparator("a", CaseSensitive::No);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("A"));
}

// Special characters

TEST_F(StringContainsMatcherTest_220, MatchesWithSpecialCharacters_220) {
    CasedString comparator("!@#$", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("test!@#$test"));
}

TEST_F(StringContainsMatcherTest_220, MatchesWithSpaces_220) {
    CasedString comparator("  ", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("hello  world"));
}

TEST_F(StringContainsMatcherTest_220, DoesNotMatchWithSpacesWhenAbsent_220) {
    CasedString comparator("  ", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("hello world"));
}

TEST_F(StringContainsMatcherTest_220, MatchesNewlineCharacter_220) {
    CasedString comparator("\n", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("hello\nworld"));
}

// Describe method test

TEST_F(StringContainsMatcherTest_220, DescribeContainsOperationName_220) {
    CasedString comparator("hello", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
    // The description should mention "contains" and the target string
    EXPECT_NE(description.find("contains"), std::string::npos);
    EXPECT_NE(description.find("hello"), std::string::npos);
}

TEST_F(StringContainsMatcherTest_220, DescribeCaseInsensitiveMentionsCaseSensitivity_220) {
    CasedString comparator("hello", CaseSensitive::No);
    StringContainsMatcher matcher(comparator);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
    EXPECT_NE(description.find("contains"), std::string::npos);
}

// Multiple occurrences

TEST_F(StringContainsMatcherTest_220, MatchesWithMultipleOccurrences_220) {
    CasedString comparator("ab", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("ababab"));
}

// Repeated characters

TEST_F(StringContainsMatcherTest_220, MatchesRepeatedCharacters_220) {
    CasedString comparator("aaa", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("aaaa"));
}

TEST_F(StringContainsMatcherTest_220, DoesNotMatchInsufficientRepeatedCharacters_220) {
    CasedString comparator("aaa", CaseSensitive::Yes);
    StringContainsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("aa"));
}
