// TEST_ID 433
// Unit tests for GfxCalRGBColorSpace::getWhiteY()
// File: ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "GfxState.h"

namespace {

class GfxCalRGBColorSpaceTest_433 : public ::testing::Test {};

TEST_F(GfxCalRGBColorSpaceTest_433, GetWhiteY_IsDeterministic_433) {
  GfxCalRGBColorSpace cs;

  const double y1 = cs.getWhiteY();
  const double y2 = cs.getWhiteY();

  // Black-box invariant: repeated calls should return the same observable value.
  EXPECT_DOUBLE_EQ(y1, y2);
}

TEST_F(GfxCalRGBColorSpaceTest_433, GetWhiteY_WorksOnConstObject_433) {
  const GfxCalRGBColorSpace cs;

  const double y = cs.getWhiteY();

  // Just validate it is callable and stable on const objects.
  EXPECT_DOUBLE_EQ(y, cs.getWhiteY());
}

TEST_F(GfxCalRGBColorSpaceTest_433, Copy_PreservesWhiteY_WhenCopyReturnsSameType_433) {
  GfxCalRGBColorSpace cs;

  std::unique_ptr<GfxColorSpace> copied = cs.copy();
  ASSERT_NE(copied, nullptr);

  // Ensure copy is a distinct object (observable via address).
  EXPECT_NE(copied.get(), static_cast<GfxColorSpace*>(&cs));

  // copy() is declared to return a GfxColorSpace; if it isn't actually a
  // GfxCalRGBColorSpace at runtime, we can't validate getWhiteY() on it.
  auto *copiedCal = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
  if (!copiedCal) {
    GTEST_SKIP() << "copy() did not return a GfxCalRGBColorSpace instance at runtime";
  }

  EXPECT_DOUBLE_EQ(cs.getWhiteY(), copiedCal->getWhiteY());
}

}  // namespace