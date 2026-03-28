#include <gtest/gtest.h>
#include <limits>
#include <cstdint>
#include "GooCheckedOps.h"

// Tests for safeAverage<T>

// --- int tests ---

TEST(SafeAverageTest_8, AverageOfTwoPositiveInts_8) {
    EXPECT_EQ(safeAverage<int>(4, 6), 5);
}

TEST(SafeAverageTest_8, AverageOfTwoNegativeInts_8) {
    EXPECT_EQ(safeAverage<int>(-4, -6), -5);
}

TEST(SafeAverageTest_8, AverageOfPositiveAndNegativeInt_8) {
    EXPECT_EQ(safeAverage<int>(-3, 7), 2);
}

TEST(SafeAverageTest_8, AverageOfZeros_8) {
    EXPECT_EQ(safeAverage<int>(0, 0), 0);
}

TEST(SafeAverageTest_8, AverageOfZeroAndPositive_8) {
    EXPECT_EQ(safeAverage<int>(0, 10), 5);
}

TEST(SafeAverageTest_8, AverageOfZeroAndNegative_8) {
    EXPECT_EQ(safeAverage<int>(0, -10), -5);
}

TEST(SafeAverageTest_8, AverageOfSameValues_8) {
    EXPECT_EQ(safeAverage<int>(42, 42), 42);
}

TEST(SafeAverageTest_8, AverageWithOddSum_TruncatesTowardZero_8) {
    // (3 + 4) / 2 = 7 / 2 = 3 (integer division truncates toward zero)
    EXPECT_EQ(safeAverage<int>(3, 4), 3);
}

TEST(SafeAverageTest_8, AverageWithNegativeOddSum_TruncatesTowardZero_8) {
    // (-3 + -4) / 2 = -7 / 2 = -3 (truncation toward zero in C++)
    EXPECT_EQ(safeAverage<int>(-3, -4), -3);
}

TEST(SafeAverageTest_8, AverageOfIntMaxValues_8) {
    int maxVal = std::numeric_limits<int>::max();
    // Without long long promotion this would overflow. safeAverage should handle it.
    int result = safeAverage<int>(maxVal, maxVal);
    EXPECT_EQ(result, maxVal);
}

TEST(SafeAverageTest_8, AverageOfIntMinValues_8) {
    int minVal = std::numeric_limits<int>::min();
    int result = safeAverage<int>(minVal, minVal);
    EXPECT_EQ(result, minVal);
}

TEST(SafeAverageTest_8, AverageOfIntMaxAndIntMin_8) {
    int maxVal = std::numeric_limits<int>::max();
    int minVal = std::numeric_limits<int>::min();
    // (INT_MAX + INT_MIN) / 2 — INT_MAX is 2147483647, INT_MIN is -2147483648
    // Sum = -1, average = -1/2 = 0 (truncation toward zero)
    int result = safeAverage<int>(maxVal, minVal);
    EXPECT_EQ(result, 0);
}

TEST(SafeAverageTest_8, AverageOfIntMaxAndZero_8) {
    int maxVal = std::numeric_limits<int>::max();
    // 2147483647 / 2 = 1073741823
    EXPECT_EQ(safeAverage<int>(maxVal, 0), maxVal / 2);
}

TEST(SafeAverageTest_8, AverageOfIntMinAndZero_8) {
    int minVal = std::numeric_limits<int>::min();
    EXPECT_EQ(safeAverage<int>(minVal, 0), minVal / 2);
}

TEST(SafeAverageTest_8, AverageOfIntMaxAndOne_8) {
    int maxVal = std::numeric_limits<int>::max();
    // (2147483647 + 1) / 2 = 2147483648 / 2 = 1073741824
    int result = safeAverage<int>(maxVal, 1);
    EXPECT_EQ(result, static_cast<int>((static_cast<long long>(maxVal) + 1LL) / 2));
}

TEST(SafeAverageTest_8, AverageOfIntMinAndMinusOne_8) {
    int minVal = std::numeric_limits<int>::min();
    // (-2147483648 + -1) / 2 = -2147483649 / 2 = -1073741824 (truncated toward zero)
    int result = safeAverage<int>(minVal, -1);
    long long expected = (static_cast<long long>(minVal) + static_cast<long long>(-1)) / 2;
    EXPECT_EQ(result, static_cast<int>(expected));
}

// --- short tests ---

TEST(SafeAverageTest_8, AverageOfShortValues_8) {
    short a = 100, b = 200;
    EXPECT_EQ(safeAverage<short>(a, b), 150);
}

TEST(SafeAverageTest_8, AverageOfShortMaxValues_8) {
    short maxVal = std::numeric_limits<short>::max();
    short result = safeAverage<short>(maxVal, maxVal);
    EXPECT_EQ(result, maxVal);
}

