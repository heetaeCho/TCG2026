#include <gtest/gtest.h>
#include "catch2/matchers/catch_matchers_string.hpp"

using namespace Catch::Matchers;

// Helper function to check if a matcher matches a given string
bool matchesString(const EndsWithMatcher& matcher, const std::string& str) {
    return matcher.match(str);
}

// ============================================================
// Tests for EndsWith factory function
// ============================================================

TEST(EndsWithMatcherTest_227, ExactMatch_227) {
    auto matcher = EndsWith("hello");
    EXPECT_TRUE(matcher.match("hello"));
}

TEST(EndsWithMatcherTest_227, StringEndsWith_227) {
    auto matcher = EndsWith("world");
    EXPECT_TRUE(matcher.match("hello world"));
}

TEST(EndsWithMatcherTest_227, StringDoesNotEndWith_227) {
    auto matcher = EndsWith("hello");
    EXPECT_FALSE(matcher.match("hello world"));
}

TEST(EndsWithMatcherTest_227, EmptySuffix_227) {
    auto matcher = EndsWith("");
    EXPECT_TRUE(matcher.match("anything"));
}

TEST(EndsWithMatcherTest_227, EmptyStringEmptySuffix_227) {
    auto matcher = EndsWith("");
    EXPECT_TRUE(matcher.match(""));
}

TEST(EndsWithMatcherTest_227, EmptyStringNonEmptySuffix_227) {
    auto matcher = EndsWith("abc");
    EXPECT_FALSE(matcher.match(""));
}

TEST(EndsWithMatcherTest_227, SuffixLongerThanString_227) {
    auto matcher = EndsWith("longersuffix");
    EXPECT_FALSE(matcher.match("suffix"));
}

// ============================================================
// Case Sensitive tests (default behavior)
// ============================================================

TEST(EndsWithMatcherTest_227, CaseSensitiveByDefault_227) {
    auto matcher = EndsWith("World");
    EXPECT_FALSE(matcher.match("hello world"));
}

TEST(EndsWithMatcherTest_227, CaseSensitiveExplicit_227) {
    auto matcher = EndsWith("World", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(matcher.match("hello world"));
    EXPECT_TRUE(matcher.match("hello World"));
}

// ============================================================
// Case Insensitive tests
// ============================================================

TEST(EndsWithMatcherTest_227, CaseInsensitiveMatch_227) {
    auto matcher = EndsWith("WORLD", Catch::CaseSensitive::No);
    EXPECT_TRUE(matcher.match("hello world"));
}

TEST(EndsWithMatcherTest_227, CaseInsensitiveExactMatch_227) {
    auto matcher = EndsWith("HELLO", Catch::CaseSensitive::No);
    EXPECT_TRUE(matcher.match("hello"));
}

TEST(EndsWithMatcherTest_227, CaseInsensitiveNoMatch_227) {
    auto matcher = EndsWith("xyz", Catch::CaseSensitive::No);
    EXPECT_FALSE(matcher.match("hello world"));
}

TEST(EndsWithMatcherTest_227, CaseInsensitiveMixedCase_227) {
    auto matcher = EndsWith("WoRlD", Catch::CaseSensitive::No);
    EXPECT_TRUE(matcher.match("Hello WORLD"));
}

TEST(EndsWithMatcherTest_227, CaseInsensitiveEmptySuffix_227) {
    auto matcher = EndsWith("", Catch::CaseSensitive::No);
    EXPECT_TRUE(matcher.match("anything"));
}

TEST(EndsWithMatcherTest_227, CaseInsensitiveEmptyBoth_227) {
    auto matcher = EndsWith("", Catch::CaseSensitive::No);
    EXPECT_TRUE(matcher.match(""));
}

// ============================================================
// Describe method tests
// ============================================================

TEST(EndsWithMatcherTest_227, DescribeContainsSuffix_227) {
    auto matcher = EndsWith("suffix");
    std::string description = matcher.describe();
    EXPECT_NE(description.find("suffix"), std::string::npos);
}

TEST(EndsWithMatcherTest_227, DescribeCaseInsensitiveMentionsCasing_227) {
    auto matcher = EndsWith("suffix", Catch::CaseSensitive::No);
    std::string description = matcher.describe();
    // The description should mention something about case insensitivity
    // We just verify it contains the suffix string at minimum
    EXPECT_NE(description.find("suffix"), std::string::npos);
}

// ============================================================
// Special character tests
// ============================================================

TEST(EndsWithMatcherTest_227, EndsWithSpecialCharacters_227) {
    auto matcher = EndsWith("!@#$");
    EXPECT_TRUE(matcher.match("hello!@#$"));
    EXPECT_FALSE(matcher.match("hello!@#"));
}

TEST(EndsWithMatcherTest_227, EndsWithSpaces_227) {
    auto matcher = EndsWith("  ");
    EXPECT_TRUE(matcher.match("hello  "));
    EXPECT_FALSE(matcher.match("hello"));
}

TEST(EndsWithMatcherTest_227, EndsWithNewline_227) {
    auto matcher = EndsWith("\n");
    EXPECT_TRUE(matcher.match("hello\n"));
    EXPECT_FALSE(matcher.match("hello"));
}

// ============================================================
// Single character boundary tests
// ============================================================

TEST(EndsWithMatcherTest_227, SingleCharSuffix_227) {
    auto matcher = EndsWith("o");
    EXPECT_TRUE(matcher.match("hello"));
    EXPECT_FALSE(matcher.match("hell"));
}

TEST(EndsWithMatcherTest_227, SingleCharString_227) {
    auto matcher = EndsWith("a");
    EXPECT_TRUE(matcher.match("a"));
    EXPECT_FALSE(matcher.match("b"));
}

TEST(EndsWithMatcherTest_227, CaseInsensitiveSingleChar_227) {
    auto matcher = EndsWith("A", Catch::CaseSensitive::No);
    EXPECT_TRUE(matcher.match("a"));
    EXPECT_TRUE(matcher.match("A"));
    EXPECT_FALSE(matcher.match("b"));
}
