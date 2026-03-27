// SPDX-License-Identifier: GPL-2.0-or-later
// File: GfxLabColorSpace_getAMin_test.cpp
//
// Unit tests for GfxLabColorSpace::getAMin()
// TEST_ID: 455

#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include <type_traits>

#include "GfxState.h"

class GfxLabColorSpaceTest_455 : public ::testing::Test {
protected:
  GfxLabColorSpace cs;
};

TEST_F(GfxLabColorSpaceTest_455, GetAMin_IsStableAcrossMultipleCalls_455) {
  const double a1 = cs.getAMin();
  const double a2 = cs.getAMin();
  EXPECT_EQ(a1, a2);
}

TEST_F(GfxLabColorSpaceTest_455, GetAMin_IsFinite_455) {
  const double a = cs.getAMin();
  EXPECT_TRUE(std::isfinite(a));
}

TEST_F(GfxLabColorSpaceTest_455, Copy_ReturnsNonNullAndPreservesGetAMin_455) {
  const double original = cs.getAMin();

  std::unique_ptr<GfxColorSpace> copiedBase = cs.copy();
  ASSERT_NE(copiedBase, nullptr);

  // Verify we can observe the same behavior on the copied object via public API.
  // If RTTI is disabled in the build, this test may need to be adjusted at the build-system level.
  auto *copied = dynamic_cast<GfxLabColorSpace *>(copiedBase.get());
  ASSERT_NE(copied, nullptr);

  EXPECT_EQ(copied->getAMin(), original);
}

TEST_F(GfxLabColorSpaceTest_455, MultipleInstances_HaveIndependentlyCallableGetAMin_455) {
  GfxLabColorSpace other;

  // No assumptions about actual values; only that calls are well-defined and stable per instance.
  const double a_this_1 = cs.getAMin();
  const double a_this_2 = cs.getAMin();
  const double a_other_1 = other.getAMin();
  const double a_other_2 = other.getAMin();

  EXPECT_EQ(a_this_1, a_this_2);
  EXPECT_EQ(a_other_1, a_other_2);
  EXPECT_TRUE(std::isfinite(a_this_1));
  EXPECT_TRUE(std::isfinite(a_other_1));
}

TEST_F(GfxLabColorSpaceTest_455, Copy_DoesNotAliasOriginalObject_455) {
  std::unique_ptr<GfxColorSpace> copiedBase = cs.copy();
  ASSERT_NE(copiedBase, nullptr);

  // Observable non-aliasing: the returned pointer should not be the same object address.
  EXPECT_NE(copiedBase.get(), static_cast<GfxColorSpace *>(&cs));
}