#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <array>
#include <string>

// We need to include the actual Catch2 matchers headers
#include "catch2/matchers/catch_matchers_quantifiers.hpp"
#include "catch2/matchers/catch_matchers_predicate.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// Since we're testing Catch2's NoneMatchMatcher using Google Test,
// we need to create a simple element matcher to use with NoneMatchMatcher.
// We'll create a minimal matcher that conforms to the Catch2 matcher interface.

namespace {

// A simple matcher that matches if an element equals a given value
template <typename T>
struct EqualsMatcher : Catch::Matchers::MatcherGenericBase {
    T m_value;
    explicit EqualsMatcher(T value) : m_value(std::move(value)) {}
    
    template <typename U>
    bool match(U&& val) const {
        return val == m_value;
    }
    
    std::string describe() const override {
        return "equals " + std::to_string(m_value);
    }
};

// A matcher that matches if value is greater than threshold
struct GreaterThanMatcher : Catch::Matchers::MatcherGenericBase {
    int m_threshold;
    explicit GreaterThanMatcher(int threshold) : m_threshold(threshold) {}
    
    bool match(int val) const {
        return val > m_threshold;
    }
    
    std::string describe() const override {
        return "is greater than " + std::to_string(m_threshold);
    }
};

// A matcher that always returns true
struct AlwaysTrueMatcher : Catch::Matchers::MatcherGenericBase {
    template <typename T>
    bool match(T&&) const {
        return true;
    }
    
    std::string describe() const override {
        return "always true";
    }
};

// A matcher that always returns false
struct AlwaysFalseMatcher : Catch::Matchers::MatcherGenericBase {
    template <typename T>
    bool match(T&&) const {
        return false;
    }
    
    std::string describe() const override {
        return "always false";
    }
};

} // anonymous namespace

class NoneMatchMatcherTest_179 : public ::testing::Test {
protected:
    // Helper to create NoneMatchMatcher
    template <typename Matcher>
    auto makeNoneMatcher(Matcher m) {
        return Catch::Matchers::NoneMatchMatcher<Matcher>(std::move(m));
    }
};

// Test: Empty range should return true (no elements match anything)
TEST_F(NoneMatchMatcherTest_179, EmptyRangeReturnsTrue_179) {
    std::vector<int> empty;
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_TRUE(matcher.match(empty));
}

// Test: No elements match the inner matcher -> returns true
TEST_F(NoneMatchMatcherTest_179, NoElementsMatchReturnsTrue_179) {
    std::vector<int> data = {1, 2, 3, 4};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_TRUE(matcher.match(data));
}

// Test: One element matches the inner matcher -> returns false
TEST_F(NoneMatchMatcherTest_179, OneElementMatchesReturnsFalse_179) {
    std::vector<int> data = {1, 2, 5, 4};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_FALSE(matcher.match(data));
}

// Test: All elements match the inner matcher -> returns false
TEST_F(NoneMatchMatcherTest_179, AllElementsMatchReturnsFalse_179) {
    std::vector<int> data = {5, 5, 5, 5};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_FALSE(matcher.match(data));
}

// Test: Single element that doesn't match -> returns true
TEST_F(NoneMatchMatcherTest_179, SingleNonMatchingElementReturnsTrue_179) {
    std::vector<int> data = {3};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_TRUE(matcher.match(data));
}

// Test: Single element that matches -> returns false
TEST_F(NoneMatchMatcherTest_179, SingleMatchingElementReturnsFalse_179) {
    std::vector<int> data = {5};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_FALSE(matcher.match(data));
}

// Test: First element matches -> returns false immediately
TEST_F(NoneMatchMatcherTest_179, FirstElementMatchesReturnsFalse_179) {
    std::vector<int> data = {5, 1, 2, 3};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_FALSE(matcher.match(data));
}

// Test: Last element matches -> returns false
TEST_F(NoneMatchMatcherTest_179, LastElementMatchesReturnsFalse_179) {
    std::vector<int> data = {1, 2, 3, 5};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_FALSE(matcher.match(data));
}

// Test: Works with std::list
TEST_F(NoneMatchMatcherTest_179, WorksWithList_179) {
    std::list<int> data = {1, 2, 3, 4};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_TRUE(matcher.match(data));
}

// Test: Works with std::array
TEST_F(NoneMatchMatcherTest_179, WorksWithArray_179) {
    std::array<int, 4> data = {1, 2, 3, 4};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_TRUE(matcher.match(data));
}

