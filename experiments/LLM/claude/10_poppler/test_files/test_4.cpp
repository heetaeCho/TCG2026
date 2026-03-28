#include <gtest/gtest.h>
#include <limits>
#include "GooCheckedOps.h"

// Tests for checkedAdd<long long>

TEST(CheckedAddLongLongTest_4, PositivePlusPositive_4) {
    long long result = 0;
    bool overflow = checkedAdd<long long>(3LL, 5LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 8LL);
}

TEST(CheckedAddLongLongTest_4, NegativePlusNegative_4) {
    long long result = 0;
    bool overflow = checkedAdd<long long>(-3LL, -5LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -8LL);
}

TEST(CheckedAddLongLongTest_4, PositivePlusNegative_4) {
    long long result = 0;
    bool overflow = checkedAdd<long long>(10LL, -3LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 7LL);
}

TEST(CheckedAddLongLongTest_4, NegativePlusPositive_4) {
    long long result = 0;
    bool overflow = checkedAdd<long long>(-10LL, 3LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -7LL);
}

TEST(CheckedAddLongLongTest_4, ZeroPlusZero_4) {
    long long result = 42;
    bool overflow = checkedAdd<long long>(0LL, 0LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0LL);
}

TEST(CheckedAddLongLongTest_4, ZeroPlusPositive_4) {
    long long result = 0;
    bool overflow = checkedAdd<long long>(0LL, 100LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 100LL);
}

TEST(CheckedAddLongLongTest_4, ZeroPlusNegative_4) {
    long long result = 0;
    bool overflow = checkedAdd<long long>(0LL, -100LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -100LL);
}

TEST(CheckedAddLongLongTest_4, PositivePlusZero_4) {
    long long result = 0;
    bool overflow = checkedAdd<long long>(100LL, 0LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 100LL);
}

TEST(CheckedAddLongLongTest_4, NegativePlusZero_4) {
    long long result = 0;
    bool overflow = checkedAdd<long long>(-100LL, 0LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -100LL);
}

TEST(CheckedAddLongLongTest_4, MaxPlusZero_4) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    bool overflow = checkedAdd<long long>(maxVal, 0LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, maxVal);
}

TEST(CheckedAddLongLongTest_4, MinPlusZero_4) {
    long long result = 0;
    long long minVal = std::numeric_limits<long long>::min();
    bool overflow = checkedAdd<long long>(minVal, 0LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, minVal);
}

TEST(CheckedAddLongLongTest_4, OverflowMaxPlusOne_4) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    bool overflow = checkedAdd<long long>(maxVal, 1LL, &result);
    EXPECT_TRUE(overflow);
}

TEST(CheckedAddLongLongTest_4, OverflowMaxPlusMax_4) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    bool overflow = checkedAdd<long long>(maxVal, maxVal, &result);
    EXPECT_TRUE(overflow);
}

TEST(CheckedAddLongLongTest_4, OverflowMinMinusOne_4) {
    long long result = 0;
    long long minVal = std::numeric_limits<long long>::min();
    bool overflow = checkedAdd<long long>(minVal, -1LL, &result);
    EXPECT_TRUE(overflow);
}

TEST(CheckedAddLongLongTest_4, OverflowMinPlusMin_4) {
    long long result = 0;
    long long minVal = std::numeric_limits<long long>::min();
    bool overflow = checkedAdd<long long>(minVal, minVal, &result);
    EXPECT_TRUE(overflow);
}

TEST(CheckedAddLongLongTest_4, BoundaryMaxMinusOnePlusOne_4) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    bool overflow = checkedAdd<long long>(maxVal - 1, 1LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, maxVal);
}

TEST(CheckedAddLongLongTest_4, BoundaryMinPlusOnePlusNegOne_4) {
    long long result = 0;
    long long minVal = std::numeric_limits<long long>::min();
    bool overflow = checkedAdd<long long>(minVal + 1, -1LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, minVal);
}

TEST(CheckedAddLongLongTest_4, MaxPlusMin_4) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    long long minVal = std::numeric_limits<long long>::min();
    bool overflow = checkedAdd<long long>(maxVal, minVal, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, maxVal + minVal);
}

TEST(CheckedAddLongLongTest_4, MinPlusMax_4) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    long long minVal = std::numeric_limits<long long>::min();
    bool overflow = checkedAdd<long long>(minVal, maxVal, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, minVal + maxVal);
}

TEST(CheckedAddLongLongTest_4, LargePositiveOverflow_4) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    long long halfMax = maxVal / 2;
    // halfMax + halfMax + 1 = maxVal, so (halfMax+1) + halfMax should equal maxVal
    bool overflow = checkedAdd<long long>(halfMax + 1, halfMax, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, maxVal);
}

TEST(CheckedAddLongLongTest_4, LargePositiveJustOverflow_4) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    long long halfMax = maxVal / 2;
    // (halfMax + 1) + (halfMax + 1) should overflow
    bool overflow = checkedAdd<long long>(halfMax + 1, halfMax + 1, &result);
    EXPECT_TRUE(overflow);
}

TEST(CheckedAddLongLongTest_4, LargeNegativeOverflow_4) {
    long long result = 0;
    long long minVal = std::numeric_limits<long long>::min();
    long long halfMin = minVal / 2;
    // halfMin + halfMin should be close to minVal (exact depends on rounding)
    bool overflow = checkedAdd<long long>(halfMin, halfMin, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, halfMin + halfMin);
}

TEST(CheckedAddLongLongTest_4, LargeNegativeJustOverflow_4) {
    long long result = 0;
    long long minVal = std::numeric_limits<long long>::min();
    long long halfMin = minVal / 2;
    // (halfMin - 1) + halfMin should overflow
    bool overflow = checkedAdd<long long>(halfMin - 1, halfMin, &result);
    EXPECT_TRUE(overflow);
}

TEST(CheckedAddLongLongTest_4, PositiveAndNegativeCancellation_4) {
    long long result = 0;
    bool overflow = checkedAdd<long long>(1000000LL, -1000000LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0LL);
}

TEST(CheckedAddLongLongTest_4, OnePlusOne_4) {
    long long result = 0;
    bool overflow = checkedAdd<long long>(1LL, 1LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 2LL);
}

TEST(CheckedAddLongLongTest_4, NegOnePlusNegOne_4) {
    long long result = 0;
    bool overflow = checkedAdd<long long>(-1LL, -1LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -2LL);
}

TEST(CheckedAddLongLongTest_4, MaxPlusNegOne_4) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    bool overflow = checkedAdd<long long>(maxVal, -1LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, maxVal - 1);
}

TEST(CheckedAddLongLongTest_4, MinPlusOne_4) {
    long long result = 0;
    long long minVal = std::numeric_limits<long long>::min();
    bool overflow = checkedAdd<long long>(minVal, 1LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, minVal + 1);
}

TEST(CheckedAddLongLongTest_4, OverflowLargePositives_4) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    bool overflow = checkedAdd<long long>(maxVal, 2LL, &result);
    EXPECT_TRUE(overflow);
}

TEST(CheckedAddLongLongTest_4, OverflowLargeNegatives_4) {
    long long result = 0;
    long long minVal = std::numeric_limits<long long>::min();
    bool overflow = checkedAdd<long long>(minVal, -2LL, &result);
    EXPECT_TRUE(overflow);
}
