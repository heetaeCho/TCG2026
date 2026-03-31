#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>
#include <catch2/matchers/catch_matchers.hpp>

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <functional>

using namespace Catch::Matchers;

class RangeEqualsMatcherTest_957 : public ::testing::Test {
protected:
};

// Test: Matching identical integer vectors returns true
TEST_F(RangeEqualsMatcherTest_957, IdenticalVectorsMatch_957) {
    std::vector<int> desired = {1, 2, 3, 4, 5};
    std::vector<int> actual = {1, 2, 3, 4, 5};
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(actual));
}

// Test: Different vectors do not match
TEST_F(RangeEqualsMatcherTest_957, DifferentVectorsDoNotMatch_957) {
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> actual = {1, 2, 4};
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(actual));
}

// Test: Empty ranges match
TEST_F(RangeEqualsMatcherTest_957, EmptyRangesMatch_957) {
    std::vector<int> desired = {};
    std::vector<int> actual = {};
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(actual));
}

// Test: Different sized ranges do not match
TEST_F(RangeEqualsMatcherTest_957, DifferentSizedRangesDoNotMatch_957) {
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> actual = {1, 2};
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(actual));
}

// Test: Actual range longer than desired does not match
TEST_F(RangeEqualsMatcherTest_957, ActualLongerThanDesiredDoesNotMatch_957) {
    std::vector<int> desired = {1, 2};
    std::vector<int> actual = {1, 2, 3};
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(actual));
}

// Test: Single element ranges that match
TEST_F(RangeEqualsMatcherTest_957, SingleElementMatch_957) {
    std::vector<int> desired = {42};
    std::vector<int> actual = {42};
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(actual));
}

// Test: Single element ranges that don't match
TEST_F(RangeEqualsMatcherTest_957, SingleElementNoMatch_957) {
    std::vector<int> desired = {42};
    std::vector<int> actual = {43};
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(actual));
}

// Test: Custom predicate for matching
TEST_F(RangeEqualsMatcherTest_957, CustomPredicateMatch_957) {
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> actual = {2, 4, 6};
    auto predicate = [](int a, int b) { return a == 2 * b; };
    auto matcher = RangeEqualsMatcher<std::vector<int>, decltype(predicate)>(desired, predicate);
    EXPECT_TRUE(matcher.match(actual));
}

// Test: Custom predicate that doesn't match
TEST_F(RangeEqualsMatcherTest_957, CustomPredicateNoMatch_957) {
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> actual = {2, 4, 7};
    auto predicate = [](int a, int b) { return a == 2 * b; };
    auto matcher = RangeEqualsMatcher<std::vector<int>, decltype(predicate)>(desired, predicate);
    EXPECT_FALSE(matcher.match(actual));
}

// Test: Matching with different container types (list vs vector)
TEST_F(RangeEqualsMatcherTest_957, DifferentContainerTypesMatch_957) {
    std::vector<int> desired = {1, 2, 3};
    std::list<int> actual = {1, 2, 3};
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(actual));
}

// Test: Matching with array
TEST_F(RangeEqualsMatcherTest_957, ArrayMatch_957) {
    std::array<int, 3> desired = {1, 2, 3};
    std::vector<int> actual = {1, 2, 3};
    auto matcher = RangeEqualsMatcher<std::array<int, 3>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(actual));
}

// Test: describe() returns a meaningful string
TEST_F(RangeEqualsMatcherTest_957, DescribeContainsElements_957) {
    std::vector<int> desired = {1, 2, 3};
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
    EXPECT_NE(description.find("elements are"), std::string::npos);
}

// Test: describe() for empty range
TEST_F(RangeEqualsMatcherTest_957, DescribeEmptyRange_957) {
    std::vector<int> desired = {};
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
    EXPECT_NE(description.find("elements are"), std::string::npos);
}

// Test: Order matters - same elements different order should not match
TEST_F(RangeEqualsMatcherTest_957, OrderMatters_957) {
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> actual = {3, 2, 1};
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(actual));
}

// Test: String ranges match
TEST_F(RangeEqualsMatcherTest_957, StringRangesMatch_957) {
    std::vector<std::string> desired = {"hello", "world"};
    std::vector<std::string> actual = {"hello", "world"};
    auto matcher = RangeEqualsMatcher<std::vector<std::string>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(actual));
}

// Test: String ranges don't match
TEST_F(RangeEqualsMatcherTest_957, StringRangesNoMatch_957) {
    std::vector<std::string> desired = {"hello", "world"};
    std::vector<std::string> actual = {"hello", "earth"};
    auto matcher = RangeEqualsMatcher<std::vector<std::string>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(actual));
}

// Test: Empty actual vs non-empty desired
TEST_F(RangeEqualsMatcherTest_957, EmptyActualNonEmptyDesired_957) {
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> actual = {};
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(actual));
}

// Test: Non-empty actual vs empty desired
TEST_F(RangeEqualsMatcherTest_957, NonEmptyActualEmptyDesired_957) {
    std::vector<int> desired = {};
    std::vector<int> actual = {1, 2, 3};
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(actual));
}

// Test: Large identical ranges match
TEST_F(RangeEqualsMatcherTest_957, LargeRangesMatch_957) {
    std::vector<int> desired(1000);
    std::vector<int> actual(1000);
    for (int i = 0; i < 1000; ++i) {
        desired[i] = i;
        actual[i] = i;
    }
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(actual));
}

// Test: Large ranges differ at last element
TEST_F(RangeEqualsMatcherTest_957, LargeRangesDifferAtEnd_957) {
    std::vector<int> desired(1000);
    std::vector<int> actual(1000);
    for (int i = 0; i < 1000; ++i) {
        desired[i] = i;
        actual[i] = i;
    }
    actual[999] = -1;
    auto matcher = RangeEqualsMatcher<std::vector<int>, std::equal_to<>>(desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(actual));
}
