#include <gtest/gtest.h>
#include <climits>
#include <limits>
#include "GooCheckedOps.h"

// Test normal multiplication of two positive numbers
TEST(CheckedMultiplyLongLongTest_7, PositiveTimesPositive_7) {
    long long result = 0;
    bool overflow = checkedMultiply<long long>(3LL, 4LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 12LL);
}

// Test multiplication by zero (left operand)
TEST(CheckedMultiplyLongLongTest_7, ZeroTimesPositive_7) {
    long long result = -1;
    bool overflow = checkedMultiply<long long>(0LL, 42LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0LL);
}

// Test multiplication by zero (right operand)
TEST(CheckedMultiplyLongLongTest_7, PositiveTimesZero_7) {
    long long result = -1;
    bool overflow = checkedMultiply<long long>(42LL, 0LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0LL);
}

// Test both operands zero
TEST(CheckedMultiplyLongLongTest_7, ZeroTimesZero_7) {
    long long result = -1;
    bool overflow = checkedMultiply<long long>(0LL, 0LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0LL);
}

// Test multiplication by one
TEST(CheckedMultiplyLongLongTest_7, OneTimesValue_7) {
    long long result = 0;
    bool overflow = checkedMultiply<long long>(1LL, 123456789LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 123456789LL);
}

// Test value times one
TEST(CheckedMultiplyLongLongTest_7, ValueTimesOne_7) {
    long long result = 0;
    bool overflow = checkedMultiply<long long>(123456789LL, 1LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 123456789LL);
}

// Test negative times positive
TEST(CheckedMultiplyLongLongTest_7, NegativeTimesPositive_7) {
    long long result = 0;
    bool overflow = checkedMultiply<long long>(-3LL, 4LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -12LL);
}

// Test positive times negative
TEST(CheckedMultiplyLongLongTest_7, PositiveTimesNegative_7) {
    long long result = 0;
    bool overflow = checkedMultiply<long long>(3LL, -4LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -12LL);
}

// Test negative times negative
TEST(CheckedMultiplyLongLongTest_7, NegativeTimesNegative_7) {
    long long result = 0;
    bool overflow = checkedMultiply<long long>(-3LL, -4LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 12LL);
}

// Test overflow: large positive * large positive
TEST(CheckedMultiplyLongLongTest_7, OverflowLargePositiveTimesLargePositive_7) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    bool overflow = checkedMultiply<long long>(maxVal, 2LL, &result);
    EXPECT_TRUE(overflow);
}

// Test overflow: max * max
TEST(CheckedMultiplyLongLongTest_7, OverflowMaxTimesMax_7) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    bool overflow = checkedMultiply<long long>(maxVal, maxVal, &result);
    EXPECT_TRUE(overflow);
}

// Test boundary: max * 1 should not overflow
TEST(CheckedMultiplyLongLongTest_7, MaxTimesOne_7) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    bool overflow = checkedMultiply<long long>(maxVal, 1LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, maxVal);
}

// Test boundary: max * 0 should not overflow
TEST(CheckedMultiplyLongLongTest_7, MaxTimesZero_7) {
    long long result = -1;
    long long maxVal = std::numeric_limits<long long>::max();
    bool overflow = checkedMultiply<long long>(maxVal, 0LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0LL);
}

// Test large numbers that just barely don't overflow
TEST(CheckedMultiplyLongLongTest_7, BarelyNoOverflow_7) {
    long long result = 0;
    // sqrt of max long long is approximately 3037000499
    // Use values that multiply to just under max
    long long a = 3037000499LL;
    long long b = 3037000499LL;
    // a * b should be close to max but let's check if it overflows
    // 3037000499^2 = 9223372030926249001 which is less than 9223372036854775807
    bool overflow = checkedMultiply<long long>(a, b, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, a * b);
}

// Test large numbers that just barely overflow
TEST(CheckedMultiplyLongLongTest_7, BarelyOverflow_7) {
    long long result = 0;
    long long a = 3037000500LL;
    long long b = 3037000500LL;
    // 3037000500^2 = 9223372025000250000... let's check
    // Actually we need to be more precise. Let's use a clear overflow case.
    long long maxVal = std::numeric_limits<long long>::max();
    // maxVal / 2 + 1 * 2 should overflow
    long long half = maxVal / 2 + 1; // 4611686018427387904
    bool overflow = checkedMultiply<long long>(half, 2LL, &result);
    EXPECT_TRUE(overflow);
}

// Test overflow with negative: min * 2
TEST(CheckedMultiplyLongLongTest_7, OverflowMinTimesTwoNegative_7) {
    long long result = 0;
    long long minVal = std::numeric_limits<long long>::min();
    bool overflow = checkedMultiply<long long>(minVal, 2LL, &result);
    EXPECT_TRUE(overflow);
}

// Test min * 1 should not overflow
TEST(CheckedMultiplyLongLongTest_7, MinTimesOne_7) {
    long long result = 0;
    long long minVal = std::numeric_limits<long long>::min();
    bool overflow = checkedMultiply<long long>(minVal, 1LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, minVal);
}

// Test min * 0 should not overflow
TEST(CheckedMultiplyLongLongTest_7, MinTimesZero_7) {
    long long result = -1;
    long long minVal = std::numeric_limits<long long>::min();
    bool overflow = checkedMultiply<long long>(minVal, 0LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0LL);
}

// Test min * -1 should overflow (result would be max + 1 for two's complement)
TEST(CheckedMultiplyLongLongTest_7, MinTimesNegativeOne_7) {
    long long result = 0;
    long long minVal = std::numeric_limits<long long>::min();
    bool overflow = checkedMultiply<long long>(minVal, -1LL, &result);
    EXPECT_TRUE(overflow);
}

// Test -1 * -1 should not overflow
TEST(CheckedMultiplyLongLongTest_7, NegOneTimesNegOne_7) {
    long long result = 0;
    bool overflow = checkedMultiply<long long>(-1LL, -1LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 1LL);
}

// Test large negative * large positive causing overflow
TEST(CheckedMultiplyLongLongTest_7, LargeNegativeTimesLargePositive_7) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    bool overflow = checkedMultiply<long long>(-2LL, maxVal, &result);
    EXPECT_TRUE(overflow);
}

// Test moderate values
TEST(CheckedMultiplyLongLongTest_7, ModerateValues_7) {
    long long result = 0;
    bool overflow = checkedMultiply<long long>(100000LL, 100000LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 10000000000LL);
}

// Test negative * zero
TEST(CheckedMultiplyLongLongTest_7, NegativeTimesZero_7) {
    long long result = -1;
    bool overflow = checkedMultiply<long long>(-42LL, 0LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0LL);
}

// Test exact boundary: (max / 2) * 2
TEST(CheckedMultiplyLongLongTest_7, ExactHalfMaxTimesTwoNoOverflow_7) {
    long long result = 0;
    long long maxVal = std::numeric_limits<long long>::max();
    long long half = maxVal / 2; // 4611686018427387903
    bool overflow = checkedMultiply<long long>(half, 2LL, &result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, half * 2LL);
}
