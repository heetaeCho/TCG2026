// File: fetzer_d_test_91.cc

#include <gtest/gtest.h>
#include <Eigen/Core>

#include "glomap/estimators/cost_function.h"

namespace {

using glomap::fetzer_d;

// TEST_ID: 91

// Basic sanity check with simple basis vectors and distinct indices.
TEST(FetzerDTest_91, BasicNonZeroCombination_91) {
  Eigen::Vector3d ai(1.0, 0.0, 0.0);
  Eigen::Vector3d bi(0.0, 0.0, 0.0);
  Eigen::Vector3d aj(0.0, 1.0, 0.0);
  Eigen::Vector3d bj(0.0, 0.0, 0.0);

  // Use u = 0, v = 1 (x and y components).
  const int u = 0;
  const int v = 1;

  Eigen::Vector4d d = fetzer_d(ai, bi, aj, bj, u, v);

  // We expect only the first component to be non-zero in this configuration.
  EXPECT_DOUBLE_EQ(d(0), 1.0);
  EXPECT_DOUBLE_EQ(d(1), 0.0);
  EXPECT_DOUBLE_EQ(d(2), 0.0);
  EXPECT_DOUBLE_EQ(d(3), 0.0);
}

// When all four input vectors are identical, the result should be the zero vector
// for any valid (u, v) pair.
TEST(FetzerDTest_91, IdenticalInputVectorsProduceZero_91) {
  Eigen::Vector3d a(1.5, -2.0, 3.25);
  Eigen::Vector3d ai = a;
  Eigen::Vector3d bi = a;
  Eigen::Vector3d aj = a;
  Eigen::Vector3d bj = a;

  const int u = 0;
  const int v = 2;

  Eigen::Vector4d d = fetzer_d(ai, bi, aj, bj, u, v);

  EXPECT_DOUBLE_EQ(d(0), 0.0);
  EXPECT_DOUBLE_EQ(d(1), 0.0);
  EXPECT_DOUBLE_EQ(d(2), 0.0);
  EXPECT_DOUBLE_EQ(d(3), 0.0);
}

// Boundary condition: when u == v, all terms use the same component twice,
// so every entry of the result should be zero regardless of the vector values.
TEST(FetzerDTest_91, SameIndexReturnsZero_91) {
  Eigen::Vector3d ai(1.0, 2.0, 3.0);
  Eigen::Vector3d bi(-1.0, -2.0, -3.0);
  Eigen::Vector3d aj(4.0, 5.0, 6.0);
  Eigen::Vector3d bj(-4.0, -5.0, -6.0);

  const int u = 1;
  const int v = 1;  // same index

  Eigen::Vector4d d = fetzer_d(ai, bi, aj, bj, u, v);

  EXPECT_DOUBLE_EQ(d(0), 0.0);
  EXPECT_DOUBLE_EQ(d(1), 0.0);
  EXPECT_DOUBLE_EQ(d(2), 0.0);
  EXPECT_DOUBLE_EQ(d(3), 0.0);
}

// Property-based check: swapping (u, v) should negate the result vector.
TEST(FetzerDTest_91, SwappingIndicesNegatesResult_91) {
  Eigen::Vector3d ai(0.5, -1.2, 2.3);
  Eigen::Vector3d bi(1.1, 0.0, -0.4);
  Eigen::Vector3d aj(-0.7, 3.3, 0.9);
  Eigen::Vector3d bj(2.0, -0.5, 1.0);

  const int u = 0;
  const int v = 2;

  Eigen::Vector4d d_uv = fetzer_d(ai, bi, aj, bj, u, v);
  Eigen::Vector4d d_vu = fetzer_d(ai, bi, aj, bj, v, u);

  for (int i = 0; i < 4; ++i) {
    EXPECT_DOUBLE_EQ(d_vu(i), -d_uv(i));
  }
}

}  // namespace
