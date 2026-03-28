#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <array>

#include "catch2/matchers/catch_matchers_container_properties.hpp"

using Catch::Matchers::SizeIs;
using Catch::Matchers::HasSizeMatcher;

class HasSizeMatcherTest_239 : public ::testing::Test {
protected:
};

// Test SizeIs factory function returns a HasSizeMatcher
TEST_F(HasSizeMatcherTest_239, SizeIsReturnsHasSizeMatcher_239) {
    auto matcher = SizeIs(5);
    // Just verify it compiles and creates a matcher
    (void)matcher;
}

// Test matching an empty vector with size 0
TEST_F(HasSizeMatcherTest_239, EmptyVectorMatchesSizeZero_239) {
    auto matcher = SizeIs(0);
    std::vector<int> v;
    EXPECT_TRUE(matcher.match(v));
}

// Test matching an empty vector does not match size 1
TEST_F(HasSizeMatcherTest_239, EmptyVectorDoesNotMatchSizeOne_239) {
    auto matcher = SizeIs(1);
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

// Test matching a vector with elements
TEST_F(HasSizeMatcherTest_239, VectorWithElementsMatchesCorrectSize_239) {
    auto matcher = SizeIs(3);
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

// Test vector with elements does not match wrong size
TEST_F(HasSizeMatcherTest_239, VectorWithElementsDoesNotMatchWrongSize_239) {
    auto matcher = SizeIs(5);
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

// Test with std::string
TEST_F(HasSizeMatcherTest_239, StringMatchesCorrectSize_239) {
    auto matcher = SizeIs(5);
    std::string s = "hello";
    EXPECT_TRUE(matcher.match(s));
}

// Test with empty string
TEST_F(HasSizeMatcherTest_239, EmptyStringMatchesSizeZero_239) {
    auto matcher = SizeIs(0);
    std::string s;
    EXPECT_TRUE(matcher.match(s));
}

// Test with std::list
TEST_F(HasSizeMatcherTest_239, ListMatchesCorrectSize_239) {
    auto matcher = SizeIs(4);
    std::list<int> l = {10, 20, 30, 40};
    EXPECT_TRUE(matcher.match(l));
}

// Test with std::map
TEST_F(HasSizeMatcherTest_239, MapMatchesCorrectSize_239) {
    auto matcher = SizeIs(2);
    std::map<int, int> m = {{1, 10}, {2, 20}};
    EXPECT_TRUE(matcher.match(m));
}

// Test with std::set
TEST_F(HasSizeMatcherTest_239, SetMatchesCorrectSize_239) {
    auto matcher = SizeIs(3);
    std::set<int> s = {1, 2, 3};
    EXPECT_TRUE(matcher.match(s));
}

// Test with std::deque
TEST_F(HasSizeMatcherTest_239, DequeMatchesCorrectSize_239) {
    auto matcher = SizeIs(2);
    std::deque<int> d = {1, 2};
    EXPECT_TRUE(matcher.match(d));
}

// Test with large size
TEST_F(HasSizeMatcherTest_239, LargeVectorMatchesCorrectSize_239) {
    std::size_t largeSize = 10000;
    auto matcher = SizeIs(largeSize);
    std::vector<int> v(largeSize, 0);
    EXPECT_TRUE(matcher.match(v));
}

// Test size mismatch by one (boundary)
TEST_F(HasSizeMatcherTest_239, SizeMismatchByOne_239) {
    auto matcher = SizeIs(3);
    std::vector<int> v = {1, 2};
    EXPECT_FALSE(matcher.match(v));
}

// Test size mismatch - expected less than actual
TEST_F(HasSizeMatcherTest_239, ExpectedLessThanActual_239) {
    auto matcher = SizeIs(2);
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

// Test describe method returns a meaningful string
TEST_F(HasSizeMatcherTest_239, DescribeContainsSizeInfo_239) {
    auto matcher = SizeIs(42);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
    // The description should mention the expected size
    EXPECT_NE(description.find("42"), std::string::npos);
}

// Test with std::array
TEST_F(HasSizeMatcherTest_239, ArrayMatchesCorrectSize_239) {
    auto matcher = SizeIs(3);
    std::array<int, 3> a = {1, 2, 3};
    EXPECT_TRUE(matcher.match(a));
}

// Test SizeIs with zero
TEST_F(HasSizeMatcherTest_239, SizeIsZeroMatchesEmptyContainers_239) {
    auto matcher = SizeIs(0);
    std::vector<double> v;
    std::list<int> l;
    std::string s;
    EXPECT_TRUE(matcher.match(v));
    EXPECT_TRUE(matcher.match(l));
    EXPECT_TRUE(matcher.match(s));
}

// Test single element container
TEST_F(HasSizeMatcherTest_239, SingleElementMatchesSizeOne_239) {
    auto matcher = SizeIs(1);
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}
