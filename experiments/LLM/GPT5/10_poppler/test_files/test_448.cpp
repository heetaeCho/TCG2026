//========================================================================
//
// GfxLabColorSpace_getNComps_ut.cc
//
// Unit tests for GfxLabColorSpace::getNComps()
//
//========================================================================

#include <gtest/gtest.h>

#include "GfxState.h"

// Poppler headers typically place GfxLabColorSpace in the global namespace.
// If your build uses a namespace, adjust accordingly.

class GfxLabColorSpaceTest_448 : public ::testing::Test {};

TEST_F(GfxLabColorSpaceTest_448, GetNComps_ReturnsThree_448) {
  GfxLabColorSpace cs;
  EXPECT_EQ(3, cs.getNComps());
}

TEST_F(GfxLabColorSpaceTest_448, GetNComps_IsStableAcrossMultipleCalls_448) {
  GfxLabColorSpace cs;
  const int first = cs.getNComps();
  const int second = cs.getNComps();
  const int third = cs.getNComps();

  EXPECT_EQ(3, first);
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(GfxLabColorSpaceTest_448, GetNComps_OnConstInstance_ReturnsThree_448) {
  const GfxLabColorSpace cs;
  EXPECT_EQ(3, cs.getNComps());
}