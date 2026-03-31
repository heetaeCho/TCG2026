#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>
#include <array>
#include <set>
#include <map>
#include <deque>

// Include Catch2 matchers
#include "catch2/matchers/catch_matchers_container_properties.hpp"
#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// We need some basic Catch2 matchers to use as the inner matcher
// For size comparison, we'll use predicates or equality matchers
#include "catch2/matchers/catch_matchers_predicate.hpp"
#include "catch2/matchers/catch_matchers_quantifiers.hpp"

// A simple custom matcher for testing purposes that matches against an exact size value
namespace {

struct EqualsMatcher : Catch::Matchers::MatcherGenericBase {
    std::size_t m_expected;
    explicit EqualsMatcher(std::size_t expected) : m_expected(expected) {}
    
    bool match(std::size_t actual) const {
        return actual == m_expected;
    }
    
    std::string describe() const override {
        return "equals " + std::to_string(m_expected);
    }
};

struct GreaterThanMatcher : Catch::Matchers::MatcherGenericBase {
    std::size_t m_threshold;
    explicit GreaterThanMatcher(std::size_t threshold) : m_threshold(threshold) {}
    
    bool match(std::size_t actual) const {
        return actual > m_threshold;
    }
    
    std::string describe() const override {
        return "is greater than " + std::to_string(m_threshold);
    }
};

struct LessThanMatcher : Catch::Matchers::MatcherGenericBase {
    std::size_t m_threshold;
    explicit LessThanMatcher(std::size_t threshold) : m_threshold(threshold) {}
    
    bool match(std::size_t actual) const {
        return actual < m_threshold;
    }
    
    std::string describe() const override {
        return "is less than " + std::to_string(m_threshold);
    }
};

} // anonymous namespace

class SizeMatchesMatcherTest_234 : public ::testing::Test {
protected:
    // Helper to create SizeMatchesMatcher
};

// Test: Match succeeds when vector size equals expected
TEST_F(SizeMatchesMatcherTest_234, MatchesExactSizeForVector_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(3));
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

// Test: Match fails when vector size does not equal expected
TEST_F(SizeMatchesMatcherTest_234, DoesNotMatchWrongSizeForVector_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(3));
    std::vector<int> v = {1, 2};
    EXPECT_FALSE(matcher.match(v));
}

// Test: Match succeeds for empty container with size 0
TEST_F(SizeMatchesMatcherTest_234, MatchesEmptyContainer_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(0));
    std::vector<int> v;
    EXPECT_TRUE(matcher.match(v));
}

// Test: Match fails for empty container when expecting non-zero
TEST_F(SizeMatchesMatcherTest_234, DoesNotMatchEmptyContainerForNonZero_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(5));
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

// Test: Works with std::string as a range-like type
TEST_F(SizeMatchesMatcherTest_234, MatchesStringSize_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(5));
    std::string s = "hello";
    EXPECT_TRUE(matcher.match(s));
}

// Test: Works with std::list
TEST_F(SizeMatchesMatcherTest_234, MatchesListSize_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(4));
    std::list<double> l = {1.0, 2.0, 3.0, 4.0};
    EXPECT_TRUE(matcher.match(l));
}

// Test: Works with std::set
TEST_F(SizeMatchesMatcherTest_234, MatchesSetSize_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(3));
    std::set<int> s = {10, 20, 30};
    EXPECT_TRUE(matcher.match(s));
}

// Test: Works with std::map
TEST_F(SizeMatchesMatcherTest_234, MatchesMapSize_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(2));
    std::map<int, std::string> m = {{1, "a"}, {2, "b"}};
    EXPECT_TRUE(matcher.match(m));
}

// Test: Works with std::array
TEST_F(SizeMatchesMatcherTest_234, MatchesArraySize_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(3));
    std::array<int, 3> a = {1, 2, 3};
    EXPECT_TRUE(matcher.match(a));
}

// Test: Works with std::deque
TEST_F(SizeMatchesMatcherTest_234, MatchesDequeSize_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(2));
    std::deque<int> d = {1, 2};
    EXPECT_TRUE(matcher.match(d));
}

// Test: GreaterThan matcher - size is greater
TEST_F(SizeMatchesMatcherTest_234, MatchesSizeGreaterThan_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<GreaterThanMatcher>(GreaterThanMatcher(2));
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

// Test: GreaterThan matcher - size is not greater
TEST_F(SizeMatchesMatcherTest_234, DoesNotMatchSizeNotGreaterThan_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<GreaterThanMatcher>(GreaterThanMatcher(5));
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

// Test: LessThan matcher - size is less
TEST_F(SizeMatchesMatcherTest_234, MatchesSizeLessThan_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<LessThanMatcher>(LessThanMatcher(5));
    std::vector<int> v = {1, 2};
    EXPECT_TRUE(matcher.match(v));
}

// Test: LessThan matcher - size is not less
TEST_F(SizeMatchesMatcherTest_234, DoesNotMatchSizeNotLessThan_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<LessThanMatcher>(LessThanMatcher(2));
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

// Test: Describe returns expected string format
TEST_F(SizeMatchesMatcherTest_234, DescribeContainsInnerMatcherDescription_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(3));
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("size matches"), std::string::npos);
    EXPECT_NE(desc.find("equals 3"), std::string::npos);
}

// Test: Describe with GreaterThan matcher
TEST_F(SizeMatchesMatcherTest_234, DescribeWithGreaterThanMatcher_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<GreaterThanMatcher>(GreaterThanMatcher(10));
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("size matches"), std::string::npos);
    EXPECT_NE(desc.find("is greater than 10"), std::string::npos);
}

// Test: Boundary - single element container matching size 1
TEST_F(SizeMatchesMatcherTest_234, MatchesSingleElementContainer_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(1));
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

// Test: Boundary - GreaterThan 0 with non-empty container
TEST_F(SizeMatchesMatcherTest_234, GreaterThanZeroWithNonEmpty_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<GreaterThanMatcher>(GreaterThanMatcher(0));
    std::vector<int> v = {1};
    EXPECT_TRUE(matcher.match(v));
}

// Test: Boundary - GreaterThan 0 with empty container
TEST_F(SizeMatchesMatcherTest_234, GreaterThanZeroWithEmpty_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<GreaterThanMatcher>(GreaterThanMatcher(0));
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

// Test: Match with const container reference
TEST_F(SizeMatchesMatcherTest_234, MatchesConstContainer_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(3));
    const std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

// Test: Large container
TEST_F(SizeMatchesMatcherTest_234, MatchesLargeContainer_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(1000));
    std::vector<int> v(1000, 0);
    EXPECT_TRUE(matcher.match(v));
}

// Test: Large container does not match wrong size
TEST_F(SizeMatchesMatcherTest_234, DoesNotMatchLargeContainerWrongSize_234) {
    auto matcher = Catch::Matchers::SizeMatchesMatcher<EqualsMatcher>(EqualsMatcher(999));
    std::vector<int> v(1000, 0);
    EXPECT_FALSE(matcher.match(v));
}
