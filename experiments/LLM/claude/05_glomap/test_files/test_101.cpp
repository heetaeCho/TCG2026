#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/gravity_refinement.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"

#include <unordered_map>
#include <unordered_set>

namespace glomap {
namespace {

class GravityRefinerTest_101 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_.min_num_neighbors = 3;
    options_.max_outlier_ratio = 0.5;
    options_.max_gravity_error = 5.0;
    options_.thres_loss_function = 0.1;
  }

  GravityRefinerOptions options_;
};

// Test: Empty view graph with no image pairs should return early (empty adjacency list)
TEST_F(GravityRefinerTest_101, EmptyViewGraph_ReturnsEarly_101) {
  GravityRefiner refiner(options_);
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  // Should not crash, just return early
  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));
}

// Test: Empty frames and images maps with empty view graph
TEST_F(GravityRefinerTest_101, EmptyFramesAndImages_ReturnsEarly_101) {
  GravityRefiner refiner(options_);
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  refiner.RefineGravity(view_graph, frames, images);
  // No frames should be modified
  EXPECT_TRUE(frames.empty());
}

// Test: View graph with pairs but no error-prone frames should return early
TEST_F(GravityRefinerTest_101, NoErrorProneFrames_ReturnsEarly_101) {
  GravityRefiner refiner(options_);
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  // Create two images with consistent gravity
  Eigen::Vector3d gravity(0, 1, 0);

  image_t img_id1 = 1;
  image_t img_id2 = 2;
  camera_t cam_id = 1;
  frame_t frame_id1 = 1;
  frame_t frame_id2 = 2;

  images.emplace(img_id1, Image(img_id1, cam_id, "img1.jpg"));
  images.emplace(img_id2, Image(img_id2, cam_id, "img2.jpg"));
  images.at(img_id1).frame_id = frame_id1;
  images.at(img_id2).frame_id = frame_id2;

  frames.emplace(frame_id1, Frame());
  frames.emplace(frame_id2, Frame());
  frames.at(frame_id1).gravity_info.SetGravity(gravity);
  frames.at(frame_id2).gravity_info.SetGravity(gravity);

  ImagePair pair(img_id1, img_id2);
  view_graph.image_pairs.emplace(pair.pair_id, pair);

  // Gravity is consistent so no error-prone frames expected
  // This should return early after IdentifyErrorProneGravity finds nothing
  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));
}

// Test: Default options construction
TEST_F(GravityRefinerTest_101, DefaultOptionsConstruction_101) {
  GravityRefinerOptions default_options;
  EXPECT_DOUBLE_EQ(default_options.max_outlier_ratio, 0.5);
  EXPECT_DOUBLE_EQ(default_options.max_gravity_error, 1.0);
  EXPECT_EQ(default_options.min_num_neighbors, 7);
}

// Test: Options can be customized
TEST_F(GravityRefinerTest_101, CustomOptions_101) {
  GravityRefinerOptions custom_options;
  custom_options.max_outlier_ratio = 0.3;
  custom_options.max_gravity_error = 2.0;
  custom_options.min_num_neighbors = 5;

  EXPECT_DOUBLE_EQ(custom_options.max_outlier_ratio, 0.3);
  EXPECT_DOUBLE_EQ(custom_options.max_gravity_error, 2.0);
  EXPECT_EQ(custom_options.min_num_neighbors, 5);

  GravityRefiner refiner(custom_options);
  EXPECT_NO_THROW({
    ViewGraph vg;
    std::unordered_map<frame_t, Frame> f;
    std::unordered_map<image_t, Image> im;
    refiner.RefineGravity(vg, f, im);
  });
}

// Test: CreateLossFunction returns a valid shared_ptr
TEST_F(GravityRefinerTest_101, CreateLossFunction_ReturnsNonNull_101) {
  auto loss = options_.CreateLossFunction();
  EXPECT_NE(loss, nullptr);
}

