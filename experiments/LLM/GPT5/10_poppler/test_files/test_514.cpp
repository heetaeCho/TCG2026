// TEST_ID: 514
#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <limits>
#include <memory>
#include <vector>

#include "poppler/GfxState.h"

class GfxFunctionShadingTest_514 : public ::testing::Test {
protected:
  static std::array<double, 6> IdentityMatrix() {
    return {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
  }

  static std::unique_ptr<GfxFunctionShading> MakeShading(double x0, double y0, double x1, double y1) {
    std::vector<std::unique_ptr<Function>> funcs; // empty is valid for construction tests here
    return std::make_unique<GfxFunctionShading>(x0, y0, x1, y1, IdentityMatrix(), std::move(funcs));
  }
};

TEST_F(GfxFunctionShadingTest_514, GetDomainWritesConstructorValues_514) {
  auto shading = MakeShading(1.25, -2.5, 3.75, 4.0);

  double x0 = 0, y0 = 0, x1 = 0, y1 = 0;
  shading->getDomain(&x0, &y0, &x1, &y1);

  EXPECT_DOUBLE_EQ(x0, 1.25);
  EXPECT_DOUBLE_EQ(y0, -2.5);
  EXPECT_DOUBLE_EQ(x1, 3.75);
  EXPECT_DOUBLE_EQ(y1, 4.0);
}

TEST_F(GfxFunctionShadingTest_514, GetDomainOverwritesExistingOutputs_514) {
  auto shading = MakeShading(-10.0, -20.0, -30.0, -40.0);

  double x0 = 111.0, y0 = 222.0, x1 = 333.0, y1 = 444.0;
  shading->getDomain(&x0, &y0, &x1, &y1);

  EXPECT_DOUBLE_EQ(x0, -10.0);
  EXPECT_DOUBLE_EQ(y0, -20.0);
  EXPECT_DOUBLE_EQ(x1, -30.0);
  EXPECT_DOUBLE_EQ(y1, -40.0);
}

TEST_F(GfxFunctionShadingTest_514, GetDomainHandlesInfinity_514) {
  const double inf = std::numeric_limits<double>::infinity();
  auto shading = MakeShading(-inf, inf, inf, -inf);

  double x0 = 0, y0 = 0, x1 = 0, y1 = 0;
  shading->getDomain(&x0, &y0, &x1, &y1);

  EXPECT_TRUE(std::isinf(x0));
  EXPECT_TRUE(std::isinf(y0));
  EXPECT_TRUE(std::isinf(x1));
  EXPECT_TRUE(std::isinf(y1));
  EXPECT_LT(x0, 0.0);
  EXPECT_GT(y0, 0.0);
  EXPECT_GT(x1, 0.0);
  EXPECT_LT(y1, 0.0);
}

TEST_F(GfxFunctionShadingTest_514, GetDomainHandlesNaN_514) {
  const double nan = std::numeric_limits<double>::quiet_NaN();
  auto shading = MakeShading(nan, 1.0, 2.0, nan);

  double x0 = 0, y0 = 0, x1 = 0, y1 = 0;
  shading->getDomain(&x0, &y0, &x1, &y1);

  EXPECT_TRUE(std::isnan(x0));
  EXPECT_DOUBLE_EQ(y0, 1.0);
  EXPECT_DOUBLE_EQ(x1, 2.0);
  EXPECT_TRUE(std::isnan(y1));
}

TEST_F(GfxFunctionShadingTest_514, CopyConstructorPreservesDomain_514) {
  auto original = MakeShading(0.125, 0.25, 0.5, 1.0);

  GfxFunctionShading copied(original.get());

  double x0 = 0, y0 = 0, x1 = 0, y1 = 0;
  copied.getDomain(&x0, &y0, &x1, &y1);

  EXPECT_DOUBLE_EQ(x0, 0.125);
  EXPECT_DOUBLE_EQ(y0, 0.25);
  EXPECT_DOUBLE_EQ(x1, 0.5);
  EXPECT_DOUBLE_EQ(y1, 1.0);
}

TEST_F(GfxFunctionShadingTest_514, CopyMethodReturnsFunctionShadingWithSameDomain_514) {
  auto shading = MakeShading(9.0, 8.0, 7.0, 6.0);

  std::unique_ptr<GfxShading> baseCopy = shading->copy();
  ASSERT_NE(baseCopy, nullptr);

  auto *copyAsFunc = dynamic_cast<GfxFunctionShading *>(baseCopy.get());
  ASSERT_NE(copyAsFunc, nullptr);

  double x0 = 0, y0 = 0, x1 = 0, y1 = 0;
  copyAsFunc->getDomain(&x0, &y0, &x1, &y1);

  EXPECT_DOUBLE_EQ(x0, 9.0);
  EXPECT_DOUBLE_EQ(y0, 8.0);
  EXPECT_DOUBLE_EQ(x1, 7.0);
  EXPECT_DOUBLE_EQ(y1, 6.0);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(GfxFunctionShadingTest_514, GetDomainNullOutputPointerDies_514) {
  auto shading = MakeShading(1.0, 2.0, 3.0, 4.0);

  double y0 = 0, x1 = 0, y1 = 0;
  EXPECT_DEATH(shading->getDomain(nullptr, &y0, &x1, &y1), "");
}
#endif