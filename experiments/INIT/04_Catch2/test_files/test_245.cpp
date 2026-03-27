// File: exception_message_matcher_test_245.cpp

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

// Catch2 matcher under test
#include <catch2/matchers/catch_matchers_exception.hpp>

using Catch::Matchers::Message;
using Catch::Matchers::ExceptionMessageMatcher;

namespace {

TEST(ExceptionMessageMatcherTest_245, MatchesExactMessage_245) {
    std::runtime_error ex("boom");
    auto matcher = Message("boom");
    EXPECT_TRUE(matcher.match(ex));
}

TEST(ExceptionMessageMatcherTest_245, DoesNotMatchDifferentMessage_245) {
    std::runtime_error ex("boom");
    auto matcher = Message("kaboom");
    EXPECT_FALSE(matcher.match(ex));
}

TEST(ExceptionMessageMatcherTest_245, MatchesEmptyString_245) {
    std::runtime_error ex("");
    auto matcher = Message("");
    EXPECT_TRUE(matcher.match(ex));
}

TEST(ExceptionMessageMatcherTest_245, EmptyExpectedDoesNotMatchNonEmpty_245) {
    std::runtime_error ex("not empty");
    auto matcher = Message("");
    EXPECT_FALSE(matcher.match(ex));
}

TEST(ExceptionMessageMatcherTest_245, SupportsUnicodeUtf8_245) {
    const std::string msg = u8"안녕🙂";
    std::runtime_error ex(msg);
    auto matcher = Message(msg);
    EXPECT_TRUE(matcher.match(ex));
}

TEST(ExceptionMessageMatcherTest_245, DescribeContainsExpectedMessage_245) {
    auto matcher = Message("needle text");
    const std::string desc = matcher.describe();
    // Do not assert on full formatting; only that the expected message appears.
    EXPECT_NE(desc.find("needle text"), std::string::npos);
}

TEST(ExceptionMessageMatcherTest_245, CopyConstructionPreservesBehavior_245) {
    std::runtime_error ex("copy me");
    auto original = Message("copy me");
    ExceptionMessageMatcher copy = original;  // copy-construct
    EXPECT_TRUE(copy.match(ex));
}

TEST(ExceptionMessageMatcherTest_245, MoveConstructionPreservesBehavior_245) {
    std::runtime_error ex("move me");
    auto temp = Message("move me");
    ExceptionMessageMatcher moved = std::move(temp);  // move-construct
    EXPECT_TRUE(moved.match(ex));
}

} // namespace
