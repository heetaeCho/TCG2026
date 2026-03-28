// File: gravity_refiner_test_101.cc

#include <gtest/gtest.h>

#include <unordered_map>
#include <unordered_set>

#include "glomap/estimators/gravity_refinement.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/image.h"

namespace glomap {

class GravityRefinerTest_101 : public ::testing::Test {
protected:
  GravityRefinerOptions options_;
  std::unique_ptr<GravityRefiner> refiner_;

  void SetUp() override {
    options_ = GravityRefinerOptions();
    // Use a relatively large min_num_neighbors so that, in tests where
    // we only create a few neighbors, the refinement branch (ceres solve)
    // is naturally skipped without us depending on solver behavior.
    options_.min_num_neighbors = 100;
    refiner_ = std::make_unique<GravityRefiner>(options_);
  }
};

// TEST_ID: 101
// Behavior: If the image adjacency list is empty, RefineGravity should
//           return early without changing existing frame gravities.
TEST_F(GravityRefinerTest_101, ReturnsEarlyWhenAdjacencyListEmpty_101) {
  ViewGraph view_graph;
  // Ensure there are no image pairs so that the adjacency list is expected
  // to be empty via the public interface.
  view_graph.image_pairs.clear();

  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  const frame_t frame_id = 1;
  Frame frame;
  const Eigen::Vector3d gravity_before(0.0, 0.0, 1.0);
  frame.gravity_info.SetGravity(gravity_before);
  frames.emplace(frame_id, frame);

  refiner_->RefineGravity(view_graph, frames, images);

  auto it = frames.find(frame_id);
  ASSERT_NE(it, frames.end());
  const Eigen::Vector3d gravity_after = it->second.gravity_info.GetGravity();

  // Gravity should remain unchanged since no refinement can be done
  // without an adjacency list.
  EXPECT_EQ(gravity_before, gravity_after);
}

// TEST_ID: 101
// Behavior: When there are no frames and no images, RefineGravity should
//           handle the situation gracefully (no crashes / exceptions).
TEST_F(GravityRefinerTest_101, HandlesEmptyFramesAndImages_101) {
  ViewGraph view_graph;
  // Explicitly start with an empty graph.
  view_graph.image_pairs.clear();

  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  EXPECT_NO_THROW(refiner_->RefineGravity(view_graph, frames, images));
  EXPECT_TRUE(frames.empty());
  EXPECT_TRUE(images.empty());
}

// TEST_ID: 101
// Behavior: With a simple non-empty ViewGraph but no frames associated
//           to refine, RefineGravity should still complete without errors
//           and without modifying the (empty) frame map.
TEST_F(GravityRefinerTest_101, NonEmptyGraphWithNoFrames_101) {
  ViewGraph view_graph;

  // Create a simple image pair in the view graph so that the adjacency
  // list is expected to be non-empty via the public interface.
  const image_t img1_id = 1;
  const image_t img2_id = 2;
  ImagePair pair(img1_id, img2_id);
  view_graph.image_pairs.emplace(pair.pair_id, pair);

  std::unordered_map<frame_t, Frame> frames;   // still empty
  std::unordered_map<image_t, Image> images;   // can also be empty for this test

  EXPECT_NO_THROW(refiner_->RefineGravity(view_graph, frames, images));

  // Frames are empty before and after (no frames to refine).
  EXPECT_TRUE(frames.empty());
}

}  // namespace glomap
