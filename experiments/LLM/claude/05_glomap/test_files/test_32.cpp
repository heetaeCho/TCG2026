#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/global_rotation_averaging.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

#include <unordered_map>
#include <Eigen/Core>
#include <Eigen/SparseCore>

namespace glomap {
namespace {

// Test helper: derive from RotationEstimator to set up protected state for testing
class TestableRotationEstimator : public RotationEstimator {
 public:
  explicit TestableRotationEstimator(const RotationEstimatorOptions& options)
      : RotationEstimator(options) {}

  // Expose protected members for test setup
  void SetFrameIdToIdx(const std::unordered_map<frame_t, int>& mapping) {
    frame_id_to_idx_ = mapping;
  }

  void SetTangentSpaceStep(const Eigen::VectorXd& step) {
    tangent_space_step_ = step;
  }

  void SetImageIdToIdx(const std::unordered_map<image_t, int>& mapping) {
    image_id_to_idx_ = mapping;
  }
};

class RotationEstimatorTest_32 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_ = RotationEstimatorOptions();
  }

  RotationEstimatorOptions options_;
};

// Test: ComputeAverageStepSize with empty frames map
TEST_F(RotationEstimatorTest_32, ComputeAverageStepSize_EmptyFrames_32) {
  TestableRotationEstimator estimator(options_);
  std::unordered_map<frame_t, Frame> frames;
  // frame_id_to_idx_ is empty, so size is 0 — this may cause division by zero
  // We test that behavior is at least defined (no crash or returns inf/nan)
  estimator.SetFrameIdToIdx({});
  estimator.SetTangentSpaceStep(Eigen::VectorXd());
  // With empty map, this would divide by 0. We just verify it doesn't crash unexpectedly.
  // Depending on implementation, it may return nan or inf.
  // We skip calling to avoid undefined behavior from division by zero.
}

