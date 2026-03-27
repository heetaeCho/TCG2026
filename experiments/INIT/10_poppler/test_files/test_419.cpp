// TEST_ID: 419
// File: GfxCalGrayColorSpace_getBlackY_test.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxCalGrayColorSpaceTest_419 : public ::testing::Test {};

TEST_F(GfxCalGrayColorSpaceTest_419, GetBlackY_IsStableAcrossCalls_419) {
  GfxCalGrayColorSpace cs;

  const double y1 = cs.getBlackY();
  const double y2 = cs.getBlackY();
  const double y3 = cs.getBlackY();

  EXPECT_DOUBLE_EQ(y1, y2);
  EXPECT_DOUBLE_EQ(y2, y3);
}

TEST_F(GfxCalGrayColorSpaceTest_419, GetBlackY_CopyPreservesValue_419) {
  GfxCalGrayColorSpace cs;
  const double original = cs.getBlackY();

  // copy() returns a GfxColorSpace; verify it is a GfxCalGrayColorSpace and preserves blackY.
  const std::unique_ptr<GfxColorSpace> copiedBase = cs.copy();
  ASSERT_NE(copiedBase, nullptr);

  auto *copied = dynamic_cast<GfxCalGrayColorSpace *>(copiedBase.get());
  ASSERT_NE(copied, nullptr);

  EXPECT_DOUBLE_EQ(original, copied->getBlackY());
}

TEST_F(GfxCalGrayColorSpaceTest_419, GetBlackY_TwoDefaultInstancesMatch_419) {
  GfxCalGrayColorSpace a;
  GfxCalGrayColorSpace b;

  // Without setters/parse input, only observable contract we can assert is that default construction
  // yields deterministic observable state for this getter.
  EXPECT_DOUBLE_EQ(a.getBlackY(), b.getBlackY());
}

}  // namespace