#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>
#include <functional>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// Test fixture
class FindSentinelTest_943 : public ::testing::Test {
protected:
    // Common comparators
    static constexpr auto equal_to_int = [](int a, int b) { return a == b; };
    static constexpr auto equal_to_str = [](const std::string& a, const std::string& b) { return a == b; };
};

// Normal operation: find an element that exists in the range
TEST_F(FindSentinelTest_943, FindsExistingElement_943) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 3, std::equal_to<int>{}
    );
    ASSERT_NE(result, vec.end());
    EXPECT_EQ(*result, 3);
}

// Normal operation: find the first element
TEST_F(FindSentinelTest_943, FindsFirstElement_943) {
    std::vector<int> vec = {10, 20, 30};
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 10, std::equal_to<int>{}
    );
    ASSERT_NE(result, vec.end());
    EXPECT_EQ(*result, 10);
    EXPECT_EQ(result, vec.begin());
}

// Normal operation: find the last element
TEST_F(FindSentinelTest_943, FindsLastElement_943) {
    std::vector<int> vec = {10, 20, 30};
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 30, std::equal_to<int>{}
    );
    ASSERT_NE(result, vec.end());
    EXPECT_EQ(*result, 30);
    EXPECT_EQ(result, vec.begin() + 2);
}

// Element not found: returns sentinel
TEST_F(FindSentinelTest_943, ReturnsEndWhenElementNotFound_943) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 99, std::equal_to<int>{}
    );
    EXPECT_EQ(result, vec.end());
}

// Boundary: empty range
TEST_F(FindSentinelTest_943, EmptyRangeReturnsSentinel_943) {
    std::vector<int> vec;
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 1, std::equal_to<int>{}
    );
    EXPECT_EQ(result, vec.end());
}

// Boundary: single element found
TEST_F(FindSentinelTest_943, SingleElementFound_943) {
    std::vector<int> vec = {42};
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 42, std::equal_to<int>{}
    );
    ASSERT_NE(result, vec.end());
    EXPECT_EQ(*result, 42);
}

// Boundary: single element not found
TEST_F(FindSentinelTest_943, SingleElementNotFound_943) {
    std::vector<int> vec = {42};
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 7, std::equal_to<int>{}
    );
    EXPECT_EQ(result, vec.end());
}

// Duplicate elements: returns the first match
TEST_F(FindSentinelTest_943, ReturnFirstMatchWhenDuplicatesExist_943) {
    std::vector<int> vec = {1, 2, 3, 2, 5};
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 2, std::equal_to<int>{}
    );
    ASSERT_NE(result, vec.end());
    EXPECT_EQ(*result, 2);
    // Should be the first occurrence
    EXPECT_EQ(std::distance(vec.begin(), result), 1);
}

// Custom comparator: less-than
TEST_F(FindSentinelTest_943, CustomComparatorLessThan_943) {
    std::vector<int> vec = {5, 3, 8, 1};
    // Find first element less than 4
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 4,
        [](int elem, int val) { return elem < val; }
    );
    ASSERT_NE(result, vec.end());
    EXPECT_EQ(*result, 3);
}

// Custom comparator: greater-than
TEST_F(FindSentinelTest_943, CustomComparatorGreaterThan_943) {
    std::vector<int> vec = {1, 2, 10, 4};
    // Find first element greater than 5
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 5,
        [](int elem, int val) { return elem > val; }
    );
    ASSERT_NE(result, vec.end());
    EXPECT_EQ(*result, 10);
}

// Custom comparator that never matches
TEST_F(FindSentinelTest_943, ComparatorNeverMatchesReturnsSentinel_943) {
    std::vector<int> vec = {1, 2, 3};
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 0,
        [](int, int) { return false; }
    );
    EXPECT_EQ(result, vec.end());
}

// Custom comparator that always matches returns first element
TEST_F(FindSentinelTest_943, ComparatorAlwaysMatchesReturnsFirst_943) {
    std::vector<int> vec = {1, 2, 3};
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 0,
        [](int, int) { return true; }
    );
    ASSERT_NE(result, vec.end());
    EXPECT_EQ(result, vec.begin());
    EXPECT_EQ(*result, 1);
}

// Works with strings
TEST_F(FindSentinelTest_943, WorksWithStrings_943) {
    std::vector<std::string> vec = {"hello", "world", "foo", "bar"};
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), std::string("foo"), std::equal_to<std::string>{}
    );
    ASSERT_NE(result, vec.end());
    EXPECT_EQ(*result, "foo");
}

