// TEST_ID: 424
// File: gfx_device_rgb_colorspace_usegetgrayline_test.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxDeviceRGBColorSpaceTest_424 : public ::testing::Test {};

TEST_F(GfxDeviceRGBColorSpaceTest_424, UseGetGrayLineReturnsTrue_424) {
  GfxDeviceRGBColorSpace cs;
  EXPECT_TRUE(cs.useGetGrayLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, UseGetGrayLineIsTrueViaBasePointer_424) {
  GfxDeviceRGBColorSpace derived;
  GfxColorSpace *base = &derived; // verify virtual dispatch observable through interface
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->useGetGrayLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, UseGetGrayLineIsConstCallable_424) {
  const GfxDeviceRGBColorSpace cs;
  EXPECT_TRUE(cs.useGetGrayLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, UseGetGrayLineConsistentAcrossInstances_424) {
  GfxDeviceRGBColorSpace cs1;
  GfxDeviceRGBColorSpace cs2;
  EXPECT_TRUE(cs1.useGetGrayLine());
  EXPECT_TRUE(cs2.useGetGrayLine());
}

} // namespace