// TEST_ID: 529
// File: gfx_image_color_map_copy_test_529.cpp

#include <gtest/gtest.h>

#include <memory>
#include <utility>

#include "poppler/GfxState.h"
#include "poppler/Object.h"

namespace {

// Helper to build a minimal GfxImageColorMap using the public ctor:
//   GfxImageColorMap(int bitsA, Object* decode, int&& colorSpaceA)
static std::unique_ptr<GfxImageColorMap> MakeColorMap(int bits, int colorSpaceModeAsInt, Object *decode)
{
  // ctor wants an rvalue int
  int cs = colorSpaceModeAsInt;
  return std::make_unique<GfxImageColorMap>(bits, decode, std::move(cs));
}

static std::unique_ptr<GfxImageColorMap> MakeDeviceRGB(int bits)
{
  Object decode; // default/null decode object is sufficient for black-box construction attempts
  return MakeColorMap(bits, static_cast<int>(csDeviceRGB), &decode);
}

} // namespace

class GfxImageColorMapTest_529 : public ::testing::Test {};

// Normal operation: copy() returns a distinct, non-null object.
TEST_F(GfxImageColorMapTest_529, CopyReturnsNonNullDistinctObject_529)
{
  auto cm = MakeDeviceRGB(8);
  ASSERT_NE(cm, nullptr);
  ASSERT_TRUE(cm->isOk());

  std::unique_ptr<GfxImageColorMap> copy(cm->copy());
  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy.get(), cm.get());
}

// Normal operation: multiple copies are distinct objects.
TEST_F(GfxImageColorMapTest_529, MultipleCopiesAreDistinct_529)
{
  auto cm = MakeDeviceRGB(8);
  ASSERT_TRUE(cm->isOk());

  std::unique_ptr<GfxImageColorMap> c1(cm->copy());
  std::unique_ptr<GfxImageColorMap> c2(cm->copy());
  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);

  EXPECT_NE(c1.get(), cm.get());
  EXPECT_NE(c2.get(), cm.get());
  EXPECT_NE(c1.get(), c2.get());
}

// Observable behavior: copy preserves basic observable properties.
TEST_F(GfxImageColorMapTest_529, CopyPreservesObservableProperties_529)
{
  auto cm = MakeDeviceRGB(8);
  ASSERT_TRUE(cm->isOk());

  std::unique_ptr<GfxImageColorMap> copy(cm->copy());
  ASSERT_NE(copy, nullptr);

  EXPECT_EQ(copy->isOk(), cm->isOk());
  EXPECT_EQ(copy->getBits(), cm->getBits());
  EXPECT_EQ(copy->getNumPixelComps(), cm->getNumPixelComps());
  EXPECT_EQ(copy->useRGBLine(), cm->useRGBLine());
  EXPECT_EQ(copy->useCMYKLine(), cm->useCMYKLine());
  EXPECT_EQ(copy->useDeviceNLine(), cm->useDeviceNLine());

  // Decode range queries should match for valid component indices.
  const int n = cm->getNumPixelComps();
  for (int i = 0; i < n; ++i) {
    EXPECT_DOUBLE_EQ(copy->getDecodeLow(i), cm->getDecodeLow(i));
    EXPECT_DOUBLE_EQ(copy->getDecodeHigh(i), cm->getDecodeHigh(i));
  }
}

// Boundary condition: smallest common bit depth.
TEST_F(GfxImageColorMapTest_529, CopyWorksAtLowBitDepth_529)
{
  auto cm = MakeDeviceRGB(1);
  ASSERT_NE(cm, nullptr);
  ASSERT_TRUE(cm->isOk());

  std::unique_ptr<GfxImageColorMap> copy(cm->copy());
  ASSERT_NE(copy, nullptr);
  EXPECT_EQ(copy->getBits(), 1);
  EXPECT_EQ(copy->getNumPixelComps(), cm->getNumPixelComps());
}

// Boundary condition: higher common bit depth.
TEST_F(GfxImageColorMapTest_529, CopyWorksAtHighBitDepth_529)
{
  auto cm = MakeDeviceRGB(16);
  ASSERT_NE(cm, nullptr);
  ASSERT_TRUE(cm->isOk());

  std::unique_ptr<GfxImageColorMap> copy(cm->copy());
  ASSERT_NE(copy, nullptr);
  EXPECT_EQ(copy->getBits(), 16);
  EXPECT_EQ(copy->getNumPixelComps(), cm->getNumPixelComps());
}

// Lifetime safety (observable): copy remains usable after original is destroyed.
TEST_F(GfxImageColorMapTest_529, CopyRemainsUsableAfterOriginalDestroyed_529)
{
  std::unique_ptr<GfxImageColorMap> copy;

  {
    auto cm = MakeDeviceRGB(8);
    ASSERT_TRUE(cm->isOk());
    copy.reset(cm->copy());
    ASSERT_NE(copy, nullptr);
    ASSERT_TRUE(copy->isOk());
    // cm goes out of scope here
  }

  // If this is a true deep copy, basic queries should remain valid.
  EXPECT_TRUE(copy->isOk());
  EXPECT_GT(copy->getNumPixelComps(), 0);
  EXPECT_GT(copy->getBits(), 0);
  EXPECT_NE(copy->getColorSpace(), nullptr);
}

// Error/exceptional case (observable): invalid construction yields !isOk (do not call copy()).
TEST_F(GfxImageColorMapTest_529, InvalidBitsYieldsNotOk_529)
{
  Object decode;
  // Use an obviously invalid bit depth (0). Observable behavior: isOk() should report failure.
  auto cm = MakeColorMap(0, static_cast<int>(csDeviceRGB), &decode);
  ASSERT_NE(cm, nullptr);
  EXPECT_FALSE(cm->isOk());

  // Intentionally do NOT call copy() on an invalid object (behavior may be undefined/unspecified).
}