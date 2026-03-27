// -*- mode: c++; -*-
// Unit tests for GfxDeviceCMYKColorSpace::getMode()
// File: test_gfxdevicecmykcolorspace_442.cc

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

// NOTE:
// We treat the class as a black box. The only observable behavior provided in the
// partial code is getMode() returning csDeviceCMYK. We do not infer behavior for
// any other methods.

// -----------------------------------------------------------------------------

class GfxDeviceCMYKColorSpaceTest_442 : public ::testing::Test {
protected:
  GfxDeviceCMYKColorSpace cs;
};

TEST_F(GfxDeviceCMYKColorSpaceTest_442, GetModeReturnsDeviceCMYK_442) {
  EXPECT_EQ(csDeviceCMYK, cs.getMode());
}

TEST_F(GfxDeviceCMYKColorSpaceTest_442, GetModeIsStableAcrossRepeatedCalls_442) {
  const auto first = cs.getMode();
  const auto second = cs.getMode();
  const auto third = cs.getMode();

  EXPECT_EQ(csDeviceCMYK, first);
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(GfxDeviceCMYKColorSpaceTest_442, GetModeDoesNotReturnOtherModes_442) {
  const auto mode = cs.getMode();

  EXPECT_NE(csDeviceGray, mode);
  EXPECT_NE(csDeviceRGB, mode);
  EXPECT_NE(csDeviceN, mode);
  EXPECT_NE(csPattern, mode);
  EXPECT_NE(csDeviceRGBA, mode);
}