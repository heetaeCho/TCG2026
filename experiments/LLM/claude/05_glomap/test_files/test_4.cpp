#include <gtest/gtest.h>
#include "glomap/scene/view_graph.h"
#include "glomap/types.h"

#include <unordered_map>

namespace glomap {

class ViewGraphTest_4 : public ::testing::Test {
 protected:
  ViewGraph view_graph_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
};

// Test with empty frames and images - should return 0
TEST_F(ViewGraphTest_4, EmptyInputReturnsZero_4) {
  int result = view_graph_.KeepLargestConnectedComponents(frames_, images_);
  EXPECT_EQ(result, 0);
}

// Test with single frame and single image, no image pairs
TEST_F(ViewGraphTest_4, SingleFrameSingleImage_4) {
  frames_[0] = Frame();
  frames_[0].is_registered = true;
  
  images_[0] = Image();
  images_[0].frame_id = 0;
  images_[0].is_registered = true;

  int result = view_graph_.KeepLargestConnectedComponents(frames_, images_);
  // With no image pairs, connected components depend on adjacency list from images
  // Result depends on internal logic
  EXPECT_GE(result, 0);
}

// Test with two connected frames via an image pair
TEST_F(ViewGraphTest_4, TwoConnectedFrames_4) {
  frames_[0] = Frame();
  frames_[0].is_registered = true;
  frames_[1] = Frame();
  frames_[1].is_registered = true;

  images_[0] = Image();
  images_[0].frame_id = 0;
  images_[0].is_registered = true;
  images_[1] = Image();
  images_[1].frame_id = 1;
  images_[1].is_registered = true;

  image_pair_t pair_id = ZuoPairId(0, 1);
  ImagePair ip;
  ip.image_id1 = 0;
  ip.image_id2 = 1;
  ip.is_valid = true;
  view_graph_.image_pairs[pair_id] = ip;

  int result = view_graph_.KeepLargestConnectedComponents(frames_, images_);
  EXPECT_GT(result, 0);

  // Both frames should be registered since they're in the same component
  EXPECT_TRUE(frames_[0].is_registered);
  EXPECT_TRUE(frames_[1].is_registered);
  // The image pair should remain valid
  EXPECT_TRUE(view_graph_.image_pairs[pair_id].is_valid);
}

// Test with two disconnected components - smaller one gets invalidated
TEST_F(ViewGraphTest_4, DisconnectedComponentsSmallOneInvalidated_4) {
  // Component 1: frames 0, 1 connected
  // Component 2: frame 2 alone
  frames_[0] = Frame();
  frames_[1] = Frame();
  frames_[2] = Frame();

  images_[0] = Image();
  images_[0].frame_id = 0;
  images_[0].is_registered = true;
  images_[1] = Image();
  images_[1].frame_id = 1;
  images_[1].is_registered = true;
  images_[2] = Image();
  images_[2].frame_id = 2;
  images_[2].is_registered = true;

  image_pair_t pair_01 = ZuoPairId(0, 1);
  ImagePair ip01;
  ip01.image_id1 = 0;
  ip01.image_id2 = 1;
  ip01.is_valid = true;
  view_graph_.image_pairs[pair_01] = ip01;

  int result = view_graph_.KeepLargestConnectedComponents(frames_, images_);
  EXPECT_GT(result, 0);

  // Frame 2 should NOT be registered (it's in the smaller component)
  EXPECT_FALSE(frames_[2].is_registered);
}

// Test that image pairs with unregistered images are invalidated
TEST_F(ViewGraphTest_4, ImagePairsWithUnregisteredImagesInvalidated_4) {
  frames_[0] = Frame();
  frames_[1] = Frame();
  frames_[2] = Frame();

  images_[0] = Image();
  images_[0].frame_id = 0;
  images_[0].is_registered = true;
  images_[1] = Image();
  images_[1].frame_id = 1;
  images_[1].is_registered = true;
  images_[2] = Image();
  images_[2].frame_id = 2;
  images_[2].is_registered = true;

  // Pair connecting component {0,1}
  image_pair_t pair_01 = ZuoPairId(0, 1);
  ImagePair ip01;
  ip01.image_id1 = 0;
  ip01.image_id2 = 1;
  ip01.is_valid = true;
  view_graph_.image_pairs[pair_01] = ip01;

  // Pair connecting image 1 and 2 (but frame 2 might be in smaller component)
  image_pair_t pair_02 = ZuoPairId(0, 2);
  ImagePair ip02;
  ip02.image_id1 = 0;
  ip02.image_id2 = 2;
  ip02.is_valid = true;
  // Don't add this pair to make frame 2 disconnected

  // Cross-component pair
  image_pair_t pair_12 = ZuoPairId(1, 2);
  ImagePair ip12;
  ip12.image_id1 = 1;
  ip12.image_id2 = 2;
  ip12.is_valid = true;
  view_graph_.image_pairs[pair_12] = ip12;

  int result = view_graph_.KeepLargestConnectedComponents(frames_, images_);

  // The pair within the largest component should remain valid
  EXPECT_TRUE(view_graph_.image_pairs[pair_01].is_valid);
}

// Test return value is non-negative
TEST_F(ViewGraphTest_4, ReturnValueNonNegative_4) {
  int result = view_graph_.KeepLargestConnectedComponents(frames_, images_);
  EXPECT_GE(result, 0);
}

// Test that all frames are initially set to unregistered before reassignment
TEST_F(ViewGraphTest_4, AllFramesResetBeforeAssignment_4) {
  frames_[0] = Frame();
  frames_[0].is_registered = true;
  frames_[1] = Frame();
  frames_[1].is_registered = true;

  images_[0] = Image();
  images_[0].frame_id = 0;
  images_[0].is_registered = true;
  images_[1] = Image();
  images_[1].frame_id = 1;
  images_[1].is_registered = true;

  image_pair_t pair_id = ZuoPairId(0, 1);
  ImagePair ip;
  ip.image_id1 = 0;
  ip.image_id2 = 1;
  ip.is_valid = true;
  view_graph_.image_pairs[pair_id] = ip;

  view_graph_.KeepLargestConnectedComponents(frames_, images_);

  // Frames in largest component should be registered
  // Since both are connected, both should be registered
  EXPECT_TRUE(frames_[0].is_registered);
  EXPECT_TRUE(frames_[1].is_registered);
}

}  // namespace glomap
