// extended_mult_test_332.cpp
#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test (path taken from the prompt)
#include "Catch2/src/catch2/internal/catch_random_integer_helpers.hpp"

using Catch::Detail::extendedMult;

namespace {

struct Case {
    std::uint64_t lhs;
    std::uint64_t rhs;
    std::uint64_t exp_high;
    std::uint64_t exp_low;
};

void ExpectHiLoEq(const Case& c) {
    auto r = extendedMult(c.lhs, c.rhs);
    SCOPED_TRACE(::testing::Message()
                 << "lhs=0x" << std::hex << c.lhs
                 << " rhs=0x" << std::hex << c.rhs);
    EXPECT_EQ(r.high, c.exp_high);
    EXPECT_EQ(r.low,  c.exp_low);
}

} // namespace

// --- Normal operation & simple identities ---

TEST(ExtendedMultTest_332, ZeroTimesZero_ReturnsZero_332) {
    Case c{0x0ULL, 0x0ULL, 0x0ULL, 0x0ULL};
    ExpectHiLoEq(c);
}

TEST(ExtendedMultTest_332, OneTimesMax_ReturnsLowMaxHighZero_332) {
    Case c{0x1ULL, 0xFFFFFFFFFFFFFFFFULL, 0x0ULL, 0xFFFFFFFFFFFFFFFFULL};
    ExpectHiLoEq(c);
}

TEST(ExtendedMultTest_332, LowPartEqualsWrappedProduct_332) {
    // Verify the observable property: low == (lhs * rhs) modulo 2^64
    const Case cases[] = {
        {0x0ULL, 0x0ULL, 0, 0},
        {0x1ULL, 0xFFFFFFFFFFFFFFFFULL, 0, 0xFFFFFFFFFFFFFFFFULL},
        {0xFFFFFFFFULL, 0xFFFFFFFFULL, 0, 0xFFFFFFFE00000001ULL},
        {0x0123456789ABCDEFULL, 0xFEDCBA9876543210ULL, 0x0121FA00AD77D742ULL, 0x2236D88FE5618CF0ULL},
        {0xDEADBEEFDEADBEEFULL, 0x1234567890ABCDEFULL, 0x0FD5BDEEE3CEB48CULL, 0xD3B89ABEFFBFA421ULL},
    };
    for (const auto& c : cases) {
        auto r = extendedMult(c.lhs, c.rhs);
        const std::uint64_t wrapped = static_cast<std::uint64_t>(c.lhs * c.rhs);
        SCOPED_TRACE(::testing::Message()
                     << "lhs=0x" << std::hex << c.lhs
                     << " rhs=0x" << std::hex << c.rhs);
        EXPECT_EQ(r.low, wrapped);
    }
}

// --- Boundary conditions ---

TEST(ExtendedMultTest_332, MaxTimesMax_CarriesCorrectly_332) {
    // (2^64-1)*(2^64-1) = high: 0xFFFFFFFFFFFFFFFE, low: 0x0000000000000001
    Case c{0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL,
           0xFFFFFFFFFFFFFFFEULL, 0x0000000000000001ULL};
    ExpectHiLoEq(c);
}

TEST(ExtendedMultTest_332, Pow32TimesPow32_Equals2Pow64_332) {
    // (2^32) * (2^32) = 2^64 -> high=1, low=0
    Case c{0x0000000100000000ULL, 0x0000000100000000ULL, 0x0000000000000001ULL, 0x0000000000000000ULL};
    ExpectHiLoEq(c);
}

TEST(ExtendedMultTest_332, HighBitTimesTwo_CrossesWordBoundary_332) {
    // (2^63) * 2 = 2^64 -> high=1, low=0
    Case c{0x8000000000000000ULL, 0x0000000000000002ULL, 0x0000000000000001ULL, 0x0000000000000000ULL};
    ExpectHiLoEq(c);
}

TEST(ExtendedMultTest_332, LowWordSquares_NoHighCarry_332) {
    // (2^32-1)^2 -> high=0, low=0xFFFFFFFE00000001
    Case c{0x00000000FFFFFFFFULL, 0x00000000FFFFFFFFULL,
           0x0000000000000000ULL, 0xFFFFFFFE00000001ULL};
    ExpectHiLoEq(c);
}

// --- Additional known-good vectors (deterministic, precomputed) ---

TEST(ExtendedMultTest_332, KnownVector_0123456789ABCDEF_x_FEDCBA9876543210_332) {
    Case c{0x0123456789ABCDEFULL, 0xFEDCBA9876543210ULL,
           0x0121FA00AD77D742ULL, 0x2236D88FE5618CF0ULL};
    ExpectHiLoEq(c);
}

TEST(ExtendedMultTest_332, KnownVector_DA_BEEF_x_1234567890ABCDEF_332) {
    Case c{0xDEADBEEFDEADBEEFULL, 0x1234567890ABCDEFULL,
           0x0FD5BDEEE3CEB48CULL, 0xD3B89ABEFFBFA421ULL};
    ExpectHiLoEq(c);
}

// --- Observable algebraic property (commutativity) ---

TEST(ExtendedMultTest_332, Commutativity_HighAndLowMatchWhenSwapped_332) {
    const std::uint64_t a = 0x0123456789ABCDEFULL;
    const std::uint64_t b = 0xFEDCBA9876543210ULL;

    auto r1 = extendedMult(a, b);
    auto r2 = extendedMult(b, a);

    EXPECT_EQ(r1.high, r2.high);
    EXPECT_EQ(r1.low,  r2.low);
}
