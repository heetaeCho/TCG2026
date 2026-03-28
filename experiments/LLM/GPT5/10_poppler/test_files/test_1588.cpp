// SplashOutputDev_getLum_1588_test.cc
#include <gtest/gtest.h>

// NOTE: getLum() is declared as `static` in SplashOutputDev.cc, so it has internal
// linkage. Including the implementation file makes the test and the function part
// of the same translation unit, allowing direct calls without changing production
// code.
//
// This is intended to test only the provided interface as a black box.
#include "SplashOutputDev.cc"

namespace {

class GetLumTest_1588 : public ::testing::Test {};

TEST_F(GetLumTest_1588, ZeroRGBReturnsZero_1588) {
  EXPECT_EQ(getLum(0, 0, 0), 0);
}

TEST_F(GetLumTest_1588, EqualRGBGivesSameOutputAsInputForCommonValues_1588) {
  // For a luminance function, grayscale inputs (r=g=b) should map back to the same
  // grayscale level.
  EXPECT_EQ(getLum(1, 1, 1), 1);
  EXPECT_EQ(getLum(2, 2, 2), 2);
  EXPECT_EQ(getLum(128, 128, 128), 128);
  EXPECT_EQ(getLum(255, 255, 255), 255);
}

TEST_F(GetLumTest_1588, OutputWithinByteRangeForCornerCases_1588) {
  // Boundary coverage for typical 8-bit channel extremes.
  const int vals[] = {0, 255};
  for (int r : vals) {
    for (int g : vals) {
      for (int b : vals) {
        const int lum = getLum(r, g, b);
        EXPECT_GE(lum, 0) << "r=" << r << " g=" << g << " b=" << b;
        EXPECT_LE(lum, 255) << "r=" << r << " g=" << g << " b=" << b;
      }
    }
  }
}

TEST_F(GetLumTest_1588, MonotonicNonDecreasingWhenIncreasingSingleChannel_1588) {
  // Observable property: increasing a single RGB component by 1 should not
  // decrease luminance (within common 8-bit input range).
  const int samples[] = {0, 1, 2, 10, 50, 127, 200, 254};

  for (int g : samples) {
    for (int b : samples) {
      for (int r : samples) {
        if (r < 255) {
          EXPECT_LE(getLum(r, g, b), getLum(r + 1, g, b))
              << "Increasing r decreased lum at r=" << r << " g=" << g << " b=" << b;
        }
        if (g < 255) {
          EXPECT_LE(getLum(r, g, b), getLum(r, g + 1, b))
              << "Increasing g decreased lum at r=" << r << " g=" << g << " b=" << b;
        }
        if (b < 255) {
          EXPECT_LE(getLum(r, g, b), getLum(r, g, b + 1))
              << "Increasing b decreased lum at r=" << r << " g=" << g << " b=" << b;
        }
      }
    }
  }
}

TEST_F(GetLumTest_1588, DeterministicForSameInputs_1588) {
  const int r = 12, g = 34, b = 56;
  const int a = getLum(r, g, b);
  const int c = getLum(r, g, b);
  EXPECT_EQ(a, c);
}

TEST_F(GetLumTest_1588, DifferentChannelsCanProduceDifferentLuminance_1588) {
  // Black-box check that changing which channel carries the same intensity can
  // change luminance (common for luminance conversions).
  const int v = 128;
  const int lr = getLum(v, 0, 0);
  const int lg = getLum(0, v, 0);
  const int lb = getLum(0, 0, v);

  // Require that not all three are identical.
  EXPECT_FALSE(lr == lg && lg == lb);
}

TEST_F(GetLumTest_1588, AcceptsOutOfRangeInputsWithoutCrashing_1588) {
  // Exceptional/error-ish inputs: function takes int, so ensure it is callable
  // for values outside typical 0..255 without fatal failures.
  (void)getLum(-1, 0, 0);
  (void)getLum(0, -1, 0);
  (void)getLum(0, 0, -1);
  (void)getLum(256, 0, 0);
  (void)getLum(0, 256, 0);
  (void)getLum(0, 0, 256);
  (void)getLum(1000, -500, 42);

  SUCCEED();
}

}  // namespace