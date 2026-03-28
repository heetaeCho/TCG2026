#include <gtest/gtest.h>
#include <limits>
#include <cstdint>

#include "GooCheckedOps.h"

// Test fixture for checkedMultiply tests
class CheckedMultiplyTest_6 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== int tests ====================

TEST_F(CheckedMultiplyTest_6, IntMultiplyZeroByZero_6) {
    int result = -1;
    bool overflow = checkedMultiply(0, 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyOneByOne_6) {
    int result = -1;
    bool overflow = checkedMultiply(1, 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 1);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyPositiveNumbers_6) {
    int result = -1;
    bool overflow = checkedMultiply(6, 7, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 42);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyByZeroLeft_6) {
    int result = -1;
    bool overflow = checkedMultiply(0, 12345, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyByZeroRight_6) {
    int result = -1;
    bool overflow = checkedMultiply(12345, 0, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyNegativeByPositive_6) {
    int result = 0;
    bool overflow = checkedMultiply(-3, 5, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -15);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyNegativeByNegative_6) {
    int result = 0;
    bool overflow = checkedMultiply(-4, -5, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 20);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyMaxByOne_6) {
    int result = 0;
    bool overflow = checkedMultiply(std::numeric_limits<int>::max(), 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::max());
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyMinByOne_6) {
    int result = 0;
    bool overflow = checkedMultiply(std::numeric_limits<int>::min(), 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::min());
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyOverflowPositive_6) {
    int result = 0;
    bool overflow = checkedMultiply(std::numeric_limits<int>::max(), 2, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyOverflowNegative_6) {
    int result = 0;
    bool overflow = checkedMultiply(std::numeric_limits<int>::min(), 2, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyOverflowMaxByMax_6) {
    int result = 0;
    bool overflow = checkedMultiply(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyOverflowMinByMin_6) {
    int result = 0;
    bool overflow = checkedMultiply(std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyOverflowMinByNegOne_6) {
    int result = 0;
    bool overflow = checkedMultiply(std::numeric_limits<int>::min(), -1, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyMaxByNegOne_6) {
    int result = 0;
    bool overflow = checkedMultiply(std::numeric_limits<int>::max(), -1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -std::numeric_limits<int>::max());
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyLargeNoOverflow_6) {
    // 46340^2 = 2147395600, which is less than INT_MAX (2147483647)
    int result = 0;
    bool overflow = checkedMultiply(46340, 46340, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 46340 * 46340);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyLargeOverflow_6) {
    // 46341^2 = 2147488281, which overflows INT_MAX
    int result = 0;
    bool overflow = checkedMultiply(46341, 46341, &result);
    EXPECT_TRUE(overflow);
}

// ==================== short tests ====================

TEST_F(CheckedMultiplyTest_6, ShortMultiplyNormal_6) {
    short result = 0;
    bool overflow = checkedMultiply<short>(10, 20, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 200);
}

TEST_F(CheckedMultiplyTest_6, ShortMultiplyOverflow_6) {
    short result = 0;
    bool overflow = checkedMultiply<short>(std::numeric_limits<short>::max(), static_cast<short>(2), &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_6, ShortMultiplyMaxByOne_6) {
    short result = 0;
    bool overflow = checkedMultiply<short>(std::numeric_limits<short>::max(), static_cast<short>(1), &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<short>::max());
}

// ==================== long long tests ====================

TEST_F(CheckedMultiplyTest_6, LongLongMultiplyNormal_6) {
    long long result = 0;
    bool overflow = checkedMultiply<long long>(100000LL, 100000LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 10000000000LL);
}

TEST_F(CheckedMultiplyTest_6, LongLongMultiplyOverflow_6) {
    long long result = 0;
    bool overflow = checkedMultiply<long long>(std::numeric_limits<long long>::max(), 2LL, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_6, LongLongMultiplyByZero_6) {
    long long result = -1;
    bool overflow = checkedMultiply<long long>(std::numeric_limits<long long>::max(), 0LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0LL);
}

// ==================== unsigned int tests ====================

TEST_F(CheckedMultiplyTest_6, UnsignedIntMultiplyNormal_6) {
    unsigned int result = 0;
    bool overflow = checkedMultiply<unsigned int>(100u, 200u, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 20000u);
}

TEST_F(CheckedMultiplyTest_6, UnsignedIntMultiplyOverflow_6) {
    unsigned int result = 0;
    bool overflow = checkedMultiply<unsigned int>(std::numeric_limits<unsigned int>::max(), 2u, &result);
    EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyTest_6, UnsignedIntMultiplyMaxByOne_6) {
    unsigned int result = 0;
    bool overflow = checkedMultiply<unsigned int>(std::numeric_limits<unsigned int>::max(), 1u, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<unsigned int>::max());
}

TEST_F(CheckedMultiplyTest_6, UnsignedIntMultiplyByZero_6) {
    unsigned int result = 99;
    bool overflow = checkedMultiply<unsigned int>(std::numeric_limits<unsigned int>::max(), 0u, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0u);
}

// ==================== Edge case: multiply by -1 ====================

TEST_F(CheckedMultiplyTest_6, IntMultiplyNegOneByNegOne_6) {
    int result = 0;
    bool overflow = checkedMultiply(-1, -1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 1);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyOneByNegOne_6) {
    int result = 0;
    bool overflow = checkedMultiply(1, -1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -1);
}

// ==================== Boundary: just at max ====================

TEST_F(CheckedMultiplyTest_6, IntMultiplyBoundaryExact_6) {
    // INT_MAX = 2147483647
    // 2147483647 * 1 should not overflow
    int result = 0;
    bool overflow = checkedMultiply(2147483647, 1, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 2147483647);
}

TEST_F(CheckedMultiplyTest_6, IntMultiplyMinByNegTwo_6) {
    int result = 0;
    bool overflow = checkedMultiply(std::numeric_limits<int>::min(), -2, &result);
    EXPECT_TRUE(overflow);
}
