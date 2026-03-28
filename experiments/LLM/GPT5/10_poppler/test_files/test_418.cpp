// TEST_ID: 418
//
// Unit tests for GfxCalGrayColorSpace::getBlackX()
// File: poppler/GfxState.h
//
// Notes:
// - We treat the implementation as a black box.
// - With only the provided partial interface, the observable contract is:
//     * getBlackX() is const, returns a double, and is callable.
// - We avoid assuming default/expected numeric values (e.g., 0.0) because the
//   constructor/initialization behavior is not part of the provided interface.
//
// If your build exposes the full Poppler headers, this should compile as-is.
// If Poppler uses different include paths in your project, adjust includes.

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <type_traits>

// Use the project's real include path if different.
#include "poppler/GfxState.h"

namespace {

// A tiny helper to check "this double looks like a real number" without
// assuming a specific value.
static bool IsFinite(double v) {
  return std::isfinite(v);
}

}  // namespace

class GfxCalGrayColorSpaceTest_418 : public ::testing::Test {};

TEST_F(GfxCalGrayColorSpaceTest_418, GetBlackX_IsCallableAndReturnsDouble_418) {
  GfxCalGrayColorSpace cs;

  // Compile-time: exact return type.
  static_assert(std::is_same_v<decltype(cs.getBlackX()), double>,
                "getBlackX() must return double");

  // Runtime: callable and yields a value.
  const double bx = cs.getBlackX();
  (void)bx;
  SUCCEED();
}

TEST_F(GfxCalGrayColorSpaceTest_418, GetBlackX_IsConstCorrect_418) {
  const GfxCalGrayColorSpace cs;

  // If this compiles, the method is const-correct.
  const double bx = cs.getBlackX();
  (void)bx;
  SUCCEED();
}

TEST_F(GfxCalGrayColorSpaceTest_418, GetBlackX_IsStableAcrossRepeatedCalls_418) {
  const GfxCalGrayColorSpace cs;

  const double v1 = cs.getBlackX();
  const double v2 = cs.getBlackX();
  const double v3 = cs.getBlackX();

  // Minimal observable expectation: repeated calls on the same const object
  // should be stable/deterministic for a simple getter.
  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

TEST_F(GfxCalGrayColorSpaceTest_418, GetBlackX_ReturnIsNotNaN_418) {
  const GfxCalGrayColorSpace cs;

  const double bx = cs.getBlackX();

  // Boundary/error-observable check: NaN is typically an invalid getter result.
  // We do NOT assert any specific numeric value.
  EXPECT_FALSE(std::isnan(bx));
}

TEST_F(GfxCalGrayColorSpaceTest_418, GetBlackX_IsFiniteOrDocumentedOtherwise_418) {
  const GfxCalGrayColorSpace cs;

  const double bx = cs.getBlackX();

  // If Poppler ever uses +/-inf as sentinel, this test would fail and should be
  // revisited with concrete interface documentation. For typical color space
  // parameters, finite is expected.
  EXPECT_TRUE(IsFinite(bx));
}

TEST_F(GfxCalGrayColorSpaceTest_418, GetBlackX_SupportsExtremeComparisons_418) {
  const GfxCalGrayColorSpace cs;

  const double bx = cs.getBlackX();

  // Boundary-style checks that do not assume a specific range:
  // - Value compares consistently against itself and standard limits.
  EXPECT_EQ(bx, bx);
  EXPECT_TRUE(bx <= std::numeric_limits<double>::infinity());
  EXPECT_TRUE(bx >= -std::numeric_limits<double>::infinity());
}