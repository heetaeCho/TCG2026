#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include "glomap/scene/view_graph.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

namespace glomap {
namespace {

class ViewGraphMarkConnectedComponentsTest_5 : public ::testing::Test {
 protected:
  ViewGraph view_graph_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;

  // Helper to add an image pair edge to the view graph
  void AddImagePair(image_t img1, image_t img2) {
    image_pair_t pair_id = ImagePair::ImagePairToPairId(img1, img2);
    view_graph_.image_pairs[pair_id] = ImagePair(img1, img2);
    view_graph_.image_pairs[pair_id].is_valid = true;
  }

  // Helper to set up an image with a given frame_id
  void AddImage(image_t img_id, frame_t frame_id) {
    images_[img_id] = Image();
    images_[img_id].frame_id = frame_id;
    if (frames_.find(frame_id) == frames_.end()) {
      frames_[frame_id] = Frame();
    }
  }
};

// Test with empty inputs - no frames, no images
TEST_F(ViewGraphMarkConnectedComponentsTest_5, EmptyInputs_5) {
  int result = view_graph_.MarkConnectedComponents(frames_, images_, 1);
  EXPECT_EQ(result, 0);
}

// Test with a single connected component that meets min_num_img threshold
TEST_F(ViewGraphMarkConnectedComponentsTest_5, SingleComponentMeetsThreshold_5) {
  AddImage(0, 0);
  AddImage(1, 1);
  AddImage(2, 2);
  AddImagePair(0, 1);
  AddImagePair(1, 2);

  int result = view_graph_.MarkConnectedComponents(frames_, images_, 1);
  EXPECT_EQ(result, 1);

  // All frames should be in cluster 0
  for (auto& [frame_id, frame] : frames_) {
    EXPECT_EQ(frame.cluster_id, 0);
  }
}

// Test with a single component that doesn't meet the threshold
TEST_F(ViewGraphMarkConnectedComponentsTest_5, SingleComponentBelowThreshold_5) {
  AddImage(0, 0);
  AddImage(1, 1);
  AddImagePair(0, 1);

  int result = view_graph_.MarkConnectedComponents(frames_, images_, 5);
  EXPECT_EQ(result, 0);

  // All frames should remain with cluster_id = -1
  for (auto& [frame_id, frame] : frames_) {
    EXPECT_EQ(frame.cluster_id, -1);
  }
}

// Test with two disconnected components, both meeting threshold
TEST_F(ViewGraphMarkConnectedComponentsTest_5, TwoComponentsBothMeetThreshold_5) {
  // Component 1: frames 0, 1, 2
  AddImage(0, 0);
  AddImage(1, 1);
  AddImage(2, 2);
  AddImagePair(0, 1);
  AddImagePair(1, 2);

  // Component 2: frames 3, 4
  AddImage(3, 3);
  AddImage(4, 4);
  AddImagePair(3, 4);

  int result = view_graph_.MarkConnectedComponents(frames_, images_, 1);
  EXPECT_EQ(result, 2);

  // The largest component (3 frames) should get cluster_id 0
  // The smaller component (2 frames) should get cluster_id 1
  // Check that frames in the same component have the same cluster_id
  EXPECT_EQ(frames_[0].cluster_id, frames_[1].cluster_id);
  EXPECT_EQ(frames_[1].cluster_id, frames_[2].cluster_id);
  EXPECT_EQ(frames_[0].cluster_id, 0);

  EXPECT_EQ(frames_[3].cluster_id, frames_[4].cluster_id);
  EXPECT_EQ(frames_[3].cluster_id, 1);
}

// Test with two components, only the larger one meets threshold
TEST_F(ViewGraphMarkConnectedComponentsTest_5, TwoComponentsOnlyLargerMeetsThreshold_5) {
  // Component 1: frames 0, 1, 2
  AddImage(0, 0);
  AddImage(1, 1);
  AddImage(2, 2);
  AddImagePair(0, 1);
  AddImagePair(1, 2);

  // Component 2: frames 3, 4
  AddImage(3, 3);
  AddImage(4, 4);
  AddImagePair(3, 4);

  int result = view_graph_.MarkConnectedComponents(frames_, images_, 3);
  EXPECT_EQ(result, 1);

  // Larger component gets cluster 0
  EXPECT_EQ(frames_[0].cluster_id, 0);
  EXPECT_EQ(frames_[1].cluster_id, 0);
  EXPECT_EQ(frames_[2].cluster_id, 0);

  // Smaller component doesn't meet threshold, so cluster_id = -1
  EXPECT_EQ(frames_[3].cluster_id, -1);
  EXPECT_EQ(frames_[4].cluster_id, -1);
}

// Test with min_num_img = 0 (boundary: all components should qualify)
TEST_F(ViewGraphMarkConnectedComponentsTest_5, MinNumImgZero_5) {
  AddImage(0, 0);
  // Isolated node (no edges)
  
  // Another isolated node
  AddImage(1, 1);

  int result = view_graph_.MarkConnectedComponents(frames_, images_, 0);
  // Both single-node components should qualify
  EXPECT_EQ(result, 2);
}

// Test that cluster_ids are reset (frames from a previous run get -1 if not in a valid component)
TEST_F(ViewGraphMarkConnectedComponentsTest_5, ClusterIdsResetBetweenCalls_5) {
  AddImage(0, 0);
  AddImage(1, 1);
  AddImagePair(0, 1);

  // First call with low threshold
  int result1 = view_graph_.MarkConnectedComponents(frames_, images_, 1);
  EXPECT_EQ(result1, 1);
  EXPECT_EQ(frames_[0].cluster_id, 0);
  EXPECT_EQ(frames_[1].cluster_id, 0);

  // Second call with high threshold - should reset cluster_ids to -1
  int result2 = view_graph_.MarkConnectedComponents(frames_, images_, 100);
  EXPECT_EQ(result2, 0);
  EXPECT_EQ(frames_[0].cluster_id, -1);
  EXPECT_EQ(frames_[1].cluster_id, -1);
}

// Test with multiple components of equal size
TEST_F(ViewGraphMarkConnectedComponentsTest_5, EqualSizeComponents_5) {
  // Component 1: frames 0, 1
  AddImage(0, 0);
  AddImage(1, 1);
  AddImagePair(0, 1);

  // Component 2: frames 2, 3
  AddImage(2, 2);
  AddImage(3, 3);
  AddImagePair(2, 3);

  int result = view_graph_.MarkConnectedComponents(frames_, images_, 2);
  EXPECT_EQ(result, 2);

  // Both components should have valid cluster_ids (0 and 1)
  EXPECT_GE(frames_[0].cluster_id, 0);
  EXPECT_GE(frames_[2].cluster_id, 0);
  EXPECT_NE(frames_[0].cluster_id, frames_[2].cluster_id);
  EXPECT_EQ(frames_[0].cluster_id, frames_[1].cluster_id);
  EXPECT_EQ(frames_[2].cluster_id, frames_[3].cluster_id);
}

// Test with isolated nodes (no edges)
TEST_F(ViewGraphMarkConnectedComponentsTest_5, IsolatedNodesWithMinOne_5) {
  AddImage(0, 0);
  AddImage(1, 1);
  AddImage(2, 2);
  // No edges between any images

  int result = view_graph_.MarkConnectedComponents(frames_, images_, 1);
  // Each isolated node forms its own component of size 1
  EXPECT_EQ(result, 3);
}

// Test with isolated nodes that don't meet min threshold of 2
TEST_F(ViewGraphMarkConnectedComponentsTest_5, IsolatedNodesBelowThreshold_5) {
  AddImage(0, 0);
  AddImage(1, 1);
  AddImage(2, 2);
  // No edges

  int result = view_graph_.MarkConnectedComponents(frames_, images_, 2);
  EXPECT_EQ(result, 0);

  for (auto& [frame_id, frame] : frames_) {
    EXPECT_EQ(frame.cluster_id, -1);
  }
}

// Test that the largest component gets cluster_id 0 (sorted descending)
TEST_F(ViewGraphMarkConnectedComponentsTest_5, LargestComponentGetsClusterZero_5) {
  // Small component: frames 0, 1
  AddImage(0, 0);
  AddImage(1, 1);
  AddImagePair(0, 1);

  // Large component: frames 2, 3, 4, 5
  AddImage(2, 2);
  AddImage(3, 3);
  AddImage(4, 4);
  AddImage(5, 5);
  AddImagePair(2, 3);
  AddImagePair(3, 4);
  AddImagePair(4, 5);

  // Medium component: frames 6, 7, 8
  AddImage(6, 6);
  AddImage(7, 7);
  AddImage(8, 8);
  AddImagePair(6, 7);
  AddImagePair(7, 8);

  int result = view_graph_.MarkConnectedComponents(frames_, images_, 1);
  EXPECT_EQ(result, 3);

  // Largest (4 frames) -> cluster 0
  EXPECT_EQ(frames_[2].cluster_id, 0);
  EXPECT_EQ(frames_[3].cluster_id, 0);
  EXPECT_EQ(frames_[4].cluster_id, 0);
  EXPECT_EQ(frames_[5].cluster_id, 0);

  // Medium (3 frames) -> cluster 1
  EXPECT_EQ(frames_[6].cluster_id, 1);
  EXPECT_EQ(frames_[7].cluster_id, 1);
  EXPECT_EQ(frames_[8].cluster_id, 1);

  // Small (2 frames) -> cluster 2
  EXPECT_EQ(frames_[0].cluster_id, 2);
  EXPECT_EQ(frames_[1].cluster_id, 2);
}

// Test min_num_img equal to exact component size (boundary)
TEST_F(ViewGraphMarkConnectedComponentsTest_5, MinNumImgExactlyEqualToComponentSize_5) {
  AddImage(0, 0);
  AddImage(1, 1);
  AddImage(2, 2);
  AddImagePair(0, 1);
  AddImagePair(1, 2);

  // min_num_img = 3, component size = 3 -> should qualify
  int result = view_graph_.MarkConnectedComponents(frames_, images_, 3);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(frames_[0].cluster_id, 0);
  EXPECT_EQ(frames_[1].cluster_id, 0);
  EXPECT_EQ(frames_[2].cluster_id, 0);
}

// Test min_num_img one more than component size (boundary)
TEST_F(ViewGraphMarkConnectedComponentsTest_5, MinNumImgOneMoreThanComponentSize_5) {
  AddImage(0, 0);
  AddImage(1, 1);
  AddImage(2, 2);
  AddImagePair(0, 1);
  AddImagePair(1, 2);

  // min_num_img = 4, component size = 3 -> should not qualify
  int result = view_graph_.MarkConnectedComponents(frames_, images_, 4);
  EXPECT_EQ(result, 0);
  for (auto& [frame_id, frame] : frames_) {
    EXPECT_EQ(frame.cluster_id, -1);
  }
}

}  // namespace
}  // namespace glomap
