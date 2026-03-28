//===----------------------------------------------------------------------===//
// Unit tests for GfxCalRGBColorSpace::getGammaB
// File: GfxCalRGBColorSpace_getGammaB_test.cpp
// TEST_ID: 440
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include <type_traits>

#include "poppler/GfxState.h"

// NOTE: These tests treat GfxCalRGBColorSpace as a black box and only verify
// observable behavior through the public interface.

class GfxCalRGBColorSpaceTest_440 : public ::testing::Test {};

TEST_F(GfxCalRGBColorSpaceTest_440, SignatureAndConstCorrectness_440) {
  // Verify return type is double and method is callable on const instances.
  static_assert(std::is_same_v<decltype(std::declval<const GfxCalRGBColorSpace&>().getGammaB()), double>,
                "getGammaB() must return double");

  GfxCalRGBColorSpace cs;
  const GfxCalRGBColorSpace& ccs = cs;

  // Callable on both const and non-const.
  (void)cs.getGammaB();
  (void)ccs.getGammaB();

  SUCCEED();
}

TEST_F(GfxCalRGBColorSpaceTest_440, RepeatedCallsAreStableOnSameObject_440) {
  GfxCalRGBColorSpace cs;

  const double v1 = cs.getGammaB();
  const double v2 = cs.getGammaB();
  const double v3 = cs.getGammaB();

  // Observable expectation for a const getter: repeated calls should be stable.
  EXPECT_DOUBLE_EQ(v1, v2);
  EXPECT_DOUBLE_EQ(v2, v3);
}

TEST_F(GfxCalRGBColorSpaceTest_440, ConstAndNonConstAccessMatch_440) {
  GfxCalRGBColorSpace cs;
  const GfxCalRGBColorSpace& ccs = cs;

  const double nonConstVal = cs.getGammaB();
  const double constVal = ccs.getGammaB();

  // Same underlying object; calling via const vs non-const reference should match.
  EXPECT_DOUBLE_EQ(nonConstVal, constVal);
}

TEST_F(GfxCalRGBColorSpaceTest_440, MultipleInstancesDoNotInterfere_440) {
  GfxCalRGBColorSpace a;
  GfxCalRGBColorSpace b;

  const double a1 = a.getGammaB();
  const double b1 = b.getGammaB();

  // Ensure calling getter on one instance does not affect the other instance.
  const double a2 = a.getGammaB();
  const double b2 = b.getGammaB();

  EXPECT_DOUBLE_EQ(a1, a2);
  EXPECT_DOUBLE_EQ(b1, b2);
}