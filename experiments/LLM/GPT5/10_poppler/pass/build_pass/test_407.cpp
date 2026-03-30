// TEST_ID: 407
// File: GfxDeviceGrayColorSpace_getMode_test.cpp
//
// Unit tests for:
//   class GfxDeviceGrayColorSpace { public: GfxColorSpaceMode getMode() const override { return csDeviceGray; } };
//
// Constraints honored:
// - Treat implementation as black box: only assert observable return values.
// - No private/internal state access.
// - No mocks needed (no external interactions observable from this interface).

#include <gtest/gtest.h>

// Include the production header under test.
#include "GfxState.h"

namespace {

class GfxDeviceGrayColorSpaceTest_407 : public ::testing::Test {};

TEST_F(GfxDeviceGrayColorSpaceTest_407, GetModeReturnsDeviceGray_407)
{
  GfxDeviceGrayColorSpace cs;
  EXPECT_EQ(csDeviceGray, cs.getMode());
}

TEST_F(GfxDeviceGrayColorSpaceTest_407, GetModeIsStableAcrossMultipleCalls_407)
{
  GfxDeviceGrayColorSpace cs;

  const auto first = cs.getMode();
  const auto second = cs.getMode();
  const auto third = cs.getMode();

  EXPECT_EQ(csDeviceGray, first);
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(GfxDeviceGrayColorSpaceTest_407, GetModeWorksThroughConstObject_407)
{
  const GfxDeviceGrayColorSpace cs;
  EXPECT_EQ(csDeviceGray, cs.getMode());
}

TEST_F(GfxDeviceGrayColorSpaceTest_407, GetModeIsWithinEnumRange_407)
{
  GfxDeviceGrayColorSpace cs;
  const auto mode = cs.getMode();

  // Boundary-style check using the visible enum values:
  // csDeviceGray is 0 and csDeviceRGBA is 11 per provided enum.
  EXPECT_GE(static_cast<int>(mode), static_cast<int>(csDeviceGray));
  EXPECT_LE(static_cast<int>(mode), static_cast<int>(csDeviceRGBA));

  // And it must be exactly DeviceGray for this concrete colorspace.
  EXPECT_EQ(csDeviceGray, mode);
}

} // namespace