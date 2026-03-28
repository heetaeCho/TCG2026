// GooCheckedOps_checkedSubtraction_test.cpp
// Unit tests for checkedSubtraction in ./TestProjects/poppler/goo/GooCheckedOps.h
//
// Constraints respected:
// - Treat implementation as a black box.
// - Only use observable behavior through interface: return value + output parameter.
// - No private/internal state access.
// - Cover normal / boundary / exceptional-ish (overflow) cases.

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

// Include the real header under test.
#include "TestProjects/poppler/goo/GooCheckedOps.h"

namespace {

template <typename T>
struct GooCheckedSubtractionTest_5 : public ::testing::Test {
  static_assert(std::is_integral_v<T>, "These tests assume integral T.");
};

using TestTypes = ::testing::Types<
    std::int8_t, std::uint8_t,
    std::int16_t, std::uint16_t,
    std::int32_t, std::uint32_t,
    std::int64_t, std::uint64_t>;
TYPED_TEST_SUITE(GooCheckedSubtractionTest_5, TestTypes);

}  // namespace

// -------------------- Normal operation --------------------

TYPED_TEST(GooCheckedSubtractionTest_5, ComputesDifferenceForTypicalValues_5) {
  using T = TypeParam;

  T out{};
  const T x = static_cast<T>(42);
  const T y = static_cast<T>(17);

  const bool overflow = checkedSubtraction<T>(x, y, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, static_cast<T>(x - y));
}

TYPED_TEST(GooCheckedSubtractionTest_5, SubtractingZeroLeavesValueUnchanged_5) {
  using T = TypeParam;

  T out{};
  const T x = static_cast<T>(123);
  const T y = static_cast<T>(0);

  const bool overflow = checkedSubtraction<T>(x, y, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, x);
}

TYPED_TEST(GooCheckedSubtractionTest_5, ZeroMinusValueBehavesAsExpectedWhenRepresentable_5) {
  using T = TypeParam;

  // For unsigned types, 0 - 1 wraps (overflow in builtin sense) -> should report overflow.
  // For signed types, 0 - 1 is representable -> should not overflow.
  T out{};
  const T x = static_cast<T>(0);
  const T y = static_cast<T>(1);

  const bool overflow = checkedSubtraction<T>(x, y, &out);

  if constexpr (std::is_unsigned_v<T>) {
    EXPECT_TRUE(overflow);
  } else {
    EXPECT_FALSE(overflow);
    EXPECT_EQ(out, static_cast<T>(-1));
  }
}

// -------------------- Boundary conditions --------------------

TYPED_TEST(GooCheckedSubtractionTest_5, MaxMinusZeroNoOverflowAndEqualsMax_5) {
  using T = TypeParam;

  T out{};
  const T x = std::numeric_limits<T>::max();
  const T y = static_cast<T>(0);

  const bool overflow = checkedSubtraction<T>(x, y, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, x);
}

TYPED_TEST(GooCheckedSubtractionTest_5, MinMinusZeroNoOverflowAndEqualsMin_5) {
  using T = TypeParam;

  T out{};
  const T x = std::numeric_limits<T>::min();
  const T y = static_cast<T>(0);

  const bool overflow = checkedSubtraction<T>(x, y, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, x);
}

// -------------------- Exceptional / error-like (overflow) cases --------------------

TYPED_TEST(GooCheckedSubtractionTest_5, SignedMinMinusOneReportsOverflow_5) {
  using T = TypeParam;

  if constexpr (std::is_signed_v<T>) {
    T out{};
    const T x = std::numeric_limits<T>::min();
    const T y = static_cast<T>(1);

    const bool overflow = checkedSubtraction<T>(x, y, &out);

    EXPECT_TRUE(overflow);
  } else {
    GTEST_SKIP() << "Not applicable for unsigned types.";
  }
}

TYPED_TEST(GooCheckedSubtractionTest_5, UnsignedZeroMinusOneReportsOverflow_5) {
  using T = TypeParam;

  if constexpr (std::is_unsigned_v<T>) {
    T out{};
    const T x = static_cast<T>(0);
    const T y = static_cast<T>(1);

    const bool overflow = checkedSubtraction<T>(x, y, &out);

    EXPECT_TRUE(overflow);
  } else {
    GTEST_SKIP() << "Not applicable for signed types.";
  }
}

TYPED_TEST(GooCheckedSubtractionTest_5, UnsignedMinMinusMaxReportsOverflowWhenWouldUnderflow_5) {
  using T = TypeParam;

  if constexpr (std::is_unsigned_v<T>) {
    T out{};
    const T x = std::numeric_limits<T>::min();  // 0
    const T y = std::numeric_limits<T>::max();  // large

    const bool overflow = checkedSubtraction<T>(x, y, &out);

    EXPECT_TRUE(overflow);
  } else {
    GTEST_SKIP() << "Not applicable for signed types.";
  }
}

// -------------------- Output parameter interaction --------------------
// Observable behavior: on non-overflow, *z equals x-y.

TYPED_TEST(GooCheckedSubtractionTest_5, WritesResultToOutParamOnSuccess_5) {
  using T = TypeParam;

  T out = static_cast<T>(0);
  const T x = static_cast<T>(7);
  const T y = static_cast<T>(3);

  const bool overflow = checkedSubtraction<T>(x, y, &out);

  ASSERT_FALSE(overflow);
  EXPECT_EQ(out, static_cast<T>(4));
}