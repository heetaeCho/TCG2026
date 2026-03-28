// TEST_ID: 504
// Unit tests for GfxShading::getBackground()
// File: gfxshading_getbackground_unittest_504.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#if __has_include("poppler/GfxState.h")
#include "poppler/GfxState.h"
#elif __has_include("GfxState.h")
#include "GfxState.h"
#else
#error "Cannot find GfxState.h (expected <poppler/GfxState.h> or <GfxState.h>)"
#endif

namespace {

class GfxShadingTest_504 : public ::testing::Test {};

TEST_F(GfxShadingTest_504, GetBackground_ReturnsNonNullPointer_504) {
  GfxShading shading(/*typeA=*/0);

  const GfxColor *bg = shading.getBackground();
  ASSERT_NE(bg, nullptr);
}

TEST_F(GfxShadingTest_504, GetBackground_ReturnsStableAddressAcrossCalls_504) {
  GfxShading shading(/*typeA=*/0);

  const GfxColor *bg1 = shading.getBackground();
  const GfxColor *bg2 = shading.getBackground();

  ASSERT_NE(bg1, nullptr);
  EXPECT_EQ(bg1, bg2);
}

TEST_F(GfxShadingTest_504, GetBackground_PointersDifferBetweenDistinctInstances_504) {
  GfxShading shading1(/*typeA=*/0);
  GfxShading shading2(/*typeA=*/0);

  const GfxColor *bg1 = shading1.getBackground();
  const GfxColor *bg2 = shading2.getBackground();

  ASSERT_NE(bg1, nullptr);
  ASSERT_NE(bg2, nullptr);

  // Background is a per-instance member; the returned pointer should refer to that instance's storage.
  EXPECT_NE(bg1, bg2);
}

TEST_F(GfxShadingTest_504, GetBackground_FromConstObject_ReturnTypeIsConstPointer_504) {
  const GfxShading shading(/*typeA=*/0);

  // Compile-time interface check: return type should be "const GfxColor *".
  static_assert(std::is_same_v<decltype(std::declval<const GfxShading &>().getBackground()),
                               const GfxColor *>,
                "GfxShading::getBackground() must return const GfxColor* for const objects.");

  const GfxColor *bg = shading.getBackground();
  ASSERT_NE(bg, nullptr);
}

TEST_F(GfxShadingTest_504, GetBackground_CopyConstructedFromPointer_UsesDistinctStorage_504) {
  GfxShading original(/*typeA=*/0);
  GfxShading copyFromPtr(&original);

  const GfxColor *origBg = original.getBackground();
  const GfxColor *copyBg = copyFromPtr.getBackground();

  ASSERT_NE(origBg, nullptr);
  ASSERT_NE(copyBg, nullptr);

  // Each instance should return the address of its own background member.
  EXPECT_NE(origBg, copyBg);
}

}  // namespace