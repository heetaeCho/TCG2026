#include <gtest/gtest.h>
#include <exiv2/types.hpp>

using namespace Exiv2;

// Test normal operation with big endian byte order
TEST(R2DataTest_1151, NormalOperationBigEndian_1151) {
  byte buf[8] = {0};
  Rational r(1, 2);
  size_t result = r2Data(buf, r, bigEndian);
  EXPECT_EQ(result, 8u);
  
  // Verify the first 4 bytes represent the numerator (1) in big endian
  int32_t numerator = getLong(buf, bigEndian);
  EXPECT_EQ(numerator, 1);
  
  // Verify the next 4 bytes represent the denominator (2) in big endian
  int32_t denominator = getLong(buf + 4, bigEndian);
  EXPECT_EQ(denominator, 2);
}

// Test normal operation with little endian byte order
TEST(R2DataTest_1151, NormalOperationLittleEndian_1151) {
  byte buf[8] = {0};
  Rational r(100, 300);
  size_t result = r2Data(buf, r, littleEndian);
  EXPECT_EQ(result, 8u);
  
  int32_t numerator = getLong(buf, littleEndian);
  EXPECT_EQ(numerator, 100);
  
  int32_t denominator = getLong(buf + 4, littleEndian);
  EXPECT_EQ(denominator, 300);
}

// Test with zero values
TEST(R2DataTest_1151, ZeroValues_1151) {
  byte buf[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  Rational r(0, 0);
  size_t result = r2Data(buf, r, bigEndian);
  EXPECT_EQ(result, 8u);
  
  int32_t numerator = getLong(buf, bigEndian);
  EXPECT_EQ(numerator, 0);
  
  int32_t denominator = getLong(buf + 4, bigEndian);
  EXPECT_EQ(denominator, 0);
}

// Test with negative numerator
TEST(R2DataTest_1151, NegativeNumerator_1151) {
  byte buf[8] = {0};
  Rational r(-5, 10);
  size_t result = r2Data(buf, r, bigEndian);
  EXPECT_EQ(result, 8u);
  
  int32_t numerator = getLong(buf, bigEndian);
  EXPECT_EQ(numerator, -5);
  
  int32_t denominator = getLong(buf + 4, bigEndian);
  EXPECT_EQ(denominator, 10);
}

// Test with negative denominator
TEST(R2DataTest_1151, NegativeDenominator_1151) {
  byte buf[8] = {0};
  Rational r(7, -3);
  size_t result = r2Data(buf, r, littleEndian);
  EXPECT_EQ(result, 8u);
  
  int32_t numerator = getLong(buf, littleEndian);
  EXPECT_EQ(numerator, 7);
  
  int32_t denominator = getLong(buf + 4, littleEndian);
  EXPECT_EQ(denominator, -3);
}

// Test with both negative values
TEST(R2DataTest_1151, BothNegativeValues_1151) {
  byte buf[8] = {0};
  Rational r(-100, -200);
  size_t result = r2Data(buf, r, bigEndian);
  EXPECT_EQ(result, 8u);
  
  int32_t numerator = getLong(buf, bigEndian);
  EXPECT_EQ(numerator, -100);
  
  int32_t denominator = getLong(buf + 4, bigEndian);
  EXPECT_EQ(denominator, -200);
}

// Test with maximum int32 values
TEST(R2DataTest_1151, MaxInt32Values_1151) {
  byte buf[8] = {0};
  Rational r(INT32_MAX, INT32_MAX);
  size_t result = r2Data(buf, r, bigEndian);
  EXPECT_EQ(result, 8u);
  
  int32_t numerator = getLong(buf, bigEndian);
  EXPECT_EQ(numerator, INT32_MAX);
  
  int32_t denominator = getLong(buf + 4, bigEndian);
  EXPECT_EQ(denominator, INT32_MAX);
}

// Test with minimum int32 values
TEST(R2DataTest_1151, MinInt32Values_1151) {
  byte buf[8] = {0};
  Rational r(INT32_MIN, INT32_MIN);
  size_t result = r2Data(buf, r, littleEndian);
  EXPECT_EQ(result, 8u);
  
  int32_t numerator = getLong(buf, littleEndian);
  EXPECT_EQ(numerator, INT32_MIN);
  
  int32_t denominator = getLong(buf + 4, littleEndian);
  EXPECT_EQ(denominator, INT32_MIN);
}

// Test return value is always 8
TEST(R2DataTest_1151, ReturnValueAlways8_1151) {
  byte buf[8] = {0};
  
  Rational r1(1, 1);
  EXPECT_EQ(r2Data(buf, r1, bigEndian), 8u);
  
  Rational r2(0, 0);
  EXPECT_EQ(r2Data(buf, r2, littleEndian), 8u);
  
  Rational r3(-1, -1);
  EXPECT_EQ(r2Data(buf, r3, bigEndian), 8u);
}

// Test with numerator 1 and denominator 1 (identity rational)
TEST(R2DataTest_1151, IdentityRational_1151) {
  byte buf[8] = {0};
  Rational r(1, 1);
  size_t result = r2Data(buf, r, littleEndian);
  EXPECT_EQ(result, 8u);
  
  int32_t numerator = getLong(buf, littleEndian);
  EXPECT_EQ(numerator, 1);
  
  int32_t denominator = getLong(buf + 4, littleEndian);
  EXPECT_EQ(denominator, 1);
}

// Test that big endian and little endian produce different byte patterns
TEST(R2DataTest_1151, EndiannessDifference_1151) {
  byte bufBE[8] = {0};
  byte bufLE[8] = {0};
  Rational r(0x01020304, 0x05060708);
  
  r2Data(bufBE, r, bigEndian);
  r2Data(bufLE, r, littleEndian);
  
  // The byte representations should differ for multi-byte values
  bool differ = false;
  for (int i = 0; i < 8; ++i) {
    if (bufBE[i] != bufLE[i]) {
      differ = true;
      break;
    }
  }
  EXPECT_TRUE(differ);
}

// Test with numerator zero and non-zero denominator
TEST(R2DataTest_1151, ZeroNumeratorNonZeroDenominator_1151) {
  byte buf[8] = {0};
  Rational r(0, 42);
  size_t result = r2Data(buf, r, bigEndian);
  EXPECT_EQ(result, 8u);
  
  int32_t numerator = getLong(buf, bigEndian);
  EXPECT_EQ(numerator, 0);
  
  int32_t denominator = getLong(buf + 4, bigEndian);
  EXPECT_EQ(denominator, 42);
}

// Test with non-zero numerator and zero denominator
TEST(R2DataTest_1151, NonZeroNumeratorZeroDenominator_1151) {
  byte buf[8] = {0};
  Rational r(42, 0);
  size_t result = r2Data(buf, r, littleEndian);
  EXPECT_EQ(result, 8u);
  
  int32_t numerator = getLong(buf, littleEndian);
  EXPECT_EQ(numerator, 42);
  
  int32_t denominator = getLong(buf + 4, littleEndian);
  EXPECT_EQ(denominator, 0);
}
