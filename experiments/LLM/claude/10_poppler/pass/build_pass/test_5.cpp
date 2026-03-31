#include <gtest/gtest.h>
#include <limits>
#include <cstdint>
#include "GooCheckedOps.h"

// Test fixture for checkedSubtraction tests
class CheckedSubtractionTest_5 : public ::testing::Test {
protected:
};

// ============================================================
// Tests for int type
// ============================================================

TEST_F(CheckedSubtractionTest_5, IntSubtractionNormalPositiveValues_5) {
    int result = 0;
    bool overflow = checkedSubtraction(10, 3, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 7);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionNormalNegativeResult_5) {
    int result = 0;
    bool overflow = checkedSubtraction(3, 10, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -7);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionBothNegative_5) {
    int result = 0;
    bool overflow = checkedSubtraction(-5, -3, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -2);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionZeroMinusZero_5) {
    int result = 42;
    bool overflow = checkedSubtraction(0, 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionZeroMinusPositive_5) {
    int result = 0;
    bool overflow = checkedSubtraction(0, 5, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -5);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionZeroMinusNegative_5) {
    int result = 0;
    bool overflow = checkedSubtraction(0, -5, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 5);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionMaxMinusZero_5) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::max(), 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::max());
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionMinMinusZero_5) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::min(), 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::min());
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionMaxMinusOne_5) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::max(), 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::max() - 1);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionMinPlusOne_5) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::min(), -1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::min() + 1);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionMaxMinusNegativeOneOverflows_5) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::max(), -1, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionMinMinusOneOverflows_5) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::min(), 1, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionMaxMinusMinOverflows_5) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionMinMinusMaxOverflows_5) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionMaxMinusMax_5) {
    int result = 42;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionMinMinusMin_5) {
    int result = 42;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionLargeNegativeOverflow_5) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), &result);
    EXPECT_TRUE(overflow);
}

// ============================================================
// Tests for short type (smaller integer)
// ============================================================

TEST_F(CheckedSubtractionTest_5, ShortSubtractionNormal_5) {
    short result = 0;
    bool overflow = checkedSubtraction<short>(100, 50, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 50);
}

TEST_F(CheckedSubtractionTest_5, ShortSubtractionMaxMinusNegativeOneOverflows_5) {
    short result = 0;
    bool overflow = checkedSubtraction<short>(std::numeric_limits<short>::max(), static_cast<short>(-1), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_5, ShortSubtractionMinMinusOneOverflows_5) {
    short result = 0;
    bool overflow = checkedSubtraction<short>(std::numeric_limits<short>::min(), static_cast<short>(1), &result);
    EXPECT_TRUE(overflow);
}

// ============================================================
// Tests for long long type
// ============================================================

TEST_F(CheckedSubtractionTest_5, LongLongSubtractionNormal_5) {
    long long result = 0;
    bool overflow = checkedSubtraction<long long>(1000000000LL, 999999999LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 1LL);
}

TEST_F(CheckedSubtractionTest_5, LongLongSubtractionMaxMinusNegativeOneOverflows_5) {
    long long result = 0;
    bool overflow = checkedSubtraction<long long>(std::numeric_limits<long long>::max(), -1LL, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_5, LongLongSubtractionMinMinusOneOverflows_5) {
    long long result = 0;
    bool overflow = checkedSubtraction<long long>(std::numeric_limits<long long>::min(), 1LL, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_5, LongLongSubtractionMaxMinusMax_5) {
    long long result = 42;
    bool overflow = checkedSubtraction<long long>(std::numeric_limits<long long>::max(), std::numeric_limits<long long>::max(), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0LL);
}

TEST_F(CheckedSubtractionTest_5, LongLongSubtractionMinMinusMin_5) {
    long long result = 42;
    bool overflow = checkedSubtraction<long long>(std::numeric_limits<long long>::min(), std::numeric_limits<long long>::min(), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0LL);
}

// ============================================================
// Tests for unsigned int type
// ============================================================

TEST_F(CheckedSubtractionTest_5, UnsignedIntSubtractionNormal_5) {
    unsigned int result = 0;
    bool overflow = checkedSubtraction<unsigned int>(10u, 3u, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 7u);
}

TEST_F(CheckedSubtractionTest_5, UnsignedIntSubtractionZeroMinusOneOverflows_5) {
    unsigned int result = 0;
    bool overflow = checkedSubtraction<unsigned int>(0u, 1u, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_5, UnsignedIntSubtractionSameValue_5) {
    unsigned int result = 42;
    bool overflow = checkedSubtraction<unsigned int>(100u, 100u, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0u);
}

TEST_F(CheckedSubtractionTest_5, UnsignedIntSubtractionMaxMinusMax_5) {
    unsigned int result = 42;
    bool overflow = checkedSubtraction<unsigned int>(std::numeric_limits<unsigned int>::max(), std::numeric_limits<unsigned int>::max(), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0u);
}

TEST_F(CheckedSubtractionTest_5, UnsignedIntSubtractionOneMinusTwoOverflows_5) {
    unsigned int result = 0;
    bool overflow = checkedSubtraction<unsigned int>(1u, 2u, &result);
    EXPECT_TRUE(overflow);
}

// ============================================================
// Additional edge cases for int
// ============================================================

TEST_F(CheckedSubtractionTest_5, IntSubtractionNegativeMinusNegative_5) {
    int result = 0;
    bool overflow = checkedSubtraction(-10, -3, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -7);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionPositiveMinusNegative_5) {
    int result = 0;
    bool overflow = checkedSubtraction(5, -5, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 10);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionNegativeMinusPositive_5) {
    int result = 0;
    bool overflow = checkedSubtraction(-5, 5, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -10);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionMaxMinusNegativeMaxOverflows_5) {
    int result = 0;
    // INT_MAX - (INT_MIN) would overflow
    bool overflow = checkedSubtraction(std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionOneMinusOne_5) {
    int result = 42;
    bool overflow = checkedSubtraction(1, 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(CheckedSubtractionTest_5, IntSubtractionMinPlusMaxNoOverflow_5) {
    int result = 0;
    // INT_MIN - (INT_MIN + 1) = -1, no overflow
    bool overflow = checkedSubtraction(std::numeric_limits<int>::min(), std::numeric_limits<int>::min() + 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -1);
}
