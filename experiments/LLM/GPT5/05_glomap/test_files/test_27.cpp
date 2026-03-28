// File: rotation_estimator_initialize_from_mst_test_27.cc

#include <unordered_map>

#include <gtest/gtest.h>

#include "glomap/estimators/global_rotation_averaging.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image_pair.h"

// If these headers exist in the project, they will provide Rig / Frame / Image.
// They are not strictly required by the prompt, but are typical in this codebase.
#include "glomap/scene/rig.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/image.h"

namespace glomap {

// Small helper subclass to expose InitializeFromMaximumSpanningTree in case it
// is declared protected in the header (the partial .cc shows it as public).
class TestableRotationEstimator_27 : public RotationEstimator {
 public:
  explicit TestableRotationEstimator_27(const RotationEstimatorOptions& options)
      : RotationEstimator(options) {}

  using RotationEstimator::InitializeFromMaximumSpanningTree;
};

class RotationEstimatorInitializeFromMSTTest_27 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Rely on default / aggregate initialization of options.
    RotationEstimatorOptions options{};
    estimator_ = std::make_unique<TestableRotationEstimator_27>(options);
  }

  std::unique_ptr<TestableRotationEstimator_27> estimator_;
};

// ---------------------------------------------------------------------------
// Test 1: Basic smoke test with completely empty inputs.
// Verifies that the method can be invoked and does not throw exceptions.
// ---------------------------------------------------------------------------
TEST_F(RotationEstimatorInitializeFromMSTTest_27,
       InitializeWithEmptyContainersDoesNotThrow_27) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  EXPECT_NO_THROW({
    estimator_->InitializeFromMaximumSpanningTree(
        view_graph, rigs, frames, images);
  });
}

// ---------------------------------------------------------------------------
// Test 2: Graph with two registered images and a single image pair.
//
// This sets up a minimal but non-trivial view graph. The goal is not to
// validate the internal rotation math, but to ensure that, given a typical
// input resembling real usage, the method runs without throwing and can be
// called successfully.
// ---------------------------------------------------------------------------
TEST_F(RotationEstimatorInitializeFromMSTTest_27,
       InitializeWithSimpleViewGraphDoesNotThrow_27) {
  ViewGraph view_graph;

  // Two images connected by a single pair.
  const image_t kImageId1 = 1;
  const image_t kImageId2 = 2;

  // Populate image_pairs with a simple relative pose.
  // We rely only on the public ImagePair constructor.
  Rigid3d relative_pose;  // Default constructed.
  ImagePair image_pair(kImageId1, kImageId2, relative_pose);
  const image_pair_t pair_id =
      colmap::ImagePairToPairId(kImageId1, kImageId2);

  view_graph.image_pairs.emplace(pair_id, image_pair);

  // Set up images map with both images marked as registered.
  std::unordered_map<image_t, Image> images;
  {
    Image img1;
    Image img2;

    // We only use the public interface; COLMAP-style Image typically exposes
    // IsRegistered / SetRegistered.
    img1.SetRegistered(true);
    img2.SetRegistered(true);

    images.emplace(kImageId1, img1);
    images.emplace(kImageId2, img2);
  }

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  EXPECT_NO_THROW({
    estimator_->InitializeFromMaximumSpanningTree(
        view_graph, rigs, frames, images);
  });
}

// ---------------------------------------------------------------------------
// Test 3: Multiple calls to InitializeFromMaximumSpanningTree on the same
// data to ensure the method can be safely invoked repeatedly without
// throwing or requiring special one-shot semantics.
// ---------------------------------------------------------------------------
TEST_F(RotationEstimatorInitializeFromMSTTest_27,
       MultipleInitializationCallsAreSafe_27) {
  ViewGraph view_graph;

  const image_t kImageId1 = 3;
  const image_t kImageId2 = 4;

  Rigid3d relative_pose;
  ImagePair image_pair(kImageId1, kImageId2, relative_pose);
  const image_pair_t pair_id =
      colmap::ImagePairToPairId(kImageId1, kImageId2);

  view_graph.image_pairs.emplace(pair_id, image_pair);

  std::unordered_map<image_t, Image> images;
  {
    Image img1;
    Image img2;

    img1.SetRegistered(true);
    img2.SetRegistered(true);

    images.emplace(kImageId1, img1);
    images.emplace(kImageId2, img2);
  }

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  EXPECT_NO_THROW({
    estimator_->InitializeFromMaximumSpanningTree(
        view_graph, rigs, frames, images);
  });

  // Call a second time with the same data to check idempotent / repeat behavior.
  EXPECT_NO_THROW({
    estimator_->InitializeFromMaximumSpanningTree(
        view_graph, rigs, frames, images);
  });
}

}  // namespace glomap
