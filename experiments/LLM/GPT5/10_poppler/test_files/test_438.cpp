// TEST_ID = 438
//
// Unit tests for GfxCalRGBColorSpace::getGammaR()
// File: ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include <cmath>
#include <memory>

// Include the real header from the codebase.
#include "poppler/GfxState.h"

namespace {

class GfxCalRGBColorSpaceTest_438 : public ::testing::Test {};

TEST_F(GfxCalRGBColorSpaceTest_438, DefaultConstruction_GetGammaRIsNotNaN_438) {
  GfxCalRGBColorSpace cs;

  const double gammaR = cs.getGammaR();

  // Observable/black-box sanity checks: it should be a valid numeric value.
  EXPECT_FALSE(std::isnan(gammaR));
}

TEST_F(GfxCalRGBColorSpaceTest_438, DefaultConstruction_GetGammaRIsFinite_438) {
  GfxCalRGBColorSpace cs;

  const double gammaR = cs.getGammaR();

  EXPECT_TRUE(std::isfinite(gammaR));
}

TEST_F(GfxCalRGBColorSpaceTest_438, MultipleCalls_GetGammaRIsStable_438) {
  GfxCalRGBColorSpace cs;

  const double g1 = cs.getGammaR();
  const double g2 = cs.getGammaR();
  const double g3 = cs.getGammaR();

  // For a simple accessor, repeated calls should return the same value.
  // (No assumptions about the actual gamma value.)
  EXPECT_EQ(g1, g2);
  EXPECT_EQ(g2, g3);
}

TEST_F(GfxCalRGBColorSpaceTest_438, Copy_PreservesGammaR_438) {
  GfxCalRGBColorSpace original;

  const double origGammaR = original.getGammaR();

  std::unique_ptr<GfxColorSpace> copiedBase = original.copy();
  ASSERT_TRUE(copiedBase) << "copy() should return a non-null color space";

  // The copied object should be a GfxCalRGBColorSpace if copy() preserves dynamic type.
  auto *copied = dynamic_cast<GfxCalRGBColorSpace *>(copiedBase.get());
  ASSERT_NE(copied, nullptr) << "copy() result should have the same dynamic type";

  EXPECT_EQ(origGammaR, copied->getGammaR());
}

}  // namespace