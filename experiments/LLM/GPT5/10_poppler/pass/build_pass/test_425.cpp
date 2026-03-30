// -*- mode: c++; -*-
// File: GfxDeviceRGBColorSpace_useGetCMYKLine_test.cpp
//
// Unit tests for:
//   bool GfxDeviceRGBColorSpace::useGetCMYKLine() const
//
// Constraints respected:
// - Treat implementation as black box (only public API used)
// - No private/internal state access
// - Observable behavior: return value
// - TEST_ID suffix on every test name (425)

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxDeviceRGBColorSpaceTest_425 : public ::testing::Test {
protected:
  GfxDeviceRGBColorSpace cs_;
};

TEST_F(GfxDeviceRGBColorSpaceTest_425, UseGetCMYKLineReturnsTrue_425)
{
  // Normal operation: method should report whether getCMYKLine is supported.
  EXPECT_TRUE(cs_.useGetCMYKLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_425, UseGetCMYKLineIsConstCallable_425)
{
  // Boundary/contract: callable on const instances and still returns a bool.
  const GfxDeviceRGBColorSpace csConst;
  EXPECT_TRUE(csConst.useGetCMYKLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_425, UseGetCMYKLineIsStableAcrossCalls_425)
{
  // Boundary: repeated calls should be stable/consistent (no observable side effects).
  const bool first = cs_.useGetCMYKLine();
  const bool second = cs_.useGetCMYKLine();
  const bool third = cs_.useGetCMYKLine();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  EXPECT_TRUE(first);
}

} // namespace