// TEST_ID: 495
// File: GfxTilingPattern_getXStep_495_test.cpp
//
// Unit tests for GfxTilingPattern::getXStep() based strictly on observable interface.
// We do NOT assume internal logic. We only check that:
//  - getXStep() is callable and returns a stable (repeatable) value for the same instance.
//  - It can be invoked on a const reference.
//  - Boundary/edge observations: result is a finite double (not NaN/Inf) when an instance exists.
//  - Null/invalid pointer usage is not tested (would be UB).
//
// Note: Creating a real GfxTilingPattern instance is not possible from the partial interface:
//  - constructor is private
//  - parse() requires Poppler's Object graph
//
// Therefore these tests are compiled only when a test hook/factory is available.
// If your build exposes Poppler internals for tests, define POPPLER_HAS_GFX_TILING_PATTERN_FACTORY
// and provide MakeGfxTilingPatternForTest(...) accordingly.

#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include <type_traits>

#include "poppler/GfxState.h"

namespace {

// If your Poppler build provides a way to construct a GfxTilingPattern for tests,
// implement this factory in your test support library and enable the macro.
//
// Expected signature (example):
// std::unique_ptr<GfxTilingPattern> MakeGfxTilingPatternForTest(double xStep);
//
// You can also build it via parse(Object*, int) if you have helpers to construct Object patObj.
#if defined(POPPLER_HAS_GFX_TILING_PATTERN_FACTORY)
std::unique_ptr<GfxTilingPattern> MakeGfxTilingPatternForTest(double xStep);
#endif

class GfxTilingPatternTest_495 : public ::testing::Test {
protected:
#if defined(POPPLER_HAS_GFX_TILING_PATTERN_FACTORY)
  static std::unique_ptr<GfxTilingPattern> Make(double xStep) {
    return MakeGfxTilingPatternForTest(xStep);
  }
#endif
};

TEST_F(GfxTilingPatternTest_495, GetXStep_IsConstCallableAndReturnsDouble_495) {
  // Compile-time property: getXStep returns a double and is callable on const object.
  static_assert(std::is_same_v<decltype(std::declval<const GfxTilingPattern&>().getXStep()), double>,
                "GfxTilingPattern::getXStep() must return double and be const-callable");
  SUCCEED();
}

#if defined(POPPLER_HAS_GFX_TILING_PATTERN_FACTORY)

TEST_F(GfxTilingPatternTest_495, GetXStep_IsStableAcrossMultipleCalls_495) {
  auto pat = Make(1.25);
  ASSERT_NE(pat, nullptr);

  const double v1 = pat->getXStep();
  const double v2 = pat->getXStep();
  const double v3 = pat->getXStep();

  // Observable requirement: same instance, repeated getter calls should be stable.
  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

TEST_F(GfxTilingPatternTest_495, GetXStep_CanBeCalledThroughConstReference_495) {
  auto pat = Make(2.0);
  ASSERT_NE(pat, nullptr);

  const GfxTilingPattern& cref = *pat;
  const double v = cref.getXStep();

  // We do not assume it equals the input; only that it returns a valid double.
  EXPECT_TRUE(std::isfinite(v));
}

TEST_F(GfxTilingPatternTest_495, GetXStep_HandlesZeroStepValue_495) {
  auto pat = Make(0.0);
  ASSERT_NE(pat, nullptr);

  const double v = pat->getXStep();

  // Boundary condition: for an existing object, getter should produce a finite double.
  EXPECT_TRUE(std::isfinite(v));
}

TEST_F(GfxTilingPatternTest_495, GetXStep_HandlesNegativeStepValue_495) {
  auto pat = Make(-3.5);
  ASSERT_NE(pat, nullptr);

  const double v = pat->getXStep();

  // Boundary condition: we do not define semantics of negative step; only that it is observable and finite.
  EXPECT_TRUE(std::isfinite(v));
}

TEST_F(GfxTilingPatternTest_495, GetXStep_HandlesLargeMagnitudeStepValue_495) {
  auto pat = Make(1e300);
  ASSERT_NE(pat, nullptr);

  const double v = pat->getXStep();

  // Large values: must remain a representable finite double for observation purposes.
  EXPECT_TRUE(std::isfinite(v));
}

#endif  // POPPLER_HAS_GFX_TILING_PATTERN_FACTORY

}  // namespace