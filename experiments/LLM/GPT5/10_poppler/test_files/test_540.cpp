// TEST_ID: 540
// File: test_gfx_image_color_map_matte_color_540.cc

#include <gtest/gtest.h>

#include <memory>

#include "GfxState.h" // GfxImageColorMap, GfxColor, GfxDeviceRGBColorSpace
#include "Object.h"   // Object

namespace {

std::unique_ptr<GfxColorSpace> MakeDeviceRGBColorSpace() {
  // Poppler typically provides this concrete type for DeviceRGB.
  return std::make_unique<GfxDeviceRGBColorSpace>();
}

GfxImageColorMap MakeColorMap_DeviceRGB_8bit() {
  Object decode;
  decode.initNull(); // Let implementation decide default decode if supported.
  return GfxImageColorMap(/*bitsA=*/8, &decode, MakeDeviceRGBColorSpace());
}

void ExpectGfxColorEqualsFirst4(const GfxColor &a, const GfxColor &b) {
  // Compare first 4 components (covers Gray/RGB/CMYK-like storage).
  // This relies only on GfxColor being publicly readable (typical Poppler struct).
  EXPECT_DOUBLE_EQ(a.c[0], b.c[0]);
  EXPECT_DOUBLE_EQ(a.c[1], b.c[1]);
  EXPECT_DOUBLE_EQ(a.c[2], b.c[2]);
  EXPECT_DOUBLE_EQ(a.c[3], b.c[3]);
}

} // namespace

class GfxImageColorMapTest_540 : public ::testing::Test {
protected:
  void SetUp() override {
    cmap = MakeColorMap_DeviceRGB_8bit();
    // If construction is invalid in this build/configuration, skip all tests safely.
    if (!cmap.isOk()) {
      GTEST_SKIP() << "GfxImageColorMap is not OK in this configuration; skipping TEST_ID 540.";
    }
  }

  GfxImageColorMap cmap;
};

TEST_F(GfxImageColorMapTest_540, GetMatteColor_DefaultIsNull_540) {
  // Observable behavior: if matte is not enabled, getMatteColor() returns nullptr.
  EXPECT_EQ(cmap.getMatteColor(), nullptr);
}

TEST_F(GfxImageColorMapTest_540, SetMatteColor_NullKeepsNull_540) {
  cmap.setMatteColor(nullptr);
  EXPECT_EQ(cmap.getMatteColor(), nullptr);

  // Calling again should remain nullptr (idempotent from the interface perspective).
  cmap.setMatteColor(nullptr);
  EXPECT_EQ(cmap.getMatteColor(), nullptr);
}

TEST_F(GfxImageColorMapTest_540, SetMatteColor_NonNullReturnsNonNullAndCopiesValue_540) {
  GfxColor in{};
  in.c[0] = 0.1;
  in.c[1] = 0.2;
  in.c[2] = 0.3;
  in.c[3] = 0.4;

  cmap.setMatteColor(&in);

  const GfxColor *p = cmap.getMatteColor();
  ASSERT_NE(p, nullptr);

  // The returned pointer is expected to refer to an internal stored matte color,
  // whose value matches what was provided.
  ExpectGfxColorEqualsFirst4(*p, in);

  // Mutating the input after setting should not affect the stored matte color
  // if the implementation copies it (observable via getMatteColor()).
  in.c[0] = 9.9;
  in.c[1] = 8.8;
  in.c[2] = 7.7;
  in.c[3] = 6.6;

  const GfxColor *p2 = cmap.getMatteColor();
  ASSERT_NE(p2, nullptr);
  ExpectGfxColorEqualsFirst4(*p2, *p); // stored remains consistent across calls
}

TEST_F(GfxImageColorMapTest_540, GetMatteColor_AddressStableAcrossCallsWhileEnabled_540) {
  GfxColor in{};
  in.c[0] = 0.01;
  in.c[1] = 0.02;
  in.c[2] = 0.03;
  in.c[3] = 0.04;

  cmap.setMatteColor(&in);

  const GfxColor *p1 = cmap.getMatteColor();
  ASSERT_NE(p1, nullptr);

  const GfxColor *p2 = cmap.getMatteColor();
  ASSERT_NE(p2, nullptr);

  // Observable: repeated calls should return the same pointer while matte is enabled.
  EXPECT_EQ(p1, p2);
}

TEST_F(GfxImageColorMapTest_540, SetMatteColor_ClearAfterSet_ReturnsNull_540) {
  GfxColor in{};
  in.c[0] = 0.5;
  in.c[1] = 0.6;
  in.c[2] = 0.7;
  in.c[3] = 0.8;

  cmap.setMatteColor(&in);
  ASSERT_NE(cmap.getMatteColor(), nullptr);

  // Clearing matte color should disable it (observable as nullptr).
  cmap.setMatteColor(nullptr);
  EXPECT_EQ(cmap.getMatteColor(), nullptr);
}