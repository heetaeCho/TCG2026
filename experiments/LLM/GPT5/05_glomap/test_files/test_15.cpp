// File: cost_function_test_15.cc

#include <gtest/gtest.h>
#include <Eigen/Dense>

#include "glomap/estimators/cost_function.h"

namespace {

// Helper to assert a 4D vector is (approximately) zero.
void ExpectVector4dIsZero(const Eigen::Vector4d& v) {
  EXPECT_DOUBLE_EQ(0.0, v(0));
  EXPECT_DOUBLE_EQ(0.0, v(1));
  EXPECT_DOUBLE_EQ(0.0, v(2));
  EXPECT_DOUBLE_EQ(0.0, v(3));
}

// -----------------------------------------------------------------------------
// TEST_ID = 15
// -----------------------------------------------------------------------------

// Verifies that when all input vectors are zero, fetzer_d returns a zero vector.
TEST(FetzerDTest_15, ZeroInputsReturnZero_15) {
  Eigen::Vector3d ai = Eigen::Vector3d::Zero();
  Eigen::Vector3d bi = Eigen::Vector3d::Zero();
  Eigen::Vector3d aj = Eigen::Vector3d::Zero();
  Eigen::Vector3d bj = Eigen::Vector3d::Zero();

  const int u = 0;
  const int v = 1;

  Eigen::Vector4d d = glomap::fetzer_d(ai, bi, aj, bj, u, v);
  ExpectVector4dIsZero(d);
}

// Verifies basic behavior on unit basis vectors; only the first component
// should be non-zero for this specific configuration.
TEST(FetzerDTest_15, BasisVectorsProduceExpected_15) {
  // ai = e0, aj = e1, bi = 0, bj = 0
  Eigen::Vector3d ai(1.0, 0.0, 0.0);
  Eigen::Vector3d bi(0.0, 0.0, 0.0);
  Eigen::Vector3d aj(0.0, 1.0, 0.0);
  Eigen::Vector3d bj(0.0, 0.0, 0.0);

  const int u = 0;
  const int v = 1;

  Eigen::Vector4d d = glomap::fetzer_d(ai, bi, aj, bj, u, v);

  // Manually computed expected values for this specific configuration.
  // d(0) = ai(0) * aj(1) - ai(1) * aj(0) = 1 * 1 - 0 * 0 = 1
  EXPECT_DOUBLE_EQ(1.0, d(0));
  EXPECT_DOUBLE_EQ(0.0, d(1));
  EXPECT_DOUBLE_EQ(0.0, d(2));
  EXPECT_DOUBLE_EQ(0.0, d(3));
}

// Verifies that using the same index for u and v produces a zero vector
// (since each term becomes x*u - x*u).
TEST(FetzerDTest_15, SameIndexUEqualsVReturnsZero_15) {
  // Use non-trivial values to ensure we are not relying on zeros in inputs.
  Eigen::Vector3d ai(1.0, 2.0, 3.0);
  Eigen::Vector3d bi(4.0, 5.0, 6.0);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  const int u = 1;
  const int v = 1;  // u == v

  Eigen::Vector4d d = glomap::fetzer_d(ai, bi, aj, bj, u, v);
  ExpectVector4dIsZero(d);
}

// Verifies an antisymmetry-like property: swapping u and v changes the sign
// of all components (d(u, v) == -d(v, u)) for valid indices.
TEST(FetzerDTest_15, SwappingIndicesNegatesResult_15) {
  Eigen::Vector3d ai(1.0, 2.0, 3.0);
  Eigen::Vector3d bi(-1.0, 0.5, 4.0);
  Eigen::Vector3d aj(0.0, -2.0, 5.0);
  Eigen::Vector3d bj(3.0, 1.5, -0.5);

  const int u = 0;
  const int v = 2;

  Eigen::Vector4d d_uv = glomap::fetzer_d(ai, bi, aj, bj, u, v);
  Eigen::Vector4d d_vu = glomap::fetzer_d(ai, bi, aj, bj, v, u);

  // Each component should be the negative of the corresponding component
  // when indices are swapped.
  for (int i = 0; i < 4; ++i) {
    EXPECT_DOUBLE_EQ(-d_uv(i), d_vu(i));
  }
}

// Verifies correct computation on a non-trivial combination of vectors and
// indices by comparing against explicitly computed expected values.
TEST(FetzerDTest_15, NonTrivialValuesProduceExpectedResult_15) {
  Eigen::Vector3d ai(1.0, 2.0, 3.0);
  Eigen::Vector3d bi(4.0, 5.0, 6.0);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  const int u = 0;  // x-component
  const int v = 1;  // y-component

  Eigen::Vector4d d = glomap::fetzer_d(ai, bi, aj, bj, u, v);

  // Explicitly compute the expected values for this single case.
  double expected0 = 1.0 * 8.0 - 2.0 * 7.0;   // = 8 - 14 = -6
  double expected1 = 1.0 * 11.0 - 2.0 * 10.0; // = 11 - 20 = -9
  double expected2 = 4.0 * 8.0 - 5.0 * 7.0;   // = 32 - 35 = -3
  double expected3 = 4.0 * 11.0 - 5.0 * 10.0; // = 44 - 50 = -6

  EXPECT_DOUBLE_EQ(expected0, d(0));
  EXPECT_DOUBLE_EQ(expected1, d(1));
  EXPECT_DOUBLE_EQ(expected2, d(2));
  EXPECT_DOUBLE_EQ(expected3, d(3));
}

}  // namespace
