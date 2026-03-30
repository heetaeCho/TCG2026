// SPDX-License-Identifier: GPL-2.0-or-later
// File: gfxcalrgbcolorspace_blacky_test_436.cpp

#include <gtest/gtest.h>

#include <memory>

#include "poppler/GfxState.h"

namespace {

class GfxCalRGBColorSpaceTest_436 : public ::testing::Test {};

TEST_F(GfxCalRGBColorSpaceTest_436, GetBlackY_ReturnsSameValueAcrossCalls_436) {
  GfxCalRGBColorSpace cs;

  const double v1 = cs.getBlackY();
  const double v2 = cs.getBlackY();
  const double v3 = cs.getBlackY();

  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

TEST_F(GfxCalRGBColorSpaceTest_436, GetBlackY_WorksThroughConstReference_436) {
  GfxCalRGBColorSpace cs;
  const GfxCalRGBColorSpace &ccs = cs;

  const double v1 = ccs.getBlackY();
  const double v2 = ccs.getBlackY();

  EXPECT_EQ(v1, v2);
}

TEST_F(GfxCalRGBColorSpaceTest_436, Copy_PreservesBlackY_436) {
  GfxCalRGBColorSpace cs;
  const double original = cs.getBlackY();

  std::unique_ptr<GfxColorSpace> copiedBase;
  ASSERT_NO_THROW(copiedBase = cs.copy());
  ASSERT_NE(copiedBase, nullptr);

  auto *copied = dynamic_cast<GfxCalRGBColorSpace *>(copiedBase.get());
  ASSERT_NE(copied, nullptr) << "copy() did not return a GfxCalRGBColorSpace instance";

  EXPECT_EQ(copied->getBlackY(), original);
}

TEST_F(GfxCalRGBColorSpaceTest_436, Copy_DoesNotAliasOriginalObject_436) {
  GfxCalRGBColorSpace cs;

  std::unique_ptr<GfxColorSpace> copiedBase;
  ASSERT_NO_THROW(copiedBase = cs.copy());
  ASSERT_NE(copiedBase, nullptr);

  // Observable independence: the copy should be a distinct object.
  EXPECT_NE(copiedBase.get(), static_cast<GfxColorSpace *>(&cs));
}

}  // namespace