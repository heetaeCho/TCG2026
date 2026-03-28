#include <gtest/gtest.h>
#include <cstring>
#include <cmath>
#include <limits>

// Include the necessary headers from exiv2
#include "types.hpp"

using namespace Exiv2;

class GetFloatTest_1143 : public ::testing::Test {
protected:
    byte buf[4];
    
    void SetUp() override {
        std::memset(buf, 0, sizeof(buf));
    }
    
    // Helper to store a uint32_t in little-endian byte order
    void storeUint32LE(byte* buffer, uint32_t value) {
        buffer[0] = static_cast<byte>(value & 0xFF);
        buffer[1] = static_cast<byte>((value >> 8) & 0xFF);
        buffer[2] = static_cast<byte>((value >> 16) & 0xFF);
        buffer[3] = static_cast<byte>((value >> 24) & 0xFF);
    }
    
    // Helper to store a uint32_t in big-endian byte order
    void storeUint32BE(byte* buffer, uint32_t value) {
        buffer[0] = static_cast<byte>((value >> 24) & 0xFF);
        buffer[1] = static_cast<byte>((value >> 16) & 0xFF);
        buffer[2] = static_cast<byte>((value >> 8) & 0xFF);
        buffer[3] = static_cast<byte>(value & 0xFF);
    }
    
    // Helper to get the bit representation of a float
    uint32_t floatToUint32(float f) {
        uint32_t result;
        std::memcpy(&result, &f, sizeof(result));
        return result;
    }
};

