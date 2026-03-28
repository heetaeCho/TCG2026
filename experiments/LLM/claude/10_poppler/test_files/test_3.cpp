#include <gtest/gtest.h>
#include <limits>
#include <cstdint>
#include "GooCheckedOps.h"

// Test normal addition of two positive integers
TEST(CheckedAddTest_3, TwoPositiveInts_3) {
    int z = 0;
    bool overflow = checkedAdd(3, 4, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 7);
}

// Test normal addition of two negative integers
TEST(CheckedAddTest_3, TwoNegativeInts_3) {
    int z = 0;
    bool overflow = checkedAdd(-3, -4, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, -7);
}

// Test addition of positive and negative that results in zero
TEST(CheckedAddTest_3, PositiveAndNegativeResultZero_3) {
    int z = 99;
    bool overflow = checkedAdd(5, -5, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 0);
}

// Test addition with zero
TEST(CheckedAddTest_3, AddZeroToPositive_3) {
    int z = 0;
    bool overflow = checkedAdd(42, 0, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 42);
}

TEST(CheckedAddTest_3, AddZeroToNegative_3) {
    int z = 0;
    bool overflow = checkedAdd(-42, 0, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, -42);
}

TEST(CheckedAddTest_3, AddZeroToZero_3) {
    int z = 99;
    bool overflow = checkedAdd(0, 0, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 0);
}

// Test overflow with int: MAX + 1
TEST(CheckedAddTest_3, IntOverflowMaxPlusOne_3) {
    int z = 0;
    bool overflow = checkedAdd(std::numeric_limits<int>::max(), 1, &z);
    EXPECT_TRUE(overflow);
}

// Test overflow with int: MAX + MAX
TEST(CheckedAddTest_3, IntOverflowMaxPlusMax_3) {
    int z = 0;
    bool overflow = checkedAdd(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), &z);
    EXPECT_TRUE(overflow);
}

// Test underflow with int: MIN + (-1)
TEST(CheckedAddTest_3, IntUnderflowMinMinusOne_3) {
    int z = 0;
    bool overflow = checkedAdd(std::numeric_limits<int>::min(), -1, &z);
    EXPECT_TRUE(overflow);
}

// Test underflow with int: MIN + MIN
TEST(CheckedAddTest_3, IntUnderflowMinPlusMin_3) {
    int z = 0;
    bool overflow = checkedAdd(std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), &z);
    EXPECT_TRUE(overflow);
}

// Test boundary: MAX + 0 (no overflow)
TEST(CheckedAddTest_3, IntMaxPlusZero_3) {
    int z = 0;
    bool overflow = checkedAdd(std::numeric_limits<int>::max(), 0, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, std::numeric_limits<int>::max());
}

// Test boundary: MIN + 0 (no overflow)
TEST(CheckedAddTest_3, IntMinPlusZero_3) {
    int z = 0;
    bool overflow = checkedAdd(std::numeric_limits<int>::min(), 0, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, std::numeric_limits<int>::min());
}

// Test boundary: MAX + (-1) (no overflow, result is MAX-1)
TEST(CheckedAddTest_3, IntMaxPlusNegOne_3) {
    int z = 0;
    bool overflow = checkedAdd(std::numeric_limits<int>::max(), -1, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, std::numeric_limits<int>::max() - 1);
}

// Test boundary: MIN + 1 (no overflow, result is MIN+1)
TEST(CheckedAddTest_3, IntMinPlusOne_3) {
    int z = 0;
    bool overflow = checkedAdd(std::numeric_limits<int>::min(), 1, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, std::numeric_limits<int>::min() + 1);
}

// Test with short type: normal addition
TEST(CheckedAddTest_3, ShortNormalAdd_3) {
    short z = 0;
    bool overflow = checkedAdd<short>(10, 20, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 30);
}

// Test with short type: overflow
TEST(CheckedAddTest_3, ShortOverflow_3) {
    short z = 0;
    bool overflow = checkedAdd<short>(std::numeric_limits<short>::max(), static_cast<short>(1), &z);
    EXPECT_TRUE(overflow);
}

// Test with short type: underflow
TEST(CheckedAddTest_3, ShortUnderflow_3) {
    short z = 0;
    bool overflow = checkedAdd<short>(std::numeric_limits<short>::min(), static_cast<short>(-1), &z);
    EXPECT_TRUE(overflow);
}

// Test with long long type: normal addition
TEST(CheckedAddTest_3, LongLongNormalAdd_3) {
    long long z = 0;
    bool overflow = checkedAdd<long long>(100LL, 200LL, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 300LL);
}

// Test with long long type: overflow
TEST(CheckedAddTest_3, LongLongOverflow_3) {
    long long z = 0;
    bool overflow = checkedAdd<long long>(std::numeric_limits<long long>::max(), 1LL, &z);
    EXPECT_TRUE(overflow);
}

// Test with long long type: underflow
TEST(CheckedAddTest_3, LongLongUnderflow_3) {
    long long z = 0;
    bool overflow = checkedAdd<long long>(std::numeric_limits<long long>::min(), -1LL, &z);
    EXPECT_TRUE(overflow);
}

// Test positive and negative that do not overflow
TEST(CheckedAddTest_3, LargePositiveAndLargeNegativeNoOverflow_3) {
    int z = 0;
    bool overflow = checkedAdd(std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, -1);
}

// Test with unsigned int: normal
TEST(CheckedAddTest_3, UnsignedIntNormal_3) {
    unsigned int z = 0;
    bool overflow = checkedAdd<unsigned int>(10u, 20u, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 30u);
}

// Test with unsigned int: overflow
TEST(CheckedAddTest_3, UnsignedIntOverflow_3) {
    unsigned int z = 0;
    bool overflow = checkedAdd<unsigned int>(std::numeric_limits<unsigned int>::max(), 1u, &z);
    EXPECT_TRUE(overflow);
}

// Test with int16_t
TEST(CheckedAddTest_3, Int16Normal_3) {
    int16_t z = 0;
    bool overflow = checkedAdd<int16_t>(100, 200, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 300);
}

TEST(CheckedAddTest_3, Int16Overflow_3) {
    int16_t z = 0;
    bool overflow = checkedAdd<int16_t>(std::numeric_limits<int16_t>::max(), static_cast<int16_t>(1), &z);
    EXPECT_TRUE(overflow);
}

// Test with int: large positive values that just fit
TEST(CheckedAddTest_3, IntJustBelowOverflow_3) {
    int z = 0;
    int half = std::numeric_limits<int>::max() / 2;
    bool overflow = checkedAdd(half, half, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, half + half);
}
