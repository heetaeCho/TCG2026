// TEST_ID: 531
// File: GfxImageColorMap_getColorSpace_531_test.cpp

#include <gtest/gtest.h>

#include <memory>

#include "GfxState.h"
#include "Object.h"

namespace {

class GfxImageColorMapTest_531 : public ::testing::Test {
protected:
  // Poppler's Object defaults to null in most versions, but keep this helper
  // explicit and local to tests.
  static Object MakeNullObject()
  {
    Object o;
    // If Object supports initNull(), use it; otherwise default-constructed is fine.
    // We avoid relying on Object internals by not asserting how it stores null.
#if defined(__clang__) || defined(__GNUC__) || defined(_MSC_VER)
    // Best-effort: call initNull() if it exists (SFINAE would be overkill here).
    // If your Poppler version doesn't have initNull(), remove this block.
    // NOLINTNEXTLINE(bugprone-branch-clone)
    try {
      o.initNull();
    } catch (...) {
      // Poppler Object typically doesn't throw; ignore if initNull() isn't available
      // in your build and you removed/disabled exceptions.
    }
#endif
    return o;
  }
};

TEST_F(GfxImageColorMapTest_531, GetColorSpaceReturnsSamePointerPassedIn_531)
{
  Object decode = MakeNullObject();

  auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
  GfxColorSpace *expected = cs.get();

  GfxImageColorMap map(/*bitsA=*/8, &decode, std::move(cs));

  ASSERT_NE(map.getColorSpace(), nullptr);
  EXPECT_EQ(map.getColorSpace(), expected);
  EXPECT_EQ(map.getColorSpace()->getMode(), csDeviceRGB);
}

TEST_F(GfxImageColorMapTest_531, GetColorSpaceIsStableAcrossMultipleCalls_531)
{
  Object decode = MakeNullObject();

  auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
  GfxColorSpace *expected = cs.get();

  GfxImageColorMap map(/*bitsA=*/8, &decode, std::move(cs));

  GfxColorSpace *first = map.getColorSpace();
  ASSERT_NE(first, nullptr);
  EXPECT_EQ(first, expected);

  // Repeated calls should not change the returned pointer.
  EXPECT_EQ(map.getColorSpace(), first);
  EXPECT_EQ(map.getColorSpace()->getMode(), csDeviceGray);
}

TEST_F(GfxImageColorMapTest_531, GetColorSpaceWorksAtLowerBitBoundary_531)
{
  Object decode = MakeNullObject();

  auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
  GfxColorSpace *expected = cs.get();

  // Boundary: smallest sensible bit depth for image components is often 1.
  GfxImageColorMap map(/*bitsA=*/1, &decode, std::move(cs));

  ASSERT_NE(map.getColorSpace(), nullptr);
  EXPECT_EQ(map.getColorSpace(), expected);
  EXPECT_EQ(map.getColorSpace()->getMode(), csDeviceRGB);
}

TEST_F(GfxImageColorMapTest_531, GetColorSpaceWorksAtUpperBitBoundary_531)
{
  Object decode = MakeNullObject();

  auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
  GfxColorSpace *expected = cs.get();

  // Boundary: many implementations support up to 16 bits/component.
  GfxImageColorMap map(/*bitsA=*/16, &decode, std::move(cs));

  ASSERT_NE(map.getColorSpace(), nullptr);
  EXPECT_EQ(map.getColorSpace(), expected);
  EXPECT_EQ(map.getColorSpace()->getMode(), csDeviceCMYK);
}

TEST_F(GfxImageColorMapTest_531, CopyPreservesColorSpaceMode_531)
{
  Object decode = MakeNullObject();

  auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
  GfxImageColorMap map(/*bitsA=*/8, &decode, std::move(cs));

  ASSERT_NE(map.getColorSpace(), nullptr);
  const auto originalMode = map.getColorSpace()->getMode();

  std::unique_ptr<GfxImageColorMap> copied(map.copy());
  ASSERT_NE(copied, nullptr);
  ASSERT_NE(copied->getColorSpace(), nullptr);

  // Observable behavior: copied map reports a color space with the same mode.
  EXPECT_EQ(copied->getColorSpace()->getMode(), originalMode);
}

TEST_F(GfxImageColorMapTest_531, GetColorSpaceCallableEvenIfMapReportsNotOk_531)
{
  Object decode = MakeNullObject();

  auto cs = std::make_unique<GfxDeviceRGBColorSpace>();

  // Intentionally pass an unusual bit depth as an "error-ish" input.
  // We do NOT assume how isOk() is computed; we only observe the interface.
  GfxImageColorMap map(/*bitsA=*/0, &decode, std::move(cs));

  // Regardless of ok-ness, calling getColorSpace() should be safe/observable.
  // If your Poppler build treats bitsA=0 as fatal, adjust this boundary value.
  GfxColorSpace *space = map.getColorSpace();
  // Either nullptr or a valid pointer are acceptable outcomes here; the key
  // behavior under test is that the call is valid and returns consistently.
  EXPECT_EQ(map.getColorSpace(), space);
}

} // namespace