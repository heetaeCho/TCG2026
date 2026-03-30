// File: extended_mult_portable_test_331.cpp
#include <gtest/gtest.h>
#include <cstdint>

// Prefer the canonical include if available in your tree:
#include <catch2/internal/catch_random_integer_helpers.hpp>
// If your include layout differs, adjust the include path accordingly.

namespace {

#if defined(__SIZEOF_INT128__)
static inline std::pair<std::uint64_t, std::uint64_t>
Mul128Oracle(std::uint64_t a, std::uint64_t b) {
    __uint128_t p = static_cast<__uint128_t>(a) * static_cast<__uint128_t>(b);
    std::uint64_t lo = static_cast<std::uint64_t>(p);
    std::uint64_t hi = static_cast<std::uint64_t>(p >> 64);
    return {hi, lo};
}
#elif defined(_MSC_VER) && defined(_M_X64)
#include <intrin.h>
#pragma intrinsic(_umul128)
static inline std::pair<std::uint64_t, std::uint64_t>
Mul128Oracle(std::uint64_t a, std::uint64_t b) {
    unsigned __int64 hi;
    unsigned __int64 lo = _umul128(a, b, &hi);
    return {static_cast<std::uint64_t>(hi), static_cast<std::uint64_t>(lo)};
}
#endif

class ExtendedMultPortableTest_331 : public ::testing::Test {};

} // namespace

// --- Tests ---

TEST_F(ExtendedMultPortableTest_331, ZeroTimesZero_ReturnsZero_331) {
    auto [hi, lo] = Catch::Detail::extendedMultPortable(0u, 0u);
    EXPECT_EQ(hi, 0u);
    EXPECT_EQ(lo, 0u);
}

TEST_F(ExtendedMultPortableTest_331, ZeroTimesX_ReturnsZero_331) {
    const std::uint64_t xs[] = {
        1u, 0xFFFFFFFFu, 0x1'0000'0000ULL, 0xDEADBEEF01234567ULL,
        0xFFFFFFFFFFFFFFFFULL
    };

    for (auto x : xs) {
        auto [hi1, lo1] = Catch::Detail::extendedMultPortable(0u, x);
        auto [hi2, lo2] = Catch::Detail::extendedMultPortable(x, 0u);
        EXPECT_EQ(hi1, 0u);
        EXPECT_EQ(lo1, 0u);
        EXPECT_EQ(hi2, 0u);
        EXPECT_EQ(lo2, 0u);
    }
}

TEST_F(ExtendedMultPortableTest_331, OneTimesX_ReturnsXInLow_331) {
    const std::uint64_t xs[] = {
        0u, 1u, 0x7FFF'FFFF'FFFF'FFFFULL, 0x8000'0000'0000'0000ULL,
        0xFFFF'FFFF'FFFF'FFFFULL
    };

    for (auto x : xs) {
        auto [hi1, lo1] = Catch::Detail::extendedMultPortable(1u, x);
        auto [hi2, lo2] = Catch::Detail::extendedMultPortable(x, 1u);
        EXPECT_EQ(hi1, 0u);
        EXPECT_EQ(lo1, x);
        EXPECT_EQ(hi2, 0u);
        EXPECT_EQ(lo2, x);
    }
}

TEST_F(ExtendedMultPortableTest_331, Cross64Boundary_2pow32x2pow32_331) {
    constexpr std::uint64_t a = 0x1'0000'0000ULL; // 2^32
    constexpr std::uint64_t b = 0x1'0000'0000ULL; // 2^32
    auto [hi, lo] = Catch::Detail::extendedMultPortable(a, b);
    // (2^32 * 2^32) = 2^64 -> hi = 1, lo = 0
    EXPECT_EQ(hi, 1u);
    EXPECT_EQ(lo, 0u);
}

TEST_F(ExtendedMultPortableTest_331, LowWordIsWrappingProduct_ModuloProperty_331) {
    // For unsigned multiply, the low word must equal (a*b) modulo 2^64.
    const std::pair<std::uint64_t, std::uint64_t> cases[] = {
        {0xFFFF'FFFF'FFFF'FFFFULL, 0xFFFF'FFFF'FFFF'FFFFULL},
        {0xDEAD'BEEF'0123'4567ULL, 0xFEED'FACE'89AB'CDEFULL},
        {0x8000'0000'0000'0000ULL, 3ULL},
        {0x0000'0000'FFFF'FFFFULL, 0x0000'0001'0000'0001ULL},
        {0x1'0000'0000ULL, 0xFFFF'FFFF'FFFF'FFFFULL}
    };
    for (auto [a, b] : cases) {
        auto [hi, lo] = Catch::Detail::extendedMultPortable(a, b);
        (void)hi; // not used in this property
        EXPECT_EQ(lo, static_cast<std::uint64_t>(a * b))
            << std::hex << "a=" << a << " b=" << b;
    }
}

TEST_F(ExtendedMultPortableTest_331, Commutativity_HighAndLowMatchWhenSwapped_331) {
    const std::pair<std::uint64_t, std::uint64_t> cases[] = {
        {0u, 0u},
        {1u, 0xFEDC'BA98'7654'3210ULL},
        {0x1234'5678'9ABC'DEF0ULL, 0x0F0F'F0F0'AAAA'5555ULL},
        {0xFFFF'FFFF'0000'0000ULL, 0x0000'0000'FFFF'FFFFULL},
        {0x8000'0000'0000'0000ULL, 0x8000'0000'0000'0000ULL}
    };
    for (auto [a, b] : cases) {
        auto [hi1, lo1] = Catch::Detail::extendedMultPortable(a, b);
        auto [hi2, lo2] = Catch::Detail::extendedMultPortable(b, a);
        EXPECT_EQ(hi1, hi2) << std::hex << "a=" << a << " b=" << b;
        EXPECT_EQ(lo1, lo2) << std::hex << "a=" << a << " b=" << b;
    }
}

#if defined(__SIZEOF_INT128__) || (defined(_MSC_VER) && defined(_M_X64))
TEST_F(ExtendedMultPortableTest_331, MatchesTrusted128BitOracle_MixedCases_331) {
    const std::pair<std::uint64_t, std::uint64_t> cases[] = {
        {0xDEAD'BEEF'0123'4567ULL, 0xFEED'FACE'89AB'CDEFULL},
        {0x0000'0001'FFFF'FFFFULL, 0x0000'0001'FFFF'FFFFULL}, // fits into 64?
        {0x8000'0000'0000'0000ULL, 3ULL},
        {0xFFFF'FFFF'FFFF'FFFFULL, 0xFFFF'FFFF'FFFF'FFFFULL},
        {0x1'0000'0000ULL, 0xFFFF'FFFF'0000'0001ULL}
    };
    for (auto [a, b] : cases) {
        const auto [exp_hi, exp_lo] = Mul128Oracle(a, b);
        auto [act_hi, act_lo] = Catch::Detail::extendedMultPortable(a, b);
        EXPECT_EQ(act_lo, exp_lo) << std::hex << "a=" << a << " b=" << b;
        EXPECT_EQ(act_hi, exp_hi) << std::hex << "a=" << a << " b=" << b;
    }
}
#endif
