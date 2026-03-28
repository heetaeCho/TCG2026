// Copyright (C) 2026
// Unit tests for GfxDeviceRGBColorSpace::getNComps
// TEST_ID: 427

#include <gtest/gtest.h>

#include <memory>

#include "poppler/GfxState.h"

namespace {

class GfxDeviceRGBColorSpaceTest_427 : public ::testing::Test {
protected:
  GfxDeviceRGBColorSpace cs_;
};

TEST_F(GfxDeviceRGBColorSpaceTest_427, GetNComps_ReturnsThree_427) {
  EXPECT_EQ(cs_.getNComps(), 3);
}

TEST_F(GfxDeviceRGBColorSpaceTest_427, GetNComps_CanBeCalledRepeatedly_427) {
  EXPECT_EQ(cs_.getNComps(), 3);
  EXPECT_EQ(cs_.getNComps(), 3);
  EXPECT_EQ(cs_.getNComps(), 3);
}

TEST_F(GfxDeviceRGBColorSpaceTest_427, GetNComps_OnConstObject_ReturnsThree_427) {
  const GfxDeviceRGBColorSpace &constRef = cs_;
  EXPECT_EQ(constRef.getNComps(), 3);
}

TEST_F(GfxDeviceRGBColorSpaceTest_427, GetNComps_ThroughBasePointer_ReturnsThree_427) {
  std::unique_ptr<GfxColorSpace> base = std::make_unique<GfxDeviceRGBColorSpace>();
  ASSERT_NE(base, nullptr);
  EXPECT_EQ(base->getNComps(), 3);
}

TEST_F(GfxDeviceRGBColorSpaceTest_427, GetNComps_DoesNotThrow_427) {
  EXPECT_NO_THROW({
    (void)cs_.getNComps();
  });
}

} // namespace