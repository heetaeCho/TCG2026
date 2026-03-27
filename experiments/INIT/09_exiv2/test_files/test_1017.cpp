// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_minoltamn_int_inRange_1017.cpp
//
// Unit tests for ./TestProjects/exiv2/src/minoltamn_int.cpp (partial)
// NOTE: The function under test is a translation-unit-local (static) helper.
// To test it through its interface without accessing private state or re-implementing,
// we include the .cpp directly in this test TU to make the function callable here.

#include <gtest/gtest.h>

// Include the implementation file to access the TU-local `inRange` symbol.
// This is a common technique for testing internal helpers when no public API exists.
#include "minoltamn_int.cpp"

namespace {

class MinoltaMnIntTest_1017 : public ::testing::Test {};

TEST_F(MinoltaMnIntTest_1017, ReturnsTrueWhenValueEqualsMin_1017) {
  ASSERT_TRUE(Exiv2::Internal::inRange(0L, 0L, 10L));
}

TEST_F(MinoltaMnIntTest_1017, ReturnsTrueWhenValueEqualsMax_1017) {
  ASSERT_TRUE(Exiv2::Internal::inRange(10L, 0L, 10L));
}

TEST_F(MinoltaMnIntTest_1017, ReturnsTrueWhenValueInsideRange_1017) {
  ASSERT_TRUE(Exiv2::Internal::inRange(5L, 0L, 10L));
}

TEST_F(MinoltaMnIntTest_1017, ReturnsTrueWhenMinEqualsMaxAndValueEqualsThat_1017) {
  ASSERT_TRUE(Exiv2::Internal::inRange(7L, 7L, 7L));
}

TEST_F(MinoltaMnIntTest_1017, ReturnsFalseWhenValueBelowMin_1017) {
  ASSERT_FALSE(Exiv2::Internal::inRange(-1L, 0L, 10L));
}

TEST_F(MinoltaMnIntTest_1017, ReturnsFalseWhenValueAboveMax_1017) {
  ASSERT_FALSE(Exiv2::Internal::inRange(11L, 0L, 10L));
}

TEST_F(MinoltaMnIntTest_1017, ReturnsFalseWhenRangeIsInvertedMinGreaterThanMax_1017) {
  // Boundary/error-ish case: inverted range. Observable behavior should be consistent
  // with the interface (a boolean result).
  ASSERT_FALSE(Exiv2::Internal::inRange(5L, 10L, 0L));
  ASSERT_FALSE(Exiv2::Internal::inRange(10L, 10L, 0L));
  ASSERT_FALSE(Exiv2::Internal::inRange(0L, 10L, 0L));
}

TEST_F(MinoltaMnIntTest_1017, HandlesLargeMagnitudeValues_1017) {
  const long kMin = std::numeric_limits<long>::min();
  const long kMax = std::numeric_limits<long>::max();

  ASSERT_TRUE(Exiv2::Internal::inRange(0L, kMin, kMax));
  ASSERT_TRUE(Exiv2::Internal::inRange(kMin, kMin, kMax));
  ASSERT_TRUE(Exiv2::Internal::inRange(kMax, kMin, kMax));
}

TEST_F(MinoltaMnIntTest_1017, HandlesNegativeRanges_1017) {
  ASSERT_TRUE(Exiv2::Internal::inRange(-5L, -10L, -1L));
  ASSERT_TRUE(Exiv2::Internal::inRange(-10L, -10L, -1L));
  ASSERT_TRUE(Exiv2::Internal::inRange(-1L, -10L, -1L));
  ASSERT_FALSE(Exiv2::Internal::inRange(0L, -10L, -1L));
  ASSERT_FALSE(Exiv2::Internal::inRange(-11L, -10L, -1L));
}

}  // namespace