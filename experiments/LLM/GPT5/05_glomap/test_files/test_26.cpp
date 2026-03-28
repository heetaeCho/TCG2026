#include <gtest/gtest.h>

#include "glomap/estimators/global_rotation_averaging.h"
#include "glomap/scene/view_graph.h"

namespace {

// Bring commonly used types into scope for readability.
using glomap::RotationEstimator;
using glomap::RotationEstimatorOptions;
using glomap::ViewGraph;
using glomap::Rig;
using glomap::Frame;
using glomap::Image;
using glomap::rig_t;
using glomap::frame_t;
using glomap::image_t;

// Test fixture holding options whose lifetime outlives the estimator
class RotationEstimatorTest_26 : public ::testing::Test {
 protected:
  RotationEstimatorOptions options_;
};

//
// Normal / boundary case:
// - No gravity
// - Initialization skipped
// - L1 and IRLS iterations disabled
// - Empty ViewGraph and containers
// Expectation: orchestration finishes and returns true, without modifying inputs.
//

TEST_F(RotationEstimatorTest_26,
       EstimateRotations_DefaultOptionsEmptyInputs_ReturnsTrue_26) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  options_.use_gravity = false;
  options_.skip_initialization = true;
  options_.max_num_l1_iterations = 0;
  options_.max_num_irls_iterations = 0;

  RotationEstimator estimator(options_);

  const bool result =
      estimator.EstimateRotations(view_graph, rigs, frames, images);

  EXPECT_TRUE(result);
  EXPECT_TRUE(rigs.empty());
  EXPECT_TRUE(frames.empty());
  EXPECT_TRUE(images.empty());
}

//
// Boundary condition around the gravity flag:
// - Gravity enabled
// - Empty rigs map (so gravity loop has no iterations)
// - Initialization skipped (because we explicitly set it so)
// - L1 and IRLS disabled
// Expectation: no error is triggered by gravity handling and the function
//              successfully returns true on empty data.
//

TEST_F(RotationEstimatorTest_26,
       EstimateRotations_UseGravityWithEmptyRigs_Succeeds_26) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;    // empty
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  options_.use_gravity = true;
  options_.skip_initialization = true;
  options_.max_num_l1_iterations = 0;
  options_.max_num_irls_iterations = 0;

  RotationEstimator estimator(options_);

  const bool result =
      estimator.EstimateRotations(view_graph, rigs, frames, images);

  EXPECT_TRUE(result);
  EXPECT_TRUE(rigs.empty());
  EXPECT_TRUE(frames.empty());
  EXPECT_TRUE(images.empty());
}

//
// Behavioral / robustness case:
// - Same estimator instance used multiple times with the same inputs
// - No gravity, initialization skipped, solvers disabled
// Expectation: calling EstimateRotations repeatedly is stable and
//              returns consistent results.
//

TEST_F(RotationEstimatorTest_26,
       EstimateRotations_RepeatedCallsReturnConsistentResult_26) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  options_.use_gravity = false;
  options_.skip_initialization = true;
  options_.max_num_l1_iterations = 0;
  options_.max_num_irls_iterations = 0;

  RotationEstimator estimator(options_);

  const bool first_result =
      estimator.EstimateRotations(view_graph, rigs, frames, images);
  const bool second_result =
      estimator.EstimateRotations(view_graph, rigs, frames, images);

  EXPECT_EQ(first_result, second_result);
}

}  // namespace
