// File: view_graph_calibration_test_11.cc

#include <gtest/gtest.h>
#include <ceres/loss_function.h>

#include "glomap/estimators/view_graph_calibration.h"

namespace {

class ViewGraphCalibratorOptionsTest_11 : public ::testing::Test {
 protected:
  glomap::ViewGraphCalibratorOptions options_;
};

// Verifies that default thresholds are initialized as declared in the interface.
TEST_F(ViewGraphCalibratorOptionsTest_11, DefaultThresholdsAreInitialized_11) {
  // From OptimizationBaseOptions
  EXPECT_DOUBLE_EQ(0.1, options_.thres_loss_function);

  // From ViewGraphCalibratorOptions
  EXPECT_DOUBLE_EQ(0.1, options_.thres_lower_ratio);
  EXPECT_DOUBLE_EQ(10.0, options_.thres_higher_ratio);
  EXPECT_DOUBLE_EQ(2.0, options_.thres_two_view_error);
}

// Verifies that CreateLossFunction returns a valid loss function.
TEST_F(ViewGraphCalibratorOptionsTest_11, CreateLossFunctionReturnsNonNull_11) {
  std::shared_ptr<ceres::LossFunction> loss = options_.CreateLossFunction();
  EXPECT_NE(loss, nullptr);
}

// Verifies that the created loss function reflects the thres_loss_function value
// in its observable behavior (loss value for a given residual).
TEST_F(ViewGraphCalibratorOptionsTest_11, LossFunctionDependsOnThreshold_11) {
  const double sq_residual = 1.0;

  // Loss function with default threshold.
  auto loss_default = options_.CreateLossFunction();
  ASSERT_NE(loss_default, nullptr);
  double rho_default[3];
  loss_default->Evaluate(sq_residual, rho_default);

  // Loss function with modified threshold.
  glomap::ViewGraphCalibratorOptions options_modified;
  options_modified.thres_loss_function = options_.thres_loss_function * 10.0;
  auto loss_modified = options_modified.CreateLossFunction();
  ASSERT_NE(loss_modified, nullptr);
  double rho_modified[3];
  loss_modified->Evaluate(sq_residual, rho_modified);

  // Changing the threshold should change the loss value for the same residual.
  EXPECT_NE(rho_default[0], rho_modified[0]);
}

// Verifies that each call to CreateLossFunction returns a distinct instance.
TEST_F(ViewGraphCalibratorOptionsTest_11, CreateLossFunctionReturnsDistinctInstances_11) {
  auto loss1 = options_.CreateLossFunction();
  auto loss2 = options_.CreateLossFunction();

  ASSERT_NE(loss1, nullptr);
  ASSERT_NE(loss2, nullptr);

  // The underlying objects should be different.
  EXPECT_NE(loss1.get(), loss2.get());
}

}  // namespace
