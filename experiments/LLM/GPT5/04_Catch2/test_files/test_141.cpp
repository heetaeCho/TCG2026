// File: match_any_of_or_operator_test.cpp

#include <gtest/gtest.h>
#include <string>
#include <catch2/matchers/catch_matchers.hpp>

using Catch::Matchers::MatcherBase;
using Catch::Matchers::Detail::MatchAnyOf;

// Simple concrete matchers for int, used as external collaborators.
struct AlwaysTrueMatcher : MatcherBase<int> {
    bool match(int const&) const override { return true; }
    std::string describe() const override { return "always true"; }
};

struct AlwaysFalseMatcher : MatcherBase<int> {
    bool match(int const&) const override { return false; }
    std::string describe() const override { return "always false"; }
};

struct IsEvenMatcher : MatcherBase<int> {
    bool match(int const& v) const override { return v % 2 == 0; }
    std::string describe() const override { return "is even"; }
};

struct EqualsMatcher : MatcherBase<int> {
    explicit EqualsMatcher(int expected) : expected_(expected) {}
    bool match(int const& v) const override { return v == expected_; }
    std::string describe() const override {
        return std::string("equals ") + std::to_string(expected_);
    }
private:
    int expected_;
};

// No fixture needed, but keeping a named test suite for clarity.
class MatchAnyOfOrOperatorTest_141 : public ::testing::Test {};

TEST_F(MatchAnyOfOrOperatorTest_141, SingleChildTrue_YieldsTrueWhenMatched_141) {
    IsEvenMatcher even;

    // Build via operator|| starting from an rvalue MatchAnyOf
    auto any = MatchAnyOf<int>() || even;

    EXPECT_TRUE(any.match(2));
    EXPECT_FALSE(any.match(3));
}

TEST_F(MatchAnyOfOrOperatorTest_141, SingleChildFalse_YieldsFalse_141) {
    AlwaysFalseMatcher f;

    auto any = MatchAnyOf<int>() || f;

    EXPECT_FALSE(any.match(0));
    EXPECT_FALSE(any.match(123));
}

TEST_F(MatchAnyOfOrOperatorTest_141, MultipleChildren_TrueIfAnyChildMatches_141) {
    AlwaysFalseMatcher f1;
    IsEvenMatcher even;
    EqualsMatcher eq7(7);

    // Chain using operator||
    auto any = MatchAnyOf<int>() || f1 || even || eq7;

    EXPECT_TRUE(any.match(4));  // matched by is even
    EXPECT_TRUE(any.match(7));  // matched by equals 7
    EXPECT_FALSE(any.match(9)); // none match
}

TEST_F(MatchAnyOfOrOperatorTest_141, MultipleChildren_AllFalse_YieldsFalse_141) {
    AlwaysFalseMatcher f1, f2, f3;

    auto any = MatchAnyOf<int>() || f1 || f2 || f3;

    EXPECT_FALSE(any.match(-10));
    EXPECT_FALSE(any.match(0));
    EXPECT_FALSE(any.match(999));
}

TEST_F(MatchAnyOfOrOperatorTest_141, ChainingFromMovedTemporary_RemainsUsable_141) {
    IsEvenMatcher even;
    EqualsMatcher eq5(5);

    // Start from a named instance to emphasize movability of lhs
    MatchAnyOf<int> start;
    auto any = std::move(start) || even || eq5;

    EXPECT_TRUE(any.match(10)); // even
    EXPECT_TRUE(any.match(5));  // equals 5
    EXPECT_FALSE(any.match(3));
}

TEST_F(MatchAnyOfOrOperatorTest_141, Describe_IncludesChildDescriptions_141) {
    IsEvenMatcher even;
    EqualsMatcher eq7(7);

    auto any = MatchAnyOf<int>() || even || eq7;

    std::string d = any.describe();
    // We don't assert exact formatting; only that child descriptions appear.
    EXPECT_NE(std::string::npos, d.find("is even"));
    EXPECT_NE(std::string::npos, d.find("equals 7"));
}
