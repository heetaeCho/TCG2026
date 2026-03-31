#include <gtest/gtest.h>
#include <string>

// Include necessary headers
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/catch_case_sensitive.hpp"

using namespace Catch::Matchers;
using namespace Catch;

// Test describe() method with case sensitive option
TEST(RegexMatcherTest_224, DescribeCaseSensitive_224) {
    RegexMatcher matcher("hello.*world", CaseSensitive::Yes);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("hello.*world"), std::string::npos);
    EXPECT_NE(description.find("case sensitively"), std::string::npos);
}

// Test describe() method with case insensitive option
TEST(RegexMatcherTest_224, DescribeCaseInsensitive_224) {
    RegexMatcher matcher("hello.*world", CaseSensitive::No);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("hello.*world"), std::string::npos);
    EXPECT_NE(description.find("case insensitively"), std::string::npos);
}

// Test describe() starts with "matches "
TEST(RegexMatcherTest_224, DescribeStartsWithMatches_224) {
    RegexMatcher matcher("test", CaseSensitive::Yes);
    std::string description = matcher.describe();
    EXPECT_EQ(description.substr(0, 8), "matches ");
}

// Test match() with a simple regex that should match
TEST(RegexMatcherTest_224, MatchSimpleRegexSuccess_224) {
    RegexMatcher matcher("hello", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("hello"));
}

// Test match() with a simple regex that should not match
TEST(RegexMatcherTest_224, MatchSimpleRegexFailure_224) {
    RegexMatcher matcher("hello", CaseSensitive::Yes);
    EXPECT_FALSE(matcher.match("world"));
}

// Test match() with case insensitive matching
TEST(RegexMatcherTest_224, MatchCaseInsensitive_224) {
    RegexMatcher matcher("hello", CaseSensitive::No);
    EXPECT_TRUE(matcher.match("HELLO"));
}

// Test match() with case sensitive matching where case doesn't match
TEST(RegexMatcherTest_224, MatchCaseSensitiveMismatch_224) {
    RegexMatcher matcher("hello", CaseSensitive::Yes);
    EXPECT_FALSE(matcher.match("HELLO"));
}

// Test match() with regex wildcard pattern
TEST(RegexMatcherTest_224, MatchWildcardPattern_224) {
    RegexMatcher matcher("hel.*rld", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("hello world"));
}

// Test match() with empty string and empty regex
TEST(RegexMatcherTest_224, MatchEmptyStringEmptyRegex_224) {
    RegexMatcher matcher("", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match(""));
}

// Test match() with empty regex against non-empty string
TEST(RegexMatcherTest_224, MatchEmptyRegexNonEmptyString_224) {
    RegexMatcher matcher("", CaseSensitive::Yes);
    // Empty regex should match (it matches empty substring)
    EXPECT_TRUE(matcher.match("hello"));
}

// Test match() with regex character classes
TEST(RegexMatcherTest_224, MatchCharacterClass_224) {
    RegexMatcher matcher("[0-9]+", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("12345"));
}

// Test match() with regex character classes that don't match
TEST(RegexMatcherTest_224, MatchCharacterClassFailure_224) {
    RegexMatcher matcher("^[0-9]+$", CaseSensitive::Yes);
    EXPECT_FALSE(matcher.match("abc"));
}

// Test match() with anchored regex
TEST(RegexMatcherTest_224, MatchAnchoredRegex_224) {
    RegexMatcher matcher("^hello$", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("hello"));
    EXPECT_FALSE(matcher.match("hello world"));
}

// Test describe() with special characters in regex
TEST(RegexMatcherTest_224, DescribeSpecialCharactersInRegex_224) {
    RegexMatcher matcher("[a-z]+\\d{3}", CaseSensitive::Yes);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("[a-z]+\\d{3}"), std::string::npos);
    EXPECT_NE(description.find("case sensitively"), std::string::npos);
}

// Test match() with case insensitive and mixed case input
TEST(RegexMatcherTest_224, MatchCaseInsensitiveMixedCase_224) {
    RegexMatcher matcher("hello", CaseSensitive::No);
    EXPECT_TRUE(matcher.match("HeLlO"));
}

// Test match() partial match behavior
TEST(RegexMatcherTest_224, MatchPartialMatch_224) {
    RegexMatcher matcher("hello", CaseSensitive::Yes);
    // "hello world" contains "hello" so regex search should find it
    EXPECT_TRUE(matcher.match("hello world"));
}

// Test describe() does not contain case insensitively when case sensitive
TEST(RegexMatcherTest_224, DescribeDoesNotContainInsensitivelyWhenSensitive_224) {
    RegexMatcher matcher("test", CaseSensitive::Yes);
    std::string description = matcher.describe();
    EXPECT_EQ(description.find("case insensitively"), std::string::npos);
}

// Test describe() does not contain case sensitively when case insensitive
TEST(RegexMatcherTest_224, DescribeDoesNotContainSensitivelyWhenInsensitive_224) {
    RegexMatcher matcher("test", CaseSensitive::No);
    std::string description = matcher.describe();
    EXPECT_EQ(description.find("case sensitively"), std::string::npos);
}
