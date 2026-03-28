#include "catch2/matchers/catch_matchers.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/matchers/catch_matchers_predicate.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_templated.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace Catch::Matchers;

// A simple custom matcher for testing
template <typename T>
class EqualsMatcher : public Catch::Matchers::MatcherBase<T> {
    T m_value;
public:
    explicit EqualsMatcher(T value) : m_value(std::move(value)) {}
    bool match(T const& arg) const override {
        return arg == m_value;
    }
    std::string describe() const override {
        return "equals custom value";
    }
};

template <typename T>
EqualsMatcher<T> EqualsCustom(T value) {
    return EqualsMatcher<T>(std::move(value));
}

class MatchAnyOfTest_141 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that combining two matchers with || produces a MatchAnyOf that matches when first matcher matches
TEST_F(MatchAnyOfTest_141, MatchesWhenFirstMatcherMatches_141) {
    auto m1 = EqualsCustom<int>(42);
    auto m2 = EqualsCustom<int>(99);
    
    auto combined = m1 || m2;
    
    EXPECT_TRUE(combined.match(42));
}

// Test that combining two matchers with || matches when second matcher matches
TEST_F(MatchAnyOfTest_141, MatchesWhenSecondMatcherMatches_141) {
    auto m1 = EqualsCustom<int>(42);
    auto m2 = EqualsCustom<int>(99);
    
    auto combined = m1 || m2;
    
    EXPECT_TRUE(combined.match(99));
}

// Test that combining two matchers with || does not match when neither matches
TEST_F(MatchAnyOfTest_141, DoesNotMatchWhenNeitherMatches_141) {
    auto m1 = EqualsCustom<int>(42);
    auto m2 = EqualsCustom<int>(99);
    
    auto combined = m1 || m2;
    
    EXPECT_FALSE(combined.match(0));
}

// Test chaining three matchers with ||
TEST_F(MatchAnyOfTest_141, ChainingThreeMatchers_141) {
    auto m1 = EqualsCustom<int>(1);
    auto m2 = EqualsCustom<int>(2);
    auto m3 = EqualsCustom<int>(3);
    
    auto combined = m1 || m2 || m3;
    
    EXPECT_TRUE(combined.match(1));
    EXPECT_TRUE(combined.match(2));
    EXPECT_TRUE(combined.match(3));
    EXPECT_FALSE(combined.match(4));
}

// Test that describe returns a non-empty string
TEST_F(MatchAnyOfTest_141, DescribeReturnsNonEmptyString_141) {
    auto m1 = EqualsCustom<int>(42);
    auto m2 = EqualsCustom<int>(99);
    
    auto combined = m1 || m2;
    
    std::string description = combined.describe();
    EXPECT_FALSE(description.empty());
}

// Test with string matchers
TEST_F(MatchAnyOfTest_141, WorksWithStringType_141) {
    auto m1 = EqualsCustom<std::string>("hello");
    auto m2 = EqualsCustom<std::string>("world");
    
    auto combined = m1 || m2;
    
    EXPECT_TRUE(combined.match("hello"));
    EXPECT_TRUE(combined.match("world"));
    EXPECT_FALSE(combined.match("foo"));
}

// Test that both matchers matching still returns true (OR semantics)
TEST_F(MatchAnyOfTest_141, BothMatchersMatchReturnsTrue_141) {
    auto m1 = EqualsCustom<int>(42);
    auto m2 = EqualsCustom<int>(42);
    
    auto combined = m1 || m2;
    
    EXPECT_TRUE(combined.match(42));
}

// Test with a single matcher chained (MatchAnyOf || MatcherBase)
TEST_F(MatchAnyOfTest_141, SingleMatcherInAnyOf_141) {
    auto m1 = EqualsCustom<int>(10);
    auto m2 = EqualsCustom<int>(20);
    
    // First || creates MatchAnyOf from two MatcherBase, then we add one more
    auto combined = m1 || m2;
    
    EXPECT_TRUE(combined.match(10));
    EXPECT_TRUE(combined.match(20));
    EXPECT_FALSE(combined.match(30));
}

// Test chaining many matchers
TEST_F(MatchAnyOfTest_141, ChainingManyMatchers_141) {
    auto m1 = EqualsCustom<int>(1);
    auto m2 = EqualsCustom<int>(2);
    auto m3 = EqualsCustom<int>(3);
    auto m4 = EqualsCustom<int>(4);
    auto m5 = EqualsCustom<int>(5);
    
    auto combined = m1 || m2 || m3 || m4 || m5;
    
    for (int i = 1; i <= 5; ++i) {
        EXPECT_TRUE(combined.match(i)) << "Should match " << i;
    }
    EXPECT_FALSE(combined.match(0));
    EXPECT_FALSE(combined.match(6));
}

// Test boundary: negative values
TEST_F(MatchAnyOfTest_141, BoundaryNegativeValues_141) {
    auto m1 = EqualsCustom<int>(-1);
    auto m2 = EqualsCustom<int>(0);
    
    auto combined = m1 || m2;
    
    EXPECT_TRUE(combined.match(-1));
    EXPECT_TRUE(combined.match(0));
    EXPECT_FALSE(combined.match(1));
}

// Test with double type
TEST_F(MatchAnyOfTest_141, WorksWithDoubleType_141) {
    auto m1 = EqualsCustom<double>(3.14);
    auto m2 = EqualsCustom<double>(2.72);
    
    auto combined = m1 || m2;
    
    EXPECT_TRUE(combined.match(3.14));
    EXPECT_TRUE(combined.match(2.72));
    EXPECT_FALSE(combined.match(1.0));
}
