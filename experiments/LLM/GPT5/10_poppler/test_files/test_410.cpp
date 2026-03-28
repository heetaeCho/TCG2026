// TEST_ID: 410
// File: test_gfxdevicegraycolorspace_usegetcmykline_410.cpp

#include <gtest/gtest.h>

#include "GfxState.h" // Provides GfxDeviceGrayColorSpace

class GfxDeviceGrayColorSpaceTest_410 : public ::testing::Test {};

TEST_F(GfxDeviceGrayColorSpaceTest_410, UseGetCMYKLine_ReturnsTrue_410)
{
  GfxDeviceGrayColorSpace cs;
  EXPECT_TRUE(cs.useGetCMYKLine());
}

TEST_F(GfxDeviceGrayColorSpaceTest_410, UseGetCMYKLine_IsStableAcrossCalls_410)
{
  GfxDeviceGrayColorSpace cs;

  const bool first = cs.useGetCMYKLine();
  const bool second = cs.useGetCMYKLine();
  const bool third = cs.useGetCMYKLine();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  EXPECT_TRUE(first);
}

TEST_F(GfxDeviceGrayColorSpaceTest_410, UseGetCMYKLine_ConstObject_ReturnsTrue_410)
{
  const GfxDeviceGrayColorSpace cs;
  EXPECT_TRUE(cs.useGetCMYKLine());
}

TEST_F(GfxDeviceGrayColorSpaceTest_410, UseGetCMYKLine_ViaBaseReference_ReturnsTrue_410)
{
  GfxDeviceGrayColorSpace derived;
  const GfxColorSpace &baseRef = derived;

  EXPECT_TRUE(baseRef.useGetCMYKLine());
}

TEST_F(GfxDeviceGrayColorSpaceTest_410, UseGetCMYKLine_ViaBasePointer_ReturnsTrue_410)
{
  auto derived = std::make_unique<GfxDeviceGrayColorSpace>();
  const GfxColorSpace *basePtr = derived.get();

  ASSERT_NE(basePtr, nullptr);
  EXPECT_TRUE(basePtr->useGetCMYKLine());
}