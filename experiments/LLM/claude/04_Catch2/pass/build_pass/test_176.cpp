#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <array>
#include <list>

#include "catch2/matchers/catch_matchers_quantifiers.hpp"
#include "catch2/matchers/catch_matchers_predicate.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// A simple custom matcher for testing purposes
class IsPositiveMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    bool match(int val) const {
        return val > 0;
    }
    std::string describe() const override {
        return "is positive";
    }
};

class IsEvenMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    bool match(int val) const {
        return val % 2 == 0;
    }
    std::string describe() const override {
        return "is even";
    }
};

class IsNonEmptyStringMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    bool match(const std::string& val) const {
        return !val.empty();
    }
    std::string describe() const override {
        return "is non-empty string";
    }
};

// Test fixture
class AllMatchMatcherTest_176 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test describe() returns the expected string
TEST_F(AllMatchMatcherTest_176, DescribeReturnsCorrectString_176) {
    IsPositiveMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsPositiveMatcher> matcher(inner);
    std::string description = matcher.describe();
    EXPECT_EQ(description, "all match is positive");
}

TEST_F(AllMatchMatcherTest_176, DescribeWithEvenMatcher_176) {
    IsEvenMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsEvenMatcher> matcher(inner);
    std::string description = matcher.describe();
    EXPECT_EQ(description, "all match is even");
}

TEST_F(AllMatchMatcherTest_176, DescribeWithStringMatcher_176) {
    IsNonEmptyStringMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsNonEmptyStringMatcher> matcher(inner);
    std::string description = matcher.describe();
    EXPECT_EQ(description, "all match is non-empty string");
}

// Test match() with all elements matching
TEST_F(AllMatchMatcherTest_176, AllElementsMatchReturnsTrue_176) {
    IsPositiveMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsPositiveMatcher> matcher(inner);
    std::vector<int> values = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(values));
}

// Test match() with no elements matching
TEST_F(AllMatchMatcherTest_176, NoElementsMatchReturnsFalse_176) {
    IsPositiveMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsPositiveMatcher> matcher(inner);
    std::vector<int> values = {-1, -2, -3};
    EXPECT_FALSE(matcher.match(values));
}

// Test match() with some elements matching
TEST_F(AllMatchMatcherTest_176, SomeElementsMatchReturnsFalse_176) {
    IsPositiveMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsPositiveMatcher> matcher(inner);
    std::vector<int> values = {1, -2, 3};
    EXPECT_FALSE(matcher.match(values));
}

// Test match() with empty range - should return true (vacuous truth)
TEST_F(AllMatchMatcherTest_176, EmptyRangeReturnsTrue_176) {
    IsPositiveMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsPositiveMatcher> matcher(inner);
    std::vector<int> values = {};
    EXPECT_TRUE(matcher.match(values));
}

// Test match() with single element matching
TEST_F(AllMatchMatcherTest_176, SingleMatchingElementReturnsTrue_176) {
    IsPositiveMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsPositiveMatcher> matcher(inner);
    std::vector<int> values = {42};
    EXPECT_TRUE(matcher.match(values));
}

// Test match() with single element not matching
TEST_F(AllMatchMatcherTest_176, SingleNonMatchingElementReturnsFalse_176) {
    IsPositiveMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsPositiveMatcher> matcher(inner);
    std::vector<int> values = {-1};
    EXPECT_FALSE(matcher.match(values));
}

// Test match() with only last element not matching
TEST_F(AllMatchMatcherTest_176, LastElementFailsReturnsFalse_176) {
    IsPositiveMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsPositiveMatcher> matcher(inner);
    std::vector<int> values = {1, 2, 3, -1};
    EXPECT_FALSE(matcher.match(values));
}

// Test match() with only first element not matching
TEST_F(AllMatchMatcherTest_176, FirstElementFailsReturnsFalse_176) {
    IsPositiveMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsPositiveMatcher> matcher(inner);
    std::vector<int> values = {-1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(values));
}

// Test match() with zero values (boundary for IsPositive)
TEST_F(AllMatchMatcherTest_176, ZeroIsNotPositiveReturnsFalse_176) {
    IsPositiveMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsPositiveMatcher> matcher(inner);
    std::vector<int> values = {1, 0, 3};
    EXPECT_FALSE(matcher.match(values));
}

// Test with IsEvenMatcher - all even
TEST_F(AllMatchMatcherTest_176, AllEvenReturnsTrue_176) {
    IsEvenMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsEvenMatcher> matcher(inner);
    std::vector<int> values = {2, 4, 6, 8, 10};
    EXPECT_TRUE(matcher.match(values));
}

// Test with IsEvenMatcher - mixed
TEST_F(AllMatchMatcherTest_176, MixedEvenOddReturnsFalse_176) {
    IsEvenMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsEvenMatcher> matcher(inner);
    std::vector<int> values = {2, 3, 6};
    EXPECT_FALSE(matcher.match(values));
}

// Test with different range type (std::array)
TEST_F(AllMatchMatcherTest_176, WorksWithStdArray_176) {
    IsPositiveMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsPositiveMatcher> matcher(inner);
    std::array<int, 3> values = {1, 2, 3};
    EXPECT_TRUE(matcher.match(values));
}

// Test with different range type (std::list)
TEST_F(AllMatchMatcherTest_176, WorksWithStdList_176) {
    IsPositiveMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsPositiveMatcher> matcher(inner);
    std::list<int> values = {1, 2, 3};
    EXPECT_TRUE(matcher.match(values));
}

// Test with string range
TEST_F(AllMatchMatcherTest_176, AllNonEmptyStringsReturnsTrue_176) {
    IsNonEmptyStringMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsNonEmptyStringMatcher> matcher(inner);
    std::vector<std::string> values = {"hello", "world", "test"};
    EXPECT_TRUE(matcher.match(values));
}

// Test with string range containing empty string
TEST_F(AllMatchMatcherTest_176, ContainsEmptyStringReturnsFalse_176) {
    IsNonEmptyStringMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsNonEmptyStringMatcher> matcher(inner);
    std::vector<std::string> values = {"hello", "", "test"};
    EXPECT_FALSE(matcher.match(values));
}

// Test with large range - all matching
TEST_F(AllMatchMatcherTest_176, LargeRangeAllMatchingReturnsTrue_176) {
    IsPositiveMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsPositiveMatcher> matcher(inner);
    std::vector<int> values(1000, 1); // 1000 elements all set to 1
    EXPECT_TRUE(matcher.match(values));
}

// Test with large range - last element fails
TEST_F(AllMatchMatcherTest_176, LargeRangeLastFailsReturnsFalse_176) {
    IsPositiveMatcher inner;
    Catch::Matchers::AllMatchMatcher<IsPositiveMatcher> matcher(inner);
    std::vector<int> values(1000, 1);
    values.back() = -1;
    EXPECT_FALSE(matcher.match(values));
}
