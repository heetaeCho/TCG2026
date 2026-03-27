// SPDX-License-Identifier: MIT
//
// Unit tests for ./TestProjects/poppler/goo/GooCheckedOps.h
// Focus: checkedMultiply(T x, T y, T* z)
//
// Constraints honored:
// - Black-box testing via observable return value + output parameter
// - No assumptions about internal implementation details
//
// NOTE: This is a header-only inline template helper. These tests validate
// general, interface-observable behavior: whether it reports overflow and
// whether it writes to *z on success.

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

namespace {

// Helper: for signed/unsigned integrals, compute "expected" overflow behavior
// using a wider intermediate type where possible, without relying on the
// implementation of checkedMultiply.
template <typename T>
struct Wider;

template <>
struct Wider<int8_t> {
  using type = int64_t;
};
template <>
struct Wider<uint8_t> {
  using type = uint64_t;
};
template <>
struct Wider<int16_t> {
  using type = int64_t;
};
template <>
struct Wider<uint16_t> {
  using type = uint64_t;
};
template <>
struct Wider<int32_t> {
  using type = int64_t;
};
template <>
struct Wider<uint32_t> {
  using type = uint64_t;
};
template <>
struct Wider<int64_t> {
#if defined(__SIZEOF_INT128__)
  using type = __int128_t;
#else
  using type = long double;  // fallback: used only for boundary-ish checks
#endif
};
template <>
struct Wider<uint64_t> {
#if defined(__SIZEOF_INT128__)
  using type = __uint128_t;
#else
  using type = long double;
#endif
};

template <typename T>
using WiderT = typename Wider<T>::type;

template <typename T>
bool computeExpectedMultiply(T x, T y, T* out) {
  static_assert(std::is_integral_v<T>, "Integral types only for this helper");
  using W = WiderT<T>;

  // Use a widened multiply and check if it fits into T.
  const W wx = static_cast<W>(x);
  const W wy = static_cast<W>(y);
  const W wprod = wx * wy;

  const W wmin = static_cast<W>(std::numeric_limits<T>::min());
  const W wmax = static_cast<W>(std::numeric_limits<T>::max());

  if (wprod < wmin || wprod > wmax) {
    return true;  // overflow expected
  }
  *out = static_cast<T>(wprod);
  return false;
}

}  // namespace

// Include the header under test *after* helpers (safe either way).
#include "./TestProjects/poppler/goo/GooCheckedOps.h"

class GooCheckedOpsCheckedMultiplyTest_25 : public ::testing::Test {};

// -------------------- Normal operation --------------------

TEST_F(GooCheckedOpsCheckedMultiplyTest_25, MultipliesSmallPositiveValues_NoOverflow_25) {
  int32_t z = -1;
  const bool overflow = checkedMultiply<int32_t>(6, 7, &z);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, 42);
}

TEST_F(GooCheckedOpsCheckedMultiplyTest_25, MultipliesWithZero_NoOverflowAndResultZero_25) {
  int32_t z = 1234;
  const bool overflow = checkedMultiply<int32_t>(0, 999, &z);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, 0);
}

TEST_F(GooCheckedOpsCheckedMultiplyTest_25, MultipliesNegativeAndPositive_NoOverflow_25) {
  int32_t z = 0;
  const bool overflow = checkedMultiply<int32_t>(-8, 5, &z);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, -40);
}

// -------------------- Boundary conditions --------------------

TEST_F(GooCheckedOpsCheckedMultiplyTest_25, Unsigned_MaxTimesOne_NoOverflow_25) {
  uint32_t z = 0;
  const uint32_t maxv = std::numeric_limits<uint32_t>::max();
  const bool overflow = checkedMultiply<uint32_t>(maxv, 1u, &z);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, maxv);
}

TEST_F(GooCheckedOpsCheckedMultiplyTest_25, Signed_MaxTimesOne_NoOverflow_25) {
  int32_t z = 0;
  const int32_t maxv = std::numeric_limits<int32_t>::max();
  const bool overflow = checkedMultiply<int32_t>(maxv, 1, &z);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, maxv);
}

