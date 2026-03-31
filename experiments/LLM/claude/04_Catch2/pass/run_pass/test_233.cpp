#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <array>
#include <list>
#include <set>
#include <map>
#include <deque>

// Include the header under test
#include "catch2/matchers/catch_matchers_container_properties.hpp"
#include "catch2/matchers/catch_matchers_templated.hpp"

// We need a simple matcher that can be used as the inner matcher for SizeMatchesMatcher.
// Since we're testing SizeMatchesMatcher's match() method, we need a matcher that
// matches against a size_t value.

// A simple custom matcher that checks equality against a given size value
// This is used as the inner matcher for SizeMatchesMatcher
namespace {

class EqualsSizeMatcher : public Catch::Matchers::MatcherGenericBase {
    std::size_t m_expected;
public:
    explicit EqualsSizeMatcher(std::size_t expected) : m_expected(expected) {}

    bool match(std::size_t actual) const {
        return actual == m_expected;
    }

    std::string describe() const override {
        return "equals size " + std::to_string(m_expected);
    }
};

class GreaterThanSizeMatcher : public Catch::Matchers::MatcherGenericBase {
    std::size_t m_threshold;
public:
    explicit GreaterThanSizeMatcher(std::size_t threshold) : m_threshold(threshold) {}

    bool match(std::size_t actual) const {
        return actual > m_threshold;
    }

    std::string describe() const override {
        return "size greater than " + std::to_string(m_threshold);
    }
};

class LessThanSizeMatcher : public Catch::Matchers::MatcherGenericBase {
    std::size_t m_threshold;
public:
    explicit LessThanSizeMatcher(std::size_t threshold) : m_threshold(threshold) {}

    bool match(std::size_t actual) const {
        return actual < m_threshold;
    }

    std::string describe() const override {
        return "size less than " + std::to_string(m_threshold);
    }
};

} // anonymous namespace

class SizeMatchesMatcherTest_233 : public ::testing::Test {
protected:
    // Helper to create a SizeMatchesMatcher with an equals-size inner matcher
    auto makeEqualsSizeMatcher(std::size_t expected) {
        return Catch::Matchers::SizeMatchesMatcher<EqualsSizeMatcher>(EqualsSizeMatcher(expected));
    }

    auto makeGreaterThanSizeMatcher(std::size_t threshold) {
        return Catch::Matchers::SizeMatchesMatcher<GreaterThanSizeMatcher>(GreaterThanSizeMatcher(threshold));
    }

    auto makeLessThanSizeMatcher(std::size_t threshold) {
        return Catch::Matchers::SizeMatchesMatcher<LessThanSizeMatcher>(LessThanSizeMatcher(threshold));
    }
};

// ==================== Normal Operation Tests ====================

