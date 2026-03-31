#include <gtest/gtest.h>
#include "glomap/estimators/global_positioning.h"

namespace glomap {
namespace {

// Test fixture for GlobalPositionerOptions
class GlobalPositionerOptionsTest_165 : public ::testing::Test {
 protected:
  GlobalPositionerOptions options_;
};

// Test default construction values
TEST_F(GlobalPositionerOptionsTest_165, DefaultConstruction_165) {
  GlobalPositionerOptions opts;
  // Verify that the object can be default constructed
  SUCCEED();
}

TEST_F(GlobalPositionerOptionsTest_165, DefaultThresLossFunction_165) {
  // The constructor sets thres_loss_function = 1e-1
  EXPECT_DOUBLE_EQ(options_.thres_loss_function, 1e-1);
}

TEST_F(GlobalPositionerOptionsTest_165, DefaultGenerateRandomPositions_165) {
  EXPECT_TRUE(options_.generate_random_positions);
}

TEST_F(GlobalPositionerOptionsTest_165, DefaultGenerateRandomPoints_165) {
  EXPECT_TRUE(options_.generate_random_points);
}

TEST_F(GlobalPositionerOptionsTest_165, DefaultGenerateScales_165) {
  EXPECT_TRUE(options_.generate_scales);
}

TEST_F(GlobalPositionerOptionsTest_165, DefaultOptimizePositions_165) {
  EXPECT_TRUE(options_.optimize_positions);
}

TEST_F(GlobalPositionerOptionsTest_165, DefaultOptimizeScales_165) {
  EXPECT_TRUE(options_.optimize_scales);
}

TEST_F(GlobalPositionerOptionsTest_165, DefaultSeed_165) {
  EXPECT_EQ(options_.seed, 1u);
}

TEST_F(GlobalPositionerOptionsTest_165, DefaultConstraintType_165) {
  EXPECT_EQ(options_.constraint_type, ONLY_POINTS);
}

TEST_F(GlobalPositionerOptionsTest_165, DefaultConstraintReweightScale_165) {
  EXPECT_DOUBLE_EQ(options_.constraint_reweight_scale, 1.0);
}

// Test that boolean fields can be modified
TEST_F(GlobalPositionerOptionsTest_165, ModifyGenerateRandomPositions_165) {
  options_.generate_random_positions = false;
  EXPECT_FALSE(options_.generate_random_positions);
}

TEST_F(GlobalPositionerOptionsTest_165, ModifyGenerateRandomPoints_165) {
  options_.generate_random_points = false;
  EXPECT_FALSE(options_.generate_random_points);
}

TEST_F(GlobalPositionerOptionsTest_165, ModifyGenerateScales_165) {
  options_.generate_scales = false;
  EXPECT_FALSE(options_.generate_scales);
}

TEST_F(GlobalPositionerOptionsTest_165, ModifyOptimizePositions_165) {
  options_.optimize_positions = false;
  EXPECT_FALSE(options_.optimize_positions);
}

TEST_F(GlobalPositionerOptionsTest_165, ModifyOptimizeScales_165) {
  options_.optimize_scales = false;
  EXPECT_FALSE(options_.optimize_scales);
}

TEST_F(GlobalPositionerOptionsTest_165, ModifySeed_165) {
  options_.seed = 42;
  EXPECT_EQ(options_.seed, 42u);
}

TEST_F(GlobalPositionerOptionsTest_165, ModifySeedZero_165) {
  options_.seed = 0;
  EXPECT_EQ(options_.seed, 0u);
}

TEST_F(GlobalPositionerOptionsTest_165, ModifySeedMaxValue_165) {
  options_.seed = std::numeric_limits<unsigned int>::max();
  EXPECT_EQ(options_.seed, std::numeric_limits<unsigned int>::max());
}

TEST_F(GlobalPositionerOptionsTest_165, ModifyConstraintReweightScale_165) {
  options_.constraint_reweight_scale = 0.5;
  EXPECT_DOUBLE_EQ(options_.constraint_reweight_scale, 0.5);
}

TEST_F(GlobalPositionerOptionsTest_165, ModifyConstraintReweightScaleZero_165) {
  options_.constraint_reweight_scale = 0.0;
  EXPECT_DOUBLE_EQ(options_.constraint_reweight_scale, 0.0);
}

TEST_F(GlobalPositionerOptionsTest_165, ModifyConstraintReweightScaleNegative_165) {
  options_.constraint_reweight_scale = -1.0;
  EXPECT_DOUBLE_EQ(options_.constraint_reweight_scale, -1.0);
}

TEST_F(GlobalPositionerOptionsTest_165, ModifyThresLossFunction_165) {
  options_.thres_loss_function = 0.5;
  EXPECT_DOUBLE_EQ(options_.thres_loss_function, 0.5);
}

// Test CreateLossFunction returns a valid shared_ptr
TEST_F(GlobalPositionerOptionsTest_165, CreateLossFunctionReturnsNonNull_165) {
  auto loss_fn = options_.CreateLossFunction();
  EXPECT_NE(loss_fn, nullptr);
}

// Test CreateLossFunction with modified thres_loss_function
TEST_F(GlobalPositionerOptionsTest_165, CreateLossFunctionWithModifiedThreshold_165) {
  options_.thres_loss_function = 1.0;
  auto loss_fn = options_.CreateLossFunction();
  EXPECT_NE(loss_fn, nullptr);
}

// Test CreateLossFunction with very small threshold
TEST_F(GlobalPositionerOptionsTest_165, CreateLossFunctionSmallThreshold_165) {
  options_.thres_loss_function = 1e-10;
  auto loss_fn = options_.CreateLossFunction();
  EXPECT_NE(loss_fn, nullptr);
}

// Test CreateLossFunction with very large threshold
TEST_F(GlobalPositionerOptionsTest_165, CreateLossFunctionLargeThreshold_165) {
  options_.thres_loss_function = 1e10;
  auto loss_fn = options_.CreateLossFunction();
  EXPECT_NE(loss_fn, nullptr);
}

// Test copy semantics
TEST_F(GlobalPositionerOptionsTest_165, CopyConstruction_165) {
  options_.generate_random_positions = false;
  options_.seed = 99;
  options_.constraint_reweight_scale = 3.14;

  GlobalPositionerOptions copy(options_);
  EXPECT_EQ(copy.generate_random_positions, false);
  EXPECT_EQ(copy.seed, 99u);
  EXPECT_DOUBLE_EQ(copy.constraint_reweight_scale, 3.14);
}

TEST_F(GlobalPositionerOptionsTest_165, CopyAssignment_165) {
  options_.optimize_scales = false;
  options_.seed = 7;

  GlobalPositionerOptions other;
  other = options_;
  EXPECT_EQ(other.optimize_scales, false);
  EXPECT_EQ(other.seed, 7u);
}

// Test that it inherits from OptimizationBaseOptions
TEST_F(GlobalPositionerOptionsTest_165, InheritsFromOptimizationBaseOptions_165) {
  OptimizationBaseOptions* base_ptr = &options_;
  EXPECT_NE(base_ptr, nullptr);
  EXPECT_DOUBLE_EQ(base_ptr->thres_loss_function, 1e-1);
}

}  // namespace
}  // namespace glomap
