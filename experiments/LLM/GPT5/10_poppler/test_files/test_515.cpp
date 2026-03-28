// File: gfx_function_shading_getmatrix_test_515.cpp
#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <limits>

#include "poppler/GfxState.h"

namespace {

class GfxFunctionShadingTest_515 : public ::testing::Test {
protected:
  static void ExpectArrayEq(const std::array<double, 6> &a, const std::array<double, 6> &b) {
    for (size_t i = 0; i < a.size(); ++i) {
      if (std::isnan(a[i]) || std::isnan(b[i])) {
        EXPECT_TRUE(std::isnan(a[i]) && std::isnan(b[i])) << "index=" << i;
      } else {
        EXPECT_DOUBLE_EQ(a[i], b[i]) << "index=" << i;
      }
    }
  }
};

} // namespace

TEST_F(GfxFunctionShadingTest_515, GetMatrixReturnsConstructorMatrix_515) {
  const std::array<double, 6> m = {1.0, 2.5, -3.0, 4.25, 10.0, -20.0};

  // Use the constructor overload that does not require constructing Function objects.
  int funcsArg = 0;
  GfxFunctionShading shading(/*x0A=*/0.0, /*y0A=*/0.0, /*x1A=*/1.0, /*y1A=*/1.0, m, std::move(funcsArg));

  const auto &got = shading.getMatrix();
  GfxFunctionShadingTest_515::ExpectArrayEq(got, m);
}

TEST_F(GfxFunctionShadingTest_515, GetMatrixReferenceIsStableAcrossCalls_515) {
  const std::array<double, 6> m = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  int funcsArg = 0;
  GfxFunctionShading shading(/*x0A=*/-1.0, /*y0A=*/-2.0, /*x1A=*/3.0, /*y1A=*/4.0, m, std::move(funcsArg));

  const auto *p1 = &shading.getMatrix();
  const auto *p2 = &shading.getMatrix();

  EXPECT_EQ(p1, p2);

  // Also ensure element addresses match (further checks reference stability).
  EXPECT_EQ(&((*p1)[0]), &((shading.getMatrix())[0]));
}

TEST_F(GfxFunctionShadingTest_515, GetMatrixSupportsExtremeValues_515) {
  const double inf = std::numeric_limits<double>::infinity();
  const double nan = std::numeric_limits<double>::quiet_NaN();

  const std::array<double, 6> m = {
      std::numeric_limits<double>::max(),
      std::numeric_limits<double>::lowest(),
      inf,
      -inf,
      nan,
      1.0,
  };

  int funcsArg = 0;
  GfxFunctionShading shading(/*x0A=*/0.0, /*y0A=*/0.0, /*x1A=*/0.0, /*y1A=*/0.0, m, std::move(funcsArg));

  const auto &got = shading.getMatrix();
  GfxFunctionShadingTest_515::ExpectArrayEq(got, m);
}

TEST_F(GfxFunctionShadingTest_515, GetMatrixPreservedByPointerCopyConstructor_515) {
  const std::array<double, 6> m = {1.0, 0.0, 0.0, 1.0, 5.0, 6.0};

  int funcsArg = 0;
  GfxFunctionShading original(/*x0A=*/10.0, /*y0A=*/20.0, /*x1A=*/30.0, /*y1A=*/40.0, m, std::move(funcsArg));

  GfxFunctionShading copied(&original);

  const auto &gotOrig = original.getMatrix();
  const auto &gotCopy = copied.getMatrix();

  GfxFunctionShadingTest_515::ExpectArrayEq(gotOrig, m);
  GfxFunctionShadingTest_515::ExpectArrayEq(gotCopy, m);

  // Sanity: ensure they are not the same reference object (implementation-dependent,
  // but typically copies should not alias the same matrix storage).
  EXPECT_NE(&gotOrig, &gotCopy);
}

TEST_F(GfxFunctionShadingTest_515, GetMatrixPreservedByVirtualCopy_515) {
  const std::array<double, 6> m = {2.0, 1.0, 0.0, 3.0, -7.0, 9.0};

  int funcsArg = 0;
  GfxFunctionShading original(/*x0A=*/0.5, /*y0A=*/-0.5, /*x1A=*/100.0, /*y1A=*/200.0, m, std::move(funcsArg));

  // copy() is a virtual clone returning a GfxShading; verify observable matrix is preserved.
  const std::unique_ptr<GfxShading> baseCopy = original.copy();
  ASSERT_NE(baseCopy, nullptr);

  auto *funcCopy = dynamic_cast<GfxFunctionShading *>(baseCopy.get());
  ASSERT_NE(funcCopy, nullptr);

  const auto &got = funcCopy->getMatrix();
  GfxFunctionShadingTest_515::ExpectArrayEq(got, m);
}