#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

#include <unordered_map>

namespace glomap {
namespace {

class GlobalPositionerTest_110 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_.optimize_positions = true;
    options_.optimize_points = true;
    options_.optimize_scales = true;
    options_.generate_random_positions = true;
    options_.generate_random_points = true;
    options_.generate_scales = true;
    options_.seed = 42;
    options_.constraint_type = ONLY_POINTS;
  }

  GlobalPositionerOptions options_;
};

// Test that GlobalPositioner can be constructed with default options
TEST_F(GlobalPositionerTest_110, ConstructWithDefaultOptions_110) {
  GlobalPositionerOptions default_options;
  EXPECT_NO_THROW(GlobalPositioner positioner(default_options));
}

// Test that GlobalPositioner can be constructed with custom options
TEST_F(GlobalPositionerTest_110, ConstructWithCustomOptions_110) {
  EXPECT_NO_THROW(GlobalPositioner positioner(options_));
}

// Test GetOptions returns modifiable reference
TEST_F(GlobalPositionerTest_110, GetOptionsReturnsReference_110) {
  GlobalPositioner positioner(options_);
  GlobalPositionerOptions& opts = positioner.GetOptions();
  EXPECT_EQ(opts.optimize_positions, true);
  EXPECT_EQ(opts.optimize_points, true);
  EXPECT_EQ(opts.optimize_scales, true);
  EXPECT_EQ(opts.seed, 42u);
}

// Test modifying options through GetOptions
TEST_F(GlobalPositionerTest_110, ModifyOptionsViaGetOptions_110) {
  GlobalPositioner positioner(options_);
  GlobalPositionerOptions& opts = positioner.GetOptions();
  opts.optimize_positions = false;
  EXPECT_EQ(positioner.GetOptions().optimize_positions, false);
}

// Test Solve with empty inputs
TEST_F(GlobalPositionerTest_110, SolveWithEmptyInputs_110) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // With empty data, Solve should handle gracefully (may return false)
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  // We just verify it doesn't crash; result may be true or false depending on implementation
  (void)result;
}

// Test default option values
TEST_F(GlobalPositionerTest_110, DefaultOptionValues_110) {
  GlobalPositionerOptions default_opts;
  EXPECT_TRUE(default_opts.generate_random_positions);
  EXPECT_TRUE(default_opts.generate_random_points);
  EXPECT_TRUE(default_opts.generate_scales);
  EXPECT_TRUE(default_opts.optimize_positions);
  EXPECT_TRUE(default_opts.optimize_scales);
  EXPECT_EQ(default_opts.seed, 1u);
  EXPECT_EQ(default_opts.constraint_type, ONLY_POINTS);
  EXPECT_DOUBLE_EQ(default_opts.constraint_reweight_scale, 1.0);
}

// Test CreateLossFunction returns valid pointer
TEST_F(GlobalPositionerTest_110, CreateLossFunctionReturnsValid_110) {
  GlobalPositionerOptions opts;
  auto loss = opts.CreateLossFunction();
  // The loss function should be non-null (or null for trivial loss)
  // We can't check internals, just that it doesn't crash
}

// Test options with optimization disabled
TEST_F(GlobalPositionerTest_110, OptionsOptimizePositionsDisabled_110) {
  options_.optimize_positions = false;
  GlobalPositioner positioner(options_);
  EXPECT_FALSE(positioner.GetOptions().optimize_positions);
}

// Test options with scales optimization disabled
TEST_F(GlobalPositionerTest_110, OptionsOptimizeScalesDisabled_110) {
  options_.optimize_scales = false;
  GlobalPositioner positioner(options_);
  EXPECT_FALSE(positioner.GetOptions().optimize_scales);
}

// Test options with different constraint types
TEST_F(GlobalPositionerTest_110, OptionsConstraintType_110) {
  options_.constraint_type = ONLY_CAMERAS;
  GlobalPositioner positioner(options_);
  EXPECT_EQ(positioner.GetOptions().constraint_type, ONLY_CAMERAS);
}

// Test options threshold loss function default value
TEST_F(GlobalPositionerTest_110, DefaultThresholdLossFunction_110) {
  GlobalPositionerOptions default_opts;
  EXPECT_NEAR(default_opts.thres_loss_function, 0.1, 1e-10);
}

// Test constraint_reweight_scale option
TEST_F(GlobalPositionerTest_110, ConstraintReweightScale_110) {
  options_.constraint_reweight_scale = 2.5;
  GlobalPositioner positioner(options_);
  EXPECT_DOUBLE_EQ(positioner.GetOptions().constraint_reweight_scale, 2.5);
}

// Test different seeds produce consistent construction
TEST_F(GlobalPositionerTest_110, DifferentSeeds_110) {
  options_.seed = 100;
  EXPECT_NO_THROW(GlobalPositioner positioner1(options_));
  
  options_.seed = 200;
  EXPECT_NO_THROW(GlobalPositioner positioner2(options_));
}

// Test GPU option defaults
TEST_F(GlobalPositionerTest_110, GPUOptionDefault_110) {
  GlobalPositionerOptions opts;
  // use_gpu might default to false
  GlobalPositioner positioner(opts);
  // Just verify construction doesn't crash
}

// Test all optimizations disabled
TEST_F(GlobalPositionerTest_110, AllOptimizationsDisabled_110) {
  options_.optimize_positions = false;
  options_.optimize_scales = false;
  options_.optimize_points = false;
  GlobalPositioner positioner(options_);
  
  EXPECT_FALSE(positioner.GetOptions().optimize_positions);
  EXPECT_FALSE(positioner.GetOptions().optimize_scales);
  EXPECT_FALSE(positioner.GetOptions().optimize_points);
}

// Test generation flags
TEST_F(GlobalPositionerTest_110, GenerationFlagsDisabled_110) {
  options_.generate_random_positions = false;
  options_.generate_random_points = false;
  options_.generate_scales = false;
  
  GlobalPositioner positioner(options_);
  auto& opts = positioner.GetOptions();
  EXPECT_FALSE(opts.generate_random_positions);
  EXPECT_FALSE(opts.generate_random_points);
  EXPECT_FALSE(opts.generate_scales);
}

}  // namespace
}  // namespace glomap
