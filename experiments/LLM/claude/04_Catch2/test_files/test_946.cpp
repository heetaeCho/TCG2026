#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <array>
#include <forward_list>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// Test with empty range
TEST(SentinelDistanceTest_946, EmptyRange_946) {
    std::vector<int> v;
    auto result = Catch::Detail::sentinel_distance(v.begin(), v.end());
    EXPECT_EQ(result, 0);
}

// Test with single element vector
TEST(SentinelDistanceTest_946, SingleElement_946) {
    std::vector<int> v = {42};
    auto result = Catch::Detail::sentinel_distance(v.begin(), v.end());
    EXPECT_EQ(result, 1);
}

// Test with multiple elements in a vector
TEST(SentinelDistanceTest_946, MultipleElements_946) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto result = Catch::Detail::sentinel_distance(v.begin(), v.end());
    EXPECT_EQ(result, 5);
}

// Test with a list (bidirectional iterator)
TEST(SentinelDistanceTest_946, ListIterator_946) {
    std::list<int> l = {10, 20, 30};
    auto result = Catch::Detail::sentinel_distance(l.begin(), l.end());
    EXPECT_EQ(result, 3);
}

// Test with empty list
TEST(SentinelDistanceTest_946, EmptyList_946) {
    std::list<int> l;
    auto result = Catch::Detail::sentinel_distance(l.begin(), l.end());
    EXPECT_EQ(result, 0);
}

// Test with string iterators
TEST(SentinelDistanceTest_946, StringIterator_946) {
    std::string s = "hello";
    auto result = Catch::Detail::sentinel_distance(s.begin(), s.end());
    EXPECT_EQ(result, 5);
}

// Test with empty string
TEST(SentinelDistanceTest_946, EmptyString_946) {
    std::string s;
    auto result = Catch::Detail::sentinel_distance(s.begin(), s.end());
    EXPECT_EQ(result, 0);
}

// Test with array
TEST(SentinelDistanceTest_946, ArrayIterator_946) {
    std::array<int, 4> arr = {1, 2, 3, 4};
    auto result = Catch::Detail::sentinel_distance(arr.begin(), arr.end());
    EXPECT_EQ(result, 4);
}

// Test with partial range (subrange of a vector)
TEST(SentinelDistanceTest_946, PartialRange_946) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto first = v.begin() + 2;
    auto last = v.begin() + 7;
    auto result = Catch::Detail::sentinel_distance(first, last);
    EXPECT_EQ(result, 5);
}

// Test with same iterator (zero distance)
TEST(SentinelDistanceTest_946, SameIterator_946) {
    std::vector<int> v = {1, 2, 3};
    auto result = Catch::Detail::sentinel_distance(v.begin(), v.begin());
    EXPECT_EQ(result, 0);
}

// Test return type is std::ptrdiff_t
TEST(SentinelDistanceTest_946, ReturnType_946) {
    std::vector<int> v = {1, 2, 3};
    auto result = Catch::Detail::sentinel_distance(v.begin(), v.end());
    static_assert(std::is_same<decltype(result), std::ptrdiff_t>::value,
                  "Return type should be std::ptrdiff_t");
    EXPECT_EQ(result, 3);
}

// Test with large container
TEST(SentinelDistanceTest_946, LargeContainer_946) {
    std::vector<int> v(10000, 0);
    auto result = Catch::Detail::sentinel_distance(v.begin(), v.end());
    EXPECT_EQ(result, 10000);
}

// Test with forward_list (forward iterator only)
TEST(SentinelDistanceTest_946, ForwardListIterator_946) {
    std::forward_list<int> fl = {1, 2, 3, 4};
    auto result = Catch::Detail::sentinel_distance(fl.begin(), fl.end());
    EXPECT_EQ(result, 4);
}

// Test with empty forward_list
TEST(SentinelDistanceTest_946, EmptyForwardList_946) {
    std::forward_list<int> fl;
    auto result = Catch::Detail::sentinel_distance(fl.begin(), fl.end());
    EXPECT_EQ(result, 0);
}

// Test with pointer as iterator (raw array)
TEST(SentinelDistanceTest_946, RawPointerIterator_946) {
    int arr[] = {10, 20, 30, 40, 50};
    auto result = Catch::Detail::sentinel_distance(std::begin(arr), std::end(arr));
    EXPECT_EQ(result, 5);
}

// Test with const iterators
TEST(SentinelDistanceTest_946, ConstIterator_946) {
    const std::vector<int> v = {1, 2, 3, 4, 5, 6};
    auto result = Catch::Detail::sentinel_distance(v.cbegin(), v.cend());
    EXPECT_EQ(result, 6);
}

// Test with single element list
TEST(SentinelDistanceTest_946, SingleElementList_946) {
    std::list<double> l = {3.14};
    auto result = Catch::Detail::sentinel_distance(l.begin(), l.end());
    EXPECT_EQ(result, 1);
}
