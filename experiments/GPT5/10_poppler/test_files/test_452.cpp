// File: GfxLabColorSpace_getBlackX_452_test.cpp
#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "poppler/GfxState.h"

namespace {

class GfxLabColorSpaceTest_452 : public ::testing::Test {};

TEST_F(GfxLabColorSpaceTest_452, DefaultConstructed_ReturnsFiniteValue_452) {
  GfxLabColorSpace cs;
  const double x = cs.getBlackX();

  // Observable, implementation-agnostic sanity: should not be NaN/Inf.
  EXPECT_TRUE(std::isfinite(x));
}

TEST_F(GfxLabColorSpaceTest_452, RepeatedCalls_AreStable_452) {
  GfxLabColorSpace cs;

  const double x1 = cs.getBlackX();
  const double x2 = cs.getBlackX();
  const double x3 = cs.getBlackX();

  // Getter should be stable for the same instance (no observable side-effects).
  EXPECT_DOUBLE_EQ(x1, x2);
  EXPECT_DOUBLE_EQ(x2, x3);
}

TEST_F(GfxLabColorSpaceTest_452, ConstGetter_CanBeCalledOnConstInstance_452) {
  const GfxLabColorSpace cs;
  const double x = cs.getBlackX();

  EXPECT_TRUE(std::isfinite(x));
}

TEST_F(GfxLabColorSpaceTest_452, Copy_PreservesBlackX_452) {
  GfxLabColorSpace original;
  const double x0 = original.getBlackX();

  std::unique_ptr<GfxColorSpace> copiedBase = original.copy();
  ASSERT_NE(copiedBase, nullptr);

  auto *copiedLab = dynamic_cast<GfxLabColorSpace *>(copiedBase.get());
  ASSERT_NE(copiedLab, nullptr) << "copy() should preserve the dynamic type for GfxLabColorSpace";

  EXPECT_DOUBLE_EQ(x0, copiedLab->getBlackX());
}

TEST_F(GfxLabColorSpaceTest_452, MultipleInstances_HaveIndependentlyReadableBlackX_452) {
  GfxLabColorSpace cs1;
  GfxLabColorSpace cs2;

  const double x1 = cs1.getBlackX();
  const double x2 = cs2.getBlackX();

  // We don't assume equality across instances (implementation-defined), but both must be readable/sane.
  EXPECT_TRUE(std::isfinite(x1));
  EXPECT_TRUE(std::isfinite(x2));

  // And stable per-instance.
  EXPECT_DOUBLE_EQ(x1, cs1.getBlackX());
  EXPECT_DOUBLE_EQ(x2, cs2.getBlackX());
}

}  // namespace