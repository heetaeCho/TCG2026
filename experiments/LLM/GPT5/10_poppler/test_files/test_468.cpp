// TEST_ID: 468
// File: gfxindexedcolorspace_usegetdevicenline_test_468.cpp

#include <gtest/gtest.h>

#include "GfxState.h"

class GfxIndexedColorSpaceTest_468 : public ::testing::Test {};

// Normal operation: returns true.
TEST_F(GfxIndexedColorSpaceTest_468, UseGetDeviceNLineReturnsTrue_468) {
  GfxIndexedColorSpace cs(int{0}, 0);
  EXPECT_TRUE(cs.useGetDeviceNLine());
}

// Boundary: different (including negative) indexHigh should not affect the observable contract.
TEST_F(GfxIndexedColorSpaceTest_468, UseGetDeviceNLineReturnsTrueWithNegativeIndexHigh_468) {
  GfxIndexedColorSpace cs(int{0}, -1);
  EXPECT_TRUE(cs.useGetDeviceNLine());
}

// Boundary: repeated calls are stable.
TEST_F(GfxIndexedColorSpaceTest_468, UseGetDeviceNLineIsStableAcrossMultipleCalls_468) {
  GfxIndexedColorSpace cs(int{0}, 255);
  EXPECT_TRUE(cs.useGetDeviceNLine());
  EXPECT_TRUE(cs.useGetDeviceNLine());
  EXPECT_TRUE(cs.useGetDeviceNLine());
}

// Verify virtual dispatch behavior through the base interface (external interaction via polymorphism).
TEST_F(GfxIndexedColorSpaceTest_468, UseGetDeviceNLineWorksViaBasePointer_468) {
  GfxIndexedColorSpace cs(int{0}, 1);

  GfxColorSpace* basePtr = &cs;
  ASSERT_NE(basePtr, nullptr);
  EXPECT_TRUE(basePtr->useGetDeviceNLine());
}

// Const-correctness: callable on const object.
TEST_F(GfxIndexedColorSpaceTest_468, UseGetDeviceNLineCallableOnConst_468) {
  const GfxIndexedColorSpace cs(int{0}, 10);
  EXPECT_TRUE(cs.useGetDeviceNLine());
}