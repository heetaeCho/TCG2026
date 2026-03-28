#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;

// Test normal operation with positive rational and big endian byte order
TEST(ToDataRationalTest_144, PositiveRationalBigEndian_144) {
    byte buf[8] = {0};
    Rational r(1, 2);
    size_t result = toData(buf, r, bigEndian);
    EXPECT_EQ(result, 8u);

    // Verify by reading back
    int32_t numerator = getLong(buf, bigEndian);
    int32_t denominator = getLong(buf + 4, bigEndian);
    EXPECT_EQ(numerator, 1);
    EXPECT_EQ(denominator, 2);
}

// Test normal operation with positive rational and little endian byte order
TEST(ToDataRationalTest_144, PositiveRationalLittleEndian_144) {
    byte buf[8] = {0};
    Rational r(3, 4);
    size_t result = toData(buf, r, littleEndian);
    EXPECT_EQ(result, 8u);

    int32_t numerator = getLong(buf, littleEndian);
    int32_t denominator = getLong(buf + 4, littleEndian);
    EXPECT_EQ(numerator, 3);
    EXPECT_EQ(denominator, 4);
}

// Test with zero numerator
TEST(ToDataRationalTest_144, ZeroNumerator_144) {
    byte buf[8] = {0};
    Rational r(0, 1);
    size_t result = toData(buf, r, bigEndian);
    EXPECT_EQ(result, 8u);

    int32_t numerator = getLong(buf, bigEndian);
    int32_t denominator = getLong(buf + 4, bigEndian);
    EXPECT_EQ(numerator, 0);
    EXPECT_EQ(denominator, 1);
}

// Test with negative numerator
TEST(ToDataRationalTest_144, NegativeNumerator_144) {
    byte buf[8] = {0};
    Rational r(-5, 3);
    size_t result = toData(buf, r, bigEndian);
    EXPECT_EQ(result, 8u);

    int32_t numerator = getLong(buf, bigEndian);
    int32_t denominator = getLong(buf + 4, bigEndian);
    EXPECT_EQ(numerator, -5);
    EXPECT_EQ(denominator, 3);
}

// Test with negative denominator
TEST(ToDataRationalTest_144, NegativeDenominator_144) {
    byte buf[8] = {0};
    Rational r(7, -2);
    size_t result = toData(buf, r, bigEndian);
    EXPECT_EQ(result, 8u);

    int32_t numerator = getLong(buf, bigEndian);
    int32_t denominator = getLong(buf + 4, bigEndian);
    EXPECT_EQ(numerator, 7);
    EXPECT_EQ(denominator, -2);
}

// Test with both negative
TEST(ToDataRationalTest_144, BothNegative_144) {
    byte buf[8] = {0};
    Rational r(-10, -3);
    size_t result = toData(buf, r, littleEndian);
    EXPECT_EQ(result, 8u);

    int32_t numerator = getLong(buf, littleEndian);
    int32_t denominator = getLong(buf + 4, littleEndian);
    EXPECT_EQ(numerator, -10);
    EXPECT_EQ(denominator, -3);
}

// Test with maximum int32 values
TEST(ToDataRationalTest_144, MaxInt32Values_144) {
    byte buf[8] = {0};
    Rational r(INT32_MAX, INT32_MAX);
    size_t result = toData(buf, r, bigEndian);
    EXPECT_EQ(result, 8u);

    int32_t numerator = getLong(buf, bigEndian);
    int32_t denominator = getLong(buf + 4, bigEndian);
    EXPECT_EQ(numerator, INT32_MAX);
    EXPECT_EQ(denominator, INT32_MAX);
}

// Test with minimum int32 values
TEST(ToDataRationalTest_144, MinInt32Values_144) {
    byte buf[8] = {0};
    Rational r(INT32_MIN, INT32_MIN);
    size_t result = toData(buf, r, littleEndian);
    EXPECT_EQ(result, 8u);

    int32_t numerator = getLong(buf, littleEndian);
    int32_t denominator = getLong(buf + 4, littleEndian);
    EXPECT_EQ(numerator, INT32_MIN);
    EXPECT_EQ(denominator, INT32_MIN);
}

// Test with zero denominator (boundary case)
TEST(ToDataRationalTest_144, ZeroDenominator_144) {
    byte buf[8] = {0};
    Rational r(1, 0);
    size_t result = toData(buf, r, bigEndian);
    EXPECT_EQ(result, 8u);

    int32_t numerator = getLong(buf, bigEndian);
    int32_t denominator = getLong(buf + 4, bigEndian);
    EXPECT_EQ(numerator, 1);
    EXPECT_EQ(denominator, 0);
}

// Test that return value is always 8 (size of two int32_t)
TEST(ToDataRationalTest_144, ReturnValueIsAlwaysEight_144) {
    byte buf[8] = {0};
    Rational r1(0, 0);
    EXPECT_EQ(toData(buf, r1, bigEndian), 8u);

    Rational r2(100, 200);
    EXPECT_EQ(toData(buf, r2, littleEndian), 8u);

    Rational r3(-1, 1);
    EXPECT_EQ(toData(buf, r3, bigEndian), 8u);
}

// Test that byte order actually matters (same value produces different bytes)
TEST(ToDataRationalTest_144, ByteOrderMatters_144) {
    byte bufBE[8] = {0};
    byte bufLE[8] = {0};
    Rational r(0x01020304, 0x05060708);

    toData(bufBE, r, bigEndian);
    toData(bufLE, r, littleEndian);

    // The buffers should be different for non-palindromic values
    EXPECT_NE(0, std::memcmp(bufBE, bufLE, 8));
}

// Test with unit rational (1/1)
TEST(ToDataRationalTest_144, UnitRational_144) {
    byte buf[8] = {0};
    Rational r(1, 1);
    size_t result = toData(buf, r, bigEndian);
    EXPECT_EQ(result, 8u);

    int32_t numerator = getLong(buf, bigEndian);
    int32_t denominator = getLong(buf + 4, bigEndian);
    EXPECT_EQ(numerator, 1);
    EXPECT_EQ(denominator, 1);
}

// Test consecutive calls overwrite buffer correctly
TEST(ToDataRationalTest_144, ConsecutiveCallsOverwrite_144) {
    byte buf[8] = {0};

    Rational r1(100, 200);
    toData(buf, r1, bigEndian);
    int32_t num1 = getLong(buf, bigEndian);
    int32_t den1 = getLong(buf + 4, bigEndian);
    EXPECT_EQ(num1, 100);
    EXPECT_EQ(den1, 200);

    Rational r2(300, 400);
    toData(buf, r2, bigEndian);
    int32_t num2 = getLong(buf, bigEndian);
    int32_t den2 = getLong(buf + 4, bigEndian);
    EXPECT_EQ(num2, 300);
    EXPECT_EQ(den2, 400);
}
