// File: test_tags_int_exposureTime_1375.cpp
// Unit tests for Exiv2::Internal::exposureTime(float)
//
// TEST_ID: 1375

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <limits>

// Exiv2 public types (URational) + internal function under test.
// Adjust include paths if your build uses different include roots.
#include <exiv2/types.hpp>
#include "tags_int.hpp"

namespace {

using Exiv2::URational;

static void ExpectURationalEq(const URational& actual, uint32_t expected_num, uint32_t expected_den) {
  // URational in Exiv2 is typically a rational pair (numerator/denominator).
  // We only assert observable public fields.
  EXPECT_EQ(actual.first, expected_num);
  EXPECT_EQ(actual.second, expected_den);
}

class ExposureTimeTest_1375 : public ::testing::Test {};

}  // namespace

TEST_F(ExposureTimeTest_1375, ZeroReturnsOneOverOne_1375) {
  const URational r = Exiv2::Internal::exposureTime(0.0f);
  ExpectURationalEq(r, 1u, 1u);
}

TEST_F(ExposureTimeTest_1375, PositiveOneReturnsOneOverTwo_1375) {
  // Common shutter speed value mapping: 1 -> 1/2
  const URational r = Exiv2::Internal::exposureTime(1.0f);
  ExpectURationalEq(r, 1u, 2u);
}

TEST_F(ExposureTimeTest_1375, NegativeOneReturnsTwoOverOne_1375) {
  // -1 -> 2/1
  const URational r = Exiv2::Internal::exposureTime(-1.0f);
  ExpectURationalEq(r, 2u, 1u);
}

TEST_F(ExposureTimeTest_1375, PositiveTwoReturnsOneOverFour_1375) {
  const URational r = Exiv2::Internal::exposureTime(2.0f);
  ExpectURationalEq(r, 1u, 4u);
}

TEST_F(ExposureTimeTest_1375, NegativeTwoReturnsFourOverOne_1375) {
  const URational r = Exiv2::Internal::exposureTime(-2.0f);
  ExpectURationalEq(r, 4u, 1u);
}

TEST_F(ExposureTimeTest_1375, FractionalValueRoundsToNearestDenominator_1375) {
  // Uses exp2(shutterSpeedValue) and rounding; check a value that rounds up.
  // 0.9 => exp2(0.9) ~= 1.866..., rounds to 2 => 1/2
  const URational r = Exiv2::Internal::exposureTime(0.9f);
  ExpectURationalEq(r, 1u, 2u);
}

TEST_F(ExposureTimeTest_1375, FractionalValueRoundsToNearestOne_1375) {
  // 0.5 => exp2(0.5) ~= 1.414..., rounds to 1 => 1/1
  const URational r = Exiv2::Internal::exposureTime(0.5f);
  ExpectURationalEq(r, 1u, 1u);
}

TEST_F(ExposureTimeTest_1375, VeryLargePositiveDoesNotOverflowAndFallsBackToOneOverOne_1375) {
  // Extremely large values can produce a result not representable in uint32_t;
  // observable behavior should be a safe fallback rational.
  const URational r = Exiv2::Internal::exposureTime(std::numeric_limits<float>::max());
  ExpectURationalEq(r, 1u, 1u);
}

TEST_F(ExposureTimeTest_1375, VeryLargeNegativeDoesNotOverflowAndFallsBackToOneOverOne_1375) {
  const URational r = Exiv2::Internal::exposureTime(-std::numeric_limits<float>::max());
  ExpectURationalEq(r, 1u, 1u);
}

TEST_F(ExposureTimeTest_1375, PositiveInfinityFallsBackToOneOverOne_1375) {
  const float inf = std::numeric_limits<float>::infinity();
  const URational r = Exiv2::Internal::exposureTime(inf);
  ExpectURationalEq(r, 1u, 1u);
}

TEST_F(ExposureTimeTest_1375, NegativeInfinityFallsBackToOneOverOne_1375) {
  const float ninf = -std::numeric_limits<float>::infinity();
  const URational r = Exiv2::Internal::exposureTime(ninf);
  ExpectURationalEq(r, 1u, 1u);
}

TEST_F(ExposureTimeTest_1375, NaNFallsBackToOneOverOne_1375) {
  const float nanv = std::numeric_limits<float>::quiet_NaN();
  const URational r = Exiv2::Internal::exposureTime(nanv);
  ExpectURationalEq(r, 1u, 1u);
}

TEST_F(ExposureTimeTest_1375, NegativeZeroBehavesSameAsZero_1375) {
  const URational r_pos0 = Exiv2::Internal::exposureTime(0.0f);
  const URational r_neg0 = Exiv2::Internal::exposureTime(-0.0f);
  EXPECT_EQ(r_pos0.first, r_neg0.first);
  EXPECT_EQ(r_pos0.second, r_neg0.second);
  ExpectURationalEq(r_neg0, 1u, 1u);
}