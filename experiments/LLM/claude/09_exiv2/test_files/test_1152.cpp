#include <gtest/gtest.h>
#include <cmath>
#include <cstring>
#include <limits>

#include "types.hpp"

using namespace Exiv2;

class F2DataTest_1152 : public ::testing::Test {
protected:
  byte buf[4];

  void SetUp() override {
    std::memset(buf, 0, sizeof(buf));
  }
};

// Test that f2Data returns the correct number of bytes written (should be 4 for a float)
TEST_F(F2DataTest_1152, ReturnsCorrectSize_1152) {
  float f = 1.0f;
  size_t result = f2Data(buf, f, littleEndian);
  EXPECT_EQ(result, 4u);
}

TEST_F(F2DataTest_1152, ReturnsCorrectSizeBigEndian_1152) {
  float f = 1.0f;
  size_t result = f2Data(buf, f, bigEndian);
  EXPECT_EQ(result, 4u);
}

// Test zero value in little endian
TEST_F(F2DataTest_1152, ZeroValueLittleEndian_1152) {
  float f = 0.0f;
  f2Data(buf, f, littleEndian);
  // IEEE 754: 0.0f is all zeros
  EXPECT_EQ(buf[0], 0);
  EXPECT_EQ(buf[1], 0);
  EXPECT_EQ(buf[2], 0);
  EXPECT_EQ(buf[3], 0);
}

// Test zero value in big endian
TEST_F(F2DataTest_1152, ZeroValueBigEndian_1152) {
  float f = 0.0f;
  f2Data(buf, f, bigEndian);
  EXPECT_EQ(buf[0], 0);
  EXPECT_EQ(buf[1], 0);
  EXPECT_EQ(buf[2], 0);
  EXPECT_EQ(buf[3], 0);
}

// Test that encoding 1.0f in little endian produces correct IEEE 754 representation
// 1.0f in IEEE 754 = 0x3F800000
TEST_F(F2DataTest_1152, OnePointZeroLittleEndian_1152) {
  float f = 1.0f;
  f2Data(buf, f, littleEndian);
  // Little endian: LSB first
  EXPECT_EQ(buf[0], 0x00);
  EXPECT_EQ(buf[1], 0x00);
  EXPECT_EQ(buf[2], 0x80);
  EXPECT_EQ(buf[3], 0x3F);
}

// Test that encoding 1.0f in big endian produces correct IEEE 754 representation
TEST_F(F2DataTest_1152, OnePointZeroBigEndian_1152) {
  float f = 1.0f;
  f2Data(buf, f, bigEndian);
  // Big endian: MSB first
  EXPECT_EQ(buf[0], 0x3F);
  EXPECT_EQ(buf[1], 0x80);
  EXPECT_EQ(buf[2], 0x00);
  EXPECT_EQ(buf[3], 0x00);
}

// Test negative value: -1.0f = 0xBF800000
TEST_F(F2DataTest_1152, NegativeOnePointZeroLittleEndian_1152) {
  float f = -1.0f;
  f2Data(buf, f, littleEndian);
  EXPECT_EQ(buf[0], 0x00);
  EXPECT_EQ(buf[1], 0x00);
  EXPECT_EQ(buf[2], 0x80);
  EXPECT_EQ(buf[3], 0xBF);
}

TEST_F(F2DataTest_1152, NegativeOnePointZeroBigEndian_1152) {
  float f = -1.0f;
  f2Data(buf, f, bigEndian);
  EXPECT_EQ(buf[0], 0xBF);
  EXPECT_EQ(buf[1], 0x80);
  EXPECT_EQ(buf[2], 0x00);
  EXPECT_EQ(buf[3], 0x00);
}

// Test that big endian and little endian produce reversed byte order for the same value
TEST_F(F2DataTest_1152, ByteOrderReversal_1152) {
  float f = 3.14f;
  byte bufLE[4], bufBE[4];
  f2Data(bufLE, f, littleEndian);
  f2Data(bufBE, f, bigEndian);

  EXPECT_EQ(bufLE[0], bufBE[3]);
  EXPECT_EQ(bufLE[1], bufBE[2]);
  EXPECT_EQ(bufLE[2], bufBE[1]);
  EXPECT_EQ(bufLE[3], bufBE[0]);
}

// Test positive infinity: IEEE 754 = 0x7F800000
TEST_F(F2DataTest_1152, PositiveInfinityBigEndian_1152) {
  float f = std::numeric_limits<float>::infinity();
  f2Data(buf, f, bigEndian);
  EXPECT_EQ(buf[0], 0x7F);
  EXPECT_EQ(buf[1], 0x80);
  EXPECT_EQ(buf[2], 0x00);
  EXPECT_EQ(buf[3], 0x00);
}

