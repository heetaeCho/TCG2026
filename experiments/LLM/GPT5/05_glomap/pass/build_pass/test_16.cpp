// File: cost_function_test_16.cc

#include <array>
#include <cmath>

#include <gtest/gtest.h>
#include <Eigen/Core>
#include "glomap/estimators/cost_function.h"

using glomap::fetzer_ds;

// Helper to check that all entries are finite.
static void ExpectArrayFinite(const std::array<Eigen::Vector4d, 3>& ds) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_TRUE(std::isfinite(ds[i](j)))
          << "Non-finite value at ds[" << i << "](" << j << ") = "
          << ds[i](j);
    }
  }
}

// Normal operation: identity matrix.
TEST(FetzerDsTest_16, IdentityMatrixProducesFiniteAndDeterministicOutput_16) {
  Eigen::Matrix3d mat = Eigen::Matrix3d::Identity();

  auto ds1 = fetzer_ds(mat);
  auto ds2 = fetzer_ds(mat);

  // All components should be finite.
  ExpectArrayFinite(ds1);
  ExpectArrayFinite(ds2);

  // Deterministic: same input => same output.
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_DOUBLE_EQ(ds1[i](j), ds2[i](j))
          << "Mismatch at index (" << i << "," << j << ")";
    }
  }

  // Compile-time size is 4, but we also assert runtime size for clarity.
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(ds1[i].size(), 4);
  }
}

// Boundary condition: rank-deficient (all-zero) matrix.
TEST(FetzerDsTest_16, ZeroMatrixHandledWithoutNaNorInf_16) {
  Eigen::Matrix3d mat = Eigen::Matrix3d::Zero();

  auto ds = fetzer_ds(mat);

  // Even for a rank-deficient matrix, implementation should return finite values.
  ExpectArrayFinite(ds);
}

// Normal operation: clearly different inputs produce different outputs (sensitivity).
TEST(FetzerDsTest_16, DifferentMatricesProduceDifferentOutputs_16) {
  Eigen::Matrix3d mat1 = Eigen::Matrix3d::Identity();
  // A matrix with nontrivial off-diagonal structure.
  Eigen::Matrix3d mat2;
  mat2 << 0.0, 1.0, 2.0,
          1.0, 0.0, 3.0,
          2.0, 3.0, 1.0;

  auto ds1 = fetzer_ds(mat1);
  auto ds2 = fetzer_ds(mat2);

  // At least one coefficient should differ for clearly different inputs.
  bool any_diff = false;
  for (int i = 0; i < 3 && !any_diff; ++i) {
    for (int j = 0; j < 4 && !any_diff; ++j) {
      if (ds1[i](j) != ds2[i](j)) {
        any_diff = true;
      }
    }
  }
  EXPECT_TRUE(any_diff);
}

// Boundary / numeric robustness: large magnitude values.
TEST(FetzerDsTest_16, LargeValuesDoNotProduceNaNOrInf_16) {
  Eigen::Matrix3d mat;
  mat << 1e6,  2e6, -3e6,
        -4e6,  5e6,  6e6,
         7e6, -8e6,  9e6;

  auto ds = fetzer_ds(mat);

  // Ensure that large but reasonable values do not overflow to NaN/Inf.
  ExpectArrayFinite(ds);
}

// Additional robustness: arbitrary non-symmetric matrix.
TEST(FetzerDsTest_16, ArbitraryMatrixProducesFiniteOutput_16) {
  Eigen::Matrix3d mat;
  mat << 0.1, -0.2,  0.3,
         4.0,  5.5, -6.1,
         7.3, -8.4,  9.9;

  auto ds = fetzer_ds(mat);

  ExpectArrayFinite(ds);
}
