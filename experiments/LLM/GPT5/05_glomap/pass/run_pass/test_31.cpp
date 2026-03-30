// File: global_rotation_averaging_compute_residuals_test_31.cc

#include <unordered_map>

#include <gtest/gtest.h>
#include <Eigen/Core>

#include "glomap/estimators/global_rotation_averaging.h"
#include "glomap/scene/view_graph.h"

namespace {

using glomap::RotationEstimator;
using glomap::RotationEstimatorOptions;
using glomap::ViewGraph;
using glomap::Image;
using glomap::image_t;

// Testable subclass to expose protected members / methods for testing only.
class TestableRotationEstimator : public RotationEstimator {
 public:
  explicit TestableRotationEstimator(const RotationEstimatorOptions& options)
      : RotationEstimator(options) {}

  // Expose the protected overload we want to test.
  using RotationEstimator::ComputeResiduals;

  // Helper setters to prepare internal state in a controlled way.
  void SetImageIdToIdx(const std::unordered_map<image_t, int>& map) {
    image_id_to_idx_ = map;
  }

  void SetRotationEstimated(const Eigen::VectorXd& vec) {
    rotation_estimated_ = vec;
  }

  void SetTangentSpaceResidual(const Eigen::VectorXd& vec) {
    tangent_space_residual_ = vec;
  }

  void SetFixedCamera(image_t id, const Eigen::Vector3d& rotation) {
    fixed_camera_id_ = id;
    fixed_camera_rotation_ = rotation;
  }

  // For verification in tests (observable effect).
  const Eigen::VectorXd& GetTangentSpaceResidual() const {
    return tangent_space_residual_;
  }

  // Ensure the loop over rel_temp_info_ does nothing.
  void ClearRelativeTempInfo() {
    rel_temp_info_.clear();
  }
};

class RotationEstimatorComputeResidualsTest_31 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_.use_gravity = false;  // default in tests unless overridden
  }

  RotationEstimatorOptions options_;
};

//------------------------------------------------------------------------------
// Test 1: When there are no relative pairs and the fixed-camera rotation and
// estimated rotation are both zero, the final fixed-camera residual (last 3
// entries) should become zero, irrespective of their previous values.
// This exercises the branch without gravity: the else-part of the final if.
//------------------------------------------------------------------------------

TEST_F(RotationEstimatorComputeResidualsTest_31,
       FixedCameraResidualWithoutGravity_AllZero_31) {
  options_.use_gravity = false;
  TestableRotationEstimator estimator(options_);

  // Choose a fixed camera id and map it to index 0 in the rotation vector.
  const image_t fixed_id = static_cast<image_t>(0);

  std::unordered_map<image_t, int> image_id_to_idx;
  image_id_to_idx[fixed_id] = 0;
  estimator.SetImageIdToIdx(image_id_to_idx);

  // rotation_estimated_[0..2] = 0 => identity rotation in angle-axis form.
  Eigen::VectorXd rotation_estimated(3);
  rotation_estimated.setZero();
  estimator.SetRotationEstimated(rotation_estimated);

  // Tangent-space residual initially non-zero to detect change.
  Eigen::VectorXd residual(3);
  residual << 1.0, 2.0, 3.0;
  estimator.SetTangentSpaceResidual(residual);

  // Fixed camera rotation is also zero => identity.
  Eigen::Vector3d fixed_rotation = Eigen::Vector3d::Zero();
  estimator.SetFixedCamera(fixed_id, fixed_rotation);

  // Ensure the loop over relative pairs does nothing.
  estimator.ClearRelativeTempInfo();

  // Empty view graph and images; we only care about the fixed-camera part.
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;

  estimator.ComputeResiduals(view_graph, images);

  const Eigen::VectorXd& result = estimator.GetTangentSpaceResidual();
  ASSERT_EQ(result.size(), residual.size());

  // With both rotations equal to identity (angle-axis = 0),
  // RotationToAngleAxis(AngleAxisToRotation(...)) should yield zero.
  EXPECT_DOUBLE_EQ(0.0, result[0]);
  EXPECT_DOUBLE_EQ(0.0, result[1]);
  EXPECT_DOUBLE_EQ(0.0, result[2]);
}

//------------------------------------------------------------------------------
// Test 2: Same setup as above, but with a larger residual vector to ensure
// that only the *last three entries* are modified for the fixed camera,
// while earlier entries remain unchanged.
//------------------------------------------------------------------------------

TEST_F(RotationEstimatorComputeResidualsTest_31,
       FixedCameraResidualWithoutGravity_ModifiesTailOnly_31) {
  options_.use_gravity = false;
  TestableRotationEstimator estimator(options_);

  const image_t fixed_id = static_cast<image_t>(1);

  std::unordered_map<image_t, int> image_id_to_idx;
  image_id_to_idx[fixed_id] = 0;  // first triplet in rotation_estimated_
  estimator.SetImageIdToIdx(image_id_to_idx);

  // zero angle-axis => identity rotation
  Eigen::VectorXd rotation_estimated(3);
  rotation_estimated.setZero();
  estimator.SetRotationEstimated(rotation_estimated);

  // Residual vector of size 5: first two should remain unchanged,
  // last three should be overwritten by the fixed-camera residual.
  Eigen::VectorXd residual(5);
  residual << 10.0, 20.0, 30.0, 40.0, 50.0;
  estimator.SetTangentSpaceResidual(residual);

  Eigen::Vector3d fixed_rotation = Eigen::Vector3d::Zero();
  estimator.SetFixedCamera(fixed_id, fixed_rotation);

  estimator.ClearRelativeTempInfo();

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;

  estimator.ComputeResiduals(view_graph, images);

  const Eigen::VectorXd& result = estimator.GetTangentSpaceResidual();
  ASSERT_EQ(result.size(), residual.size());

  // First part should be unchanged.
  EXPECT_DOUBLE_EQ(10.0, result[0]);
  EXPECT_DOUBLE_EQ(20.0, result[1]);

  // Last three entries: with zero rotations, expected to be zero.
  EXPECT_DOUBLE_EQ(0.0, result[2]);
  EXPECT_DOUBLE_EQ(0.0, result[3]);
  EXPECT_DOUBLE_EQ(0.0, result[4]);
}

}  // namespace
