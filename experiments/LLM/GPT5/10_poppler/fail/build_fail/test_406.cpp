// File: GfxColorSpace_getOverprintMask_406_test.cpp
#include <gtest/gtest.h>

#include "GfxState.h"

// Test helper: expose a way to set the protected overprintMask without touching private internals.
class TestGfxColorSpace_406 : public GfxColorSpace {
public:
  void setOverprintMaskForTest(unsigned int mask) { overprintMask = mask; }
};

class GfxColorSpaceTest_406 : public ::testing::Test {
protected:
  TestGfxColorSpace_406 cs_;
};

TEST_F(GfxColorSpaceTest_406, ReturnsZeroWhenMaskIsZero_406) {
  cs_.setOverprintMaskForTest(0u);
  EXPECT_EQ(cs_.getOverprintMask(), 0u);
}

TEST_F(GfxColorSpaceTest_406, ReturnsMaxUnsignedWhenMaskIsMax_406) {
  cs_.setOverprintMaskForTest(~0u);
  EXPECT_EQ(cs_.getOverprintMask(), ~0u);
}

TEST_F(GfxColorSpaceTest_406, ReturnsExactValueForTypicalMask_406) {
  const unsigned int kMask = 0xA5A5u;
  cs_.setOverprintMaskForTest(kMask);
  EXPECT_EQ(cs_.getOverprintMask(), kMask);
}

TEST_F(GfxColorSpaceTest_406, ReflectsUpdatedMaskValueAfterChange_406) {
  cs_.setOverprintMaskForTest(0x1u);
  EXPECT_EQ(cs_.getOverprintMask(), 0x1u);

  cs_.setOverprintMaskForTest(0x12345678u);
  EXPECT_EQ(cs_.getOverprintMask(), 0x12345678u);
}

TEST_F(GfxColorSpaceTest_406, CallableOnConstObject_406) {
  cs_.setOverprintMaskForTest(0x55u);

  const GfxColorSpace &constRef = cs_;
  EXPECT_EQ(constRef.getOverprintMask(), 0x55u);
}