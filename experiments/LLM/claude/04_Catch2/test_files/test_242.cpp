#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <stdexcept>
#include <string>

// We need to use Catch2's own test framework since this is a Catch2 component.
// However, the requirement says to use Google Test. We'll write GTest tests
// that exercise the Catch2 matcher interface.

#include <gtest/gtest.h>

using namespace Catch::Matchers;

class MessageMatchesTest_242 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to check if a matcher matches an exception
template<typename MatcherType>
bool matcherMatches(const std::exception& ex, const MatcherType& matcher) {
    return matcher.match(ex);
}

// Test: MessageMatches with ContainsSubstring matches exception containing the substring
TEST_F(MessageMatchesTest_242, MatchesExceptionWithContainsSubstring_242) {
    auto matcher = MessageMatches(Catch::Matchers::ContainsSubstring("test error"));
    std::runtime_error ex("this is a test error message");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: MessageMatches with ContainsSubstring does not match when substring is absent
TEST_F(MessageMatchesTest_242, DoesNotMatchWhenSubstringAbsent_242) {
    auto matcher = MessageMatches(Catch::Matchers::ContainsSubstring("missing"));
    std::runtime_error ex("this is a test error message");
    EXPECT_FALSE(matcher.match(ex));
}

// Test: MessageMatches with exact string match using Equals
TEST_F(MessageMatchesTest_242, MatchesExactExceptionMessage_242) {
    auto matcher = MessageMatches(Catch::Matchers::Equals("exact message"));
    std::runtime_error ex("exact message");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: MessageMatches with Equals does not match different message
TEST_F(MessageMatchesTest_242, DoesNotMatchDifferentExactMessage_242) {
    auto matcher = MessageMatches(Catch::Matchers::Equals("exact message"));
    std::runtime_error ex("different message");
    EXPECT_FALSE(matcher.match(ex));
}

// Test: MessageMatches with empty exception message
TEST_F(MessageMatchesTest_242, MatchesEmptyExceptionMessage_242) {
    auto matcher = MessageMatches(Catch::Matchers::Equals(""));
    std::runtime_error ex("");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: MessageMatches with empty matcher on non-empty message
TEST_F(MessageMatchesTest_242, EmptyEqualsDoesNotMatchNonEmptyMessage_242) {
    auto matcher = MessageMatches(Catch::Matchers::Equals(""));
    std::runtime_error ex("non-empty");
    EXPECT_FALSE(matcher.match(ex));
}

// Test: MessageMatches with StartsWith matcher
TEST_F(MessageMatchesTest_242, MatchesWithStartsWith_242) {
    auto matcher = MessageMatches(Catch::Matchers::StartsWith("Error:"));
    std::runtime_error ex("Error: something went wrong");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: MessageMatches with StartsWith matcher does not match
TEST_F(MessageMatchesTest_242, DoesNotMatchWithStartsWith_242) {
    auto matcher = MessageMatches(Catch::Matchers::StartsWith("Error:"));
    std::runtime_error ex("Warning: something went wrong");
    EXPECT_FALSE(matcher.match(ex));
}

// Test: MessageMatches with EndsWith matcher
TEST_F(MessageMatchesTest_242, MatchesWithEndsWith_242) {
    auto matcher = MessageMatches(Catch::Matchers::EndsWith("went wrong"));
    std::runtime_error ex("something went wrong");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: MessageMatches works with std::logic_error (another std::exception subclass)
TEST_F(MessageMatchesTest_242, MatchesLogicError_242) {
    auto matcher = MessageMatches(Catch::Matchers::ContainsSubstring("logic"));
    std::logic_error ex("logic failure");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: MessageMatches has a describe method that returns non-empty string
TEST_F(MessageMatchesTest_242, DescribeReturnsNonEmptyString_242) {
    auto matcher = MessageMatches(Catch::Matchers::ContainsSubstring("test"));
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test: MessageMatches with case-insensitive ContainsSubstring
TEST_F(MessageMatchesTest_242, MatchesCaseInsensitiveSubstring_242) {
    auto matcher = MessageMatches(Catch::Matchers::ContainsSubstring("TEST", Catch::CaseSensitive::No));
    std::runtime_error ex("this is a test message");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: MessageMatches with case-sensitive ContainsSubstring fails on wrong case
TEST_F(MessageMatchesTest_242, DoesNotMatchCaseSensitiveSubstring_242) {
    auto matcher = MessageMatches(Catch::Matchers::ContainsSubstring("TEST", Catch::CaseSensitive::Yes));
    std::runtime_error ex("this is a test message");
    EXPECT_FALSE(matcher.match(ex));
}

// Test: MessageMatches with very long exception message
TEST_F(MessageMatchesTest_242, MatchesLongExceptionMessage_242) {
    std::string longMsg(10000, 'a');
    longMsg += "needle";
    auto matcher = MessageMatches(Catch::Matchers::ContainsSubstring("needle"));
    std::runtime_error ex(longMsg.c_str());
    EXPECT_TRUE(matcher.match(ex));
}

// Test: MessageMatches with special characters in message
TEST_F(MessageMatchesTest_242, MatchesSpecialCharactersInMessage_242) {
    auto matcher = MessageMatches(Catch::Matchers::ContainsSubstring("special\n\ttab"));
    std::runtime_error ex("some special\n\ttab characters");
    EXPECT_TRUE(matcher.match(ex));
}
