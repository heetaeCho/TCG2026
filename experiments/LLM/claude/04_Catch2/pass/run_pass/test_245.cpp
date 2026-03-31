#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

#include "catch2/matchers/catch_matchers_exception.hpp"

class ExceptionMessageMatcherTest_245 : public ::testing::Test {
protected:
    // Helper to check if matcher matches a given exception
    bool matchesException(const Catch::Matchers::ExceptionMessageMatcher& matcher, const std::exception& ex) {
        return matcher.match(ex);
    }
};

// Test that Message factory function creates a valid matcher
TEST_F(ExceptionMessageMatcherTest_245, MessageFactoryCreatesMatcherSuccessfully_245) {
    auto matcher = Catch::Matchers::Message("test error");
    // Should not throw, just verify creation
    SUCCEED();
}

// Test matching an exception with the exact same message
TEST_F(ExceptionMessageMatcherTest_245, MatchesExactExceptionMessage_245) {
    auto matcher = Catch::Matchers::Message("something went wrong");
    std::runtime_error ex("something went wrong");
    EXPECT_TRUE(matchesException(matcher, ex));
}

// Test that a different message does not match
TEST_F(ExceptionMessageMatcherTest_245, DoesNotMatchDifferentMessage_245) {
    auto matcher = Catch::Matchers::Message("expected message");
    std::runtime_error ex("different message");
    EXPECT_FALSE(matchesException(matcher, ex));
}

// Test matching an empty exception message
TEST_F(ExceptionMessageMatcherTest_245, MatchesEmptyMessage_245) {
    auto matcher = Catch::Matchers::Message("");
    std::runtime_error ex("");
    EXPECT_TRUE(matchesException(matcher, ex));
}

// Test that empty matcher does not match non-empty exception message
TEST_F(ExceptionMessageMatcherTest_245, EmptyMatcherDoesNotMatchNonEmptyMessage_245) {
    auto matcher = Catch::Matchers::Message("");
    std::runtime_error ex("not empty");
    EXPECT_FALSE(matchesException(matcher, ex));
}

// Test that non-empty matcher does not match empty exception message
TEST_F(ExceptionMessageMatcherTest_245, NonEmptyMatcherDoesNotMatchEmptyMessage_245) {
    auto matcher = Catch::Matchers::Message("some message");
    std::runtime_error ex("");
    EXPECT_FALSE(matchesException(matcher, ex));
}

// Test matching with std::logic_error (another std::exception subclass)
TEST_F(ExceptionMessageMatcherTest_245, MatchesLogicErrorMessage_245) {
    auto matcher = Catch::Matchers::Message("logic error occurred");
    std::logic_error ex("logic error occurred");
    EXPECT_TRUE(matchesException(matcher, ex));
}

// Test matching with std::invalid_argument
TEST_F(ExceptionMessageMatcherTest_245, MatchesInvalidArgumentMessage_245) {
    auto matcher = Catch::Matchers::Message("invalid arg");
    std::invalid_argument ex("invalid arg");
    EXPECT_TRUE(matchesException(matcher, ex));
}

// Test that partial message does not match (substring)
TEST_F(ExceptionMessageMatcherTest_245, PartialMessageDoesNotMatch_245) {
    auto matcher = Catch::Matchers::Message("partial");
    std::runtime_error ex("partial message here");
    EXPECT_FALSE(matchesException(matcher, ex));
}

// Test that message with extra whitespace does not match
TEST_F(ExceptionMessageMatcherTest_245, MessageWithExtraWhitespaceDoesNotMatch_245) {
    auto matcher = Catch::Matchers::Message("hello world");
    std::runtime_error ex("hello  world");
    EXPECT_FALSE(matchesException(matcher, ex));
}

// Test matching message with special characters
TEST_F(ExceptionMessageMatcherTest_245, MatchesMessageWithSpecialCharacters_245) {
    auto matcher = Catch::Matchers::Message("error: file not found! @#$%");
    std::runtime_error ex("error: file not found! @#$%");
    EXPECT_TRUE(matchesException(matcher, ex));
}

// Test that the matcher has a describe method (returns a non-empty string)
TEST_F(ExceptionMessageMatcherTest_245, DescribeReturnsNonEmptyString_245) {
    auto matcher = Catch::Matchers::Message("test message");
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test that describe contains the expected message
TEST_F(ExceptionMessageMatcherTest_245, DescribeContainsExpectedMessage_245) {
    auto matcher = Catch::Matchers::Message("specific error text");
    std::string description = matcher.describe();
    EXPECT_NE(description.find("specific error text"), std::string::npos);
}

// Test case sensitivity
TEST_F(ExceptionMessageMatcherTest_245, MatchIsCaseSensitive_245) {
    auto matcher = Catch::Matchers::Message("Error");
    std::runtime_error ex("error");
    EXPECT_FALSE(matchesException(matcher, ex));
}
