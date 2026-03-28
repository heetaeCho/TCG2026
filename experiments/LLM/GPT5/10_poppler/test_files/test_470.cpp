// SPDX-License-Identifier: GPL-2.0-or-later
// File: GfxIndexedColorSpace_getBase_test_470.cpp

#include <gtest/gtest.h>

#include <memory>

#include "poppler/GfxState.h"

namespace {

TEST(GfxIndexedColorSpaceTest_470, GetBaseReturnsNullWhenConstructedWithNullBase_470) {
  std::unique_ptr<GfxColorSpace> nullBase;
  GfxIndexedColorSpace cs(std::move(nullBase), /*indexHighA=*/0);

  EXPECT_EQ(cs.getBase(), nullptr);
}

TEST(GfxIndexedColorSpaceTest_470, ConstructorMovesUniquePtrAndGetBaseMatchesOriginalPointer_470) {
  // Use a concrete color space type provided by Poppler.
  auto base = std::make_unique<GfxDeviceGrayColorSpace>();
  GfxColorSpace *expectedPtr = base.get();

  GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/1);

  // Move should leave the source unique_ptr empty.
  EXPECT_EQ(base.get(), nullptr);

  // getBase() should return the stored base pointer.
  EXPECT_EQ(cs.getBase(), expectedPtr);
}

TEST(GfxIndexedColorSpaceTest_470, GetBaseIsStableAcrossCalls_470) {
  auto base = std::make_unique<GfxDeviceRGBColorSpace>();
  GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/255);

  GfxColorSpace *p1 = cs.getBase();
  GfxColorSpace *p2 = cs.getBase();

  EXPECT_NE(p1, nullptr);
  EXPECT_EQ(p1, p2);
}

TEST(GfxIndexedColorSpaceTest_470, GetBaseDoesNotChangeAfterRepeatedCalls_470) {
  auto base = std::make_unique<GfxDeviceCMYKColorSpace>();
  GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/10);

  GfxColorSpace *first = cs.getBase();
  ASSERT_NE(first, nullptr);

  // Repeated calls should not change the returned pointer.
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(cs.getBase(), first);
  }
}

}  // namespace