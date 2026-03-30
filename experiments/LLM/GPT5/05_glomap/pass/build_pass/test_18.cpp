// File: fetzer_focal_length_same_camera_cost_test_18.cc

#include <cmath>
#include <memory>

#include <gtest/gtest.h>
#include <ceres/ceres.h>
#include <Eigen/Core>

#include "glomap/estimators/cost_function.h"

namespace glomap {

class FetzerFocalLengthSameCameraCostTest_18 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Use a fixed, non-degenerate fundamental matrix and principal point.
    i1_F_i0_ << 0.0,  1.0,  2.0,
               -1.0,  0.5,  0.0,
                3.0, -0.5,  0.25;
    principal_point_ << 0.1, -0.2;

    cost_functor_ =
        std::make_unique<FetzerFocalLengthSameCameraCost>(i1_F_i0_,
                                                          principal_point_);
  }

  Eigen::Matrix3d i1_F_i0_;
  Eigen::Vector2d principal_point_;
  std::unique_ptr<FetzerFocalLengthSameCameraCost> cost_functor_;
};

// Normal operation: operator() returns true and produces finite residuals
// for a typical focal length.
TEST_F(FetzerFocalLengthSameCameraCostTest_18,
       OperatorReturnsTrueAndFiniteResiduals_18) {
  double fi = 800.0;
  double residuals[2];

  const bool ok = (*cost_functor_)(&fi, residuals);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Determinism: calling operator() twice with the same input should
// produce identical residuals (black-box determinism).
TEST_F(FetzerFocalLengthSameCameraCostTest_18,
       OperatorIsDeterministicForSameInput_18) {
  double fi = 800.0;
  double residuals1[2];
  double residuals2[2];

  ASSERT_TRUE((*cost_functor_)(&fi, residuals1));
  ASSERT_TRUE((*cost_functor_)(&fi, residuals2));

  EXPECT_DOUBLE_EQ(residuals1[0], residuals2[0]);
  EXPECT_DOUBLE_EQ(residuals1[1], residuals2[1]);
}

// Boundary-ish case: small (but non-zero) focal length should still
// return true and finite residuals.
TEST_F(FetzerFocalLengthSameCameraCostTest_18,
       OperatorHandlesSmallPositiveFocalLength_18) {
  double fi = 1e-3;
  double residuals[2];

  const bool ok = (*cost_functor_)(&fi, residuals);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Create(): verify that the returned Ceres cost function is non-null and
// configured consistently with the functor interface (2 residuals,
// 1 parameter block of size 1).
TEST_F(FetzerFocalLengthSameCameraCostTest_18,
       CreateReturnsConfiguredCeresCostFunction_18) {
  std::unique_ptr<ceres::CostFunction> cost(
      FetzerFocalLengthSameCameraCost::Create(i1_F_i0_, principal_point_));

  ASSERT_NE(cost, nullptr);

  // The functor writes residuals[0] and residuals[1] => 2 residuals expected.
  EXPECT_EQ(cost->num_residuals(), 2);

  // Functor takes a single pointer fi_ (T* const) => one parameter block.
  ASSERT_EQ(cost->parameter_block_sizes().size(), 1u);
  EXPECT_EQ(cost->parameter_block_sizes()[0], 1);
}

// Integration test: Ceres CostFunction created via Create() should
// produce the same residuals as invoking the functor directly for the
// same focal length.
TEST_F(FetzerFocalLengthSameCameraCostTest_18,
       CreateEvaluateMatchesDirectOperator_18) {
  std::unique_ptr<ceres::CostFunction> cost(
      FetzerFocalLengthSameCameraCost::Create(i1_F_i0_, principal_point_));
  ASSERT_NE(cost, nullptr);

  double fi = 800.0;

  // Evaluate via Ceres::CostFunction
  double ceres_residuals[2];
  double* parameters[] = { &fi };
  const bool eval_ok =
      cost->Evaluate(const_cast<const double* const*>(parameters),
                     ceres_residuals,
                     nullptr);
  ASSERT_TRUE(eval_ok);

  // Evaluate via direct functor call
  double direct_residuals[2];
  const bool direct_ok = (*cost_functor_)(&fi, direct_residuals);
  ASSERT_TRUE(direct_ok);

  // Both paths should yield the same residuals (up to numerical tolerance).
  EXPECT_NEAR(direct_residuals[0], ceres_residuals[0], 1e-12);
  EXPECT_NEAR(direct_residuals[1], ceres_residuals[1], 1e-12);
}

}  // namespace glomap
