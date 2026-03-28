#include <gtest/gtest.h>
#include <type_traits>

// Minimal stubs for macros if not defined
#ifndef JKJ_FORCEINLINE
#define JKJ_FORCEINLINE
#endif
#ifndef JKJ_SAFEBUFFERS
#define JKJ_SAFEBUFFERS
#endif

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox;

// Mock SignedSignificandBits that returns even
struct EvenSignificandBits {
    constexpr bool has_even_significand_bits() const noexcept { return true; }
};

// Mock SignedSignificandBits that returns odd
struct OddSignificandBits {
    constexpr bool has_even_significand_bits() const noexcept { return false; }
};

// Tag types to identify which boundary was selected
struct ClosedResult {};
struct OpenResult {};

// A functor that returns different types/values based on the boundary tag
struct BoundaryDispatcher {
    constexpr int operator()(detail::nearest_always_closed_t) const noexcept {
        return 1;
    }
    constexpr int operator()(detail::nearest_always_open_t) const noexcept {
        return 2;
    }
};

// A functor that also takes extra args
struct BoundaryDispatcherWithArgs {
    constexpr int operator()(detail::nearest_always_closed_t, int a, int b) const noexcept {
        return a + b;
    }
    constexpr int operator()(detail::nearest_always_open_t, int a, int b) const noexcept {
        return a * b;
    }
};

// A functor with no extra args returning a string-like indicator
struct BoundaryDispatcherString {
    constexpr const char* operator()(detail::nearest_always_closed_t) const noexcept {
        return "closed";
    }
    constexpr const char* operator()(detail::nearest_always_open_t) const noexcept {
        return "open";
    }
};

using NearestToEven = policy::decimal_to_binary_rounding::nearest_to_even_static_boundary_t;

class NearestToEvenStaticBoundaryTest_377 : public ::testing::Test {};

// Test that even significand bits delegate to closed boundary
TEST_F(NearestToEvenStaticBoundaryTest_377, EvenSignificandDelegatesToClosed_377) {
    EvenSignificandBits s;
    int result = NearestToEven::delegate(s, BoundaryDispatcher{});
    EXPECT_EQ(result, 1);
}

// Test that odd significand bits delegate to open boundary
TEST_F(NearestToEvenStaticBoundaryTest_377, OddSignificandDelegatesToOpen_377) {
    OddSignificandBits s;
    int result = NearestToEven::delegate(s, BoundaryDispatcher{});
    EXPECT_EQ(result, 2);
}

// Test with additional arguments - even significand (closed: a+b)
TEST_F(NearestToEvenStaticBoundaryTest_377, EvenSignificandWithArgs_377) {
    EvenSignificandBits s;
    int result = NearestToEven::delegate(s, BoundaryDispatcherWithArgs{}, 3, 4);
    EXPECT_EQ(result, 7); // 3 + 4
}

// Test with additional arguments - odd significand (open: a*b)
TEST_F(NearestToEvenStaticBoundaryTest_377, OddSignificandWithArgs_377) {
    OddSignificandBits s;
    int result = NearestToEven::delegate(s, BoundaryDispatcherWithArgs{}, 3, 4);
    EXPECT_EQ(result, 12); // 3 * 4
}

// Test with string return - even significand
TEST_F(NearestToEvenStaticBoundaryTest_377, EvenSignificandReturnsClosedString_377) {
    EvenSignificandBits s;
    const char* result = NearestToEven::delegate(s, BoundaryDispatcherString{});
    EXPECT_STREQ(result, "closed");
}

// Test with string return - odd significand
TEST_F(NearestToEvenStaticBoundaryTest_377, OddSignificandReturnsOpenString_377) {
    OddSignificandBits s;
    const char* result = NearestToEven::delegate(s, BoundaryDispatcherString{});
    EXPECT_STREQ(result, "open");
}

// Boundary: zero args beyond the boundary tag, even
TEST_F(NearestToEvenStaticBoundaryTest_377, EvenWithZeroExtraArgs_377) {
    EvenSignificandBits s;
    int result = NearestToEven::delegate(s, BoundaryDispatcher{});
    EXPECT_EQ(result, 1);
}

// Boundary: zero args beyond the boundary tag, odd
TEST_F(NearestToEvenStaticBoundaryTest_377, OddWithZeroExtraArgs_377) {
    OddSignificandBits s;
    int result = NearestToEven::delegate(s, BoundaryDispatcher{});
    EXPECT_EQ(result, 2);
}

// Test with boundary values in args - even with zeros
TEST_F(NearestToEvenStaticBoundaryTest_377, EvenSignificandWithZeroArgs_377) {
    EvenSignificandBits s;
    int result = NearestToEven::delegate(s, BoundaryDispatcherWithArgs{}, 0, 0);
    EXPECT_EQ(result, 0); // 0 + 0
}

// Test with boundary values in args - odd with zeros
TEST_F(NearestToEvenStaticBoundaryTest_377, OddSignificandWithZeroArgs_377) {
    OddSignificandBits s;
    int result = NearestToEven::delegate(s, BoundaryDispatcherWithArgs{}, 0, 0);
    EXPECT_EQ(result, 0); // 0 * 0
}

// Test with negative arguments - even
TEST_F(NearestToEvenStaticBoundaryTest_377, EvenSignificandWithNegativeArgs_377) {
    EvenSignificandBits s;
    int result = NearestToEven::delegate(s, BoundaryDispatcherWithArgs{}, -3, 5);
    EXPECT_EQ(result, 2); // -3 + 5
}

// Test with negative arguments - odd
TEST_F(NearestToEvenStaticBoundaryTest_377, OddSignificandWithNegativeArgs_377) {
    OddSignificandBits s;
    int result = NearestToEven::delegate(s, BoundaryDispatcherWithArgs{}, -3, 5);
    EXPECT_EQ(result, -15); // -3 * 5
}
