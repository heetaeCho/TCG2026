// SPDX-License-Identifier: GPL-2.0-or-later
// File: GfxCalRGBColorSpace_getGammaG_test.cpp
//
// Unit tests for GfxCalRGBColorSpace::getGammaG()
// Constraints: treat implementation as black box; do not access private state.

#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "poppler/GfxState.h"

namespace {

class GfxCalRGBColorSpaceTest_439 : public ::testing::Test {
protected:
  GfxCalRGBColorSpace cs;
};

TEST_F(GfxCalRGBColorSpaceTest_439, GetGammaG_DoesNotThrow_439) {
  EXPECT_NO_THROW({
    volatile double g = cs.getGammaG();
    (void)g;
  });
}

TEST_F(GfxCalRGBColorSpaceTest_439, GetGammaG_IsStableAcrossRepeatedCalls_439) {
  const double g1 = cs.getGammaG();
  const double g2 = cs.getGammaG();
  const double g3 = cs.getGammaG();

  EXPECT_EQ(g1, g2);
  EXPECT_EQ(g2, g3);
}

TEST_F(GfxCalRGBColorSpaceTest_439, GetGammaG_IsFinite_439) {
  const double g = cs.getGammaG();
  EXPECT_TRUE(std::isfinite(g));
}

TEST_F(GfxCalRGBColorSpaceTest_439, Copy_PreservesGammaG_439) {
  // copy() is part of the public interface; verify observable behavior only.
  std::unique_ptr<GfxColorSpace> baseCopy;
  ASSERT_NO_THROW({ baseCopy = cs.copy(); });
  ASSERT_NE(baseCopy, nullptr);

  auto *calCopy = dynamic_cast<GfxCalRGBColorSpace *>(baseCopy.get());
  ASSERT_NE(calCopy, nullptr);

  EXPECT_EQ(cs.getGammaG(), calCopy->getGammaG());
}

}  // namespace