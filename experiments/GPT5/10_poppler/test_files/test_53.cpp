// Copyright (C) 2026
// Unit tests for GooCheckedOps.h : checkedAdd
// The TEST_ID is 53

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

// Include the header under test.
// Adjust include path if your test target sets include directories differently.
#include "goo/GooCheckedOps.h"

namespace {

// Helper to keep test code terse and consistent.
template <typename T>
void ExpectCheckedAdd(T x, T y, bool expectedOverflow, T expectedZ) {
  T z = static_cast<T>(0x7);  // sentinel
  const bool overflow = checkedAdd<T>(x, y, &z);
  EXPECT_EQ(overflow, expectedOverflow);
  if (!expectedOverflow) {
    EXPECT_EQ(z, expectedZ);
  }
}

}  // namespace

// -------------------------
// Normal operation
// -------------------------

TEST(GooCheckedOpsCheckedAddTest_53, AddsSmallPositiveIntegers_53) {
  ExpectCheckedAdd<int>(1, 2, /*expectedOverflow=*/false, /*expectedZ=*/3);
  ExpectCheckedAdd<int>(0, 0, /*expectedOverflow=*/false, /*expectedZ=*/0);
  ExpectCheckedAdd<int>(42, 58, /*expectedOverflow=*/false, /*expectedZ=*/100);
}

TEST(GooCheckedOpsCheckedAddTest_53, AddsWithNegativeOperandsNoOverflow_53) {
  ExpectCheckedAdd<int>(-1, -2, /*expectedOverflow=*/false, /*expectedZ=*/-3);
  ExpectCheckedAdd<int>(-10, 3, /*expectedOverflow=*/false, /*expectedZ=*/-7);
  ExpectCheckedAdd<int>(10, -3, /*expectedOverflow=*/false, /*expectedZ=*/7);
}

TEST(GooCheckedOpsCheckedAddTest_53, AddsUnsignedNoOverflow_53) {
  using U = std::uint32_t;
  ExpectCheckedAdd<U>(1u, 2u, /*expectedOverflow=*/false, /*expectedZ=*/3u);
  ExpectCheckedAdd<U>(0u, 123u, /*expectedOverflow=*/false, /*expectedZ=*/123u);
}

// -------------------------
// Boundary conditions
// -------------------------

TEST(GooCheckedOpsCheckedAddTest_53, BoundarySignedMaxNoOverflow_53) {
  using T = int;
  const T mx = std::numeric_limits<T>::max();
  ExpectCheckedAdd<T>(mx, 0, /*expectedOverflow=*/false, /*expectedZ=*/mx);
  ExpectCheckedAdd<T>(mx - 1, 1, /*expectedOverflow=*/false, /*expectedZ=*/mx);
}

TEST(GooCheckedOpsCheckedAddTest_53, BoundarySignedMinNoOverflow_53) {
  using T = int;
  const T mn = std::numeric_limits<T>::min();
  ExpectCheckedAdd<T>(mn, 0, /*expectedOverflow=*/false, /*expectedZ=*/mn);
  ExpectCheckedAdd<T>(mn + 1, -1, /*expectedOverflow=*/false, /*expectedZ=*/mn);
}

TEST(GooCheckedOpsCheckedAddTest_53, BoundaryUnsignedMaxNoOverflow_53) {
  using T = std::uint32_t;
  const T mx = std::numeric_limits<T>::max();
  ExpectCheckedAdd<T>(mx, 0u, /*expectedOverflow=*/false, /*expectedZ=*/mx);
}

// -------------------------
// Exceptional / error cases (overflow) - observable via return value
// -------------------------

TEST(GooCheckedOpsCheckedAddTest_53, DetectsSignedPositiveOverflow_53) {
  using T = int;
  const T mx = std::numeric_limits<T>::max();
  T z = 0;
  const bool overflow = checkedAdd<T>(mx, 1, &z);
  EXPECT_TRUE(overflow);
}

TEST(GooCheckedOpsCheckedAddTest_53, DetectsSignedNegativeOverflow_53) {
  using T = int;
  const T mn = std::numeric_limits<T>::min();
  T z = 0;
  const bool overflow = checkedAdd<T>(mn, -1, &z);
  EXPECT_TRUE(overflow);
}

TEST(GooCheckedOpsCheckedAddTest_53, DetectsUnsignedOverflow_53) {
  using T = std::uint32_t;
  const T mx = std::numeric_limits<T>::max();
  T z = 0;
  const bool overflow = checkedAdd<T>(mx, 1u, &z);
  EXPECT_TRUE(overflow);
}

TEST(GooCheckedOpsCheckedAddTest_53, DetectsOverflowForSmallWidthTypes_53) {
  // Exercise narrow integer types where overflow is common.
  using S8 = std::int8_t;
  using U8 = std::uint8_t;

  {
    S8 z = 0;
    const bool overflow = checkedAdd<S8>(std::numeric_limits<S8>::max(), static_cast<S8>(1), &z);
    EXPECT_TRUE(overflow);
  }
  {
    U8 z = 0;
    const bool overflow = checkedAdd<U8>(std::numeric_limits<U8>::max(), static_cast<U8>(1), &z);
    EXPECT_TRUE(overflow);
  }
}

// -------------------------
// Interface robustness
// -------------------------

TEST(GooCheckedOpsCheckedAddTest_53, WritesResultWhenNoOverflow_53) {
  using T = long long;
  T z = 0;
  const bool overflow = checkedAdd<T>(123, 456, &z);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, 579);
}

TEST(GooCheckedOpsCheckedAddTest_53, DoesNotCrashWithValidPointer_53) {
  // Minimal sanity check for pointer usage; nullptr behavior is not specified,
  // so we do not test passing nullptr.
  int z = 0;
  EXPECT_NO_THROW({
    (void)checkedAdd<int>(1, 1, &z);
  });
}