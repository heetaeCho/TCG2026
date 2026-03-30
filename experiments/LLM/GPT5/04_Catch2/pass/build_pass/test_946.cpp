// File: tests/sentinel_distance_946_tests.cpp

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <forward_list>
#include <iterator>
#include <array>

#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Detail::sentinel_distance;

namespace {

// -------------------------------
// Normal operation: pointers
// -------------------------------
TEST(SentinelDistanceTest_946, PointerFullRange_946) {
    int arr[] = {1, 2, 3, 4, 5};
    auto d = sentinel_distance(std::begin(arr), std::end(arr));
    EXPECT_EQ(d, 5);
}

// -------------------------------
// Boundary: same iterator => zero
// -------------------------------
TEST(SentinelDistanceTest_946, SameIteratorZero_946) {
    std::vector<int> v;            // empty
    auto d = sentinel_distance(v.begin(), v.begin());
    EXPECT_EQ(d, 0);
}

// -------------------------------
// Normal operation: vector (random access, whole range)
// -------------------------------
TEST(SentinelDistanceTest_946, VectorWholeRange_946) {
    std::vector<int> v = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    auto d = sentinel_distance(v.begin(), v.end());
    EXPECT_EQ(d, static_cast<std::ptrdiff_t>(v.size()));
}

// -------------------------------
// Normal operation: forward_list (forward iterator category)
// -------------------------------
TEST(SentinelDistanceTest_946, ForwardListWholeRange_946) {
    std::forward_list<int> fl = {1, 2, 3, 4, 5, 6, 7};
    auto d = sentinel_distance(fl.begin(), fl.end());
    // std::distance for forward iterators yields element count
    EXPECT_EQ(d, 7);
}

// -------------------------------
// Subrange: list (bidirectional iterator)
// -------------------------------
TEST(SentinelDistanceTest_946, ListSubrange_946) {
    std::list<int> ls = {0, 1, 2, 3, 4, 5, 6};
    auto first = ls.begin();
    std::advance(first, 3); // points to element '3'
    auto d = sentinel_distance(first, ls.end());
    EXPECT_EQ(d, 4); // elements: 3,4,5,6
}

// -------------------------------
// Subrange: vector (random access) middle slice
// -------------------------------
TEST(SentinelDistanceTest_946, VectorMiddleSubrange_946) {
    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9};
    auto first = v.begin() + 2; // points to 2
    auto last  = v.begin() + 7; // points past 6, i.e., up to index 6 inclusive
    auto d = sentinel_distance(first, last);
    EXPECT_EQ(d, 5); // elements: 2,3,4,5,6
}

// -------------------------------
// Larger range sanity: confirms it scales with size
// -------------------------------
TEST(SentinelDistanceTest_946, LargeVectorRange_946) {
    std::vector<int> v(1000, 42);
    auto d = sentinel_distance(v.begin(), v.end());
    EXPECT_EQ(d, 1000);
}

// -------------------------------
// (Optional) constexpr validation when available
// Guarded because std::distance constexpr depends on standard/library
// -------------------------------
#if defined(__cpp_lib_constexpr_algorithms) && __cpp_lib_constexpr_algorithms >= 201806L
TEST(SentinelDistanceTest_946, ConstexprPointerRangeWhenAvailable_946) {
    constexpr int arr[] = {1,2,3,4};
    // Note: This ensures the expression is valid at runtime; compile-time checks
    // are only performed when the standard library supports constexpr algorithms.
    constexpr auto expected = 4;
    auto d = sentinel_distance(std::begin(arr), std::end(arr));
    EXPECT_EQ(d, expected);
}
#endif

// NOTE: We intentionally do NOT test cases where first comes after last for
// forward/bidirectional iterators, as such usage is outside the contract of
// forward-range semantics and is not observable "normal" behavior via the
// public interface.

} // namespace
