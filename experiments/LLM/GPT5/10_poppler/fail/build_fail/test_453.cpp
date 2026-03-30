// GfxLabColorSpace_getBlackY_453_test.cc
#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include <type_traits>

#include "poppler/GfxState.h"

namespace {

bool sameDouble(double a, double b) {
  // Treat NaN as equal-to-NaN for the purpose of "value preserved" checks.
  if (std::isnan(a) && std::isnan(b)) {
    return true;
  }
  return a == b;
}

} // namespace

class GfxLabColorSpaceTest_453 : public ::testing::Test {
protected:
  static void ExpectSameDouble(double a, double b) {
    if (std::isnan(a) && std::isnan(b)) {
      SUCCEED();
      return;
    }
    EXPECT_DOUBLE_EQ(a, b);
  }
};

TEST_F(GfxLabColorSpaceTest_453, GetBlackY_IsCallableOnConstInstance_453) {
  const GfxLabColorSpace cs;
  (void)cs.getBlackY(); // observable behavior: callable, no crash
}

TEST_F(GfxLabColorSpaceTest_453, GetBlackY_RepeatedCallsReturnSameValue_453) {
  const GfxLabColorSpace cs;
  const double v1 = cs.getBlackY();
  const double v2 = cs.getBlackY();
  ASSERT_TRUE(sameDouble(v1, v2));
}

TEST_F(GfxLabColorSpaceTest_453, GetBlackY_CopyPreservesValue_453) {
  const GfxLabColorSpace original;

  // copy() returns a GfxColorSpace base pointer; verify the dynamic type and value preservation.
  std::unique_ptr<GfxColorSpace> baseCopy = original.copy();
  ASSERT_NE(baseCopy, nullptr);

  auto *labCopy = dynamic_cast<GfxLabColorSpace *>(baseCopy.get());
  ASSERT_NE(labCopy, nullptr);

  ExpectSameDouble(original.getBlackY(), labCopy->getBlackY());
}

TEST_F(GfxLabColorSpaceTest_453, GetBlackY_DoesNotModifyObjectState_453) {
  GfxLabColorSpace cs;

  // Since getBlackY() is const, this primarily validates it doesn't have observable side effects
  // (e.g., changing the returned value across calls).
  const double before = cs.getBlackY();
  (void)cs.getBlackY();
  const double after = cs.getBlackY();

  ASSERT_TRUE(sameDouble(before, after));
}

// Compile-time boundary/contract checks (no runtime assumptions about internal values).
TEST_F(GfxLabColorSpaceTest_453, GetBlackY_ReturnTypeIsDouble_453) {
  static_assert(std::is_same_v<decltype(std::declval<const GfxLabColorSpace &>().getBlackY()), double>,
                "getBlackY() must return double");
  SUCCEED();
}