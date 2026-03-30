// -*- mode: c++; -*-
// File: test_gfx_univariate_shading_getDomain0_508.cc

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <utility>

#include "poppler/GfxState.h"

namespace {

class GfxUnivariateShadingTest_508 : public ::testing::Test {};

// Normal operation: value provided at construction is observable via getDomain0().
TEST_F(GfxUnivariateShadingTest_508, GetDomain0ReturnsConstructorT0_508) {
  const int typeA = 1;
  const double t0A = 0.25;
  const double t1A = 0.75;
  int funcsA = 0;
  const bool extend0A = false;
  const bool extend1A = true;

  GfxUnivariateShading shading(typeA, t0A, t1A, std::move(funcsA), extend0A, extend1A);
  EXPECT_DOUBLE_EQ(shading.getDomain0(), t0A);
}

// Boundary: t0 can be negative; returned value should match what was provided.
TEST_F(GfxUnivariateShadingTest_508, GetDomain0WithNegativeValue_508) {
  const int typeA = 2;
  const double t0A = -123.456;
  const double t1A = 10.0;
  int funcsA = 1;

  GfxUnivariateShading shading(typeA, t0A, t1A, std::move(funcsA), true, false);
  EXPECT_DOUBLE_EQ(shading.getDomain0(), t0A);
}

// Boundary: t0 = 0.0
TEST_F(GfxUnivariateShadingTest_508, GetDomain0WithZero_508) {
  const int typeA = 3;
  const double t0A = 0.0;
  const double t1A = 1.0;
  int funcsA = 2;

  GfxUnivariateShading shading(typeA, t0A, t1A, std::move(funcsA), false, false);
  EXPECT_DOUBLE_EQ(shading.getDomain0(), t0A);
}

// Boundary: very large magnitude value
TEST_F(GfxUnivariateShadingTest_508, GetDomain0WithLargeMagnitude_508) {
  const int typeA = 4;
  const double t0A = std::numeric_limits<double>::max();
  const double t1A = std::numeric_limits<double>::max();
  int funcsA = 0;

  GfxUnivariateShading shading(typeA, t0A, t1A, std::move(funcsA), false, false);
  EXPECT_DOUBLE_EQ(shading.getDomain0(), t0A);
}

// Boundary: NaN should round-trip through the observable getter (checked via isnan).
TEST_F(GfxUnivariateShadingTest_508, GetDomain0WithNaN_508) {
  const int typeA = 5;
  const double t0A = std::numeric_limits<double>::quiet_NaN();
  const double t1A = 1.0;
  int funcsA = 0;

  GfxUnivariateShading shading(typeA, t0A, t1A, std::move(funcsA), true, true);
  EXPECT_TRUE(std::isnan(shading.getDomain0()));
}

// Boundary: +infinity should be observable as infinity.
TEST_F(GfxUnivariateShadingTest_508, GetDomain0WithInfinity_508) {
  const int typeA = 6;
  const double t0A = std::numeric_limits<double>::infinity();
  const double t1A = 1.0;
  int funcsA = 0;

  GfxUnivariateShading shading(typeA, t0A, t1A, std::move(funcsA), false, true);
  EXPECT_TRUE(std::isinf(shading.getDomain0()));
  EXPECT_GT(shading.getDomain0(), 0.0);
}

// Copy construction: copied object should expose the same domain0 as the source.
TEST_F(GfxUnivariateShadingTest_508, CopyConstructorPreservesDomain0_508) {
  const int typeA = 7;
  const double t0A = 3.141592653589793;
  const double t1A = 2.718281828459045;
  int funcsA = 0;

  GfxUnivariateShading original(typeA, t0A, t1A, std::move(funcsA), true, false);
  GfxUnivariateShading copy(&original);

  EXPECT_DOUBLE_EQ(copy.getDomain0(), original.getDomain0());
  EXPECT_DOUBLE_EQ(copy.getDomain0(), t0A);
}

// Const-correctness: getter should be callable on a const reference.
TEST_F(GfxUnivariateShadingTest_508, GetDomain0CallableOnConstObject_508) {
  const int typeA = 8;
  const double t0A = -0.5;
  const double t1A = 0.5;
  int funcsA = 0;

  GfxUnivariateShading shading(typeA, t0A, t1A, std::move(funcsA), false, false);
  const GfxUnivariateShading &cshading = shading;

  EXPECT_DOUBLE_EQ(cshading.getDomain0(), t0A);
}

// Exceptional/robustness (observable): construction should not throw for typical values.
TEST_F(GfxUnivariateShadingTest_508, ConstructionDoesNotThrowForTypicalInputs_508) {
  EXPECT_NO_THROW({
    int funcsA = 0;
    GfxUnivariateShading shading(/*typeA=*/1,
                                 /*t0A=*/0.1,
                                 /*t1A=*/0.2,
                                 std::move(funcsA),
                                 /*extend0A=*/false,
                                 /*extend1A=*/false);
    (void)shading.getDomain0();
  });
}

} // namespace