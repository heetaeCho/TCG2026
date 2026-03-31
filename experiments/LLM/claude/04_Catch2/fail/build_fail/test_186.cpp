#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_quantifiers.hpp>
#include <catch2/matchers/catch_matchers_predicate.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers.hpp>

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>
#include <array>
#include <deque>

using namespace Catch::Matchers;

// Helper predicate matcher for testing
auto IsEven() {
    return Catch::Matchers::Predicate<int>(
        [](int x) { return x % 2 == 0; },
        "is even"
    );
}

auto IsNegative() {
    return Catch::Matchers::Predicate<int>(
        [](int x) { return x < 0; },
        "is negative"
    );
}

auto IsGreaterThan(int threshold) {
    return Catch::Matchers::Predicate<int>(
        [threshold](int x) { return x > threshold; },
        "is greater than " + std::to_string(threshold)
    );
}

class NoneMatchTest_186 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test NoneMatch with empty container - should match (vacuously true)
TEST_F(NoneMatchTest_186, EmptyContainerMatches_186) {
    std::vector<int> empty;
    auto matcher = NoneMatch(IsEven());
    EXPECT_TRUE(matcher.match(empty));
}

// Test NoneMatch where no elements satisfy the matcher
TEST_F(NoneMatchTest_186, NoElementsMatchReturnsTrue_186) {
    std::vector<int> odds = {1, 3, 5, 7, 9};
    auto matcher = NoneMatch(IsEven());
    EXPECT_TRUE(matcher.match(odds));
}

// Test NoneMatch where one element satisfies the matcher
TEST_F(NoneMatchTest_186, OneElementMatchesReturnsFalse_186) {
    std::vector<int> v = {1, 3, 4, 7, 9};
    auto matcher = NoneMatch(IsEven());
    EXPECT_FALSE(matcher.match(v));
}

// Test NoneMatch where all elements satisfy the matcher
TEST_F(NoneMatchTest_186, AllElementsMatchReturnsFalse_186) {
    std::vector<int> evens = {2, 4, 6, 8, 10};
    auto matcher = NoneMatch(IsEven());
    EXPECT_FALSE(matcher.match(evens));
}

// Test NoneMatch with single element that does not match
TEST_F(NoneMatchTest_186, SingleElementNoMatchReturnsTrue_186) {
    std::vector<int> v = {1};
    auto matcher = NoneMatch(IsEven());
    EXPECT_TRUE(matcher.match(v));
}

// Test NoneMatch with single element that matches
TEST_F(NoneMatchTest_186, SingleElementMatchesReturnsFalse_186) {
    std::vector<int> v = {2};
    auto matcher = NoneMatch(IsEven());
    EXPECT_FALSE(matcher.match(v));
}

// Test NoneMatch with negative numbers - none negative
TEST_F(NoneMatchTest_186, NoNegativeNumbersReturnsTrue_186) {
    std::vector<int> v = {0, 1, 2, 3};
    auto matcher = NoneMatch(IsNegative());
    EXPECT_TRUE(matcher.match(v));
}

// Test NoneMatch with negative numbers - some negative
TEST_F(NoneMatchTest_186, SomeNegativeNumbersReturnsFalse_186) {
    std::vector<int> v = {-1, 0, 1, 2};
    auto matcher = NoneMatch(IsNegative());
    EXPECT_FALSE(matcher.match(v));
}

// Test NoneMatch with list container
TEST_F(NoneMatchTest_186, WorksWithListContainer_186) {
    std::list<int> odds = {1, 3, 5, 7};
    auto matcher = NoneMatch(IsEven());
    EXPECT_TRUE(matcher.match(odds));
}

// Test NoneMatch with deque container
TEST_F(NoneMatchTest_186, WorksWithDequeContainer_186) {
    std::deque<int> odds = {1, 3, 5};
    auto matcher = NoneMatch(IsEven());
    EXPECT_TRUE(matcher.match(odds));
}

// Test NoneMatch with array container
TEST_F(NoneMatchTest_186, WorksWithArrayContainer_186) {
    std::array<int, 3> odds = {1, 3, 5};
    auto matcher = NoneMatch(IsEven());
    EXPECT_TRUE(matcher.match(odds));
}

// Test NoneMatch with matching element at the beginning
TEST_F(NoneMatchTest_186, MatchingElementAtBeginningReturnsFalse_186) {
    std::vector<int> v = {2, 1, 3, 5};
    auto matcher = NoneMatch(IsEven());
    EXPECT_FALSE(matcher.match(v));
}

// Test NoneMatch with matching element at the end
TEST_F(NoneMatchTest_186, MatchingElementAtEndReturnsFalse_186) {
    std::vector<int> v = {1, 3, 5, 2};
    auto matcher = NoneMatch(IsEven());
    EXPECT_FALSE(matcher.match(v));
}

// Test NoneMatch with threshold predicate
TEST_F(NoneMatchTest_186, NoneGreaterThanThresholdReturnsTrue_186) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto matcher = NoneMatch(IsGreaterThan(10));
    EXPECT_TRUE(matcher.match(v));
}

// Test NoneMatch with threshold predicate where some match
TEST_F(NoneMatchTest_186, SomeGreaterThanThresholdReturnsFalse_186) {
    std::vector<int> v = {1, 2, 3, 4, 15};
    auto matcher = NoneMatch(IsGreaterThan(10));
    EXPECT_FALSE(matcher.match(v));
}

// Test that NoneMatch describe method returns a non-empty string
TEST_F(NoneMatchTest_186, DescribeReturnsNonEmptyString_186) {
    auto matcher = NoneMatch(IsEven());
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test NoneMatch with large container where none match
TEST_F(NoneMatchTest_186, LargeContainerNoneMatchReturnsTrue_186) {
    std::vector<int> v;
    for (int i = 0; i < 10000; ++i) {
        v.push_back(2 * i + 1); // all odd
    }
    auto matcher = NoneMatch(IsEven());
    EXPECT_TRUE(matcher.match(v));
}

// Test NoneMatch with large container where last element matches
TEST_F(NoneMatchTest_186, LargeContainerLastElementMatchesReturnsFalse_186) {
    std::vector<int> v;
    for (int i = 0; i < 9999; ++i) {
        v.push_back(2 * i + 1); // all odd
    }
    v.push_back(2); // even at end
    auto matcher = NoneMatch(IsEven());
    EXPECT_FALSE(matcher.match(v));
}

// Test NoneMatch with strings
TEST_F(NoneMatchTest_186, WorksWithStringPredicate_186) {
    auto IsLong = Catch::Matchers::Predicate<std::string>(
        [](const std::string& s) { return s.size() > 10; },
        "is long"
    );
    std::vector<std::string> v = {"hi", "hey", "yo"};
    auto matcher = NoneMatch(IsLong);
    EXPECT_TRUE(matcher.match(v));
}

// Test NoneMatch with strings where one matches
TEST_F(NoneMatchTest_186, StringMatchReturnsFalse_186) {
    auto IsLong = Catch::Matchers::Predicate<std::string>(
        [](const std::string& s) { return s.size() > 10; },
        "is long"
    );
    std::vector<std::string> v = {"hi", "this is a very long string", "yo"};
    auto matcher = NoneMatch(IsLong);
    EXPECT_FALSE(matcher.match(v));
}
