#include <gtest/gtest.h>
#include "glomap/estimators/view_graph_calibration.h"

namespace glomap {
namespace {

// Test default construction and default values
TEST(ViewGraphCalibratorOptionsTest_162, DefaultConstruction_162) {
  ViewGraphCalibratorOptions options;
  // thres_loss_function should be overridden to 1e-2 by ViewGraphCalibratorOptions constructor
  EXPECT_DOUBLE_EQ(options.thres_loss_function, 1e-2);
}

TEST(ViewGraphCalibratorOptionsTest_162, DefaultThresLowerRatio_162) {
  ViewGraphCalibratorOptions options;
  EXPECT_DOUBLE_EQ(options.thres_lower_ratio, 0.1);
}

TEST(ViewGraphCalibratorOptionsTest_162, DefaultThresHigherRatio_162) {
  ViewGraphCalibratorOptions options;
  EXPECT_DOUBLE_EQ(options.thres_higher_ratio, 10.0);
}

TEST(ViewGraphCalibratorOptionsTest_162, DefaultThresTwoViewError_162) {
  ViewGraphCalibratorOptions options;
  EXPECT_DOUBLE_EQ(options.thres_two_view_error, 2.0);
}

// Test that values can be modified after construction
TEST(ViewGraphCalibratorOptionsTest_162, ModifyThresLowerRatio_162) {
  ViewGraphCalibratorOptions options;
  options.thres_lower_ratio = 0.5;
  EXPECT_DOUBLE_EQ(options.thres_lower_ratio, 0.5);
}

TEST(ViewGraphCalibratorOptionsTest_162, ModifyThresHigherRatio_162) {
  ViewGraphCalibratorOptions options;
  options.thres_higher_ratio = 20.0;
  EXPECT_DOUBLE_EQ(options.thres_higher_ratio, 20.0);
}

TEST(ViewGraphCalibratorOptionsTest_162, ModifyThresTwoViewError_162) {
  ViewGraphCalibratorOptions options;
  options.thres_two_view_error = 5.0;
  EXPECT_DOUBLE_EQ(options.thres_two_view_error, 5.0);
}

TEST(ViewGraphCalibratorOptionsTest_162, ModifyThresLossFunction_162) {
  ViewGraphCalibratorOptions options;
  options.thres_loss_function = 0.5;
  EXPECT_DOUBLE_EQ(options.thres_loss_function, 0.5);
}

// Test that CreateLossFunction returns a non-null shared_ptr
TEST(ViewGraphCalibratorOptionsTest_162, CreateLossFunctionNotNull_162) {
  ViewGraphCalibratorOptions options;
  auto loss = options.CreateLossFunction();
  EXPECT_NE(loss, nullptr);
}

// Test that CreateLossFunction can be called multiple times
TEST(ViewGraphCalibratorOptionsTest_162, CreateLossFunctionMultipleCalls_162) {
  ViewGraphCalibratorOptions options;
  auto loss1 = options.CreateLossFunction();
  auto loss2 = options.CreateLossFunction();
  EXPECT_NE(loss1, nullptr);
  EXPECT_NE(loss2, nullptr);
}

// Test that the struct inherits from OptimizationBaseOptions
TEST(ViewGraphCalibratorOptionsTest_162, InheritsFromOptimizationBaseOptions_162) {
  ViewGraphCalibratorOptions options;
  OptimizationBaseOptions* base = &options;
  // The overridden value should be visible through the base pointer
  EXPECT_DOUBLE_EQ(base->thres_loss_function, 1e-2);
}

// Boundary: setting thres_lower_ratio to 0
TEST(ViewGraphCalibratorOptionsTest_162, BoundaryThresLowerRatioZero_162) {
  ViewGraphCalibratorOptions options;
  options.thres_lower_ratio = 0.0;
  EXPECT_DOUBLE_EQ(options.thres_lower_ratio, 0.0);
}

// Boundary: setting thres_higher_ratio to a very large value
TEST(ViewGraphCalibratorOptionsTest_162, BoundaryThresHigherRatioLarge_162) {
  ViewGraphCalibratorOptions options;
  options.thres_higher_ratio = 1e10;
  EXPECT_DOUBLE_EQ(options.thres_higher_ratio, 1e10);
}

// Boundary: setting thres_two_view_error to 0
TEST(ViewGraphCalibratorOptionsTest_162, BoundaryThresTwoViewErrorZero_162) {
  ViewGraphCalibratorOptions options;
  options.thres_two_view_error = 0.0;
  EXPECT_DOUBLE_EQ(options.thres_two_view_error, 0.0);
}

// Boundary: negative values
TEST(ViewGraphCalibratorOptionsTest_162, BoundaryNegativeValues_162) {
  ViewGraphCalibratorOptions options;
  options.thres_lower_ratio = -1.0;
  options.thres_higher_ratio = -1.0;
  options.thres_two_view_error = -1.0;
  EXPECT_DOUBLE_EQ(options.thres_lower_ratio, -1.0);
  EXPECT_DOUBLE_EQ(options.thres_higher_ratio, -1.0);
  EXPECT_DOUBLE_EQ(options.thres_two_view_error, -1.0);
}

// Test copy construction preserves values
TEST(ViewGraphCalibratorOptionsTest_162, CopyConstruction_162) {
  ViewGraphCalibratorOptions options;
  options.thres_lower_ratio = 0.5;
  options.thres_higher_ratio = 15.0;
  options.thres_two_view_error = 3.0;
  options.thres_loss_function = 0.05;

  ViewGraphCalibratorOptions copied = options;
  EXPECT_DOUBLE_EQ(copied.thres_lower_ratio, 0.5);
  EXPECT_DOUBLE_EQ(copied.thres_higher_ratio, 15.0);
  EXPECT_DOUBLE_EQ(copied.thres_two_view_error, 3.0);
  EXPECT_DOUBLE_EQ(copied.thres_loss_function, 0.05);
}

// Test that modifying thres_loss_function and then calling CreateLossFunction still works
TEST(ViewGraphCalibratorOptionsTest_162, CreateLossFunctionAfterModification_162) {
  ViewGraphCalibratorOptions options;
  options.thres_loss_function = 1.0;
  auto loss = options.CreateLossFunction();
  EXPECT_NE(loss, nullptr);
}

}  // namespace
}  // namespace glomap