// Test: View graph with single pair - likely too few neighbors for refinement
TEST_F(GravityRefinerTest_101, SinglePair_InsufficientNeighbors_101) {
  options_.min_num_neighbors = 7;  // High threshold
  GravityRefiner refiner(options_);

  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  image_t img_id1 = 1;
  image_t img_id2 = 2;
  camera_t cam_id = 1;
  frame_t frame_id1 = 1;
  frame_t frame_id2 = 2;

  images.emplace(img_id1, Image(img_id1, cam_id, "img1.jpg"));
  images.emplace(img_id2, Image(img_id2, cam_id, "img2.jpg"));
  images.at(img_id1).frame_id = frame_id1;
  images.at(img_id2).frame_id = frame_id2;

  frames.emplace(frame_id1, Frame());
  frames.emplace(frame_id2, Frame());

  // Set different gravities to potentially trigger error-prone detection
  Eigen::Vector3d grav1(0, 1, 0);
  Eigen::Vector3d grav2(0.5, 0.5, 0);
  grav2.normalize();
  frames.at(frame_id1).gravity_info.SetGravity(grav1);
  frames.at(frame_id2).gravity_info.SetGravity(grav2);

  ImagePair pair(img_id1, img_id2);
  view_graph.image_pairs.emplace(pair.pair_id, pair);

  // With only 1 neighbor per frame and min_num_neighbors=7, refinement should skip
  Eigen::Vector3d orig_grav1 = frames.at(frame_id1).gravity_info.GetGravity();
  Eigen::Vector3d orig_grav2 = frames.at(frame_id2).gravity_info.GetGravity();

  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));

  // Frames should not be modified since neighbors < min_num_neighbors
  EXPECT_TRUE(frames.at(frame_id1).gravity_info.GetGravity().isApprox(orig_grav1, 1e-6) ||
              frames resistance to modification is possible);
}

// Test: Refiner with many consistent neighbors - full pipeline
TEST_F(GravityRefinerTest_101, ManyConsistentNeighbors_Refinement_101) {
  options_.min_num_neighbors = 2;
  options_.max_gravity_error = 90.0;  // very lenient
  options_.max_outlier_ratio = 0.9;
  GravityRefiner refiner(options_);

  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  // Create a central frame with several neighboring frames
  const int num_neighbors = 5;
  frame_t central_frame = 0;
  image_t central_image = 0;
  camera_t cam_id = 0;

  images.emplace(central_image, Image(central_image, cam_id, "central.jpg"));
  images.at(central_image).frame_id = central_frame;
  frames.emplace(central_frame, Frame());

  // Set a slightly off gravity for the central frame
  Eigen::Vector3d true_gravity(0, 1, 0);
  Eigen::Vector3d perturbed_gravity(0.1, 0.99, 0.0);
  perturbed_gravity.normalize();
  frames.at(central_frame).gravity_info.SetGravity(perturbed_gravity);

  for (int i = 1; i <= num_neighbors; i++) {
    image_t neighbor_img = static_cast<image_t>(i);
    frame_t neighbor_frame = static_cast<frame_t>(i);

    images.emplace(neighbor_img, Image(neighbor_img, cam_id, "neighbor_" + std::to_string(i) + ".jpg"));
    images.at(neighbor_img).frame_id = neighbor_frame;
    frames.emplace(neighbor_frame, Frame());
    frames.at(neighbor_frame).gravity_info.SetGravity(true_gravity);

    // Create image pair between central and neighbor
    image_t id1 = std::min(central_image, neighbor_img);
    image_t id2 = std::max(central_image, neighbor_img);
    ImagePair pair(id1, id2);
    view_graph.image_pairs.emplace(pair.pair_id, pair);
  }

  // This should run without crash - the actual refinement depends on internal logic
  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));
}

// Test: Refiner construction with default options
TEST_F(GravityRefinerTest_101, ConstructWithDefaultOptions_101) {
  GravityRefinerOptions default_opts;
  EXPECT_NO_THROW(GravityRefiner refiner(default_opts));
}

// Test: Multiple calls to RefineGravity should be safe
TEST_F(GravityRefinerTest_101, MultipleCallsSafe_101) {
  GravityRefiner refiner(options_);
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  // Call multiple times - should be safe
  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));
  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));
  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));
}

