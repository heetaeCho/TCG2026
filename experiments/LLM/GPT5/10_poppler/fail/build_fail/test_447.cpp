// ============================================================================
// Test file: GfxLabColorSpace_getMode_447_test.cc
// Target:    ./TestProjects/poppler/poppler/GfxState.h
// Focus:     GfxLabColorSpace::getMode() const
// TEST_ID:   447
// ============================================================================

#include <gtest/gtest.h>

#include "GfxState.h"

// NOTE:
// - We treat implementation as a black box.
// - Only observable behavior: getMode() return value.
// - No mocks needed (no external collaborators visible for getMode()).

class GfxLabColorSpaceTest_447 : public ::testing::Test {
protected:
  GfxLabColorSpace cs_;
};

TEST_F(GfxLabColorSpaceTest_447, GetModeReturnsCsLab_447) {
  EXPECT_EQ(csLab, cs_.getMode());
}

TEST_F(GfxLabColorSpaceTest_447, GetModeIsStableAcrossRepeatedCalls_447) {
  const auto first = cs_.getMode();
  const auto second = cs_.getMode();
  const auto third = cs_.getMode();
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(GfxLabColorSpaceTest_447, GetModeDoesNotReturnOtherModes_447) {
  const auto mode = cs_.getMode();

  // Boundary-ish coverage across the enum space: ensure it is not any other defined mode.
  EXPECT_NE(csDeviceGray, mode);
  EXPECT_NE(csCalGray, mode);
  EXPECT_NE(csDeviceRGB, mode);
  EXPECT_NE(csCalRGB, mode);
  EXPECT_NE(csDeviceCMYK, mode);
  EXPECT_NE(csICCBased, mode);
  EXPECT_NE(csIndexed, mode);
  EXPECT_NE(csSeparation, mode);
  EXPECT_NE(csDeviceN, mode);
  EXPECT_NE(csPattern, mode);
  EXPECT_NE(csDeviceRGBA, mode);

  // And the positive check again (keeps the intent crystal clear).
  EXPECT_EQ(csLab, mode);
}