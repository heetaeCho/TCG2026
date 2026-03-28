#include <gtest/gtest.h>
#include <limits>
#include <cstdint>

// Include the header under test
#include "GooCheckedOps.h"

// ============================================================
// Tests for checkedAdd with int type
// ============================================================

class CheckedAddIntTest_53 : public ::testing::Test {
protected:
    int result;
};

TEST_F(CheckedAddIntTest_53, AddTwoPositiveNumbers_53) {
    bool overflow = checkedAdd<int>(3, 4, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 7);
}

TEST_F(CheckedAddIntTest_53, AddTwoNegativeNumbers_53) {
    bool overflow = checkedAdd<int>(-3, -4, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -7);
}

TEST_F(CheckedAddIntTest_53, AddPositiveAndNegative_53) {
    bool overflow = checkedAdd<int>(10, -3, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 7);
}

TEST_F(CheckedAddIntTest_53, AddZeroAndZero_53) {
    bool overflow = checkedAdd<int>(0, 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(CheckedAddIntTest_53, AddZeroAndPositive_53) {
    bool overflow = checkedAdd<int>(0, 42, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 42);
}

TEST_F(CheckedAddIntTest_53, AddZeroAndNegative_53) {
    bool overflow = checkedAdd<int>(0, -42, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -42);
}

TEST_F(CheckedAddIntTest_53, AddMaxIntAndZero_53) {
    bool overflow = checkedAdd<int>(std::numeric_limits<int>::max(), 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::max());
}

TEST_F(CheckedAddIntTest_53, AddMinIntAndZero_53) {
    bool overflow = checkedAdd<int>(std::numeric_limits<int>::min(), 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::min());
}

TEST_F(CheckedAddIntTest_53, OverflowMaxIntPlusOne_53) {
    bool overflow = checkedAdd<int>(std::numeric_limits<int>::max(), 1, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddIntTest_53, OverflowMaxIntPlusMaxInt_53) {
    bool overflow = checkedAdd<int>(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddIntTest_53, UnderflowMinIntMinusOne_53) {
    bool overflow = checkedAdd<int>(std::numeric_limits<int>::min(), -1, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddIntTest_53, UnderflowMinIntPlusMinInt_53) {
    bool overflow = checkedAdd<int>(std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddIntTest_53, MaxIntPlusMinIntNoOverflow_53) {
    bool overflow = checkedAdd<int>(std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -1);
}

TEST_F(CheckedAddIntTest_53, NearMaxBoundaryNoOverflow_53) {
    bool overflow = checkedAdd<int>(std::numeric_limits<int>::max() - 1, 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::max());
}

TEST_F(CheckedAddIntTest_53, NearMinBoundaryNoUnderflow_53) {
    bool overflow = checkedAdd<int>(std::numeric_limits<int>::min() + 1, -1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::min());
}

// ============================================================
// Tests for checkedAdd with short type
// ============================================================

class CheckedAddShortTest_53 : public ::testing::Test {
protected:
    short result;
};

TEST_F(CheckedAddShortTest_53, AddTwoSmallPositives_53) {
    bool overflow = checkedAdd<short>(10, 20, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 30);
}

TEST_F(CheckedAddShortTest_53, OverflowMaxShortPlusOne_53) {
    bool overflow = checkedAdd<short>(std::numeric_limits<short>::max(), static_cast<short>(1), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddShortTest_53, UnderflowMinShortMinusOne_53) {
    bool overflow = checkedAdd<short>(std::numeric_limits<short>::min(), static_cast<short>(-1), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddShortTest_53, MaxShortPlusZero_53) {
    bool overflow = checkedAdd<short>(std::numeric_limits<short>::max(), static_cast<short>(0), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<short>::max());
}

// ============================================================
// Tests for checkedAdd with long long type
// ============================================================

class CheckedAddLongLongTest_53 : public ::testing::Test {
protected:
    long long result;
};

TEST_F(CheckedAddLongLongTest_53, AddTwoPositives_53) {
    bool overflow = checkedAdd<long long>(100LL, 200LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 300LL);
}

TEST_F(CheckedAddLongLongTest_53, OverflowMaxLongLongPlusOne_53) {
    bool overflow = checkedAdd<long long>(std::numeric_limits<long long>::max(), 1LL, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddLongLongTest_53, UnderflowMinLongLongMinusOne_53) {
    bool overflow = checkedAdd<long long>(std::numeric_limits<long long>::min(), -1LL, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddLongLongTest_53, MaxLongLongPlusZero_53) {
    bool overflow = checkedAdd<long long>(std::numeric_limits<long long>::max(), 0LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<long long>::max());
}

TEST_F(CheckedAddLongLongTest_53, MaxLongLongPlusMinLongLong_53) {
    bool overflow = checkedAdd<long long>(std::numeric_limits<long long>::max(), std::numeric_limits<long long>::min(), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -1LL);
}

// ============================================================
// Tests for checkedAdd with unsigned int type (if applicable)
// ============================================================

class CheckedAddUnsignedTest_53 : public ::testing::Test {
protected:
    unsigned int result;
};

TEST_F(CheckedAddUnsignedTest_53, AddTwoSmallPositives_53) {
    bool overflow = checkedAdd<unsigned int>(5u, 10u, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 15u);
}

TEST_F(CheckedAddUnsignedTest_53, AddZeroAndZero_53) {
    bool overflow = checkedAdd<unsigned int>(0u, 0u, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0u);
}

TEST_F(CheckedAddUnsignedTest_53, OverflowMaxUintPlusOne_53) {
    bool overflow = checkedAdd<unsigned int>(std::numeric_limits<unsigned int>::max(), 1u, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddUnsignedTest_53, MaxUintPlusZero_53) {
    bool overflow = checkedAdd<unsigned int>(std::numeric_limits<unsigned int>::max(), 0u, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<unsigned int>::max());
}

TEST_F(CheckedAddUnsignedTest_53, OverflowMaxUintPlusMaxUint_53) {
    bool overflow = checkedAdd<unsigned int>(std::numeric_limits<unsigned int>::max(), std::numeric_limits<unsigned int>::max(), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddUnsignedTest_53, NearMaxBoundaryNoOverflow_53) {
    bool overflow = checkedAdd<unsigned int>(std::numeric_limits<unsigned int>::max() - 1u, 1u, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<unsigned int>::max());
}

// ============================================================
// Tests for checkedAdd with int32_t
// ============================================================

class CheckedAddInt32Test_53 : public ::testing::Test {
protected:
    int32_t result;
};

TEST_F(CheckedAddInt32Test_53, SimpleAddition_53) {
    bool overflow = checkedAdd<int32_t>(1000, 2000, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 3000);
}

TEST_F(CheckedAddInt32Test_53, OverflowInt32Max_53) {
    bool overflow = checkedAdd<int32_t>(std::numeric_limits<int32_t>::max(), 1, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddInt32Test_53, UnderflowInt32Min_53) {
    bool overflow = checkedAdd<int32_t>(std::numeric_limits<int32_t>::min(), -1, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddInt32Test_53, LargePositiveAndLargeNegative_53) {
    bool overflow = checkedAdd<int32_t>(std::numeric_limits<int32_t>::max(), std::numeric_limits<int32_t>::min(), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -1);
}

TEST_F(CheckedAddInt32Test_53, AddNegativeOneAndOne_53) {
    bool overflow = checkedAdd<int32_t>(-1, 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}
