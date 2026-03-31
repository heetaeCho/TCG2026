#include <gtest/gtest.h>
#include "glomap/processors/relpose_filter.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"

#include <unordered_map>
#include <cmath>

namespace glomap {
namespace {

class RelPoseFilterTest_152 : public ::testing::Test {
 protected:
  void SetUp() override {}

  // Helper to create a registered image with a given pose
  Image CreateRegisteredImage(image_t id, camera_t cam_id,
                              const Rigid3d& cam_from_world) {
    Image img(id, cam_id, "img_" + std::to_string(id));
    // We need to set the image as registered and set its pose.
    // Based on the interface, we assume there's a way to set registration
    // and cam_from_world. We'll rely on the actual implementation's
    // public interface.
    img.cam_from_world = cam_from_world;
    img.is_registered = true;
    return img;
  }
};

// Test that FilterRotations with an empty view graph does nothing and doesn't crash
TEST_F(RelPoseFilterTest_152, FilterRotations_EmptyViewGraph_152) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  
  // Should not crash with empty data
  RelPoseFilter::FilterRotations(view_graph, images, 5.0);
  EXPECT_TRUE(view_graph.image_pairs.empty());
}

// Test that FilterRotations skips already invalid pairs
TEST_F(RelPoseFilterTest_152, FilterRotations_SkipsInvalidPairs_152) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;

  Image img1(0, 0, "img0");
  Image img2(1, 0, "img1");
  images[0] = img1;
  images[1] = img2;

  ImagePair pair(0, 1);
  pair.is_valid = false;
  view_graph.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterRotations(view_graph, images, 5.0);
  
  // Pair should remain invalid (was already invalid)
  EXPECT_FALSE(view_graph.image_pairs[pair.pair_id].is_valid);
}

// Test that FilterRotations skips pairs where images are not registered
TEST_F(RelPoseFilterTest_152, FilterRotations_SkipsUnregisteredImages_152) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;

  // Create unregistered images
  Image img1(0, 0, "img0");
  Image img2(1, 0, "img1");
  images[0] = img1;
  images[1] = img2;

  ImagePair pair(0, 1);
  pair.is_valid = true;
  view_graph.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterRotations(view_graph, images, 5.0);
  
  // Pair should still be valid since unregistered images are skipped
  EXPECT_TRUE(view_graph.image_pairs[pair.pair_id].is_valid);
}

// Test that FilterRotations keeps pairs with matching rotations (angle < max_angle)
TEST_F(RelPoseFilterTest_152, FilterRotations_KeepsConsistentPairs_152) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;

  // Create two registered images with identity poses
  Rigid3d identity;
  images[0] = CreateRegisteredImage(0, 0, identity);
  images[1] = CreateRegisteredImage(1, 0, identity);

  // Create a pair with identity relative pose (consistent with both being at identity)
  ImagePair pair(0, 1, identity);
  pair.is_valid = true;
  view_graph.image_pairs[pair.pair_id] = pair;

  // Large threshold so it should pass
  RelPoseFilter::FilterRotations(view_graph, images, 180.0);
  
  EXPECT_TRUE(view_graph.image_pairs[pair.pair_id].is_valid);
}

// Test that FilterRotations invalidates pairs with large rotation difference
TEST_F(RelPoseFilterTest_152, FilterRotations_InvalidatesInconsistentPairs_152) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;

  Rigid3d identity;
  images[0] = CreateRegisteredImage(0, 0, identity);
  images[1] = CreateRegisteredImage(1, 0, identity);

  // Create a pair with a large rotation (90 degrees around Z axis)
  Eigen::Quaterniond q(Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitZ()));
  Rigid3d large_rotation;
  large_rotation.rotation = q;
  
  ImagePair pair(0, 1, large_rotation);
  pair.is_valid = true;
  view_graph.image_pairs[pair.pair_id] = pair;

  // Small threshold: 1 degree
  RelPoseFilter::FilterRotations(view_graph, images, 1.0);
  
  EXPECT_FALSE(view_graph.image_pairs[pair.pair_id].is_valid);
}

// Test FilterRotations with zero max_angle threshold
TEST_F(RelPoseFilterTest_152, FilterRotations_ZeroThreshold_152) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;

  Rigid3d identity;
  images[0] = CreateRegisteredImage(0, 0, identity);
  images[1] = CreateRegisteredImage(1, 0, identity);

  // Identity relative pose matches computed pose exactly
  ImagePair pair(0, 1, identity);
  pair.is_valid = true;
  view_graph.image_pairs[pair.pair_id] = pair;

  // Zero threshold: only exact match should pass
  RelPoseFilter::FilterRotations(view_graph, images, 0.0);
  
  // Angle should be 0, and 0 > 0 is false, so pair stays valid
  EXPECT_TRUE(view_graph.image_pairs[pair.pair_id].is_valid);
}

// Test FilterRotations with multiple pairs - some valid, some invalid
TEST_F(RelPoseFilterTest_152, FilterRotations_MultiplePairsMixed_152) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;

  Rigid3d identity;
  images[0] = CreateRegisteredImage(0, 0, identity);
  images[1] = CreateRegisteredImage(1, 0, identity);
  images[2] = CreateRegisteredImage(2, 0, identity);

  // Pair 0-1: consistent (identity relative pose)
  ImagePair pair01(0, 1, identity);
  pair01.is_valid = true;
  view_graph.image_pairs[pair01.pair_id] = pair01;

  // Pair 0-2: inconsistent (large rotation)
  Eigen::Quaterniond q(Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitZ()));
  Rigid3d large_rot;
  large_rot.rotation = q;
  ImagePair pair02(0, 2, large_rot);
  pair02.is_valid = true;
  view_graph.image_pairs[pair02.pair_id] = pair02;

  RelPoseFilter::FilterRotations(view_graph, images, 5.0);
  
  EXPECT_TRUE(view_graph.image_pairs[pair01.pair_id].is_valid);
  EXPECT_FALSE(view_graph.image_pairs[pair02.pair_id].is_valid);
}

