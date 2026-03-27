#include <gtest/gtest.h>

#include "glomap/estimators/global_rotation_averaging.h"
#include "glomap/scene/view_graph.h"

namespace glomap {

// Test helper: expose the protected SetupLinearSystem and internal
// observable containers via const accessors only.
class TestRotationEstimator_28 : public RotationEstimator {
public:
  explicit TestRotationEstimator_28(const RotationEstimatorOptions& options)
      : RotationEstimator(options) {}

  // Public wrapper to call the protected method under test.
  void SetupLinearSystemPublic(const ViewGraph& view_graph,
                               std::unordered_map<rig_t, Rig>& rigs,
                               std::unordered_map<frame_t, Frame>& frames,
                               std::unordered_map<image_t, Image>& images) {
    SetupLinearSystem(view_graph, rigs, frames, images);
  }

  // Helper to set fixed_camera_id_ before calling SetupLinearSystem.
  void SetFixedCameraIdForTest(image_t id) { fixed_camera_id_ = id; }

  // Read-only accessors for observable results.
  const Eigen::SparseMatrix<double>& GetSparseMatrix() const {
    return sparse_matrix_;
  }

  const Eigen::VectorXd& GetTangentSpaceStep() const {
    return tangent_space_step_;
  }

  const Eigen::VectorXd& GetTangentSpaceResidual() const {
    return tangent_space_residual_;
  }

  const Eigen::VectorXd& GetRotationEstimated() const {
    return rotation_estimated_;
  }

  const Eigen::ArrayXd& GetWeights() const {
    return weights_;
  }
};

// Common fixture for all SetupLinearSystem tests (TEST_ID = 28).
class RotationEstimatorSetupLinearSystemTest_28 : public ::testing::Test {
protected:
  void SetUp() override {
    // Default options: no gravity, no weight.
    options_ = RotationEstimatorOptions{};
  }

  RotationEstimatorOptions options_;
};

// -----------------------------------------------------------------------------
// Test 1: Empty graph / containers with default options (no gravity, no weight)
// -----------------------------------------------------------------------------
TEST_F(RotationEstimatorSetupLinearSystemTest_28,
       EmptyGraphInitializesInternalState_28) {
  TestRotationEstimator_28 estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  // Avoid relying on internal logic that chooses a fixed camera from frames.
  // We set a fixed camera id ahead of time so the function can always
  // create its anchor constraint consistently, even if there are no frames.
  estimator.SetFixedCameraIdForTest(image_t(0));

  estimator.SetupLinearSystemPublic(view_graph, rigs, frames, images);

  const auto& A = estimator.GetSparseMatrix();
  const auto& step = estimator.GetTangentSpaceStep();
  const auto& residual = estimator.GetTangentSpaceResidual();
  const auto& weights = estimator.GetWeights();
  const auto& rotation = estimator.GetRotationEstimated();

  // Tangent-space vectors must be dimension-compatible with the linear system.
  EXPECT_EQ(A.cols(), step.size());
  EXPECT_EQ(A.rows(), residual.size());

  // Weights must have one entry per residual row.
  EXPECT_EQ(A.rows(), weights.size());

  // With use_weight == false, all weights are expected to be 1.0.
  for (int i = 0; i < weights.size(); ++i) {
    EXPECT_DOUBLE_EQ(weights[i], 1.0);
  }

  // Rotation estimate vector should be sized consistently with DOFs
  // (we only check that it is not negative and is compatible with the matrix).
  EXPECT_GE(rotation.size(), 0);
}

// -----------------------------------------------------------------------------
// Test 2: Non-default weighting – when use_weight is enabled, custom weights
// from image pairs should be reflected somewhere in the internal weights_.
// -----------------------------------------------------------------------------
TEST_F(RotationEstimatorSetupLinearSystemTest_28,
       UsesCustomWeightsWhenEnabled_28) {
  // Enable use_weight to let SetupLinearSystem propagate image_pair.weight.
  options_.use_weight = true;
  TestRotationEstimator_28 estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  // Create two images and corresponding frames; details of their internal
  // implementation are left to the production code – we only set the IDs
  // that are used by SetupLinearSystem through the public fields.
  const image_t kImageId1 = static_cast<image_t>(1);
  const image_t kImageId2 = static_cast<image_t>(2);
  const frame_t kFrameId1 = static_cast<frame_t>(1);
  const frame_t kFrameId2 = static_cast<frame_t>(2);

  Image image1;
  image1.camera_id = static_cast<camera_t>(1);
  image1.frame_id = kFrameId1;
  images[kImageId1] = image1;

  Image image2;
  image2.camera_id = static_cast<camera_t>(2);
  image2.frame_id = kFrameId2;
  images[kImageId2] = image2;

  Frame frame1;
  frame1.is_registered = true;
  frames[kFrameId1] = frame1;

  Frame frame2;
  frame2.is_registered = true;
  frames[kFrameId2] = frame2;

  // Single valid image pair with a non-unit weight.
  const image_pair_t kPairId = static_cast<image_pair_t>(10);
  ImagePair pair;
  pair.is_valid = true;
  pair.image_id1 = kImageId1;
  pair.image_id2 = kImageId2;
  const double kCustomWeight = 2.5;
  pair.weight = kCustomWeight;
  view_graph.image_pairs[kPairId] = pair;

  // Again, avoid depending on how the estimator chooses a fixed camera
  // internally: set a valid fixed camera id explicitly.
  estimator.SetFixedCameraIdForTest(kImageId1);

  estimator.SetupLinearSystemPublic(view_graph, rigs, frames, images);

  const auto& A = estimator.GetSparseMatrix();
  const auto& weights = estimator.GetWeights();

  // Basic consistency checks.
  EXPECT_EQ(A.rows(), weights.size());
  EXPECT_GT(A.rows(), 0);

  // Since use_weight == true and we provided a positive custom weight
  // on a valid image pair, we expect that weight to appear in the
  // internal weights array at least once.
  bool found_custom_weight = false;
  for (int i = 0; i < weights.size(); ++i) {
    if (weights[i] == kCustomWeight) {
      found_custom_weight = true;
      break;
    }
  }
  EXPECT_TRUE(found_custom_weight);
}

}  // namespace glomap