// Test negative infinity: IEEE 754 = 0xFF800000
TEST_F(F2DataTest_1152, NegativeInfinityBigEndian_1152) {
  float f = -std::numeric_limits<float>::infinity();
  f2Data(buf, f, bigEndian);
  EXPECT_EQ(buf[0], 0xFF);
  EXPECT_EQ(buf[1], 0x80);
  EXPECT_EQ(buf[2], 0x00);
  EXPECT_EQ(buf[3], 0x00);
}

// Test NaN - the sign bit may vary but exponent should be all 1s and mantissa non-zero
TEST_F(F2DataTest_1152, NaNBigEndian_1152) {
  float f = std::numeric_limits<float>::quiet_NaN();
  f2Data(buf, f, bigEndian);
  // Exponent bits should be all 1s (0x7F8 in upper bits)
  EXPECT_EQ(buf[0] & 0x7F, 0x7F);
  EXPECT_TRUE((buf[1] & 0x80) == 0x80); // exponent continuation
  // Mantissa should be non-zero for NaN
  uint32_t mantissa = ((uint32_t)(buf[1] & 0x7F) << 16) | ((uint32_t)buf[2] << 8) | buf[3];
  EXPECT_NE(mantissa, 0u);
}

// Test max float value: FLT_MAX = 0x7F7FFFFF
TEST_F(F2DataTest_1152, MaxFloatBigEndian_1152) {
  float f = std::numeric_limits<float>::max();
  f2Data(buf, f, bigEndian);
  EXPECT_EQ(buf[0], 0x7F);
  EXPECT_EQ(buf[1], 0x7F);
  EXPECT_EQ(buf[2], 0xFF);
  EXPECT_EQ(buf[3], 0xFF);
}

// Test smallest positive normalized float: FLT_MIN = 0x00800000
TEST_F(F2DataTest_1152, MinNormalizedFloatBigEndian_1152) {
  float f = std::numeric_limits<float>::min();
  f2Data(buf, f, bigEndian);
  EXPECT_EQ(buf[0], 0x00);
  EXPECT_EQ(buf[1], 0x80);
  EXPECT_EQ(buf[2], 0x00);
  EXPECT_EQ(buf[3], 0x00);
}

// Test denormalized (subnormal) float: smallest denorm = 0x00000001
TEST_F(F2DataTest_1152, DenormalizedFloatBigEndian_1152) {
  float f = std::numeric_limits<float>::denorm_min();
  f2Data(buf, f, bigEndian);
  EXPECT_EQ(buf[0], 0x00);
  EXPECT_EQ(buf[1], 0x00);
  EXPECT_EQ(buf[2], 0x00);
  EXPECT_EQ(buf[3], 0x01);
}

// Test negative zero: -0.0f = 0x80000000
TEST_F(F2DataTest_1152, NegativeZeroBigEndian_1152) {
  float f = -0.0f;
  f2Data(buf, f, bigEndian);
  EXPECT_EQ(buf[0], 0x80);
  EXPECT_EQ(buf[1], 0x00);
  EXPECT_EQ(buf[2], 0x00);
  EXPECT_EQ(buf[3], 0x00);
}

// Test a specific float value: 2.0f = 0x40000000
TEST_F(F2DataTest_1152, TwoPointZeroBigEndian_1152) {
  float f = 2.0f;
  f2Data(buf, f, bigEndian);
  EXPECT_EQ(buf[0], 0x40);
  EXPECT_EQ(buf[1], 0x00);
  EXPECT_EQ(buf[2], 0x00);
  EXPECT_EQ(buf[3], 0x00);
}

// Test that the same value written twice produces the same bytes
TEST_F(F2DataTest_1152, Deterministic_1152) {
  float f = 42.5f;
  byte buf1[4], buf2[4];
  f2Data(buf1, f, littleEndian);
  f2Data(buf2, f, littleEndian);
  EXPECT_EQ(std::memcmp(buf1, buf2, 4), 0);
}

// Test a fractional value: 0.5f = 0x3F000000
TEST_F(F2DataTest_1152, ZeroPointFiveBigEndian_1152) {
  float f = 0.5f;
  f2Data(buf, f, bigEndian);
  EXPECT_EQ(buf[0], 0x3F);
  EXPECT_EQ(buf[1], 0x00);
  EXPECT_EQ(buf[2], 0x00);
  EXPECT_EQ(buf[3], 0x00);
}

// Test a large negative value: -FLT_MAX = 0xFF7FFFFF
TEST_F(F2DataTest_1152, NegativeMaxFloatBigEndian_1152) {
  float f = -std::numeric_limits<float>::max();
  f2Data(buf, f, bigEndian);
  EXPECT_EQ(buf[0], 0xFF);
  EXPECT_EQ(buf[1], 0x7F);
  EXPECT_EQ(buf[2], 0xFF);
  EXPECT_EQ(buf[3], 0xFF);
}
