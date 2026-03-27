// TEST_ID: 457
// File: gfxlabcolorspace_getbmin_test_457.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "poppler/GfxState.h"

namespace {

class GfxLabColorSpaceTest_457 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxLabColorSpace> MakeLab() {
    return std::make_unique<GfxLabColorSpace>();
  }
};

TEST_F(GfxLabColorSpaceTest_457, GetBMin_IsStableAcrossCalls_457) {
  auto lab = MakeLab();
  const double v1 = lab->getBMin();
  const double v2 = lab->getBMin();
  EXPECT_EQ(v1, v2);
}

TEST_F(GfxLabColorSpaceTest_457, GetBMin_IsFinite_457) {
  auto lab = MakeLab();
  const double v = lab->getBMin();
  EXPECT_TRUE(std::isfinite(v));
}

TEST_F(GfxLabColorSpaceTest_457, Copy_ReturnsNonNull_457) {
  auto lab = MakeLab();
  std::unique_ptr<GfxColorSpace> copied = lab->copy();
  ASSERT_NE(copied, nullptr);
}

TEST_F(GfxLabColorSpaceTest_457, Copy_ProducesDifferentObject_457) {
  auto lab = MakeLab();
  std::unique_ptr<GfxColorSpace> copied = lab->copy();
  ASSERT_NE(copied, nullptr);

  // The copy should be a distinct object.
  EXPECT_NE(copied.get(), static_cast<GfxColorSpace*>(lab.get()));
}

TEST_F(GfxLabColorSpaceTest_457, Copy_PreservesBMinValue_457) {
  auto lab = MakeLab();
  const double before = lab->getBMin();

  std::unique_ptr<GfxColorSpace> copied = lab->copy();
  ASSERT_NE(copied, nullptr);

  auto *labCopied = dynamic_cast<GfxLabColorSpace*>(copied.get());
  ASSERT_NE(labCopied, nullptr);

  EXPECT_EQ(before, labCopied->getBMin());
}

TEST_F(GfxLabColorSpaceTest_457, GetBMin_DoesNotExceedBMax_457) {
  auto lab = MakeLab();

  // A range "min/max" pair should be ordered.
  // This checks an observable invariant without relying on the specific values.
  EXPECT_LE(lab->getBMin(), lab->getBMax());
}

} // namespace