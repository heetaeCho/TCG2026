#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

// Include the Catch2 amalgamated header for the matchers
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

class ContainsMatcherTest_977 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a vector containing all elements of the comparator matches
TEST_F(ContainsMatcherTest_977, MatchesWhenAllElementsPresent_977) {
    std::vector<int> comparator = {1, 2, 3};
    std::vector<int> target = {1, 2, 3, 4, 5};
    
    auto matcher = Catch::Matchers::Contains(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test that an empty comparator matches any vector
TEST_F(ContainsMatcherTest_977, EmptyComparatorMatchesAnyVector_977) {
    std::vector<int> comparator = {};
    std::vector<int> target = {1, 2, 3};
    
    auto matcher = Catch::Matchers::Contains(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test that an empty comparator matches an empty vector
TEST_F(ContainsMatcherTest_977, EmptyComparatorMatchesEmptyVector_977) {
    std::vector<int> comparator = {};
    std::vector<int> target = {};
    
    auto matcher = Catch::Matchers::Contains(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test that a non-empty comparator does not match an empty vector
TEST_F(ContainsMatcherTest_977, NonEmptyComparatorDoesNotMatchEmptyVector_977) {
    std::vector<int> comparator = {1, 2};
    std::vector<int> target = {};
    
    auto matcher = Catch::Matchers::Contains(comparator);
    EXPECT_FALSE(matcher.match(target));
}

// Test that missing elements cause no match
TEST_F(ContainsMatcherTest_977, DoesNotMatchWhenElementsMissing_977) {
    std::vector<int> comparator = {1, 2, 6};
    std::vector<int> target = {1, 2, 3, 4, 5};
    
    auto matcher = Catch::Matchers::Contains(comparator);
    EXPECT_FALSE(matcher.match(target));
}

// Test exact match (same elements)
TEST_F(ContainsMatcherTest_977, MatchesExactSameVector_977) {
    std::vector<int> comparator = {1, 2, 3};
    std::vector<int> target = {1, 2, 3};
    
    auto matcher = Catch::Matchers::Contains(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test with single element present
TEST_F(ContainsMatcherTest_977, SingleElementPresent_977) {
    std::vector<int> comparator = {3};
    std::vector<int> target = {1, 2, 3, 4, 5};
    
    auto matcher = Catch::Matchers::Contains(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test with single element absent
TEST_F(ContainsMatcherTest_977, SingleElementAbsent_977) {
    std::vector<int> comparator = {99};
    std::vector<int> target = {1, 2, 3, 4, 5};
    
    auto matcher = Catch::Matchers::Contains(comparator);
    EXPECT_FALSE(matcher.match(target));
}

// Test with string type
TEST_F(ContainsMatcherTest_977, WorksWithStrings_977) {
    std::vector<std::string> comparator = {"hello", "world"};
    std::vector<std::string> target = {"hello", "beautiful", "world"};
    
    auto matcher = Catch::Matchers::Contains(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test with string type - missing element
TEST_F(ContainsMatcherTest_977, StringMissingElement_977) {
    std::vector<std::string> comparator = {"hello", "missing"};
    std::vector<std::string> target = {"hello", "beautiful", "world"};
    
    auto matcher = Catch::Matchers::Contains(comparator);
    EXPECT_FALSE(matcher.match(target));
}

// Test with duplicate elements in target
TEST_F(ContainsMatcherTest_977, DuplicatesInTarget_977) {
    std::vector<int> comparator = {1, 2};
    std::vector<int> target = {1, 1, 2, 2, 3};
    
    auto matcher = Catch::Matchers::Contains(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test that the matcher has a description
TEST_F(ContainsMatcherTest_977, HasDescription_977) {
    std::vector<int> comparator = {1, 2, 3};
    auto matcher = Catch::Matchers::Contains(comparator);
    
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

// Test with elements in different order
TEST_F(ContainsMatcherTest_977, MatchesRegardlessOfOrder_977) {
    std::vector<int> comparator = {3, 1, 2};
    std::vector<int> target = {1, 2, 3, 4, 5};
    
    auto matcher = Catch::Matchers::Contains(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test comparator larger than target
TEST_F(ContainsMatcherTest_977, ComparatorLargerThanTarget_977) {
    std::vector<int> comparator = {1, 2, 3, 4, 5, 6};
    std::vector<int> target = {1, 2, 3};
    
    auto matcher = Catch::Matchers::Contains(comparator);
    EXPECT_FALSE(matcher.match(target));
}

// Test with double type
TEST_F(ContainsMatcherTest_977, WorksWithDoubles_977) {
    std::vector<double> comparator = {1.5, 2.5};
    std::vector<double> target = {1.5, 2.5, 3.5};
    
    auto matcher = Catch::Matchers::Contains(comparator);
    EXPECT_TRUE(matcher.match(target));
}
