#include <gtest/gtest.h>
#include <string>
#include <sstream>

// Include Catch2 matcher headers
#include "catch2/matchers/catch_matchers.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/matchers/catch_matchers_predicate.hpp"
#include "catch2/matchers/catch_matchers_contains.hpp"

// We need to include enough of Catch2 to use matchers
// If specific headers aren't available, we define simple test matchers

namespace {

// A simple custom matcher for testing purposes
template <typename T>
class EqualsMatcher : public Catch::Matchers::MatcherBase<T> {
    T m_value;
public:
    explicit EqualsMatcher(T value) : m_value(std::move(value)) {}
    
    bool match(T const& other) const override {
        return m_value == other;
    }
    
    std::string describe() const override {
        std::ostringstream oss;
        oss << "equals " << m_value;
        return oss.str();
    }
};

template <typename T>
class GreaterThanMatcher : public Catch::Matchers::MatcherBase<T> {
    T m_value;
public:
    explicit GreaterThanMatcher(T value) : m_value(std::move(value)) {}
    
    bool match(T const& other) const override {
        return other > m_value;
    }
    
    std::string describe() const override {
        std::ostringstream oss;
        oss << "is greater than " << m_value;
        return oss.str();
    }
};

template <typename T>
class LessThanMatcher : public Catch::Matchers::MatcherBase<T> {
    T m_value;
public:
    explicit LessThanMatcher(T value) : m_value(std::move(value)) {}
    
    bool match(T const& other) const override {
        return other < m_value;
    }
    
    std::string describe() const override {
        std::ostringstream oss;
        oss << "is less than " << m_value;
        return oss.str();
    }
};

class MatchAnyOfOperatorTest_146 : public ::testing::Test {
protected:
};

// Test that operator|| with two matchers where first matches
TEST_F(MatchAnyOfOperatorTest_146, FirstMatcherMatches_146) {
    EqualsMatcher<int> lhs(42);
    EqualsMatcher<int> rhs(100);
    
    auto combined = lhs || rhs;
    EXPECT_TRUE(combined.match(42));
}

// Test that operator|| with two matchers where second matches
TEST_F(MatchAnyOfOperatorTest_146, SecondMatcherMatches_146) {
    EqualsMatcher<int> lhs(42);
    EqualsMatcher<int> rhs(100);
    
    auto combined = lhs || rhs;
    EXPECT_TRUE(combined.match(100));
}

// Test that operator|| with two matchers where neither matches
TEST_F(MatchAnyOfOperatorTest_146, NeitherMatcherMatches_146) {
    EqualsMatcher<int> lhs(42);
    EqualsMatcher<int> rhs(100);
    
    auto combined = lhs || rhs;
    EXPECT_FALSE(combined.match(50));
}

// Test that operator|| with two matchers where both match
TEST_F(MatchAnyOfOperatorTest_146, BothMatchersMatch_146) {
    GreaterThanMatcher<int> lhs(10);
    LessThanMatcher<int> rhs(100);
    
    auto combined = lhs || rhs;
    // 50 is greater than 10 AND less than 100 - both match, so || should be true
    EXPECT_TRUE(combined.match(50));
}

// Test chaining three matchers with operator||
TEST_F(MatchAnyOfOperatorTest_146, ChainingThreeMatchers_146) {
    EqualsMatcher<int> a(1);
    EqualsMatcher<int> b(2);
    EqualsMatcher<int> c(3);
    
    auto combined = a || b || c;
    EXPECT_TRUE(combined.match(1));
    EXPECT_TRUE(combined.match(2));
    EXPECT_TRUE(combined.match(3));
    EXPECT_FALSE(combined.match(4));
}

// Test with string type matchers
TEST_F(MatchAnyOfOperatorTest_146, StringMatchers_146) {
    EqualsMatcher<std::string> lhs("hello");
    EqualsMatcher<std::string> rhs("world");
    
    auto combined = lhs || rhs;
    EXPECT_TRUE(combined.match(std::string("hello")));
    EXPECT_TRUE(combined.match(std::string("world")));
    EXPECT_FALSE(combined.match(std::string("foo")));
}

// Test describe() produces a meaningful description
TEST_F(MatchAnyOfOperatorTest_146, DescribeContainsBothDescriptions_146) {
    EqualsMatcher<int> lhs(42);
    EqualsMatcher<int> rhs(100);
    
    auto combined = lhs || rhs;
    std::string description = combined.describe();
    
    // The description should mention both sub-matchers
    EXPECT_FALSE(description.empty());
    EXPECT_NE(description.find("42"), std::string::npos);
    EXPECT_NE(description.find("100"), std::string::npos);
}

// Test with double type
TEST_F(MatchAnyOfOperatorTest_146, DoubleTypeMatchers_146) {
    EqualsMatcher<double> lhs(3.14);
    EqualsMatcher<double> rhs(2.72);
    
    auto combined = lhs || rhs;
    EXPECT_TRUE(combined.match(3.14));
    EXPECT_TRUE(combined.match(2.72));
    EXPECT_FALSE(combined.match(1.0));
}

// Test boundary: value at exact boundary of greater than matcher
TEST_F(MatchAnyOfOperatorTest_146, BoundaryConditionExactValue_146) {
    GreaterThanMatcher<int> lhs(10);
    EqualsMatcher<int> rhs(10);
    
    auto combined = lhs || rhs;
    // 10 is not greater than 10, but equals 10
    EXPECT_TRUE(combined.match(10));
    // 11 is greater than 10
    EXPECT_TRUE(combined.match(11));
    // 9 is neither greater than 10 nor equal to 10
    EXPECT_FALSE(combined.match(9));
}

// Test chaining four matchers
TEST_F(MatchAnyOfOperatorTest_146, ChainingFourMatchers_146) {
    EqualsMatcher<int> a(10);
    EqualsMatcher<int> b(20);
    EqualsMatcher<int> c(30);
    EqualsMatcher<int> d(40);
    
    auto combined = a || b || c || d;
    EXPECT_TRUE(combined.match(10));
    EXPECT_TRUE(combined.match(20));
    EXPECT_TRUE(combined.match(30));
    EXPECT_TRUE(combined.match(40));
    EXPECT_FALSE(combined.match(50));
}

// Test with negative values
TEST_F(MatchAnyOfOperatorTest_146, NegativeValues_146) {
    EqualsMatcher<int> lhs(-1);
    EqualsMatcher<int> rhs(-2);
    
    auto combined = lhs || rhs;
    EXPECT_TRUE(combined.match(-1));
    EXPECT_TRUE(combined.match(-2));
    EXPECT_FALSE(combined.match(0));
    EXPECT_FALSE(combined.match(1));
}

// Test with empty string
TEST_F(MatchAnyOfOperatorTest_146, EmptyStringMatcher_146) {
    EqualsMatcher<std::string> lhs("");
    EqualsMatcher<std::string> rhs("notempty");
    
    auto combined = lhs || rhs;
    EXPECT_TRUE(combined.match(std::string("")));
    EXPECT_TRUE(combined.match(std::string("notempty")));
    EXPECT_FALSE(combined.match(std::string("other")));
}

} // anonymous namespace
