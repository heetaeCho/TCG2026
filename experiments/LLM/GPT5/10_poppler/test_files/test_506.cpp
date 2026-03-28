// SPDX-License-Identifier: GPL-2.0-or-later
// File: GfxShading_getBBox_506_test.cc

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

// These tests treat GfxShading as a black box from the perspective of behavior.
// To make the behavior observable for getBBox (which only reports internal bbox values),
// we use a derived test helper that *only* sets the bbox inputs and then validates
// the public getBBox() output. No internal logic is re-implemented.

namespace {

// Test helper to provide controlled bbox values for exercising the public API.
class TestableGfxShading_506 final : public GfxShading {
public:
  explicit TestableGfxShading_506(int typeA) : GfxShading(typeA) {}

  void setBBox(double xMin, double yMin, double xMax, double yMax) {
    bbox_xMin = xMin;
    bbox_yMin = yMin;
    bbox_xMax = xMax;
    bbox_yMax = yMax;
  }
};

class GfxShadingTest_506 : public ::testing::Test {
protected:
  TestableGfxShading_506 shading{0};
};

} // namespace

TEST_F(GfxShadingTest_506, GetBBoxWritesAllOutputs_506) {
  shading.setBBox(1.25, -2.5, 10.0, 20.5);

  double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
  shading.getBBox(&xMin, &yMin, &xMax, &yMax);

  EXPECT_DOUBLE_EQ(xMin, 1.25);
  EXPECT_DOUBLE_EQ(yMin, -2.5);
  EXPECT_DOUBLE_EQ(xMax, 10.0);
  EXPECT_DOUBLE_EQ(yMax, 20.5);
}

TEST_F(GfxShadingTest_506, GetBBoxWorksOnConstObject_506) {
  shading.setBBox(-1.0, -2.0, -3.0, -4.0);

  const GfxShading &constRef = shading;

  double xMin = 123, yMin = 456, xMax = 789, yMax = 321;
  constRef.getBBox(&xMin, &yMin, &xMax, &yMax);

  EXPECT_DOUBLE_EQ(xMin, -1.0);
  EXPECT_DOUBLE_EQ(yMin, -2.0);
  EXPECT_DOUBLE_EQ(xMax, -3.0);
  EXPECT_DOUBLE_EQ(yMax, -4.0);
}

TEST_F(GfxShadingTest_506, GetBBoxSupportsAliasedOutputPointers_506) {
  // Boundary/robustness: caller provides the same address for multiple outputs.
  // Observable behavior: writes occur in order; final value is last assigned.
  shading.setBBox(11.0, 22.0, 33.0, 44.0);

  double v = 0.0;
  shading.getBBox(&v, &v, &v, &v);

  // Assigned in order: xMin -> yMin -> xMax -> yMax, so the final value should be yMax.
  EXPECT_DOUBLE_EQ(v, 44.0);
}

TEST_F(GfxShadingTest_506, GetBBoxHandlesLargeMagnitudeValues_506) {
  // Boundary: large/small magnitudes and sign.
  shading.setBBox(1e300, -1e300, 1e-300, -1e-300);

  double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
  shading.getBBox(&xMin, &yMin, &xMax, &yMax);

  EXPECT_DOUBLE_EQ(xMin, 1e300);
  EXPECT_DOUBLE_EQ(yMin, -1e300);
  EXPECT_DOUBLE_EQ(xMax, 1e-300);
  EXPECT_DOUBLE_EQ(yMax, -1e-300);
}

TEST_F(GfxShadingTest_506, GetBBoxPreservesSignedZero_506) {
  // Boundary: signed zero can matter in floating computations; ensure pass-through.
  shading.setBBox(-0.0, 0.0, -0.0, 0.0);

  double xMin = 1, yMin = 1, xMax = 1, yMax = 1;
  shading.getBBox(&xMin, &yMin, &xMax, &yMax);

  EXPECT_DOUBLE_EQ(xMin, -0.0);
  EXPECT_DOUBLE_EQ(yMin, 0.0);
  EXPECT_DOUBLE_EQ(xMax, -0.0);
  EXPECT_DOUBLE_EQ(yMax, 0.0);

  // Optional extra observability: signbit distinguishes -0.0 vs +0.0.
  EXPECT_TRUE(std::signbit(xMin));
  EXPECT_FALSE(std::signbit(yMin));
  EXPECT_TRUE(std::signbit(xMax));
  EXPECT_FALSE(std::signbit(yMax));
}