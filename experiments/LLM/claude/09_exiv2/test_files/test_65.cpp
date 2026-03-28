#include <gtest/gtest.h>
#include <limits>
#include <cstdint>

// Include the header under test
#include "safe_op.hpp"

// Test fixture
class SafeOpTest_65 : public ::testing::Test {
protected:
};

// ============================================================
// Tests for int type
// ============================================================

TEST_F(SafeOpTest_65, IntAddNoOverflow_65) {
  int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(3, 4, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, 7);
}

TEST_F(SafeOpTest_65, IntAddZeros_65) {
  int result = -1;
  bool overflow = Safe::Internal::builtin_add_overflow(0, 0, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, 0);
}

TEST_F(SafeOpTest_65, IntAddNegativeNumbers_65) {
  int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(-3, -4, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, -7);
}

TEST_F(SafeOpTest_65, IntAddPositiveAndNegative_65) {
  int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(10, -3, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, 7);
}

TEST_F(SafeOpTest_65, IntAddMaxOverflow_65) {
  int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<int>::max(), 1, result);
  EXPECT_TRUE(overflow);
}

TEST_F(SafeOpTest_65, IntAddMinOverflow_65) {
  int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<int>::min(), -1, result);
  EXPECT_TRUE(overflow);
}

TEST_F(SafeOpTest_65, IntAddMaxPlusZero_65) {
  int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<int>::max(), 0, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, std::numeric_limits<int>::max());
}

TEST_F(SafeOpTest_65, IntAddMinPlusZero_65) {
  int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<int>::min(), 0, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, std::numeric_limits<int>::min());
}

TEST_F(SafeOpTest_65, IntAddMaxPlusMax_65) {
  int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), result);
  EXPECT_TRUE(overflow);
}

TEST_F(SafeOpTest_65, IntAddMinPlusMin_65) {
  int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), result);
  EXPECT_TRUE(overflow);
}

TEST_F(SafeOpTest_65, IntAddMaxPlusMinNoOverflow_65) {
  int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, -1);
}

// ============================================================
// Tests for long type
// ============================================================

TEST_F(SafeOpTest_65, LongAddNoOverflow_65) {
  long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(3L, 4L, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, 7L);
}

TEST_F(SafeOpTest_65, LongAddMaxOverflow_65) {
  long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<long>::max(), 1L, result);
  EXPECT_TRUE(overflow);
}

TEST_F(SafeOpTest_65, LongAddMinOverflow_65) {
  long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<long>::min(), -1L, result);
  EXPECT_TRUE(overflow);
}

TEST_F(SafeOpTest_65, LongAddMaxPlusZero_65) {
  long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<long>::max(), 0L, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, std::numeric_limits<long>::max());
}

TEST_F(SafeOpTest_65, LongAddMaxPlusMin_65) {
  long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<long>::max(), std::numeric_limits<long>::min(), result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, -1L);
}

// ============================================================
// Tests for long long type
// ============================================================

TEST_F(SafeOpTest_65, LongLongAddNoOverflow_65) {
  long long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(3LL, 4LL, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, 7LL);
}

TEST_F(SafeOpTest_65, LongLongAddMaxOverflow_65) {
  long long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<long long>::max(), 1LL, result);
  EXPECT_TRUE(overflow);
}

TEST_F(SafeOpTest_65, LongLongAddMinOverflow_65) {
  long long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<long long>::min(), -1LL, result);
  EXPECT_TRUE(overflow);
}

TEST_F(SafeOpTest_65, LongLongAddNegatives_65) {
  long long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(-100LL, -200LL, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, -300LL);
}

TEST_F(SafeOpTest_65, LongLongAddMaxPlusMin_65) {
  long long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<long long>::max(), std::numeric_limits<long long>::min(), result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, -1LL);
}

// ============================================================
// Tests for unsigned int type
// ============================================================

TEST_F(SafeOpTest_65, UnsignedIntAddNoOverflow_65) {
  unsigned int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(3u, 4u, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, 7u);
}

TEST_F(SafeOpTest_65, UnsignedIntAddZeros_65) {
  unsigned int result = 99u;
  bool overflow = Safe::Internal::builtin_add_overflow(0u, 0u, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, 0u);
}

TEST_F(SafeOpTest_65, UnsignedIntAddMaxOverflow_65) {
  unsigned int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<unsigned int>::max(), 1u, result);
  EXPECT_TRUE(overflow);
}

TEST_F(SafeOpTest_65, UnsignedIntAddMaxPlusMax_65) {
  unsigned int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<unsigned int>::max(), std::numeric_limits<unsigned int>::max(), result);
  EXPECT_TRUE(overflow);
}

