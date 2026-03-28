#include <gtest/gtest.h>
#include <limits>
#include <cstdint>

// Include the header under test
#include "safe_op.hpp"

// ============================================================
// Tests for Safe::abs with signed integer types
// ============================================================

// --- int ---

TEST(SafeAbsTest_67, PositiveInt_67) {
  EXPECT_EQ(Safe::abs(42), 42);
}

TEST(SafeAbsTest_67, NegativeInt_67) {
  EXPECT_EQ(Safe::abs(-42), 42);
}

TEST(SafeAbsTest_67, ZeroInt_67) {
  EXPECT_EQ(Safe::abs(0), 0);
}

TEST(SafeAbsTest_67, IntMinReturnsIntMax_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<int>::min()), std::numeric_limits<int>::max());
}

TEST(SafeAbsTest_67, IntMaxReturnsIntMax_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<int>::max()), std::numeric_limits<int>::max());
}

TEST(SafeAbsTest_67, NegativeOneInt_67) {
  EXPECT_EQ(Safe::abs(-1), 1);
}

TEST(SafeAbsTest_67, PositiveOneInt_67) {
  EXPECT_EQ(Safe::abs(1), 1);
}

// --- long ---

TEST(SafeAbsTest_67, PositiveLong_67) {
  EXPECT_EQ(Safe::abs(100L), 100L);
}

TEST(SafeAbsTest_67, NegativeLong_67) {
  EXPECT_EQ(Safe::abs(-100L), 100L);
}

TEST(SafeAbsTest_67, ZeroLong_67) {
  EXPECT_EQ(Safe::abs(0L), 0L);
}

TEST(SafeAbsTest_67, LongMinReturnsLongMax_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<long>::min()), std::numeric_limits<long>::max());
}

TEST(SafeAbsTest_67, LongMaxReturnsLongMax_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<long>::max()), std::numeric_limits<long>::max());
}

// --- long long ---

TEST(SafeAbsTest_67, PositiveLongLong_67) {
  EXPECT_EQ(Safe::abs(999LL), 999LL);
}

TEST(SafeAbsTest_67, NegativeLongLong_67) {
  EXPECT_EQ(Safe::abs(-999LL), 999LL);
}

TEST(SafeAbsTest_67, LongLongMinReturnsLongLongMax_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<long long>::min()), std::numeric_limits<long long>::max());
}

TEST(SafeAbsTest_67, LongLongMaxReturnsLongLongMax_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<long long>::max()), std::numeric_limits<long long>::max());
}

// --- short ---

TEST(SafeAbsTest_67, PositiveShort_67) {
  short val = 10;
  EXPECT_EQ(Safe::abs(val), static_cast<short>(10));
}

TEST(SafeAbsTest_67, NegativeShort_67) {
  short val = -10;
  EXPECT_EQ(Safe::abs(val), static_cast<short>(10));
}

TEST(SafeAbsTest_67, ShortMinReturnsShortMax_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<short>::min()), std::numeric_limits<short>::max());
}

// --- int8_t ---

TEST(SafeAbsTest_67, PositiveInt8_67) {
  int8_t val = 127;
  EXPECT_EQ(Safe::abs(val), static_cast<int8_t>(127));
}

TEST(SafeAbsTest_67, NegativeInt8_67) {
  int8_t val = -50;
  EXPECT_EQ(Safe::abs(val), static_cast<int8_t>(50));
}

TEST(SafeAbsTest_67, Int8MinReturnsInt8Max_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<int8_t>::min()), std::numeric_limits<int8_t>::max());
}

// --- int16_t ---

TEST(SafeAbsTest_67, Int16MinReturnsInt16Max_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<int16_t>::min()), std::numeric_limits<int16_t>::max());
}

// --- int32_t ---

TEST(SafeAbsTest_67, Int32MinReturnsInt32Max_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<int32_t>::min()), std::numeric_limits<int32_t>::max());
}

// --- int64_t ---

TEST(SafeAbsTest_67, Int64MinReturnsInt64Max_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<int64_t>::min()), std::numeric_limits<int64_t>::max());
}

// ============================================================
// Tests for Safe::abs with unsigned integer types
// ============================================================

