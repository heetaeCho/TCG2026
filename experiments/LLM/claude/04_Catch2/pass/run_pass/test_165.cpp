#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/matchers/catch_matchers_predicate.hpp"

// We need to include Catch2 headers for the matcher infrastructure
#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_all.hpp"

#include <string>
#include <type_traits>

// Custom matcher for testing purposes
struct AlwaysTrueMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const&) const { return true; }
    std::string describe() const override { return "is always true"; }
};

struct AlwaysFalseMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const&) const { return false; }
    std::string describe() const override { return "is always false"; }
};

struct IsEvenMatcher : Catch::Matchers::MatcherGenericBase {
    bool match(int val) const { return val % 2 == 0; }
    std::string describe() const override { return "is even"; }
};

struct IsPositiveMatcher : Catch::Matchers::MatcherGenericBase {
    bool match(int val) const { return val > 0; }
    std::string describe() const override { return "is positive"; }
};

struct IsNegativeMatcher : Catch::Matchers::MatcherGenericBase {
    bool match(int val) const { return val < 0; }
    std::string describe() const override { return "is negative"; }
};

struct GreaterThanMatcher : Catch::Matchers::MatcherGenericBase {
    int threshold;
    explicit GreaterThanMatcher(int t) : threshold(t) {}
    bool match(int val) const { return val > threshold; }
    std::string describe() const override { return "is greater than " + std::to_string(threshold); }
};

struct LessThanMatcher : Catch::Matchers::MatcherGenericBase {
    int threshold;
    explicit LessThanMatcher(int t) : threshold(t) {}
    bool match(int val) const { return val < threshold; }
    std::string describe() const override { return "is less than " + std::to_string(threshold); }
};

struct StringContainsMatcher : Catch::Matchers::MatcherGenericBase {
    std::string substr;
    explicit StringContainsMatcher(std::string s) : substr(std::move(s)) {}
    bool match(std::string const& val) const { return val.find(substr) != std::string::npos; }
    std::string describe() const override { return "contains \"" + substr + "\""; }
};

// Test fixture
class MatchAnyOfGenericTest_165 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Basic OR of two matchers where first matches
TEST_F(MatchAnyOfGenericTest_165, FirstMatcherMatchesReturnsTrue_165) {
    AlwaysTrueMatcher trueMatcher;
    AlwaysFalseMatcher falseMatcher;
    auto combined = trueMatcher || falseMatcher;
    EXPECT_TRUE(combined.match(42));
}

// Test: Basic OR of two matchers where second matches
TEST_F(MatchAnyOfGenericTest_165, SecondMatcherMatchesReturnsTrue_165) {
    AlwaysFalseMatcher falseMatcher;
    AlwaysTrueMatcher trueMatcher;
    auto combined = falseMatcher || trueMatcher;
    EXPECT_TRUE(combined.match(42));
}

// Test: Both matchers match
TEST_F(MatchAnyOfGenericTest_165, BothMatchersMatchReturnsTrue_165) {
    AlwaysTrueMatcher trueMatcher1;
    AlwaysTrueMatcher trueMatcher2;
    auto combined = trueMatcher1 || trueMatcher2;
    EXPECT_TRUE(combined.match(42));
}

// Test: Neither matcher matches
TEST_F(MatchAnyOfGenericTest_165, NeitherMatcherMatchesReturnsFalse_165) {
    AlwaysFalseMatcher falseMatcher1;
    AlwaysFalseMatcher falseMatcher2;
    auto combined = falseMatcher1 || falseMatcher2;
    EXPECT_FALSE(combined.match(42));
}

// Test: Chaining three matchers with OR (left associative)
TEST_F(MatchAnyOfGenericTest_165, ThreeMatchersChainingLastMatchesReturnsTrue_165) {
    AlwaysFalseMatcher falseMatcher1;
    AlwaysFalseMatcher falseMatcher2;
    AlwaysTrueMatcher trueMatcher;
    auto combined = falseMatcher1 || falseMatcher2 || trueMatcher;
    EXPECT_TRUE(combined.match(42));
}

// Test: Chaining three matchers with OR, none matches
TEST_F(MatchAnyOfGenericTest_165, ThreeMatchersChainingNoneMatchesReturnsFalse_165) {
    AlwaysFalseMatcher falseMatcher1;
    AlwaysFalseMatcher falseMatcher2;
    AlwaysFalseMatcher falseMatcher3;
    auto combined = falseMatcher1 || falseMatcher2 || falseMatcher3;
    EXPECT_FALSE(combined.match(42));
}

// Test: OR with integer-specific matchers where value is even but not positive
TEST_F(MatchAnyOfGenericTest_165, IsEvenOrIsPositiveWithNegativeEvenValue_165) {
    IsEvenMatcher isEven;
    IsPositiveMatcher isPositive;
    auto combined = isEven || isPositive;
    EXPECT_TRUE(combined.match(-2)); // -2 is even, so should match
}

// Test: OR with integer-specific matchers where value is positive but not even
TEST_F(MatchAnyOfGenericTest_165, IsEvenOrIsPositiveWithOddPositiveValue_165) {
    IsEvenMatcher isEven;
    IsPositiveMatcher isPositive;
    auto combined = isEven || isPositive;
    EXPECT_TRUE(combined.match(3)); // 3 is positive, so should match
}

// Test: OR with integer-specific matchers where neither matches
TEST_F(MatchAnyOfGenericTest_165, IsEvenOrIsPositiveWithOddNegativeValue_165) {
    IsEvenMatcher isEven;
    IsPositiveMatcher isPositive;
    auto combined = isEven || isPositive;
    EXPECT_FALSE(combined.match(-3)); // -3 is neither even nor positive
}

