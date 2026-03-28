#include <gtest/gtest.h>
#include <limits>
#include <climits>

// Include the header under test
#include "GooCheckedOps.h"

// ============================================================
// Tests for checkedAdd with int type
// ============================================================

class CheckedAddIntTest_1842 : public ::testing::Test {
protected:
    int result;
};

TEST_F(CheckedAddIntTest_1842, AddTwoPositiveNumbers_1842)
{
    bool overflow = checkedAdd<int>(3, 4, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 7);
}

TEST_F(CheckedAddIntTest_1842, AddTwoNegativeNumbers_1842)
{
    bool overflow = checkedAdd<int>(-3, -4, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -7);
}

TEST_F(CheckedAddIntTest_1842, AddPositiveAndNegative_1842)
{
    bool overflow = checkedAdd<int>(10, -3, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 7);
}

TEST_F(CheckedAddIntTest_1842, AddZeros_1842)
{
    bool overflow = checkedAdd<int>(0, 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(CheckedAddIntTest_1842, AddZeroToPositive_1842)
{
    bool overflow = checkedAdd<int>(0, 42, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 42);
}

TEST_F(CheckedAddIntTest_1842, AddZeroToNegative_1842)
{
    bool overflow = checkedAdd<int>(0, -42, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -42);
}

TEST_F(CheckedAddIntTest_1842, OverflowIntMaxPlusOne_1842)
{
    bool overflow = checkedAdd<int>(INT_MAX, 1, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddIntTest_1842, OverflowIntMaxPlusIntMax_1842)
{
    bool overflow = checkedAdd<int>(INT_MAX, INT_MAX, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddIntTest_1842, UnderflowIntMinMinusOne_1842)
{
    bool overflow = checkedAdd<int>(INT_MIN, -1, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddIntTest_1842, UnderflowIntMinPlusIntMin_1842)
{
    bool overflow = checkedAdd<int>(INT_MIN, INT_MIN, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddIntTest_1842, IntMaxPlusZero_1842)
{
    bool overflow = checkedAdd<int>(INT_MAX, 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, INT_MAX);
}

TEST_F(CheckedAddIntTest_1842, IntMinPlusZero_1842)
{
    bool overflow = checkedAdd<int>(INT_MIN, 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, INT_MIN);
}

TEST_F(CheckedAddIntTest_1842, IntMaxPlusNegativeOne_1842)
{
    bool overflow = checkedAdd<int>(INT_MAX, -1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, INT_MAX - 1);
}

TEST_F(CheckedAddIntTest_1842, IntMinPlusOne_1842)
{
    bool overflow = checkedAdd<int>(INT_MIN, 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, INT_MIN + 1);
}

TEST_F(CheckedAddIntTest_1842, IntMaxPlusIntMin_1842)
{
    bool overflow = checkedAdd<int>(INT_MAX, INT_MIN, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -1);
}

TEST_F(CheckedAddIntTest_1842, LargePositiveNumbers_1842)
{
    // INT_MAX / 2 + INT_MAX / 2 should not overflow
    int half = INT_MAX / 2;
    bool overflow = checkedAdd<int>(half, half, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, half + half);
}

TEST_F(CheckedAddIntTest_1842, BoundaryOverflowByOne_1842)
{
    // INT_MAX - 5 + 6 = INT_MAX + 1 => overflow
    bool overflow = checkedAdd<int>(INT_MAX - 5, 6, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddIntTest_1842, BoundaryNoOverflowByOne_1842)
{
    // INT_MAX - 5 + 5 = INT_MAX => no overflow
    bool overflow = checkedAdd<int>(INT_MAX - 5, 5, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, INT_MAX);
}

TEST_F(CheckedAddIntTest_1842, BoundaryUnderflowByOne_1842)
{
    // INT_MIN + 5 + (-6) = INT_MIN - 1 => underflow
    bool overflow = checkedAdd<int>(INT_MIN + 5, -6, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddIntTest_1842, BoundaryNoUnderflowByOne_1842)
{
    // INT_MIN + 5 + (-5) = INT_MIN => no underflow
    bool overflow = checkedAdd<int>(INT_MIN + 5, -5, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, INT_MIN);
}

// ============================================================
// Tests for checkedAdd with short type (if supported)
// ============================================================

class CheckedAddShortTest_1842 : public ::testing::Test {
protected:
    short result;
};

TEST_F(CheckedAddShortTest_1842, AddTwoSmallPositives_1842)
{
    bool overflow = checkedAdd<short>(static_cast<short>(3), static_cast<short>(4), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 7);
}

TEST_F(CheckedAddShortTest_1842, OverflowShortMax_1842)
{
    bool overflow = checkedAdd<short>(SHRT_MAX, static_cast<short>(1), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddShortTest_1842, UnderflowShortMin_1842)
{
    bool overflow = checkedAdd<short>(SHRT_MIN, static_cast<short>(-1), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddShortTest_1842, NoOverflowShortMaxPlusZero_1842)
{
    bool overflow = checkedAdd<short>(SHRT_MAX, static_cast<short>(0), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, SHRT_MAX);
}

// ============================================================
// Tests for checkedAdd with long type
// ============================================================

class CheckedAddLongTest_1842 : public ::testing::Test {
protected:
    long result;
};

TEST_F(CheckedAddLongTest_1842, AddTwoPositiveNumbers_1842)
{
    bool overflow = checkedAdd<long>(100L, 200L, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 300L);
}

TEST_F(CheckedAddLongTest_1842, AddNegativeNumbers_1842)
{
    bool overflow = checkedAdd<long>(-100L, -200L, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -300L);
}

// ============================================================
// Tests for checkedAdd with unsigned int type (if applicable)
// Note: The template may or may not work for unsigned types
// depending on checkedAssign implementation. These tests
// verify observable behavior.
// ============================================================

class CheckedAddUnsignedTest_1842 : public ::testing::Test {
protected:
    unsigned int result;
};

TEST_F(CheckedAddUnsignedTest_1842, AddTwoSmallUnsigned_1842)
{
    bool overflow = checkedAdd<unsigned int>(3u, 4u, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 7u);
}

TEST_F(CheckedAddUnsignedTest_1842, OverflowUnsignedMax_1842)
{
    bool overflow = checkedAdd<unsigned int>(UINT_MAX, 1u, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddUnsignedTest_1842, NoOverflowUnsignedMaxPlusZero_1842)
{
    bool overflow = checkedAdd<unsigned int>(UINT_MAX, 0u, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, UINT_MAX);
}

// ============================================================
// Commutativity tests
// ============================================================

TEST(CheckedAddCommutativityTest_1842, CommutativePositive_1842)
{
    int r1, r2;
    bool o1 = checkedAdd<int>(3, 7, &r1);
    bool o2 = checkedAdd<int>(7, 3, &r2);
    EXPECT_EQ(o1, o2);
    EXPECT_EQ(r1, r2);
}

TEST(CheckedAddCommutativityTest_1842, CommutativeOverflow_1842)
{
    int r1, r2;
    bool o1 = checkedAdd<int>(INT_MAX, 1, &r1);
    bool o2 = checkedAdd<int>(1, INT_MAX, &r2);
    EXPECT_EQ(o1, o2);
    EXPECT_TRUE(o1);
}

TEST(CheckedAddCommutativityTest_1842, CommutativeMixed_1842)
{
    int r1, r2;
    bool o1 = checkedAdd<int>(100, -50, &r1);
    bool o2 = checkedAdd<int>(-50, 100, &r2);
    EXPECT_EQ(o1, o2);
    EXPECT_EQ(r1, r2);
    EXPECT_EQ(r1, 50);
}
