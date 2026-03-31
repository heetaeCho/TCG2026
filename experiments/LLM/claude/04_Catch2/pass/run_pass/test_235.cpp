#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>
#include <array>
#include <deque>

// Include Catch2 headers for matchers
#include "catch2/matchers/catch_matchers_container_properties.hpp"
#include "catch2/matchers/catch_matchers.hpp"
#include "catch2/matchers/catch_matchers_predicate.hpp"
#include "catch2/matchers/catch_matchers_quantifiers.hpp"

// We need to test the Catch2 SizeIs matcher functionality.
// Since this is Catch2's matcher, we'll test it by using the matcher's
// match() and describe() methods directly, rather than through Catch2's
// REQUIRE_THAT macro.

// Helper: a simple matcher that checks equality to a value
// We'll use Catch2's own matchers as the inner matcher for SizeIs

namespace {

// A simple custom Catch2 matcher for testing purposes
class EqualsMatcher final : public Catch::Matchers::MatcherBase<size_t> {
    size_t m_expected;
public:
    explicit EqualsMatcher(size_t expected) : m_expected(expected) {}
    bool match(size_t const& actual) const override {
        return actual == m_expected;
    }
    std::string describe() const override {
        return "equals " + std::to_string(m_expected);
    }
};

class GreaterThanMatcher final : public Catch::Matchers::MatcherBase<size_t> {
    size_t m_threshold;
public:
    explicit GreaterThanMatcher(size_t threshold) : m_threshold(threshold) {}
    bool match(size_t const& actual) const override {
        return actual > m_threshold;
    }
    std::string describe() const override {
        return "is greater than " + std::to_string(m_threshold);
    }
};

class LessThanMatcher final : public Catch::Matchers::MatcherBase<size_t> {
    size_t m_threshold;
public:
    explicit LessThanMatcher(size_t threshold) : m_threshold(threshold) {}
    bool match(size_t const& actual) const override {
        return actual < m_threshold;
    }
    std::string describe() const override {
        return "is less than " + std::to_string(m_threshold);
    }
};

} // anonymous namespace

// Test fixture
class SizeIsMatcherTest_235 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Normal operation tests
// ============================================================

TEST_F(SizeIsMatcherTest_235, VectorMatchesExactSize_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(3));
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeIsMatcherTest_235, VectorDoesNotMatchWrongSize_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(3));
    std::vector<int> v = {1, 2};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(SizeIsMatcherTest_235, EmptyVectorMatchesSizeZero_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(0));
    std::vector<int> v;
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeIsMatcherTest_235, EmptyVectorDoesNotMatchNonZeroSize_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(1));
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(SizeIsMatcherTest_235, StringMatchesSize_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(5));
    std::string s = "hello";
    EXPECT_TRUE(matcher.match(s));
}

TEST_F(SizeIsMatcherTest_235, StringDoesNotMatchWrongSize_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(3));
    std::string s = "hello";
    EXPECT_FALSE(matcher.match(s));
}

TEST_F(SizeIsMatcherTest_235, EmptyStringMatchesSizeZero_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(0));
    std::string s;
    EXPECT_TRUE(matcher.match(s));
}

TEST_F(SizeIsMatcherTest_235, ListMatchesSize_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(4));
    std::list<double> l = {1.0, 2.0, 3.0, 4.0};
    EXPECT_TRUE(matcher.match(l));
}

TEST_F(SizeIsMatcherTest_235, ListDoesNotMatchWrongSize_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(2));
    std::list<double> l = {1.0, 2.0, 3.0, 4.0};
    EXPECT_FALSE(matcher.match(l));
}

TEST_F(SizeIsMatcherTest_235, MapMatchesSize_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(2));
    std::map<int, std::string> m = {{1, "a"}, {2, "b"}};
    EXPECT_TRUE(matcher.match(m));
}

TEST_F(SizeIsMatcherTest_235, SetMatchesSize_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(3));
    std::set<int> s = {10, 20, 30};
    EXPECT_TRUE(matcher.match(s));
}

TEST_F(SizeIsMatcherTest_235, DequeMatchesSize_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(2));
    std::deque<int> d = {1, 2};
    EXPECT_TRUE(matcher.match(d));
}

// ============================================================
// Tests with GreaterThan matcher
// ============================================================

