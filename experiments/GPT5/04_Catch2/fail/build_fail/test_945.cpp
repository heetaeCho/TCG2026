// File: tests/sentinel_distance_945_tests.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <utility>
#include <cstddef>

// Include the amalgamated header providing Catch::Detail::sentinel_distance
#include "Catch2/extras/catch_amalgamated.hpp"

namespace {

using Catch::Detail::sentinel_distance;

// --- Utilities for compile-time detectability checks (no reimplementation of logic) ---
template <typename, typename, typename = void>
struct is_sentinel_distance_invocable : std::false_type {};

template <typename Iter, typename Sent>
struct is_sentinel_distance_invocable<
    Iter, Sent,
    std::void_t<decltype(sentinel_distance(std::declval<Iter>(), std::declval<Sent>()))>
> : std::true_type {};

template <typename Iter, typename Sent>
constexpr bool is_sentinel_distance_invocable_v = is_sentinel_distance_invocable<Iter, Sent>::value;

// --- Lightweight helper iterator & sentinel types for testing interoperability ---

// 1) A simple counting iterator/sentinel pair
struct LimitSentinel;

struct CountingIter {
    int value;

    CountingIter& operator++() {
        ++value;                // Only observable action needed for the public interface use
        return *this;
    }
    CountingIter operator++(int) = delete; // Not required by the function under test
    // Note: operator* not required; sentinel_distance never dereferences
};

struct LimitSentinel {
    int stop;
};

inline bool operator!=(const CountingIter& it, const LimitSentinel& s) {
    return it.value != s.stop;
}

// 2) Pointer + custom sentinel wrapper (to verify it works with "iterator != different-type sentinel")
template <typename T>
struct PtrSentinel {
    const T* end;
};

template <typename T>
inline bool operator!=(const T* it, const PtrSentinel<T>& s) {
    return it != s.end;
}

} // namespace

// -----------------------------------------------------------------------------
// TESTS
// -----------------------------------------------------------------------------

// Normal operation: counts number of increments until iterator equals sentinel.
TEST(SentinelDistanceTest_945, CountsUntilSentinel_945) {
    CountingIter it{0};
    LimitSentinel s{5};

    std::ptrdiff_t dist = sentinel_distance(it, s);

    EXPECT_EQ(dist, 5);
}

// Boundary condition: zero-distance when iterator is already at sentinel.
TEST(SentinelDistanceTest_945, ZeroWhenAlreadyAtSentinel_945) {
    CountingIter it{7};
    LimitSentinel s{7};

    std::ptrdiff_t dist = sentinel_distance(it, s);

    EXPECT_EQ(dist, 0);
}

// Larger distance (still lightweight): ensures loop progresses correctly.
TEST(SentinelDistanceTest_945, LargerDistanceProgressesCorrectly_945) {
    CountingIter it{10};
    LimitSentinel s{1010}; // Distance = 1000

    std::ptrdiff_t dist = sentinel_distance(it, s);

    EXPECT_EQ(dist, 1000);
}

// Works with raw pointer as iterator and a different sentinel type that wraps the end pointer.
TEST(SentinelDistanceTest_945, PointerWithCustomSentinelType_945) {
    int data[] = {1, 2, 3, 4};
    const int* begin = &data[0];
    PtrSentinel<const int> end{ &data[0] + 4 };

    std::ptrdiff_t dist = sentinel_distance(begin, end);

    EXPECT_EQ(dist, 4);
}

// Compile-time constraint: the function should NOT be viable when ForwardIter and Sentinel are the same type.
TEST(SentinelDistanceTest_945, SFINAE_DisabledForSameTypes_945) {
    // When both template parameters are the same type (e.g., int* and int*),
    // the enable_if requires !std::is_same<ForwardIter, Sentinel>::value, so it should be non-invocable.
    static_assert(!is_sentinel_distance_invocable_v<int*, int*>,
                  "sentinel_distance should not be invocable when iterator and sentinel types are the same.");
    // Sanity check: with different types (pointer vs wrapper) it should be invocable.
    static_assert(is_sentinel_distance_invocable_v<const int*, PtrSentinel<const int>>,
                  "sentinel_distance should be invocable for iterator and different sentinel type when operators are available.");

    SUCCEED(); // Run-time part just to mark the test as passed.
}
