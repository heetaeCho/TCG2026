// TEST_ID: 429
// File: test_gfx_device_rgba_colorspace_429.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

// These tests treat the implementation as a black box and only verify
// behavior observable through the public interface.

namespace {

class GfxDeviceRGBAColorSpaceTest_429 : public ::testing::Test {};

TEST_F(GfxDeviceRGBAColorSpaceTest_429, GetNCompsReturnsFour_429) {
  GfxDeviceRGBAColorSpace cs;
  EXPECT_EQ(cs.getNComps(), 4);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_429, GetNCompsIsConstCallable_429) {
  const GfxDeviceRGBAColorSpace cs;
  EXPECT_EQ(cs.getNComps(), 4);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_429, GetNCompsViaBaseReferenceIfPossible_429) {
  // Verify virtual dispatch works through the known base type.
  // (No assumptions about other behavior.)
  GfxDeviceRGBAColorSpace derived;
  const GfxDeviceRGBColorSpace& baseRef = derived;
  EXPECT_EQ(baseRef.getNComps(), 4);
}

}  // namespace