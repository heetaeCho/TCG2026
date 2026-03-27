// File: view_graph_calibrator_options_test_162.cc

#include <memory>
#include <cmath>

#include <gtest/gtest.h>
#include <ceres/loss_function.h>
#include <ceres/solver.h>

#include "glomap/estimators/view_graph_calibration.h"

using glomap::ViewGraphCalibratorOptions;

class ViewGraphCalibratorOptionsTest_162 : public ::testing::Test {};

// TEST_ID: 162
TEST_F(ViewGraphCalibratorOptionsTest_162,
       DefaultConstructorInitializesThresholds_162) {
  ViewGraphCalibratorOptions options;

  // Derived class members – from header default member initializers
  EXPECT_NEAR(options.thres_lower_ratio, 0.1, 1e-12);
  EXPECT_DOUBLE_EQ(options.thres_higher_ratio, 10.0);
  EXPECT_DOUBLE_EQ(options.thres_two_view_error, 2.0);

  // Base class member overridden in derived constructor
  // (first partial snippet: thres_loss_function = 1e-2)
  EXPECT_NEAR(options.thres_loss_function, 1e-2, 1e-12);
}

// TEST_ID: 162
TEST_F(ViewGraphCalibratorOptionsTest_162,
       CreateLossFunctionReturnsValidLoss_162) {
  ViewGraphCalibratorOptions options;

  // Normal operation: should create a non-null loss function
  std::shared_ptr<ceres::LossFunction> loss = options.CreateLossFunction();
  ASSERT_TRUE(static_cast<bool>(loss));

  // Basic sanity: the created loss function should be usable
  double rho[3] = {0.0, 0.0, 0.0};
  EXPECT_NO_THROW({
    loss->Evaluate(1.0, rho);
  });

  // The primary loss value should be finite (very weak, generic check)
  EXPECT_TRUE(std::isfinite(rho[0]));
}

// TEST_ID: 162
TEST_F(ViewGraphCalibratorOptionsTest_162,
       CreateLossFunctionWorksWithModifiedThreshold_162) {
  ViewGraphCalibratorOptions options;

  // Modify the base-class threshold before creating the loss function
  // (boundary-style scenario: much smaller threshold)
  options.thres_loss_function = 1e-6;

  std::shared_ptr<ceres::LossFunction> loss = options.CreateLossFunction();
  ASSERT_TRUE(static_cast<bool>(loss));

  double rho[3] = {0.0, 0.0, 0.0};
  EXPECT_NO_THROW({
    loss->Evaluate(0.5, rho);
  });

  EXPECT_TRUE(std::isfinite(rho[0]));
}
