// TEST_ID 422
//
// Unit tests for GfxDeviceRGBColorSpace::getMode()
// File: ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include "GfxState.h"

namespace {

class GfxDeviceRGBColorSpaceTest_422 : public ::testing::Test {};

TEST_F(GfxDeviceRGBColorSpaceTest_422, GetModeReturnsDeviceRGB_422) {
  GfxDeviceRGBColorSpace cs;
  EXPECT_EQ(csDeviceRGB, cs.getMode());
}

TEST_F(GfxDeviceRGBColorSpaceTest_422, GetModeIsStableAcrossMultipleCalls_422) {
  GfxDeviceRGBColorSpace cs;
  const auto m1 = cs.getMode();
  const auto m2 = cs.getMode();
  const auto m3 = cs.getMode();
  EXPECT_EQ(csDeviceRGB, m1);
  EXPECT_EQ(m1, m2);
  EXPECT_EQ(m2, m3);
}

TEST_F(GfxDeviceRGBColorSpaceTest_422, GetModeWorksViaBasePointer_422) {
  // Verify observable behavior through the public base-class interface.
  std::unique_ptr<GfxColorSpace> base = std::make_unique<GfxDeviceRGBColorSpace>();
  ASSERT_NE(nullptr, base);
  EXPECT_EQ(csDeviceRGB, base->getMode());
}

}  // namespace