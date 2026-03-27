// TEST_ID: 533
//
// Unit tests for GfxImageColorMap::getBits()
// File: ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include "GfxState.h"
#include "Object.h"

namespace {

Object MakeNullDecodeObject() {
  Object decode;
  // In Poppler, Object typically supports initNull().
  // If your Object API differs, adjust this helper to create a "no decode" object.
  decode.initNull();
  return decode;
}

std::unique_ptr<GfxColorSpace> MakeDeviceRGBColorSpace() {
  // Poppler provides concrete color space types in/through GfxState.h.
  return std::unique_ptr<GfxColorSpace>(new GfxDeviceRGBColorSpace());
}

std::unique_ptr<GfxColorSpace> MakeDeviceGrayColorSpace() {
  return std::unique_ptr<GfxColorSpace>(new GfxDeviceGrayColorSpace());
}

}  // namespace

class GfxImageColorMapTest_533 : public ::testing::Test {
 protected:
  Object decode_ = MakeNullDecodeObject();
};

TEST_F(GfxImageColorMapTest_533, GetBitsReturnsConstructorBits_DeviceRGB_533) {
  auto cs = MakeDeviceRGBColorSpace();
  const int bits = 8;

  GfxImageColorMap cmap(bits, &decode_, std::move(cs));

  EXPECT_EQ(cmap.getBits(), bits);
}

TEST_F(GfxImageColorMapTest_533, GetBitsWorksOnConstObject_533) {
  auto cs = MakeDeviceGrayColorSpace();
  const int bits = 1;

  GfxImageColorMap cmap(bits, &decode_, std::move(cs));
  const GfxImageColorMap &ccmap = cmap;

  EXPECT_EQ(ccmap.getBits(), bits);
}

TEST_F(GfxImageColorMapTest_533, GetBitsBoundaryCommonMaximum16_533) {
  auto cs = MakeDeviceRGBColorSpace();
  const int bits = 16;

  GfxImageColorMap cmap(bits, &decode_, std::move(cs));

  EXPECT_EQ(cmap.getBits(), bits);
}

TEST_F(GfxImageColorMapTest_533, CopyPreservesBitsWhenOk_533) {
  auto cs = MakeDeviceRGBColorSpace();
  const int bits = 8;

  GfxImageColorMap cmap(bits, &decode_, std::move(cs));

  // Only assert copy behavior when the object reports it's usable.
  if (cmap.isOk()) {
    std::unique_ptr<GfxImageColorMap> copy(cmap.copy());
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getBits(), cmap.getBits());
  } else {
    GTEST_SKIP() << "Color map reported not ok(); skipping copy() assertions.";
  }
}

TEST_F(GfxImageColorMapTest_533, CopyOfConstPreservesBitsWhenOk_533) {
  auto cs = MakeDeviceGrayColorSpace();
  const int bits = 4;

  GfxImageColorMap cmap(bits, &decode_, std::move(cs));
  const GfxImageColorMap &ccmap = cmap;

  if (ccmap.isOk()) {
    std::unique_ptr<GfxImageColorMap> copy(ccmap.copy());
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getBits(), bits);
  } else {
    GTEST_SKIP() << "Color map reported not ok(); skipping copy() assertions.";
  }
}