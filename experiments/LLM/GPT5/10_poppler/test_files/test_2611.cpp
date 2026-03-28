// File: splash_imgCoordMungeLower_test_2611.cc
//
// Unit tests for the small inline helper and related macro in:
//   ./TestProjects/poppler/splash/Splash.cc
//
// NOTE: The function under test is declared `static inline` in the .cc file,
// so we include the implementation file to make it visible in this test TU.
// This does NOT re-implement logic; it only allows calling the already-defined
// function as a black box.

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <type_traits>

// Make the static inline helper visible in this translation unit.
#include "TestProjects/poppler/splash/Splash.cc"

namespace {

class SplashImgCoordMungeLowerTest_2611 : public ::testing::Test {};

TEST_F(SplashImgCoordMungeLowerTest_2611, SplashAAGammaIsDefinedAndExpectedValue_2611) {
  // Observable behavior: macro expands to a numeric literal usable as a double.
  EXPECT_DOUBLE_EQ(static_cast<double>(splashAAGamma), 1.5);
  EXPECT_GT(static_cast<double>(splashAAGamma), 0.0);
}

TEST_F(SplashImgCoordMungeLowerTest_2611, ImgCoordMungeLowerMatchesSplashFloorForTypicalValues_2611) {
  // Observable behavior from provided interface: imgCoordMungeLower(x) returns splashFloor(x).
  const SplashCoord values[] = {
      static_cast<SplashCoord>(0),
      static_cast<SplashCoord>(1),
      static_cast<SplashCoord>(-1),
      static_cast<SplashCoord>(1.25),
      static_cast<SplashCoord>(-1.25),
      static_cast<SplashCoord>(123456.789),
      static_cast<SplashCoord>(-123456.789),
  };

  for (SplashCoord x : values) {
    EXPECT_EQ(imgCoordMungeLower(x), splashFloor(x)) << "x=" << static_cast<double>(x);
  }
}

TEST_F(SplashImgCoordMungeLowerTest_2611, ImgCoordMungeLowerMatchesSplashFloorNearIntegerBoundaries_2611) {
  // Boundary conditions around an integer value.
  // We do not assume what splashFloor does internally; we only assert equivalence.
  const SplashCoord base = static_cast<SplashCoord>(2);

  // Use a small delta based on the value's magnitude.
  const SplashCoord delta = static_cast<SplashCoord>(1e-6);

  const SplashCoord values[] = {
      base,
      static_cast<SplashCoord>(base + delta),
      static_cast<SplashCoord>(base - delta),
      static_cast<SplashCoord>(-base),
      static_cast<SplashCoord>(-base + delta),
      static_cast<SplashCoord>(-base - delta),
  };

  for (SplashCoord x : values) {
    EXPECT_EQ(imgCoordMungeLower(x), splashFloor(x)) << "x=" << static_cast<double>(x);
  }
}

TEST_F(SplashImgCoordMungeLowerTest_2611, ImgCoordMungeLowerMatchesSplashFloorForInfinityAndNaNWhenSupported_2611) {
  // Exceptional / special floating values, if SplashCoord is floating-point.
  if constexpr (std::is_floating_point_v<SplashCoord>) {
    const SplashCoord pos_inf = std::numeric_limits<SplashCoord>::infinity();
    const SplashCoord neg_inf = -std::numeric_limits<SplashCoord>::infinity();
    const SplashCoord nan = std::numeric_limits<SplashCoord>::quiet_NaN();

    EXPECT_EQ(imgCoordMungeLower(pos_inf), splashFloor(pos_inf));
    EXPECT_EQ(imgCoordMungeLower(neg_inf), splashFloor(neg_inf));

    // For NaN, equality comparisons are false; check "both are NaN" if applicable.
    const auto out1 = imgCoordMungeLower(nan);
    const auto out2 = splashFloor(nan);
    EXPECT_EQ(std::isnan(static_cast<double>(out1)), std::isnan(static_cast<double>(out2)));
  } else {
    GTEST_SKIP() << "SplashCoord is not floating-point; Infinity/NaN tests not applicable.";
  }
}

}  // namespace