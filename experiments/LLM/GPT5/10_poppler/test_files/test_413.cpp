// TEST_ID 413
// File: GfxCalGrayColorSpace_getMode_test.cpp

#include <gtest/gtest.h>

#include "GfxState.h" // Provides GfxCalGrayColorSpace, GfxColorSpace, GfxColorSpaceMode

namespace {

class GfxCalGrayColorSpaceTest_413 : public ::testing::Test {
protected:
  GfxCalGrayColorSpace cs_;
};

TEST_F(GfxCalGrayColorSpaceTest_413, GetModeReturnsCsCalGray_413) {
  EXPECT_EQ(csCalGray, cs_.getMode());
}

TEST_F(GfxCalGrayColorSpaceTest_413, GetModeIsStableAcrossMultipleCalls_413) {
  const auto first = cs_.getMode();
  const auto second = cs_.getMode();
  const auto third = cs_.getMode();

  EXPECT_EQ(csCalGray, first);
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(GfxCalGrayColorSpaceTest_413, GetModeWorksThroughBaseReference_413) {
  const GfxColorSpace &baseRef = cs_;
  EXPECT_EQ(csCalGray, baseRef.getMode());
}

TEST_F(GfxCalGrayColorSpaceTest_413, GetModeWorksThroughBasePointer_413) {
  const GfxColorSpace *basePtr = &cs_;
  ASSERT_NE(nullptr, basePtr);
  EXPECT_EQ(csCalGray, basePtr->getMode());
}

TEST_F(GfxCalGrayColorSpaceTest_413, GetModeIsNotOtherCommonModes_413) {
  // Boundary-ish sanity: ensure it doesn't accidentally report other enum values.
  EXPECT_NE(csDeviceGray, cs_.getMode());
  EXPECT_NE(csDeviceRGB, cs_.getMode());
  EXPECT_NE(csDeviceCMYK, cs_.getMode());
  EXPECT_NE(csPattern, cs_.getMode());
}

} // namespace