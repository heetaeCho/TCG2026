#include <gtest/gtest.h>
#include <limits>
#include <cstdint>

// Include the header under test
#include "safe_op.hpp"

// ============================================================================
// Tests for signed types where sizeof(T) >= sizeof(int)
// Typically: int, long, long long
// ============================================================================

class SafeAddSignedInt_64 : public ::testing::Test {};

TEST_F(SafeAddSignedInt_64, NoOverflow_PositivePlusPositive_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(10, 20, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 30);
}

TEST_F(SafeAddSignedInt_64, NoOverflow_NegativePlusNegative_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(-10, -20, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -30);
}

TEST_F(SafeAddSignedInt_64, NoOverflow_PositivePlusNegative_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(100, -50, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 50);
}

TEST_F(SafeAddSignedInt_64, NoOverflow_NegativePlusPositive_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(-100, 50, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -50);
}

TEST_F(SafeAddSignedInt_64, NoOverflow_ZeroPlusZero_64) {
    int result = 42;
    bool overflow = Safe::Internal::fallback_add_overflow(0, 0, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(SafeAddSignedInt_64, NoOverflow_ZeroPlusPositive_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(0, 5, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 5);
}

TEST_F(SafeAddSignedInt_64, NoOverflow_ZeroPlusNegative_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(0, -5, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -5);
}

TEST_F(SafeAddSignedInt_64, Overflow_MaxPlusOne_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::max(), 1, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddSignedInt_64, Overflow_MaxPlusMax_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddSignedInt_64, Overflow_MinMinusOne_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::min(), -1, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddSignedInt_64, Overflow_MinPlusMin_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddSignedInt_64, NoOverflow_MaxPlusZero_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::max(), 0, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::max());
}

TEST_F(SafeAddSignedInt_64, NoOverflow_MinPlusZero_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::min(), 0, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::min());
}

TEST_F(SafeAddSignedInt_64, NoOverflow_MaxPlusMinusOne_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::max(), -1, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::max() - 1);
}

TEST_F(SafeAddSignedInt_64, NoOverflow_MinPlusOne_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::min(), 1, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::min() + 1);
}

