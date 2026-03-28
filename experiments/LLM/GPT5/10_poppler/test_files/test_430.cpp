// TEST_ID: 430
// File: GfxCalRGBColorSpace_test_430.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxCalRGBColorSpaceTest_430 : public ::testing::Test {};

TEST_F(GfxCalRGBColorSpaceTest_430, GetMode_ReturnsCsCalRGB_430) {
  GfxCalRGBColorSpace cs;
  EXPECT_EQ(cs.getMode(), csCalRGB);
}

TEST_F(GfxCalRGBColorSpaceTest_430, GetMode_WorksViaBasePointer_430) {
  GfxCalRGBColorSpace derived;
  const GfxColorSpace *base = &derived;

  // Observable behavior through the public virtual interface.
  EXPECT_EQ(base->getMode(), csCalRGB);
}

TEST_F(GfxCalRGBColorSpaceTest_430, GetMode_IsStableAcrossMultipleCalls_430) {
  GfxCalRGBColorSpace cs;

  const auto m1 = cs.getMode();
  const auto m2 = cs.getMode();
  const auto m3 = cs.getMode();

  EXPECT_EQ(m1, csCalRGB);
  EXPECT_EQ(m2, csCalRGB);
  EXPECT_EQ(m3, csCalRGB);
}

TEST_F(GfxCalRGBColorSpaceTest_430, Copy_ProducesNonNullAndPreservesMode_430) {
  GfxCalRGBColorSpace cs;

  // copy() is part of the public interface; treat it as a black box and only
  // validate observable properties of the returned object.
  std::unique_ptr<GfxColorSpace> cloned = cs.copy();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->getMode(), csCalRGB);
}

TEST_F(GfxCalRGBColorSpaceTest_430, EnumValue_IsDefinedAndMatchesDeclaration_430) {
  // Boundary/definition check based on the provided public enum declaration.
  EXPECT_EQ(static_cast<int>(csCalRGB), 3);
}

}  // namespace