#include <gtest/gtest.h>
#include "catch2/matchers/catch_matchers_string.hpp"

using namespace Catch::Matchers;

// Helper to check if a matcher matches a given string
static bool matches(const StringContainsMatcher& matcher, const std::string& str) {
    return matcher.match(str);
}

// ==================== Normal Operation Tests ====================

TEST(ContainsSubstringTest_226, MatchesWhenSubstringPresent_226) {
    auto matcher = ContainsSubstring("hello");
    EXPECT_TRUE(matches(matcher, "say hello world"));
}

TEST(ContainsSubstringTest_226, MatchesExactString_226) {
    auto matcher = ContainsSubstring("hello");
    EXPECT_TRUE(matches(matcher, "hello"));
}

TEST(ContainsSubstringTest_226, DoesNotMatchWhenSubstringAbsent_226) {
    auto matcher = ContainsSubstring("hello");
    EXPECT_FALSE(matches(matcher, "world"));
}

TEST(ContainsSubstringTest_226, MatchesAtBeginning_226) {
    auto matcher = ContainsSubstring("hello");
    EXPECT_TRUE(matches(matcher, "hello world"));
}

TEST(ContainsSubstringTest_226, MatchesAtEnd_226) {
    auto matcher = ContainsSubstring("world");
    EXPECT_TRUE(matches(matcher, "hello world"));
}

// ==================== Case Sensitivity Tests ====================

TEST(ContainsSubstringTest_226, CaseSensitiveMatchSucceeds_226) {
    auto matcher = ContainsSubstring("Hello", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(matches(matcher, "Hello World"));
}

TEST(ContainsSubstringTest_226, CaseSensitiveMatchFails_226) {
    auto matcher = ContainsSubstring("Hello", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(matches(matcher, "hello world"));
}

TEST(ContainsSubstringTest_226, CaseInsensitiveMatchSucceeds_226) {
    auto matcher = ContainsSubstring("hello", Catch::CaseSensitive::No);
    EXPECT_TRUE(matches(matcher, "HELLO WORLD"));
}

TEST(ContainsSubstringTest_226, CaseInsensitiveMatchMixedCase_226) {
    auto matcher = ContainsSubstring("HeLLo", Catch::CaseSensitive::No);
    EXPECT_TRUE(matches(matcher, "hElLo WoRlD"));
}

TEST(ContainsSubstringTest_226, CaseInsensitiveNoMatch_226) {
    auto matcher = ContainsSubstring("xyz", Catch::CaseSensitive::No);
    EXPECT_FALSE(matches(matcher, "HELLO WORLD"));
}

// ==================== Boundary Conditions ====================

TEST(ContainsSubstringTest_226, EmptySubstringMatchesAnyString_226) {
    auto matcher = ContainsSubstring("");
    EXPECT_TRUE(matches(matcher, "anything"));
}

TEST(ContainsSubstringTest_226, EmptySubstringMatchesEmptyString_226) {
    auto matcher = ContainsSubstring("");
    EXPECT_TRUE(matches(matcher, ""));
}

TEST(ContainsSubstringTest_226, NonEmptySubstringDoesNotMatchEmptyString_226) {
    auto matcher = ContainsSubstring("hello");
    EXPECT_FALSE(matches(matcher, ""));
}

TEST(ContainsSubstringTest_226, SubstringLongerThanTarget_226) {
    auto matcher = ContainsSubstring("hello world this is long");
    EXPECT_FALSE(matches(matcher, "hello"));
}

TEST(ContainsSubstringTest_226, SingleCharacterSubstringMatch_226) {
    auto matcher = ContainsSubstring("a");
    EXPECT_TRUE(matches(matcher, "abc"));
}

TEST(ContainsSubstringTest_226, SingleCharacterSubstringNoMatch_226) {
    auto matcher = ContainsSubstring("z");
    EXPECT_FALSE(matches(matcher, "abc"));
}

TEST(ContainsSubstringTest_226, SpecialCharacters_226) {
    auto matcher = ContainsSubstring("!@#$");
    EXPECT_TRUE(matches(matcher, "test!@#$test"));
}

TEST(ContainsSubstringTest_226, SpacesInSubstring_226) {
    auto matcher = ContainsSubstring("hello world");
    EXPECT_TRUE(matches(matcher, "say hello world now"));
}

TEST(ContainsSubstringTest_226, NewlineInSubstring_226) {
    auto matcher = ContainsSubstring("line1\nline2");
    EXPECT_TRUE(matches(matcher, "line1\nline2"));
}

TEST(ContainsSubstringTest_226, RepeatedSubstring_226) {
    auto matcher = ContainsSubstring("aa");
    EXPECT_TRUE(matches(matcher, "aaa"));
}

// ==================== Default Case Sensitivity ====================

TEST(ContainsSubstringTest_226, DefaultCaseSensitivityIsCaseSensitive_226) {
    // Default should be case sensitive
    auto matcher = ContainsSubstring("Hello");
    EXPECT_FALSE(matches(matcher, "hello"));
    EXPECT_TRUE(matches(matcher, "Hello"));
}

// ==================== Description Tests ====================

TEST(ContainsSubstringTest_226, DescribeReturnsNonEmptyString_226) {
    auto matcher = ContainsSubstring("hello");
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

TEST(ContainsSubstringTest_226, DescribeContainsSearchedString_226) {
    auto matcher = ContainsSubstring("needle");
    std::string description = matcher.describe();
    EXPECT_NE(description.find("needle"), std::string::npos);
}
