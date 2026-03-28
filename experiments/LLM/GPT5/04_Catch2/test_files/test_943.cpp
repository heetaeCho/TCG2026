// File: find_sentinel_943_tests.cpp
// Tests for Catch::Detail::find_sentinel (black-box, interface-only)

#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <forward_list>
#include <iterator>
#include <type_traits>

// CUT
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Detail::find_sentinel;

// ---------- Helpers (test-only) ----------

// Comparator that counts how many times it is invoked.
template <typename Eq = std::equal_to<>>
struct CountingCmp {
    int& calls;
    Eq eq{};
    template <typename L, typename R>
    bool operator()(const L& l, const R& r) const {
        ++calls;
        return eq(l, r);
    }
};

// A different "sentinel" type that can be compared with an iterator.
// start != sentinel should become (start != end_it_).
template <typename Iter>
struct LimitSentinel {
    Iter end_it_;
};
template <typename Iter>
bool operator!=(Iter it, const LimitSentinel<Iter>& s) {
    return it != s.end_it_;
}

// ---------- A few constexpr sanity checks (compile-time evaluation) ----------
namespace {
    // equal comparator for constexpr
    struct CxEq {
        constexpr bool operator()(int a, int b) const { return a == b; }
    };

    // Found case
    constexpr const int cx_arr1[] = {1, 2, 3, 4};
    static_assert(
        find_sentinel(cx_arr1, cx_arr1 + 4, 3, CxEq{}) == cx_arr1 + 2,
        "constexpr: should find value at index 2");

    // Not found case
    constexpr const int cx_arr2[] = {5, 6, 7};
    static_assert(
        find_sentinel(cx_arr2, cx_arr2 + 3, 4, CxEq{}) == cx_arr2 + 3,
        "constexpr: should return sentinel when not found");
} // namespace

// ---------- Runtime tests ----------

TEST(FindSentinelTest_943, EmptyRange_ReturnsStart_943) {
    std::vector<int> v;
    int calls = 0;
    auto it = find_sentinel(v.begin(), v.end(), 123, CountingCmp<>{calls});
    EXPECT_EQ(it, v.begin());
    EXPECT_EQ(calls, 0) << "Comparator must not be called for empty range";
}

TEST(FindSentinelTest_943, ValueAtFirst_ReturnsBegin_943) {
    std::vector<int> v{3, 1, 2};
    int calls = 0;
    auto it = find_sentinel(v.begin(), v.end(), 3, CountingCmp<>{calls});
    ASSERT_EQ(it, v.begin());
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(calls, 1);
}

TEST(FindSentinelTest_943, ValueInMiddle_ReturnsIterator_943) {
    std::vector<int> v{1, 4, 5};
    int calls = 0;
    auto it = find_sentinel(v.begin(), v.end(), 4, CountingCmp<>{calls});
    ASSERT_NE(it, v.end());
    EXPECT_EQ(std::distance(v.begin(), it), 1);
    EXPECT_EQ(*it, 4);
    EXPECT_EQ(calls, 2); // checked 1 then 4
}

TEST(FindSentinelTest_943, ValueAtLast_ReturnsLast_943) {
    std::vector<int> v{7, 8, 9};
    int calls = 0;
    auto it = find_sentinel(v.begin(), v.end(), 9, CountingCmp<>{calls});
    ASSERT_NE(it, v.end());
    EXPECT_EQ(std::distance(v.begin(), it), 2);
    EXPECT_EQ(*it, 9);
    EXPECT_EQ(calls, 3);
}

TEST(FindSentinelTest_943, ValueNotFound_ReturnsSentinel_943) {
    std::vector<int> v{1, 2, 3};
    int calls = 0;
    auto it = find_sentinel(v.begin(), v.end(), 5, CountingCmp<>{calls});
    EXPECT_EQ(it, v.end());
    EXPECT_EQ(calls, static_cast<int>(v.size()));
}

TEST(FindSentinelTest_943, StopsAtFirstMatch_WhenDuplicates_943) {
    std::vector<int> v{2, 3, 2, 2};
    int calls = 0;
    auto it = find_sentinel(v.begin(), v.end(), 2, CountingCmp<>{calls});
    ASSERT_EQ(it, v.begin());
    EXPECT_EQ(*it, 2);
    EXPECT_EQ(calls, 1) << "Must stop at the first match";
}

TEST(FindSentinelTest_943, WorksWithPointerIterators_943) {
    int a[] = {1, 2, 3, 4};
    int* start = &a[0];
    int* sent  = &a[4];
    auto it = find_sentinel(start, sent, 2, std::equal_to<>{});
    ASSERT_EQ(it, &a[1]);
    EXPECT_EQ(*it, 2);
}

TEST(FindSentinelTest_943, CustomComparator_GreaterThan_943) {
    std::vector<int> v{1, 3, 2, 5};
    // Find first element greater than 2 -> should be 3 at index 1
    auto greater_than = [](int x, int y){ return x > y; };
    auto it = find_sentinel(v.begin(), v.end(), 2, greater_than);
    ASSERT_NE(it, v.end());
    EXPECT_EQ(std::distance(v.begin(), it), 1);
    EXPECT_EQ(*it, 3);
}

TEST(FindSentinelTest_943, DifferentSentinelType_LimitsRange_NoMatchWithinLimit_943) {
    std::vector<int> v{10, 20, 30, 40, 50};
    // Limit the search to the first 2 elements (indices 0..1)
    LimitSentinel end2{v.begin() + 2};
    int calls = 0;
    auto it = find_sentinel(v.begin(), end2, 30, CountingCmp<>{calls});
    // 30 is at index 2, but sentinel stops iteration early
    EXPECT_EQ(it, v.begin() + 2);
    EXPECT_EQ(calls, 2) << "Comparator invoked only for elements before sentinel";
}

TEST(FindSentinelTest_943, DifferentSentinelType_FoundBeforeLimit_943) {
    std::vector<int> v{10, 99, 30, 99};
    // Limit at index 3 (so indices 0..2 are considered)
    LimitSentinel end3{v.begin() + 3};
    int calls = 0;
    auto it = find_sentinel(v.begin(), end3, 99, CountingCmp<>{calls});
    ASSERT_NE(it, v.begin() + 3);
    EXPECT_EQ(std::distance(v.begin(), it), 1);
    EXPECT_EQ(*it, 99);
    EXPECT_EQ(calls, 2); // checked 10, then 99 (match)
}

TEST(FindSentinelTest_943, WorksWithForwardIterators_943) {
    std::forward_list<int> fl = {4, 5, 6};
    auto start = fl.begin();
    auto end   = fl.end(); // same type sentinel here, but forward-only category
    auto it = find_sentinel(start, end, 5, std::equal_to<>{});
    ASSERT_NE(it, end);
    EXPECT_EQ(*it, 5);
}