// Test that zero is correctly read in little-endian
TEST_F(GetFloatTest_1143, ZeroLittleEndian_1143) {
    uint32_t bits = floatToUint32(0.0f);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Test that zero is correctly read in big-endian
TEST_F(GetFloatTest_1143, ZeroBigEndian_1143) {
    uint32_t bits = floatToUint32(0.0f);
    storeUint32BE(buf, bits);
    float result = getFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Test positive float value in little-endian
TEST_F(GetFloatTest_1143, PositiveFloatLittleEndian_1143) {
    float expected = 1.0f;
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test positive float value in big-endian
TEST_F(GetFloatTest_1143, PositiveFloatBigEndian_1143) {
    float expected = 1.0f;
    uint32_t bits = floatToUint32(expected);
    storeUint32BE(buf, bits);
    float result = getFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test negative float value in little-endian
TEST_F(GetFloatTest_1143, NegativeFloatLittleEndian_1143) {
    float expected = -1.0f;
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test negative float value in big-endian
TEST_F(GetFloatTest_1143, NegativeFloatBigEndian_1143) {
    float expected = -1.0f;
    uint32_t bits = floatToUint32(expected);
    storeUint32BE(buf, bits);
    float result = getFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test a specific known float: Pi approximation
TEST_F(GetFloatTest_1143, PiValueLittleEndian_1143) {
    float expected = 3.14159265f;
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test a specific known float: Pi approximation big-endian
TEST_F(GetFloatTest_1143, PiValueBigEndian_1143) {
    float expected = 3.14159265f;
    uint32_t bits = floatToUint32(expected);
    storeUint32BE(buf, bits);
    float result = getFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test a very small positive float (denormalized)
TEST_F(GetFloatTest_1143, SmallPositiveFloatLittleEndian_1143) {
    float expected = std::numeric_limits<float>::min();
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test maximum float value
TEST_F(GetFloatTest_1143, MaxFloatLittleEndian_1143) {
    float expected = std::numeric_limits<float>::max();
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test maximum float value big-endian
TEST_F(GetFloatTest_1143, MaxFloatBigEndian_1143) {
    float expected = std::numeric_limits<float>::max();
    uint32_t bits = floatToUint32(expected);
    storeUint32BE(buf, bits);
    float result = getFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test lowest (most negative) float value
TEST_F(GetFloatTest_1143, LowestFloatLittleEndian_1143) {
    float expected = std::numeric_limits<float>::lowest();
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test positive infinity
TEST_F(GetFloatTest_1143, PositiveInfinityLittleEndian_1143) {
    float expected = std::numeric_limits<float>::infinity();
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_GT(result, 0.0f);
}

// Test negative infinity
TEST_F(GetFloatTest_1143, NegativeInfinityLittleEndian_1143) {
    float expected = -std::numeric_limits<float>::infinity();
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_LT(result, 0.0f);
}

// Test NaN
TEST_F(GetFloatTest_1143, NaNLittleEndian_1143) {
    float expected = std::numeric_limits<float>::quiet_NaN();
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_TRUE(std::isnan(result));
}

// Test NaN big-endian
TEST_F(GetFloatTest_1143, NaNBigEndian_1143) {
    float expected = std::numeric_limits<float>::quiet_NaN();
    uint32_t bits = floatToUint32(expected);
    storeUint32BE(buf, bits);
    float result = getFloat(buf, bigEndian);
    EXPECT_TRUE(std::isnan(result));
}

// Test negative zero
TEST_F(GetFloatTest_1143, NegativeZeroLittleEndian_1143) {
    float expected = -0.0f;
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    // -0.0 == 0.0 is true, but we check the sign bit
    EXPECT_FLOAT_EQ(result, 0.0f);
    EXPECT_TRUE(std::signbit(result));
}

// Test negative zero big-endian
TEST_F(GetFloatTest_1143, NegativeZeroBigEndian_1143) {
    float expected = -0.0f;
    uint32_t bits = floatToUint32(expected);
    storeUint32BE(buf, bits);
    float result = getFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(result, 0.0f);
    EXPECT_TRUE(std::signbit(result));
}

// Test a fractional value
TEST_F(GetFloatTest_1143, FractionalValueLittleEndian_1143) {
    float expected = 0.5f;
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test a fractional value big-endian
TEST_F(GetFloatTest_1143, FractionalValueBigEndian_1143) {
    float expected = 0.5f;
    uint32_t bits = floatToUint32(expected);
    storeUint32BE(buf, bits);
    float result = getFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test a large integer value represented as float
TEST_F(GetFloatTest_1143, LargeIntegerFloatLittleEndian_1143) {
    float expected = 1000000.0f;
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test epsilon (smallest difference from 1.0)
TEST_F(GetFloatTest_1143, EpsilonLittleEndian_1143) {
    float expected = std::numeric_limits<float>::epsilon();
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test denormalized minimum
TEST_F(GetFloatTest_1143, DenormalizedMinLittleEndian_1143) {
    float expected = std::numeric_limits<float>::denorm_min();
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test that byte order matters - same bytes give different results
TEST_F(GetFloatTest_1143, ByteOrderMatters_1143) {
    float value = 1.0f; // 0x3F800000
    uint32_t bits = floatToUint32(value);
    storeUint32LE(buf, bits);
    
    float resultLE = getFloat(buf, littleEndian);
    float resultBE = getFloat(buf, bigEndian);
    
    // Unless the value has symmetric byte representation, these should differ
    // 1.0f = 0x3F800000 -> LE: 00 00 80 3F, BE interprets as 0x0000803F which is a tiny denorm
    EXPECT_FLOAT_EQ(resultLE, 1.0f);
    EXPECT_NE(resultLE, resultBE);
}

// Test known bit pattern: 0x41200000 = 10.0f in big-endian
TEST_F(GetFloatTest_1143, KnownBitPatternTenBigEndian_1143) {
    // 10.0f = 0x41200000
    buf[0] = 0x41;
    buf[1] = 0x20;
    buf[2] = 0x00;
    buf[3] = 0x00;
    float result = getFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(result, 10.0f);
}

// Test known bit pattern: 0x41200000 = 10.0f in little-endian
TEST_F(GetFloatTest_1143, KnownBitPatternTenLittleEndian_1143) {
    // 10.0f = 0x41200000, in little-endian: 00 00 20 41
    buf[0] = 0x00;
    buf[1] = 0x00;
    buf[2] = 0x20;
    buf[3] = 0x41;
    float result = getFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(result, 10.0f);
}

// Test known bit pattern: 0x42C80000 = 100.0f
TEST_F(GetFloatTest_1143, KnownBitPatternHundredBigEndian_1143) {
    // 100.0f = 0x42C80000
    buf[0] = 0x42;
    buf[1] = 0xC8;
    buf[2] = 0x00;
    buf[3] = 0x00;
    float result = getFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(result, 100.0f);
}

// Test a very small negative value
TEST_F(GetFloatTest_1143, SmallNegativeValueLittleEndian_1143) {
    float expected = -0.001f;
    uint32_t bits = floatToUint32(expected);
    storeUint32LE(buf, bits);
    float result = getFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(result, expected);
}
