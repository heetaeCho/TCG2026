#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <limits>

// Declaration of the function under test
namespace Catch {
namespace Detail {
    uint64_t convertToBits(double d);
}
}

class ConvertToBitsTest_607 : public ::testing::Test {
protected:
    // Helper to get expected bits via memcpy (same technique the implementation uses)
    uint64_t expectedBits(double d) {
        uint64_t bits;
        std::memcpy(&bits, &d, sizeof(d));
        return bits;
    }
};

// Test that converting 0.0 produces the expected bit pattern
TEST_F(ConvertToBitsTest_607, ZeroProducesExpectedBits_607) {
    double val = 0.0;
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
    EXPECT_EQ(result, 0ULL);
}

// Test that converting negative zero produces a different bit pattern than positive zero
TEST_F(ConvertToBitsTest_607, NegativeZeroProducesExpectedBits_607) {
    double val = -0.0;
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
    // Negative zero has the sign bit set
    EXPECT_NE(result, Catch::Detail::convertToBits(0.0));
    EXPECT_EQ(result, 0x8000000000000000ULL);
}

// Test that converting 1.0 gives the expected IEEE 754 representation
TEST_F(ConvertToBitsTest_607, OnePointZeroProducesExpectedBits_607) {
    double val = 1.0;
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
    // IEEE 754: 1.0 = 0x3FF0000000000000
    EXPECT_EQ(result, 0x3FF0000000000000ULL);
}

// Test that converting -1.0 gives the expected IEEE 754 representation
TEST_F(ConvertToBitsTest_607, NegativeOnePointZeroProducesExpectedBits_607) {
    double val = -1.0;
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
    // IEEE 754: -1.0 = 0xBFF0000000000000
    EXPECT_EQ(result, 0xBFF0000000000000ULL);
}

// Test that converting positive infinity produces expected bits
TEST_F(ConvertToBitsTest_607, PositiveInfinityProducesExpectedBits_607) {
    double val = std::numeric_limits<double>::infinity();
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
    EXPECT_EQ(result, 0x7FF0000000000000ULL);
}

// Test that converting negative infinity produces expected bits
TEST_F(ConvertToBitsTest_607, NegativeInfinityProducesExpectedBits_607) {
    double val = -std::numeric_limits<double>::infinity();
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
    EXPECT_EQ(result, 0xFFF0000000000000ULL);
}

// Test that converting NaN produces expected bits (NaN has specific bit patterns)
TEST_F(ConvertToBitsTest_607, NaNProducesExpectedBits_607) {
    double val = std::numeric_limits<double>::quiet_NaN();
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
    // NaN has exponent bits all set and non-zero mantissa
    uint64_t exponentMask = 0x7FF0000000000000ULL;
    uint64_t mantissaMask = 0x000FFFFFFFFFFFFFULL;
    EXPECT_EQ(result & exponentMask, exponentMask);
    EXPECT_NE(result & mantissaMask, 0ULL);
}

// Test that converting the smallest positive denormalized double
TEST_F(ConvertToBitsTest_607, SmallestDenormProducesExpectedBits_607) {
    double val = std::numeric_limits<double>::denorm_min();
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
    EXPECT_EQ(result, 1ULL);
}

// Test that converting the smallest positive normalized double
TEST_F(ConvertToBitsTest_607, SmallestNormalProducesExpectedBits_607) {
    double val = std::numeric_limits<double>::min();
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
    EXPECT_EQ(result, 0x0010000000000000ULL);
}

// Test that converting max double produces expected bits
TEST_F(ConvertToBitsTest_607, MaxDoubleProducesExpectedBits_607) {
    double val = std::numeric_limits<double>::max();
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
    EXPECT_EQ(result, 0x7FEFFFFFFFFFFFFFULL);
}

// Test that converting lowest (most negative) double produces expected bits
TEST_F(ConvertToBitsTest_607, LowestDoubleProducesExpectedBits_607) {
    double val = std::numeric_limits<double>::lowest();
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
    EXPECT_EQ(result, 0xFFEFFFFFFFFFFFFFULL);
}

// Test that two different double values produce different bit patterns
TEST_F(ConvertToBitsTest_607, DifferentValuesProduceDifferentBits_607) {
    uint64_t bits1 = Catch::Detail::convertToBits(1.0);
    uint64_t bits2 = Catch::Detail::convertToBits(2.0);
    EXPECT_NE(bits1, bits2);
}

// Test that the same value always produces the same bit pattern
TEST_F(ConvertToBitsTest_607, SameValueProducesSameBits_607) {
    double val = 3.14159265358979323846;
    uint64_t bits1 = Catch::Detail::convertToBits(val);
    uint64_t bits2 = Catch::Detail::convertToBits(val);
    EXPECT_EQ(bits1, bits2);
}

// Test epsilon value
TEST_F(ConvertToBitsTest_607, EpsilonProducesExpectedBits_607) {
    double val = std::numeric_limits<double>::epsilon();
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
}

// Test a typical floating point value
TEST_F(ConvertToBitsTest_607, PiProducesExpectedBits_607) {
    double val = 3.14159265358979323846;
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
}

// Test adjacent doubles differ by exactly 1 ULP in bit representation (for normal numbers)
TEST_F(ConvertToBitsTest_607, AdjacentDoublesOneBitApart_607) {
    double val = 1.0;
    double next = std::nextafter(val, std::numeric_limits<double>::infinity());
    uint64_t bits_val = Catch::Detail::convertToBits(val);
    uint64_t bits_next = Catch::Detail::convertToBits(next);
    EXPECT_EQ(bits_next - bits_val, 1ULL);
}

// Test signaling NaN
TEST_F(ConvertToBitsTest_607, SignalingNaNProducesExpectedBits_607) {
    double val = std::numeric_limits<double>::signaling_NaN();
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
    // Signaling NaN also has exponent bits all set and non-zero mantissa
    uint64_t exponentMask = 0x7FF0000000000000ULL;
    EXPECT_EQ(result & exponentMask, exponentMask);
}

// Test a very small negative number
TEST_F(ConvertToBitsTest_607, SmallNegativeNumberProducesExpectedBits_607) {
    double val = -std::numeric_limits<double>::denorm_min();
    uint64_t result = Catch::Detail::convertToBits(val);
    EXPECT_EQ(result, expectedBits(val));
    // Should have sign bit set
    EXPECT_NE(result & 0x8000000000000000ULL, 0ULL);
}