// Test: Works with std::array where an element matches
TEST_F(NoneMatchMatcherTest_179, WorksWithArrayMatchingElement_179) {
    std::array<int, 4> data = {1, 5, 3, 4};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_FALSE(matcher.match(data));
}

// Test: AlwaysTrue inner matcher on non-empty range -> returns false
TEST_F(NoneMatchMatcherTest_179, AlwaysTrueMatcherNonEmptyReturnsFalse_179) {
    std::vector<int> data = {1, 2, 3};
    auto matcher = makeNoneMatcher(AlwaysTrueMatcher{});
    EXPECT_FALSE(matcher.match(data));
}

// Test: AlwaysTrue inner matcher on empty range -> returns true
TEST_F(NoneMatchMatcherTest_179, AlwaysTrueMatcherEmptyReturnsTrue_179) {
    std::vector<int> empty;
    auto matcher = makeNoneMatcher(AlwaysTrueMatcher{});
    EXPECT_TRUE(matcher.match(empty));
}

// Test: AlwaysFalse inner matcher -> returns true for any range
TEST_F(NoneMatchMatcherTest_179, AlwaysFalseMatcherReturnsTrue_179) {
    std::vector<int> data = {1, 2, 3, 4, 5};
    auto matcher = makeNoneMatcher(AlwaysFalseMatcher{});
    EXPECT_TRUE(matcher.match(data));
}

// Test: GreaterThan matcher with no elements above threshold
TEST_F(NoneMatchMatcherTest_179, GreaterThanNoneAboveThreshold_179) {
    std::vector<int> data = {1, 2, 3, 4, 5};
    auto matcher = makeNoneMatcher(GreaterThanMatcher(10));
    EXPECT_TRUE(matcher.match(data));
}

// Test: GreaterThan matcher with some elements above threshold
TEST_F(NoneMatchMatcherTest_179, GreaterThanSomeAboveThreshold_179) {
    std::vector<int> data = {1, 2, 15, 4, 5};
    auto matcher = makeNoneMatcher(GreaterThanMatcher(10));
    EXPECT_FALSE(matcher.match(data));
}

// Test: Large range with no matches -> returns true
TEST_F(NoneMatchMatcherTest_179, LargeRangeNoMatch_179) {
    std::vector<int> data(10000, 1);
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_TRUE(matcher.match(data));
}

// Test: Large range with match at the end -> returns false
TEST_F(NoneMatchMatcherTest_179, LargeRangeMatchAtEnd_179) {
    std::vector<int> data(10000, 1);
    data.back() = 5;
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_FALSE(matcher.match(data));
}

// Test: describe() returns a non-empty string
TEST_F(NoneMatchMatcherTest_179, DescribeReturnsNonEmptyString_179) {
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test: Works with C-style array via initializer_list or wrapper
TEST_F(NoneMatchMatcherTest_179, WorksWithInitializerListLikeRange_179) {
    int arr[] = {1, 2, 3, 4};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_TRUE(matcher.match(arr));
}

// Test: Works with C-style array that has a match
TEST_F(NoneMatchMatcherTest_179, CStyleArrayWithMatch_179) {
    int arr[] = {1, 5, 3, 4};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_FALSE(matcher.match(arr));
}

// Test: Works with negative numbers
TEST_F(NoneMatchMatcherTest_179, NegativeNumbersNoMatch_179) {
    std::vector<int> data = {-1, -2, -3, -4};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(0));
    EXPECT_TRUE(matcher.match(data));
}

// Test: Works with negative numbers where one matches
TEST_F(NoneMatchMatcherTest_179, NegativeNumbersWithMatch_179) {
    std::vector<int> data = {-1, -2, 0, -4};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(0));
    EXPECT_FALSE(matcher.match(data));
}

// Test: Boundary - matching value is at both ends
TEST_F(NoneMatchMatcherTest_179, MatchAtBothEnds_179) {
    std::vector<int> data = {5, 1, 2, 3, 5};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_FALSE(matcher.match(data));
}

// Test: Multiple different matching elements
TEST_F(NoneMatchMatcherTest_179, MultipleMatchingElements_179) {
    std::vector<int> data = {5, 5, 5};
    auto matcher = makeNoneMatcher(EqualsMatcher<int>(5));
    EXPECT_FALSE(matcher.match(data));
}
