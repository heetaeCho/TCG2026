// File: convert_to_bits_tests_606.cpp
#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <cmath>

namespace Catch { namespace Detail {
    // Forward declaration of the function under test (treating implementation as a black box).
    uint32_t convertToBits(float f);
}}

// A small helper to make intent clear in expectations; it does not re-implement any logic.
static ::testing::AssertionResult BitsEq(uint32_t actual, uint32_t expected) {
    if (actual == expected) return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure()
        << "Bits mismatch. Expected 0x" << std::hex << expected
        << " but got 0x" << actual;
}

using CatchFloatingPointHelpersTest_606 = ::testing::Test;

TEST_F(CatchFloatingPointHelpersTest_606, Convert_PositiveZero_606) {
    uint32_t bits = Catch::Detail::convertToBits(0.0f);
    EXPECT_TRUE(BitsEq(bits, 0x00000000u));
}

TEST_F(CatchFloatingPointHelpersTest_606, Convert_NegativeZero_606) {
    // Distinguish -0.0f from +0.0f via sign bit.
    float negZero = -0.0f;
    ASSERT_TRUE(std::signbit(negZero)); // observable via <cmath>
    uint32_t bits = Catch::Detail::convertToBits(negZero);
    EXPECT_TRUE(BitsEq(bits, 0x80000000u));
}

TEST_F(CatchFloatingPointHelpersTest_606, Convert_PositiveOne_606) {
    uint32_t bits = Catch::Detail::convertToBits(1.0f);
    EXPECT_TRUE(BitsEq(bits, 0x3f800000u));
}

TEST_F(CatchFloatingPointHelpersTest_606, Convert_NegativeOne_606) {
    uint32_t bits = Catch::Detail::convertToBits(-1.0f);
    EXPECT_TRUE(BitsEq(bits, 0xbf800000u));
}

TEST_F(CatchFloatingPointHelpersTest_606, Convert_PositiveInfinity_606) {
    float inf = std::numeric_limits<float>::infinity();
    uint32_t bits = Catch::Detail::convertToBits(inf);
    EXPECT_TRUE(BitsEq(bits, 0x7f800000u));
}

TEST_F(CatchFloatingPointHelpersTest_606, Convert_NegativeInfinity_606) {
    float ninf = -std::numeric_limits<float>::infinity();
    uint32_t bits = Catch::Detail::convertToBits(ninf);
    EXPECT_TRUE(BitsEq(bits, 0xff800000u));
}

TEST_F(CatchFloatingPointHelpersTest_606, Convert_DenormMin_606) {
    // Smallest positive subnormal value.
    float denorm_min = std::numeric_limits<float>::denorm_min();
    // Sanity: ensure it is subnormal & > 0
    ASSERT_GT(denorm_min, 0.0f);
    ASSERT_FALSE(std::fpclassify(denorm_min) == FP_NORMAL);

    uint32_t bits = Catch::Detail::convertToBits(denorm_min);
    EXPECT_TRUE(BitsEq(bits, 0x00000001u));
}

TEST_F(CatchFloatingPointHelpersTest_606, Convert_QuietNaN_HasAllOnesExponentAndNonzeroMantissa_606) {
    float qnan = std::numeric_limits<float>::quiet_NaN();
    ASSERT_TRUE(std::isnan(qnan)); // observable behavior via <cmath>

    uint32_t bits = Catch::Detail::convertToBits(qnan);

    // For IEEE-754 single-precision: exponent all ones (0xFF) and mantissa non-zero.
    // We do not assume a specific NaN payload, only these observable properties.
    const uint32_t signMask = 0x80000000u;
    const uint32_t expMask  = 0x7f800000u;
    const uint32_t manMask  = 0x007fffffu;

    EXPECT_EQ((bits & expMask), 0x7f800000u);      // exponent == 0xFF
    EXPECT_NE((bits & manMask), 0u);               // mantissa != 0
    (void)signMask; // sign may be either 0 or 1 for NaN; we don't assert it.
}