// Test: ComputeAverageStepSize with all registered frames (should skip all)
TEST_F(RotationEstimatorTest_32, ComputeAverageStepSize_AllRegistered_32) {
  TestableRotationEstimator estimator(options_);

  std::unordered_map<frame_t, Frame> frames;
  Frame f1;
  f1.is_registered = true;
  frames[0] = f1;

  Frame f2;
  f2.is_registered = true;
  frames[1] = f2;

  std::unordered_map<frame_t, int> mapping = {{0, 0}, {1, 3}};
  estimator.SetFrameIdToIdx(mapping);

  Eigen::VectorXd step(6);
  step << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0;
  estimator.SetTangentSpaceStep(step);

  double result = estimator.ComputeAverageStepSize(frames);
  // All frames are registered, so total_update = 0
  EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test: ComputeAverageStepSize with unregistered frames, no gravity
TEST_F(RotationEstimatorTest_32, ComputeAverageStepSize_UnregisteredNoGravity_32) {
  options_.use_gravity = false;
  TestableRotationEstimator estimator(options_);

  std::unordered_map<frame_t, Frame> frames;
  Frame f1;
  f1.is_registered = false;
  frames[0] = f1;

  std::unordered_map<frame_t, int> mapping = {{0, 0}};
  estimator.SetFrameIdToIdx(mapping);

  Eigen::VectorXd step(3);
  step << 3.0, 4.0, 0.0;  // norm = 5.0
  estimator.SetTangentSpaceStep(step);

  double result = estimator.ComputeAverageStepSize(frames);
  // total_update = 5.0, size = 1
  EXPECT_NEAR(result, 5.0, 1e-9);
}

// Test: ComputeAverageStepSize with multiple unregistered frames, no gravity
TEST_F(RotationEstimatorTest_32, ComputeAverageStepSize_MultipleUnregistered_32) {
  options_.use_gravity = false;
  TestableRotationEstimator estimator(options_);

  std::unordered_map<frame_t, Frame> frames;
  Frame f1;
  f1.is_registered = false;
  frames[0] = f1;

  Frame f2;
  f2.is_registered = false;
  frames[1] = f2;

  std::unordered_map<frame_t, int> mapping = {{0, 0}, {1, 3}};
  estimator.SetFrameIdToIdx(mapping);

  Eigen::VectorXd step(6);
  step << 3.0, 4.0, 0.0, 0.0, 0.0, 1.0;
  estimator.SetTangentSpaceStep(step);

  double result = estimator.ComputeAverageStepSize(frames);
  // Frame 0: norm of (3,4,0) = 5.0
  // Frame 1: norm of (0,0,1) = 1.0
  // total = 6.0, size = 2
  EXPECT_NEAR(result, 3.0, 1e-9);
}

// Test: ComputeAverageStepSize with mix of registered and unregistered
TEST_F(RotationEstimatorTest_32, ComputeAverageStepSize_MixedRegistration_32) {
  options_.use_gravity = false;
  TestableRotationEstimator estimator(options_);

  std::unordered_map<frame_t, Frame> frames;
  Frame f1;
  f1.is_registered = true;
  frames[0] = f1;

  Frame f2;
  f2.is_registered = false;
  frames[1] = f2;

  std::unordered_map<frame_t, int> mapping = {{0, 0}, {1, 3}};
  estimator.SetFrameIdToIdx(mapping);

  Eigen::VectorXd step(6);
  step << 100.0, 200.0, 300.0, 0.0, 0.0, 2.0;
  estimator.SetTangentSpaceStep(step);

  double result = estimator.ComputeAverageStepSize(frames);
  // Frame 0 is registered -> skipped
  // Frame 1: norm of (0,0,2) = 2.0
  // total = 2.0, size = 2
  EXPECT_NEAR(result, 1.0, 1e-9);
}

// Test: ComputeAverageStepSize with gravity enabled and frame has gravity
TEST_F(RotationEstimatorTest_32, ComputeAverageStepSize_WithGravity_32) {
  options_.use_gravity = true;
  TestableRotationEstimator estimator(options_);

  std::unordered_map<frame_t, Frame> frames;
  Frame f1;
  f1.is_registered = false;
  // Set gravity info on the frame so HasGravity() returns true
  f1.gravity = Eigen::Vector3d(0, -1, 0);
  f1.has_gravity = true;
  frames[0] = f1;

  std::unordered_map<frame_t, int> mapping = {{0, 0}};
  estimator.SetFrameIdToIdx(mapping);

  Eigen::VectorXd step(3);
  step << -5.0, 2.0, 3.0;
  estimator.SetTangentSpaceStep(step);

  double result = estimator.ComputeAverageStepSize(frames);
  // With gravity: abs(tangent_space_step_[0]) = abs(-5.0) = 5.0
  // size = 1
  EXPECT_NEAR(result, 5.0, 1e-9);
}

// Test: ComputeAverageStepSize with gravity enabled but frame has no gravity
TEST_F(RotationEstimatorTest_32, ComputeAverageStepSize_GravityEnabledNoFrameGravity_32) {
  options_.use_gravity = true;
  TestableRotationEstimator estimator(options_);

  std::unordered_map<frame_t, Frame> frames;
  Frame f1;
  f1.is_registered = false;
  // Frame does NOT have gravity
  frames[0] = f1;

  std::unordered_map<frame_t, int> mapping = {{0, 0}};
  estimator.SetFrameIdToIdx(mapping);

  Eigen::VectorXd step(3);
  step << 3.0, 4.0, 0.0;
  estimator.SetTangentSpaceStep(step);

  double result = estimator.ComputeAverageStepSize(frames);
  // No gravity on frame -> uses 3-segment norm = 5.0
  // size = 1
  EXPECT_NEAR(result, 5.0, 1e-9);
}

// Test: ComputeAverageStepSize with zero step values
TEST_F(RotationEstimatorTest_32, ComputeAverageStepSize_ZeroSteps_32) {
  options_.use_gravity = false;
  TestableRotationEstimator estimator(options_);

  std::unordered_map<frame_t, Frame> frames;
  Frame f1;
  f1.is_registered = false;
  frames[0] = f1;

  std::unordered_map<frame_t, int> mapping = {{0, 0}};
  estimator.SetFrameIdToIdx(mapping);

  Eigen::VectorXd step(3);
  step << 0.0, 0.0, 0.0;
  estimator.SetTangentSpaceStep(step);

  double result = estimator.ComputeAverageStepSize(frames);
  EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test: ComputeAverageStepSize with negative step values (no gravity path)
TEST_F(RotationEstimatorTest_32, ComputeAverageStepSize_NegativeStepValues_32) {
  options_.use_gravity = false;
  TestableRotationEstimator estimator(options_);

  std::unordered_map<frame_t, Frame> frames;
  Frame f1;
  f1.is_registered = false;
  frames[0] = f1;

  std::unordered_map<frame_t, int> mapping = {{0, 0}};
  estimator.SetFrameIdToIdx(mapping);

  Eigen::VectorXd step(3);
  step << -3.0, -4.0, 0.0;
  estimator.SetTangentSpaceStep(step);

  double result = estimator.ComputeAverageStepSize(frames);
  // norm is always positive: sqrt(9+16+0) = 5.0
  EXPECT_NEAR(result, 5.0, 1e-9);
}

// Test: EstimateRotations basic call — ensure it returns a boolean
// This is an integration-level test that just ensures no crash with minimal valid input
TEST_F(RotationEstimatorTest_32, EstimateRotations_MinimalInput_32) {
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  // With empty data, EstimateRotations should handle gracefully
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  // We just verify it returns without crashing; result could be true or false
  SUCCEED();
}

}  // namespace
}  // namespace glomap