TEST(SafeAverageTest_8, AverageOfShortMinValues_8) {
    short minVal = std::numeric_limits<short>::min();
    short result = safeAverage<short>(minVal, minVal);
    EXPECT_EQ(result, minVal);
}

TEST(SafeAverageTest_8, AverageOfShortMaxAndMin_8) {
    short maxVal = std::numeric_limits<short>::max();
    short minVal = std::numeric_limits<short>::min();
    short result = safeAverage<short>(maxVal, minVal);
    long long expected = (static_cast<long long>(maxVal) + static_cast<long long>(minVal)) / 2;
    EXPECT_EQ(result, static_cast<short>(expected));
}

// --- int32_t tests ---

TEST(SafeAverageTest_8, AverageOfInt32MaxValues_8) {
    int32_t maxVal = std::numeric_limits<int32_t>::max();
    int32_t result = safeAverage<int32_t>(maxVal, maxVal);
    EXPECT_EQ(result, maxVal);
}

TEST(SafeAverageTest_8, AverageOfInt32MinValues_8) {
    int32_t minVal = std::numeric_limits<int32_t>::min();
    int32_t result = safeAverage<int32_t>(minVal, minVal);
    EXPECT_EQ(result, minVal);
}

// --- Commutativity test ---

TEST(SafeAverageTest_8, AverageIsCommutative_8) {
    EXPECT_EQ(safeAverage<int>(3, 7), safeAverage<int>(7, 3));
}

TEST(SafeAverageTest_8, AverageIsCommutativeForNegatives_8) {
    EXPECT_EQ(safeAverage<int>(-5, 15), safeAverage<int>(15, -5));
}

// --- Symmetry around zero ---

TEST(SafeAverageTest_8, AverageOfOpposites_8) {
    EXPECT_EQ(safeAverage<int>(10, -10), 0);
}

TEST(SafeAverageTest_8, AverageOfLargeOpposites_8) {
    EXPECT_EQ(safeAverage<int>(1000000, -1000000), 0);
}

// --- unsigned char test (to verify with small unsigned type) ---

TEST(SafeAverageTest_8, AverageOfUnsignedCharValues_8) {
    unsigned char a = 200, b = 100;
    EXPECT_EQ(safeAverage<unsigned char>(a, b), 150);
}

TEST(SafeAverageTest_8, AverageOfUnsignedCharMaxValues_8) {
    unsigned char maxVal = std::numeric_limits<unsigned char>::max();
    unsigned char result = safeAverage<unsigned char>(maxVal, maxVal);
    EXPECT_EQ(result, maxVal);
}

TEST(SafeAverageTest_8, AverageOfUnsignedCharZeroAndMax_8) {
    unsigned char maxVal = std::numeric_limits<unsigned char>::max();
    unsigned char result = safeAverage<unsigned char>(0, maxVal);
    EXPECT_EQ(result, static_cast<unsigned char>(maxVal / 2));
}

// --- signed char test ---

TEST(SafeAverageTest_8, AverageOfSignedCharMinMax_8) {
    signed char maxVal = std::numeric_limits<signed char>::max();
    signed char minVal = std::numeric_limits<signed char>::min();
    signed char result = safeAverage<signed char>(maxVal, minVal);
    long long expected = (static_cast<long long>(maxVal) + static_cast<long long>(minVal)) / 2;
    EXPECT_EQ(result, static_cast<signed char>(expected));
}

// --- int16_t test ---

TEST(SafeAverageTest_8, AverageOfInt16MaxAndMin_8) {
    int16_t maxVal = std::numeric_limits<int16_t>::max();
    int16_t minVal = std::numeric_limits<int16_t>::min();
    int16_t result = safeAverage<int16_t>(maxVal, minVal);
    long long expected = (static_cast<long long>(maxVal) + static_cast<long long>(minVal)) / 2;
    EXPECT_EQ(result, static_cast<int16_t>(expected));
}

// --- uint16_t test ---

TEST(SafeAverageTest_8, AverageOfUint16MaxValues_8) {
    uint16_t maxVal = std::numeric_limits<uint16_t>::max();
    uint16_t result = safeAverage<uint16_t>(maxVal, maxVal);
    EXPECT_EQ(result, maxVal);
}

// --- One and negative one ---

TEST(SafeAverageTest_8, AverageOfOneAndNegativeOne_8) {
    EXPECT_EQ(safeAverage<int>(1, -1), 0);
}

// --- Consecutive integers ---

TEST(SafeAverageTest_8, AverageOfConsecutiveIntegers_8) {
    // Average of consecutive integers truncates to the smaller one
    EXPECT_EQ(safeAverage<int>(5, 6), 5);
    EXPECT_EQ(safeAverage<int>(6, 7), 6);
}

TEST(SafeAverageTest_8, AverageOfNegativeConsecutiveIntegers_8) {
    // (-6 + -5) / 2 = -11 / 2 = -5 (truncation toward zero)
    EXPECT_EQ(safeAverage<int>(-6, -5), -5);
}