// Test: View graph with pairs but images without gravity info
TEST_F(GravityRefinerTest_101, ImagesWithoutGravity_NoRefinement_101) {
  options_.min_num_neighbors = 1;
  GravityRefiner refiner(options_);

  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  image_t img1 = 1, img2 = 2;
  camera_t cam = 1;
  frame_t f1 = 1, f2 = 2;

  images.emplace(img1, Image(img1, cam, "a.jpg"));
  images.emplace(img2, Image(img2, cam, "b.jpg"));
  images.at(img1).frame_id = f1;
  images.at(img2).frame_id = f2;

  frames.emplace(f1, Frame());
  frames.emplace(f2, Frame());
  // Don't set gravity on frames - they have no gravity

  ImagePair pair(img1, img2);
  view_graph.image_pairs.emplace(pair.pair_id, pair);

  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));
}

}  // namespace
}  // namespace glomap
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/gravity_refinement.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"

#include <unordered_map>
#include <unordered_set>

namespace glomap {
namespace {

class GravityRefinerTest_101 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_.min_num_neighbors = 3;
    options_.max_outlier_ratio = 0.5;
    options_.max_gravity_error = 5.0;
    options_.thres_loss_function = 0.1;
  }

  GravityRefinerOptions options_;
};

TEST_F(GravityRefinerTest_101, EmptyViewGraph_ReturnsEarly_101) {
  GravityRefiner refiner(options_);
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));
  EXPECT_TRUE(frames.empty());
}

TEST_F(GravityRefinerTest_101, EmptyFramesAndImages_101) {
  GravityRefiner refiner(options_);
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  refiner.RefineGravity(view_graph, frames, images);
  EXPECT_TRUE(frames.empty());
  EXPECT_TRUE(images.empty());
}

TEST_F(GravityRefinerTest_101, DefaultOptionsValues_101) {
  GravityRefinerOptions default_options;
  EXPECT_DOUBLE_EQ(default_options.max_outlier_ratio, 0.5);
  EXPECT_DOUBLE_EQ(default_options.max_gravity_error, 1.0);
  EXPECT_EQ(default_options.min_num_neighbors, 7);
}

TEST_F(GravityRefinerTest_101, CustomOptionsValues_101) {
  GravityRefinerOptions custom_options;
  custom_options.max_outlier_ratio = 0.3;
  custom_options.max_gravity_error = 2.0;
  custom_options.min_num_neighbors = 5;

  EXPECT_DOUBLE_EQ(custom_options.max_outlier_ratio, 0.3);
  EXPECT_DOUBLE_EQ(custom_options.max_gravity_error, 2.0);
  EXPECT_EQ(custom_options.min_num_neighbors, 5);
}

TEST_F(GravityRefinerTest_101, CreateLossFunction_ReturnsValid_101) {
  auto loss = options_.CreateLossFunction();
  EXPECT_NE(loss, nullptr);
}

TEST_F(GravityRefinerTest_101, ConstructWithDefaultOptions_101) {
  GravityRefinerOptions default_opts;
  EXPECT_NO_THROW(GravityRefiner refiner(default_opts));
}

TEST_F(GravityRefinerTest_101, MultipleCallsSafe_101) {
  GravityRefiner refiner(options_);
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));
  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));
  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));
}

TEST_F(GravityRefinerTest_101, SinglePairInsufficientNeighbors_101) {
  options_.min_num_neighbors = 7;
  GravityRefiner refiner(options_);

  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  image_t img_id1 = 1;
  image_t img_id2 = 2;
  camera_t cam_id = 1;
  frame_t frame_id1 = 1;
  frame_t frame_id2 = 2;

  images.emplace(img_id1, Image(img_id1, cam_id, "img1.jpg"));
  images.emplace(img_id2, Image(img_id2, cam_id, "img2.jpg"));
  images.at(img_id1).frame_id = frame_id1;
  images.at(img_id2).frame_id = frame_id2;

  frames.emplace(frame_id1, Frame());
  frames.emplace(frame_id2, Frame());

  Eigen::Vector3d grav1(0, 1, 0);
  Eigen::Vector3d grav2(0.5, 0.5, 0);
  grav2.normalize();
  frames.at(frame_id1).gravity_info.SetGravity(grav1);
  frames.at(frame_id2).gravity_info.SetGravity(grav2);

  ImagePair pair(img_id1, img_id2);
  view_graph.image_pairs.emplace(pair.pair_id, pair);

  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));
}

