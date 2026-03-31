#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <sstream>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

// ============================================================================
// Tests for VectorContainsElementMatcher
// ============================================================================

// Test: match returns true when vector contains the element
TEST(VectorContainsElementMatcherTest_965, MatchReturnsTrueWhenElementPresent_965) {
    int target = 3;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(target);
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

// Test: match returns false when vector does not contain the element
TEST(VectorContainsElementMatcherTest_965, MatchReturnsFalseWhenElementAbsent_965) {
    int target = 10;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(target);
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

// Test: match returns false for empty vector
TEST(VectorContainsElementMatcherTest_965, MatchReturnsFalseForEmptyVector_965) {
    int target = 1;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(target);
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

// Test: match returns true when element is at the beginning
TEST(VectorContainsElementMatcherTest_965, MatchReturnsTrueWhenElementAtBeginning_965) {
    int target = 1;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(target);
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

// Test: match returns true when element is at the end
TEST(VectorContainsElementMatcherTest_965, MatchReturnsTrueWhenElementAtEnd_965) {
    int target = 3;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(target);
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

// Test: match works with a single-element vector that contains the target
TEST(VectorContainsElementMatcherTest_965, MatchReturnsTrueForSingleElementVectorContaining_965) {
    int target = 42;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(target);
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

// Test: match works with a single-element vector that does not contain the target
TEST(VectorContainsElementMatcherTest_965, MatchReturnsFalseForSingleElementVectorNotContaining_965) {
    int target = 42;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(target);
    std::vector<int> v = {99};
    EXPECT_FALSE(matcher.match(v));
}

// Test: match works with string type
TEST(VectorContainsElementMatcherTest_965, MatchWorksWithStringType_965) {
    std::string target = "hello";
    VectorContainsElementMatcher<std::string, std::allocator<std::string>> matcher(target);
    std::vector<std::string> v = {"world", "hello", "foo"};
    EXPECT_TRUE(matcher.match(v));
}

// Test: match returns false with string type when not present
TEST(VectorContainsElementMatcherTest_965, MatchReturnsFalseWithStringTypeWhenAbsent_965) {
    std::string target = "bar";
    VectorContainsElementMatcher<std::string, std::allocator<std::string>> matcher(target);
    std::vector<std::string> v = {"world", "hello", "foo"};
    EXPECT_FALSE(matcher.match(v));
}

// Test: match with duplicate elements still returns true
TEST(VectorContainsElementMatcherTest_965, MatchReturnsTrueWithDuplicateElements_965) {
    int target = 5;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(target);
    std::vector<int> v = {5, 5, 5, 5};
    EXPECT_TRUE(matcher.match(v));
}

// Test: describe returns a string containing "Contains:"
TEST(VectorContainsElementMatcherTest_965, DescribeContainsExpectedPrefix_965) {
    int target = 7;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(target);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("Contains:"), std::string::npos);
}

// Test: describe includes the stringified comparator value
TEST(VectorContainsElementMatcherTest_965, DescribeIncludesComparatorValue_965) {
    int target = 42;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(target);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("42"), std::string::npos);
}

// Test: describe with string comparator
TEST(VectorContainsElementMatcherTest_965, DescribeIncludesStringComparatorValue_965) {
    std::string target = "test_value";
    VectorContainsElementMatcher<std::string, std::allocator<std::string>> matcher(target);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("test_value"), std::string::npos);
}

// Test: match with negative numbers
TEST(VectorContainsElementMatcherTest_965, MatchWorksWithNegativeNumbers_965) {
    int target = -5;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(target);
    std::vector<int> v = {-10, -5, 0, 5, 10};
    EXPECT_TRUE(matcher.match(v));
}

// Test: match with zero
TEST(VectorContainsElementMatcherTest_965, MatchWorksWithZero_965) {
    int target = 0;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(target);
    std::vector<int> v = {-1, 0, 1};
    EXPECT_TRUE(matcher.match(v));
}

// Test: match with double type
TEST(VectorContainsElementMatcherTest_965, MatchWorksWithDoubleType_965) {
    double target = 3.14;
    VectorContainsElementMatcher<double, std::allocator<double>> matcher(target);
    std::vector<double> v = {1.0, 2.0, 3.14, 4.0};
    EXPECT_TRUE(matcher.match(v));
}

// Test: match with large vector
TEST(VectorContainsElementMatcherTest_965, MatchWorksWithLargeVector_965) {
    int target = 9999;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(target);
    std::vector<int> v(10000);
    for (int i = 0; i < 10000; ++i) {
        v[i] = i;
    }
    EXPECT_TRUE(matcher.match(v));
}

// Test: match returns false with large vector when element not present
TEST(VectorContainsElementMatcherTest_965, MatchReturnsFalseWithLargeVectorWhenAbsent_965) {
    int target = 10000;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(target);
    std::vector<int> v(10000);
    for (int i = 0; i < 10000; ++i) {
        v[i] = i;
    }
    EXPECT_FALSE(matcher.match(v));
}
