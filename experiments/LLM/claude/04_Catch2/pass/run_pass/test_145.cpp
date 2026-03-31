#include <gtest/gtest.h>
#include <string>

// Include Catch2 matcher headers
#include "catch2/matchers/catch_matchers.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/matchers/catch_matchers_predicate.hpp"
#include "catch2/matchers/catch_matchers_contains.hpp"
#include "catch2/matchers/catch_matchers_templated.hpp"

// We need to test the operator&& for MatcherBase<T>, which produces MatchAllOf<T>.
// Since we're treating the implementation as a black box, we test observable behavior:
// - That combining two matchers with && produces a combined matcher
// - That the combined matcher matches when both sub-matchers match
// - That the combined matcher fails when either sub-matcher fails
// - That the description of the combined matcher contains both sub-matcher descriptions

// A simple custom matcher for testing purposes
template <typename T>
class EqualsMatcher : public Catch::Matchers::MatcherBase<T> {
    T m_expected;
public:
    explicit EqualsMatcher(T expected) : m_expected(std::move(expected)) {}

    bool match(T const& actual) const override {
        return actual == m_expected;
    }

    std::string describe() const override {
        return "equals " + Catch::Detail::stringify(m_expected);
    }
};

template <typename T>
class GreaterThanMatcher : public Catch::Matchers::MatcherBase<T> {
    T m_threshold;
public:
    explicit GreaterThanMatcher(T threshold) : m_threshold(std::move(threshold)) {}

    bool match(T const& actual) const override {
        return actual > m_threshold;
    }

    std::string describe() const override {
        return "is greater than " + Catch::Detail::stringify(m_threshold);
    }
};

template <typename T>
class LessThanMatcher : public Catch::Matchers::MatcherBase<T> {
    T m_threshold;
public:
    explicit LessThanMatcher(T threshold) : m_threshold(std::move(threshold)) {}

    bool match(T const& actual) const override {
        return actual < m_threshold;
    }

    std::string describe() const override {
        return "is less than " + Catch::Detail::stringify(m_threshold);
    }
};

// Helper matcher that always matches
template <typename T>
class AlwaysTrueMatcher : public Catch::Matchers::MatcherBase<T> {
public:
    bool match(T const&) const override { return true; }
    std::string describe() const override { return "always true"; }
};

// Helper matcher that never matches
template <typename T>
class AlwaysFalseMatcher : public Catch::Matchers::MatcherBase<T> {
public:
    bool match(T const&) const override { return false; }
    std::string describe() const override { return "always false"; }
};

class MatchAllOfOperatorTest_145 : public ::testing::Test {
protected:
};

// Test that operator&& with two matching matchers produces a matcher that matches
TEST_F(MatchAllOfOperatorTest_145, BothMatchersMatch_ReturnsTrue_145) {
    GreaterThanMatcher<int> gt(0);
    LessThanMatcher<int> lt(10);

    auto combined = gt && lt;

    EXPECT_TRUE(combined.match(5));
}

// Test that operator&& fails when the left matcher fails
TEST_F(MatchAllOfOperatorTest_145, LeftMatcherFails_ReturnsFalse_145) {
    GreaterThanMatcher<int> gt(10);
    LessThanMatcher<int> lt(20);

    auto combined = gt && lt;

    EXPECT_FALSE(combined.match(5));
}

// Test that operator&& fails when the right matcher fails
TEST_F(MatchAllOfOperatorTest_145, RightMatcherFails_ReturnsFalse_145) {
    GreaterThanMatcher<int> gt(0);
    LessThanMatcher<int> lt(5);

    auto combined = gt && lt;

    EXPECT_FALSE(combined.match(10));
}

// Test that operator&& fails when both matchers fail
TEST_F(MatchAllOfOperatorTest_145, BothMatchersFail_ReturnsFalse_145) {
    GreaterThanMatcher<int> gt(100);
    LessThanMatcher<int> lt(0);

    auto combined = gt && lt;

    EXPECT_FALSE(combined.match(50));
}

// Test that the description of the combined matcher includes info from both matchers
TEST_F(MatchAllOfOperatorTest_145, DescriptionContainsBothMatchers_145) {
    GreaterThanMatcher<int> gt(0);
    LessThanMatcher<int> lt(10);

    auto combined = gt && lt;

    std::string desc = combined.describe();
    EXPECT_FALSE(desc.empty());
    // The description should mention both sub-matchers
    EXPECT_NE(desc.find("greater than"), std::string::npos);
    EXPECT_NE(desc.find("less than"), std::string::npos);
}