TEST_F(GooCheckedOpsCheckedMultiplyTest_25, Signed_MinTimesOne_NoOverflow_25) {
  int32_t z = 0;
  const int32_t minv = std::numeric_limits<int32_t>::min();
  const bool overflow = checkedMultiply<int32_t>(minv, 1, &z);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, minv);
}

// -------------------- Exceptional / error cases (overflow observable) --------------------

TEST_F(GooCheckedOpsCheckedMultiplyTest_25, Signed_MaxTimesTwo_ReportsOverflow_25) {
  int32_t z = 777;  // sentinel; on overflow, output may or may not change
  const int32_t maxv = std::numeric_limits<int32_t>::max();
  const bool overflow = checkedMultiply<int32_t>(maxv, 2, &z);
  EXPECT_TRUE(overflow);
}

TEST_F(GooCheckedOpsCheckedMultiplyTest_25, Unsigned_MaxTimesTwo_ReportsOverflow_25) {
  uint32_t z = 777u;
  const uint32_t maxv = std::numeric_limits<uint32_t>::max();
  const bool overflow = checkedMultiply<uint32_t>(maxv, 2u, &z);
  EXPECT_TRUE(overflow);
}

TEST_F(GooCheckedOpsCheckedMultiplyTest_25, Signed_MinTimesMinusOne_ReportsOverflow_25) {
  int32_t z = 123;
  const int32_t minv = std::numeric_limits<int32_t>::min();
  const bool overflow = checkedMultiply<int32_t>(minv, -1, &z);
  EXPECT_TRUE(overflow);
}

// -------------------- Cross-check vs mathematically expected outcome --------------------
// This stays black-box: we compute expected overflow/result independently and compare.

TEST_F(GooCheckedOpsCheckedMultiplyTest_25, MatchesExpectedForSeveralInt16Pairs_25) {
  struct Case {
    int16_t x;
    int16_t y;
  };
  const Case cases[] = {
      {0, 0},
      {1, 1},
      {2, 3},
      {-2, 3},
      {-300, 100},
      {std::numeric_limits<int16_t>::max(), 1},
      {std::numeric_limits<int16_t>::max(), 2},   // overflow
      {std::numeric_limits<int16_t>::min(), 1},
      {std::numeric_limits<int16_t>::min(), -1},  // overflow
  };

  for (const auto& c : cases) {
    int16_t expected = 0;
    const bool expectedOverflow = computeExpectedMultiply<int16_t>(c.x, c.y, &expected);

    int16_t z = 0x7B;  // sentinel
    const bool overflow = checkedMultiply<int16_t>(c.x, c.y, &z);

    EXPECT_EQ(overflow, expectedOverflow) << "x=" << c.x << " y=" << c.y;
    if (!overflow) {
      EXPECT_EQ(z, expected) << "x=" << c.x << " y=" << c.y;
    }
  }
}

TEST_F(GooCheckedOpsCheckedMultiplyTest_25, MatchesExpectedForSeveralUInt16Pairs_25) {
  struct Case {
    uint16_t x;
    uint16_t y;
  };
  const Case cases[] = {
      {0u, 0u},
      {1u, 1u},
      {2u, 3u},
      {100u, 200u},
      {std::numeric_limits<uint16_t>::max(), 1u},
      {std::numeric_limits<uint16_t>::max(), 2u},  // overflow
  };

  for (const auto& c : cases) {
    uint16_t expected = 0;
    const bool expectedOverflow = computeExpectedMultiply<uint16_t>(c.x, c.y, &expected);

    uint16_t z = 0xBEEF;  // sentinel
    const bool overflow = checkedMultiply<uint16_t>(c.x, c.y, &z);

    EXPECT_EQ(overflow, expectedOverflow) << "x=" << c.x << " y=" << c.y;
    if (!overflow) {
      EXPECT_EQ(z, expected) << "x=" << c.x << " y=" << c.y;
    }
  }
}

// -------------------- Defensive usage (null out pointer) --------------------
// The interface requires T* z. Behavior for nullptr is not specified.
// We avoid calling with nullptr to prevent UB. This test just documents that
// our test suite never passes nullptr.

TEST_F(GooCheckedOpsCheckedMultiplyTest_25, DoesNotInvokeWithNullOutputPointer_25) {
  SUCCEED();
}