// TEST_ID: 432
// File: GfxCalRGBColorSpace_getWhiteX_test.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "poppler/GfxState.h"

namespace {

class GfxCalRGBColorSpaceTest_432 : public ::testing::Test {};

TEST_F(GfxCalRGBColorSpaceTest_432, GetWhiteX_IsFinite_432)
{
  GfxCalRGBColorSpace cs;
  const double x = cs.getWhiteX();

  // Black-box observable property: should be a valid numeric value.
  EXPECT_TRUE(std::isfinite(x));
}

TEST_F(GfxCalRGBColorSpaceTest_432, GetWhiteX_IsStableAcrossCalls_432)
{
  GfxCalRGBColorSpace cs;

  const double x1 = cs.getWhiteX();
  const double x2 = cs.getWhiteX();
  const double x3 = cs.getWhiteX();

  // Repeated calls should be consistent for a const getter.
  EXPECT_EQ(x1, x2);
  EXPECT_EQ(x2, x3);
}

TEST_F(GfxCalRGBColorSpaceTest_432, Copy_PreservesWhiteX_WhenSameConcreteType_432)
{
  GfxCalRGBColorSpace cs;
  const double origX = cs.getWhiteX();

  const std::unique_ptr<GfxColorSpace> copiedBase = cs.copy();
  ASSERT_NE(copiedBase, nullptr);

  // If copy() preserves the dynamic type (expected for copy/clone),
  // then the observable getter should match.
  auto *copied = dynamic_cast<GfxCalRGBColorSpace *>(copiedBase.get());
  ASSERT_NE(copied, nullptr);

  EXPECT_EQ(copied->getWhiteX(), origX);
}

TEST_F(GfxCalRGBColorSpaceTest_432, Copy_DoesNotAliasOriginal_ObjectIsIndependent_432)
{
  GfxCalRGBColorSpace cs;

  const std::unique_ptr<GfxColorSpace> copiedBase = cs.copy();
  ASSERT_NE(copiedBase, nullptr);

  // Observable boundary: ensure distinct objects.
  EXPECT_NE(copiedBase.get(), static_cast<GfxColorSpace *>(&cs));

  // And calling getters on both remains valid.
  EXPECT_TRUE(std::isfinite(cs.getWhiteX()));
  auto *copied = dynamic_cast<GfxCalRGBColorSpace *>(copiedBase.get());
  ASSERT_NE(copied, nullptr);
  EXPECT_TRUE(std::isfinite(copied->getWhiteX()));
}

} // namespace