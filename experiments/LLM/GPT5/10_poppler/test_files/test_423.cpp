// TEST_ID: 423
// File: GfxDeviceRGBColorSpace_useGetRGBLine_test.cpp
//
// Unit tests for GfxDeviceRGBColorSpace::useGetRGBLine()
// Constraints respected:
// - Black-box: only tests observable behavior from the public interface.
// - No private state access.
// - No re-implementation of internal logic.

#include <gtest/gtest.h>

// Include the real header from the codebase.
#include "poppler/GfxState.h"

namespace {

// Minimal fixture for consistent naming / future expansion.
class GfxDeviceRGBColorSpaceTest_423 : public ::testing::Test {};

TEST_F(GfxDeviceRGBColorSpaceTest_423, UseGetRGBLine_ReturnsTrue_423)
{
  GfxDeviceRGBColorSpace cs;
  EXPECT_TRUE(cs.useGetRGBLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_423, UseGetRGBLine_ConstObject_ReturnsTrue_423)
{
  const GfxDeviceRGBColorSpace cs;
  EXPECT_TRUE(cs.useGetRGBLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_423, UseGetRGBLine_CalledMultipleTimes_AlwaysTrue_423)
{
  GfxDeviceRGBColorSpace cs;

  EXPECT_TRUE(cs.useGetRGBLine());
  EXPECT_TRUE(cs.useGetRGBLine());
  EXPECT_TRUE(cs.useGetRGBLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_423, UseGetRGBLine_ThroughBasePointer_ReturnsTrue_423)
{
  // Verifies override dispatch through the base class interface (observable behavior).
  GfxDeviceRGBColorSpace derived;
  GfxColorSpace *base = &derived;

  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->useGetRGBLine());
}

} // namespace