// TEST_ID: 446
// File: gfxdevicecmykcolorspace_getncomps_test_446.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

class GfxDeviceCMYKColorSpaceTest_446 : public ::testing::Test {};

TEST_F(GfxDeviceCMYKColorSpaceTest_446, GetNCompsReturnsFour_446)
{
  GfxDeviceCMYKColorSpace cs;
  EXPECT_EQ(cs.getNComps(), 4);
}

TEST_F(GfxDeviceCMYKColorSpaceTest_446, GetNCompsIsStableAcrossRepeatedCalls_446)
{
  GfxDeviceCMYKColorSpace cs;

  const int first = cs.getNComps();
  const int second = cs.getNComps();
  const int third = cs.getNComps();

  EXPECT_EQ(first, 4);
  EXPECT_EQ(second, 4);
  EXPECT_EQ(third, 4);
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(GfxDeviceCMYKColorSpaceTest_446, GetNCompsWorksThroughBasePointer_446)
{
  GfxDeviceCMYKColorSpace cs;
  const GfxColorSpace *base = &cs;

  // Observable behavior via the public virtual interface.
  EXPECT_EQ(base->getNComps(), 4);
}

TEST_F(GfxDeviceCMYKColorSpaceTest_446, GetNCompsCallableOnConstObject_446)
{
  const GfxDeviceCMYKColorSpace cs;
  EXPECT_EQ(cs.getNComps(), 4);
}