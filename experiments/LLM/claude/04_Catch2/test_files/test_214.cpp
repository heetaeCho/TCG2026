#include <gtest/gtest.h>
#include <string>
#include <functional>

// Since we're testing the PredicateMatcher from Catch2, we need to include the relevant headers.
// Based on the partial code, we'll include the necessary Catch2 headers.
#include "catch2/matchers/catch_matchers_predicate.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// Test fixture for PredicateMatcher tests
class PredicateMatcherTest_214 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a simple predicate that always returns true matches any value
TEST_F(PredicateMatcherTest_214, AlwaysTruePredicateMatchesAnyValue_214) {
    auto matcher = Catch::Matchers::Predicate<int>(
        [](int) { return true; },
        "always true"
    );
    EXPECT_TRUE(matcher.match(0));
    EXPECT_TRUE(matcher.match(42));
    EXPECT_TRUE(matcher.match(-1));
}

// Test that a simple predicate that always returns false matches no value
TEST_F(PredicateMatcherTest_214, AlwaysFalsePredicateMatchesNoValue_214) {
    auto matcher = Catch::Matchers::Predicate<int>(
        [](int) { return false; },
        "always false"
    );
    EXPECT_FALSE(matcher.match(0));
    EXPECT_FALSE(matcher.match(42));
    EXPECT_FALSE(matcher.match(-1));
}

// Test that describe returns the provided description
TEST_F(PredicateMatcherTest_214, DescribeReturnsProvidedDescription_214) {
    std::string description = "is a positive number";
    auto matcher = Catch::Matchers::Predicate<int>(
        [](int x) { return x > 0; },
        description
    );
    std::string result = matcher.describe();
    // The description may be finalized (e.g., wrapped), but should contain the original text
    EXPECT_NE(result.find("is a positive number"), std::string::npos);
}

// Test that a predicate checking for even numbers works correctly
TEST_F(PredicateMatcherTest_214, EvenNumberPredicateMatchesCorrectly_214) {
    auto matcher = Catch::Matchers::Predicate<int>(
        [](int x) { return x % 2 == 0; },
        "is even"
    );
    EXPECT_TRUE(matcher.match(0));
    EXPECT_TRUE(matcher.match(2));
    EXPECT_TRUE(matcher.match(-4));
    EXPECT_FALSE(matcher.match(1));
    EXPECT_FALSE(matcher.match(3));
    EXPECT_FALSE(matcher.match(-7));
}

// Test with string type
TEST_F(PredicateMatcherTest_214, StringPredicateMatchesCorrectly_214) {
    auto matcher = Catch::Matchers::Predicate<std::string>(
        [](std::string const& s) { return s.length() > 3; },
        "has length greater than 3"
    );
    EXPECT_TRUE(matcher.match("hello"));
    EXPECT_TRUE(matcher.match("test"));
    EXPECT_FALSE(matcher.match("hi"));
    EXPECT_FALSE(matcher.match(""));
    EXPECT_FALSE(matcher.match("abc"));
}

// Test with empty string predicate
TEST_F(PredicateMatcherTest_214, EmptyStringPredicateMatchesCorrectly_214) {
    auto matcher = Catch::Matchers::Predicate<std::string>(
        [](std::string const& s) { return s.empty(); },
        "is empty"
    );
    EXPECT_TRUE(matcher.match(""));
    EXPECT_FALSE(matcher.match("not empty"));
}

// Test boundary condition: zero
TEST_F(PredicateMatcherTest_214, BoundaryZeroPredicateMatchesCorrectly_214) {
    auto matcher = Catch::Matchers::Predicate<int>(
        [](int x) { return x >= 0; },
        "is non-negative"
    );
    EXPECT_TRUE(matcher.match(0));
    EXPECT_TRUE(matcher.match(1));
    EXPECT_FALSE(matcher.match(-1));
}

// Test with double type
TEST_F(PredicateMatcherTest_214, DoublePredicateMatchesCorrectly_214) {
    auto matcher = Catch::Matchers::Predicate<double>(
        [](double x) { return x > 0.0 && x < 1.0; },
        "is between 0 and 1 exclusive"
    );
    EXPECT_TRUE(matcher.match(0.5));
    EXPECT_TRUE(matcher.match(0.001));
    EXPECT_TRUE(matcher.match(0.999));
    EXPECT_FALSE(matcher.match(0.0));
    EXPECT_FALSE(matcher.match(1.0));
    EXPECT_FALSE(matcher.match(-0.5));
    EXPECT_FALSE(matcher.match(1.5));
}

// Test describe with empty description
TEST_F(PredicateMatcherTest_214, DescribeWithEmptyDescription_214) {
    auto matcher = Catch::Matchers::Predicate<int>(
        [](int) { return true; },
        ""
    );
    // Should not crash; describe should return something
    std::string result = matcher.describe();
    // Even with empty input, describe() should return a valid string
    EXPECT_NO_THROW(matcher.describe());
}

// Test with a complex predicate involving multiple conditions
TEST_F(PredicateMatcherTest_214, ComplexPredicateMatchesCorrectly_214) {
    auto matcher = Catch::Matchers::Predicate<int>(
        [](int x) { return x > 10 && x < 20 && x % 2 == 0; },
        "is an even number between 10 and 20"
    );
    EXPECT_TRUE(matcher.match(12));
    EXPECT_TRUE(matcher.match(14));
    EXPECT_TRUE(matcher.match(16));
    EXPECT_TRUE(matcher.match(18));
    EXPECT_FALSE(matcher.match(10));
    EXPECT_FALSE(matcher.match(20));
    EXPECT_FALSE(matcher.match(11));
    EXPECT_FALSE(matcher.match(13));
    EXPECT_FALSE(matcher.match(5));
}

// Test with a vector type
TEST_F(PredicateMatcherTest_214, VectorPredicateMatchesCorrectly_214) {
    auto matcher = Catch::Matchers::Predicate<std::vector<int>>(
        [](std::vector<int> const& v) { return v.size() == 3; },
        "has exactly 3 elements"
    );
    EXPECT_TRUE(matcher.match(std::vector<int>{1, 2, 3}));
    EXPECT_FALSE(matcher.match(std::vector<int>{}));
    EXPECT_FALSE(matcher.match(std::vector<int>{1}));
    EXPECT_FALSE(matcher.match(std::vector<int>{1, 2, 3, 4}));
}

// Test that match is const-correct (can be called on const reference)
TEST_F(PredicateMatcherTest_214, MatchWorksWithConstReference_214) {
    auto matcher = Catch::Matchers::Predicate<int>(
        [](int x) { return x == 42; },
        "is 42"
    );
    const int value = 42;
    EXPECT_TRUE(matcher.match(value));
    const int other_value = 43;
    EXPECT_FALSE(matcher.match(other_value));
}
