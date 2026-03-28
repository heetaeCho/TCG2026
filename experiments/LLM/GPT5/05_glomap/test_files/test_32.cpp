#include <unordered_map>

#include <gtest/gtest.h>

#include "glomap/estimators/global_rotation_averaging.h"

namespace {

// Simple testable subclass to access protected members needed to drive the
// public ComputeAverageStepSize behavior without re-implementing it.
class TestableRotationEstimator_32 : public glomap::RotationEstimator {
 public:
  explicit TestableRotationEstimator_32(
      const glomap::RotationEstimatorOptions& options)
      : glomap::RotationEstimator(options) {}

  // Helpers to configure internal state in a controlled way for testing.
  void SetTangentSpaceStep_32(const Eigen::VectorXd& step) {
    tangent_space_step_ = step;
  }

  void SetFrameIndex_32(glomap::frame_t frame_id, int idx) {
    frame_id_to_idx_[frame_id] = idx;
  }

  // Expose size of the internal map so tests can double-check assumptions
  // without relying on undocumented behavior.
  size_t FrameIndexSize_32() const { return frame_id_to_idx_.size(); }
};

class RotationEstimatorComputeAverageStepSizeTest_32 : public ::testing::Test {
 protected:
  RotationEstimatorComputeAverageStepSizeTest_32()
      : options_(), estimator_(options_) {
    // Default: do not use gravity so behavior does not depend on Frame::HasGravity().
    options_.use_gravity = false;
  }

  glomap::RotationEstimatorOptions options_;
  TestableRotationEstimator_32 estimator_;
};

}  // namespace

// -----------------------------------------------------------------------------
// Normal operation: multiple frames, gravity disabled.
// Verifies that the result matches the average of the L2 norms of the
// corresponding 3-element segments in tangent_space_step_.
// -----------------------------------------------------------------------------
TEST_F(RotationEstimatorComputeAverageStepSizeTest_32,
       UsesL2NormOfThreeDimSegmentsWhenGravityDisabled_32) {
  using glomap::Frame;
  using glomap::frame_t;

  // Configure frames: two unregistered frames.
  std::unordered_map<frame_t, Frame> frames;
  const frame_t kFrameId0 = static_cast<frame_t>(0);
  const frame_t kFrameId1 = static_cast<frame_t>(1);

  frames.emplace(kFrameId0, Frame());
  frames.emplace(kFrameId1, Frame());

  // Mark both as not registered so they are included in the accumulation.
  frames.at(kFrameId0).is_registered = false;
  frames.at(kFrameId1).is_registered = false;

  // Map frame IDs to disjoint 3-element segments in the step vector.
  estimator_.SetFrameIndex_32(kFrameId0, 0);
  estimator_.SetFrameIndex_32(kFrameId1, 3);

  // tangent_space_step_ has 6 entries:
  //  - For kFrameId0: [3, 0, 4] -> norm = 5
  //  - For kFrameId1: [0, 0, 6] -> norm = 6
  Eigen::VectorXd step(6);
  step << 3.0, 0.0, 4.0, 0.0, 0.0, 6.0;
  estimator_.SetTangentSpaceStep_32(step);

  ASSERT_EQ(estimator_.FrameIndexSize_32(), 2u);

  const double result = estimator_.ComputeAverageStepSize(frames);

  const double expected_sum = 5.0 + 6.0;
  const double expected_avg = expected_sum / 2.0;

  EXPECT_DOUBLE_EQ(result, expected_avg);
}

// -----------------------------------------------------------------------------
// Boundary condition: no frames in the input map, but internal index map
// contains entries. The loop contributes nothing, so the total update is zero
// and the average should be zero (0 / |frame_id_to_idx_|).
// -----------------------------------------------------------------------------
TEST_F(RotationEstimatorComputeAverageStepSizeTest_32,
       EmptyFramesMapReturnsZero_32) {
  using glomap::frame_t;

  // No frames provided.
  std::unordered_map<frame_t, glomap::Frame> frames;

  // Still configure one frame index internally to avoid division by zero.
  const frame_t kFrameId = static_cast<frame_t>(0);
  estimator_.SetFrameIndex_32(kFrameId, 0);

  // Provide some non-zero step entries; they should not be used because
  // there are no frames to iterate over.
  Eigen::VectorXd step(3);
  step << 10.0, 20.0, 30.0;
  estimator_.SetTangentSpaceStep_32(step);

  ASSERT_EQ(estimator_.FrameIndexSize_32(), 1u);

  const double result = estimator_.ComputeAverageStepSize(frames);

  // No frames -> no accumulation -> total_update == 0.
  // Denominator is 1, so average should be 0.
  EXPECT_DOUBLE_EQ(result, 0.0);
}

// -----------------------------------------------------------------------------
// Exceptional/edge behavior: registered frames should be skipped when computing
// the average step size.
// We construct two frames but mark one as registered; only the unregistered
// frame's step should contribute to the accumulated update.
// -----------------------------------------------------------------------------
TEST_F(RotationEstimatorComputeAverageStepSizeTest_32,
       RegisteredFramesAreSkippedInAverage_32) {
  using glomap::Frame;
  using glomap::frame_t;

  std::unordered_map<frame_t, Frame> frames;
  const frame_t kFrameId0 = static_cast<frame_t>(0);
  const frame_t kFrameId1 = static_cast<frame_t>(1);

  frames.emplace(kFrameId0, Frame());
  frames.emplace(kFrameId1, Frame());

  // Frame 0 is registered and should be ignored.
  frames.at(kFrameId0).is_registered = true;
  // Frame 1 is unregistered and should be included.
  frames.at(kFrameId1).is_registered = false;

  estimator_.SetFrameIndex_32(kFrameId0, 0);
  estimator_.SetFrameIndex_32(kFrameId1, 3);

  // tangent_space_step_:
  //  - Registered frame (id 0): [100, 0, 0]  -> norm = 100 (should be ignored)
  //  - Unregistered frame (id 1): [0, 0, 1] -> norm = 1   (should be used)
  Eigen::VectorXd step(6);
  step << 100.0, 0.0, 0.0, 0.0, 0.0, 1.0;
  estimator_.SetTangentSpaceStep_32(step);

  ASSERT_EQ(estimator_.FrameIndexSize_32(), 2u);

  const double result = estimator_.ComputeAverageStepSize(frames);

  const double expected_sum = 1.0;       // only from unregistered frame
  const double expected_avg = expected_sum / 2.0;  // divided by map size (2)

  EXPECT_DOUBLE_EQ(result, expected_avg);
}
