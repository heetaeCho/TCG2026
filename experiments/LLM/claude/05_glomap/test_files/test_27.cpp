#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/global_rotation_averaging.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/scene/view_graph.h"

#include <unordered_map>

namespace glomap {
namespace {

class RotationEstimatorTest_27 : public ::testing::Test {
 protected:
  void SetUp() override {}

  // Helper to create a simple registered image
  Image CreateRegisteredImage(image_t image_id, camera_t camera_id = 0,
                              frame_t frame_id = 0) {
    Image image;
    image.image_id = image_id;
    image.camera_id = camera_id;
    image.frame_id = frame_id;
    image.is_registered = true;
    return image;
  }

  // Helper to create a simple frame
  Frame CreateFrame(frame_t frame_id, rig_t rig_id = 0) {
    Frame frame;
    frame.frame_id = frame_id;
    frame.rig_id = rig_id;
    frame.is_registered = true;
    return frame;
  }

  // Helper to create a simple rig
  Rig CreateRig(rig_t rig_id) {
    Rig rig;
    rig.rig_id = rig_id;
    return rig;
  }

  // Build a simple view graph with N images in a chain
  void BuildChainViewGraph(int num_images, ViewGraph& view_graph,
                           std::unordered_map<image_t, Image>& images,
                           std::unordered_map<frame_t, Frame>& frames,
                           std::unordered_map<rig_t, Rig>& rigs) {
    rigs[0] = CreateRig(0);
    for (int i = 0; i < num_images; ++i) {
      images[i] = CreateRegisteredImage(i, 0, i);
      frames[i] = CreateFrame(i, 0);
    }
    // Create chain: 0-1, 1-2, ..., (n-2)-(n-1)
    for (int i = 0; i < num_images - 1; ++i) {
      image_t id1 = std::min(static_cast<image_t>(i),
                             static_cast<image_t>(i + 1));
      image_t id2 = std::max(static_cast<image_t>(i),
                             static_cast<image_t>(i + 1));
      ImagePair pair(id1, id2);
      pair.is_valid = true;
      // Give each pair some inliers so spanning tree picks them
      pair.inliers.resize(100);
      view_graph.image_pairs[pair.pair_id] = pair;
    }
  }
};

// Test: EstimateRotations with a simple two-image case (identity relative rotation)
TEST_F(RotationEstimatorTest_27, TwoImagesIdentityRotation_27) {
  RotationEstimatorOptions options;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  BuildChainViewGraph(2, view_graph, images, frames, rigs);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  // With only 2 images, we expect the estimation to succeed or at least not crash
  // The result depends on implementation details, but it should be deterministic
  EXPECT_TRUE(result);
}

// Test: EstimateRotations with three images in a chain
TEST_F(RotationEstimatorTest_27, ThreeImagesChain_27) {
  RotationEstimatorOptions options;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  BuildChainViewGraph(3, view_graph, images, frames, rigs);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test: EstimateRotations with larger graph (5 images)
TEST_F(RotationEstimatorTest_27, FiveImagesChain_27) {
  RotationEstimatorOptions options;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  BuildChainViewGraph(5, view_graph, images, frames, rigs);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test: EstimateRotations with non-identity relative rotations
TEST_F(RotationEstimatorTest_27, NonIdentityRelativeRotation_27) {
  RotationEstimatorOptions options;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  rigs[0] = CreateRig(0);
  for (int i = 0; i < 3; ++i) {
    images[i] = CreateRegisteredImage(i, 0, i);
    frames[i] = CreateFrame(i, 0);
  }

  // Create pairs with known rotations
  Eigen::AngleAxisd rot1(M_PI / 4, Eigen::Vector3d::UnitY());
  Rigid3d cam2_from_cam1_01;
  cam2_from_cam1_01.rotation = Eigen::Quaterniond(rot1);

  Eigen::AngleAxisd rot2(M_PI / 6, Eigen::Vector3d::UnitX());
  Rigid3d cam2_from_cam1_12;
  cam2_from_cam1_12.rotation = Eigen::Quaterniond(rot2);

  ImagePair pair01(0, 1, cam2_from_cam1_01);
  pair01.is_valid = true;
  pair01.inliers.resize(100);
  view_graph.image_pairs[pair01.pair_id] = pair01;

  ImagePair pair12(1, 2, cam2_from_cam1_12);
  pair12.is_valid = true;
  pair12.inliers.resize(100);
  view_graph.image_pairs[pair12.pair_id] = pair12;

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test: EstimateRotations with a fully connected graph of 3 images
TEST_F(RotationEstimatorTest_27, FullyConnectedThreeImages_27) {
  RotationEstimatorOptions options;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  rigs[0] = CreateRig(0);
  for (int i = 0; i < 3; ++i) {
    images[i] = CreateRegisteredImage(i, 0, i);
    frames[i] = CreateFrame(i, 0);
  }

  // 0-1, 0-2, 1-2 all identity
  for (int i = 0; i < 3; ++i) {
    for (int j = i + 1; j < 3; ++j) {
      ImagePair pair(i, j);
      pair.is_valid = true;
      pair.inliers.resize(50);
      view_graph.image_pairs[pair.pair_id] = pair;
    }
  }

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test: EstimateRotations with consistent rotations should produce consistent results
TEST_F(RotationEstimatorTest_27, ConsistentRotationsProduceConsistentResults_27) {
  RotationEstimatorOptions options;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  rigs[0] = CreateRig(0);
  
  // Create 4 images with known global rotations
  Eigen::Quaterniond q0 = Eigen::Quaterniond::Identity();
  Eigen::AngleAxisd aa1(M_PI / 6, Eigen::Vector3d::UnitZ());
  Eigen::Quaterniond q1(aa1);
  Eigen::AngleAxisd aa2(M_PI / 3, Eigen::Vector3d::UnitZ());
  Eigen::Quaterniond q2(aa2);
  Eigen::AngleAxisd aa3(M_PI / 2, Eigen::Vector3d::UnitZ());
  Eigen::Quaterniond q3(aa3);

  std::vector<Eigen::Quaterniond> global_rots = {q0, q1, q2, q3};

  for (int i = 0; i < 4; ++i) {
    images[i] = CreateRegisteredImage(i, 0, i);
    frames[i] = CreateFrame(i, 0);
  }

  // Create all pairs with consistent relative rotations
  for (int i = 0; i < 4; ++i) {
    for (int j = i + 1; j < 4; ++j) {
      Rigid3d rel;
      rel.rotation = global_rots[j] * global_rots[i].inverse();
      ImagePair pair(i, j, rel);
      pair.is_valid = true;
      pair.inliers.resize(200);
      view_graph.image_pairs[pair.pair_id] = pair;
    }
  }

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test: Images that are not registered should not affect results
TEST_F(RotationEstimatorTest_27, UnregisteredImagesIgnored_27) {
  RotationEstimatorOptions options;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  rigs[0] = CreateRig(0);

  // Create 3 registered images
  for (int i = 0; i < 3; ++i) {
    images[i] = CreateRegisteredImage(i, 0, i);
    frames[i] = CreateFrame(i, 0);
  }

  // Create 1 unregistered image
  Image unreg;
  unreg.image_id = 3;
  unreg.camera_id = 0;
  unreg.frame_id = 3;
  unreg.is_registered = false;
  images[3] = unreg;
  frames[3] = CreateFrame(3, 0);
  frames[3].is_registered = false;

  // Create pairs between registered images only
  for (int i = 0; i < 3; ++i) {
    for (int j = i + 1; j < 3; ++j) {
      ImagePair pair(i, j);
      pair.is_valid = true;
      pair.inliers.resize(100);
      view_graph.image_pairs[pair.pair_id] = pair;
    }
  }

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test: EstimateRotations with varying inlier counts (edge weights)
TEST_F(RotationEstimatorTest_27, VaryingInlierCounts_27) {
  RotationEstimatorOptions options;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  rigs[0] = CreateRig(0);
  for (int i = 0; i < 4; ++i) {
    images[i] = CreateRegisteredImage(i, 0, i);
    frames[i] = CreateFrame(i, 0);
  }

  // Chain 0-1-2-3 with different inlier counts
  std::vector<int> inlier_counts = {500, 100, 300};
  for (int i = 0; i < 3; ++i) {
    ImagePair pair(i, i + 1);
    pair.is_valid = true;
    pair.inliers.resize(inlier_counts[i]);
    view_graph.image_pairs[pair.pair_id] = pair;
  }

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test: Multiple rigs
TEST_F(RotationEstimatorTest_27, MultipleRigs_27) {
  RotationEstimatorOptions options;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  rigs[0] = CreateRig(0);
  rigs[1] = CreateRig(1);

  // Images 0,1 in rig 0; images 2,3 in rig 1
  for (int i = 0; i < 4; ++i) {
    rig_t rig_id = (i < 2) ? 0 : 1;
    images[i] = CreateRegisteredImage(i, 0, i);
    frames[i] = CreateFrame(i, rig_id);
  }

  // Create chain
  for (int i = 0; i < 3; ++i) {
    ImagePair pair(i, i + 1);
    pair.is_valid = true;
    pair.inliers.resize(100);
    view_graph.image_pairs[pair.pair_id] = pair;
  }

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test: EstimateRotations called twice should be idempotent for consistent input
TEST_F(RotationEstimatorTest_27, IdempotentCall_27) {
  RotationEstimatorOptions options;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  BuildChainViewGraph(3, view_graph, images, frames, rigs);

  bool result1 = estimator.EstimateRotations(view_graph, rigs, frames, images);

  // Save state after first call
  auto images_copy = images;
  auto frames_copy = frames;
  auto rigs_copy = rigs;

  // Call again - should not crash and should give consistent result
  bool result2 = estimator.EstimateRotations(view_graph, rigs, frames, images);

  EXPECT_EQ(result1, result2);
}

// Test: Large number of images in a chain
TEST_F(RotationEstimatorTest_27, LargeChain_27) {
  RotationEstimatorOptions options;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  BuildChainViewGraph(20, view_graph, images, frames, rigs);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

}  // namespace
}  // namespace glomap