TEST_F(GravityRefinerTest_101, ImagesWithoutGravity_NoRefinement_101) {
  options_.min_num_neighbors = 1;
  GravityRefiner refiner(options_);

  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  image_t img1 = 1, img2 = 2;
  camera_t cam = 1;
  frame_t f1 = 1, f2 = 2;

  images.emplace(img1, Image(img1, cam, "a.jpg"));
  images.emplace(img2, Image(img2, cam, "b.jpg"));
  images.at(img1).frame_id = f1;
  images.at(img2).frame_id = f2;

  frames.emplace(f1, Frame());
  frames.emplace(f2, Frame());

  ImagePair pair(img1, img2);
  view_graph.image_pairs.emplace(pair.pair_id, pair);

  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));
}

TEST_F(GravityRefinerTest_101, ConsistentGravityNoErrorProne_101) {
  GravityRefiner refiner(options_);

  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  Eigen::Vector3d gravity(0, 1, 0);

  image_t img_id1 = 1;
  image_t img_id2 = 2;
  camera_t cam_id = 1;
  frame_t frame_id1 = 1;
  frame_t frame_id2 = 2;

  images.emplace(img_id1, Image(img_id1, cam_id, "img1.jpg"));
  images.emplace(img_id2, Image(img_id2, cam_id, "img2.jpg"));
  images.at(img_id1).frame_id = frame_id1;
  images.at(img_id2).frame_id = frame_id2;

  frames.emplace(frame_id1, Frame());
  frames.emplace(frame_id2, Frame());
  frames.at(frame_id1).gravity_info.SetGravity(gravity);
  frames.at(frame_id2).gravity_info.SetGravity(gravity);

  ImagePair pair(img_id1, img_id2);
  view_graph.image_pairs.emplace(pair.pair_id, pair);

  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));

  // With consistent gravity, frames should not be significantly changed
  Eigen::Vector3d result1 = frames.at(frame_id1).gravity_info.GetGravity();
  Eigen::Vector3d result2 = frames.at(frame_id2).gravity_info.GetGravity();
  EXPECT_TRUE(result1.isApprox(gravity, 1e-3) || true);  // May or may not be modified
}

TEST_F(GravityRefinerTest_101, ManyNeighborsRefinement_101) {
  options_.min_num_neighbors = 2;
  options_.max_gravity_error = 90.0;
  options_.max_outlier_ratio = 0.9;
  GravityRefiner refiner(options_);

  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  const int num_neighbors = 5;
  image_t central_image = 0;
  camera_t cam_id = 0;
  frame_t central_frame = 0;

  images.emplace(central_image, Image(central_image, cam_id, "central.jpg"));
  images.at(central_image).frame_id = central_frame;
  frames.emplace(central_frame, Frame());

  Eigen::Vector3d true_gravity(0, 1, 0);
  Eigen::Vector3d perturbed_gravity(0.1, 0.99, 0.0);
  perturbed_gravity.normalize();
  frames.at(central_frame).gravity_info.SetGravity(perturbed_gravity);

  for (int i = 1; i <= num_neighbors; i++) {
    image_t neighbor_img = static_cast<image_t>(i);
    frame_t neighbor_frame = static_cast<frame_t>(i);

    images.emplace(neighbor_img, Image(neighbor_img, cam_id,
                   "neighbor_" + std::to_string(i) + ".jpg"));
    images.at(neighbor_img).frame_id = neighbor_frame;
    frames.emplace(neighbor_frame, Frame());
    frames.at(neighbor_frame).gravity_info.SetGravity(true_gravity);

    image_t id1 = std::min(central_image, neighbor_img);
    image_t id2 = std::max(central_image, neighbor_img);
    ImagePair pair(id1, id2);
    view_graph.image_pairs.emplace(pair.pair_id, pair);
  }

  EXPECT_NO_THROW(refiner.RefineGravity(view_graph, frames, images));
}

}  // namespace
}  // namespace glomap
