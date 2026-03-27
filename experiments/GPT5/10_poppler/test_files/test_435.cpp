//===----------------------------------------------------------------------===//
// Unit tests for GfxCalRGBColorSpace::getBlackX (TEST_ID: 435)
// File: GfxCalRGBColorSpace_getBlackX_test.cpp
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include <cmath>
#include <memory>

// Adjust include as needed for your build/include paths.
#include "poppler/GfxState.h"

namespace {

class GfxCalRGBColorSpaceTest_435 : public ::testing::Test {};

TEST_F(GfxCalRGBColorSpaceTest_435, DefaultConstructed_GetBlackX_IsDeterministic_435) {
  GfxCalRGBColorSpace cs;

  const double x1 = cs.getBlackX();
  const double x2 = cs.getBlackX();

  // Black-box friendly: we don't assume a specific value, only that repeated
  // calls are stable/consistent for the same object.
  ASSERT_TRUE(std::isfinite(x1) || std::isnan(x1));
  ASSERT_TRUE(std::isfinite(x2) || std::isnan(x2));

  if (std::isnan(x1) || std::isnan(x2)) {
    EXPECT_TRUE(std::isnan(x1));
    EXPECT_TRUE(std::isnan(x2));
  } else {
    EXPECT_DOUBLE_EQ(x1, x2);
  }
}

TEST_F(GfxCalRGBColorSpaceTest_435, Copy_PreservesBlackX_435) {
  GfxCalRGBColorSpace original;

  const double before = original.getBlackX();

  // copy() returns a base pointer; verify it is a CalRGB instance and that
  // observable behavior (getBlackX) matches the original.
  std::unique_ptr<GfxColorSpace> baseCopy = original.copy();
  ASSERT_NE(baseCopy, nullptr);

  auto *copy = dynamic_cast<GfxCalRGBColorSpace *>(baseCopy.get());
  ASSERT_NE(copy, nullptr);

  const double after = copy->getBlackX();

  if (std::isnan(before) || std::isnan(after)) {
    EXPECT_TRUE(std::isnan(before));
    EXPECT_TRUE(std::isnan(after));
  } else {
    EXPECT_DOUBLE_EQ(before, after);
  }
}

TEST_F(GfxCalRGBColorSpaceTest_435, Copy_ReturnsDistinctObject_435) {
  GfxCalRGBColorSpace original;

  std::unique_ptr<GfxColorSpace> baseCopy = original.copy();
  ASSERT_NE(baseCopy, nullptr);

  // Since original is a stack object, the copied heap object must not alias it.
  EXPECT_NE(baseCopy.get(), static_cast<GfxColorSpace *>(&original));

  auto *copy = dynamic_cast<GfxCalRGBColorSpace *>(baseCopy.get());
  ASSERT_NE(copy, nullptr);

  // Basic sanity: both objects remain callable independently.
  (void)original.getBlackX();
  (void)copy->getBlackX();
}

}  // namespace