TEST_F(SizeMatchesMatcherTest_233, MatchesVectorWithCorrectSize_233) {
    auto matcher = makeEqualsSizeMatcher(3);
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeMatchesMatcherTest_233, DoesNotMatchVectorWithIncorrectSize_233) {
    auto matcher = makeEqualsSizeMatcher(5);
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(SizeMatchesMatcherTest_233, MatchesStringWithCorrectSize_233) {
    auto matcher = makeEqualsSizeMatcher(5);
    std::string s = "hello";
    EXPECT_TRUE(matcher.match(s));
}

TEST_F(SizeMatchesMatcherTest_233, DoesNotMatchStringWithIncorrectSize_233) {
    auto matcher = makeEqualsSizeMatcher(3);
    std::string s = "hello";
    EXPECT_FALSE(matcher.match(s));
}

TEST_F(SizeMatchesMatcherTest_233, MatchesListWithCorrectSize_233) {
    auto matcher = makeEqualsSizeMatcher(4);
    std::list<double> l = {1.0, 2.0, 3.0, 4.0};
    EXPECT_TRUE(matcher.match(l));
}

TEST_F(SizeMatchesMatcherTest_233, MatchesSetWithCorrectSize_233) {
    auto matcher = makeEqualsSizeMatcher(3);
    std::set<int> s = {10, 20, 30};
    EXPECT_TRUE(matcher.match(s));
}

TEST_F(SizeMatchesMatcherTest_233, MatchesMapWithCorrectSize_233) {
    auto matcher = makeEqualsSizeMatcher(2);
    std::map<int, std::string> m = {{1, "a"}, {2, "b"}};
    EXPECT_TRUE(matcher.match(m));
}

TEST_F(SizeMatchesMatcherTest_233, MatchesDequeWithCorrectSize_233) {
    auto matcher = makeEqualsSizeMatcher(3);
    std::deque<int> d = {1, 2, 3};
    EXPECT_TRUE(matcher.match(d));
}

TEST_F(SizeMatchesMatcherTest_233, MatchesArrayWithCorrectSize_233) {
    auto matcher = makeEqualsSizeMatcher(4);
    std::array<int, 4> arr = {1, 2, 3, 4};
    EXPECT_TRUE(matcher.match(arr));
}

TEST_F(SizeMatchesMatcherTest_233, DoesNotMatchArrayWithIncorrectSize_233) {
    auto matcher = makeEqualsSizeMatcher(3);
    std::array<int, 4> arr = {1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(arr));
}

// ==================== Boundary Condition Tests ====================

TEST_F(SizeMatchesMatcherTest_233, MatchesEmptyVector_233) {
    auto matcher = makeEqualsSizeMatcher(0);
    std::vector<int> v;
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeMatchesMatcherTest_233, DoesNotMatchEmptyVectorWithNonZeroExpected_233) {
    auto matcher = makeEqualsSizeMatcher(1);
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(SizeMatchesMatcherTest_233, MatchesEmptyString_233) {
    auto matcher = makeEqualsSizeMatcher(0);
    std::string s;
    EXPECT_TRUE(matcher.match(s));
}

TEST_F(SizeMatchesMatcherTest_233, MatchesEmptyMap_233) {
    auto matcher = makeEqualsSizeMatcher(0);
    std::map<int, int> m;
    EXPECT_TRUE(matcher.match(m));
}

TEST_F(SizeMatchesMatcherTest_233, MatchesSingleElementVector_233) {
    auto matcher = makeEqualsSizeMatcher(1);
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeMatchesMatcherTest_233, MatchesLargeVector_233) {
    auto matcher = makeEqualsSizeMatcher(10000);
    std::vector<int> v(10000, 0);
    EXPECT_TRUE(matcher.match(v));
}

// ==================== Tests with GreaterThan inner matcher ====================

TEST_F(SizeMatchesMatcherTest_233, GreaterThanMatchesWhenSizeIsLarger_233) {
    auto matcher = makeGreaterThanSizeMatcher(2);
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeMatchesMatcherTest_233, GreaterThanDoesNotMatchWhenSizeIsEqual_233) {
    auto matcher = makeGreaterThanSizeMatcher(3);
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(SizeMatchesMatcherTest_233, GreaterThanDoesNotMatchWhenSizeIsSmaller_233) {
    auto matcher = makeGreaterThanSizeMatcher(5);
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(SizeMatchesMatcherTest_233, GreaterThanDoesNotMatchEmptyContainer_233) {
    auto matcher = makeGreaterThanSizeMatcher(0);
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

// ==================== Tests with LessThan inner matcher ====================

TEST_F(SizeMatchesMatcherTest_233, LessThanMatchesWhenSizeIsSmaller_233) {
    auto matcher = makeLessThanSizeMatcher(5);
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeMatchesMatcherTest_233, LessThanDoesNotMatchWhenSizeIsEqual_233) {
    auto matcher = makeLessThanSizeMatcher(3);
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(SizeMatchesMatcherTest_233, LessThanDoesNotMatchWhenSizeIsLarger_233) {
    auto matcher = makeLessThanSizeMatcher(2);
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(SizeMatchesMatcherTest_233, LessThanMatchesEmptyContainer_233) {
    auto matcher = makeLessThanSizeMatcher(1);
    std::vector<int> v;
    EXPECT_TRUE(matcher.match(v));
}

// ==================== Const container tests ====================

TEST_F(SizeMatchesMatcherTest_233, MatchesConstVector_233) {
    auto matcher = makeEqualsSizeMatcher(3);
    const std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeMatchesMatcherTest_233, MatchesConstString_233) {
    auto matcher = makeEqualsSizeMatcher(4);
    const std::string s = "test";
    EXPECT_TRUE(matcher.match(s));
}

// ==================== Rvalue reference tests ====================

TEST_F(SizeMatchesMatcherTest_233, MatchesRvalueVector_233) {
    auto matcher = makeEqualsSizeMatcher(2);
    EXPECT_TRUE(matcher.match(std::vector<int>{10, 20}));
}

TEST_F(SizeMatchesMatcherTest_233, MatchesRvalueString_233) {
    auto matcher = makeEqualsSizeMatcher(3);
    EXPECT_TRUE(matcher.match(std::string("abc")));
}

// ==================== Describe tests ====================

TEST_F(SizeMatchesMatcherTest_233, DescribeReturnsNonEmptyString_233) {
    auto matcher = makeEqualsSizeMatcher(5);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

TEST_F(SizeMatchesMatcherTest_233, DescribeContainsSizeInfo_233) {
    auto matcher = makeEqualsSizeMatcher(5);
    std::string description = matcher.describe();
    // The description should mention something about size
    // We can't know the exact format, but it should not be empty
    EXPECT_GT(description.length(), 0u);
}

// ==================== Different element types ====================

TEST_F(SizeMatchesMatcherTest_233, MatchesVectorOfStrings_233) {
    auto matcher = makeEqualsSizeMatcher(2);
    std::vector<std::string> v = {"hello", "world"};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeMatchesMatcherTest_233, MatchesVectorOfVectors_233) {
    auto matcher = makeEqualsSizeMatcher(3);
    std::vector<std::vector<int>> v = {{1}, {2, 3}, {4, 5, 6}};
    EXPECT_TRUE(matcher.match(v));
}

// ==================== Set with duplicates (size validation) ====================

TEST_F(SizeMatchesMatcherTest_233, SetIgnoresDuplicatesInSize_233) {
    auto matcher = makeEqualsSizeMatcher(3);
    std::set<int> s = {1, 2, 3, 3, 3}; // duplicates are ignored in set
    EXPECT_TRUE(matcher.match(s));
}
