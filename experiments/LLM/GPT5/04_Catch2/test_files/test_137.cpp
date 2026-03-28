// File: match_all_of_and_operator_tests_137.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

using Catch::Matchers::MatcherBase;
using Catch::Matchers::Detail::MatchAllOf;

// A mock matcher for int that lets us verify interactions.
class MockIntMatcher : public MatcherBase<int> {
public:
    MOCK_METHOD(bool, match, (int const&), (const, override));
    MOCK_METHOD(std::string, describe, (), (const, override));
};

// ---------- Tests ----------

// Verifies that chaining via operator&& stores both rhs matchers and
// that calling match() on the combined matcher invokes both submatchers
// with the provided argument.
// Also verifies the overall result when all submatchers return true.
TEST(MatchAllOfAndOperatorTest_137, CallsAllSubmatchersAndAllTrueYieldsTrue_137) {
    StrictMock<MockIntMatcher> m1;
    StrictMock<MockIntMatcher> m2;

    EXPECT_CALL(m1, match(123)).WillOnce(Return(true));
    EXPECT_CALL(m2, match(123)).WillOnce(Return(true));

    // Build via rvalue chaining: MatchAllOf<int>() && m1 && m2
    auto combined = MatchAllOf<int>() && m1 && m2;

    // Observable behavior: both matchers are consulted with the same arg.
    EXPECT_TRUE(combined.match(123));
}

// Verifies that the composed matcher yields false if any submatcher yields false.
// This tests observable AND semantics without peeking into internals.
TEST(MatchAllOfAndOperatorTest_137, AnyFalseYieldsFalse_137) {
    StrictMock<MockIntMatcher> mTrue;
    StrictMock<MockIntMatcher> mFalse;

    EXPECT_CALL(mTrue, match(42)).WillOnce(Return(true));
    EXPECT_CALL(mFalse, match(42)).WillOnce(Return(false));

    auto combined = MatchAllOf<int>() && mTrue && mFalse;

    EXPECT_FALSE(combined.match(42));
}

// Verifies that chaining is possible across multiple operator&& applications
// and that all submatchers participate in matching.
TEST(MatchAllOfAndOperatorTest_137, SupportsChainingMultipleMatchers_137) {
    StrictMock<MockIntMatcher> m1;
    StrictMock<MockIntMatcher> m2;
    StrictMock<MockIntMatcher> m3;

    EXPECT_CALL(m1, match(7)).WillOnce(Return(true));
    EXPECT_CALL(m2, match(7)).WillOnce(Return(true));
    EXPECT_CALL(m3, match(7)).WillOnce(Return(true));

    auto combined = MatchAllOf<int>() && m1 && m2 && m3;

    EXPECT_TRUE(combined.match(7));
}

// Verifies that describe() of the composed matcher contains the submatchers' descriptions.
// We only assert presence of the substrings (not formatting), to avoid relying
// on internal formatting details.
TEST(MatchAllOfAndOperatorTest_137, DescribeContainsSubmatcherDescriptions_137) {
    StrictMock<MockIntMatcher> mA;
    StrictMock<MockIntMatcher> mB;

    EXPECT_CALL(mA, match(_)).WillOnce(Return(true));
    EXPECT_CALL(mB, match(_)).WillOnce(Return(true));

    EXPECT_CALL(mA, describe()).WillRepeatedly(Return("is A"));
    EXPECT_CALL(mB, describe()).WillRepeatedly(Return("is B"));

    auto combined = MatchAllOf<int>() && mA && mB;

    // Trigger describe after a match to avoid making assumptions about when
    // descriptions are generated/used. (Description content is independent of arg.)
    (void)combined.match(1);

    const std::string desc = combined.describe();
    EXPECT_NE(desc.find("is A"), std::string::npos);
    EXPECT_NE(desc.find("is B"), std::string::npos);
}

// Verifies that operator&& accepts an rvalue MatchAllOf (moved) and remains usable.
// This ensures the returned rvalue can be stored and used for later matching.
TEST(MatchAllOfAndOperatorTest_137, AcceptsRvalueAndRemainsUsableAfterMove_137) {
    StrictMock<MockIntMatcher> m1;
    StrictMock<MockIntMatcher> m2;

    EXPECT_CALL(m1, match(5)).WillOnce(Return(true));
    EXPECT_CALL(m2, match(5)).WillOnce(Return(true));

    MatchAllOf<int> base;
    auto combined = std::move(base) && m1 && m2;  // explicit move into operator&&

    EXPECT_TRUE(combined.match(5));
}