// Test combining AlwaysTrue && AlwaysTrue
TEST_F(MatchAllOfOperatorTest_145, TrueAndTrue_ReturnsTrue_145) {
    AlwaysTrueMatcher<int> t1;
    AlwaysTrueMatcher<int> t2;

    auto combined = t1 && t2;

    EXPECT_TRUE(combined.match(42));
}

// Test combining AlwaysTrue && AlwaysFalse
TEST_F(MatchAllOfOperatorTest_145, TrueAndFalse_ReturnsFalse_145) {
    AlwaysTrueMatcher<int> t;
    AlwaysFalseMatcher<int> f;

    auto combined = t && f;

    EXPECT_FALSE(combined.match(42));
}

// Test combining AlwaysFalse && AlwaysTrue
TEST_F(MatchAllOfOperatorTest_145, FalseAndTrue_ReturnsFalse_145) {
    AlwaysFalseMatcher<int> f;
    AlwaysTrueMatcher<int> t;

    auto combined = f && t;

    EXPECT_FALSE(combined.match(42));
}

// Test combining AlwaysFalse && AlwaysFalse
TEST_F(MatchAllOfOperatorTest_145, FalseAndFalse_ReturnsFalse_145) {
    AlwaysFalseMatcher<int> f1;
    AlwaysFalseMatcher<int> f2;

    auto combined = f1 && f2;

    EXPECT_FALSE(combined.match(42));
}

// Test chaining three matchers with &&
TEST_F(MatchAllOfOperatorTest_145, ChainingThreeMatchers_AllMatch_145) {
    GreaterThanMatcher<int> gt(0);
    LessThanMatcher<int> lt(100);
    GreaterThanMatcher<int> gt2(-10);

    // (gt && lt) && gt2  — first && produces MatchAllOf, second && chains onto it
    auto combined = gt && lt && gt2;

    EXPECT_TRUE(combined.match(50));
}

// Test chaining three matchers where middle fails
TEST_F(MatchAllOfOperatorTest_145, ChainingThreeMatchers_MiddleFails_145) {
    GreaterThanMatcher<int> gt(0);
    LessThanMatcher<int> lt(5);   // will fail for value 50
    GreaterThanMatcher<int> gt2(-10);

    auto combined = gt && lt && gt2;

    EXPECT_FALSE(combined.match(50));
}

// Test with string type matchers
TEST_F(MatchAllOfOperatorTest_145, StringMatchers_BothMatch_145) {
    EqualsMatcher<std::string> eq("hello");
    AlwaysTrueMatcher<std::string> t;

    auto combined = eq && t;

    EXPECT_TRUE(combined.match(std::string("hello")));
}

// Test with string type matchers where equality fails
TEST_F(MatchAllOfOperatorTest_145, StringMatchers_EqualityFails_145) {
    EqualsMatcher<std::string> eq("hello");
    AlwaysTrueMatcher<std::string> t;

    auto combined = eq && t;

    EXPECT_FALSE(combined.match(std::string("world")));
}

// Boundary: Test with value exactly at the boundary
TEST_F(MatchAllOfOperatorTest_145, BoundaryValue_ExactThreshold_145) {
    GreaterThanMatcher<int> gt(5);
    LessThanMatcher<int> lt(10);

    auto combined = gt && lt;

    // Value == 5 is NOT greater than 5
    EXPECT_FALSE(combined.match(5));
    // Value == 10 is NOT less than 10
    EXPECT_FALSE(combined.match(10));
    // Value == 6 should pass both
    EXPECT_TRUE(combined.match(6));
    // Value == 9 should pass both
    EXPECT_TRUE(combined.match(9));
}

// Test that the combined matcher can be used with double types
TEST_F(MatchAllOfOperatorTest_145, DoubleType_BothMatch_145) {
    GreaterThanMatcher<double> gt(1.0);
    LessThanMatcher<double> lt(2.0);

    auto combined = gt && lt;

    EXPECT_TRUE(combined.match(1.5));
    EXPECT_FALSE(combined.match(0.5));
    EXPECT_FALSE(combined.match(2.5));
}

// Test chaining four matchers
TEST_F(MatchAllOfOperatorTest_145, ChainingFourMatchers_AllMatch_145) {
    GreaterThanMatcher<int> gt1(0);
    GreaterThanMatcher<int> gt2(1);
    LessThanMatcher<int> lt1(100);
    LessThanMatcher<int> lt2(50);

    auto combined = gt1 && gt2 && lt1 && lt2;

    EXPECT_TRUE(combined.match(25));
    EXPECT_FALSE(combined.match(0));   // fails gt1 and gt2
    EXPECT_FALSE(combined.match(75));  // fails lt2
}
