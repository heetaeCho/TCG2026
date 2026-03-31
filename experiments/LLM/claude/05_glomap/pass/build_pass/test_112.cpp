#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/controllers/rotation_averager.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/frame.h"
#include "glomap/estimators/global_rotation_averaging.h"

namespace glomap {
namespace {

class RotationAveragerTest_112 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_ = RotationAveragerOptions();
  }

  // Helper to create a minimal connected scene with N images in a chain
  void CreateMinimalScene(int num_images) {
    // Create a single rig with one reference sensor
    Rig rig;
    rig.SetRigId(0);
    sensor_t ref_sensor(SensorType::CAMERA, 0);
    rig.AddRefSensor(ref_sensor);
    rigs_[0] = rig;

    for (int i = 0; i < num_images; ++i) {
      image_t img_id = static_cast<image_t>(i);
      camera_t cam_id = 0;
      images_.emplace(img_id, Image(img_id, cam_id, "image_" + std::to_string(i) + ".jpg"));
    }

    frame_t frame_id = 0;
    for (auto& [img_id, image] : images_) {
      Frame frame;
      frame.SetFrameId(frame_id);
      frame.SetRigId(0);
      frame.SetRigPtr(&rigs_[0]);
      frame.AddDataId(image.DataId());
      image.frame_id = frame_id;
      image.frame_ptr = nullptr; // Will set after emplacing
      frames_[frame_id] = frame;
      frame_id++;
    }

    // Set frame pointers
    for (auto& [img_id, image] : images_) {
      image.frame_ptr = &frames_[image.frame_id];
    }

    // Create image pairs in a chain: 0-1, 1-2, 2-3, ...
    for (int i = 0; i < num_images - 1; ++i) {
      image_t id1 = static_cast<image_t>(i);
      image_t id2 = static_cast<image_t>(i + 1);
      ImagePair pair(id1, id2, Rigid3d());
      pair.is_valid = true;
      view_graph_.image_pairs.emplace(pair.pair_id, pair);
    }
  }

  ViewGraph view_graph_;
  std::unordered_map<rig_t, Rig> rigs_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
  RotationAveragerOptions options_;
};

// Test with empty view graph - no image pairs
TEST_F(RotationAveragerTest_112, EmptyViewGraph_112) {
  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  // With no data, rotation averaging should fail or return false
  EXPECT_FALSE(result);
}

// Test with empty images and frames but non-empty view graph
TEST_F(RotationAveragerTest_112, EmptyImagesAndFrames_112) {
  ImagePair pair(0, 1, Rigid3d());
  pair.is_valid = true;
  view_graph_.image_pairs.emplace(pair.pair_id, pair);

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  EXPECT_FALSE(result);
}

// Test RotationAveragerOptions default construction
TEST_F(RotationAveragerTest_112, DefaultOptionsConstruction_112) {
  RotationAveragerOptions opts;
  EXPECT_TRUE(opts.use_stratified);
  EXPECT_FALSE(opts.skip_initialization);
  EXPECT_FALSE(opts.use_gravity);
}

// Test RotationAveragerOptions construction from base options
TEST_F(RotationAveragerTest_112, OptionsFromBaseConstruction_112) {
  RotationEstimatorOptions base_opts;
  base_opts.max_num_l1_iterations = 10;
  base_opts.skip_initialization = true;
  base_opts.use_gravity = true;

  RotationAveragerOptions opts(base_opts);
  EXPECT_EQ(opts.max_num_l1_iterations, 10);
  EXPECT_TRUE(opts.skip_initialization);
  EXPECT_TRUE(opts.use_gravity);
  // use_stratified should still be default
  EXPECT_TRUE(opts.use_stratified);
}

// Test with a minimal valid scene (2 images connected)
TEST_F(RotationAveragerTest_112, MinimalTwoImageScene_112) {
  CreateMinimalScene(2);

  // Register the frames/images
  for (auto& [fid, frame] : frames_) {
    frame.is_registered = true;
  }

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  // With a minimal valid scene, this should succeed
  EXPECT_TRUE(result);
}

