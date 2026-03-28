#include <gtest/gtest.h>
#include <string>
#include <type_traits>

#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// A simple custom matcher for testing purposes
struct AlwaysTrueMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T&&) const { return true; }
    std::string describe() const override { return "always true"; }
};

struct AlwaysFalseMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T&&) const { return false; }
    std::string describe() const override { return "always false"; }
};

struct IsPositiveMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T&& val) const { return val > 0; }
    std::string describe() const override { return "is positive"; }
};

struct IsEvenMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T&& val) const { return static_cast<int>(val) % 2 == 0; }
    std::string describe() const override { return "is even"; }
};

struct IsLessThan100Matcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T&& val) const { return val < 100; }
    std::string describe() const override { return "is less than 100"; }
};

struct StringContainsMatcher : Catch::Matchers::MatcherGenericBase {
    std::string m_substr;
    explicit StringContainsMatcher(std::string s) : m_substr(std::move(s)) {}
    bool match(const std::string& val) const { return val.find(m_substr) != std::string::npos; }
    std::string describe() const override { return "contains \"" + m_substr + "\""; }
};

class MatchAllOfGenericTest_160 : public ::testing::Test {
protected:
    AlwaysTrueMatcher alwaysTrue;
    AlwaysFalseMatcher alwaysFalse;
    IsPositiveMatcher isPositive;
    IsEvenMatcher isEven;
    IsLessThan100Matcher isLessThan100;
};

// Test: Single matcher in MatchAllOfGeneric matches correctly
TEST_F(MatchAllOfGenericTest_160, SingleMatcherTrue_160) {
    auto combined = alwaysTrue && alwaysTrue;
    EXPECT_TRUE(combined.match(42));
}

// Test: Two matchers both true yields true
TEST_F(MatchAllOfGenericTest_160, TwoMatchersBothTrue_160) {
    auto combined = isPositive && isEven;
    EXPECT_TRUE(combined.match(4));
}

// Test: Two matchers, first false yields false
TEST_F(MatchAllOfGenericTest_160, TwoMatchersFirstFalse_160) {
    auto combined = isPositive && isEven;
    EXPECT_FALSE(combined.match(-2));
}

// Test: Two matchers, second false yields false
TEST_F(MatchAllOfGenericTest_160, TwoMatchersSecondFalse_160) {
    auto combined = isPositive && isEven;
    EXPECT_FALSE(combined.match(3));
}

// Test: Two matchers both false yields false
TEST_F(MatchAllOfGenericTest_160, TwoMatchersBothFalse_160) {
    auto combined = isPositive && isEven;
    EXPECT_FALSE(combined.match(-3));
}

// Test: Chaining three matchers with operator&& - all true
TEST_F(MatchAllOfGenericTest_160, ThreeMatchersAllTrue_160) {
    auto combined = isPositive && isEven && isLessThan100;
    EXPECT_TRUE(combined.match(42));
}

// Test: Chaining three matchers with operator&& - last false
TEST_F(MatchAllOfGenericTest_160, ThreeMatchersLastFalse_160) {
    auto combined = isPositive && isEven && isLessThan100;
    EXPECT_FALSE(combined.match(200));
}

// Test: AlwaysFalse combined with AlwaysTrue is false
TEST_F(MatchAllOfGenericTest_160, AlwaysFalseAndAlwaysTrue_160) {
    auto combined = alwaysFalse && alwaysTrue;
    EXPECT_FALSE(combined.match(42));
}

// Test: AlwaysTrue combined with AlwaysFalse is false
TEST_F(MatchAllOfGenericTest_160, AlwaysTrueAndAlwaysFalse_160) {
    auto combined = alwaysTrue && alwaysFalse;
    EXPECT_FALSE(combined.match(42));
}

// Test: describe returns a non-empty string
TEST_F(MatchAllOfGenericTest_160, DescribeIsNonEmpty_160) {
    auto combined = isPositive && isEven;
    std::string desc = combined.describe();
    EXPECT_FALSE(desc.empty());
}

// Test: describe for chained matchers returns a non-empty string
TEST_F(MatchAllOfGenericTest_160, DescribeChainedIsNonEmpty_160) {
    auto combined = isPositive && isEven && isLessThan100;
    std::string desc = combined.describe();
    EXPECT_FALSE(desc.empty());
}

// Test: describe contains component descriptions
TEST_F(MatchAllOfGenericTest_160, DescribeContainsComponentDescriptions_160) {
    auto combined = isPositive && isEven;
    std::string desc = combined.describe();
    EXPECT_NE(desc.find("is positive"), std::string::npos);
    EXPECT_NE(desc.find("is even"), std::string::npos);
}

// Test: Boundary value - zero is not positive but is even
TEST_F(MatchAllOfGenericTest_160, BoundaryZero_160) {
    auto combined = isPositive && isEven;
    EXPECT_FALSE(combined.match(0));
}

// Test: Boundary value - 1 is positive but not even
TEST_F(MatchAllOfGenericTest_160, BoundaryOne_160) {
    auto combined = isPositive && isEven;
    EXPECT_FALSE(combined.match(1));
}

// Test: Boundary value - 2 is positive and even
TEST_F(MatchAllOfGenericTest_160, BoundaryTwo_160) {
    auto combined = isPositive && isEven;
    EXPECT_TRUE(combined.match(2));
}

// Test: Matching with string type
TEST_F(MatchAllOfGenericTest_160, StringMatchers_160) {
    StringContainsMatcher containsHello("hello");
    StringContainsMatcher containsWorld("world");
    auto combined = containsHello && containsWorld;
    EXPECT_TRUE(combined.match(std::string("hello world")));
    EXPECT_FALSE(combined.match(std::string("hello")));
    EXPECT_FALSE(combined.match(std::string("world")));
    EXPECT_FALSE(combined.match(std::string("goodbye")));
}

// Test: MatchAllOfGeneric is move-constructible
TEST_F(MatchAllOfGenericTest_160, MoveConstructible_160) {
    auto combined = isPositive && isEven;
    auto moved = std::move(combined);
    EXPECT_TRUE(moved.match(4));
    EXPECT_FALSE(moved.match(3));
}

// Test: operator&& with MatchAllOfGeneric on right (lhs && MatchAllOfGeneric rhs)
TEST_F(MatchAllOfGenericTest_160, LhsAndMatchAllOfGenericRhs_160) {
    auto rhs = isEven && isLessThan100;
    auto combined = isPositive && std::move(rhs);
    EXPECT_TRUE(combined.match(42));
    EXPECT_FALSE(combined.match(-2));
    EXPECT_FALSE(combined.match(3));
    EXPECT_FALSE(combined.match(200));
}

// Test: Large negative value
TEST_F(MatchAllOfGenericTest_160, LargeNegativeValue_160) {
    auto combined = isPositive && isEven;
    EXPECT_FALSE(combined.match(-1000000));
}

// Test: Large positive even value less than 100
TEST_F(MatchAllOfGenericTest_160, ValueAtBoundary99_160) {
    auto combined = isPositive && isLessThan100;
    EXPECT_TRUE(combined.match(99));
}

// Test: Value exactly at boundary 100
TEST_F(MatchAllOfGenericTest_160, ValueAtBoundary100_160) {
    auto combined = isPositive && isLessThan100;
    EXPECT_FALSE(combined.match(100));
}