// --- unsigned int ---

TEST(SafeAbsTest_67, UnsignedIntReturnsItself_67) {
  unsigned int val = 42u;
  EXPECT_EQ(Safe::abs(val), 42u);
}

TEST(SafeAbsTest_67, UnsignedIntZero_67) {
  unsigned int val = 0u;
  EXPECT_EQ(Safe::abs(val), 0u);
}

TEST(SafeAbsTest_67, UnsignedIntMax_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<unsigned int>::max()), std::numeric_limits<unsigned int>::max());
}

// --- unsigned long ---

TEST(SafeAbsTest_67, UnsignedLongReturnsItself_67) {
  unsigned long val = 100UL;
  EXPECT_EQ(Safe::abs(val), 100UL);
}

TEST(SafeAbsTest_67, UnsignedLongMax_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<unsigned long>::max()), std::numeric_limits<unsigned long>::max());
}

// --- unsigned long long ---

TEST(SafeAbsTest_67, UnsignedLongLongReturnsItself_67) {
  unsigned long long val = 999ULL;
  EXPECT_EQ(Safe::abs(val), 999ULL);
}

TEST(SafeAbsTest_67, UnsignedLongLongMax_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<unsigned long long>::max()), std::numeric_limits<unsigned long long>::max());
}

// --- uint8_t ---

TEST(SafeAbsTest_67, Uint8ReturnsItself_67) {
  uint8_t val = 200;
  EXPECT_EQ(Safe::abs(val), static_cast<uint8_t>(200));
}

TEST(SafeAbsTest_67, Uint8Zero_67) {
  uint8_t val = 0;
  EXPECT_EQ(Safe::abs(val), static_cast<uint8_t>(0));
}

TEST(SafeAbsTest_67, Uint8Max_67) {
  EXPECT_EQ(Safe::abs(std::numeric_limits<uint8_t>::max()), std::numeric_limits<uint8_t>::max());
}

// --- uint16_t ---

TEST(SafeAbsTest_67, Uint16ReturnsItself_67) {
  uint16_t val = 50000;
  EXPECT_EQ(Safe::abs(val), static_cast<uint16_t>(50000));
}

// --- uint32_t ---

TEST(SafeAbsTest_67, Uint32ReturnsItself_67) {
  uint32_t val = 123456789u;
  EXPECT_EQ(Safe::abs(val), 123456789u);
}

// --- uint64_t ---

TEST(SafeAbsTest_67, Uint64ReturnsItself_67) {
  uint64_t val = 9999999999ULL;
  EXPECT_EQ(Safe::abs(val), 9999999999ULL);
}

// ============================================================
// Additional boundary tests for signed types near zero
// ============================================================

TEST(SafeAbsTest_67, SignedMinPlusOneInt_67) {
  int val = std::numeric_limits<int>::min() + 1;
  EXPECT_EQ(Safe::abs(val), std::numeric_limits<int>::max());
}

TEST(SafeAbsTest_67, SignedMinPlusTwoInt_67) {
  int val = std::numeric_limits<int>::min() + 2;
  EXPECT_EQ(Safe::abs(val), std::numeric_limits<int>::max() - 1);
}

TEST(SafeAbsTest_67, NegativeMaxInt_67) {
  // -INT_MAX should return INT_MAX
  int val = -std::numeric_limits<int>::max();
  EXPECT_EQ(Safe::abs(val), std::numeric_limits<int>::max());
}

// ============================================================
// Noexcept verification
// ============================================================

TEST(SafeAbsTest_67, IsNoexceptForSignedInt_67) {
  EXPECT_TRUE(noexcept(Safe::abs(0)));
}

TEST(SafeAbsTest_67, IsNoexceptForUnsignedInt_67) {
  EXPECT_TRUE(noexcept(Safe::abs(0u)));
}

TEST(SafeAbsTest_67, IsNoexceptForInt64_67) {
  EXPECT_TRUE(noexcept(Safe::abs(static_cast<int64_t>(0))));
}

TEST(SafeAbsTest_67, IsNoexceptForUint64_67) {
  EXPECT_TRUE(noexcept(Safe::abs(static_cast<uint64_t>(0))));
}
