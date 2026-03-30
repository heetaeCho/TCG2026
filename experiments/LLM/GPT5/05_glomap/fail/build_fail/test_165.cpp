// File: global_positioner_options_test_165.cc

#include <gtest/gtest.h>

#include "glomap/estimators/global_positioning.h"

namespace {

using glomap::GlobalPositionerOptions;

class GlobalPositionerOptionsTest_165 : public ::testing::Test {
 protected:
  GlobalPositionerOptions options_;
};

// Verifies that the default constructor initializes base and derived fields
// according to the in-class defaults / constructor body.
TEST_F(GlobalPositionerOptionsTest_165, DefaultConstructionInitialValues_165) {
  // From OptimizationBaseOptions / constructor override
  // (partial code shows thres_loss_function = 1e-1)
  EXPECT_DOUBLE_EQ(0.1, options_.thres_loss_function);

  // In-class defaults in GlobalPositionerOptions
  EXPECT_TRUE(options_.generate_random_positions);
  EXPECT_TRUE(options_.generate_random_points);
  EXPECT_TRUE(options_.generate_scales);
  EXPECT_TRUE(options_.optimize_positions);
  EXPECT_TRUE(options_.optimize_scales);

  EXPECT_EQ(1u, options_.seed);

  // Constraint type default (enum lives in production header).
  EXPECT_EQ(glomap::ONLY_POINTS, options_.constraint_type);

  EXPECT_DOUBLE_EQ(1.0, options_.constraint_reweight_scale);
}

// Verifies that GlobalPositionerOptions behaves like a regular options struct:
// we can modify fields and the values persist as expected.
TEST_F(GlobalPositionerOptionsTest_165, FieldMutationPersistsValues_165) {
  options_.generate_random_positions = false;
  options_.generate_random_points = false;
  options_.generate_scales = false;
  options_.optimize_positions = false;
  options_.optimize_scales = false;

  options_.seed = 42u;
  options_.constraint_reweight_scale = 3.5;

  // We cannot assume any particular meaning of non-default constraint types,
  // but we can at least assign back the existing one.
  options_.constraint_type = glomap::ONLY_POINTS;

  EXPECT_FALSE(options_.generate_random_positions);
  EXPECT_FALSE(options_.generate_random_points);
  EXPECT_FALSE(options_.generate_scales);
  EXPECT_FALSE(options_.optimize_positions);
  EXPECT_FALSE(options_.optimize_scales);

  EXPECT_EQ(42u, options_.seed);
  EXPECT_DOUBLE_EQ(3.5, options_.constraint_reweight_scale);
  EXPECT_EQ(glomap::ONLY_POINTS, options_.constraint_type);
}

// Verifies that CreateLossFunction returns a non-null shared_ptr, which is the
// most natural observable contract for a factory-style function.
TEST_F(GlobalPositionerOptionsTest_165, CreateLossFunctionReturnsNonNull_165) {
  auto loss_fn = options_.CreateLossFunction();
  EXPECT_TRUE(static_cast<bool>(loss_fn));
}

// Verifies that CreateLossFunction can be called multiple times and each call
// yields a non-null pointer (no guarantees about identity or sharing).
TEST_F(GlobalPositionerOptionsTest_165, CreateLossFunctionMultipleCallsNonNull_165) {
  auto loss_fn1 = options_.CreateLossFunction();
  auto loss_fn2 = options_.CreateLossFunction();

  EXPECT_TRUE(static_cast<bool>(loss_fn1));
  EXPECT_TRUE(static_cast<bool>(loss_fn2));
}

}  // namespace
