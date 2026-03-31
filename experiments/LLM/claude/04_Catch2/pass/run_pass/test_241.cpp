#include <catch2/matchers/catch_matchers_exception.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

class ExceptionMessageMatchesMatcherTest_241 : public ::testing::Test {
protected:
};

// Test that describe() returns expected format with ContainsSubstring matcher
TEST_F(ExceptionMessageMatchesMatcherTest_241, DescribeContainsExpectedFormat_241) {
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::ContainsSubstring("test error"));
    std::string desc = matcher.describe();
    // describe should contain "matches" and the inner matcher's description
    EXPECT_NE(desc.find("matches"), std::string::npos);
    EXPECT_NE(desc.find("test error"), std::string::npos);
}

// Test that match returns true when exception message matches the string matcher
TEST_F(ExceptionMessageMatchesMatcherTest_241, MatchReturnsTrueForMatchingMessage_241) {
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::ContainsSubstring("hello"));
    std::runtime_error ex("hello world");
    EXPECT_TRUE(matcher.match(ex));
}

// Test that match returns false when exception message does not match
TEST_F(ExceptionMessageMatchesMatcherTest_241, MatchReturnsFalseForNonMatchingMessage_241) {
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::ContainsSubstring("goodbye"));
    std::runtime_error ex("hello world");
    EXPECT_FALSE(matcher.match(ex));
}

// Test with exact match using Equals
TEST_F(ExceptionMessageMatchesMatcherTest_241, MatchWithEqualsMatcherExact_241) {
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::Equals("exact message"));
    std::runtime_error ex("exact message");
    EXPECT_TRUE(matcher.match(ex));
}

// Test with Equals matcher that doesn't match
TEST_F(ExceptionMessageMatchesMatcherTest_241, MatchWithEqualsMatcherNoMatch_241) {
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::Equals("exact message"));
    std::runtime_error ex("different message");
    EXPECT_FALSE(matcher.match(ex));
}

// Test with empty exception message
TEST_F(ExceptionMessageMatchesMatcherTest_241, MatchWithEmptyExceptionMessage_241) {
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::ContainsSubstring("something"));
    std::runtime_error ex("");
    EXPECT_FALSE(matcher.match(ex));
}

// Test matching empty string in empty exception message
TEST_F(ExceptionMessageMatchesMatcherTest_241, MatchEmptySubstringInEmptyMessage_241) {
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::ContainsSubstring(""));
    std::runtime_error ex("");
    EXPECT_TRUE(matcher.match(ex));
}

// Test with StartsWith matcher
TEST_F(ExceptionMessageMatchesMatcherTest_241, MatchWithStartsWithMatcher_241) {
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::StartsWith("Error:"));
    std::runtime_error ex("Error: something went wrong");
    EXPECT_TRUE(matcher.match(ex));
}

// Test with EndsWith matcher
TEST_F(ExceptionMessageMatchesMatcherTest_241, MatchWithEndsWithMatcher_241) {
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::EndsWith("wrong"));
    std::runtime_error ex("something went wrong");
    EXPECT_TRUE(matcher.match(ex));
}

// Test with std::exception base class directly
TEST_F(ExceptionMessageMatchesMatcherTest_241, MatchWithBaseStdException_241) {
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::ContainsSubstring("logic"));
    std::logic_error ex("logic error occurred");
    EXPECT_TRUE(matcher.match(ex));
}

// Test describe includes quotes
TEST_F(ExceptionMessageMatchesMatcherTest_241, DescribeIncludesQuotes_241) {
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::ContainsSubstring("foo"));
    std::string desc = matcher.describe();
    // Should have a closing quote based on the implementation
    EXPECT_NE(desc.find('"'), std::string::npos);
}

// Test with case-sensitive matching (default behavior)
TEST_F(ExceptionMessageMatchesMatcherTest_241, CaseSensitiveMatchFails_241) {
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::Equals("Hello World"));
    std::runtime_error ex("hello world");
    EXPECT_FALSE(matcher.match(ex));
}

// Test with case-insensitive ContainsSubstring
TEST_F(ExceptionMessageMatchesMatcherTest_241, CaseInsensitiveMatch_241) {
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::ContainsSubstring("HELLO", Catch::CaseSensitive::No));
    std::runtime_error ex("hello world");
    EXPECT_TRUE(matcher.match(ex));
}

// Test with very long exception message
TEST_F(ExceptionMessageMatchesMatcherTest_241, MatchWithLongMessage_241) {
    std::string longMsg(10000, 'a');
    longMsg += "needle";
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::ContainsSubstring("needle"));
    std::runtime_error ex(longMsg.c_str());
    EXPECT_TRUE(matcher.match(ex));
}

// Test with special characters in exception message
TEST_F(ExceptionMessageMatchesMatcherTest_241, MatchWithSpecialCharacters_241) {
    auto matcher = Catch::Matchers::ExceptionMessageMatchesMatcher(
        Catch::Matchers::ContainsSubstring("line1\nline2"));
    std::runtime_error ex("line1\nline2\nline3");
    EXPECT_TRUE(matcher.match(ex));
}
