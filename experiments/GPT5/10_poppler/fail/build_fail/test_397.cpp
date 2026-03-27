// SPDX-License-Identifier: GPL-2.0-or-later
// File: gfxcolortransform_getintent_test_397.cc
//
// Unit tests for GfxColorTransform::getIntent()
// Based strictly on the provided public interface.
//
// TEST_ID: 397

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "poppler/GfxState.h"

// Compile-time interface checks (observable at compile time, no internal access).
static_assert(!std::is_copy_constructible_v<GfxColorTransform>,
              "GfxColorTransform must not be copy constructible");
static_assert(!std::is_copy_assignable_v<GfxColorTransform>,
              "GfxColorTransform must not be copy assignable");

// Helper to create a transform object with a "safe" transform pointer value.
// We prefer nullptr because many implementations treat it as a no-op on destroy.
static GfxColorTransform MakeTransform(int intent,
                                      unsigned int inType = 0u,
                                      unsigned int outType = 0u) {
  return GfxColorTransform(/*transformA=*/nullptr, intent, inType, outType);
}

TEST(GfxColorTransformTest_397, GetIntentReturnsConstructorIntent_397) {
  auto t = MakeTransform(/*intent=*/0);
  EXPECT_EQ(t.getIntent(), 0);
}

TEST(GfxColorTransformTest_397, GetIntentSupportsNegativeIntent_397) {
  auto t = MakeTransform(/*intent=*/-1);
  EXPECT_EQ(t.getIntent(), -1);
}

TEST(GfxColorTransformTest_397, GetIntentSupportsLargePositiveIntent_397) {
  // Use a large value that still fits in int.
  const int kLarge = 1'000'000'000;
  auto t = MakeTransform(/*intent=*/kLarge);
  EXPECT_EQ(t.getIntent(), kLarge);
}

TEST(GfxColorTransformTest_397, GetIntentUnaffectedByPixelTypeArguments_397) {
  // getIntent() should reflect the intent argument regardless of pixel type params.
  // This is observable solely via the public API (constructor + getIntent()).
  auto t1 = MakeTransform(/*intent=*/3, /*inType=*/0u, /*outType=*/0u);
  auto t2 = MakeTransform(/*intent=*/3, /*inType=*/42u, /*outType=*/7u);

  EXPECT_EQ(t1.getIntent(), 3);
  EXPECT_EQ(t2.getIntent(), 3);
}

TEST(GfxColorTransformTest_397, GetIntentIsConstCallable_397) {
  const auto t = MakeTransform(/*intent=*/2);
  EXPECT_EQ(t.getIntent(), 2);
}