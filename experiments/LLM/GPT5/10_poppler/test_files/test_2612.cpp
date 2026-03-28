// File: splash_imgCoordMungeUpper_test_2612.cc
#include <gtest/gtest.h>

#include <cmath>
#include <limits>

// We include the implementation file to access the TU-local `static inline` helper.
// This is intentional: the function has internal linkage and is not exposed via headers.
#include "./TestProjects/poppler/splash/Splash.cc"

namespace {

class ImgCoordMungeUpperTest_2612 : public ::testing::Test {};

TEST_F(ImgCoordMungeUpperTest_2612, ZeroReturnsOne_2612) {
  const SplashCoord x = static_cast<SplashCoord>(0);
  EXPECT_EQ(imgCoordMungeUpper(x), 1);
}

TEST_F(ImgCoordMungeUpperTest_2612, PositiveIntegerReturnsNextInteger_2612) {
  const SplashCoord x = static_cast<SplashCoord>(5);
  EXPECT_EQ(imgCoordMungeUpper(x), 6);
}

TEST_F(ImgCoordMungeUpperTest_2612, NegativeIntegerReturnsPlusOne_2612) {
  const SplashCoord x = static_cast<SplashCoord>(-2);
  EXPECT_EQ(imgCoordMungeUpper(x), -1);
}

TEST_F(ImgCoordMungeUpperTest_2612, PositiveFractionRoundsDownThenPlusOne_2612) {
  const SplashCoord x = static_cast<SplashCoord>(3.25);
  EXPECT_EQ(imgCoordMungeUpper(x), 4);
}

TEST_F(ImgCoordMungeUpperTest_2612, JustBelowAndJustAboveIntegerBoundary_2612) {
  const SplashCoord three = static_cast<SplashCoord>(3.0);

  // Value just below 3.0 should map to (floor(2.999..)+1) == 3
  const SplashCoord just_below =
      std::nextafter(three, -std::numeric_limits<SplashCoord>::infinity());
  EXPECT_EQ(imgCoordMungeUpper(just_below), 3);

  // Exactly 3.0 should map to 4.
  EXPECT_EQ(imgCoordMungeUpper(three), 4);

  // Value just above 3.0 should also map to 4.
  const SplashCoord just_above =
      std::nextafter(three, std::numeric_limits<SplashCoord>::infinity());
  EXPECT_EQ(imgCoordMungeUpper(just_above), 4);
}

TEST_F(ImgCoordMungeUpperTest_2612, LargeMagnitudeValuesDoNotCrash_2612) {
  // This test is intentionally minimal: it checks that calling the function on
  // large finite values is safe and produces a deterministic int.
  const SplashCoord big_pos = static_cast<SplashCoord>(1e9);
  const SplashCoord big_neg = static_cast<SplashCoord>(-1e9);

  const int r1 = imgCoordMungeUpper(big_pos);
  const int r2 = imgCoordMungeUpper(big_neg);

  // Basic sanity: results should be finite ints; also ensure they are stable.
  EXPECT_EQ(r1, imgCoordMungeUpper(big_pos));
  EXPECT_EQ(r2, imgCoordMungeUpper(big_neg));
}

}  // namespace