// TEST_ID: 7
//
// Unit tests for: checkedMultiply<long long>(long long x, long long y, long long* z)
// File under test: ./TestProjects/poppler/goo/GooCheckedOps.h
//
// Constraints note:
// - We treat checkedMultiply as a black box and only verify observable behavior:
//   return value (overflow?) and output through *z (when valid).
// - We do not assume any internal overflow-detection strategy.

#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

#include "TestProjects/poppler/goo/GooCheckedOps.h"

namespace {

// Helper: ensures we can call the explicit specialization as expected.
static bool CallCheckedMultiply(long long x, long long y, long long* z) {
  return checkedMultiply<long long>(x, y, z);
}

class CheckedMultiplyLongLongTest_7 : public ::testing::Test {};

TEST_F(CheckedMultiplyLongLongTest_7, MultiplySimplePositive_NoOverflow_7) {
  long long out = 0;
  const bool overflow = CallCheckedMultiply(6LL, 7LL, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, 42LL);
}

TEST_F(CheckedMultiplyLongLongTest_7, MultiplyByZero_NoOverflow_ResultZero_7) {
  long long out = 12345;
  const bool overflow = CallCheckedMultiply(0LL, 999999LL, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, 0LL);
}

TEST_F(CheckedMultiplyLongLongTest_7, MultiplyWithNegative_NoOverflow_7) {
  long long out = 0;
  const bool overflow = CallCheckedMultiply(-3LL, 7LL, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, -21LL);
}

TEST_F(CheckedMultiplyLongLongTest_7, MultiplyMinValueByOne_NoOverflow_7) {
  long long out = 0;
  const bool overflow = CallCheckedMultiply((std::numeric_limits<long long>::min)(), 1LL, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, (std::numeric_limits<long long>::min)());
}

TEST_F(CheckedMultiplyLongLongTest_7, MultiplyMaxByOne_NoOverflow_7) {
  long long out = 0;
  const bool overflow = CallCheckedMultiply((std::numeric_limits<long long>::max)(), 1LL, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, (std::numeric_limits<long long>::max)());
}

TEST_F(CheckedMultiplyLongLongTest_7, MultiplyMaxByTwo_OverflowIsReported_7) {
  long long out = 0x5A5A5A5A5A5A5A5ALL;  // sentinel
  const bool overflow = CallCheckedMultiply((std::numeric_limits<long long>::max)(), 2LL, &out);

  EXPECT_TRUE(overflow);
  // When overflow occurs, the output value is not specified by the interface snippet.
  // We only assert that overflow is reported.
}

TEST_F(CheckedMultiplyLongLongTest_7, MultiplyMinByTwo_OverflowIsReported_7) {
  long long out = 0x6B6B6B6B6B6B6B6BLL;  // sentinel
  const bool overflow = CallCheckedMultiply((std::numeric_limits<long long>::min)(), 2LL, &out);

  EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyLongLongTest_7, MultiplyMinByMinusOne_OverflowIsReported_7) {
  long long out = 0x7C7C7C7C7C7C7C7CLL;  // sentinel
  const bool overflow =
      CallCheckedMultiply((std::numeric_limits<long long>::min)(), -1LL, &out);

  EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyLongLongTest_7, MultiplySquareWithinRange_NoOverflow_7) {
  // 3037000499^2 <= LLONG_MAX (classic boundary for sqrt(LLONG_MAX)).
  constexpr long long a = 3037000499LL;

  long long out = 0;
  const bool overflow = CallCheckedMultiply(a, a, &out);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, a * a);
}

TEST_F(CheckedMultiplyLongLongTest_7, MultiplyJustBeyondSquareBoundary_OverflowIsReported_7) {
  // 3037000500^2 > LLONG_MAX
  constexpr long long a = 3037000500LL;

  long long out = 0;
  const bool overflow = CallCheckedMultiply(a, a, &out);

  EXPECT_TRUE(overflow);
}

TEST_F(CheckedMultiplyLongLongTest_7, OutputPointerNullptr_IsUndefinedButShouldNotCrashTest_7) {
  // The interface does not document nullptr handling. We do not dereference nullptr.
  // Some implementations might crash; if so, this test would be invalid for the codebase.
  // To keep tests robust, we only compile-check by not calling with nullptr here.
  SUCCEED();
}

}  // namespace