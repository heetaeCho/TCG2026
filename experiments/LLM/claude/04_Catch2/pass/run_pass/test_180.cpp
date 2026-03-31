#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <list>
#include <array>

// Include the necessary Catch2 headers
#include "catch2/matchers/catch_matchers_quantifiers.hpp"
#include "catch2/matchers/catch_matchers_predicate.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// We need to work with the Catch2 matchers framework
// Since AnyMatchMatcher is a template class that checks if ANY element in a range matches,
// we'll test it through the public interface.

using namespace Catch::Matchers;

// A simple predicate matcher for testing
class IsEvenMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    bool match(int value) const {
        return value % 2 == 0;
    }
    std::string describe() const override {
        return "is even";
    }
};

class IsPositiveMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    bool match(int value) const {
        return value > 0;
    }
    std::string describe() const override {
        return "is positive";
    }
};

class IsEmptyStringMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    bool match(const std::string& value) const {
        return value.empty();
    }
    std::string describe() const override {
        return "is empty string";
    }
};

class GreaterThanMatcher : public Catch::Matchers::MatcherGenericBase {
    int m_threshold;
public:
    explicit GreaterThanMatcher(int threshold) : m_threshold(threshold) {}
    bool match(int value) const {
        return value > m_threshold;
    }
    std::string describe() const override {
        return "is greater than " + std::to_string(m_threshold);
    }
};

// Test fixture
class AnyMatchMatcherTest_180 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: AnyMatchMatcher matches when at least one element satisfies the inner matcher
TEST_F(AnyMatchMatcherTest_180, MatchesWhenOneElementSatisfies_180) {
    auto matcher = AnyTrue();
    std::vector<bool> values = {false, false, true, false};
    // AnyTrue checks if any element is true
    EXPECT_TRUE(matcher.match(values));
}

