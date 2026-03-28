// TEST_ID: 456
#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "GfxState.h"

class GfxLabColorSpaceTest_456 : public ::testing::Test {};

TEST_F(GfxLabColorSpaceTest_456, GetAMax_CanBeCalledOnConstObject_456)
{
  const GfxLabColorSpace cs;
  // Observable behavior: method is callable and returns a double.
  (void)cs.getAMax();
}

TEST_F(GfxLabColorSpaceTest_456, GetAMax_IsStableAcrossMultipleCalls_456)
{
  const GfxLabColorSpace cs;

  const double a1 = cs.getAMax();
  const double a2 = cs.getAMax();
  const double a3 = cs.getAMax();

  // Without inferring any specific value, we can assert consistency.
  EXPECT_DOUBLE_EQ(a1, a2);
  EXPECT_DOUBLE_EQ(a2, a3);
}

TEST_F(GfxLabColorSpaceTest_456, Copy_ReturnsNonNullAndPreservesGetAMax_456)
{
  const GfxLabColorSpace original;

  std::unique_ptr<GfxColorSpace> copiedBase = original.copy();
  ASSERT_NE(copiedBase, nullptr);

  auto *copied = dynamic_cast<GfxLabColorSpace *>(copiedBase.get());
  ASSERT_NE(copied, nullptr);

  EXPECT_DOUBLE_EQ(original.getAMax(), copied->getAMax());
}

TEST_F(GfxLabColorSpaceTest_456, Copy_ReturnsDistinctObject_456)
{
  const GfxLabColorSpace original;

  std::unique_ptr<GfxColorSpace> copiedBase = original.copy();
  ASSERT_NE(copiedBase, nullptr);

  // Observable: the copy should be a different object instance.
  EXPECT_NE(static_cast<const void *>(&original),
            static_cast<const void *>(copiedBase.get()));

  // If the copy is also a GfxLabColorSpace, verify it doesn't alias the original.
  auto *copied = dynamic_cast<GfxLabColorSpace *>(copiedBase.get());
  if (copied) {
    EXPECT_NE(static_cast<const void *>(&original), static_cast<const void *>(copied));
  }
}