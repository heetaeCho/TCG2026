#include <catch2/matchers/catch_matchers_templated.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_predicate.hpp>

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <type_traits>

// Define a simple generic matcher for testing
struct AlwaysTrueMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const&) const { return true; }

    std::string describe() const { return "always true"; }
};

struct AlwaysFalseMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const&) const { return false; }

    std::string describe() const { return "always false"; }
};

struct IsEqualToIntMatcher : Catch::Matchers::MatcherGenericBase {
    int expected;
    explicit IsEqualToIntMatcher(int val) : expected(val) {}

    bool match(int const& actual) const { return actual == expected; }

    std::string describe() const { return "equals " + std::to_string(expected); }
};

struct IsEmptyMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename Container>
    bool match(Container const& c) const { return c.empty(); }

    std::string describe() const { return "is empty"; }
};

struct StringContainsMatcher : Catch::Matchers::MatcherGenericBase {
    std::string substr;
    explicit StringContainsMatcher(std::string s) : substr(std::move(s)) {}

    bool match(std::string const& actual) const {
        return actual.find(substr) != std::string::npos;
    }

    std::string describe() const { return "contains \"" + substr + "\""; }
};

class MatchNotOfGenericTest_171 : public ::testing::Test {
protected:
};

// Test that negating an always-true matcher yields false
TEST_F(MatchNotOfGenericTest_171, NegateAlwaysTrueMatcherReturnsFalse_171) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    EXPECT_FALSE(notMatcher.match(42));
    EXPECT_FALSE(notMatcher.match(std::string("hello")));
    EXPECT_FALSE(notMatcher.match(3.14));
}

// Test that negating an always-false matcher yields true
TEST_F(MatchNotOfGenericTest_171, NegateAlwaysFalseMatcherReturnsTrue_171) {
    AlwaysFalseMatcher falseMatcher;
    auto notMatcher = !falseMatcher;
    EXPECT_TRUE(notMatcher.match(42));
    EXPECT_TRUE(notMatcher.match(std::string("hello")));
    EXPECT_TRUE(notMatcher.match(3.14));
}

// Test negation with int equality matcher when value matches
TEST_F(MatchNotOfGenericTest_171, NegateEqualMatcherWhenEqual_171) {
    IsEqualToIntMatcher matcher(5);
    auto notMatcher = !matcher;
    EXPECT_FALSE(notMatcher.match(5));
}

// Test negation with int equality matcher when value doesn't match
TEST_F(MatchNotOfGenericTest_171, NegateEqualMatcherWhenNotEqual_171) {
    IsEqualToIntMatcher matcher(5);
    auto notMatcher = !matcher;
    EXPECT_TRUE(notMatcher.match(10));
    EXPECT_TRUE(notMatcher.match(0));
    EXPECT_TRUE(notMatcher.match(-1));
}

// Test negation with empty container matcher on empty container
TEST_F(MatchNotOfGenericTest_171, NegateIsEmptyOnEmptyContainer_171) {
    IsEmptyMatcher matcher;
    auto notMatcher = !matcher;
    std::vector<int> empty;
    EXPECT_FALSE(notMatcher.match(empty));
}

// Test negation with empty container matcher on non-empty container
TEST_F(MatchNotOfGenericTest_171, NegateIsEmptyOnNonEmptyContainer_171) {
    IsEmptyMatcher matcher;
    auto notMatcher = !matcher;
    std::vector<int> nonEmpty = {1, 2, 3};
    EXPECT_TRUE(notMatcher.match(nonEmpty));
}

// Test negation with string contains matcher
TEST_F(MatchNotOfGenericTest_171, NegateStringContainsWhenPresent_171) {
    StringContainsMatcher matcher("hello");
    auto notMatcher = !matcher;
    EXPECT_FALSE(notMatcher.match(std::string("say hello world")));
}

TEST_F(MatchNotOfGenericTest_171, NegateStringContainsWhenAbsent_171) {
    StringContainsMatcher matcher("hello");
    auto notMatcher = !matcher;
    EXPECT_TRUE(notMatcher.match(std::string("goodbye world")));
}

// Test that describe contains "not" indication
TEST_F(MatchNotOfGenericTest_171, DescribeContainsNegation_171) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    std::string description = notMatcher.describe();
    // The negated matcher description should contain "not" or be non-empty
    EXPECT_FALSE(description.empty());
    // Typically the describe should include "not" to indicate negation
    EXPECT_NE(description.find("not"), std::string::npos);
}

// Test that the result type is correct (MatchNotOfGeneric)
TEST_F(MatchNotOfGenericTest_171, ResultTypeIsMatchNotOfGeneric_171) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    bool isCorrectType = std::is_same<
        decltype(notMatcher),
        Catch::Matchers::Detail::MatchNotOfGeneric<AlwaysTrueMatcher>
    >::value;
    EXPECT_TRUE(isCorrectType);
}

// Test double negation
TEST_F(MatchNotOfGenericTest_171, DoubleNegationRestoresOriginalBehavior_171) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    auto doubleNotMatcher = !notMatcher;
    EXPECT_TRUE(doubleNotMatcher.match(42));
}

TEST_F(MatchNotOfGenericTest_171, DoubleNegationOfFalseMatcherReturnsFalse_171) {
    AlwaysFalseMatcher falseMatcher;
    auto notMatcher = !falseMatcher;
    auto doubleNotMatcher = !notMatcher;
    EXPECT_FALSE(doubleNotMatcher.match(42));
}

// Boundary: negation of equality matcher with zero
TEST_F(MatchNotOfGenericTest_171, NegateEqualMatcherWithZero_171) {
    IsEqualToIntMatcher matcher(0);
    auto notMatcher = !matcher;
    EXPECT_FALSE(notMatcher.match(0));
    EXPECT_TRUE(notMatcher.match(1));
    EXPECT_TRUE(notMatcher.match(-1));
}

// Boundary: negation of equality with negative number
TEST_F(MatchNotOfGenericTest_171, NegateEqualMatcherWithNegative_171) {
    IsEqualToIntMatcher matcher(-42);
    auto notMatcher = !matcher;
    EXPECT_FALSE(notMatcher.match(-42));
    EXPECT_TRUE(notMatcher.match(42));
}

// Test with empty string
TEST_F(MatchNotOfGenericTest_171, NegateStringContainsEmptySubstring_171) {
    StringContainsMatcher matcher("");
    auto notMatcher = !matcher;
    // Every string contains empty string, so negation should be false
    EXPECT_FALSE(notMatcher.match(std::string("anything")));
    EXPECT_FALSE(notMatcher.match(std::string("")));
}

// Test negation with string empty matcher on empty string
TEST_F(MatchNotOfGenericTest_171, NegateIsEmptyOnEmptyString_171) {
    IsEmptyMatcher matcher;
    auto notMatcher = !matcher;
    EXPECT_FALSE(notMatcher.match(std::string("")));
}

TEST_F(MatchNotOfGenericTest_171, NegateIsEmptyOnNonEmptyString_171) {
    IsEmptyMatcher matcher;
    auto notMatcher = !matcher;
    EXPECT_TRUE(notMatcher.match(std::string("not empty")));
}

// SFINAE check: operator! should only be available for generic matchers
TEST_F(MatchNotOfGenericTest_171, SFINAEOnlyGenericMatchersEnabled_171) {
    // This test verifies the enable_if constraint compiles for valid generic matchers
    bool isGeneric = Catch::Matchers::Detail::is_generic_matcher_v<AlwaysTrueMatcher>;
    EXPECT_TRUE(isGeneric);
}
