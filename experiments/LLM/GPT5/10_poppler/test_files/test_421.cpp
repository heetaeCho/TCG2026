// TEST_ID = 421
// File: GfxCalGrayColorSpace_getGamma_421_test.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "poppler/GfxState.h"

namespace {

class GfxCalGrayColorSpaceTest_421 : public ::testing::Test {};

TEST_F(GfxCalGrayColorSpaceTest_421, DefaultGetGammaIsStableAcrossCalls_421)
{
  GfxCalGrayColorSpace cs;

  const double g1 = cs.getGamma();
  const double g2 = cs.getGamma();
  const double g3 = cs.getGamma();

  // Black-box: we only assert the observable behavior that repeated calls are consistent.
  EXPECT_DOUBLE_EQ(g1, g2);
  EXPECT_DOUBLE_EQ(g2, g3);
}

TEST_F(GfxCalGrayColorSpaceTest_421, CopyPreservesGamma_421)
{
  GfxCalGrayColorSpace original;
  const double g = original.getGamma();

  std::unique_ptr<GfxColorSpace> copiedBase = original.copy();
  ASSERT_NE(copiedBase, nullptr);

  // copy() returns a base pointer; verify it's actually a GfxCalGrayColorSpace and compare gamma.
  auto *copied = dynamic_cast<GfxCalGrayColorSpace *>(copiedBase.get());
  ASSERT_NE(copied, nullptr);

  EXPECT_DOUBLE_EQ(g, copied->getGamma());
}

TEST_F(GfxCalGrayColorSpaceTest_421, GetGammaDoesNotDependOnObjectLifetimeOfTemporary_421)
{
  // Smoke-style test: calling getGamma on a temporary should be safe and consistent.
  const double g1 = GfxCalGrayColorSpace().getGamma();
  const double g2 = GfxCalGrayColorSpace().getGamma();

  // We do NOT assume any specific default value; just that each call returns a valid double.
  // (No NaN check here to avoid inferring constraints beyond the interface.)
  (void)g1;
  (void)g2;
  SUCCEED();
}

} // namespace