// File: GooCheckedOps_checkedMultiply_test_6.cpp
// Unit tests for checkedMultiply in ./TestProjects/poppler/goo/GooCheckedOps.h

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

#include "goo/GooCheckedOps.h"

namespace {

// Helpers to compute expected products safely in tests.
template <typename T>
static T SafeMulSigned(T a, T b) {
  static_assert(std::is_signed_v<T>, "Signed type required");
#if defined(__SIZEOF_INT128__)
  __int128 prod = static_cast<__int128>(a) * static_cast<__int128>(b);
  return static_cast<T>(prod);
#else
  long long prod = static_cast<long long>(a) * static_cast<long long>(b);
  return static_cast<T>(prod);
#endif
}

template <typename T>
static T SafeMulUnsigned(T a, T b) {
  static_assert(std::is_unsigned_v<T>, "Unsigned type required");
#if defined(__SIZEOF_INT128__)
  unsigned __int128 prod = static_cast<unsigned __int128>(a) * static_cast<unsigned __int128>(b);
  return static_cast<T>(prod);
#else
  // Fallback should still be safe for small values used in "no overflow" tests.
  auto prod = static_cast<unsigned long long>(a) * static_cast<unsigned long long>(b);
  return static_cast<T>(prod);
#endif
}

}  // namespace

// -------------------- Normal operation --------------------

TEST(GooCheckedOpsTest_6, Int32_NoOverflow_Positive_6) {
  int32_t out = 0;
  const int32_t x = 30000;
  const int32_t y = 2;

  const bool overflow = checkedMultiply<int32_t>(x, y, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, SafeMulSigned<int32_t>(x, y));
}

TEST(GooCheckedOpsTest_6, Int32_NoOverflow_NegativeTimesPositive_6) {
  int32_t out = 123;  // sentinel overwritten on success
  const int32_t x = -7;
  const int32_t y = 6;

  const bool overflow = checkedMultiply<int32_t>(x, y, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, SafeMulSigned<int32_t>(x, y));
}

TEST(GooCheckedOpsTest_6, UInt32_NoOverflow_SmallValues_6) {
  uint32_t out = 0;
  const uint32_t x = 40000u;
  const uint32_t y = 3u;

  const bool overflow = checkedMultiply<uint32_t>(x, y, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, SafeMulUnsigned<uint32_t>(x, y));
}

// -------------------- Boundary conditions --------------------

TEST(GooCheckedOpsTest_6, MultiplyByZero_YieldsZero_6) {
  int out = 99;
  const bool overflow = checkedMultiply<int>(12345, 0, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, 0);
}

TEST(GooCheckedOpsTest_6, MultiplyByOne_YieldsSameValue_6) {
  long long out = 0;
  const long long x = std::numeric_limits<long long>::max();
  const bool overflow = checkedMultiply<long long>(x, 1LL, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, x);
}

TEST(GooCheckedOpsTest_6, SizeT_NoOverflow_SmallValues_6) {
  std::size_t out = 0;
  const std::size_t x = static_cast<std::size_t>(1234);
  const std::size_t y = static_cast<std::size_t>(567);

  const bool overflow = checkedMultiply<std::size_t>(x, y, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, SafeMulUnsigned<std::size_t>(x, y));
}

// -------------------- Exceptional / error cases (overflow) --------------------

TEST(GooCheckedOpsTest_6, Int_Overflow_ReturnsTrue_6) {
  int out = 0;
  const int x = std::numeric_limits<int>::max();
  const int y = 2;

  const bool overflow = checkedMultiply<int>(x, y, &out);

  EXPECT_TRUE(overflow);
  // Do not assert on `out` on overflow: value may be unspecified.
}

TEST(GooCheckedOpsTest_6, Int64_Overflow_ReturnsTrue_6) {
  int64_t out = 0;
  const int64_t x = std::numeric_limits<int64_t>::max();
  const int64_t y = 2;

  const bool overflow = checkedMultiply<int64_t>(x, y, &out);

  EXPECT_TRUE(overflow);
}

TEST(GooCheckedOpsTest_6, UInt32_Overflow_ReturnsTrue_6) {
  uint32_t out = 0;
  const uint32_t x = std::numeric_limits<uint32_t>::max();
  const uint32_t y = 2u;

  const bool overflow = checkedMultiply<uint32_t>(x, y, &out);

  EXPECT_TRUE(overflow);
}

TEST(GooCheckedOpsTest_6, SizeT_Overflow_ReturnsTrue_6) {
  std::size_t out = 0;
  const std::size_t x = std::numeric_limits<std::size_t>::max();
  const std::size_t y = static_cast<std::size_t>(2);

  const bool overflow = checkedMultiply<std::size_t>(x, y, &out);

  EXPECT_TRUE(overflow);
}

TEST(GooCheckedOpsTest_6, IntMinTimesMinusOne_OverflowIfSignedTwoComplementLike_6) {
  // This is a commonly observable overflow case for signed integers.
  // We only assert the observable return value; we avoid any assumptions about `out`.
  int out = 0;
  const int x = std::numeric_limits<int>::min();
  const int y = -1;

  const bool overflow = checkedMultiply<int>(x, y, &out);

  // If the implementation reports overflow for this case (typical), it should be true.
  // If a platform/compiler treats it differently, the function contract (return value)
  // is the only observable; this expectation reflects the standard overflow check behavior.
  EXPECT_TRUE(overflow);
}