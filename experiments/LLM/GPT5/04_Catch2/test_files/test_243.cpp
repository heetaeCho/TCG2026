// File: exception_message_matcher_test_243.cpp

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

// Include the matcher interface as provided by the codebase
#include "catch2/matchers/catch_matchers_exception.hpp"

using Catch::Matchers::ExceptionMessageMatcher;

//
// Test suite: ExceptionMessageMatcherTest_243
// Each test name includes the TEST_ID suffix `_243` per the requirement.
//

// Normal operation: exact match should return true.
TEST(ExceptionMessageMatcherTest_243, MatchExactMessage_243) {
    const std::string msg = "exact error";
    ExceptionMessageMatcher matcher(msg);

    std::runtime_error ex(msg);
    EXPECT_TRUE(matcher.match(ex));
}

// Normal operation: different message should return false.
TEST(ExceptionMessageMatcherTest_243, MismatchDifferentMessage_243) {
    ExceptionMessageMatcher matcher("expected message");

    std::runtime_error ex("actual message");
    EXPECT_FALSE(matcher.match(ex));
}

// Boundary: empty message should match an exception with empty what().
TEST(ExceptionMessageMatcherTest_243, EmptyMessageMatchesEmptyException_243) {
    ExceptionMessageMatcher matcher("");

    std::runtime_error ex("");
    EXPECT_TRUE(matcher.match(ex));
}

// Boundary: special characters and whitespace should be compared exactly.
TEST(ExceptionMessageMatcherTest_243, SpecialCharactersMatch_243) {
    const std::string special = "line1\nline2\t\u2603  spaces  ";
    ExceptionMessageMatcher matcher(special);

    std::runtime_error ex(special);
    EXPECT_TRUE(matcher.match(ex));

    // Off-by-one space should fail
    std::runtime_error ex_diff("line1\nline2\t\u2603  spaces ");
    EXPECT_FALSE(matcher.match(ex_diff));
}

// Type variance: works with different std::exception-derived types via base ref.
TEST(ExceptionMessageMatcherTest_243, DifferentExceptionTypeStillMatchesByWhat_243) {
    ExceptionMessageMatcher matcher("logic boom");

    std::logic_error ex("logic boom");
    EXPECT_TRUE(matcher.match(ex));

    std::invalid_argument ex2("not this");
    EXPECT_FALSE(matcher.match(ex2));
}

// Case sensitivity: comparisons should be exact (no case folding).
TEST(ExceptionMessageMatcherTest_243, CaseSensitivity_243) {
    ExceptionMessageMatcher matcher("Network Error");

    std::runtime_error ex_lower("network error");
    EXPECT_FALSE(matcher.match(ex_lower));

    std::runtime_error ex_exact("Network Error");
    EXPECT_TRUE(matcher.match(ex_exact));
}

// Long message: handles long strings (no truncation/partial compare).
TEST(ExceptionMessageMatcherTest_243, LongMessage_243) {
    std::string long_msg(4096, 'A'); // 4KB of 'A'
    ExceptionMessageMatcher matcher(long_msg);

    std::runtime_error ex_same(long_msg);
    EXPECT_TRUE(matcher.match(ex_same));

    std::string long_msg_off = long_msg + "B";
    std::runtime_error ex_diff(long_msg_off);
    EXPECT_FALSE(matcher.match(ex_diff));
}
