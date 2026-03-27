// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 458
//
// Unit tests for GfxLabColorSpace::getBMax()
// File: ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include "GfxState.h"

namespace {

class GfxLabColorSpaceTest_458 : public ::testing::Test {};

TEST_F(GfxLabColorSpaceTest_458, GetBMax_CanBeCalledOnConstObject_458) {
  const GfxLabColorSpace cs;
  // Primary observable behavior: callable and returns a double.
  const double bMax = cs.getBMax();
  (void)bMax; // Avoid unused warnings in case of -Werror.
}

TEST_F(GfxLabColorSpaceTest_458, GetBMax_IsStableAcrossMultipleCalls_458) {
  GfxLabColorSpace cs;

  const double first = cs.getBMax();
  const double second = cs.getBMax();
  const double third = cs.getBMax();

  EXPECT_DOUBLE_EQ(first, second);
  EXPECT_DOUBLE_EQ(second, third);
}

TEST_F(GfxLabColorSpaceTest_458, GetBMax_IsPreservedByCopyPolymorphic_458) {
  GfxLabColorSpace cs;

  const double original = cs.getBMax();

  // copy() is part of the public interface (polymorphic).
  const std::unique_ptr<GfxColorSpace> copiedBase = cs.copy();
  ASSERT_NE(copiedBase, nullptr);

  auto *copiedLab = dynamic_cast<GfxLabColorSpace *>(copiedBase.get());
  ASSERT_NE(copiedLab, nullptr);

  EXPECT_DOUBLE_EQ(original, copiedLab->getBMax());
}

TEST_F(GfxLabColorSpaceTest_458, GetBMax_DoesNotChangeAcrossIndependentCopies_458) {
  GfxLabColorSpace cs;

  const std::unique_ptr<GfxColorSpace> copy1 = cs.copy();
  const std::unique_ptr<GfxColorSpace> copy2 = cs.copy();

  ASSERT_NE(copy1, nullptr);
  ASSERT_NE(copy2, nullptr);

  auto *lab1 = dynamic_cast<GfxLabColorSpace *>(copy1.get());
  auto *lab2 = dynamic_cast<GfxLabColorSpace *>(copy2.get());
  ASSERT_NE(lab1, nullptr);
  ASSERT_NE(lab2, nullptr);

  EXPECT_DOUBLE_EQ(lab1->getBMax(), lab2->getBMax());
  EXPECT_DOUBLE_EQ(cs.getBMax(), lab1->getBMax());
}

} // namespace