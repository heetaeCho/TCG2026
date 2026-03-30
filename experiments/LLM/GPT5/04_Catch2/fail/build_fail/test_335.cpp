// File: transpose_to_natural_order_test_335.cpp

#include <gtest/gtest.h>
#include <cstdint>
#include <climits>
#include <limits>
#include <type_traits>

// Include the header under test
#include "Catch2/src/catch2/internal/catch_random_integer_helpers.hpp"

using Catch::Detail::transposeToNaturalOrder;

// ---- Detection idiom to check callability without instantiating the body ----
template <typename O, typename U, typename = void>
struct is_callable_transpose : std::false_type {};

template <typename O, typename U>
struct is_callable_transpose<
    O,
    U,
    std::void_t<decltype(transposeToNaturalOrder<O, U>(std::declval<U>()))>
> : std::true_type {};

// ---- Typed fixture over common signed/unsigned pairs of the same size ----
template <typename T>
struct Pair { using Original = typename T::Original; using Unsigned = typename T::Unsigned; };

template <typename O_, typename U_>
struct Types { using Original = O_; using Unsigned = U_; };

using UnderTestTypes = ::testing::Types<
    Types<int8_t,  uint8_t>,
    Types<int16_t, uint16_t>,
    Types<int32_t, uint32_t>,
    Types<int64_t, uint64_t>
>;

template <class T>
class TransposeToNaturalOrderTest_335 : public ::testing::Test {};
TYPED_TEST_SUITE(TransposeToNaturalOrderTest_335, UnderTestTypes);

// ---- Helpers ----
template <typename U>
constexpr U HighestBit() {
    return static_cast<U>(U(1) << (sizeof(U) * CHAR_BIT - 1));
}

// ========================= Test Cases =========================

TYPED_TEST(TransposeToNaturalOrderTest_335, ZeroInput_FlipsMSB_335) {
    using O = typename TypeParam::Original;
    using U = typename TypeParam::Unsigned;

    constexpr U hb = HighestBit<U>();
    const U out = transposeToNaturalOrder<O, U>(U{0});
    EXPECT_EQ(out, hb);
}

TYPED_TEST(TransposeToNaturalOrderTest_335, HighestBitInput_BecomesZero_335) {
    using O = typename TypeParam::Original;
    using U = typename TypeParam::Unsigned;

    constexpr U hb = HighestBit<U>();
    const U out = transposeToNaturalOrder<O, U>(hb);
    EXPECT_EQ(out, U{0});
}

TYPED_TEST(TransposeToNaturalOrderTest_335, MaxUnsignedInput_MSBIsToggled_335) {
    using O = typename TypeParam::Original;
    using U = typename TypeParam::Unsigned;

    constexpr U hb  = HighestBit<U>();
    constexpr U max = std::numeric_limits<U>::max();

    const U out = transposeToNaturalOrder<O, U>(max);
    EXPECT_EQ(out, static_cast<U>(max ^ hb));
}

TYPED_TEST(TransposeToNaturalOrderTest_335, RoundTrip_TwiceGivesOriginal_335) {
    using O = typename TypeParam::Original;
    using U = typename TypeParam::Unsigned;

    // Use the same sample value for all widths; fits in every U.
    const U sample = static_cast<U>(0x5Au);

    const U once  = transposeToNaturalOrder<O, U>(sample);
    const U twice = transposeToNaturalOrder<O, U>(once);
    EXPECT_EQ(twice, sample);
}

TEST(TransposeToNaturalOrder_Static_335, IsConstexpr_EvaluatesAtCompileTime_335) {
    // Pick concrete types to exercise constexpr.
    constexpr uint32_t hb = static_cast<uint32_t>(uint32_t{1} << (sizeof(uint32_t) * CHAR_BIT - 1));
    constexpr uint32_t r0 = transposeToNaturalOrder<int32_t, uint32_t>(0u);
    static_assert(r0 == hb, "Expected constexpr evaluation to flip the highest bit for zero input.");

    constexpr uint32_t r1 = transposeToNaturalOrder<int32_t, uint32_t>(hb);
    static_assert(r1 == 0u, "Expected constexpr evaluation to clear the highest bit for highest-bit input.");
    (void)r0; (void)r1; // silence unused warnings in some toolchains
}

TEST(TransposeToNaturalOrder_SFINAE_335, DisabledForUnsignedOriginalType_335) {
    // Enabled when OriginalType is signed …
    static_assert(is_callable_transpose<int32_t,  uint32_t>::value,  "Should be callable for signed OriginalType.");
    static_assert(is_callable_transpose<int16_t,  uint16_t>::value,  "Should be callable for signed OriginalType.");
    static_assert(is_callable_transpose<int8_t,   uint8_t>::value,   "Should be callable for signed OriginalType.");

    // … and not available when OriginalType is unsigned (due to enable_if constraint).
    static_assert(!is_callable_transpose<uint32_t, uint32_t>::value, "Should NOT be callable for unsigned OriginalType.");
    static_assert(!is_callable_transpose<uint16_t, uint16_t>::value, "Should NOT be callable for unsigned OriginalType.");
    static_assert(!is_callable_transpose<uint8_t,  uint8_t>::value,  "Should NOT be callable for unsigned OriginalType.");
}
