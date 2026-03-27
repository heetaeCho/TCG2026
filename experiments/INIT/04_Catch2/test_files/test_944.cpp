// File: tests/count_sentinel_tests_944.cpp

#include <gtest/gtest.h>
#include <vector>
#include <cstddef>
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Detail::count_sentinel;

namespace {

// A stateful comparator to verify external interactions (call counts).
struct CountingEq {
    int* calls; // non-owning
    explicit CountingEq(int& c) : calls(&c) {}
    bool operator()(int a, int b) const {
        ++(*calls);
        return a == b;
    }
};

// A custom sentinel type different from the iterator type.
struct IntPtrSentinel {
    const int* end;
    // Enable comparison: iterator (const int*) != sentinel
    friend bool operator!=(const int* it, IntPtrSentinel s) {
        return it != s.end;
    }
};

} // namespace

// ---------- Normal operation ----------

TEST(CountSentinelTest_944, EmptyRangeReturnsZero_944) {
    std::vector<int> v; // start == sentinel
    auto eq = [](int a, int b) { return a == b; };
    EXPECT_EQ(count_sentinel(v.begin(), v.end(), 123, eq), 0);
}

TEST(CountSentinelTest_944, NoMatches_944) {
    std::vector<int> v{1, 2, 3, 4};
    auto eq = [](int a, int b) { return a == b; };
    EXPECT_EQ(count_sentinel(v.begin(), v.end(), 99, eq), 0);
}

TEST(CountSentinelTest_944, AllMatch_944) {
    std::vector<int> v{5, 5, 5};
    auto eq = [](int a, int b) { return a == b; };
    EXPECT_EQ(count_sentinel(v.begin(), v.end(), 5, eq), 3);
}

TEST(CountSentinelTest_944, SomeMatch_944) {
    std::vector<int> v{1, 2, 1, 3, 1};
    auto eq = [](int a, int b) { return a == b; };
    EXPECT_EQ(count_sentinel(v.begin(), v.end(), 1, eq), 3);
}

// ---------- Boundary conditions ----------

TEST(CountSentinelTest_944, SingleElementMatch_944) {
    std::vector<int> v{7};
    auto eq = [](int a, int b) { return a == b; };
    EXPECT_EQ(count_sentinel(v.begin(), v.end(), 7, eq), 1);
}

TEST(CountSentinelTest_944, StopsAtSentinelEarly_944) {
    int arr[] = {1, 1, 1, 1};
    auto eq = [](int a, int b) { return a == b; };
    // Only count up to arr + 2 (exclusive)
    EXPECT_EQ(count_sentinel(arr, arr + 2, 1, eq), 2);
}

// ---------- Custom comparator semantics ----------

TEST(CountSentinelTest_944, CustomComparatorLessThan_944) {
    std::vector<int> v{1, 3, 5, 7};
    auto lt = [](int a, int b) { return a < b; };
    // Count elements less than 4: {1,3} -> 2
    EXPECT_EQ(count_sentinel(v.begin(), v.end(), 4, lt), 2);
}

// ---------- Verification of external interactions ----------

TEST(CountSentinelTest_944, ComparatorCallCountMatchesTraversedElements_944) {
    std::vector<int> v{1, 2, 2, 3, 4};
    int calls = 0;
    CountingEq cmp{calls};
    int result = count_sentinel(v.begin(), v.end(), 2, cmp);
    // Should traverse every element exactly once
    EXPECT_EQ(calls, static_cast<int>(v.size()));
    // And count two matches
    EXPECT_EQ(result, 2);
}

// ---------- Distinct sentinel type (iterator/sentinel mismatch) ----------

TEST(CountSentinelTest_944, WorksWithDifferentSentinelType_944) {
    int arr[] = {1, 2, 3, 2, 1};
    auto eq = [](int a, int b) { return a == b; };
    // Use pointer as ForwardIter and custom sentinel that ends at arr + 3
    IntPtrSentinel s{arr + 3}; // stops before indices 3 and 4
    // Range considered: arr[0], arr[1], arr[2] -> only one '2' at index 1
    EXPECT_EQ(count_sentinel(arr, s, 2, eq), 1);
}

// ---------- Compile-time (constexpr) evaluation ----------

namespace {
constexpr bool constexpr_check() {
    constexpr int arr[] = {1, 2, 3, 2};
    // Equality comparator
    return count_sentinel(arr, arr + 4, 2, [](int a, int b) { return a == b; }) == 2;
}
} // namespace

static_assert(constexpr_check(), "count_sentinel should be usable at compile time (TEST_ID 944).")
