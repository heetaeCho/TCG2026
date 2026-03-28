#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>
#include <deque>
#include <set>
#include <array>

// Include the Catch2 amalgamated header for the Contains matcher
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

class ContainsMatcherTest_953 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to check if a matcher matches a given container
template <typename Container, typename Matcher>
bool matcherMatches(const Container& container, const Matcher& matcher) {
    return matcher.match(container);
}

// Normal operation: vector contains the element
TEST_F(ContainsMatcherTest_953, VectorContainsIntElement_953) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto matcher = Catch::Matchers::Contains(3);
    EXPECT_TRUE(matcherMatches(v, matcher));
}

// Normal operation: vector does not contain the element
TEST_F(ContainsMatcherTest_953, VectorDoesNotContainIntElement_953) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto matcher = Catch::Matchers::Contains(6);
    EXPECT_FALSE(matcherMatches(v, matcher));
}

// Boundary: empty container
TEST_F(ContainsMatcherTest_953, EmptyVectorDoesNotContainElement_953) {
    std::vector<int> v;
    auto matcher = Catch::Matchers::Contains(1);
    EXPECT_FALSE(matcherMatches(v, matcher));
}

// Boundary: single element container - element present
TEST_F(ContainsMatcherTest_953, SingleElementVectorContainsElement_953) {
    std::vector<int> v = {42};
    auto matcher = Catch::Matchers::Contains(42);
    EXPECT_TRUE(matcherMatches(v, matcher));
}

// Boundary: single element container - element not present
TEST_F(ContainsMatcherTest_953, SingleElementVectorDoesNotContainElement_953) {
    std::vector<int> v = {42};
    auto matcher = Catch::Matchers::Contains(43);
    EXPECT_FALSE(matcherMatches(v, matcher));
}

// Normal operation: contains string element
TEST_F(ContainsMatcherTest_953, VectorContainsStringElement_953) {
    std::vector<std::string> v = {"hello", "world", "foo"};
    auto matcher = Catch::Matchers::Contains(std::string("world"));
    EXPECT_TRUE(matcherMatches(v, matcher));
}

// Normal operation: does not contain string element
TEST_F(ContainsMatcherTest_953, VectorDoesNotContainStringElement_953) {
    std::vector<std::string> v = {"hello", "world", "foo"};
    auto matcher = Catch::Matchers::Contains(std::string("bar"));
    EXPECT_FALSE(matcherMatches(v, matcher));
}

// Normal operation: contains with double values
TEST_F(ContainsMatcherTest_953, VectorContainsDoubleElement_953) {
    std::vector<double> v = {1.0, 2.5, 3.7};
    auto matcher = Catch::Matchers::Contains(2.5);
    EXPECT_TRUE(matcherMatches(v, matcher));
}

// Test with list container
TEST_F(ContainsMatcherTest_953, ListContainsElement_953) {
    std::list<int> l = {10, 20, 30};
    auto matcher = Catch::Matchers::Contains(20);
    EXPECT_TRUE(matcherMatches(l, matcher));
}

// Test with list container - not found
TEST_F(ContainsMatcherTest_953, ListDoesNotContainElement_953) {
    std::list<int> l = {10, 20, 30};
    auto matcher = Catch::Matchers::Contains(40);
    EXPECT_FALSE(matcherMatches(l, matcher));
}

// Test with deque container
TEST_F(ContainsMatcherTest_953, DequeContainsElement_953) {
    std::deque<int> d = {5, 10, 15};
    auto matcher = Catch::Matchers::Contains(10);
    EXPECT_TRUE(matcherMatches(d, matcher));
}

// Boundary: duplicate elements - contains
TEST_F(ContainsMatcherTest_953, VectorWithDuplicatesContainsElement_953) {
    std::vector<int> v = {1, 2, 2, 3, 3, 3};
    auto matcher = Catch::Matchers::Contains(2);
    EXPECT_TRUE(matcherMatches(v, matcher));
}

// Test with first element
TEST_F(ContainsMatcherTest_953, ContainsFirstElement_953) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto matcher = Catch::Matchers::Contains(1);
    EXPECT_TRUE(matcherMatches(v, matcher));
}

// Test with last element
TEST_F(ContainsMatcherTest_953, ContainsLastElement_953) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto matcher = Catch::Matchers::Contains(5);
    EXPECT_TRUE(matcherMatches(v, matcher));
}

// Boundary: negative values
TEST_F(ContainsMatcherTest_953, ContainsNegativeElement_953) {
    std::vector<int> v = {-3, -2, -1, 0, 1};
    auto matcher = Catch::Matchers::Contains(-2);
    EXPECT_TRUE(matcherMatches(v, matcher));
}

// Boundary: zero element
TEST_F(ContainsMatcherTest_953, ContainsZeroElement_953) {
    std::vector<int> v = {-1, 0, 1};
    auto matcher = Catch::Matchers::Contains(0);
    EXPECT_TRUE(matcherMatches(v, matcher));
}

// Test with std::array
TEST_F(ContainsMatcherTest_953, ArrayContainsElement_953) {
    std::array<int, 3> a = {10, 20, 30};
    auto matcher = Catch::Matchers::Contains(20);
    EXPECT_TRUE(matcherMatches(a, matcher));
}

// Test with std::array - element not present
TEST_F(ContainsMatcherTest_953, ArrayDoesNotContainElement_953) {
    std::array<int, 3> a = {10, 20, 30};
    auto matcher = Catch::Matchers::Contains(40);
    EXPECT_FALSE(matcherMatches(a, matcher));
}

// Test describe method returns non-empty string
TEST_F(ContainsMatcherTest_953, DescribeReturnsNonEmptyString_953) {
    auto matcher = Catch::Matchers::Contains(42);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test with large container
TEST_F(ContainsMatcherTest_953, LargeVectorContainsElement_953) {
    std::vector<int> v(10000);
    for (int i = 0; i < 10000; ++i) {
        v[i] = i;
    }
    auto matcher = Catch::Matchers::Contains(9999);
    EXPECT_TRUE(matcherMatches(v, matcher));
}

// Test with large container - element not present
TEST_F(ContainsMatcherTest_953, LargeVectorDoesNotContainElement_953) {
    std::vector<int> v(10000);
    for (int i = 0; i < 10000; ++i) {
        v[i] = i;
    }
    auto matcher = Catch::Matchers::Contains(10000);
    EXPECT_FALSE(matcherMatches(v, matcher));
}

// Test with char values
TEST_F(ContainsMatcherTest_953, VectorContainsCharElement_953) {
    std::vector<char> v = {'a', 'b', 'c', 'd'};
    auto matcher = Catch::Matchers::Contains('c');
    EXPECT_TRUE(matcherMatches(v, matcher));
}

// Test with char values - not found
TEST_F(ContainsMatcherTest_953, VectorDoesNotContainCharElement_953) {
    std::vector<char> v = {'a', 'b', 'c', 'd'};
    auto matcher = Catch::Matchers::Contains('z');
    EXPECT_FALSE(matcherMatches(v, matcher));
}

// Test with bool values
TEST_F(ContainsMatcherTest_953, VectorContainsBoolElement_953) {
    std::vector<bool> v = {true, false, true};
    auto matcher = Catch::Matchers::Contains(false);
    EXPECT_TRUE(matcherMatches(v, matcher));
}
