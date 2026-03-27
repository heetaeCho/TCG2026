// -*- mode: c++; -*-
// TEST_ID is 408
//
// Unit tests for GfxDeviceGrayColorSpace::useGetRGBLine().
//
// Constraints respected:
// - Treat implementation as black box.
// - Test only observable behavior via public interface.
// - No private state access.
// - No re-implementation of internal logic.

#include <gtest/gtest.h>

#include "GfxState.h"

// If poppler headers require additional includes in your tree, add them here.
// e.g. #include "Object.h" etc.

class GfxDeviceGrayColorSpaceTest_408 : public ::testing::Test {};

// Normal operation: returns true.
TEST_F(GfxDeviceGrayColorSpaceTest_408, UseGetRGBLineReturnsTrue_408)
{
  GfxDeviceGrayColorSpace cs;
  EXPECT_TRUE(cs.useGetRGBLine());
}

// Boundary-ish: multiple calls are consistent.
TEST_F(GfxDeviceGrayColorSpaceTest_408, UseGetRGBLineIsStableAcrossCalls_408)
{
  GfxDeviceGrayColorSpace cs;
  EXPECT_TRUE(cs.useGetRGBLine());
  EXPECT_TRUE(cs.useGetRGBLine());
  EXPECT_TRUE(cs.useGetRGBLine());
}

// Boundary-ish: const correctness (call on const object).
TEST_F(GfxDeviceGrayColorSpaceTest_408, UseGetRGBLineCallableOnConst_408)
{
  const GfxDeviceGrayColorSpace cs;
  EXPECT_TRUE(cs.useGetRGBLine());
}

// Verification of external interactions: N/A for this method (no collaborators),
// but we can still validate polymorphic dispatch through base pointer.
TEST_F(GfxDeviceGrayColorSpaceTest_408, UseGetRGBLineThroughBasePointerDispatches_408)
{
  // This test assumes GfxDeviceGrayColorSpace is-a GfxColorSpace as declared.
  GfxDeviceGrayColorSpace derived;
  GfxColorSpace *base = &derived;

  // If override is wired correctly, result should match derived behavior.
  EXPECT_TRUE(base->useGetRGBLine());
}