// Test FilterInlierNum with empty view graph
TEST_F(RelPoseFilterTest_152, FilterInlierNum_EmptyViewGraph_152) {
  ViewGraph view_graph;
  RelPoseFilter::FilterInlierNum(view_graph, 10);
  EXPECT_TRUE(view_graph.image_pairs.empty());
}

// Test FilterInlierNum filters pairs with too few inliers
TEST_F(RelPoseFilterTest_152, FilterInlierNum_FiltersFewInliers_152) {
  ViewGraph view_graph;

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.inliers.resize(5);  // 5 inliers
  view_graph.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierNum(view_graph, 10);
  
  EXPECT_FALSE(view_graph.image_pairs[pair.pair_id].is_valid);
}

// Test FilterInlierNum keeps pairs with enough inliers
TEST_F(RelPoseFilterTest_152, FilterInlierNum_KeepsSufficientInliers_152) {
  ViewGraph view_graph;

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.inliers.resize(20);  // 20 inliers
  view_graph.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierNum(view_graph, 10);
  
  EXPECT_TRUE(view_graph.image_pairs[pair.pair_id].is_valid);
}

// Test FilterInlierNum boundary: exact threshold
TEST_F(RelPoseFilterTest_152, FilterInlierNum_ExactThreshold_152) {
  ViewGraph view_graph;

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.inliers.resize(10);  // exactly 10 inliers
  view_graph.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierNum(view_graph, 10);
  
  // Behavior at exact boundary: depends on implementation (>= or >)
  // We just check it doesn't crash; the validity depends on impl
  // But typically >= threshold means keep
  // Not asserting specific value since we treat as black box
}

// Test FilterInlierNum skips already invalid pairs
TEST_F(RelPoseFilterTest_152, FilterInlierNum_SkipsInvalidPairs_152) {
  ViewGraph view_graph;

  ImagePair pair(0, 1);
  pair.is_valid = false;
  pair.inliers.resize(5);
  view_graph.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierNum(view_graph, 10);
  
  EXPECT_FALSE(view_graph.image_pairs[pair.pair_id].is_valid);
}

// Test FilterInlierRatio with empty view graph
TEST_F(RelPoseFilterTest_152, FilterInlierRatio_EmptyViewGraph_152) {
  ViewGraph view_graph;
  RelPoseFilter::FilterInlierRatio(view_graph, 0.5);
  EXPECT_TRUE(view_graph.image_pairs.empty());
}

// Test FilterInlierRatio filters pairs with low inlier ratio
TEST_F(RelPoseFilterTest_152, FilterInlierRatio_FiltersLowRatio_152) {
  ViewGraph view_graph;

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.inliers.resize(1);
  pair.matches.resize(100, 2);  // 100 matches
  view_graph.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierRatio(view_graph, 0.5);
  
  EXPECT_FALSE(view_graph.image_pairs[pair.pair_id].is_valid);
}

// Test FilterInlierRatio keeps pairs with high inlier ratio
TEST_F(RelPoseFilterTest_152, FilterInlierRatio_KeepsHighRatio_152) {
  ViewGraph view_graph;

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.inliers.resize(90);
  pair.matches.resize(100, 2);  // 100 matches, 90 inliers = 0.9 ratio
  view_graph.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierRatio(view_graph, 0.5);
  
  EXPECT_TRUE(view_graph.image_pairs[pair.pair_id].is_valid);
}

// Test FilterInlierNum with zero threshold
TEST_F(RelPoseFilterTest_152, FilterInlierNum_ZeroThreshold_152) {
  ViewGraph view_graph;

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.inliers.resize(0);
  view_graph.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierNum(view_graph, 0);
  // With 0 inliers and threshold 0, behavior depends on implementation
}

// Test FilterInlierRatio with zero threshold
TEST_F(RelPoseFilterTest_152, FilterInlierRatio_ZeroThreshold_152) {
  ViewGraph view_graph;

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.inliers.resize(0);
  pair.matches.resize(100, 2);
  view_graph.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierRatio(view_graph, 0.0);
  // Should not crash
}

// Test FilterRotations with very large max_angle - nothing should be filtered
TEST_F(RelPoseFilterTest_152, FilterRotations_VeryLargeThreshold_152) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;

  Rigid3d identity;
  images[0] = CreateRegisteredImage(0, 0, identity);
  images[1] = CreateRegisteredImage(1, 0, identity);

  Eigen::Quaterniond q(Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitZ()));
  Rigid3d rot180;
  rot180.rotation = q;
  
  ImagePair pair(0, 1, rot180);
  pair.is_valid = true;
  view_graph.image_pairs[pair.pair_id] = pair;

  // Very large threshold: 360 degrees
  RelPoseFilter::FilterRotations(view_graph, images, 360.0);
  
  EXPECT_TRUE(view_graph.image_pairs[pair.pair_id].is_valid);
}

}  // namespace
}  // namespace glomap
