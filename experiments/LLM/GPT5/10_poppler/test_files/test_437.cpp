// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 437
//
// Unit tests for GfxCalRGBColorSpace::getBlackZ()
// File: ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include <memory>

#include "poppler/GfxState.h"

namespace {

class GfxCalRGBColorSpaceTest_437 : public ::testing::Test {};

TEST_F(GfxCalRGBColorSpaceTest_437, GetBlackZ_IsCallableOnConstObject_437) {
  const GfxCalRGBColorSpace cs;
  // Behavior: callable and returns a double (observable: compilation + no crash).
  (void)cs.getBlackZ();
}

TEST_F(GfxCalRGBColorSpaceTest_437, GetBlackZ_IsStableAcrossRepeatedCalls_437) {
  GfxCalRGBColorSpace cs;

  const double z1 = cs.getBlackZ();
  const double z2 = cs.getBlackZ();
  const double z3 = cs.getBlackZ();

  // Observable behavior without assuming the actual numeric value:
  // repeated calls should be consistent for an unchanged object.
  EXPECT_EQ(z1, z2);
  EXPECT_EQ(z2, z3);
}

TEST_F(GfxCalRGBColorSpaceTest_437, Copy_PreservesBlackZValue_437) {
  GfxCalRGBColorSpace cs;
  const double originalZ = cs.getBlackZ();

  std::unique_ptr<GfxColorSpace> baseCopy = cs.copy();
  ASSERT_NE(baseCopy, nullptr);

  auto *calCopy = dynamic_cast<GfxCalRGBColorSpace *>(baseCopy.get());
  ASSERT_NE(calCopy, nullptr);

  EXPECT_EQ(calCopy->getBlackZ(), originalZ);
}

TEST_F(GfxCalRGBColorSpaceTest_437, Copy_ReturnsDistinctObject_437) {
  GfxCalRGBColorSpace cs;
  std::unique_ptr<GfxColorSpace> baseCopy = cs.copy();
  ASSERT_NE(baseCopy, nullptr);

  // Observable: copy should not alias the original object address.
  EXPECT_NE(baseCopy.get(), static_cast<GfxColorSpace *>(&cs));
}

}  // namespace