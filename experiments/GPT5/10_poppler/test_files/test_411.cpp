// TEST_ID: 411
// File: GfxDeviceGrayColorSpace_useGetDeviceNLine_test.cpp
//
// Unit tests for:
//   GfxDeviceGrayColorSpace::useGetDeviceNLine()
//
// Constraints honored:
// - Treat implementation as black box.
// - Only test observable behavior via public interface.

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxDeviceGrayColorSpaceTest_411 : public ::testing::Test {
protected:
  GfxDeviceGrayColorSpace cs;
};

} // namespace

TEST_F(GfxDeviceGrayColorSpaceTest_411, UseGetDeviceNLineReturnsTrue_411)
{
  // Normal operation: the interface promises true for this class.
  EXPECT_TRUE(cs.useGetDeviceNLine());
}

TEST_F(GfxDeviceGrayColorSpaceTest_411, UseGetDeviceNLineIsStableAcrossCalls_411)
{
  // Boundary-ish: repeat calls; should remain consistent.
  EXPECT_TRUE(cs.useGetDeviceNLine());
  EXPECT_TRUE(cs.useGetDeviceNLine());
  EXPECT_TRUE(cs.useGetDeviceNLine());
}

TEST_F(GfxDeviceGrayColorSpaceTest_411, UseGetDeviceNLineWorksThroughBaseReference_411)
{
  // Verifies virtual dispatch (observable behavior through base interface).
  GfxColorSpace &base = cs;
  EXPECT_TRUE(base.useGetDeviceNLine());
}

TEST_F(GfxDeviceGrayColorSpaceTest_411, UseGetDeviceNLineWorksThroughBasePointer_411)
{
  // Another virtual dispatch check through pointer.
  GfxColorSpace *base = &cs;
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->useGetDeviceNLine());
}