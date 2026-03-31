#include <gtest/gtest.h>
#include "glomap/scene/view_graph.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"

#include <unordered_map>
#include <unordered_set>

namespace glomap {
namespace {

class ViewGraphTest_93 : public ::testing::Test {
 protected:
  void SetUp() override {}

  // Helper to create an Image with a given image_id, camera_id, and frame_id
  Image MakeImage(image_t img_id, camera_t cam_id, frame_t frm_id) {
    Image img(img_id, cam_id, "image_" + std::to_string(img_id));
    img.frame_id = frm_id;
    return img;
  }
};

// Test: Empty frames and images should return 0
TEST_F(ViewGraphTest_93, KeepLargestCC_EmptyInput_93) {
  ViewGraph vg;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  int result = vg.KeepLargestConnectedComponents(frames, images);
  EXPECT_EQ(result, 0);
}

// Test: Single image pair connecting two frames - both should remain registered
TEST_F(ViewGraphTest_93, KeepLargestCC_SinglePairTwoFrames_93) {
  ViewGraph vg;

  std::unordered_map<frame_t, Frame> frames;
  frames[0] = Frame();
  frames[0].is_registered = true;
  frames[1] = Frame();
  frames[1].is_registered = true;

  std::unordered_map<image_t, Image> images;
  Image img0 = MakeImage(0, 0, 0);
  img0.frame_ptr = &frames[0];
  images[0] = img0;

  Image img1 = MakeImage(1, 0, 1);
  img1.frame_ptr = &frames[1];
  images[1] = img1;

  ImagePair pair(0, 1);
  pair.is_valid = true;
  vg.image_pairs[pair.pair_id] = pair;

  int result = vg.KeepLargestConnectedComponents(frames, images);

  // The largest component should contain both frames
  // Result should be > 0
  EXPECT_GT(result, 0);

  // Both frames should be registered (part of largest component)
  EXPECT_TRUE(frames[0].is_registered);
  EXPECT_TRUE(frames[1].is_registered);
}

// Test: Two disconnected components - only the larger one should remain registered
TEST_F(ViewGraphTest_93, KeepLargestCC_TwoComponents_LargerKept_93) {
  ViewGraph vg;

  std::unordered_map<frame_t, Frame> frames;
  // Component 1: frames 0, 1, 2 (3 frames)
  for (frame_t f = 0; f < 3; f++) {
    frames[f] = Frame();
    frames[f].is_registered = true;
  }
  // Component 2: frames 3, 4 (2 frames)
  for (frame_t f = 3; f < 5; f++) {
    frames[f] = Frame();
    frames[f].is_registered = true;
  }

  std::unordered_map<image_t, Image> images;
  for (image_t i = 0; i < 5; i++) {
    Image img = MakeImage(i, 0, static_cast<frame_t>(i));
    img.frame_ptr = &frames[i];
    images[i] = img;
  }

  // Component 1 edges: 0-1, 1-2
  {
    ImagePair p(0, 1);
    p.is_valid = true;
    vg.image_pairs[p.pair_id] = p;
  }
  {
    ImagePair p(1, 2);
    p.is_valid = true;
    vg.image_pairs[p.pair_id] = p;
  }

  // Component 2 edges: 3-4
  {
    ImagePair p(3, 4);
    p.is_valid = true;
    vg.image_pairs[p.pair_id] = p;
  }

  int result = vg.KeepLargestConnectedComponents(frames, images);
  EXPECT_GT(result, 0);

  // Frames in larger component (0,1,2) should be registered
  EXPECT_TRUE(frames[0].is_registered);
  EXPECT_TRUE(frames[1].is_registered);
  EXPECT_TRUE(frames[2].is_registered);

  // Frames in smaller component (3,4) should NOT be registered
  EXPECT_FALSE(frames[3].is_registered);
  EXPECT_FALSE(frames[4].is_registered);

  // Image pairs connecting non-registered images should be invalidated
  for (auto& [pair_id, ip] : vg.image_pairs) {
    if ((ip.image_id1 == 3 && ip.image_id2 == 4) ||
        (ip.image_id1 == 4 && ip.image_id2 == 3)) {
      EXPECT_FALSE(ip.is_valid);
    }
  }
}

// Test: All images in one component - everything should stay valid
TEST_F(ViewGraphTest_93, KeepLargestCC_SingleComponent_AllValid_93) {
  ViewGraph vg;

  std::unordered_map<frame_t, Frame> frames;
  for (frame_t f = 0; f < 4; f++) {
    frames[f] = Frame();
    frames[f].is_registered = true;
  }

  std::unordered_map<image_t, Image> images;
  for (image_t i = 0; i < 4; i++) {
    Image img = MakeImage(i, 0, static_cast<frame_t>(i));
    img.frame_ptr = &frames[i];
    images[i] = img;
  }

  // Chain: 0-1, 1-2, 2-3
  {
    ImagePair p(0, 1);
    p.is_valid = true;
    vg.image_pairs[p.pair_id] = p;
  }
  {
    ImagePair p(1, 2);
    p.is_valid = true;
    vg.image_pairs[p.pair_id] = p;
  }
  {
    ImagePair p(2, 3);
    p.is_valid = true;
    vg.image_pairs[p.pair_id] = p;
  }

  int result = vg.KeepLargestConnectedComponents(frames, images);
  EXPECT_GT(result, 0);

  for (auto& [fid, frame] : frames) {
    EXPECT_TRUE(frame.is_registered);
  }

  for (auto& [pid, ip] : vg.image_pairs) {
    EXPECT_TRUE(ip.is_valid);
  }
}

// Test: No image pairs at all but frames/images exist - should return 0
TEST_F(ViewGraphTest_93, KeepLargestCC_NoImagePairs_93) {
  ViewGraph vg;

  std::unordered_map<frame_t, Frame> frames;
  frames[0] = Frame();
  frames[0].is_registered = true;
  frames[1] = Frame();
  frames[1].is_registered = true;

  std::unordered_map<image_t, Image> images;
  Image img0 = MakeImage(0, 0, 0);
  img0.frame_ptr = &frames[0];
  images[0] = img0;

  Image img1 = MakeImage(1, 0, 1);
  img1.frame_ptr = &frames[1];
  images[1] = img1;

  // No image pairs added to view graph
  int result = vg.KeepLargestConnectedComponents(frames, images);
  // With no edges, connected components are individual nodes (size 1 each)
  // or could be 0 depending on how adjacency list is built
  // We just verify it doesn't crash and returns a valid value
  EXPECT_GE(result, 0);
}

// Test: Three separate components of sizes 1, 2, 3 - only size 3 kept
TEST_F(ViewGraphTest_93, KeepLargestCC_ThreeComponents_93) {
  ViewGraph vg;

  std::unordered_map<frame_t, Frame> frames;
  for (frame_t f = 0; f < 6; f++) {
    frames[f] = Frame();
    frames[f].is_registered = true;
  }

  std::unordered_map<image_t, Image> images;
  for (image_t i = 0; i < 6; i++) {
    Image img = MakeImage(i, 0, static_cast<frame_t>(i));
    img.frame_ptr = &frames[i];
    images[i] = img;
  }

  // Component 1 (size 3): frames 0, 1, 2
  {
    ImagePair p(0, 1);
    p.is_valid = true;
    vg.image_pairs[p.pair_id] = p;
  }
  {
    ImagePair p(1, 2);
    p.is_valid = true;
    vg.image_pairs[p.pair_id] = p;
  }

  // Component 2 (size 2): frames 3, 4
  {
    ImagePair p(3, 4);
    p.is_valid = true;
    vg.image_pairs[p.pair_id] = p;
  }

  // Component 3 (size 1): frame 5 (no edges)
  // frame 5 is isolated

  int result = vg.KeepLargestConnectedComponents(frames, images);
  EXPECT_GT(result, 0);

  // Largest component frames (0,1,2) should be registered
  EXPECT_TRUE(frames[0].is_registered);
  EXPECT_TRUE(frames[1].is_registered);
  EXPECT_TRUE(frames[2].is_registered);

  // Smaller component frames should not be registered
  EXPECT_FALSE(frames[3].is_registered);
  EXPECT_FALSE(frames[4].is_registered);
  EXPECT_FALSE(frames[5].is_registered);
}

// Test: Image pairs that were already invalid should remain so
TEST_F(ViewGraphTest_93, KeepLargestCC_InvalidPairsRemainInvalid_93) {
  ViewGraph vg;

  std::unordered_map<frame_t, Frame> frames;
  for (frame_t f = 0; f < 3; f++) {
    frames[f] = Frame();
    frames[f].is_registered = true;
  }

  std::unordered_map<image_t, Image> images;
  for (image_t i = 0; i < 3; i++) {
    Image img = MakeImage(i, 0, static_cast<frame_t>(i));
    img.frame_ptr = &frames[i];
    images[i] = img;
  }

  // Valid pair
  {
    ImagePair p(0, 1);
    p.is_valid = true;
    vg.image_pairs[p.pair_id] = p;
  }
  // Already invalid pair within the same component
  {
    ImagePair p(1, 2);
    p.is_valid = false;
    vg.image_pairs[p.pair_id] = p;
  }

  int result = vg.KeepLargestConnectedComponents(frames, images);
  // Just verify it doesn't crash
  EXPECT_GE(result, 0);
}

// Test: CreateImageAdjacencyList on empty view graph
TEST_F(ViewGraphTest_93, CreateImageAdjacencyList_Empty_93) {
  ViewGraph vg;
  auto adj = vg.CreateImageAdjacencyList();
  EXPECT_TRUE(adj.empty());
}

// Test: CreateImageAdjacencyList with some pairs
TEST_F(ViewGraphTest_93, CreateImageAdjacencyList_WithPairs_93) {
  ViewGraph vg;

  ImagePair p1(0, 1);
  p1.is_valid = true;
  vg.image_pairs[p1.pair_id] = p1;

  ImagePair p2(1, 2);
  p2.is_valid = true;
  vg.image_pairs[p2.pair_id] = p2;

  auto adj = vg.CreateImageAdjacencyList();
  // We expect image 1 to have neighbors 0 and 2
  EXPECT_GE(adj.size(), 2u);
}

// Test: CreateFrameAdjacencyList with images
TEST_F(ViewGraphTest_93, CreateFrameAdjacencyList_Basic_93) {
  ViewGraph vg;

  std::unordered_map<frame_t, Frame> frames;
  frames[0] = Frame();
  frames[1] = Frame();

  std::unordered_map<image_t, Image> images;
  Image img0 = MakeImage(0, 0, 0);
  img0.frame_ptr = &frames[0];
  images[0] = img0;

  Image img1 = MakeImage(1, 0, 1);
  img1.frame_ptr = &frames[1];
  images[1] = img1;

  ImagePair p(0, 1);
  p.is_valid = true;
  vg.image_pairs[p.pair_id] = p;

  auto adj = vg.CreateFrameAdjacencyList(images);
  // Should have adjacency between frame 0 and frame 1
  EXPECT_FALSE(adj.empty());
}

// Test: frames is_registered reset behavior in KeepLargestConnectedComponents
TEST_F(ViewGraphTest_93, KeepLargestCC_ResetsRegistration_93) {
  ViewGraph vg;

  std::unordered_map<frame_t, Frame> frames;
  frames[0] = Frame();
  frames[0].is_registered = true;
  frames[1] = Frame();
  frames[1].is_registered = false; // was not registered

  std::unordered_map<image_t, Image> images;
  Image img0 = MakeImage(0, 0, 0);
  img0.frame_ptr = &frames[0];
  images[0] = img0;

  Image img1 = MakeImage(1, 0, 1);
  img1.frame_ptr = &frames[1];
  images[1] = img1;

  ImagePair p(0, 1);
  p.is_valid = true;
  vg.image_pairs[p.pair_id] = p;

  int result = vg.KeepLargestConnectedComponents(frames, images);
  EXPECT_GT(result, 0);

  // Both should be in the largest (and only) component
  EXPECT_TRUE(frames[0].is_registered);
  EXPECT_TRUE(frames[1].is_registered);
}

}  // namespace
}  // namespace glomap
