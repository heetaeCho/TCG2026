#include <gtest/gtest.h>
#include <cstring>
#include <cmath>
#include "exiv2/types.hpp"

// Declaration of the function under test
namespace Exiv2 {
    typedef unsigned char byte;
    double getDouble(const byte* buf, ByteOrder byteOrder);
}

using Exiv2::byte;
using Exiv2::getDouble;
using Exiv2::littleEndian;
using Exiv2::bigEndian;

class GetDoubleTest_1144 : public ::testing::Test {
protected:
    // Helper to store a double in little-endian byte order
    void storeDoubleLittleEndian(double val, byte* buf) {
        uint64_t bits;
        std::memcpy(&bits, &val, sizeof(bits));
        for (int i = 0; i < 8; ++i) {
            buf[i] = static_cast<byte>((bits >> (i * 8)) & 0xFF);
        }
    }

    // Helper to store a double in big-endian byte order
    void storeDoubleBigEndian(double val, byte* buf) {
        uint64_t bits;
        std::memcpy(&bits, &val, sizeof(bits));
        for (int i = 0; i < 8; ++i) {
            buf[7 - i] = static_cast<byte>((bits >> (i * 8)) & 0xFF);
        }
    }
};

// Test: Zero value in little endian
TEST_F(GetDoubleTest_1144, ZeroLittleEndian_1144) {
    byte buf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    double result = getDouble(buf, littleEndian);
    EXPECT_EQ(result, 0.0);
}

// Test: Zero value in big endian
TEST_F(GetDoubleTest_1144, ZeroBigEndian_1144) {
    byte buf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    double result = getDouble(buf, bigEndian);
    EXPECT_EQ(result, 0.0);
}

// Test: 1.0 in little endian
TEST_F(GetDoubleTest_1144, OneLittleEndian_1144) {
    byte buf[8];
    storeDoubleLittleEndian(1.0, buf);
    double result = getDouble(buf, littleEndian);
    EXPECT_DOUBLE_EQ(result, 1.0);
}

// Test: 1.0 in big endian
TEST_F(GetDoubleTest_1144, OneBigEndian_1144) {
    byte buf[8];
    storeDoubleBigEndian(1.0, buf);
    double result = getDouble(buf, bigEndian);
    EXPECT_DOUBLE_EQ(result, 1.0);
}

// Test: -1.0 in little endian
TEST_F(GetDoubleTest_1144, NegativeOneLittleEndian_1144) {
    byte buf[8];
    storeDoubleLittleEndian(-1.0, buf);
    double result = getDouble(buf, littleEndian);
    EXPECT_DOUBLE_EQ(result, -1.0);
}

// Test: -1.0 in big endian
TEST_F(GetDoubleTest_1144, NegativeOneBigEndian_1144) {
    byte buf[8];
    storeDoubleBigEndian(-1.0, buf);
    double result = getDouble(buf, bigEndian);
    EXPECT_DOUBLE_EQ(result, -1.0);
}

// Test: Pi in little endian
TEST_F(GetDoubleTest_1144, PiLittleEndian_1144) {
    byte buf[8];
    double pi = 3.141592653589793;
    storeDoubleLittleEndian(pi, buf);
    double result = getDouble(buf, littleEndian);
    EXPECT_DOUBLE_EQ(result, pi);
}

// Test: Pi in big endian
TEST_F(GetDoubleTest_1144, PiBigEndian_1144) {
    byte buf[8];
    double pi = 3.141592653589793;
    storeDoubleBigEndian(pi, buf);
    double result = getDouble(buf, bigEndian);
    EXPECT_DOUBLE_EQ(result, pi);
}

// Test: Very small positive number (subnormal) in little endian
TEST_F(GetDoubleTest_1144, SmallPositiveLittleEndian_1144) {
    byte buf[8];
    double val = 5e-324; // smallest positive subnormal double
    storeDoubleLittleEndian(val, buf);
    double result = getDouble(buf, littleEndian);
    EXPECT_DOUBLE_EQ(result, val);
}

// Test: Very small positive number in big endian
TEST_F(GetDoubleTest_1144, SmallPositiveBigEndian_1144) {
    byte buf[8];
    double val = 5e-324;
    storeDoubleBigEndian(val, buf);
    double result = getDouble(buf, bigEndian);
    EXPECT_DOUBLE_EQ(result, val);
}

// Test: Max double in little endian
TEST_F(GetDoubleTest_1144, MaxDoubleLittleEndian_1144) {
    byte buf[8];
    double val = std::numeric_limits<double>::max();
    storeDoubleLittleEndian(val, buf);
    double result = getDouble(buf, littleEndian);
    EXPECT_DOUBLE_EQ(result, val);
}

// Test: Max double in big endian
TEST_F(GetDoubleTest_1144, MaxDoubleBigEndian_1144) {
    byte buf[8];
    double val = std::numeric_limits<double>::max();
    storeDoubleBigEndian(val, buf);
    double result = getDouble(buf, bigEndian);
    EXPECT_DOUBLE_EQ(result, val);
}

// Test: Lowest (most negative) double in little endian
TEST_F(GetDoubleTest_1144, LowestDoubleLittleEndian_1144) {
    byte buf[8];
    double val = std::numeric_limits<double>::lowest();
    storeDoubleLittleEndian(val, buf);
    double result = getDouble(buf, littleEndian);
    EXPECT_DOUBLE_EQ(result, val);
}

