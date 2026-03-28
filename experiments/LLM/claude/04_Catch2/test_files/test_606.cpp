#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <limits>

// Declaration of the function under test
namespace Catch {
namespace Detail {
    uint32_t convertToBits(float f);
}
}

class ConvertToBitsTest_606 : public ::testing::Test {
protected:
    // Helper to get expected bits via memcpy (same technique, but we treat
    // the function as a black box and verify against the standard bit pattern)
    uint32_t expectedBits(float f) {
        uint32_t result;
        std::memcpy(&result, &f, sizeof(f));
        return result;
    }
};

// Test: Zero should convert to its known bit pattern (all zeros)
TEST_F(ConvertToBitsTest_606, PositiveZero_606) {
    float f = 0.0f;
    uint32_t result = Catch::Detail::convertToBits(f);
    EXPECT_EQ(result, 0u);
}

// Test: Negative zero has the sign bit set
TEST_F(ConvertToBitsTest_606, NegativeZero_606) {
    float f = -0.0f;
    uint32_t result = Catch::Detail::convertToBits(f);
    EXPECT_EQ(result, 0x80000000u);
}

// Test: 1.0f has a well-known IEEE 754 representation
TEST_F(ConvertToBitsTest_606, OnePointZero_606) {
    float f = 1.0f;
    uint32_t result = Catch::Detail::convertToBits(f);
    // IEEE 754: 1.0f = 0 01111111 00000000000000000000000 = 0x3F800000
    EXPECT_EQ(result, 0x3F800000u);
}

// Test: -1.0f has the sign bit set compared to 1.0f
TEST_F(ConvertToBitsTest_606, NegativeOnePointZero_606) {
    float f = -1.0f;
    uint32_t result = Catch::Detail::convertToBits(f);
    // IEEE 754: -1.0f = 0xBF800000
    EXPECT_EQ(result, 0xBF800000u);
}

// Test: 2.0f known bit pattern
TEST_F(ConvertToBitsTest_606, TwoPointZero_606) {
    float f = 2.0f;
    uint32_t result = Catch::Detail::convertToBits(f);
    // IEEE 754: 2.0f = 0x40000000
    EXPECT_EQ(result, 0x40000000u);
}

// Test: Positive infinity
TEST_F(ConvertToBitsTest_606, PositiveInfinity_606) {
    float f = std::numeric_limits<float>::infinity();
    uint32_t result = Catch::Detail::convertToBits(f);
    // IEEE 754: +inf = 0x7F800000
    EXPECT_EQ(result, 0x7F800000u);
}

// Test: Negative infinity
TEST_F(ConvertToBitsTest_606, NegativeInfinity_606) {
    float f = -std::numeric_limits<float>::infinity();
    uint32_t result = Catch::Detail::convertToBits(f);
    // IEEE 754: -inf = 0xFF800000
    EXPECT_EQ(result, 0xFF800000u);
}

// Test: NaN has specific bit pattern (exponent all 1s, mantissa non-zero)
TEST_F(ConvertToBitsTest_606, NaN_606) {
    float f = std::numeric_limits<float>::quiet_NaN();
    uint32_t result = Catch::Detail::convertToBits(f);
    // For NaN, exponent bits should all be 1 and mantissa should be non-zero
    uint32_t exponent = result & 0x7F800000u;
    uint32_t mantissa = result & 0x007FFFFFu;
    EXPECT_EQ(exponent, 0x7F800000u);
    EXPECT_NE(mantissa, 0u);
}

// Test: Smallest positive denormalized float
TEST_F(ConvertToBitsTest_606, SmallestDenorm_606) {
    float f = std::numeric_limits<float>::denorm_min();
    uint32_t result = Catch::Detail::convertToBits(f);
    // Smallest denorm = 0x00000001
    EXPECT_EQ(result, 0x00000001u);
}

// Test: Smallest positive normalized float
TEST_F(ConvertToBitsTest_606, SmallestNormalized_606) {
    float f = std::numeric_limits<float>::min();
    uint32_t result = Catch::Detail::convertToBits(f);
    // Smallest normalized = 0x00800000
    EXPECT_EQ(result, 0x00800000u);
}

// Test: Largest finite float
TEST_F(ConvertToBitsTest_606, LargestFinite_606) {
    float f = std::numeric_limits<float>::max();
    uint32_t result = Catch::Detail::convertToBits(f);
    // FLT_MAX = 0x7F7FFFFF
    EXPECT_EQ(result, 0x7F7FFFFFu);
}

// Test: Negative largest finite float
TEST_F(ConvertToBitsTest_606, NegativeLargestFinite_606) {
    float f = -std::numeric_limits<float>::max();
    uint32_t result = Catch::Detail::convertToBits(f);
    EXPECT_EQ(result, 0xFF7FFFFFu);
}

// Test: Machine epsilon
TEST_F(ConvertToBitsTest_606, Epsilon_606) {
    float f = std::numeric_limits<float>::epsilon();
    uint32_t result = Catch::Detail::convertToBits(f);
    EXPECT_EQ(result, expectedBits(f));
}

// Test: 0.5f
TEST_F(ConvertToBitsTest_606, ZeroPointFive_606) {
    float f = 0.5f;
    uint32_t result = Catch::Detail::convertToBits(f);
    // IEEE 754: 0.5f = 0x3F000000
    EXPECT_EQ(result, 0x3F000000u);
}

// Test: A small negative number
TEST_F(ConvertToBitsTest_606, SmallNegative_606) {
    float f = -0.5f;
    uint32_t result = Catch::Detail::convertToBits(f);
    // IEEE 754: -0.5f = 0xBF000000
    EXPECT_EQ(result, 0xBF000000u);
}

// Test: Verify round-trip consistency - converting bits back to float gives the same value
TEST_F(ConvertToBitsTest_606, RoundTripConsistency_606) {
    float original = 3.14159f;
    uint32_t bits = Catch::Detail::convertToBits(original);
    float recovered;
    std::memcpy(&recovered, &bits, sizeof(bits));
    EXPECT_EQ(original, recovered);
}

// Test: Different values produce different bit patterns
TEST_F(ConvertToBitsTest_606, DifferentValuesProduceDifferentBits_606) {
    uint32_t bits1 = Catch::Detail::convertToBits(1.0f);
    uint32_t bits2 = Catch::Detail::convertToBits(2.0f);
    EXPECT_NE(bits1, bits2);
}

// Test: Adjacent floats differ by exactly 1 ULP in bit representation
TEST_F(ConvertToBitsTest_606, AdjacentFloatsOneULP_606) {
    float f = 1.0f;
    float next = std::nextafter(f, 2.0f);
    uint32_t bits_f = Catch::Detail::convertToBits(f);
    uint32_t bits_next = Catch::Detail::convertToBits(next);
    EXPECT_EQ(bits_next - bits_f, 1u);
}

// Test: Negative small denorm
TEST_F(ConvertToBitsTest_606, NegativeSmallestDenorm_606) {
    float f = -std::numeric_limits<float>::denorm_min();
    uint32_t result = Catch::Detail::convertToBits(f);
    EXPECT_EQ(result, 0x80000001u);
}
