#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <list>
#include <array>
#include <deque>

// Include the Catch2 amalgamated header
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

// Helper matcher that matches a specific value
// We use Catch2's own matchers as the inner matcher

// Test fixture
class ContainsMatcherMatcherTest_952 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: describe() returns a string containing "contains element matching"
TEST_F(ContainsMatcherMatcherTest_952, DescribeContainsExpectedPrefix_952) {
    auto matcher = ContainsElement(Catch::Matchers::Equals(42));
    std::string description = matcher.describe();
    EXPECT_NE(description.find("contains element matching"), std::string::npos);
}

// Test: match returns true when vector contains an element matching the inner matcher
TEST_F(ContainsMatcherMatcherTest_952, MatchReturnsTrueWhenElementFound_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<int>([](int x) { return x == 3; }, "equals 3"));
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

// Test: match returns false when vector does not contain a matching element
TEST_F(ContainsMatcherMatcherTest_952, MatchReturnsFalseWhenElementNotFound_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<int>([](int x) { return x == 10; }, "equals 10"));
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

// Test: match returns false for an empty container
TEST_F(ContainsMatcherMatcherTest_952, MatchReturnsFalseForEmptyContainer_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<int>([](int x) { return x == 1; }, "equals 1"));
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

// Test: match works with a single-element container that matches
TEST_F(ContainsMatcherMatcherTest_952, MatchReturnsTrueForSingleElementMatch_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<int>([](int x) { return x == 42; }, "equals 42"));
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

// Test: match works with a single-element container that doesn't match
TEST_F(ContainsMatcherMatcherTest_952, MatchReturnsFalseForSingleElementNoMatch_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<int>([](int x) { return x == 42; }, "equals 42"));
    std::vector<int> v = {99};
    EXPECT_FALSE(matcher.match(v));
}

// Test: match works with list container
TEST_F(ContainsMatcherMatcherTest_952, MatchWorksWithList_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<int>([](int x) { return x > 5; }, "greater than 5"));
    std::list<int> lst = {1, 2, 3, 10};
    EXPECT_TRUE(matcher.match(lst));
}

// Test: match works with list container - no match
TEST_F(ContainsMatcherMatcherTest_952, MatchReturnsFalseWithListNoMatch_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<int>([](int x) { return x > 100; }, "greater than 100"));
    std::list<int> lst = {1, 2, 3, 10};
    EXPECT_FALSE(matcher.match(lst));
}

// Test: match works with deque container
TEST_F(ContainsMatcherMatcherTest_952, MatchWorksWithDeque_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<std::string>(
        [](const std::string& s) { return s == "hello"; }, "equals hello"));
    std::deque<std::string> dq = {"world", "hello", "foo"};
    EXPECT_TRUE(matcher.match(dq));
}

// Test: match works with array container
TEST_F(ContainsMatcherMatcherTest_952, MatchWorksWithArray_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<int>([](int x) { return x == 3; }, "equals 3"));
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(arr));
}

// Test: match finds first matching element (multiple matches exist)
TEST_F(ContainsMatcherMatcherTest_952, MatchReturnsTrueWithMultipleMatches_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<int>([](int x) { return x % 2 == 0; }, "is even"));
    std::vector<int> v = {2, 4, 6, 8};
    EXPECT_TRUE(matcher.match(v));
}

// Test: describe includes inner matcher's description
TEST_F(ContainsMatcherMatcherTest_952, DescribeIncludesInnerMatcherDescription_952) {
    auto innerDesc = "is greater than 5";
    auto matcher = ContainsElement(Catch::Matchers::Predicate<int>([](int x) { return x > 5; }, innerDesc));
    std::string description = matcher.describe();
    EXPECT_NE(description.find(innerDesc), std::string::npos);
}

// Test: match with string elements
TEST_F(ContainsMatcherMatcherTest_952, MatchWorksWithStringElements_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<std::string>(
        [](const std::string& s) { return s.length() > 3; }, "length > 3"));
    std::vector<std::string> v = {"ab", "cd", "efgh"};
    EXPECT_TRUE(matcher.match(v));
}

// Test: match with string elements - no match
TEST_F(ContainsMatcherMatcherTest_952, MatchReturnsFalseWithStringElementsNoMatch_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<std::string>(
        [](const std::string& s) { return s.length() > 10; }, "length > 10"));
    std::vector<std::string> v = {"ab", "cd", "efgh"};
    EXPECT_FALSE(matcher.match(v));
}

// Test: match works with const container reference
TEST_F(ContainsMatcherMatcherTest_952, MatchWorksWithConstContainer_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<int>([](int x) { return x == 5; }, "equals 5"));
    const std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

// Test: match with element at the beginning
TEST_F(ContainsMatcherMatcherTest_952, MatchFindsElementAtBeginning_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<int>([](int x) { return x == 1; }, "equals 1"));
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

// Test: match with element at the end
TEST_F(ContainsMatcherMatcherTest_952, MatchFindsElementAtEnd_952) {
    auto matcher = ContainsElement(Catch::Matchers::Predicate<int>([](int x) { return x == 5; }, "equals 5"));
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}
