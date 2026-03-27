// File: matchers_operator_or_tests_146.cpp
#include <gtest/gtest.h>
#include <catch2/matchers/catch_matchers.hpp>

using namespace Catch::Matchers;

// Minimal custom matchers using only the public MatcherBase<T> interface
struct IsEvenMatcher : MatcherBase<int> {
    bool match(int const& v) const override { return v % 2 == 0; }
    std::string describe() const override { return "is even"; }
};

struct IsPositiveMatcher : MatcherBase<int> {
    bool match(int const& v) const override { return v > 0; }
    std::string describe() const override { return "is positive"; }
};

struct IsZeroMatcher : MatcherBase<int> {
    bool match(int const& v) const override { return v == 0; }
    std::string describe() const override { return "is zero"; }
};

// ---- Type property (compile-time) -----------------------------------------

// Ensures operator|| returns MatchAnyOf<T>, without relying on implementation details
static_assert(std::is_same<
    Detail::MatchAnyOf<int>,
    decltype(std::declval<const MatcherBase<int>&>() || std::declval<const MatcherBase<int>&>())
>::value, "operator|| must return Detail::MatchAnyOf<T>");

// ---- Tests ----------------------------------------------------------------

TEST(MatchersOperatorOrTest_146, MatchesWhenEitherOperandMatches_146) {
    IsEvenMatcher isEven;
    IsPositiveMatcher isPositive;

    auto anyOf = isEven || isPositive;

    // Observable behavior: combined matcher should accept values matched by either operand
    EXPECT_TRUE(anyOf.match(2));   // even
    EXPECT_TRUE(anyOf.match(3));   // positive
    EXPECT_FALSE(anyOf.match(-3)); // neither even nor positive
}

TEST(MatchersOperatorOrTest_146, MatchesWhenRightOperandMatches_146) {
    IsZeroMatcher isZero;
    IsPositiveMatcher isPositive;

    auto anyOf = isZero || isPositive;

    EXPECT_TRUE(anyOf.match(0));   // zero
    EXPECT_TRUE(anyOf.match(5));   // positive
    EXPECT_FALSE(anyOf.match(-4)); // neither zero nor positive
}

TEST(MatchersOperatorOrTest_146, DoesNotMatchWhenBothOperandsDoNotMatch_146) {
    IsZeroMatcher isZero;
    IsPositiveMatcher isPositive;

    auto anyOf = isZero || isPositive;

    EXPECT_FALSE(anyOf.match(-1)); // not zero, not positive
    EXPECT_FALSE(anyOf.match(-2)); // not zero, not positive
}

TEST(MatchersOperatorOrTest_146, SupportsChainingWithMultipleOperands_146) {
    IsEvenMatcher isEven;
    IsPositiveMatcher isPositive;
    IsZeroMatcher isZero;

    // (even || positive) || zero
    auto lhsAssoc = (isEven || isPositive) || isZero;
    // even || (positive || zero)
    auto rhsAssoc = isEven || (isPositive || isZero);

    // Check a variety of values; observable behavior for both chained results should match
    for (int v : {-3, -2, 0, 1, 2, 3}) {
        bool lhs = lhsAssoc.match(v);
        bool rhs = rhsAssoc.match(v);
        EXPECT_EQ(lhs, rhs) << "Associativity mismatch for value " << v;

        // Spot-check expected truth table for clarity
        if (v == -3)      { EXPECT_FALSE(lhs); }
        else if (v == -2) { EXPECT_TRUE(lhs); }  // even
        else if (v == 0)  { EXPECT_TRUE(lhs); }  // zero
        else if (v > 0)   { EXPECT_TRUE(lhs); }  // positive
    }
}

TEST(MatchersOperatorOrTest_146, DescriptionMentionsBothOperands_146) {
    IsEvenMatcher isEven;
    IsPositiveMatcher isPositive;

    auto anyOf = isEven || isPositive;
    const std::string desc = anyOf.describe();

    // We do not assert on exact formatting; only that both operand descriptions are present.
    EXPECT_NE(desc.find("is even"), std::string::npos);
    EXPECT_NE(desc.find("is positive"), std::string::npos);
}

