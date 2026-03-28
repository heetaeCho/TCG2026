// File: array_cat_tests_150.cpp
#include <gtest/gtest.h>
#include <array>
#include <type_traits>
#include <tuple>

// Use the header path that exposes the function under test.
// Adjust include path as needed for your project layout.
#include "catch2/matchers/catch_matchers_templated.hpp"

using Catch::Matchers::Detail::array_cat;

namespace {

// Helpers to get distinct, stable addresses as void const*
template <typename T>
static void const* VP(T* p) {
    return static_cast<void const*>(p);
}

} // namespace

// --- Type/size properties (interface-level, compile-time) ---

// Verifies that the returned type size is N+1 (for multiple N).
TEST(ArrayCatTest_150, ReturnArrayHasSizeNPlusOne_150) {
    // N = 0
    {
        using Ret0 = decltype(array_cat(nullptr, std::array<void const*, 0>{}));
        static_assert(std::tuple_size<Ret0>::value == 1, "Size must be 1 when N=0");
    }
    // N = 1
    {
        using Ret1 = decltype(array_cat(nullptr, std::array<void const*, 1>{nullptr}));
        static_assert(std::tuple_size<Ret1>::value == 2, "Size must be 2 when N=1");
    }
    // N = 3
    {
        using Ret3 = decltype(array_cat(nullptr, std::array<void const*, 3>{nullptr, nullptr, nullptr}));
        static_assert(std::tuple_size<Ret3>::value == 4, "Size must be 4 when N=3");
    }
    SUCCEED(); // Test is compile-time; ensures a runtime pass entry
}

// Verifies the element type is void const* (from the interface).
TEST(ArrayCatTest_150, ReturnElementTypeIsVoidConstPtr_150) {
    using Ret = decltype(array_cat(nullptr, std::array<void const*, 2>{nullptr, nullptr}));
    using Elem = typename Ret::value_type;
    static_assert(std::is_same<Elem, void const*>::value, "Element type must be void const*");
    SUCCEED();
}

// --- Runtime behavior tests (observable outputs only) ---

// Normal operation: prepends lhs and preserves rhs order.
TEST(ArrayCatTest_150, PrependsLhsAndPreservesOrder_150) {
    int a = 1, b = 2, c = 3, d = 4;

    std::array<void const*, 3> rhs{ VP(&b), VP(&c), VP(&d) };
    auto out = array_cat(VP(&a), std::move(rhs));

    ASSERT_EQ(out.size(), 4u);
    EXPECT_EQ(out[0], VP(&a));
    EXPECT_EQ(out[1], VP(&b));
    EXPECT_EQ(out[2], VP(&c));
    EXPECT_EQ(out[3], VP(&d));
}

// Boundary condition: N == 0 (empty rhs) results in single-element array with lhs.
TEST(ArrayCatTest_150, HandlesEmptyRhs_NEqualsZero_150) {
    double lhs = 42.0;

    std::array<void const*, 0> rhs{};
    auto out = array_cat(VP(&lhs), std::move(rhs));

    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], VP(&lhs));
}

// Null handling: accepts nullptr as lhs and/or inside rhs.
TEST(ArrayCatTest_150, AcceptsNullPointers_150) {
    long x = 7;

    std::array<void const*, 2> rhs{ nullptr, VP(&x) };
    auto out = array_cat(nullptr, std::move(rhs));

    ASSERT_EQ(out.size(), 3u);
    EXPECT_EQ(out[0], nullptr);     // lhs nullptr is kept
    EXPECT_EQ(out[1], nullptr);     // rhs[0] nullptr preserved in order
    EXPECT_EQ(out[2], VP(&x));      // rhs[1]
}

// Order verification with distinct addresses (no duplication or reordering).
TEST(ArrayCatTest_150, StrictOrderingIsMaintained_150) {
    char a=0, b=0, c=0;

    std::array<void const*, 2> rhs{ VP(&b), VP(&c) };
    auto out = array_cat(VP(&a), std::move(rhs));

    // Ensure no unintended aliasing or swapping.
    EXPECT_NE(out[0], out[1]);
    EXPECT_NE(out[1], out[2]);
    EXPECT_NE(out[0], out[2]);

    EXPECT_EQ(out[0], VP(&a));
    EXPECT_EQ(out[1], VP(&b));
    EXPECT_EQ(out[2], VP(&c));
}

// Larger N sanity: works for a bigger rhs and keeps exact sequence.
TEST(ArrayCatTest_150, WorksForLargerArrays_150) {
    int p0=0, p1=1, p2=2, p3=3, p4=4, p5=5;

    std::array<void const*, 5> rhs{ VP(&p1), VP(&p2), VP(&p3), VP(&p4), VP(&p5) };
    auto out = array_cat(VP(&p0), std::move(rhs));

    ASSERT_EQ(out.size(), 6u);
    const void* expected[6] = { VP(&p0), VP(&p1), VP(&p2), VP(&p3), VP(&p4), VP(&p5) };
    for (size_t i = 0; i < 6; ++i) {
        EXPECT_EQ(out[i], expected[i]) << "Mismatch at index " << i;
    }
}
