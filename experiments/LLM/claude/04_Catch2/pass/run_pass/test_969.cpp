#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

// Test fixture
class EqualsMatcherTest_969 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation tests

TEST_F(EqualsMatcherTest_969, MatchReturnsTrueForIdenticalIntVectors_969) {
    std::vector<int> comparator = {1, 2, 3, 4, 5};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchReturnsFalseForDifferentIntVectors_969) {
    std::vector<int> comparator = {1, 2, 3};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::vector<int> v = {1, 2, 4};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchReturnsFalseForDifferentSizedVectors_969) {
    std::vector<int> comparator = {1, 2, 3};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::vector<int> v = {1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchReturnsTrueForBothEmptyVectors_969) {
    std::vector<int> comparator = {};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::vector<int> v = {};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchReturnsFalseWhenComparatorEmptyAndMatchNotEmpty_969) {
    std::vector<int> comparator = {};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::vector<int> v = {1};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchReturnsFalseWhenMatchEmptyAndComparatorNotEmpty_969) {
    std::vector<int> comparator = {1};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::vector<int> v = {};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchReturnsTrueForIdenticalStringVectors_969) {
    std::vector<std::string> comparator = {"hello", "world"};
    EqualsMatcher<std::string, std::allocator<std::string>, std::allocator<std::string>> matcher(comparator);
    std::vector<std::string> v = {"hello", "world"};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchReturnsFalseForDifferentStringVectors_969) {
    std::vector<std::string> comparator = {"hello", "world"};
    EqualsMatcher<std::string, std::allocator<std::string>, std::allocator<std::string>> matcher(comparator);
    std::vector<std::string> v = {"hello", "earth"};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchReturnsFalseForSameElementsDifferentOrder_969) {
    std::vector<int> comparator = {1, 2, 3};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::vector<int> v = {3, 2, 1};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, DescribeContainsEqualsPrefix_969) {
    std::vector<int> comparator = {1, 2, 3};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("Equals:"), std::string::npos);
}

TEST_F(EqualsMatcherTest_969, DescribeForEmptyVector_969) {
    std::vector<int> comparator = {};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("Equals:"), std::string::npos);
}

TEST_F(EqualsMatcherTest_969, MatchReturnsTrueForSingleElementVectors_969) {
    std::vector<int> comparator = {42};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchReturnsFalseForSingleElementDifferentValues_969) {
    std::vector<int> comparator = {42};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::vector<int> v = {43};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchWorksWithLargeVectors_969) {
    std::vector<int> comparator(10000);
    for (int i = 0; i < 10000; ++i) {
        comparator[i] = i;
    }
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> v(comparator);
    EXPECT_TRUE(matcher.match(v));

    v[9999] = -1;
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchWithDuplicateElements_969) {
    std::vector<int> comparator = {1, 1, 2, 2, 3, 3};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::vector<int> v = {1, 1, 2, 2, 3, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchWithDuplicateElementsDifferentCount_969) {
    std::vector<int> comparator = {1, 1, 2, 2, 3, 3};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::vector<int> v = {1, 2, 2, 3, 3, 3};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchReturnsTrueForIdenticalDoubleVectors_969) {
    std::vector<double> comparator = {1.0, 2.5, 3.7};
    EqualsMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    std::vector<double> v = {1.0, 2.5, 3.7};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchReturnsFalseForDifferentDoubleVectors_969) {
    std::vector<double> comparator = {1.0, 2.5, 3.7};
    EqualsMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    std::vector<double> v = {1.0, 2.5, 3.8};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, DescribeContainsStringifiedComparator_969) {
    std::vector<int> comparator = {1, 2, 3};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::string description = matcher.describe();
    // The description should contain representation of the comparator elements
    EXPECT_FALSE(description.empty());
    EXPECT_NE(description.find("Equals:"), std::string::npos);
}

TEST_F(EqualsMatcherTest_969, MatchWithNegativeNumbers_969) {
    std::vector<int> comparator = {-1, -2, -3};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::vector<int> v = {-1, -2, -3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(EqualsMatcherTest_969, MatchSelfComparison_969) {
    std::vector<int> comparator = {1, 2, 3};
    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(comparator));
}
