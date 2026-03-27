// TEST_ID: 431
// File: GfxCalRGBColorSpace_getNComps_431_test.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

// NOTE:
// - Treat implementation as a black box.
// - Only observable behavior tested here is getNComps() return value and
//   correct virtual dispatch via the public interface.

namespace {

class GfxCalRGBColorSpaceTest_431 : public ::testing::Test {};

TEST_F(GfxCalRGBColorSpaceTest_431, GetNCompsReturnsThree_431) {
  GfxCalRGBColorSpace cs;
  EXPECT_EQ(cs.getNComps(), 3);
}

TEST_F(GfxCalRGBColorSpaceTest_431, GetNCompsWorksThroughConstObject_431) {
  const GfxCalRGBColorSpace cs;
  EXPECT_EQ(cs.getNComps(), 3);
}

TEST_F(GfxCalRGBColorSpaceTest_431, GetNCompsIsStableAcrossMultipleCalls_431) {
  GfxCalRGBColorSpace cs;
  EXPECT_EQ(cs.getNComps(), 3);
  EXPECT_EQ(cs.getNComps(), 3);
  EXPECT_EQ(cs.getNComps(), 3);
}

TEST_F(GfxCalRGBColorSpaceTest_431, GetNCompsUsesVirtualDispatchViaBasePointer_431) {
  // Verifies observable behavior through the base-class interface (external interaction:
  // correct override dispatch).
  GfxCalRGBColorSpace derived;
  GfxColorSpace *base = &derived;

  ASSERT_NE(base, nullptr);
  EXPECT_EQ(base->getNComps(), 3);
}

TEST_F(GfxCalRGBColorSpaceTest_431, GetNCompsUsesVirtualDispatchViaBaseReference_431) {
  GfxCalRGBColorSpace derived;
  const GfxColorSpace &baseRef = derived;

  EXPECT_EQ(baseRef.getNComps(), 3);
}

}  // namespace