TEST_F(SafeOpTest_65, UnsignedIntAddMaxPlusZero_65) {
  unsigned int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<unsigned int>::max(), 0u, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, std::numeric_limits<unsigned int>::max());
}

// ============================================================
// Tests for unsigned long type
// ============================================================

TEST_F(SafeOpTest_65, UnsignedLongAddNoOverflow_65) {
  unsigned long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(3UL, 4UL, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, 7UL);
}

TEST_F(SafeOpTest_65, UnsignedLongAddMaxOverflow_65) {
  unsigned long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<unsigned long>::max(), 1UL, result);
  EXPECT_TRUE(overflow);
}

TEST_F(SafeOpTest_65, UnsignedLongAddMaxPlusZero_65) {
  unsigned long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<unsigned long>::max(), 0UL, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, std::numeric_limits<unsigned long>::max());
}

TEST_F(SafeOpTest_65, UnsignedLongAddLargeValues_65) {
  unsigned long half = std::numeric_limits<unsigned long>::max() / 2;
  unsigned long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(half, half, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, half + half);
}

// ============================================================
// Tests for unsigned long long type
// ============================================================

TEST_F(SafeOpTest_65, UnsignedLongLongAddNoOverflow_65) {
  unsigned long long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(3ULL, 4ULL, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, 7ULL);
}

TEST_F(SafeOpTest_65, UnsignedLongLongAddMaxOverflow_65) {
  unsigned long long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<unsigned long long>::max(), 1ULL, result);
  EXPECT_TRUE(overflow);
}

TEST_F(SafeOpTest_65, UnsignedLongLongAddMaxPlusZero_65) {
  unsigned long long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<unsigned long long>::max(), 0ULL, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, std::numeric_limits<unsigned long long>::max());
}

TEST_F(SafeOpTest_65, UnsignedLongLongAddMaxPlusMax_65) {
  unsigned long long result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<unsigned long long>::max(), std::numeric_limits<unsigned long long>::max(), result);
  EXPECT_TRUE(overflow);
}

// ============================================================
// Boundary: near-overflow cases
// ============================================================

TEST_F(SafeOpTest_65, IntAddJustBelowMaxNoOverflow_65) {
  int result = 0;
  int max = std::numeric_limits<int>::max();
  bool overflow = Safe::Internal::builtin_add_overflow(max - 1, 1, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, max);
}

TEST_F(SafeOpTest_65, IntAddJustAboveMinNoOverflow_65) {
  int result = 0;
  int min = std::numeric_limits<int>::min();
  bool overflow = Safe::Internal::builtin_add_overflow(min + 1, -1, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, min);
}

TEST_F(SafeOpTest_65, UnsignedIntAddJustBelowMaxNoOverflow_65) {
  unsigned int result = 0;
  unsigned int max = std::numeric_limits<unsigned int>::max();
  bool overflow = Safe::Internal::builtin_add_overflow(max - 1u, 1u, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, max);
}

TEST_F(SafeOpTest_65, IntAddOneNegativeOnePositive_65) {
  int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(-1, 1, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, 0);
}

TEST_F(SafeOpTest_65, LongLongAddJustBelowMax_65) {
  long long result = 0;
  long long max = std::numeric_limits<long long>::max();
  bool overflow = Safe::Internal::builtin_add_overflow(max - 1LL, 1LL, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, max);
}

TEST_F(SafeOpTest_65, UnsignedLongLongAddJustBelowMax_65) {
  unsigned long long result = 0;
  unsigned long long max = std::numeric_limits<unsigned long long>::max();
  bool overflow = Safe::Internal::builtin_add_overflow(max - 1ULL, 1ULL, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, max);
}

// ============================================================
// Additional edge cases
// ============================================================

TEST_F(SafeOpTest_65, IntAddMinPlusMaxNoOverflow_65) {
  int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, -1);
}

TEST_F(SafeOpTest_65, IntAddLargePositiveOverflow_65) {
  int result = 0;
  int half = std::numeric_limits<int>::max() / 2 + 1;
  bool overflow = Safe::Internal::builtin_add_overflow(half, half, result);
  EXPECT_TRUE(overflow);
}

TEST_F(SafeOpTest_65, IntAddLargeNegativeOverflow_65) {
  int result = 0;
  int half = std::numeric_limits<int>::min() / 2 - 1;
  bool overflow = Safe::Internal::builtin_add_overflow(half, half, result);
  EXPECT_TRUE(overflow);
}

TEST_F(SafeOpTest_65, UnsignedIntAddTwoOnes_65) {
  unsigned int result = 0;
  bool overflow = Safe::Internal::builtin_add_overflow(1u, 1u, result);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(result, 2u);
}