// Test: Infinity in little endian
TEST_F(GetDoubleTest_1144, InfinityLittleEndian_1144) {
    byte buf[8];
    double val = std::numeric_limits<double>::infinity();
    storeDoubleLittleEndian(val, buf);
    double result = getDouble(buf, littleEndian);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_GT(result, 0);
}

// Test: Infinity in big endian
TEST_F(GetDoubleTest_1144, InfinityBigEndian_1144) {
    byte buf[8];
    double val = std::numeric_limits<double>::infinity();
    storeDoubleBigEndian(val, buf);
    double result = getDouble(buf, bigEndian);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_GT(result, 0);
}

// Test: Negative infinity in little endian
TEST_F(GetDoubleTest_1144, NegativeInfinityLittleEndian_1144) {
    byte buf[8];
    double val = -std::numeric_limits<double>::infinity();
    storeDoubleLittleEndian(val, buf);
    double result = getDouble(buf, littleEndian);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_LT(result, 0);
}

// Test: NaN in little endian
TEST_F(GetDoubleTest_1144, NaNLittleEndian_1144) {
    byte buf[8];
    double val = std::numeric_limits<double>::quiet_NaN();
    storeDoubleLittleEndian(val, buf);
    double result = getDouble(buf, littleEndian);
    EXPECT_TRUE(std::isnan(result));
}

// Test: NaN in big endian
TEST_F(GetDoubleTest_1144, NaNBigEndian_1144) {
    byte buf[8];
    double val = std::numeric_limits<double>::quiet_NaN();
    storeDoubleBigEndian(val, buf);
    double result = getDouble(buf, bigEndian);
    EXPECT_TRUE(std::isnan(result));
}

// Test: Negative zero in little endian
TEST_F(GetDoubleTest_1144, NegativeZeroLittleEndian_1144) {
    byte buf[8];
    double val = -0.0;
    storeDoubleLittleEndian(val, buf);
    double result = getDouble(buf, littleEndian);
    EXPECT_EQ(result, 0.0);
    // Check sign bit: -0.0 should have sign bit set
    EXPECT_TRUE(std::signbit(result));
}

// Test: Negative zero in big endian
TEST_F(GetDoubleTest_1144, NegativeZeroBigEndian_1144) {
    byte buf[8];
    double val = -0.0;
    storeDoubleBigEndian(val, buf);
    double result = getDouble(buf, bigEndian);
    EXPECT_EQ(result, 0.0);
    EXPECT_TRUE(std::signbit(result));
}

// Test: Known IEEE 754 representation of 1.0 in big endian (0x3FF0000000000000)
TEST_F(GetDoubleTest_1144, KnownBytesOneBigEndian_1144) {
    byte buf[8] = {0x3F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    double result = getDouble(buf, bigEndian);
    EXPECT_DOUBLE_EQ(result, 1.0);
}

// Test: Known IEEE 754 representation of 1.0 in little endian
TEST_F(GetDoubleTest_1144, KnownBytesOneLittleEndian_1144) {
    byte buf[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F};
    double result = getDouble(buf, littleEndian);
    EXPECT_DOUBLE_EQ(result, 1.0);
}

// Test: Arbitrary fractional value round-trip in little endian
TEST_F(GetDoubleTest_1144, ArbitraryFractionalLittleEndian_1144) {
    byte buf[8];
    double val = 123456.789012345;
    storeDoubleLittleEndian(val, buf);
    double result = getDouble(buf, littleEndian);
    EXPECT_DOUBLE_EQ(result, val);
}

// Test: Arbitrary fractional value round-trip in big endian
TEST_F(GetDoubleTest_1144, ArbitraryFractionalBigEndian_1144) {
    byte buf[8];
    double val = -987654.321098765;
    storeDoubleBigEndian(val, buf);
    double result = getDouble(buf, bigEndian);
    EXPECT_DOUBLE_EQ(result, val);
}

// Test: Epsilon in little endian
TEST_F(GetDoubleTest_1144, EpsilonLittleEndian_1144) {
    byte buf[8];
    double val = std::numeric_limits<double>::epsilon();
    storeDoubleLittleEndian(val, buf);
    double result = getDouble(buf, littleEndian);
    EXPECT_DOUBLE_EQ(result, val);
}

// Test: Byte order matters - same bytes give different results for LE and BE
TEST_F(GetDoubleTest_1144, ByteOrderMatters_1144) {
    byte buf[8];
    double val = 42.5;
    storeDoubleLittleEndian(val, buf);
    double resultLE = getDouble(buf, littleEndian);
    double resultBE = getDouble(buf, bigEndian);
    // Unless the value has a palindrome bit pattern, these should differ
    EXPECT_DOUBLE_EQ(resultLE, val);
    // resultBE should not equal val (42.5 doesn't have palindrome pattern)
    EXPECT_NE(resultBE, val);
}

// Test: Denormalized (subnormal) min value in big endian
TEST_F(GetDoubleTest_1144, DenormMinBigEndian_1144) {
    byte buf[8];
    double val = std::numeric_limits<double>::denorm_min();
    storeDoubleBigEndian(val, buf);
    double result = getDouble(buf, bigEndian);
    EXPECT_DOUBLE_EQ(result, val);
}

// Test: Min normal positive double in little endian
TEST_F(GetDoubleTest_1144, MinNormalLittleEndian_1144) {
    byte buf[8];
    double val = std::numeric_limits<double>::min();
    storeDoubleLittleEndian(val, buf);
    double result = getDouble(buf, littleEndian);
    EXPECT_DOUBLE_EQ(result, val);
}
