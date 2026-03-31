#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Include the Catch2 matchers header under test
#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// We need to create some simple generic matchers for testing purposes.
// A generic matcher in Catch2 is one that has a `match` template or 
// a `match` method, and a `describe` method, but does NOT inherit from
// Catch::Matchers::MatcherBase (which would make it non-generic).

// Simple always-true generic matcher
struct AlwaysTrueMatcher {
    bool match(int const& val) const { return true; }
    bool match(std::string const& val) const { return true; }
    std::string describe() const { return "is always true"; }
};

// Simple always-false generic matcher
struct AlwaysFalseMatcher {
    bool match(int const& val) const { return false; }
    bool match(std::string const& val) const { return false; }
    std::string describe() const { return "is always false"; }
};

// Matcher that checks if value equals a specific int
struct EqualsIntMatcher {
    int expected;
    bool match(int const& val) const { return val == expected; }
    std::string describe() const { return "equals " + std::to_string(expected); }
};

// Matcher that checks if value is positive
struct IsPositiveMatcher {
    bool match(int const& val) const { return val > 0; }
    std::string describe() const { return "is positive"; }
};

// Matcher that checks if value is even
struct IsEvenMatcher {
    bool match(int const& val) const { return val % 2 == 0; }
    std::string describe() const { return "is even"; }
};

// Matcher that checks if value is negative
struct IsNegativeMatcher {
    bool match(int const& val) const { return val < 0; }
    std::string describe() const { return "is negative"; }
};

// Test fixture
class MatchAnyOfGenericTest_170 : public ::testing::Test {
protected:
    AlwaysTrueMatcher alwaysTrue;
    AlwaysFalseMatcher alwaysFalse;
    EqualsIntMatcher equals5{5};
    EqualsIntMatcher equals10{10};
    IsPositiveMatcher isPositive;
    IsEvenMatcher isEven;
    IsNegativeMatcher isNegative;
};

// Test: operator|| returns a combined matcher type (compiles and is usable)
TEST_F(MatchAnyOfGenericTest_170, OperatorOrReturnsCombinedMatcher_170) {
    auto combined = alwaysTrue || alwaysFalse;
    // The combined matcher should be usable with match
    EXPECT_TRUE(combined.match(42));
}

// Test: true || false => true
TEST_F(MatchAnyOfGenericTest_170, TrueOrFalseMatchesTrue_170) {
    auto combined = alwaysTrue || alwaysFalse;
    EXPECT_TRUE(combined.match(0));
    EXPECT_TRUE(combined.match(100));
}

// Test: false || true => true
TEST_F(MatchAnyOfGenericTest_170, FalseOrTrueMatchesTrue_170) {
    auto combined = alwaysFalse || alwaysTrue;
    EXPECT_TRUE(combined.match(0));
    EXPECT_TRUE(combined.match(-5));
}

// Test: false || false => false
TEST_F(MatchAnyOfGenericTest_170, FalseOrFalseMatchesFalse_170) {
    auto combined = alwaysFalse || alwaysFalse;
    EXPECT_FALSE(combined.match(42));
    EXPECT_FALSE(combined.match(0));
}

// Test: true || true => true
TEST_F(MatchAnyOfGenericTest_170, TrueOrTrueMatchesTrue_170) {
    auto combined = alwaysTrue || alwaysTrue;
    EXPECT_TRUE(combined.match(42));
}

// Test: specific matchers - equals5 || equals10, test with 5
TEST_F(MatchAnyOfGenericTest_170, Equals5OrEquals10MatchesWith5_170) {
    auto combined = equals5 || equals10;
    EXPECT_TRUE(combined.match(5));
}

// Test: specific matchers - equals5 || equals10, test with 10
TEST_F(MatchAnyOfGenericTest_170, Equals5OrEquals10MatchesWith10_170) {
    auto combined = equals5 || equals10;
    EXPECT_TRUE(combined.match(10));
}

// Test: specific matchers - equals5 || equals10, test with 7 (neither)
TEST_F(MatchAnyOfGenericTest_170, Equals5OrEquals10DoesNotMatchWith7_170) {
    auto combined = equals5 || equals10;
    EXPECT_FALSE(combined.match(7));
}

