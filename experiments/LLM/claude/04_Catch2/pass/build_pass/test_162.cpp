#include <gtest/gtest.h>
#include <string>
#include <type_traits>

#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// Simple custom matchers for testing purposes
namespace {

class IsEqualToInt : public Catch::Matchers::MatcherGenericBase {
    int m_value;
public:
    explicit IsEqualToInt(int value) : m_value(value) {}

    bool match(int const& arg) const {
        return arg == m_value;
    }

    std::string describe() const override {
        return "equals " + std::to_string(m_value);
    }
};

class IsGreaterThanInt : public Catch::Matchers::MatcherGenericBase {
    int m_value;
public:
    explicit IsGreaterThanInt(int value) : m_value(value) {}

    bool match(int const& arg) const {
        return arg > m_value;
    }

    std::string describe() const override {
        return "is greater than " + std::to_string(m_value);
    }
};

class IsLessThanInt : public Catch::Matchers::MatcherGenericBase {
    int m_value;
public:
    explicit IsLessThanInt(int value) : m_value(value) {}

    bool match(int const& arg) const {
        return arg < m_value;
    }

    std::string describe() const override {
        return "is less than " + std::to_string(m_value);
    }
};

class StringContainsMatcher : public Catch::Matchers::MatcherGenericBase {
    std::string m_substr;
public:
    explicit StringContainsMatcher(std::string substr) : m_substr(std::move(substr)) {}

    bool match(std::string const& arg) const {
        return arg.find(m_substr) != std::string::npos;
    }

    std::string describe() const override {
        return "contains \"" + m_substr + "\"";
    }
};

class AlwaysTrueMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    bool match(int const&) const { return true; }
    std::string describe() const override { return "always true"; }
};

class AlwaysFalseMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    bool match(int const&) const { return false; }
    std::string describe() const override { return "always false"; }
};

} // anonymous namespace

class MatchAnyOfGenericTest_162 : public ::testing::Test {
protected:
};

// Test that match returns true when the first matcher matches
TEST_F(MatchAnyOfGenericTest_162, MatchReturnsTrueWhenFirstMatcherMatches_162) {
    IsEqualToInt eq5(5);
    IsEqualToInt eq10(10);
    auto combined = eq5 || eq10;
    EXPECT_TRUE(combined.match(5));
}

// Test that match returns true when the second matcher matches
TEST_F(MatchAnyOfGenericTest_162, MatchReturnsTrueWhenSecondMatcherMatches_162) {
    IsEqualToInt eq5(5);
    IsEqualToInt eq10(10);
    auto combined = eq5 || eq10;
    EXPECT_TRUE(combined.match(10));
}

// Test that match returns false when no matchers match
TEST_F(MatchAnyOfGenericTest_162, MatchReturnsFalseWhenNoMatcherMatches_162) {
    IsEqualToInt eq5(5);
    IsEqualToInt eq10(10);
    auto combined = eq5 || eq10;
    EXPECT_FALSE(combined.match(7));
}

// Test that match returns true when both matchers match
TEST_F(MatchAnyOfGenericTest_162, MatchReturnsTrueWhenBothMatchersMatch_162) {
    IsEqualToInt eq5(5);
    IsGreaterThanInt gt3(3);
    auto combined = eq5 || gt3;
    EXPECT_TRUE(combined.match(5));
}

// Test describe produces a string containing "or"
TEST_F(MatchAnyOfGenericTest_162, DescribeContainsOrKeyword_162) {
    IsEqualToInt eq5(5);
    IsEqualToInt eq10(10);
    auto combined = eq5 || eq10;
    std::string description = combined.describe();
    EXPECT_NE(description.find(" or "), std::string::npos);
}

// Test describe includes descriptions of individual matchers
TEST_F(MatchAnyOfGenericTest_162, DescribeIncludesIndividualMatcherDescriptions_162) {
    IsEqualToInt eq5(5);
    IsGreaterThanInt gt10(10);
    auto combined = eq5 || gt10;
    std::string description = combined.describe();
    EXPECT_NE(description.find("equals 5"), std::string::npos);
    EXPECT_NE(description.find("is greater than 10"), std::string::npos);
}

