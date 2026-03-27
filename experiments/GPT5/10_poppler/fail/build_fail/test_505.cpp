// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 505
//
// Unit tests for GfxShading::getHasBackground()
// File: ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include "GfxState.h"

namespace {

class GfxShadingTest_505 : public ::testing::Test {};

TEST_F(GfxShadingTest_505, GetHasBackground_IsStableAcrossCalls_505)
{
  GfxShading shading(/*typeA=*/0);

  const bool first = shading.getHasBackground();
  const bool second = shading.getHasBackground();

  EXPECT_EQ(first, second);
}

TEST_F(GfxShadingTest_505, CopyCtorFromPointer_PreservesHasBackgroundValue_505)
{
  GfxShading original(/*typeA=*/0);
  const bool originalHasBg = original.getHasBackground();

  GfxShading copied(&original);
  EXPECT_EQ(copied.getHasBackground(), originalHasBg);

  // Also ensure copied result is stable.
  EXPECT_EQ(copied.getHasBackground(), copied.getHasBackground());
}

TEST_F(GfxShadingTest_505, VirtualCopy_PreservesHasBackgroundValue_505)
{
  GfxShading original(/*typeA=*/0);
  const bool originalHasBg = original.getHasBackground();

  // copy() is part of the public interface in the provided dependency list.
  auto copied = original.copy();
  ASSERT_TRUE(static_cast<bool>(copied));

  EXPECT_EQ(copied->getHasBackground(), originalHasBg);
  EXPECT_EQ(copied->getHasBackground(), copied->getHasBackground());
}

TEST_F(GfxShadingTest_505, ConstructionWithVariousTypeValues_AllowsQueryingHasBackground_505)
{
  // Boundary-ish values for the ctor parameter (treated as black-box).
  EXPECT_NO_THROW({
    GfxShading sNeg(/*typeA=*/-1);
    (void)sNeg.getHasBackground();
  });

  EXPECT_NO_THROW({
    GfxShading sZero(/*typeA=*/0);
    (void)sZero.getHasBackground();
  });

  EXPECT_NO_THROW({
    GfxShading sLarge(/*typeA=*/2147483647);
    (void)sLarge.getHasBackground();
  });
}

} // namespace