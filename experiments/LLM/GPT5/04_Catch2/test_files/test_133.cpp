// MatchExpr_streamReconstructedExpression_test_133.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <limits>

// Include the class under test (path mirrors the provided snippet)
#include "catch2/matchers/internal/catch_matchers_impl.hpp"

using ::testing::Return;

// Minimal mock for the matcher dependency passed into MatchExpr.
// We only verify observable interaction: that toString() is invoked.
class MockMatcher {
public:
    MOCK_METHOD(std::string, toString, (), (const));
};

class MatchExprTest_133 : public ::testing::Test {};

// [Normal] Prints "stringify(arg) + ' ' + matcher.toString()"
TEST(MatchExprTest_133, StreamsIntAndMatcherString_133) {
    int value = 42;
    MockMatcher matcher;
    EXPECT_CALL(matcher, toString())
        .Times(1)
        .WillOnce(Return("is even"));

    Catch::MatchExpr<int&, MockMatcher> expr(value, matcher);

    std::ostringstream os;
    expr.streamReconstructedExpression(os);

    EXPECT_EQ(os.str(), "42 is even");
}

// [Interaction] Ensures matcher.toString() is called exactly once
TEST(MatchExprTest_133, CallsMatcherToStringOnce_133) {
    int value = -5;
    MockMatcher matcher;
    EXPECT_CALL(matcher, toString())
        .Times(1)
        .WillOnce(Return("is negative"));

    Catch::MatchExpr<int&, MockMatcher> expr(value, matcher);

    std::ostringstream os;
    expr.streamReconstructedExpression(os);
    EXPECT_EQ(os.str(), "-5 is negative");
}

// [Boundary] Large integer value (checks stringify of boundary-sized arg)
TEST(MatchExprTest_133, HandlesLargeIntegerArg_133) {
    int value = std::numeric_limits<int>::max();
    MockMatcher matcher;
    EXPECT_CALL(matcher, toString())
        .Times(1)
        .WillOnce(Return("ok"));

    Catch::MatchExpr<int&, MockMatcher> expr(value, matcher);

    std::ostringstream os;
    expr.streamReconstructedExpression(os);
    EXPECT_EQ(os.str(), std::to_string(std::numeric_limits<int>::max()) + " ok");
}

// [Behavior] Appends to existing stream content without clearing it
TEST(MatchExprTest_133, PreservesAndAppendsToExistingStreamContent_133) {
    int value = 7;
    MockMatcher matcher;
    EXPECT_CALL(matcher, toString())
        .Times(1)
        .WillOnce(Return("units"));

    Catch::MatchExpr<int&, MockMatcher> expr(value, matcher);

    std::ostringstream os;
    os << "prefix:";
    expr.streamReconstructedExpression(os);

    EXPECT_EQ(os.str(), "prefix:7 units");
}

// [Boundary] Empty matcher string — still prints space between parts
TEST(MatchExprTest_133, HandlesEmptyMatcherString_133) {
    int value = 0;
    MockMatcher matcher;
    EXPECT_CALL(matcher, toString())
        .Times(1)
        .WillOnce(Return(""));

    Catch::MatchExpr<int&, MockMatcher> expr(value, matcher);

    std::ostringstream os;
    expr.streamReconstructedExpression(os);

    // Expected: stringify(0) + ' ' + ""  => "0 "
    EXPECT_EQ(os.str(), "0 ");
}
