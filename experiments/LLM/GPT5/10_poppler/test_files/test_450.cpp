// TEST_ID: 450
// File: GfxLabColorSpace_getWhiteY_ut_450.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "GfxState.h"

namespace {

class GfxLabColorSpaceTest_450 : public ::testing::Test {
protected:
  GfxLabColorSpaceTest_450() = default;
  ~GfxLabColorSpaceTest_450() override = default;
};

// Normal operation: accessor can be called and returns a stable value.
TEST_F(GfxLabColorSpaceTest_450, GetWhiteY_MultipleCallsReturnSameValue_450) {
  GfxLabColorSpace cs;

  const double y1 = cs.getWhiteY();
  const double y2 = cs.getWhiteY();

  EXPECT_DOUBLE_EQ(y1, y2);
}

// Boundary/robustness: returned value is a normal floating-point number (not NaN/Inf).
TEST_F(GfxLabColorSpaceTest_450, GetWhiteY_ReturnValueIsFinite_450) {
  GfxLabColorSpace cs;

  const double y = cs.getWhiteY();

  EXPECT_TRUE(std::isfinite(y));
  EXPECT_FALSE(std::isnan(y));
}

// External interaction / observable behavior via public API: copy() preserves observable value.
TEST_F(GfxLabColorSpaceTest_450, Copy_PreservesWhiteY_450) {
  GfxLabColorSpace cs;
  const double y = cs.getWhiteY();

  std::unique_ptr<GfxColorSpace> copiedBase = cs.copy();
  ASSERT_NE(copiedBase, nullptr);

  auto *copied = dynamic_cast<GfxLabColorSpace *>(copiedBase.get());
  ASSERT_NE(copied, nullptr);

  EXPECT_DOUBLE_EQ(copied->getWhiteY(), y);
}

// Boundary/robustness: copy() returns an independent object (distinct address) while preserving value.
TEST_F(GfxLabColorSpaceTest_450, Copy_ReturnsDistinctObject_450) {
  GfxLabColorSpace cs;

  std::unique_ptr<GfxColorSpace> copiedBase = cs.copy();
  ASSERT_NE(copiedBase, nullptr);

  EXPECT_NE(copiedBase.get(), static_cast<GfxColorSpace *>(&cs));

  auto *copied = dynamic_cast<GfxLabColorSpace *>(copiedBase.get());
  ASSERT_NE(copied, nullptr);

  EXPECT_DOUBLE_EQ(copied->getWhiteY(), cs.getWhiteY());
}

} // namespace