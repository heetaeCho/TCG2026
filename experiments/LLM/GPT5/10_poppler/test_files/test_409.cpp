// TEST_ID: 409
//
// Unit tests for GfxDeviceGrayColorSpace::useGetGrayLine()
// File: ./TestProjects/poppler/poppler/GfxState.h
//
// Notes:
// - Treat implementation as a black box.
// - Only observable behavior here: return value of useGetGrayLine().
// - We avoid relying on any private state or internal logic.

#include <gtest/gtest.h>

#include "GfxState.h"

namespace {

class GfxDeviceGrayColorSpaceTest_409 : public ::testing::Test {
protected:
  GfxDeviceGrayColorSpace cs_;
};

// Normal operation: should report it supports getGrayLine().
TEST_F(GfxDeviceGrayColorSpaceTest_409, UseGetGrayLineReturnsTrue_409) {
  EXPECT_TRUE(cs_.useGetGrayLine());
}

// Boundary-ish: repeated calls should be stable/consistent and not depend on call order.
TEST_F(GfxDeviceGrayColorSpaceTest_409, UseGetGrayLineIsStableAcrossMultipleCalls_409) {
  for (int i = 0; i < 10; ++i) {
    EXPECT_TRUE(cs_.useGetGrayLine()) << "Iteration: " << i;
  }
}

// Boundary-ish: calling through base pointer still yields the overridden behavior.
TEST_F(GfxDeviceGrayColorSpaceTest_409, UseGetGrayLineThroughBasePointer_409) {
  GfxColorSpace* base = &cs_;
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->useGetGrayLine());
}

}  // namespace