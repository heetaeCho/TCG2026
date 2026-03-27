// TEST_ID: 451
// File: GfxLabColorSpace_getWhiteZ_test.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxLabColorSpaceTest_451 : public ::testing::Test {};

TEST_F(GfxLabColorSpaceTest_451, GetterIsCallableOnConstObject_451) {
  GfxLabColorSpace cs;
  const GfxLabColorSpace &ccs = cs;

  // Verifies the method is callable on a const object and returns a double.
  const double z = ccs.getWhiteZ();
  (void)z;
  SUCCEED();
}

TEST_F(GfxLabColorSpaceTest_451, GetterReturnsStableValueAcrossCalls_451) {
  GfxLabColorSpace cs;

  const double z1 = cs.getWhiteZ();
  const double z2 = cs.getWhiteZ();

  // Black-box expectation: a const getter should be stable across repeated calls.
  EXPECT_DOUBLE_EQ(z1, z2);
}

TEST_F(GfxLabColorSpaceTest_451, CopyPreservesWhiteZValue_451) {
  GfxLabColorSpace cs;
  const double originalZ = cs.getWhiteZ();

  std::unique_ptr<GfxColorSpace> copiedBase = cs.copy();
  ASSERT_NE(copiedBase, nullptr);

  auto *copiedLab = dynamic_cast<GfxLabColorSpace *>(copiedBase.get());
  ASSERT_NE(copiedLab, nullptr);

  EXPECT_DOUBLE_EQ(copiedLab->getWhiteZ(), originalZ);
}

TEST_F(GfxLabColorSpaceTest_451, CopyReturnsDistinctObject_451) {
  GfxLabColorSpace cs;

  std::unique_ptr<GfxColorSpace> copiedBase = cs.copy();
  ASSERT_NE(copiedBase, nullptr);

  // Should not be the same object instance.
  EXPECT_NE(static_cast<void *>(copiedBase.get()), static_cast<void *>(&cs));

  auto *copiedLab = dynamic_cast<GfxLabColorSpace *>(copiedBase.get());
  ASSERT_NE(copiedLab, nullptr);

  // And it should still report a consistent value.
  EXPECT_DOUBLE_EQ(copiedLab->getWhiteZ(), cs.getWhiteZ());
}

}  // namespace