// Test with three matchers combined
TEST_F(MatchAnyOfGenericTest_162, ThreeMatchersCombined_162) {
    IsEqualToInt eq5(5);
    IsEqualToInt eq10(10);
    IsEqualToInt eq15(15);
    auto combined = eq5 || eq10 || eq15;
    EXPECT_TRUE(combined.match(5));
    EXPECT_TRUE(combined.match(10));
    EXPECT_TRUE(combined.match(15));
    EXPECT_FALSE(combined.match(7));
}

// Test with all false matchers
TEST_F(MatchAnyOfGenericTest_162, AllFalseMatchersReturnFalse_162) {
    AlwaysFalseMatcher f1;
    AlwaysFalseMatcher f2;
    auto combined = f1 || f2;
    EXPECT_FALSE(combined.match(42));
}

// Test with one true matcher among false ones
TEST_F(MatchAnyOfGenericTest_162, OneTrueAmongFalseReturnsTrue_162) {
    AlwaysFalseMatcher f1;
    AlwaysTrueMatcher t1;
    AlwaysFalseMatcher f2;
    auto combined = f1 || t1 || f2;
    EXPECT_TRUE(combined.match(42));
}

// Test with string matchers
TEST_F(MatchAnyOfGenericTest_162, StringMatchersCombined_162) {
    StringContainsMatcher hello("hello");
    StringContainsMatcher world("world");
    auto combined = hello || world;
    EXPECT_TRUE(combined.match(std::string("hello there")));
    EXPECT_TRUE(combined.match(std::string("brave world")));
    EXPECT_TRUE(combined.match(std::string("hello world")));
    EXPECT_FALSE(combined.match(std::string("foo bar")));
}

// Test describe with three matchers contains multiple "or" keywords
TEST_F(MatchAnyOfGenericTest_162, DescribeWithThreeMatchersContainsMultipleOr_162) {
    IsEqualToInt eq1(1);
    IsEqualToInt eq2(2);
    IsEqualToInt eq3(3);
    auto combined = eq1 || eq2 || eq3;
    std::string description = combined.describe();
    // Should contain at least two occurrences of " or "
    size_t first = description.find(" or ");
    ASSERT_NE(first, std::string::npos);
    size_t second = description.find(" or ", first + 4);
    EXPECT_NE(second, std::string::npos);
}

// Test boundary: matching with boundary integer values
TEST_F(MatchAnyOfGenericTest_162, BoundaryIntegerValues_162) {
    IsEqualToInt eqMin(std::numeric_limits<int>::min());
    IsEqualToInt eqMax(std::numeric_limits<int>::max());
    auto combined = eqMin || eqMax;
    EXPECT_TRUE(combined.match(std::numeric_limits<int>::min()));
    EXPECT_TRUE(combined.match(std::numeric_limits<int>::max()));
    EXPECT_FALSE(combined.match(0));
}

// Test that MatchAnyOfGeneric is move constructible
TEST_F(MatchAnyOfGenericTest_162, MoveConstructible_162) {
    IsEqualToInt eq5(5);
    IsEqualToInt eq10(10);
    auto combined = eq5 || eq10;
    auto moved = std::move(combined);
    EXPECT_TRUE(moved.match(5));
    EXPECT_TRUE(moved.match(10));
    EXPECT_FALSE(moved.match(7));
}

// Test describe is non-empty
TEST_F(MatchAnyOfGenericTest_162, DescribeIsNonEmpty_162) {
    IsEqualToInt eq5(5);
    IsEqualToInt eq10(10);
    auto combined = eq5 || eq10;
    EXPECT_FALSE(combined.describe().empty());
}

// Test with mixed matcher types (greater than OR less than)
TEST_F(MatchAnyOfGenericTest_162, MixedMatcherTypesGreaterOrLessThan_162) {
    IsGreaterThanInt gt100(100);
    IsLessThanInt lt0(0);
    auto combined = gt100 || lt0;
    EXPECT_TRUE(combined.match(200));
    EXPECT_TRUE(combined.match(-5));
    EXPECT_FALSE(combined.match(50));
    EXPECT_FALSE(combined.match(0));
    EXPECT_FALSE(combined.match(100));
}