// Test: AnyMatchMatcher with custom matcher on vector with some even numbers
TEST_F(AnyMatchMatcherTest_180, MatchesWhenSomeElementsAreEven_180) {
    auto anyMatcher = AnyMatch(IsEvenMatcher{});
    std::vector<int> values = {1, 3, 4, 5};
    EXPECT_TRUE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher does not match when no element satisfies the condition
TEST_F(AnyMatchMatcherTest_180, DoesNotMatchWhenNoElementSatisfies_180) {
    auto anyMatcher = AnyMatch(IsEvenMatcher{});
    std::vector<int> values = {1, 3, 5, 7};
    EXPECT_FALSE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher with empty range returns false
TEST_F(AnyMatchMatcherTest_180, DoesNotMatchEmptyRange_180) {
    auto anyMatcher = AnyMatch(IsEvenMatcher{});
    std::vector<int> emptyVec;
    EXPECT_FALSE(anyMatcher.match(emptyVec));
}

// Test: AnyMatchMatcher matches when all elements satisfy the condition
TEST_F(AnyMatchMatcherTest_180, MatchesWhenAllElementsSatisfy_180) {
    auto anyMatcher = AnyMatch(IsEvenMatcher{});
    std::vector<int> values = {2, 4, 6, 8};
    EXPECT_TRUE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher matches with single element that satisfies
TEST_F(AnyMatchMatcherTest_180, MatchesSingleElementThatSatisfies_180) {
    auto anyMatcher = AnyMatch(IsEvenMatcher{});
    std::vector<int> values = {2};
    EXPECT_TRUE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher does not match with single element that doesn't satisfy
TEST_F(AnyMatchMatcherTest_180, DoesNotMatchSingleElementThatDoesNotSatisfy_180) {
    auto anyMatcher = AnyMatch(IsEvenMatcher{});
    std::vector<int> values = {1};
    EXPECT_FALSE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher describe includes inner matcher description
TEST_F(AnyMatchMatcherTest_180, DescribeContainsInnerMatcherDescription_180) {
    auto anyMatcher = AnyMatch(IsEvenMatcher{});
    std::string description = anyMatcher.describe();
    EXPECT_NE(description.find("is even"), std::string::npos);
    EXPECT_NE(description.find("any match"), std::string::npos);
}

// Test: AnyMatchMatcher works with std::list
TEST_F(AnyMatchMatcherTest_180, MatchesWithListContainer_180) {
    auto anyMatcher = AnyMatch(IsEvenMatcher{});
    std::list<int> values = {1, 3, 5, 6};
    EXPECT_TRUE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher works with std::array
TEST_F(AnyMatchMatcherTest_180, MatchesWithArrayContainer_180) {
    auto anyMatcher = AnyMatch(IsEvenMatcher{});
    std::array<int, 4> values = {1, 3, 5, 7};
    EXPECT_FALSE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher with string matcher
TEST_F(AnyMatchMatcherTest_180, MatchesWithStringMatcher_180) {
    auto anyMatcher = AnyMatch(IsEmptyStringMatcher{});
    std::vector<std::string> values = {"hello", "", "world"};
    EXPECT_TRUE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher with string matcher no match
TEST_F(AnyMatchMatcherTest_180, DoesNotMatchWithStringMatcherNoEmptyStrings_180) {
    auto anyMatcher = AnyMatch(IsEmptyStringMatcher{});
    std::vector<std::string> values = {"hello", "world", "foo"};
    EXPECT_FALSE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher with parameterized inner matcher
TEST_F(AnyMatchMatcherTest_180, MatchesWithParameterizedInnerMatcher_180) {
    auto anyMatcher = AnyMatch(GreaterThanMatcher{10});
    std::vector<int> values = {1, 5, 3, 11};
    EXPECT_TRUE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher with parameterized inner matcher no match
TEST_F(AnyMatchMatcherTest_180, DoesNotMatchWithParameterizedInnerMatcherNoMatch_180) {
    auto anyMatcher = AnyMatch(GreaterThanMatcher{100});
    std::vector<int> values = {1, 5, 3, 11};
    EXPECT_FALSE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher only first element matches
TEST_F(AnyMatchMatcherTest_180, MatchesWhenOnlyFirstElementSatisfies_180) {
    auto anyMatcher = AnyMatch(IsEvenMatcher{});
    std::vector<int> values = {2, 1, 3, 5};
    EXPECT_TRUE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher only last element matches
TEST_F(AnyMatchMatcherTest_180, MatchesWhenOnlyLastElementSatisfies_180) {
    auto anyMatcher = AnyMatch(IsEvenMatcher{});
    std::vector<int> values = {1, 3, 5, 8};
    EXPECT_TRUE(anyMatcher.match(values));
}

// Test: AnyTrue with all false
TEST_F(AnyMatchMatcherTest_180, AnyTrueWithAllFalse_180) {
    auto matcher = AnyTrue();
    std::vector<bool> values = {false, false, false};
    EXPECT_FALSE(matcher.match(values));
}

// Test: AnyTrue with empty container
TEST_F(AnyMatchMatcherTest_180, AnyTrueWithEmptyContainer_180) {
    auto matcher = AnyTrue();
    std::vector<bool> values;
    EXPECT_FALSE(matcher.match(values));
}

// Test: AnyTrue with all true
TEST_F(AnyMatchMatcherTest_180, AnyTrueWithAllTrue_180) {
    auto matcher = AnyTrue();
    std::vector<bool> values = {true, true, true};
    EXPECT_TRUE(matcher.match(values));
}

// Test: AnyMatchMatcher with large range
TEST_F(AnyMatchMatcherTest_180, MatchesWithLargeRangeLastElementMatches_180) {
    auto anyMatcher = AnyMatch(IsEvenMatcher{});
    std::vector<int> values(1000, 1); // all odd
    values.back() = 2; // last one is even
    EXPECT_TRUE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher with large range no match
TEST_F(AnyMatchMatcherTest_180, DoesNotMatchWithLargeRangeNoMatch_180) {
    auto anyMatcher = AnyMatch(IsEvenMatcher{});
    std::vector<int> values(1000, 1); // all odd
    EXPECT_FALSE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher with positive matcher
TEST_F(AnyMatchMatcherTest_180, MatchesWithPositiveMatcherMixedValues_180) {
    auto anyMatcher = AnyMatch(IsPositiveMatcher{});
    std::vector<int> values = {-5, -3, 0, -1};
    EXPECT_FALSE(anyMatcher.match(values));
}

// Test: AnyMatchMatcher with positive matcher has positive
TEST_F(AnyMatchMatcherTest_180, MatchesWithPositiveMatcherHasPositive_180) {
    auto anyMatcher = AnyMatch(IsPositiveMatcher{});
    std::vector<int> values = {-5, -3, 1, -1};
    EXPECT_TRUE(anyMatcher.match(values));
}
