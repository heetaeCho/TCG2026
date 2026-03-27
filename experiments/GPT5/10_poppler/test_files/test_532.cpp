// TEST_ID: 532
// File: test_gfximagecolormap_getnumpixelcomps_532.cpp

#include <gtest/gtest.h>

#include <memory>

#include "poppler/GfxState.h"
#include "poppler/Object.h"

namespace {

// Helper that tries to create a color space using the common Poppler API.
// If your Poppler fork differs, adjust only this helper (tests stay black-box).
static std::unique_ptr<GfxColorSpace> makeColorSpace(GfxColorSpaceMode mode) {
  // Common Poppler API: static GfxColorSpace *GfxColorSpace::create(GfxColorSpaceMode)
  return std::unique_ptr<GfxColorSpace>(GfxColorSpace::create(mode));
}

static Object makeNullObject() {
  Object obj;
  // Most Poppler versions support default-constructed Object as a valid "null"-like object.
  // If your version requires explicit initialization, adjust here.
  return obj;
}

}  // namespace

class GfxImageColorMapTest_532 : public ::testing::Test {
 protected:
  Object decodeNull_ = makeNullObject();
};

TEST_F(GfxImageColorMapTest_532, DeviceGray_ReturnsOneComponent_532) {
  auto cs = makeColorSpace(csDeviceGray);
  ASSERT_NE(cs, nullptr);

  GfxImageColorMap cmap(/*bitsA=*/8, &decodeNull_, std::move(cs));
  ASSERT_TRUE(cmap.isOk());

  EXPECT_EQ(cmap.getNumPixelComps(), 1);
}

TEST_F(GfxImageColorMapTest_532, DeviceRGB_ReturnsThreeComponents_532) {
  auto cs = makeColorSpace(csDeviceRGB);
  ASSERT_NE(cs, nullptr);

  GfxImageColorMap cmap(/*bitsA=*/8, &decodeNull_, std::move(cs));
  ASSERT_TRUE(cmap.isOk());

  EXPECT_EQ(cmap.getNumPixelComps(), 3);
}

TEST_F(GfxImageColorMapTest_532, DeviceCMYK_ReturnsFourComponents_532) {
  auto cs = makeColorSpace(csDeviceCMYK);
  ASSERT_NE(cs, nullptr);

  GfxImageColorMap cmap(/*bitsA=*/8, &decodeNull_, std::move(cs));
  ASSERT_TRUE(cmap.isOk());

  EXPECT_EQ(cmap.getNumPixelComps(), 4);
}

TEST_F(GfxImageColorMapTest_532, BitsBoundary_LowAndHigh_DoNotChangeComponentCount_532) {
  // Boundary-ish bits values commonly supported in image sample decoding.
  // We only assert the observable component-count contract via the public API.
  for (int bits : {1, 16}) {
    auto cs = makeColorSpace(csDeviceRGB);
    ASSERT_NE(cs, nullptr);

    GfxImageColorMap cmap(bits, &decodeNull_, std::move(cs));
    ASSERT_TRUE(cmap.isOk()) << "Expected cmap to be OK for bits=" << bits;

    EXPECT_EQ(cmap.getNumPixelComps(), 3) << "bits=" << bits;
  }
}

TEST_F(GfxImageColorMapTest_532, Copy_PreservesNumPixelComponents_532) {
  auto cs = makeColorSpace(csDeviceRGB);
  ASSERT_NE(cs, nullptr);

  GfxImageColorMap cmap(/*bitsA=*/8, &decodeNull_, std::move(cs));
  ASSERT_TRUE(cmap.isOk());

  std::unique_ptr<GfxImageColorMap> copy(cmap.copy());
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->isOk());

  EXPECT_EQ(copy->getNumPixelComps(), cmap.getNumPixelComps());
}

TEST_F(GfxImageColorMapTest_532, InvalidBits_IsOkMayBeFalse_GetNumPixelCompsIsCallable_532) {
  auto cs = makeColorSpace(csDeviceRGB);
  ASSERT_NE(cs, nullptr);

  // Use a clearly suspicious bits value (implementation-defined handling).
  GfxImageColorMap cmap(/*bitsA=*/0, &decodeNull_, std::move(cs));

  // Black-box: if not OK, we still verify the getter is callable and returns a non-negative int.
  // (We do not assert any specific value; only basic observable sanity.)
  int n = cmap.getNumPixelComps();
  EXPECT_GE(n, 0);
}

TEST_F(GfxImageColorMapTest_532, DecodeNullptr_ConstructionIsObservableViaIsOk_532) {
  auto cs = makeColorSpace(csDeviceGray);
  ASSERT_NE(cs, nullptr);

  // Some Poppler versions may accept a null decode pointer and apply defaults.
  // We only assert that construction is observable (no crash) and, if OK, component count matches.
  GfxImageColorMap cmap(/*bitsA=*/8, /*decode=*/nullptr, std::move(cs));

  if (cmap.isOk()) {
    EXPECT_EQ(cmap.getNumPixelComps(), 1);
  } else {
    SUCCEED() << "Construction with decode=nullptr is not OK in this build (acceptable).";
  }
}