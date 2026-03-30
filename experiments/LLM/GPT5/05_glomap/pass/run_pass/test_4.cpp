#include <gtest/gtest.h>

#include <unordered_map>

// Assuming the real header defines glomap::ViewGraph, Frame, Image, frame_t, image_t
#include "glomap/scene/view_graph.h"

namespace glomap {

class ViewGraphKeepLargestConnectedComponentsTest_4 : public ::testing::Test {
 protected:
  ViewGraph view_graph_;
};

// [Boundary] Empty frames and images: no connected components → returns 0.
TEST_F(ViewGraphKeepLargestConnectedComponentsTest_4,
       EmptyFramesAndImagesReturnsZero_4) {
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  int result = view_graph_.KeepLargestConnectedComponents(frames, images);

  // With no images, there should be no connected components to keep.
  EXPECT_EQ(result, 0);
  EXPECT_TRUE(frames.empty());
  EXPECT_TRUE(images.empty());
}

// [Boundary] Non-empty frames, but no images: still no connected components → returns 0.
// Also verifies that the function does not touch frames when there are no components.
TEST_F(ViewGraphKeepLargestConnectedComponentsTest_4,
       FramesWithoutImagesReturnZeroAndKeepRegistration_4) {
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  // Prepare a couple of frames and mark them as registered.
  frame_t f1 = static_cast<frame_t>(1);
  frame_t f2 = static_cast<frame_t>(2);

  Frame frame1;
  Frame frame2;

  frame1.is_registered = true;
  frame2.is_registered = true;

  frames.emplace(f1, frame1);
  frames.emplace(f2, frame2);

  int result = view_graph_.KeepLargestConnectedComponents(frames, images);

  // With no images, we still expect no connected components.
  EXPECT_EQ(result, 0);

  // Because there are no connected components, the early return path should be taken
  // and the function should not modify frame registration flags.
  ASSERT_EQ(frames.size(), 2u);
  EXPECT_TRUE(frames[f1].is_registered);
  EXPECT_TRUE(frames[f2].is_registered);
}

}  // namespace glomap