// Test: chaining three matchers via operator||
TEST_F(MatchAnyOfGenericTest_170, ChainingThreeMatchers_170) {
    auto combined = equals5 || equals10 || isNegative;
    EXPECT_TRUE(combined.match(5));
    EXPECT_TRUE(combined.match(10));
    EXPECT_TRUE(combined.match(-3));
    EXPECT_FALSE(combined.match(7));
}

// Test: chaining four matchers
TEST_F(MatchAnyOfGenericTest_170, ChainingFourMatchers_170) {
    auto combined = equals5 || equals10 || isNegative || isEven;
    EXPECT_TRUE(combined.match(5));
    EXPECT_TRUE(combined.match(10));
    EXPECT_TRUE(combined.match(-3));
    EXPECT_TRUE(combined.match(4));  // even
    EXPECT_FALSE(combined.match(7)); // not 5, not 10, not negative, not even
}

// Test: boundary - value of 0 (not positive, is even, not negative)
TEST_F(MatchAnyOfGenericTest_170, BoundaryZeroValue_170) {
    auto combined = isPositive || isNegative;
    EXPECT_FALSE(combined.match(0)); // 0 is neither positive nor negative
}

// Test: boundary - value of 0 with even matcher
TEST_F(MatchAnyOfGenericTest_170, BoundaryZeroWithEvenMatcher_170) {
    auto combined = isPositive || isEven;
    EXPECT_TRUE(combined.match(0)); // 0 is even
}

// Test: describe method exists and returns a non-empty string
TEST_F(MatchAnyOfGenericTest_170, DescribeReturnsNonEmptyString_170) {
    auto combined = equals5 || equals10;
    std::string description = combined.describe();
    EXPECT_FALSE(description.empty());
}

// Test: describe for chained matchers returns a non-empty string
TEST_F(MatchAnyOfGenericTest_170, DescribeChainedReturnsNonEmptyString_170) {
    auto combined = equals5 || equals10 || isNegative;
    std::string description = combined.describe();
    EXPECT_FALSE(description.empty());
}

// Test: combined matcher with string type
TEST_F(MatchAnyOfGenericTest_170, CombinedMatcherWithStringType_170) {
    auto combined = alwaysTrue || alwaysFalse;
    std::string testStr = "hello";
    EXPECT_TRUE(combined.match(testStr));
}

// Test: both false matchers with string type
TEST_F(MatchAnyOfGenericTest_170, BothFalseMatchersWithStringType_170) {
    auto combined = alwaysFalse || alwaysFalse;
    std::string testStr = "hello";
    EXPECT_FALSE(combined.match(testStr));
}

// Test: isPositive || isEven - positive odd number
TEST_F(MatchAnyOfGenericTest_170, PositiveOddMatchesPositiveOrEven_170) {
    auto combined = isPositive || isEven;
    EXPECT_TRUE(combined.match(3)); // positive but odd
}

// Test: isPositive || isEven - negative even number
TEST_F(MatchAnyOfGenericTest_170, NegativeEvenMatchesPositiveOrEven_170) {
    auto combined = isPositive || isEven;
    EXPECT_TRUE(combined.match(-4)); // not positive but even
}

// Test: isPositive || isEven - negative odd number (should fail)
TEST_F(MatchAnyOfGenericTest_170, NegativeOddDoesNotMatchPositiveOrEven_170) {
    auto combined = isPositive || isEven;
    EXPECT_FALSE(combined.match(-3)); // not positive and not even
}

// Test: Large boundary values
TEST_F(MatchAnyOfGenericTest_170, LargeBoundaryValues_170) {
    auto combined = isPositive || isEven;
    EXPECT_TRUE(combined.match(INT_MAX));  // positive
    EXPECT_TRUE(combined.match(INT_MIN));  // even (INT_MIN is even)
}

// Test: equals matcher with exact boundary
TEST_F(MatchAnyOfGenericTest_170, EqualsMatcherExactBoundary_170) {
    EqualsIntMatcher equalsZero{0};
    auto combined = equalsZero || isPositive;
    EXPECT_TRUE(combined.match(0));
    EXPECT_TRUE(combined.match(1));
    EXPECT_FALSE(combined.match(-1));
}
