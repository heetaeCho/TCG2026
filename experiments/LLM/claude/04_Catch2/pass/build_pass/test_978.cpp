#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

// Include the Catch2 amalgamated header for the matchers
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// Helper function to check if a Catch2 matcher matches a given vector
// We use the matcher's match() method which should be available on the matcher object
template<typename Matcher, typename Container>
bool doesMatch(const Matcher& matcher, const Container& container) {
    return matcher.match(container);
}

// Test fixture
class VectorContainsTest_978 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: VectorContains matches when element is present in vector of ints
TEST_F(VectorContainsTest_978, MatchesWhenElementPresent_978) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto matcher = Catch::Matchers::VectorContains(3);
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test: VectorContains does not match when element is absent from vector of ints
TEST_F(VectorContainsTest_978, DoesNotMatchWhenElementAbsent_978) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto matcher = Catch::Matchers::VectorContains(6);
    EXPECT_FALSE(doesMatch(matcher, vec));
}

// Test: VectorContains does not match on empty vector
TEST_F(VectorContainsTest_978, DoesNotMatchEmptyVector_978) {
    std::vector<int> vec = {};
    auto matcher = Catch::Matchers::VectorContains(1);
    EXPECT_FALSE(doesMatch(matcher, vec));
}

// Test: VectorContains matches first element
TEST_F(VectorContainsTest_978, MatchesFirstElement_978) {
    std::vector<int> vec = {10, 20, 30};
    auto matcher = Catch::Matchers::VectorContains(10);
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test: VectorContains matches last element
TEST_F(VectorContainsTest_978, MatchesLastElement_978) {
    std::vector<int> vec = {10, 20, 30};
    auto matcher = Catch::Matchers::VectorContains(30);
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test: VectorContains matches with single element vector - element present
TEST_F(VectorContainsTest_978, MatchesSingleElementVectorPresent_978) {
    std::vector<int> vec = {42};
    auto matcher = Catch::Matchers::VectorContains(42);
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test: VectorContains does not match with single element vector - element absent
TEST_F(VectorContainsTest_978, DoesNotMatchSingleElementVectorAbsent_978) {
    std::vector<int> vec = {42};
    auto matcher = Catch::Matchers::VectorContains(99);
    EXPECT_FALSE(doesMatch(matcher, vec));
}

// Test: VectorContains works with string type
TEST_F(VectorContainsTest_978, MatchesStringElement_978) {
    std::vector<std::string> vec = {"hello", "world", "foo"};
    auto matcher = Catch::Matchers::VectorContains(std::string("world"));
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test: VectorContains does not match absent string
TEST_F(VectorContainsTest_978, DoesNotMatchAbsentString_978) {
    std::vector<std::string> vec = {"hello", "world", "foo"};
    auto matcher = Catch::Matchers::VectorContains(std::string("bar"));
    EXPECT_FALSE(doesMatch(matcher, vec));
}

// Test: VectorContains matches with duplicate elements
TEST_F(VectorContainsTest_978, MatchesWithDuplicateElements_978) {
    std::vector<int> vec = {1, 2, 2, 3, 3, 3};
    auto matcher = Catch::Matchers::VectorContains(2);
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test: VectorContains works with double type
TEST_F(VectorContainsTest_978, MatchesDoubleElement_978) {
    std::vector<double> vec = {1.1, 2.2, 3.3};
    auto matcher = Catch::Matchers::VectorContains(2.2);
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test: VectorContains does not match absent double element
TEST_F(VectorContainsTest_978, DoesNotMatchAbsentDouble_978) {
    std::vector<double> vec = {1.1, 2.2, 3.3};
    auto matcher = Catch::Matchers::VectorContains(4.4);
    EXPECT_FALSE(doesMatch(matcher, vec));
}

// Test: VectorContains matches negative numbers
TEST_F(VectorContainsTest_978, MatchesNegativeNumbers_978) {
    std::vector<int> vec = {-5, -3, -1, 0, 1, 3, 5};
    auto matcher = Catch::Matchers::VectorContains(-3);
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test: VectorContains matches zero
TEST_F(VectorContainsTest_978, MatchesZero_978) {
    std::vector<int> vec = {-1, 0, 1};
    auto matcher = Catch::Matchers::VectorContains(0);
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test: VectorContains with large vector
TEST_F(VectorContainsTest_978, MatchesInLargeVector_978) {
    std::vector<int> vec(10000);
    for (int i = 0; i < 10000; ++i) {
        vec[i] = i;
    }
    auto matcher = Catch::Matchers::VectorContains(9999);
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test: VectorContains does not match value just outside range in large vector
TEST_F(VectorContainsTest_978, DoesNotMatchOutOfRangeInLargeVector_978) {
    std::vector<int> vec(10000);
    for (int i = 0; i < 10000; ++i) {
        vec[i] = i;
    }
    auto matcher = Catch::Matchers::VectorContains(10000);
    EXPECT_FALSE(doesMatch(matcher, vec));
}

// Test: VectorContains matcher has a describe method that returns non-empty string
TEST_F(VectorContainsTest_978, DescribeReturnsNonEmpty_978) {
    auto matcher = Catch::Matchers::VectorContains(42);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test: VectorContains with empty string in vector of strings
TEST_F(VectorContainsTest_978, MatchesEmptyStringInVector_978) {
    std::vector<std::string> vec = {"hello", "", "world"};
    auto matcher = Catch::Matchers::VectorContains(std::string(""));
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test: VectorContains with char type
TEST_F(VectorContainsTest_978, MatchesCharElement_978) {
    std::vector<char> vec = {'a', 'b', 'c', 'd'};
    auto matcher = Catch::Matchers::VectorContains('c');
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test: VectorContains does not match absent char
TEST_F(VectorContainsTest_978, DoesNotMatchAbsentChar_978) {
    std::vector<char> vec = {'a', 'b', 'c'};
    auto matcher = Catch::Matchers::VectorContains('z');
    EXPECT_FALSE(doesMatch(matcher, vec));
}