// Test: OR with integer-specific matchers where both match
TEST_F(MatchAnyOfGenericTest_165, IsEvenOrIsPositiveWithEvenPositiveValue_165) {
    IsEvenMatcher isEven;
    IsPositiveMatcher isPositive;
    auto combined = isEven || isPositive;
    EXPECT_TRUE(combined.match(4)); // 4 is even and positive
}

// Test: LHS matcher combined with existing MatchAnyOfGeneric via operator||
TEST_F(MatchAnyOfGenericTest_165, LHSMatcherCombinedWithMatchAnyOfGeneric_165) {
    IsNegativeMatcher isNegative;
    IsEvenMatcher isEven;
    IsPositiveMatcher isPositive;
    // (isEven || isPositive) creates MatchAnyOfGeneric, then isNegative || that
    auto rightCombined = isEven || isPositive;
    auto combined = isNegative || std::move(rightCombined);
    EXPECT_TRUE(combined.match(-3)); // -3 is negative
    EXPECT_TRUE(combined.match(2));  // 2 is even and positive
    EXPECT_FALSE(combined.match(0)); // 0 is even, so matches
}

// Test: Zero value boundary
TEST_F(MatchAnyOfGenericTest_165, BoundaryZeroValue_165) {
    IsEvenMatcher isEven;
    IsPositiveMatcher isPositive;
    auto combined = isEven || isPositive;
    EXPECT_TRUE(combined.match(0)); // 0 is even
}

// Test: describe() returns a non-empty string
TEST_F(MatchAnyOfGenericTest_165, DescribeReturnsNonEmptyString_165) {
    IsEvenMatcher isEven;
    IsPositiveMatcher isPositive;
    auto combined = isEven || isPositive;
    std::string description = combined.describe();
    EXPECT_FALSE(description.empty());
}

// Test: describe() contains descriptions of constituent matchers
TEST_F(MatchAnyOfGenericTest_165, DescribeContainsConstituentDescriptions_165) {
    IsEvenMatcher isEven;
    IsPositiveMatcher isPositive;
    auto combined = isEven || isPositive;
    std::string description = combined.describe();
    // The description should contain info about both matchers
    EXPECT_NE(description.find("even"), std::string::npos);
    EXPECT_NE(description.find("positive"), std::string::npos);
}

// Test: String matcher OR combination
TEST_F(MatchAnyOfGenericTest_165, StringMatchersCombination_165) {
    StringContainsMatcher containsHello("hello");
    StringContainsMatcher containsWorld("world");
    auto combined = containsHello || containsWorld;
    EXPECT_TRUE(combined.match(std::string("hello there")));
    EXPECT_TRUE(combined.match(std::string("brave world")));
    EXPECT_TRUE(combined.match(std::string("hello world")));
    EXPECT_FALSE(combined.match(std::string("goodbye")));
}

// Test: Chaining four matchers
TEST_F(MatchAnyOfGenericTest_165, FourMatchersChained_165) {
    GreaterThanMatcher gt10(10);
    LessThanMatcher lt0(0);
    IsEvenMatcher isEven;
    AlwaysFalseMatcher alwaysFalse;
    auto combined = gt10 || lt0 || isEven || alwaysFalse;
    EXPECT_TRUE(combined.match(15));  // > 10
    EXPECT_TRUE(combined.match(-5));  // < 0
    EXPECT_TRUE(combined.match(4));   // even
    EXPECT_FALSE(combined.match(3));  // 3 is not > 10, not < 0, not even
}

// Test: Match with boundary values for GreaterThan
TEST_F(MatchAnyOfGenericTest_165, BoundaryGreaterThanOrLessThan_165) {
    GreaterThanMatcher gt0(0);
    LessThanMatcher lt0(0);
    auto combined = gt0 || lt0;
    EXPECT_TRUE(combined.match(1));
    EXPECT_TRUE(combined.match(-1));
    EXPECT_FALSE(combined.match(0)); // 0 is neither > 0 nor < 0
}

// Test: MatchAnyOfGeneric is move constructible
TEST_F(MatchAnyOfGenericTest_165, MoveConstructible_165) {
    IsEvenMatcher isEven;
    IsPositiveMatcher isPositive;
    auto combined = isEven || isPositive;
    auto moved = std::move(combined);
    EXPECT_TRUE(moved.match(2));
    EXPECT_FALSE(moved.match(-3));
}

// Test: Single match value that satisfies only the last in a chain
TEST_F(MatchAnyOfGenericTest_165, OnlyLastMatcherInChainMatches_165) {
    AlwaysFalseMatcher f1;
    AlwaysFalseMatcher f2;
    AlwaysFalseMatcher f3;
    AlwaysTrueMatcher t1;
    auto combined = f1 || f2 || f3 || t1;
    EXPECT_TRUE(combined.match(42));
}

// Test: Single match value that satisfies only the first in a chain
TEST_F(MatchAnyOfGenericTest_165, OnlyFirstMatcherInChainMatches_165) {
    AlwaysTrueMatcher t1;
    AlwaysFalseMatcher f1;
    AlwaysFalseMatcher f2;
    AlwaysFalseMatcher f3;
    auto combined = t1 || f1 || f2 || f3;
    EXPECT_TRUE(combined.match(42));
}

// Test: Describe with three matchers
TEST_F(MatchAnyOfGenericTest_165, DescribeWithThreeMatchers_165) {
    IsEvenMatcher isEven;
    IsPositiveMatcher isPositive;
    IsNegativeMatcher isNegative;
    auto combined = isEven || isPositive || isNegative;
    std::string description = combined.describe();
    EXPECT_FALSE(description.empty());
    EXPECT_NE(description.find("even"), std::string::npos);
    EXPECT_NE(description.find("positive"), std::string::npos);
    EXPECT_NE(description.find("negative"), std::string::npos);
}
