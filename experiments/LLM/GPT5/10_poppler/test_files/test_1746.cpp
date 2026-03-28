// ============================================================================
// Unit tests for CairoImageOutputDev::axialShadedFill (TEST_ID=1746)
// File: test_cairo_image_output_dev_axial_shaded_fill_1746.cc
// ============================================================================

#include <gtest/gtest.h>

#include "CairoOutputDev.h"

// The provided partial code shows this interface/implementation:
//
// class CairoImageOutputDev {
// public:
//   bool axialShadedFill(GfxState* /*state*/, GfxAxialShading* /*shading*/,
//                        double /*tMin*/, double /*tMax*/) override { return true; }
// };
//
// We treat it as a black box and only verify observable behavior via the public API.

namespace {

// A small fixture for consistency and potential future expansion.
class CairoImageOutputDevTest_1746 : public ::testing::Test {
protected:
  CairoImageOutputDev dev;
};

TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillReturnsTrueWithNullPointers_1746) {
  // Normal-ish usage from the interface perspective: method accepts pointers and doubles.
  // Observable behavior: returns a bool.
  EXPECT_TRUE(dev.axialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillReturnsTrueWithSameMinMax_1746) {
  // Boundary: tMin == tMax
  EXPECT_TRUE(dev.axialShadedFill(nullptr, nullptr, 0.5, 0.5));
}

TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillReturnsTrueWithReversedRange_1746) {
  // Boundary / potential error-ish input: tMin > tMax
  EXPECT_TRUE(dev.axialShadedFill(nullptr, nullptr, 2.0, -3.0));
}

TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillReturnsTrueWithLargeMagnitudes_1746) {
  // Boundary: very large magnitude doubles
  EXPECT_TRUE(dev.axialShadedFill(nullptr, nullptr, 1e308, -1e308));
}

TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillReturnsTrueWithNegativeRange_1746) {
  // Boundary: negative values
  EXPECT_TRUE(dev.axialShadedFill(nullptr, nullptr, -10.0, -1.0));
}

TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillReturnsTrueWithInfinityInputs_1746) {
  // Boundary: +/- infinity
  const double posInf = std::numeric_limits<double>::infinity();
  const double negInf = -std::numeric_limits<double>::infinity();
  EXPECT_TRUE(dev.axialShadedFill(nullptr, nullptr, negInf, posInf));
}

TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillReturnsTrueWithNaNInputs_1746) {
  // Boundary: NaN (if the implementation can handle it, it should still return a bool)
  const double nan = std::numeric_limits<double>::quiet_NaN();
  EXPECT_TRUE(dev.axialShadedFill(nullptr, nullptr, nan, 1.0));
  EXPECT_TRUE(dev.axialShadedFill(nullptr, nullptr, 0.0, nan));
  EXPECT_TRUE(dev.axialShadedFill(nullptr, nullptr, nan, nan));
}

}  // namespace