TEST_F(SizeIsMatcherTest_235, VectorSizeGreaterThanThreshold_235) {
    auto matcher = Catch::Matchers::SizeIs(GreaterThanMatcher(2));
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeIsMatcherTest_235, VectorSizeNotGreaterThanThreshold_235) {
    auto matcher = Catch::Matchers::SizeIs(GreaterThanMatcher(3));
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(SizeIsMatcherTest_235, VectorSizeEqualToThresholdNotGreater_235) {
    auto matcher = Catch::Matchers::SizeIs(GreaterThanMatcher(3));
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

// ============================================================
// Tests with LessThan matcher
// ============================================================

TEST_F(SizeIsMatcherTest_235, VectorSizeLessThanThreshold_235) {
    auto matcher = Catch::Matchers::SizeIs(LessThanMatcher(5));
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeIsMatcherTest_235, VectorSizeNotLessThanThreshold_235) {
    auto matcher = Catch::Matchers::SizeIs(LessThanMatcher(2));
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

// ============================================================
// Boundary condition tests
// ============================================================

TEST_F(SizeIsMatcherTest_235, SingleElementVectorMatchesSizeOne_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(1));
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeIsMatcherTest_235, LargeVectorMatchesSize_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(1000));
    std::vector<int> v(1000, 0);
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeIsMatcherTest_235, LargeVectorDoesNotMatchWrongSize_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(999));
    std::vector<int> v(1000, 0);
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(SizeIsMatcherTest_235, EmptyContainerGreaterThanZeroFails_235) {
    auto matcher = Catch::Matchers::SizeIs(GreaterThanMatcher(0));
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(SizeIsMatcherTest_235, EmptyContainerLessThanOnePasses_235) {
    auto matcher = Catch::Matchers::SizeIs(LessThanMatcher(1));
    std::vector<int> v;
    EXPECT_TRUE(matcher.match(v));
}

// ============================================================
// describe() tests
// ============================================================

TEST_F(SizeIsMatcherTest_235, DescribeContainsSizeInformation_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(5));
    std::string description = matcher.describe();
    // The description should contain something meaningful about size
    EXPECT_FALSE(description.empty());
}

TEST_F(SizeIsMatcherTest_235, DescribeContainsInnerMatcherDescription_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(42));
    std::string description = matcher.describe();
    // The description should incorporate the inner matcher's description
    // which includes "equals 42"
    EXPECT_NE(description.find("42"), std::string::npos);
}

// ============================================================
// Tests with different element types
// ============================================================

TEST_F(SizeIsMatcherTest_235, VectorOfStringsMatchesSize_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(2));
    std::vector<std::string> v = {"hello", "world"};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeIsMatcherTest_235, VectorOfVectorsMatchesSize_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(3));
    std::vector<std::vector<int>> v = {{1}, {2, 3}, {4, 5, 6}};
    EXPECT_TRUE(matcher.match(v));
}

// ============================================================
// Test that SizeIs works correctly after container modification
// ============================================================

TEST_F(SizeIsMatcherTest_235, MatcherWorksAfterContainerGrows_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(3));
    std::vector<int> v = {1, 2};
    EXPECT_FALSE(matcher.match(v));
    v.push_back(3);
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(SizeIsMatcherTest_235, MatcherWorksAfterContainerShrinks_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(1));
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
    v.resize(1);
    EXPECT_TRUE(matcher.match(v));
}

// ============================================================
// Test reusability of the matcher
// ============================================================

TEST_F(SizeIsMatcherTest_235, MatcherCanBeReusedMultipleTimes_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(2));
    
    std::vector<int> v1 = {1, 2};
    std::vector<int> v2 = {3, 4};
    std::vector<int> v3 = {5};
    
    EXPECT_TRUE(matcher.match(v1));
    EXPECT_TRUE(matcher.match(v2));
    EXPECT_FALSE(matcher.match(v3));
}

TEST_F(SizeIsMatcherTest_235, SameMatcherDifferentContainerTypes_235) {
    auto matcher = Catch::Matchers::SizeIs(EqualsMatcher(2));
    
    std::vector<int> v = {1, 2};
    EXPECT_TRUE(matcher.match(v));
    
    std::string s = "ab";
    EXPECT_TRUE(matcher.match(s));
    
    std::list<float> l = {1.0f, 2.0f};
    EXPECT_TRUE(matcher.match(l));
}
