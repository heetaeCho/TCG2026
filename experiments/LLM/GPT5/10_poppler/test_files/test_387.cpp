// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: Matrix_determinant_test_387.cpp
//
// Unit tests for poppler::Matrix (GfxState.h) determinant().
// Black-box tests based only on the public interface.

#include <gtest/gtest.h>

#include <array>
#include <cmath>

#include "GfxState.h"

namespace {

// The TEST_ID is 387
class MatrixTest_387 : public ::testing::Test {};

}  // namespace

// The TEST_ID is 387
TEST_F(MatrixTest_387, Determinant_IdentityIsOne_387) {
  Matrix m;
  // Identity: [1 0; 0 1]
  m.m = std::array<double, 6>{1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
  EXPECT_DOUBLE_EQ(m.determinant(), 1.0);
}

// The TEST_ID is 387
TEST_F(MatrixTest_387, Determinant_ZeroMatrixIsZero_387) {
  Matrix m;
  m.m = std::array<double, 6>{0.0, 0.0, 0.0, 0.0, 123.0, -456.0};  // translation should not matter
  EXPECT_DOUBLE_EQ(m.determinant(), 0.0);
}

// The TEST_ID is 387
TEST_F(MatrixTest_387, Determinant_UpperTriangularProductOfDiagonal_387) {
  Matrix m;
  // [a b; 0 d] => det = a*d
  m.m = std::array<double, 6>{2.5, 0.0, -7.0, 4.0, 0.0, 0.0};
  EXPECT_DOUBLE_EQ(m.determinant(), 2.5 * 4.0);
}

// The TEST_ID is 387
TEST_F(MatrixTest_387, Determinant_ShearHasDetOne_387) {
  Matrix m;
  // x-shear: [1 k; 0 1] => det = 1
  m.m = std::array<double, 6>{1.0, 0.0, 3.75, 1.0, 0.0, 0.0};
  EXPECT_DOUBLE_EQ(m.determinant(), 1.0);
}

// The TEST_ID is 387
TEST_F(MatrixTest_387, Determinant_ScalingMatrix_387) {
  Matrix m;
  // scale by sx, sy: [sx 0; 0 sy] => det = sx*sy
  m.m = std::array<double, 6>{-2.0, 0.0, 0.0, 0.5, 10.0, 20.0};
  EXPECT_DOUBLE_EQ(m.determinant(), (-2.0) * 0.5);
}

// The TEST_ID is 387
TEST_F(MatrixTest_387, Determinant_TranslationDoesNotAffectDeterminant_387) {
  Matrix m1;
  Matrix m2;

  // Same linear part, different translation (x0,y0) in m[4], m[5]
  m1.m = std::array<double, 6>{3.0, 4.0, 5.0, 6.0, 0.0, 0.0};
  m2.m = std::array<double, 6>{3.0, 4.0, 5.0, 6.0, 999.0, -888.0};

  EXPECT_DOUBLE_EQ(m1.determinant(), m2.determinant());
  EXPECT_DOUBLE_EQ(m1.determinant(), 3.0 * 6.0 - 4.0 * 5.0);
}

// The TEST_ID is 387
TEST_F(MatrixTest_387, Determinant_NegativeDetForOrientationFlip_387) {
  Matrix m;
  // Reflection across Y axis: [-1 0; 0 1] => det = -1
  m.m = std::array<double, 6>{-1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
  EXPECT_DOUBLE_EQ(m.determinant(), -1.0);
}

// The TEST_ID is 387
TEST_F(MatrixTest_387, Determinant_SwappedRowsGivesNegatedDeterminant_387) {
  Matrix a;
  Matrix b;

  // a: [p q; r s]
  const double p = 1.25, q = -2.0, r = 3.5, s = 4.0;
  a.m = std::array<double, 6>{p, r, q, s, 0.0, 0.0};  // m[0]=xx=p, m[1]=yx=r, m[2]=xy=q, m[3]=yy=s

  // b: swap the two rows => [r s; p q] => det = -(det(a))
  b.m = std::array<double, 6>{r, p, s, q, 0.0, 0.0};

  EXPECT_DOUBLE_EQ(b.determinant(), -a.determinant());
}

// The TEST_ID is 387
TEST_F(MatrixTest_387, Determinant_NearSingularSmallValue_387) {
  Matrix m;
  // Construct a nearly singular matrix where det is small but known:
  // [1 1; 1 1+eps] => det = eps
  const double eps = 1e-12;
  m.m = std::array<double, 6>{1.0, 1.0, 1.0, 1.0 + eps, 0.0, 0.0};

  const double det = m.determinant();
  EXPECT_NEAR(det, eps, 1e-15);
}

// The TEST_ID is 387
TEST_F(MatrixTest_387, Determinant_WithLargeMagnitudesRemainsFiniteWhenExpected_387) {
  Matrix m;
  // Choose values that avoid overflow in intermediate products for IEEE double:
  // (1e150 * 1e150) - (0 * 0) = 1e300 (finite)
  m.m = std::array<double, 6>{1e150, 0.0, 0.0, 1e150, 0.0, 0.0};

  const double det = m.determinant();
  EXPECT_TRUE(std::isfinite(det));
  EXPECT_DOUBLE_EQ(det, 1e300);
}