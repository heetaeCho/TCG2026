// TEST_ID 534
// File: gfx_image_colormap_getdecodelow_ut_534.cpp

#include <gtest/gtest.h>

#include "./TestProjects/poppler/poppler/GfxState.h"

// Many Poppler builds expose Object/XRef headers in different paths;
// include opportunistically but keep tests independent from Object internals.
#if __has_include("./TestProjects/poppler/poppler/Object.h")
#include "./TestProjects/poppler/poppler/Object.h"
#endif
#if __has_include("./TestProjects/poppler/poppler/XRef.h")
#include "./TestProjects/poppler/poppler/XRef.h"
#endif

namespace {

// Helper: create a usable GfxColorSpace for constructing GfxImageColorMap
static std::unique_ptr<GfxColorSpace> makeDeviceRGBColorSpaceOrNull() {
  // Poppler commonly provides GfxColorSpace::create(mode) with enums like csDeviceRGB.
  // We avoid relying on private state; this is only to obtain a valid collaborator.
#if defined(csDeviceRGB)
  if (auto *cs = GfxColorSpace::create(csDeviceRGB)) {
    return std::unique_ptr<GfxColorSpace>(cs);
  }
#elif defined(csDeviceGray)
  // Fall back to DeviceGray if DeviceRGB isn't available in this build.
  if (auto *cs = GfxColorSpace::create(csDeviceGray)) {
    return std::unique_ptr<GfxColorSpace>(cs);
  }
#endif

  // As a last resort, return nullptr and let the tests skip if construction is impossible.
  return nullptr;
}

class GfxImageColorMapTest_534 : public ::testing::Test {
 protected:
  std::unique_ptr<GfxImageColorMap> makeMapOrSkip(int bits) {
    auto cs = makeDeviceRGBColorSpaceOrNull();
    if (!cs) {
      GTEST_SKIP() << "No creatable GfxColorSpace available in this Poppler build.";
    }

    // Decode can often be nullptr to mean "use defaults"; we don't assume what defaults are.
    // The tests only compare observable behavior (stability, copy consistency).
    Object *decode = nullptr;

    auto map = std::make_unique<GfxImageColorMap>(bits, decode, std::move(cs));
    if (!map->isOk()) {
      GTEST_SKIP() << "Constructed GfxImageColorMap is not OK in this build/config.";
    }
    return map;
  }
};

}  // namespace

// Normal operation: getDecodeLow should be stable across repeated calls for same index.
TEST_F(GfxImageColorMapTest_534, GetDecodeLow_IsStableAcrossRepeatedCalls_534) {
  auto map = makeMapOrSkip(/*bits=*/8);

  const int n = map->getNumPixelComps();
  ASSERT_GT(n, 0);

  // Test first and last component indices.
  const int idxs[] = {0, n - 1};
  for (int idx : idxs) {
    const double v1 = map->getDecodeLow(idx);
    const double v2 = map->getDecodeLow(idx);
    const double v3 = map->getDecodeLow(idx);
    EXPECT_DOUBLE_EQ(v1, v2);
    EXPECT_DOUBLE_EQ(v2, v3);
  }
}

// Boundary conditions: iterate all valid component indices and ensure calls do not crash
// and are stable per-index (no assumption about actual numeric values).
TEST_F(GfxImageColorMapTest_534, GetDecodeLow_ForAllValidIndices_IsCallableAndStable_534) {
  auto map = makeMapOrSkip(/*bits=*/8);

  const int n = map->getNumPixelComps();
  ASSERT_GT(n, 0);

  for (int i = 0; i < n; ++i) {
    const double a = map->getDecodeLow(i);
    const double b = map->getDecodeLow(i);
    EXPECT_DOUBLE_EQ(a, b) << "index=" << i;
  }
}

// Normal operation + external interaction verification (copy): copy() should preserve
// observable decodeLow behavior per component index.
TEST_F(GfxImageColorMapTest_534, Copy_PreservesGetDecodeLowForEachComponent_534) {
  auto map = makeMapOrSkip(/*bits=*/8);

  std::unique_ptr<GfxImageColorMap> copy(map->copy());
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->isOk());

  const int n1 = map->getNumPixelComps();
  const int n2 = copy->getNumPixelComps();
  ASSERT_EQ(n1, n2);
  ASSERT_GT(n1, 0);

  for (int i = 0; i < n1; ++i) {
    EXPECT_DOUBLE_EQ(map->getDecodeLow(i), copy->getDecodeLow(i)) << "index=" << i;
  }
}

// Boundary/robustness: copy remains usable after original is destroyed.
TEST_F(GfxImageColorMapTest_534, Copy_RemainsUsableAfterOriginalDestroyed_534) {
  std::unique_ptr<GfxImageColorMap> copy;

  {
    auto map = makeMapOrSkip(/*bits=*/8);
    copy.reset(map->copy());
    ASSERT_NE(copy, nullptr);
    ASSERT_TRUE(copy->isOk());
  }  // original destroyed here

  const int n = copy->getNumPixelComps();
  ASSERT_GT(n, 0);

  // Access first/last after original is gone.
  EXPECT_NO_THROW({ (void)copy->getDecodeLow(0); });
  EXPECT_NO_THROW({ (void)copy->getDecodeLow(n - 1); });
}

// Boundary conditions: construction with different bit depths should still allow getDecodeLow
// calls for valid indices (no assumptions about the numeric values).
TEST_F(GfxImageColorMapTest_534, GetDecodeLow_WorksAcrossCommonBitDepths_534) {
  const int bitDepths[] = {1, 2, 4, 8, 16};

  for (int bits : bitDepths) {
    auto map = makeMapOrSkip(bits);
    const int n = map->getNumPixelComps();
    ASSERT_GT(n, 0) << "bits=" << bits;

    // Just verify callable/stable for a representative index.
    const int idx = 0;
    const double v1 = map->getDecodeLow(idx);
    const double v2 = map->getDecodeLow(idx);
    EXPECT_DOUBLE_EQ(v1, v2) << "bits=" << bits;
  }
}