#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ceres/ceres.h>
#include <memory>

#include "glomap/estimators/global_positioning.h"

namespace glomap {
namespace {

class GlobalPositionerOptionsTest_24 : public ::testing::Test {
 protected:
  GlobalPositionerOptions options_;
};

// Test default construction and default values
TEST_F(GlobalPositionerOptionsTest_24, DefaultConstruction_24) {
  GlobalPositionerOptions opts;
  EXPECT_TRUE(opts.generate_random_positions);
  EXPECT_TRUE(opts.generate_random_points);
  EXPECT_TRUE(opts.generate_scales);
  EXPECT_TRUE(opts.optimize_positions);
  EXPECT_TRUE(opts.optimize_scales);
  EXPECT_EQ(opts.seed, 1u);
  EXPECT_EQ(opts.constraint_type, ONLY_POINTS);
  EXPECT_DOUBLE_EQ(opts.constraint_reweight_scale, 1.0);
}

// Test that CreateLossFunction returns a non-null pointer
TEST_F(GlobalPositionerOptionsTest_24, CreateLossFunctionReturnsNonNull_24) {
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);
}

// Test that CreateLossFunction returns a valid shared_ptr that can be used
TEST_F(GlobalPositionerOptionsTest_24, CreateLossFunctionReturnsUsableLoss_24) {
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);
  
  // Evaluate the Huber loss at a point - the loss function should be callable
  double rho[3];
  loss->Evaluate(0.0, rho);
  // At sq_norm = 0, Huber loss: rho[0] = 0, rho[1] = 1, rho[2] = 0
  EXPECT_DOUBLE_EQ(rho[0], 0.0);
  EXPECT_DOUBLE_EQ(rho[1], 1.0);
}

// Test that the loss function uses the threshold from base class
TEST_F(GlobalPositionerOptionsTest_24, CreateLossFunctionUsesThreshold_24) {
  // Default thres_loss_function is 0.1
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);
  
  // For HuberLoss with threshold a, when sq_norm < a:
  //   rho[0] = sq_norm (quadratic region)
  // When sq_norm > a:
  //   rho[0] = 2*a*sqrt(sq_norm) - a^2 (linear region)
  
  // Test in quadratic region (sq_norm < 0.1)
  double rho[3];
  double small_val = 0.01;  // less than 0.1
  loss->Evaluate(small_val, rho);
  EXPECT_DOUBLE_EQ(rho[0], small_val);
  EXPECT_DOUBLE_EQ(rho[1], 1.0);
  
  // Test in linear region (sq_norm > 0.1)
  double large_val = 1.0;  // greater than 0.1
  loss->Evaluate(large_val, rho);
  double expected = 2.0 * 0.1 * std::sqrt(large_val) - 0.1 * 0.1;
  EXPECT_NEAR(rho[0], expected, 1e-10);
}

// Test that modifying thres_loss_function affects CreateLossFunction
TEST_F(GlobalPositionerOptionsTest_24, ModifiedThresholdAffectsLoss_24) {
  options_.thres_loss_function = 1.0;
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);
  
  // With threshold 1.0, sq_norm = 0.5 should be in quadratic region
  double rho[3];
  loss->Evaluate(0.5, rho);
  EXPECT_DOUBLE_EQ(rho[0], 0.5);
  EXPECT_DOUBLE_EQ(rho[1], 1.0);
}

// Test that each call to CreateLossFunction returns a new object
TEST_F(GlobalPositionerOptionsTest_24, CreateLossFunctionReturnsNewInstance_24) {
  auto loss1 = options_.CreateLossFunction();
  auto loss2 = options_.CreateLossFunction();
  ASSERT_NE(loss1, nullptr);
  ASSERT_NE(loss2, nullptr);
  EXPECT_NE(loss1.get(), loss2.get());
}

// Test inherited thres_loss_function default
TEST_F(GlobalPositionerOptionsTest_24, InheritedThresholdDefault_24) {
  EXPECT_DOUBLE_EQ(options_.thres_loss_function, 0.1);
}

// Test that boolean options can be modified
TEST_F(GlobalPositionerOptionsTest_24, BooleanOptionsModifiable_24) {
  options_.generate_random_positions = false;
  options_.generate_random_points = false;
  options_.generate_scales = false;
  options_.optimize_positions = false;
  options_.optimize_scales = false;
  
  EXPECT_FALSE(options_.generate_random_positions);
  EXPECT_FALSE(options_.generate_random_points);
  EXPECT_FALSE(options_.generate_scales);
  EXPECT_FALSE(options_.optimize_positions);
  EXPECT_FALSE(options_.optimize_scales);
}

// Test seed modification
TEST_F(GlobalPositionerOptionsTest_24, SeedModifiable_24) {
  options_.seed = 42;
  EXPECT_EQ(options_.seed, 42u);
}

// Test constraint_reweight_scale modification
TEST_F(GlobalPositionerOptionsTest_24, ConstraintReweightScaleModifiable_24) {
  options_.constraint_reweight_scale = 2.5;
  EXPECT_DOUBLE_EQ(options_.constraint_reweight_scale, 2.5);
}

// Test with very small threshold
TEST_F(GlobalPositionerOptionsTest_24, VerySmallThreshold_24) {
  options_.thres_loss_function = 1e-10;
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);
  
  double rho[3];
  loss->Evaluate(1e-12, rho);
  // Should be in quadratic region
  EXPECT_NEAR(rho[0], 1e-12, 1e-20);
}

// Test with very large threshold
TEST_F(GlobalPositionerOptionsTest_24, VeryLargeThreshold_24) {
  options_.thres_loss_function = 1e10;
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);
  
  double rho[3];
  // Even a large value should be in quadratic region with such a large threshold
  loss->Evaluate(100.0, rho);
  EXPECT_DOUBLE_EQ(rho[0], 100.0);
  EXPECT_DOUBLE_EQ(rho[1], 1.0);
}

// Test loss at the boundary of the Huber threshold
TEST_F(GlobalPositionerOptionsTest_24, LossAtBoundary_24) {
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);
  
  // Evaluate at exactly the threshold value (0.1)
  double rho[3];
  loss->Evaluate(options_.thres_loss_function, rho);
  // At the boundary, both regions give the same value = thres_loss_function
  EXPECT_NEAR(rho[0], options_.thres_loss_function, 1e-12);
}

// Test that GlobalPositionerOptions is a subclass of OptimizationBaseOptions
TEST_F(GlobalPositionerOptionsTest_24, InheritsFromOptimizationBaseOptions_24) {
  OptimizationBaseOptions* base_ptr = &options_;
  EXPECT_NE(base_ptr, nullptr);
  // Should be able to access base class member
  EXPECT_DOUBLE_EQ(base_ptr->thres_loss_function, 0.1);
}

}  // namespace
}  // namespace glomap
