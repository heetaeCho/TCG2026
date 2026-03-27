// TEST_ID: 420
// File: GfxCalGrayColorSpace_getBlackZ_tests_420.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#include "GfxState.h" // Adjust include path if your build uses <poppler/GfxState.h>

namespace {

class GfxCalGrayColorSpaceTest_420 : public ::testing::Test {};

TEST_F(GfxCalGrayColorSpaceTest_420, DefaultConstruction_GetBlackZCallableAndStable_420) {
  GfxCalGrayColorSpace cs;

  const double v1 = cs.getBlackZ();
  const double v2 = cs.getBlackZ();

  // As a pure getter, repeated calls should be stable/consistent.
  EXPECT_EQ(v1, v2);
}

TEST_F(GfxCalGrayColorSpaceTest_420, ConstObject_GetBlackZCallable_420) {
  const GfxCalGrayColorSpace cs;

  // Const-correctness: method is declared const, should be callable on const instance.
  const double v = cs.getBlackZ();
  (void)v;

  SUCCEED();
}

TEST_F(GfxCalGrayColorSpaceTest_420, Copy_PreservesBlackZ_420) {
  GfxCalGrayColorSpace original;
  const double originalBlackZ = original.getBlackZ();

  std::unique_ptr<GfxColorSpace> copiedBase = original.copy();
  ASSERT_NE(copiedBase, nullptr);

  auto *copied = dynamic_cast<GfxCalGrayColorSpace *>(copiedBase.get());
  ASSERT_NE(copied, nullptr) << "copy() should preserve the dynamic type for GfxCalGrayColorSpace";

  EXPECT_EQ(copied->getBlackZ(), originalBlackZ);
}

TEST_F(GfxCalGrayColorSpaceTest_420, Copy_ReturnsDistinctObject_420) {
  GfxCalGrayColorSpace original;

  std::unique_ptr<GfxColorSpace> copiedBase = original.copy();
  ASSERT_NE(copiedBase, nullptr);

  auto *copied = dynamic_cast<GfxCalGrayColorSpace *>(copiedBase.get());
  ASSERT_NE(copied, nullptr);

  // Observable behavior: copy() should return a different object instance.
  EXPECT_NE(copied, &original);

  // And getters should remain callable on both.
  (void)original.getBlackZ();
  (void)copied->getBlackZ();
}

}  // namespace