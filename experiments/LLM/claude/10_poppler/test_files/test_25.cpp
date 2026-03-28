#include <gtest/gtest.h>
#include <climits>
#include <cstdint>

// Include the header under test
#include "GooCheckedOps.h"

// ============================================================
// Tests for checkedMultiply
// ============================================================

class CheckedMultiplyTest_25 : public ::testing::Test {
protected:
};

// --- Normal operation tests ---

TEST_F(CheckedMultiplyTest_25, MultiplyTwoPositiveInts_25) {
    int z = 0;
    bool overflow = checkedMultiply(3, 4, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 12);
}

TEST_F(CheckedMultiplyTest_25, MultiplyPositiveAndNegativeInt_25) {
    int z = 0;
    bool overflow = checkedMultiply(3, -4, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, -12);
}

TEST_F(CheckedMultiplyTest_25, MultiplyTwoNegativeInts_25) {
    int z = 0;
    bool overflow = checkedMultiply(-3, -4, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 12);
}

TEST_F(CheckedMultiplyTest_25, MultiplyByZero_25) {
    int z = 42;
    bool overflow = checkedMultiply(0, 12345, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 0);
}

TEST_F(CheckedMultiplyTest_25, MultiplyZeroByZero_25) {
    int z = 42;
    bool overflow = checkedMultiply(0, 0, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 0);
}

TEST_F(CheckedMultiplyTest_25, MultiplyByOne_25) {
    int z = 0;
    bool overflow = checkedMultiply(1, INT_MAX, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, INT_MAX);
}

TEST_F(CheckedMultiplyTest_25, MultiplyByNegativeOne_25) {
    int z = 0;
    bool overflow = checkedMultiply(-1, INT_MAX, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, -INT_MAX);
}

// --- Boundary conditions ---

TEST_F(CheckedMultiplyTest_25, IntMaxTimesOne_25) {
    int z = 0;
    bool overflow = checkedMultiply(INT_MAX, 1, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, INT_MAX);
}

TEST_F(CheckedMultiplyTest_25, IntMinTimesOne_25) {
    int z = 0;
    bool overflow = checkedMultiply(INT_MIN, 1, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, INT_MIN);
}

TEST_F(CheckedMultiplyTest_25, IntMaxTimesZero_25) {
    int z = 99;
    bool overflow = checkedMultiply(INT_MAX, 0, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 0);
}

TEST_F(CheckedMultiplyTest_25, IntMinTimesZero_25) {
    int z = 99;
    bool overflow = checkedMultiply(INT_MIN, 0, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 0);
}

// --- Overflow tests ---

TEST_F(CheckedMultiplyTest_25, OverflowIntMaxTimesTwo_25) {
    int z = 0;
    bool overflow = checkedMultiply(INT_MAX, 2, &z);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_25, OverflowIntMinTimesTwo_25) {
    int z = 0;
    bool overflow = checkedMultiply(INT_MIN, 2, &z);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_25, OverflowIntMaxTimesIntMax_25) {
    int z = 0;
    bool overflow = checkedMultiply(INT_MAX, INT_MAX, &z);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_25, OverflowIntMinTimesIntMin_25) {
    int z = 0;
    bool overflow = checkedMultiply(INT_MIN, INT_MIN, &z);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_25, OverflowIntMinTimesNegativeOne_25) {
    int z = 0;
    bool overflow = checkedMultiply(INT_MIN, -1, &z);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_25, OverflowLargePositives_25) {
    int z = 0;
    // 50000 * 50000 = 2,500,000,000 which overflows 32-bit int
    bool overflow = checkedMultiply(50000, 50000, &z);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_25, OverflowLargeNegatives_25) {
    int z = 0;
    // -50000 * 50000 = -2,500,000,000 which underflows 32-bit int
    bool overflow = checkedMultiply(-50000, 50000, &z);
    EXPECT_TRUE(overflow);
}

// --- Edge case: just at the boundary ---

TEST_F(CheckedMultiplyTest_25, NoOverflowJustBelowMax_25) {
    int z = 0;
    // INT_MAX = 2147483647
    // 46340 * 46340 = 2147395600, which fits in int
    bool overflow = checkedMultiply(46340, 46340, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 46340 * 46340);
}

TEST_F(CheckedMultiplyTest_25, OverflowJustAboveMax_25) {
    int z = 0;
    // 46341 * 46341 = 2147488281 which overflows int
    bool overflow = checkedMultiply(46341, 46341, &z);
    EXPECT_TRUE(overflow);
}

// --- Tests with short type ---

TEST_F(CheckedMultiplyTest_25, ShortMultiplyNoOverflow_25) {
    short z = 0;
    bool overflow = checkedMultiply<short>(10, 20, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 200);
}

TEST_F(CheckedMultiplyTest_25, ShortMultiplyOverflow_25) {
    short z = 0;
    bool overflow = checkedMultiply<short>(SHRT_MAX, static_cast<short>(2), &z);
    EXPECT_TRUE(overflow);
}

// --- Tests with long long type ---

TEST_F(CheckedMultiplyTest_25, LongLongMultiplyNoOverflow_25) {
    long long z = 0;
    bool overflow = checkedMultiply<long long>(1000000LL, 1000000LL, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 1000000000000LL);
}

TEST_F(CheckedMultiplyTest_25, LongLongMultiplyOverflow_25) {
    long long z = 0;
    bool overflow = checkedMultiply<long long>(LLONG_MAX, 2LL, &z);
    EXPECT_TRUE(overflow);
}

// --- Tests with unsigned int ---

TEST_F(CheckedMultiplyTest_25, UnsignedIntMultiplyNoOverflow_25) {
    unsigned int z = 0;
    bool overflow = checkedMultiply<unsigned int>(100u, 200u, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 20000u);
}

TEST_F(CheckedMultiplyTest_25, UnsignedIntMultiplyOverflow_25) {
    unsigned int z = 0;
    bool overflow = checkedMultiply<unsigned int>(UINT_MAX, 2u, &z);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_25, UnsignedIntMultiplyByZero_25) {
    unsigned int z = 99;
    bool overflow = checkedMultiply<unsigned int>(UINT_MAX, 0u, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 0u);
}