TEST_F(SafeAddSignedInt_64, NoOverflow_MaxPlusNegativeMax_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::max(), -std::numeric_limits<int>::max(), result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

// ============================================================================
// Tests for signed types where sizeof(T) < sizeof(int)
// Typically: int8_t, int16_t (short)
// ============================================================================

class SafeAddSignedSmall_64 : public ::testing::Test {};

TEST_F(SafeAddSignedSmall_64, Int8_NoOverflow_64) {
    int8_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int8_t>(10, 20, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 30);
}

TEST_F(SafeAddSignedSmall_64, Int8_NoOverflow_NegativeValues_64) {
    int8_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int8_t>(-10, -20, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -30);
}

TEST_F(SafeAddSignedSmall_64, Int8_Overflow_MaxPlusOne_64) {
    int8_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int8_t>(127, 1, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddSignedSmall_64, Int8_Overflow_MinMinusOne_64) {
    int8_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int8_t>(-128, -1, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddSignedSmall_64, Int8_NoOverflow_MaxPlusZero_64) {
    int8_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int8_t>(127, 0, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 127);
}

TEST_F(SafeAddSignedSmall_64, Int8_NoOverflow_MinPlusZero_64) {
    int8_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int8_t>(-128, 0, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -128);
}

TEST_F(SafeAddSignedSmall_64, Int8_Overflow_MaxPlusMax_64) {
    int8_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int8_t>(127, 127, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddSignedSmall_64, Int8_Overflow_MinPlusMin_64) {
    int8_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int8_t>(-128, -128, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddSignedSmall_64, Int8_NoOverflow_ZeroPlusZero_64) {
    int8_t result = 42;
    bool overflow = Safe::Internal::fallback_add_overflow<int8_t>(0, 0, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0);
}

TEST_F(SafeAddSignedSmall_64, Int16_NoOverflow_64) {
    int16_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int16_t>(1000, 2000, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 3000);
}

TEST_F(SafeAddSignedSmall_64, Int16_Overflow_MaxPlusOne_64) {
    int16_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int16_t>(std::numeric_limits<int16_t>::max(), 1, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddSignedSmall_64, Int16_Overflow_MinMinusOne_64) {
    int16_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int16_t>(std::numeric_limits<int16_t>::min(), -1, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddSignedSmall_64, Int16_NoOverflow_MaxMinusOne_64) {
    int16_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int16_t>(std::numeric_limits<int16_t>::max(), -1, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int16_t>::max() - 1);
}

TEST_F(SafeAddSignedSmall_64, Int16_NoOverflow_MinPlusOne_64) {
    int16_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int16_t>(std::numeric_limits<int16_t>::min(), 1, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int16_t>::min() + 1);
}

// ============================================================================
// Tests for unsigned types
// ============================================================================

class SafeAddUnsigned_64 : public ::testing::Test {};

TEST_F(SafeAddUnsigned_64, UInt_NoOverflow_64) {
    unsigned int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(10u, 20u, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 30u);
}

TEST_F(SafeAddUnsigned_64, UInt_NoOverflow_ZeroPlusZero_64) {
    unsigned int result = 42;
    bool overflow = Safe::Internal::fallback_add_overflow(0u, 0u, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 0u);
}

TEST_F(SafeAddUnsigned_64, UInt_NoOverflow_MaxPlusZero_64) {
    unsigned int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<unsigned int>::max(), 0u, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<unsigned int>::max());
}

TEST_F(SafeAddUnsigned_64, UInt_Overflow_MaxPlusOne_64) {
    unsigned int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<unsigned int>::max(), 1u, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddUnsigned_64, UInt_Overflow_MaxPlusMax_64) {
    unsigned int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<unsigned int>::max(), std::numeric_limits<unsigned int>::max(), result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddUnsigned_64, UInt8_NoOverflow_64) {
    uint8_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<uint8_t>(100, 50, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 150);
}

TEST_F(SafeAddUnsigned_64, UInt8_Overflow_MaxPlusOne_64) {
    uint8_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<uint8_t>(255, 1, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddUnsigned_64, UInt8_NoOverflow_MaxPlusZero_64) {
    uint8_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<uint8_t>(255, 0, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 255);
}

TEST_F(SafeAddUnsigned_64, UInt16_NoOverflow_64) {
    uint16_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<uint16_t>(1000, 2000, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 3000);
}

TEST_F(SafeAddUnsigned_64, UInt16_Overflow_MaxPlusOne_64) {
    uint16_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<uint16_t>(std::numeric_limits<uint16_t>::max(), 1, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddUnsigned_64, UInt32_NoOverflow_64) {
    uint32_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<uint32_t>(100000, 200000, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 300000u);
}

TEST_F(SafeAddUnsigned_64, UInt32_Overflow_MaxPlusOne_64) {
    uint32_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<uint32_t>(std::numeric_limits<uint32_t>::max(), 1, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddUnsigned_64, UInt64_NoOverflow_64) {
    uint64_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<uint64_t>(1000000000ULL, 2000000000ULL, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 3000000000ULL);
}

TEST_F(SafeAddUnsigned_64, UInt64_Overflow_MaxPlusOne_64) {
    uint64_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<uint64_t>(std::numeric_limits<uint64_t>::max(), 1, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddUnsigned_64, UInt64_NoOverflow_MaxPlusZero_64) {
    uint64_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<uint64_t>(std::numeric_limits<uint64_t>::max(), 0, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<uint64_t>::max());
}

// ============================================================================
// Tests for long long (signed, sizeof >= sizeof(int))
// ============================================================================

class SafeAddSignedLongLong_64 : public ::testing::Test {};

TEST_F(SafeAddSignedLongLong_64, NoOverflow_64) {
    long long result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<long long>(1000000LL, 2000000LL, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 3000000LL);
}

TEST_F(SafeAddSignedLongLong_64, Overflow_MaxPlusOne_64) {
    long long result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<long long>(std::numeric_limits<long long>::max(), 1LL, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddSignedLongLong_64, Overflow_MinMinusOne_64) {
    long long result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<long long>(std::numeric_limits<long long>::min(), -1LL, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddSignedLongLong_64, NoOverflow_MaxPlusNegOne_64) {
    long long result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<long long>(std::numeric_limits<long long>::max(), -1LL, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<long long>::max() - 1);
}

TEST_F(SafeAddSignedLongLong_64, NoOverflow_MinPlusOne_64) {
    long long result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<long long>(std::numeric_limits<long long>::min(), 1LL, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<long long>::min() + 1);
}

// ============================================================================
// Tests for size_t (typically unsigned, large)
// ============================================================================

class SafeAddSizeT_64 : public ::testing::Test {};

TEST_F(SafeAddSizeT_64, NoOverflow_64) {
    size_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<size_t>(100, 200, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 300u);
}

TEST_F(SafeAddSizeT_64, Overflow_MaxPlusOne_64) {
    size_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<size_t>(std::numeric_limits<size_t>::max(), 1, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeAddSizeT_64, NoOverflow_MaxPlusZero_64) {
    size_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<size_t>(std::numeric_limits<size_t>::max(), 0, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<size_t>::max());
}

// ============================================================================
// Edge case: result is not modified on overflow (for signed int path)
// ============================================================================

class SafeAddResultUnchangedOnOverflow_64 : public ::testing::Test {};

TEST_F(SafeAddResultUnchangedOnOverflow_64, SignedIntOverflow_ResultUnchanged_64) {
    int result = 42;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::max(), 1, result);
    EXPECT_TRUE(overflow);
    // On overflow, result should not be modified (it stays 42)
    EXPECT_EQ(result, 42);
}

TEST_F(SafeAddResultUnchangedOnOverflow_64, SignedIntUnderflow_ResultUnchanged_64) {
    int result = 42;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::min(), -1, result);
    EXPECT_TRUE(overflow);
    EXPECT_EQ(result, 42);
}

TEST_F(SafeAddResultUnchangedOnOverflow_64, Int8Overflow_ResultUnchanged_64) {
    int8_t result = 42;
    bool overflow = Safe::Internal::fallback_add_overflow<int8_t>(127, 1, result);
    EXPECT_TRUE(overflow);
    EXPECT_EQ(result, 42);
}

// ============================================================================
// Commutativity tests
// ============================================================================

class SafeAddCommutativity_64 : public ::testing::Test {};

TEST_F(SafeAddCommutativity_64, SignedInt_Commutative_64) {
    int result1 = 0, result2 = 0;
    bool ov1 = Safe::Internal::fallback_add_overflow(30, 50, result1);
    bool ov2 = Safe::Internal::fallback_add_overflow(50, 30, result2);
    EXPECT_EQ(ov1, ov2);
    EXPECT_EQ(result1, result2);
}

TEST_F(SafeAddCommutativity_64, UnsignedInt_Commutative_64) {
    unsigned int result1 = 0, result2 = 0;
    bool ov1 = Safe::Internal::fallback_add_overflow(30u, 50u, result1);
    bool ov2 = Safe::Internal::fallback_add_overflow(50u, 30u, result2);
    EXPECT_EQ(ov1, ov2);
    EXPECT_EQ(result1, result2);
}

TEST_F(SafeAddCommutativity_64, SignedInt_OverflowCommutative_64) {
    int result1 = 0, result2 = 0;
    bool ov1 = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::max(), 5, result1);
    bool ov2 = Safe::Internal::fallback_add_overflow(5, std::numeric_limits<int>::max(), result2);
    EXPECT_EQ(ov1, ov2);
    EXPECT_TRUE(ov1);
}

// ============================================================================
// Boundary: exactly at max and min without overflowing
// ============================================================================

class SafeAddBoundary_64 : public ::testing::Test {};

TEST_F(SafeAddBoundary_64, SignedInt_ExactMax_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::max() - 5, 5, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::max());
}

TEST_F(SafeAddBoundary_64, SignedInt_ExactMin_64) {
    int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::min() + 5, -5, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<int>::min());
}

TEST_F(SafeAddBoundary_64, UnsignedInt_ExactMax_64) {
    unsigned int result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<unsigned int>::max() - 5u, 5u, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, std::numeric_limits<unsigned int>::max());
}

TEST_F(SafeAddBoundary_64, UInt8_ExactMax_64) {
    uint8_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<uint8_t>(250, 5, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 255);
}

TEST_F(SafeAddBoundary_64, Int8_ExactMax_64) {
    int8_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int8_t>(122, 5, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 127);
}

TEST_F(SafeAddBoundary_64, Int8_ExactMin_64) {
    int8_t result = 0;
    bool overflow = Safe::Internal::fallback_add_overflow<int8_t>(-123, -5, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, -128);
}
