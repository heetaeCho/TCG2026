#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>
#include <array>

// Include Catch2 matchers
#include "catch2/matchers/catch_matchers_quantifiers.hpp"
#include "catch2/matchers/catch_matchers_predicate.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// We need to test NoneMatchMatcher through its public interface:
// - describe() returns a string
// - match(RangeLike&&) returns bool

// Helper: A simple predicate matcher for testing
// We'll use Catch::Matchers::Predicate if available, or create a minimal matcher

namespace {

// A minimal matcher that matches if value equals a target
template <typename T>
class EqualsMatcher : public Catch::Matchers::MatcherGenericBase {
    T m_target;
public:
    explicit EqualsMatcher(T target) : m_target(std::move(target)) {}

    template <typename U>
    bool match(U const& value) const {
        return value == m_target;
    }

    std::string describe() const override {
        return "equals target";
    }
};

// A matcher that always matches
class AlwaysTrueMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    template <typename T>
    bool match(T const&) const {
        return true;
    }

    std::string describe() const override {
        return "is always true";
    }
};

// A matcher that never matches
class AlwaysFalseMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    template <typename T>
    bool match(T const&) const {
        return false;
    }

    std::string describe() const override {
        return "is always false";
    }
};

// A matcher that checks if value is positive
class IsPositiveMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    template <typename T>
    bool match(T const& value) const {
        return value > 0;
    }

    std::string describe() const override {
        return "is positive";
    }
};

} // anonymous namespace

class NoneMatchMatcherTest_178 : public ::testing::Test {
protected:
};

// Test: NoneMatch returns true when no elements match
TEST_F(NoneMatchMatcherTest_178, ReturnsTrueWhenNoElementsMatch_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(99));
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

// Test: NoneMatch returns false when at least one element matches
TEST_F(NoneMatchMatcherTest_178, ReturnsFalseWhenOneElementMatches_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(3));
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

// Test: NoneMatch returns false when all elements match
TEST_F(NoneMatchMatcherTest_178, ReturnsFalseWhenAllElementsMatch_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<AlwaysTrueMatcher>(AlwaysTrueMatcher{});
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

// Test: NoneMatch returns true when all elements don't match (AlwaysFalse)
TEST_F(NoneMatchMatcherTest_178, ReturnsTrueWhenNoElementsMatchAlwaysFalse_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<AlwaysFalseMatcher>(AlwaysFalseMatcher{});
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

// Test: NoneMatch on empty container returns true
TEST_F(NoneMatchMatcherTest_178, ReturnsTrueForEmptyContainer_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<AlwaysTrueMatcher>(AlwaysTrueMatcher{});
    std::vector<int> v = {};
    EXPECT_TRUE(matcher.match(v));
}

// Test: NoneMatch on single element that matches returns false
TEST_F(NoneMatchMatcherTest_178, ReturnsFalseForSingleMatchingElement_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(42));
    std::vector<int> v = {42};
    EXPECT_FALSE(matcher.match(v));
}

// Test: NoneMatch on single element that doesn't match returns true
TEST_F(NoneMatchMatcherTest_178, ReturnsTrueForSingleNonMatchingElement_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(42));
    std::vector<int> v = {7};
    EXPECT_TRUE(matcher.match(v));
}

// Test: NoneMatch works with std::list
TEST_F(NoneMatchMatcherTest_178, WorksWithStdList_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(5));
    std::list<int> lst = {1, 2, 3, 4};
    EXPECT_TRUE(matcher.match(lst));
}

// Test: NoneMatch works with std::list containing matching element
TEST_F(NoneMatchMatcherTest_178, ReturnsFalseWithStdListContainingMatch_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(3));
    std::list<int> lst = {1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(lst));
}

// Test: NoneMatch works with std::array
TEST_F(NoneMatchMatcherTest_178, WorksWithStdArray_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<IsPositiveMatcher>(IsPositiveMatcher{});
    std::array<int, 3> arr = {-1, -2, -3};
    EXPECT_TRUE(matcher.match(arr));
}

// Test: NoneMatch with std::array containing positive element
TEST_F(NoneMatchMatcherTest_178, ReturnsFalseWithStdArrayContainingPositive_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<IsPositiveMatcher>(IsPositiveMatcher{});
    std::array<int, 3> arr = {-1, 2, -3};
    EXPECT_FALSE(matcher.match(arr));
}

// Test: describe() returns expected string format
TEST_F(NoneMatchMatcherTest_178, DescribeReturnsExpectedString_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<AlwaysTrueMatcher>(AlwaysTrueMatcher{});
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("none match"), std::string::npos);
    EXPECT_NE(desc.find("is always true"), std::string::npos);
}

// Test: describe() includes inner matcher description
TEST_F(NoneMatchMatcherTest_178, DescribeIncludesInnerMatcherDescription_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<IsPositiveMatcher>(IsPositiveMatcher{});
    std::string desc = matcher.describe();
    EXPECT_EQ(desc, "none match is positive");
}

// Test: NoneMatch with strings
TEST_F(NoneMatchMatcherTest_178, WorksWithStringVector_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<EqualsMatcher<std::string>>(EqualsMatcher<std::string>("hello"));
    std::vector<std::string> v = {"world", "foo", "bar"};
    EXPECT_TRUE(matcher.match(v));
}

// Test: NoneMatch with strings containing match
TEST_F(NoneMatchMatcherTest_178, ReturnsFalseWithStringVectorContainingMatch_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<EqualsMatcher<std::string>>(EqualsMatcher<std::string>("hello"));
    std::vector<std::string> v = {"world", "hello", "bar"};
    EXPECT_FALSE(matcher.match(v));
}

// Test: NoneMatch returns false when only first element matches
TEST_F(NoneMatchMatcherTest_178, ReturnsFalseWhenFirstElementMatches_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(1));
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

// Test: NoneMatch returns false when only last element matches
TEST_F(NoneMatchMatcherTest_178, ReturnsFalseWhenLastElementMatches_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(5));
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

// Test: NoneMatch with empty array
TEST_F(NoneMatchMatcherTest_178, ReturnsTrueForEmptyArray_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<AlwaysTrueMatcher>(AlwaysTrueMatcher{});
    std::array<int, 0> arr = {};
    EXPECT_TRUE(matcher.match(arr));
}

// Test: NoneMatch with large container where no elements match
TEST_F(NoneMatchMatcherTest_178, ReturnsTrueForLargeContainerNoMatch_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(-1));
    std::vector<int> v(1000, 0);
    EXPECT_TRUE(matcher.match(v));
}

// Test: NoneMatch with large container where one element matches (at end)
TEST_F(NoneMatchMatcherTest_178, ReturnsFalseForLargeContainerOneMatchAtEnd_178) {
    auto matcher = Catch::Matchers::NoneMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(-1));
    std::vector<int> v(1000, 0);
    v.back() = -1;
    EXPECT_FALSE(matcher.match(v));
}
