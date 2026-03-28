#include <gtest/gtest.h>
#include <climits>
#include <cstdint>

// Include the header under test
#include "GooCheckedOps.h"

// ============================================================================
// Tests for checkedMultiply
// ============================================================================

// --- Normal operation tests ---

TEST(CheckedMultiplyTest_1843, ZeroTimesZero_1843) {
    int result = -1;
    bool overflow = checkedMultiply(0, 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST(CheckedMultiplyTest_1843, ZeroTimesPositive_1843) {
    int result = -1;
    bool overflow = checkedMultiply(0, 42, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST(CheckedMultiplyTest_1843, PositiveTimesZero_1843) {
    int result = -1;
    bool overflow = checkedMultiply(42, 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST(CheckedMultiplyTest_1843, OneTimesValue_1843) {
    int result = 0;
    bool overflow = checkedMultiply(1, 123, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 123);
}

TEST(CheckedMultiplyTest_1843, ValueTimesOne_1843) {
    int result = 0;
    bool overflow = checkedMultiply(123, 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 123);
}

TEST(CheckedMultiplyTest_1843, SmallPositiveMultiplication_1843) {
    int result = 0;
    bool overflow = checkedMultiply(3, 7, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 21);
}

TEST(CheckedMultiplyTest_1843, NegativeTimesPositive_1843) {
    int result = 0;
    bool overflow = checkedMultiply(-3, 7, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -21);
}

TEST(CheckedMultiplyTest_1843, NegativeTimesNegative_1843) {
    int result = 0;
    bool overflow = checkedMultiply(-3, -7, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 21);
}

TEST(CheckedMultiplyTest_1843, PositiveTimesNegative_1843) {
    int result = 0;
    bool overflow = checkedMultiply(5, -4, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -20);
}

// --- Boundary condition tests ---

TEST(CheckedMultiplyTest_1843, MaxIntTimesOne_1843) {
    int result = 0;
    bool overflow = checkedMultiply(INT_MAX, 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, INT_MAX);
}

TEST(CheckedMultiplyTest_1843, MinIntTimesOne_1843) {
    int result = 0;
    bool overflow = checkedMultiply(INT_MIN, 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, INT_MIN);
}

TEST(CheckedMultiplyTest_1843, MaxIntTimesZero_1843) {
    int result = -1;
    bool overflow = checkedMultiply(INT_MAX, 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST(CheckedMultiplyTest_1843, MinIntTimesZero_1843) {
    int result = -1;
    bool overflow = checkedMultiply(INT_MIN, 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

// --- Overflow / error case tests ---

TEST(CheckedMultiplyTest_1843, OverflowMaxIntTimesTwo_1843) {
    int result = 0;
    bool overflow = checkedMultiply(INT_MAX, 2, &result);
    EXPECT_TRUE(overflow);
}

TEST(CheckedMultiplyTest_1843, OverflowMinIntTimesTwo_1843) {
    int result = 0;
    bool overflow = checkedMultiply(INT_MIN, 2, &result);
    EXPECT_TRUE(overflow);
}

TEST(CheckedMultiplyTest_1843, OverflowMaxIntTimesMaxInt_1843) {
    int result = 0;
    bool overflow = checkedMultiply(INT_MAX, INT_MAX, &result);
    EXPECT_TRUE(overflow);
}

TEST(CheckedMultiplyTest_1843, OverflowMinIntTimesMinInt_1843) {
    int result = 0;
    bool overflow = checkedMultiply(INT_MIN, INT_MIN, &result);
    EXPECT_TRUE(overflow);
}

TEST(CheckedMultiplyTest_1843, OverflowMinIntTimesNegativeOne_1843) {
    int result = 0;
    bool overflow = checkedMultiply(INT_MIN, -1, &result);
    // INT_MIN * -1 = INT_MAX + 1 which overflows for int
    EXPECT_TRUE(overflow);
}

TEST(CheckedMultiplyTest_1843, NoOverflowNegativeOneTimesMaxInt_1843) {
    int result = 0;
    bool overflow = checkedMultiply(-1, INT_MAX, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -INT_MAX);
}

TEST(CheckedMultiplyTest_1843, OverflowLargePositives_1843) {
    int result = 0;
    bool overflow = checkedMultiply(100000, 100000, &result);
    // 100000 * 100000 = 10^10, which overflows int32
    EXPECT_TRUE(overflow);
}

TEST(CheckedMultiplyTest_1843, NoOverflowModerateValues_1843) {
    int result = 0;
    bool overflow = checkedMultiply(1000, 1000, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 1000000);
}

// --- Tests with different integer types ---

TEST(CheckedMultiplyTest_1843, ShortOverflow_1843) {
    short result = 0;
    bool overflow = checkedMultiply<short>(200, 200, &result);
    // 200 * 200 = 40000, which overflows short (max 32767)
    EXPECT_TRUE(overflow);
}

TEST(CheckedMultiplyTest_1843, ShortNoOverflow_1843) {
    short result = 0;
    bool overflow = checkedMultiply<short>(100, 100, &result);
    // 100 * 100 = 10000, fits in short
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 10000);
}

TEST(CheckedMultiplyTest_1843, LongLongNoOverflow_1843) {
    long long result = 0;
    bool overflow = checkedMultiply<long long>(100000LL, 100000LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 10000000000LL);
}

TEST(CheckedMultiplyTest_1843, UnsignedIntNoOverflow_1843) {
    unsigned int result = 0;
    bool overflow = checkedMultiply<unsigned int>(50000u, 50000u, &result);
    // 50000 * 50000 = 2,500,000,000 which fits in uint32 (max ~4.29 billion)
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 2500000000u);
}

TEST(CheckedMultiplyTest_1843, UnsignedIntOverflow_1843) {
    unsigned int result = 0;
    bool overflow = checkedMultiply<unsigned int>(UINT_MAX, 2u, &result);
    EXPECT_TRUE(overflow);
}

TEST(CheckedMultiplyTest_1843, NegativeOneTimesOne_1843) {
    int result = 0;
    bool overflow = checkedMultiply(-1, 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -1);
}

TEST(CheckedMultiplyTest_1843, NegativeOneTimesNegativeOne_1843) {
    int result = 0;
    bool overflow = checkedMultiply(-1, -1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 1);
}

TEST(CheckedMultiplyTest_1843, JustBelowOverflowThreshold_1843) {
    int result = 0;
    // INT_MAX = 2147483647, 46340^2 = 2147395600 which fits
    bool overflow = checkedMultiply(46340, 46340, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 46340 * 46340);
}

TEST(CheckedMultiplyTest_1843, JustAboveOverflowThreshold_1843) {
    int result = 0;
    // 46341^2 = 2147488281 which overflows int32
    bool overflow = checkedMultiply(46341, 46341, &result);
    EXPECT_TRUE(overflow);
}
