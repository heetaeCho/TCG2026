#include <gtest/gtest.h>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <catch2/matchers/catch_matchers_predicate.hpp>
#include <catch2/matchers/catch_matchers_contains.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>
#include <string>
#include <vector>

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
        return "equals: " + Catch::Detail::stringify(m_expected);
    }
};

template <typename T>
EqualsMatcher<T> Equals(T expected) {
    return EqualsMatcher<T>(std::move(expected));
}

class MatchNotOfTest_147 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that negating a matching matcher results in no match
TEST_F(MatchNotOfTest_147, NegatedMatchingMatcherDoesNotMatch_147) {
    auto matcher = Equals(42);
    auto negated = !matcher;
    EXPECT_FALSE(negated.match(42));
}

// Test that negating a non-matching matcher results in a match
TEST_F(MatchNotOfTest_147, NegatedNonMatchingMatcherMatches_147) {
    auto matcher = Equals(42);
    auto negated = !matcher;
    EXPECT_TRUE(negated.match(99));
}

// Test negation with string matchers
TEST_F(MatchNotOfTest_147, NegatedStringMatcherMatchesWhenOriginalDoesNot_147) {
    auto matcher = Equals(std::string("hello"));
    auto negated = !matcher;
    EXPECT_TRUE(negated.match(std::string("world")));
}

// Test negation with string matchers - matching case
TEST_F(MatchNotOfTest_147, NegatedStringMatcherDoesNotMatchWhenOriginalDoes_147) {
    auto matcher = Equals(std::string("hello"));
    auto negated = !matcher;
    EXPECT_FALSE(negated.match(std::string("hello")));
}

// Test that the description of negated matcher contains "not"
TEST_F(MatchNotOfTest_147, NegatedMatcherDescriptionContainsNot_147) {
    auto matcher = Equals(42);
    auto negated = !matcher;
    std::string desc = negated.describe();
    EXPECT_NE(desc.find("not"), std::string::npos);
}

// Test negation with zero value
TEST_F(MatchNotOfTest_147, NegatedMatcherWithZeroValue_147) {
    auto matcher = Equals(0);
    auto negated = !matcher;
    EXPECT_FALSE(negated.match(0));
    EXPECT_TRUE(negated.match(1));
}

// Test negation with negative values
TEST_F(MatchNotOfTest_147, NegatedMatcherWithNegativeValue_147) {
    auto matcher = Equals(-1);
    auto negated = !matcher;
    EXPECT_FALSE(negated.match(-1));
    EXPECT_TRUE(negated.match(0));
}

// Test negation with empty string
TEST_F(MatchNotOfTest_147, NegatedMatcherWithEmptyString_147) {
    auto matcher = Equals(std::string(""));
    auto negated = !matcher;
    EXPECT_FALSE(negated.match(std::string("")));
    EXPECT_TRUE(negated.match(std::string("notempty")));
}

// Test negation with double values
TEST_F(MatchNotOfTest_147, NegatedMatcherWithDoubleValue_147) {
    auto matcher = Equals(3.14);
    auto negated = !matcher;
    EXPECT_FALSE(negated.match(3.14));
    EXPECT_TRUE(negated.match(2.71));
}

// Test that the negated matcher is a valid matcher (can be used in expressions)
TEST_F(MatchNotOfTest_147, NegatedMatcherIsValidMatcherType_147) {
    auto matcher = Equals(42);
    auto negated = !matcher;
    // Verify it behaves consistently across multiple calls
    EXPECT_TRUE(negated.match(1));
    EXPECT_TRUE(negated.match(1));
    EXPECT_FALSE(negated.match(42));
    EXPECT_FALSE(negated.match(42));
}
