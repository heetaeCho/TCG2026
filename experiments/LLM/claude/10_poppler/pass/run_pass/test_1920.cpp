#include <gtest/gtest.h>
#include <limits>
#include <cstdint>

#include "GooCheckedOps.h"

// Test fixture for checkedSubtraction tests
class CheckedSubtractionTest_1920 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== int tests ====================

TEST_F(CheckedSubtractionTest_1920, IntNormalSubtraction_1920) {
    int result = 0;
    bool overflow = checkedSubtraction(10, 3, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 7);
}

TEST_F(CheckedSubtractionTest_1920, IntSubtractionResultZero_1920) {
    int result = -1;
    bool overflow = checkedSubtraction(5, 5, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(CheckedSubtractionTest_1920, IntSubtractionNegativeResult_1920) {
    int result = 0;
    bool overflow = checkedSubtraction(3, 10, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -7);
}

TEST_F(CheckedSubtractionTest_1920, IntSubtractionBothNegative_1920) {
    int result = 0;
    bool overflow = checkedSubtraction(-3, -10, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 7);
}

TEST_F(CheckedSubtractionTest_1920, IntSubtractionZeroMinusZero_1920) {
    int result = -1;
    bool overflow = checkedSubtraction(0, 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(CheckedSubtractionTest_1920, IntSubtractionZeroMinusPositive_1920) {
    int result = 0;
    bool overflow = checkedSubtraction(0, 42, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -42);
}

TEST_F(CheckedSubtractionTest_1920, IntSubtractionZeroMinusNegative_1920) {
    int result = 0;
    bool overflow = checkedSubtraction(0, -42, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 42);
}

TEST_F(CheckedSubtractionTest_1920, IntOverflowMaxMinusNegativeOne_1920) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::max(), -1, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_1920, IntOverflowMinMinusOne_1920) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::min(), 1, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_1920, IntOverflowMinMinusMax_1920) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_1920, IntNoOverflowMaxMinusZero_1920) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::max(), 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::max());
}

TEST_F(CheckedSubtractionTest_1920, IntNoOverflowMinMinusZero_1920) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::min(), 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::min());
}

TEST_F(CheckedSubtractionTest_1920, IntNoOverflowMaxMinusMax_1920) {
    int result = -1;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(CheckedSubtractionTest_1920, IntNoOverflowMinMinusMin_1920) {
    int result = -1;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(CheckedSubtractionTest_1920, IntOverflowMaxMinusNegativeMax_1920) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::max(), -std::numeric_limits<int>::max(), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_1920, IntBoundaryNoOverflowMinPlusOneMinusOne_1920) {
    int result = 0;
    // (INT_MIN + 1) - 1 = INT_MIN, should not overflow
    bool overflow = checkedSubtraction(std::numeric_limits<int>::min() + 1, 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::min());
}

TEST_F(CheckedSubtractionTest_1920, IntBoundaryNoOverflowMaxMinusOne_1920) {
    int result = 0;
    bool overflow = checkedSubtraction(std::numeric_limits<int>::max(), 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::max() - 1);
}

// ==================== short tests ====================

TEST_F(CheckedSubtractionTest_1920, ShortNormalSubtraction_1920) {
    short result = 0;
    bool overflow = checkedSubtraction<short>(100, 50, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 50);
}

TEST_F(CheckedSubtractionTest_1920, ShortOverflowMinMinusOne_1920) {
    short result = 0;
    bool overflow = checkedSubtraction<short>(std::numeric_limits<short>::min(), static_cast<short>(1), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_1920, ShortOverflowMaxMinusNegOne_1920) {
    short result = 0;
    bool overflow = checkedSubtraction<short>(std::numeric_limits<short>::max(), static_cast<short>(-1), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_1920, ShortNoOverflowBoundary_1920) {
    short result = 0;
    bool overflow = checkedSubtraction<short>(std::numeric_limits<short>::max(), std::numeric_limits<short>::max(), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

// ==================== long long tests ====================

TEST_F(CheckedSubtractionTest_1920, LongLongNormalSubtraction_1920) {
    long long result = 0;
    bool overflow = checkedSubtraction<long long>(1000000000LL, 999999999LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 1LL);
}

TEST_F(CheckedSubtractionTest_1920, LongLongOverflowMinMinusOne_1920) {
    long long result = 0;
    bool overflow = checkedSubtraction<long long>(std::numeric_limits<long long>::min(), 1LL, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_1920, LongLongOverflowMaxMinusNegOne_1920) {
    long long result = 0;
    bool overflow = checkedSubtraction<long long>(std::numeric_limits<long long>::max(), -1LL, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_1920, LongLongNoOverflowMaxMinusMax_1920) {
    long long result = -1;
    bool overflow = checkedSubtraction<long long>(std::numeric_limits<long long>::max(), std::numeric_limits<long long>::max(), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0LL);
}

// ==================== unsigned int tests ====================

TEST_F(CheckedSubtractionTest_1920, UnsignedIntNormalSubtraction_1920) {
    unsigned int result = 0;
    bool overflow = checkedSubtraction<unsigned int>(10u, 3u, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 7u);
}

TEST_F(CheckedSubtractionTest_1920, UnsignedIntOverflowZeroMinusOne_1920) {
    unsigned int result = 0;
    bool overflow = checkedSubtraction<unsigned int>(0u, 1u, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_1920, UnsignedIntNoOverflowSameValues_1920) {
    unsigned int result = 99;
    bool overflow = checkedSubtraction<unsigned int>(42u, 42u, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0u);
}

TEST_F(CheckedSubtractionTest_1920, UnsignedIntOverflowSmallMinusLarge_1920) {
    unsigned int result = 0;
    bool overflow = checkedSubtraction<unsigned int>(5u, 10u, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_1920, UnsignedIntNoOverflowMaxMinusMax_1920) {
    unsigned int result = 99;
    bool overflow = checkedSubtraction<unsigned int>(std::numeric_limits<unsigned int>::max(), std::numeric_limits<unsigned int>::max(), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0u);
}

TEST_F(CheckedSubtractionTest_1920, UnsignedIntOverflowZeroMinusMax_1920) {
    unsigned int result = 0;
    bool overflow = checkedSubtraction<unsigned int>(0u, std::numeric_limits<unsigned int>::max(), &result);
    EXPECT_TRUE(overflow);
}

// ==================== Large value int tests ====================

TEST_F(CheckedSubtractionTest_1920, IntLargePositiveMinusLargeNegative_1920) {
    int result = 0;
    // INT_MAX / 2 + 1 minus -(INT_MAX / 2 + 1) would overflow
    int half = std::numeric_limits<int>::max() / 2 + 1;
    bool overflow = checkedSubtraction(half, -half, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_1920, IntNegativeMinusPositiveBoundary_1920) {
    int result = 0;
    // -(INT_MAX/2 + 1) minus (INT_MAX/2 + 1) should overflow
    int half = std::numeric_limits<int>::max() / 2 + 1;
    bool overflow = checkedSubtraction(-half, half, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedSubtractionTest_1920, IntNoOverflowNegOneMinusNegOne_1920) {
    int result = 99;
    bool overflow = checkedSubtraction(-1, -1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(CheckedSubtractionTest_1920, IntNoOverflowOneMinusOne_1920) {
    int result = 99;
    bool overflow = checkedSubtraction(1, 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}
