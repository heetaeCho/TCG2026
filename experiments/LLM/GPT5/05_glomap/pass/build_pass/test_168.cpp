// File: glomap/estimators/fetzer_focal_length_same_camera_cost_test.cc

#include <cmath>
#include <vector>

#include <gtest/gtest.h>
#include <ceres/ceres.h>
#include <Eigen/Core>

#include "glomap/estimators/cost_function.h"

namespace glomap {

/// TEST_ID: 168
class FetzerFocalLengthSameCameraCostTest_168 : public ::testing::Test {
 protected:
  // A helper to build a reasonable, fixed fundamental matrix.
  Eigen::Matrix3d MakeTestFundamentalMatrix() const {
    Eigen::Matrix3d F;
    F <<  0.0,   -1e-3,  1e-2,
          1e-3,   0.0,  -2e-2,
         -1e-2,   2e-2,  1.0;
    return F;
  }

  // A helper to build a typical principal point.
  Eigen::Vector2d MakeTestPrincipalPoint() const {
    return Eigen::Vector2d(320.0, 240.0);
  }
};

//------------------------------------------------------------------------------
// Basic construction: verify that the class can be constructed with
// a valid fundamental matrix and principal point without throwing.
//------------------------------------------------------------------------------
TEST_F(FetzerFocalLengthSameCameraCostTest_168,
       ConstructorAcceptsValidInputs_168) {
  const Eigen::Matrix3d F = MakeTestFundamentalMatrix();
  const Eigen::Vector2d pp = MakeTestPrincipalPoint();

  // Just verify construction is possible (no crashes / exceptions).
  FetzerFocalLengthSameCameraCost cost(F, pp);

  (void)cost;  // Suppress unused variable warning.
}

//------------------------------------------------------------------------------
// Create() should return a non-null ceres::CostFunction pointer for
// valid inputs, which is the minimal contract we can assert from
// the public interface.
//------------------------------------------------------------------------------
TEST_F(FetzerFocalLengthSameCameraCostTest_168,
       CreateReturnsNonNullCostFunction_168) {
  const Eigen::Matrix3d F = MakeTestFundamentalMatrix();
  const Eigen::Vector2d pp = MakeTestPrincipalPoint();

  ceres::CostFunction* cost_function =
      FetzerFocalLengthSameCameraCost::Create(F, pp);

  ASSERT_NE(cost_function, nullptr);

  // We don't assume any specific internal structure like residual count
  // or parameter block sizes beyond what can be queried via the interface.
  EXPECT_GT(cost_function->num_residuals(), 0);

  // Ceres guarantees at least one parameter block for a valid cost function.
  ASSERT_FALSE(cost_function->parameter_block_sizes().empty());

  delete cost_function;
}

//------------------------------------------------------------------------------
// Verify that evaluating the created CostFunction is deterministic for the
// same input parameter values: calling Evaluate twice with identical
// inputs should produce identical residuals. This only relies on
// observable behavior (output consistency).
//------------------------------------------------------------------------------
TEST_F(FetzerFocalLengthSameCameraCostTest_168,
       EvaluateIsDeterministicForSameInput_168) {
  const Eigen::Matrix3d F = MakeTestFundamentalMatrix();
  const Eigen::Vector2d pp = MakeTestPrincipalPoint();

  ceres::CostFunction* cost_function =
      FetzerFocalLengthSameCameraCost::Create(F, pp);
  ASSERT_NE(cost_function, nullptr);

  const int num_residuals = cost_function->num_residuals();
  ASSERT_GT(num_residuals, 0);

  // Assume at least one parameter block; we don't depend on its exact size.
  const std::vector<int32_t>& param_block_sizes =
      cost_function->parameter_block_sizes();
  ASSERT_FALSE(param_block_sizes.empty());

  // Allocate one parameter block and fill with a fixed value.
  const int param_block_size = param_block_sizes[0];
  ASSERT_GT(param_block_size, 0);

  std::vector<double> params_storage(param_block_size, 800.0);
  double* parameter_blocks[] = { params_storage.data() };

  std::vector<double> residuals_first(num_residuals);
  std::vector<double> residuals_second(num_residuals);

  // First evaluation.
  bool ok_first = cost_function->Evaluate(
      reinterpret_cast<double* const*>(parameter_blocks),
      residuals_first.data(),
      nullptr);
  EXPECT_TRUE(ok_first);

  // Second evaluation with the same parameters.
  bool ok_second = cost_function->Evaluate(
      reinterpret_cast<double* const*>(parameter_blocks),
      residuals_second.data(),
      nullptr);
  EXPECT_TRUE(ok_second);

  // For a deterministic, side-effect-free cost, residuals must match.
  for (int i = 0; i < num_residuals; ++i) {
    EXPECT_DOUBLE_EQ(residuals_first[i], residuals_second[i]);
  }

  delete cost_function;
}

//------------------------------------------------------------------------------
// Boundary-ish case: use a highly degenerate fundamental matrix (all zeros)
// and check that the cost function can still be constructed and evaluated,
// and that it produces finite residuals. We don't assert specific values,
// only that the outputs are well-formed and observable through the API.
//------------------------------------------------------------------------------
TEST_F(FetzerFocalLengthSameCameraCostTest_168,
       EvaluateHandlesDegenerateFundamentalMatrix_168) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  Eigen::Vector2d pp = MakeTestPrincipalPoint();

  ceres::CostFunction* cost_function =
      FetzerFocalLengthSameCameraCost::Create(F, pp);
  ASSERT_NE(cost_function, nullptr);

  const int num_residuals = cost_function->num_residuals();
  ASSERT_GT(num_residuals, 0);

  const std::vector<int32_t>& param_block_sizes =
      cost_function->parameter_block_sizes();
  ASSERT_FALSE(param_block_sizes.empty());
  const int param_block_size = param_block_sizes[0];
  ASSERT_GT(param_block_size, 0);

  std::vector<double> params_storage(param_block_size, 1200.0);
  double* parameter_blocks[] = { params_storage.data() };

  std::vector<double> residuals(num_residuals);

  bool ok = cost_function->Evaluate(
      reinterpret_cast<double* const*>(parameter_blocks),
      residuals.data(),
      nullptr);

  EXPECT_TRUE(ok);

  // Check that residuals are finite numbers (no NaN or infinity).
  for (int i = 0; i < num_residuals; ++i) {
    EXPECT_TRUE(std::isfinite(residuals[i]));
  }

  delete cost_function;
}

}  // namespace glomap
