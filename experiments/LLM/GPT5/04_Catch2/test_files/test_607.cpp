// File: tests/convert_to_bits_tests_607.cpp
#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <limits>

// The SUT declaration (as seen from the provided partial code)
namespace Catch { namespace Detail {
    uint64_t convertToBits(double d);
}}

// Helper: build a double from raw IEEE-754 bits without invoking UB.
static double makeDoubleFromBits(uint64_t bits) {
    double d;
    std::memcpy(&d, &bits, sizeof(d));
    return d;
}

class ConvertToBitsTest_607 : public ::testing::Test {};

// Normal operation: +0.0 maps to all-zero bits.
TEST_F(ConvertToBitsTest_607, PositiveZeroYieldsAllZeroBits_607) {
    const double plus_zero = 0.0;
    const uint64_t bits = Catch::Detail::convertToBits(plus_zero);
    EXPECT_EQ(bits, 0x0000000000000000ULL);
}

// Boundary: -0.0 has sign bit set and other bits zero.
TEST_F(ConvertToBitsTest_607, NegativeZeroHasOnlySignBit_607) {
    const double minus_zero = -0.0;
    const uint64_t bits = Catch::Detail::convertToBits(minus_zero);
    EXPECT_EQ(bits, 0x8000000000000000ULL);
}

// Normal operation: +/-1.0 known IEEE-754 encodings.
TEST_F(ConvertToBitsTest_607, OneAndMinusOneHaveExpectedEncodings_607) {
    const uint64_t one_bits = Catch::Detail::convertToBits(1.0);
    const uint64_t neg_one_bits = Catch::Detail::convertToBits(-1.0);

    EXPECT_EQ(one_bits,    0x3FF0000000000000ULL);
    EXPECT_EQ(neg_one_bits,0xBFF0000000000000ULL);
    EXPECT_NE(one_bits, neg_one_bits);
}

// Boundary: infinities have canonical encodings.
TEST_F(ConvertToBitsTest_607, InfinitiesHaveCanonicalEncodings_607) {
    const double pos_inf = std::numeric_limits<double>::infinity();
    const double neg_inf = -std::numeric_limits<double>::infinity();

    const uint64_t pos_bits = Catch::Detail::convertToBits(pos_inf);
    const uint64_t neg_bits = Catch::Detail::convertToBits(neg_inf);

    EXPECT_EQ(pos_bits, 0x7FF0000000000000ULL);
    EXPECT_EQ(neg_bits, 0xFFF0000000000000ULL);
}

// Exceptional/edge: NaN payloads can vary by platform, so construct a specific NaN by bits
// and verify the function returns the exact same bit pattern (round-trip check).
TEST_F(ConvertToBitsTest_607, NaNBitPatternIsPreserved_607) {
    // Quiet NaN with a small payload
    const uint64_t qnan_bits = 0x7FF8000000000001ULL;
    const double qnan = makeDoubleFromBits(qnan_bits);

    const uint64_t observed = Catch::Detail::convertToBits(qnan);
    EXPECT_EQ(observed, qnan_bits);
}

// Additional normal case: an arbitrary finite value round-trips to the expected bits.
TEST_F(ConvertToBitsTest_607, ArbitraryFiniteValueMatchesExpectedBits_607) {
    // Precomputed from IEEE-754 representation of 123.456
    // 123.456 double = 0x405EDD2F1A9FBE77
    const double value = 123.456;
    const uint64_t expected_bits = 0x405EDD2F1A9FBE77ULL;

    const uint64_t observed_bits = Catch::Detail::convertToBits(value);
    EXPECT_EQ(observed_bits, expected_bits);
}
