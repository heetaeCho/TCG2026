// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 858
//
// Unit tests for Exiv2::LangAltValue::toInt64(size_t)
//
// Constraints respected:
// - Treat implementation as a black box (test only observable behavior).
// - No private state access (e.g., ok_).
// - Cover normal, boundary, and observable error/exception cases.

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <limits>

#include <exiv2/value.hpp>

namespace {

using Exiv2::LangAltValue;

TEST(LangAltValueTest_858, ToInt64ReturnsAStableValueForIndex0_858) {
  LangAltValue v;
  EXPECT_NO_THROW({
    const int64_t r = v.toInt64(0);
    // Observable behavior from interface: returns an int64_t value.
    // The partial implementation returns 0, so we assert that behavior.
    EXPECT_EQ(0, r);
  });
}

TEST(LangAltValueTest_858, ToInt64ReturnsAStableValueForSmallPositiveIndex_858) {
  LangAltValue v;

  const int64_t r1 = v.toInt64(1);
  const int64_t r2 = v.toInt64(2);

  EXPECT_EQ(0, r1);
  EXPECT_EQ(0, r2);
}

TEST(LangAltValueTest_858, ToInt64AcceptsLargeIndexWithoutThrowing_858) {
  LangAltValue v;
  const size_t big = (std::numeric_limits<size_t>::max)();

  EXPECT_NO_THROW({
    const int64_t r = v.toInt64(big);
    EXPECT_EQ(0, r);
  });
}

TEST(LangAltValueTest_858, ToInt64IsCallableOnConstObject_858) {
  const LangAltValue v;

  EXPECT_NO_THROW({
    const int64_t r = v.toInt64(0);
    EXPECT_EQ(0, r);
  });
}

TEST(LangAltValueTest_858, ToInt64IsDeterministicAcrossMultipleCalls_858) {
  LangAltValue v;

  const int64_t a = v.toInt64(0);
  const int64_t b = v.toInt64(0);
  const int64_t c = v.toInt64(123);

  EXPECT_EQ(a, b);
  EXPECT_EQ(0, a);
  EXPECT_EQ(0, c);
}

}  // namespace