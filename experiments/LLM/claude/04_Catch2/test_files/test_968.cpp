#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

// ============================================================
// Tests for EqualsMatcher with int vectors
// ============================================================

class EqualsMatcherTest_968 : public ::testing::Test {
protected:
    // Helper to create an EqualsMatcher
    template<typename T>
    EqualsMatcher<T, std::allocator<T>, std::allocator<T>> makeEqualsMatcher(const std::vector<T>& comparator) {
        return EqualsMatcher<T, std::allocator<T>, std::allocator<T>>(comparator);
    }
};

// Test: Two identical non-empty integer vectors should match
TEST_F(EqualsMatcherTest_968, IdenticalIntVectorsMatch_968) {
    std::vector<int> comparator = {1, 2, 3, 4, 5};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Two empty vectors should match
TEST_F(EqualsMatcherTest_968, EmptyVectorsMatch_968) {
    std::vector<int> comparator = {};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Different sizes should not match (comparator larger)
TEST_F(EqualsMatcherTest_968, DifferentSizesDoNotMatch_ComparatorLarger_968) {
    std::vector<int> comparator = {1, 2, 3};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {1, 2};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Different sizes should not match (target larger)
TEST_F(EqualsMatcherTest_968, DifferentSizesDoNotMatch_TargetLarger_968) {
    std::vector<int> comparator = {1, 2};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {1, 2, 3};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Same size but different elements should not match
TEST_F(EqualsMatcherTest_968, SameSizeDifferentElementsDoNotMatch_968) {
    std::vector<int> comparator = {1, 2, 3};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {1, 2, 4};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Vectors with single element that matches
TEST_F(EqualsMatcherTest_968, SingleElementMatch_968) {
    std::vector<int> comparator = {42};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {42};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Vectors with single element that does not match
TEST_F(EqualsMatcherTest_968, SingleElementNoMatch_968) {
    std::vector<int> comparator = {42};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {43};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Difference only at the first element
TEST_F(EqualsMatcherTest_968, DifferenceAtFirstElement_968) {
    std::vector<int> comparator = {1, 2, 3};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {99, 2, 3};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Difference only at the last element
TEST_F(EqualsMatcherTest_968, DifferenceAtLastElement_968) {
    std::vector<int> comparator = {1, 2, 3};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {1, 2, 99};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Empty comparator vs non-empty target should not match
TEST_F(EqualsMatcherTest_968, EmptyComparatorNonEmptyTarget_968) {
    std::vector<int> comparator = {};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {1};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Non-empty comparator vs empty target should not match
TEST_F(EqualsMatcherTest_968, NonEmptyComparatorEmptyTarget_968) {
    std::vector<int> comparator = {1};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Same elements but different order should not match
TEST_F(EqualsMatcherTest_968, SameElementsDifferentOrder_968) {
    std::vector<int> comparator = {1, 2, 3};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {3, 2, 1};
    EXPECT_FALSE(matcher.match(target));
}

// Test: With string type - identical vectors match
TEST_F(EqualsMatcherTest_968, StringVectorsMatch_968) {
    std::vector<std::string> comparator = {"hello", "world"};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<std::string> target = {"hello", "world"};
    EXPECT_TRUE(matcher.match(target));
}

// Test: With string type - different vectors do not match
TEST_F(EqualsMatcherTest_968, StringVectorsDoNotMatch_968) {
    std::vector<std::string> comparator = {"hello", "world"};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<std::string> target = {"hello", "earth"};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Large identical vectors should match
TEST_F(EqualsMatcherTest_968, LargeIdenticalVectorsMatch_968) {
    std::vector<int> comparator(1000);
    for (int i = 0; i < 1000; ++i) {
        comparator[i] = i;
    }
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Large vectors with one difference should not match
TEST_F(EqualsMatcherTest_968, LargeVectorsOneDifference_968) {
    std::vector<int> comparator(1000);
    for (int i = 0; i < 1000; ++i) {
        comparator[i] = i;
    }
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target(comparator);
    target[999] = -1;
    EXPECT_FALSE(matcher.match(target));
}

// Test: Vectors with duplicate elements that match
TEST_F(EqualsMatcherTest_968, DuplicateElementsMatch_968) {
    std::vector<int> comparator = {5, 5, 5, 5};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {5, 5, 5, 5};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Vectors with duplicate elements that don't match
TEST_F(EqualsMatcherTest_968, DuplicateElementsDoNotMatch_968) {
    std::vector<int> comparator = {5, 5, 5, 5};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {5, 5, 5, 6};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Vectors with negative numbers
TEST_F(EqualsMatcherTest_968, NegativeNumbersMatch_968) {
    std::vector<int> comparator = {-1, -2, -3};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {-1, -2, -3};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Vectors with mixed positive and negative numbers
TEST_F(EqualsMatcherTest_968, MixedSignNumbersDoNotMatch_968) {
    std::vector<int> comparator = {-1, 2, -3};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<int> target = {1, 2, -3};
    EXPECT_FALSE(matcher.match(target));
}

// Test: describe() returns a non-empty string
TEST_F(EqualsMatcherTest_968, DescribeReturnsNonEmptyString_968) {
    std::vector<int> comparator = {1, 2, 3};
    auto matcher = makeEqualsMatcher(comparator);

    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test: With double type - identical vectors match
TEST_F(EqualsMatcherTest_968, DoubleVectorsMatch_968) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<double> target = {1.0, 2.0, 3.0};
    EXPECT_TRUE(matcher.match(target));
}

// Test: With double type - different vectors do not match
TEST_F(EqualsMatcherTest_968, DoubleVectorsDoNotMatch_968) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = makeEqualsMatcher(comparator);

    std::vector<double> target = {1.0, 2.0, 3.1};
    EXPECT_FALSE(matcher.match(target));
}
