#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <ceres/ceres.h>
#include "glomap/estimators/view_graph_calibration.h"

namespace glomap {
namespace {

class ViewGraphCalibratorOptionsTest_11 : public ::testing::Test {
 protected:
  ViewGraphCalibratorOptions options_;
};

// Test default construction and default values
TEST_F(ViewGraphCalibratorOptionsTest_11, DefaultConstruction_11) {
  ViewGraphCalibratorOptions opts;
  // Verify default values from the known interface
  EXPECT_DOUBLE_EQ(opts.thres_lower_ratio, 0.1);
  EXPECT_DOUBLE_EQ(opts.thres_higher_ratio, 10.0);
  EXPECT_DOUBLE_EQ(opts.thres_two_view_error, 2.0);
}

// Test that base class default values are inherited
TEST_F(ViewGraphCalibratorOptionsTest_11, InheritsBaseDefaults_11) {
  EXPECT_DOUBLE_EQ(options_.thres_loss_function, 0.1);
}

// Test CreateLossFunction returns a non-null pointer
TEST_F(ViewGraphCalibratorOptionsTest_11, CreateLossFunctionReturnsNonNull_11) {
  auto loss = options_.CreateLossFunction();
  EXPECT_NE(loss, nullptr);
}

// Test CreateLossFunction returns a valid shared_ptr that can be used
TEST_F(ViewGraphCalibratorOptionsTest_11, CreateLossFunctionReturnsValidSharedPtr_11) {
  std::shared_ptr<ceres::LossFunction> loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);
  
  // The loss function should be callable - CauchyLoss::Evaluate
  double rho[3];
  loss->Evaluate(1.0, rho);
  // CauchyLoss with parameter c: rho[0] = c^2 * log(1 + s/c^2)
  // For s=1.0, c=0.1: rho[0] = 0.01 * log(1 + 1.0/0.01) = 0.01 * log(101)
  EXPECT_GT(rho[0], 0.0);
}

// Test CreateLossFunction with modified thres_loss_function
TEST_F(ViewGraphCalibratorOptionsTest_11, CreateLossFunctionRespectsThreshold_11) {
  ViewGraphCalibratorOptions opts1;
  opts1.thres_loss_function = 0.1;
  auto loss1 = opts1.CreateLossFunction();

  ViewGraphCalibratorOptions opts2;
  opts2.thres_loss_function = 1.0;
  auto loss2 = opts2.CreateLossFunction();

  double rho1[3], rho2[3];
  double sq_norm = 4.0;
  loss1->Evaluate(sq_norm, rho1);
  loss2->Evaluate(sq_norm, rho2);

  // Different threshold should produce different loss values
  EXPECT_NE(rho1[0], rho2[0]);
}

// Test CreateLossFunction produces consistent results when called multiple times
TEST_F(ViewGraphCalibratorOptionsTest_11, CreateLossFunctionConsistency_11) {
  auto loss1 = options_.CreateLossFunction();
  auto loss2 = options_.CreateLossFunction();

  double rho1[3], rho2[3];
  loss1->Evaluate(2.0, rho1);
  loss2->Evaluate(2.0, rho2);

  EXPECT_DOUBLE_EQ(rho1[0], rho2[0]);
  EXPECT_DOUBLE_EQ(rho1[1], rho2[1]);
  EXPECT_DOUBLE_EQ(rho1[2], rho2[2]);
}

// Test CreateLossFunction returns independent shared_ptr instances
TEST_F(ViewGraphCalibratorOptionsTest_11, CreateLossFunctionReturnsIndependentInstances_11) {
  auto loss1 = options_.CreateLossFunction();
  auto loss2 = options_.CreateLossFunction();

  // They should be different objects
  EXPECT_NE(loss1.get(), loss2.get());
}

// Test that the loss function evaluates correctly at zero
TEST_F(ViewGraphCalibratorOptionsTest_11, CreateLossFunctionEvaluateAtZero_11) {
  auto loss = options_.CreateLossFunction();
  double rho[3];
  loss->Evaluate(0.0, rho);
  
  // CauchyLoss at s=0: rho[0] = c^2 * log(1 + 0/c^2) = 0
  EXPECT_DOUBLE_EQ(rho[0], 0.0);
}

// Test that the loss function evaluates at large values (robustness)
TEST_F(ViewGraphCalibratorOptionsTest_11, CreateLossFunctionEvaluateAtLargeValue_11) {
  auto loss = options_.CreateLossFunction();
  double rho[3];
  loss->Evaluate(1e6, rho);
  
  // The CauchyLoss should produce a finite, positive value
  EXPECT_TRUE(std::isfinite(rho[0]));
  EXPECT_GT(rho[0], 0.0);
}

// Test modifying thres_lower_ratio
TEST_F(ViewGraphCalibratorOptionsTest_11, ModifyThresLowerRatio_11) {
  options_.thres_lower_ratio = 0.5;
  EXPECT_DOUBLE_EQ(options_.thres_lower_ratio, 0.5);
}

// Test modifying thres_higher_ratio
TEST_F(ViewGraphCalibratorOptionsTest_11, ModifyThresHigherRatio_11) {
  options_.thres_higher_ratio = 20.0;
  EXPECT_DOUBLE_EQ(options_.thres_higher_ratio, 20.0);
}

// Test modifying thres_two_view_error
TEST_F(ViewGraphCalibratorOptionsTest_11, ModifyThresTwoViewError_11) {
  options_.thres_two_view_error = 5.0;
  EXPECT_DOUBLE_EQ(options_.thres_two_view_error, 5.0);
}

// Test that changing thres_loss_function after construction affects CreateLossFunction
TEST_F(ViewGraphCalibratorOptionsTest_11, ChangingThresLossFunctionAffectsCreation_11) {
  double rho_before[3], rho_after[3];
  double test_val = 10.0;

  auto loss_before = options_.CreateLossFunction();
  loss_before->Evaluate(test_val, rho_before);

  options_.thres_loss_function = 5.0;
  auto loss_after = options_.CreateLossFunction();
  loss_after->Evaluate(test_val, rho_after);

  // With a very different threshold, the loss values should differ
  EXPECT_NE(rho_before[0], rho_after[0]);
}

// Boundary: very small thres_loss_function
TEST_F(ViewGraphCalibratorOptionsTest_11, VerySmallThresLossFunction_11) {
  options_.thres_loss_function = 1e-10;
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);

  double rho[3];
  loss->Evaluate(1.0, rho);
  EXPECT_TRUE(std::isfinite(rho[0]));
  EXPECT_GT(rho[0], 0.0);
}

// Boundary: very large thres_loss_function
TEST_F(ViewGraphCalibratorOptionsTest_11, VeryLargeThresLossFunction_11) {
  options_.thres_loss_function = 1e10;
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);

  double rho[3];
  loss->Evaluate(1.0, rho);
  EXPECT_TRUE(std::isfinite(rho[0]));
  EXPECT_GT(rho[0], 0.0);
}

// Test that CauchyLoss derivative (rho[1]) is positive for positive input
TEST_F(ViewGraphCalibratorOptionsTest_11, CreateLossFunctionPositiveDerivative_11) {
  auto loss = options_.CreateLossFunction();
  double rho[3];
  loss->Evaluate(1.0, rho);
  
  // CauchyLoss rho[1] = 1 / (1 + s/c^2), which should be positive
  EXPECT_GT(rho[1], 0.0);
}

}  // namespace
}  // namespace glomap