// Test with three images forming a chain
TEST_F(RotationAveragerTest_112, ThreeImageChain_112) {
  CreateMinimalScene(3);

  for (auto& [fid, frame] : frames_) {
    frame.is_registered = true;
  }

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  EXPECT_TRUE(result);
}

// Test with all invalid pairs
TEST_F(RotationAveragerTest_112, AllInvalidPairs_112) {
  CreateMinimalScene(3);

  for (auto& [fid, frame] : frames_) {
    frame.is_registered = true;
  }

  // Mark all pairs as invalid
  for (auto& [pair_id, pair] : view_graph_.image_pairs) {
    pair.is_valid = false;
  }

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  // With all invalid pairs, likely fails
  EXPECT_FALSE(result);
}

// Test with gravity options enabled but no gravity info
TEST_F(RotationAveragerTest_112, GravityEnabledNoGravityInfo_112) {
  CreateMinimalScene(3);

  for (auto& [fid, frame] : frames_) {
    frame.is_registered = true;
  }

  options_.use_gravity = true;
  options_.use_stratified = true;

  // Images don't have gravity info, so it should fall through
  // to the non-gravity path
  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  EXPECT_TRUE(result);
}

// Test with use_stratified false
TEST_F(RotationAveragerTest_112, StratifiedDisabled_112) {
  CreateMinimalScene(3);

  for (auto& [fid, frame] : frames_) {
    frame.is_registered = true;
  }

  options_.use_stratified = false;
  options_.use_gravity = true;

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  EXPECT_TRUE(result);
}

// Test with skip_initialization set to true
TEST_F(RotationAveragerTest_112, SkipInitialization_112) {
  CreateMinimalScene(3);

  for (auto& [fid, frame] : frames_) {
    frame.is_registered = true;
  }

  options_.skip_initialization = true;

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  // skip_initialization changes the path but should still work
  // on a minimal valid scene
  EXPECT_TRUE(result);
}

// Test with unregistered images
TEST_F(RotationAveragerTest_112, UnregisteredImages_112) {
  CreateMinimalScene(3);

  // Don't register any frames
  for (auto& [fid, frame] : frames_) {
    frame.is_registered = false;
  }

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  // Unregistered images should cause failure
  EXPECT_FALSE(result);
}

// Test with single image (no pairs possible)
TEST_F(RotationAveragerTest_112, SingleImage_112) {
  CreateMinimalScene(1);

  for (auto& [fid, frame] : frames_) {
    frame.is_registered = true;
  }

  // No image pairs
  EXPECT_TRUE(view_graph_.image_pairs.empty());

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  EXPECT_FALSE(result);
}

// Test that options weight type can be set
TEST_F(RotationAveragerTest_112, OptionsWeightType_112) {
  CreateMinimalScene(3);

  for (auto& [fid, frame] : frames_) {
    frame.is_registered = true;
  }

  options_.use_weight = true;

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  EXPECT_TRUE(result);
}

// Test with larger scene (5 images)
TEST_F(RotationAveragerTest_112, FiveImageScene_112) {
  CreateMinimalScene(5);

  for (auto& [fid, frame] : frames_) {
    frame.is_registered = true;
  }

  // Add more connections to make it better connected
  ImagePair pair02(0, 2, Rigid3d());
  pair02.is_valid = true;
  view_graph_.image_pairs.emplace(pair02.pair_id, pair02);

  ImagePair pair13(1, 3, Rigid3d());
  pair13.is_valid = true;
  view_graph_.image_pairs.emplace(pair13.pair_id, pair13);

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  EXPECT_TRUE(result);
}

// Test with empty rigs map
TEST_F(RotationAveragerTest_112, EmptyRigs_112) {
  // Create images and frames without proper rig setup
  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  EXPECT_FALSE(result);
}

}  // namespace
}  // namespace glomap
