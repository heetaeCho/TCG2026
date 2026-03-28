// TEST_ID: 511
// File: test_gfx_univariate_shading_getExtend1_511.cpp

#include <gtest/gtest.h>

#include "GfxState.h"

// These tests treat GfxUnivariateShading as a black box and only validate
// observable behavior via the public interface (getExtend1()).

namespace {

class GfxUnivariateShadingTest_511 : public ::testing::Test {
protected:
  static GfxUnivariateShading MakeShading(bool extend0, bool extend1) {
    // Use the constructor signature provided in the prompt that avoids Function dependencies:
    // GfxUnivariateShading(int typeA, double t0A, double t1A, int&& funcsA, bool extend0A, bool extend1A);
    int funcs = 0;
    return GfxUnivariateShading(/*typeA=*/1, /*t0A=*/0.0, /*t1A=*/1.0, std::move(funcs), extend0, extend1);
  }
};

} // namespace

TEST_F(GfxUnivariateShadingTest_511, GetExtend1ReturnsTrueWhenConstructedWithTrue_511) {
  const auto shading = MakeShading(/*extend0=*/false, /*extend1=*/true);
  EXPECT_TRUE(shading.getExtend1());
}

TEST_F(GfxUnivariateShadingTest_511, GetExtend1ReturnsFalseWhenConstructedWithFalse_511) {
  const auto shading = MakeShading(/*extend0=*/true, /*extend1=*/false);
  EXPECT_FALSE(shading.getExtend1());
}

TEST_F(GfxUnivariateShadingTest_511, GetExtend1IsConstCallable_511) {
  const auto shading = MakeShading(/*extend0=*/false, /*extend1=*/true);
  const GfxUnivariateShading &cref = shading;

  // Boundary/const usage: ensure the const-qualified getter is callable and stable.
  EXPECT_TRUE(cref.getExtend1());
  EXPECT_TRUE(cref.getExtend1());
}

TEST_F(GfxUnivariateShadingTest_511, CopyConstructedInstancePreservesGetExtend1Value_511) {
  const auto original = MakeShading(/*extend0=*/false, /*extend1=*/true);

  // Copy constructor (as listed in dependencies): explicit GfxUnivariateShading(const GfxUnivariateShading* shading);
  const GfxUnivariateShading copied(&original);

  EXPECT_TRUE(copied.getExtend1());
}

TEST_F(GfxUnivariateShadingTest_511, CopyConstructedInstancePreservesFalseGetExtend1Value_511) {
  const auto original = MakeShading(/*extend0=*/true, /*extend1=*/false);
  const GfxUnivariateShading copied(&original);

  EXPECT_FALSE(copied.getExtend1());
}