// Works with strings - not found
TEST_F(FindSentinelTest_943, StringNotFound_943) {
    std::vector<std::string> vec = {"hello", "world"};
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), std::string("missing"), std::equal_to<std::string>{}
    );
    EXPECT_EQ(result, vec.end());
}

// Works with list (bidirectional iterator instead of random access)
TEST_F(FindSentinelTest_943, WorksWithListIterators_943) {
    std::list<int> lst = {10, 20, 30, 40};
    auto result = Catch::Detail::find_sentinel(
        lst.begin(), lst.end(), 30, std::equal_to<int>{}
    );
    ASSERT_NE(result, lst.end());
    EXPECT_EQ(*result, 30);
}

// Works with raw pointers as iterators
TEST_F(FindSentinelTest_943, WorksWithRawPointers_943) {
    int arr[] = {5, 10, 15, 20, 25};
    int* begin = arr;
    int* end = arr + 5;
    auto result = Catch::Detail::find_sentinel(
        begin, end, 15, std::equal_to<int>{}
    );
    ASSERT_NE(result, end);
    EXPECT_EQ(*result, 15);
}

// Works with raw pointers - not found
TEST_F(FindSentinelTest_943, RawPointersNotFound_943) {
    int arr[] = {5, 10, 15};
    int* begin = arr;
    int* end = arr + 3;
    auto result = Catch::Detail::find_sentinel(
        begin, end, 99, std::equal_to<int>{}
    );
    EXPECT_EQ(result, end);
}

// Partial range search
TEST_F(FindSentinelTest_943, PartialRangeSearch_943) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    // Search only in [begin+1, begin+4), so elements {2, 3, 4}
    auto result = Catch::Detail::find_sentinel(
        vec.begin() + 1, vec.begin() + 4, 4, std::equal_to<int>{}
    );
    ASSERT_NE(result, vec.begin() + 4);
    EXPECT_EQ(*result, 4);
}

// Partial range: element exists outside the searched sub-range
TEST_F(FindSentinelTest_943, ElementOutsideSubRange_943) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    // Search in {2, 3, 4} for 5, which is outside
    auto result = Catch::Detail::find_sentinel(
        vec.begin() + 1, vec.begin() + 4, 5, std::equal_to<int>{}
    );
    EXPECT_EQ(result, vec.begin() + 4);
}

// Verify comparator is called with correct arguments (element first, value second)
TEST_F(FindSentinelTest_943, ComparatorReceivesCorrectArguments_943) {
    std::vector<int> vec = {10};
    bool called = false;
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 42,
        [&called](int elem, int val) {
            called = true;
            EXPECT_EQ(elem, 10);
            EXPECT_EQ(val, 42);
            return true;
        }
    );
    EXPECT_TRUE(called);
    ASSERT_NE(result, vec.end());
    EXPECT_EQ(*result, 10);
}

// Large range
TEST_F(FindSentinelTest_943, LargeRange_943) {
    std::vector<int> vec(10000);
    for (int i = 0; i < 10000; ++i) {
        vec[i] = i;
    }
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 9999, std::equal_to<int>{}
    );
    ASSERT_NE(result, vec.end());
    EXPECT_EQ(*result, 9999);
}

// Large range - element at beginning
TEST_F(FindSentinelTest_943, LargeRangeFirstElement_943) {
    std::vector<int> vec(10000);
    for (int i = 0; i < 10000; ++i) {
        vec[i] = i;
    }
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 0, std::equal_to<int>{}
    );
    ASSERT_NE(result, vec.end());
    EXPECT_EQ(*result, 0);
    EXPECT_EQ(result, vec.begin());
}

// All elements are the same - should return iterator to first
TEST_F(FindSentinelTest_943, AllSameElements_943) {
    std::vector<int> vec(5, 7);
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 7, std::equal_to<int>{}
    );
    ASSERT_NE(result, vec.end());
    EXPECT_EQ(result, vec.begin());
    EXPECT_EQ(*result, 7);
}

// Negative values
TEST_F(FindSentinelTest_943, NegativeValues_943) {
    std::vector<int> vec = {-5, -3, -1, 0, 1};
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), -3, std::equal_to<int>{}
    );
    ASSERT_NE(result, vec.end());
    EXPECT_EQ(*result, -3);
}

// Double type
TEST_F(FindSentinelTest_943, WorksWithDoubles_943) {
    std::vector<double> vec = {1.1, 2.2, 3.3};
    auto result = Catch::Detail::find_sentinel(
        vec.begin(), vec.end(), 2.2, std::equal_to<double>{}
    );
    ASSERT_NE(result, vec.end());
    EXPECT_DOUBLE_EQ(*result, 2.2);
}
