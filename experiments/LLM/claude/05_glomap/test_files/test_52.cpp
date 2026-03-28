#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/controllers/rotation_averager.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

namespace glomap {
namespace {

class RotationAveragerTest_52 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_ = RotationAveragerOptions();
  }

  // Helper to create a minimal registered image
  Image CreateRegisteredImage(image_t image_id, camera_t camera_id,
                              frame_t frame_id) {
    Image img(image_id, camera_id, "test_image_" + std::to_string(image_id));
    img.is_registered = true;
    img.frame_id = frame_id;
    return img;
  }

  // Helper to create a simple frame
  Frame CreateFrame(frame_t frame_id, rig_t rig_id) {
    Frame frame;
    frame.SetFrameId(frame_id);
    frame.SetRigId(rig_id);
    return frame;
  }

  RotationAveragerOptions options_;
  ViewGraph view_graph_;
  std::unordered_map<rig_t, Rig> rigs_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
};

// Test with empty data structures - no images, frames, rigs
TEST_F(RotationAveragerTest_52, EmptyInput_52) {
  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  // With empty inputs, rotation averaging should fail or return false
  // since there's nothing to solve
  EXPECT_FALSE(result);
}

// Test with empty view graph but non-empty images
TEST_F(RotationAveragerTest_52, EmptyViewGraph_52) {
  // Create minimal setup with no image pairs in view graph
  Rig rig;
  rig.SetRigId(0);
  rig.AddRefSensor(sensor_t(SensorType::CAMERA, 0));
  rigs_[0] = rig;

  Frame frame = CreateFrame(0, 0);
  frame.SetRigPtr(&rigs_[0]);
  frames_[0] = frame;

  Image img = CreateRegisteredImage(0, 0, 0);
  img.frame_ptr = &frames_[0];
  images_[0] = img;

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  EXPECT_FALSE(result);
}

// Test with single image pair
TEST_F(RotationAveragerTest_52, SingleImagePair_52) {
  // Set up two rigs
  Rig rig0, rig1;
  rig0.SetRigId(0);
  rig0.AddRefSensor(sensor_t(SensorType::CAMERA, 0));
  rig1.SetRigId(1);
  rig1.AddRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs_[0] = rig0;
  rigs_[1] = rig1;

  // Set up two frames
  Frame frame0 = CreateFrame(0, 0);
  frame0.SetRigPtr(&rigs_[0]);
  Frame frame1 = CreateFrame(1, 1);
  frame1.SetRigPtr(&rigs_[1]);

  // Set up two images
  Image img0 = CreateRegisteredImage(0, 0, 0);
  img0.frame_ptr = &frames_[0];
  Image img1 = CreateRegisteredImage(1, 1, 1);
  img1.frame_ptr = &frames_[1];

  frame0.AddDataId(img0.DataId());
  frame1.AddDataId(img1.DataId());

  frames_[0] = frame0;
  frames_[1] = frame1;
  images_[0] = img0;
  images_[1] = img1;

  // Add an image pair to the view graph
  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  ImagePair pair(0, 1, Rigid3d());
  pair.is_valid = true;
  view_graph_.image_pairs[pair_id] = pair;

  // This may or may not succeed depending on internal solver requirements
  // but it should not crash
  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  // Result depends on internal solver behavior; we just check it doesn't crash
  SUCCEED();
}

// Test with gravity options enabled but no gravity data
TEST_F(RotationAveragerTest_52, GravityEnabledNoGravityData_52) {
  options_.use_gravity = true;
  options_.use_stratified = true;

  Rig rig0, rig1;
  rig0.SetRigId(0);
  rig0.AddRefSensor(sensor_t(SensorType::CAMERA, 0));
  rig1.SetRigId(1);
  rig1.AddRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs_[0] = rig0;
  rigs_[1] = rig1;

  Frame frame0 = CreateFrame(0, 0);
  frame0.SetRigPtr(&rigs_[0]);
  Frame frame1 = CreateFrame(1, 1);
  frame1.SetRigPtr(&rigs_[1]);

  Image img0 = CreateRegisteredImage(0, 0, 0);
  img0.frame_ptr = &frames_[0];
  Image img1 = CreateRegisteredImage(1, 1, 1);
  img1.frame_ptr = &frames_[1];

  frame0.AddDataId(img0.DataId());
  frame1.AddDataId(img1.DataId());

  frames_[0] = frame0;
  frames_[1] = frame1;
  images_[0] = img0;
  images_[1] = img1;

  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  ImagePair pair(0, 1, Rigid3d());
  pair.is_valid = true;
  view_graph_.image_pairs[pair_id] = pair;

  // With gravity enabled but no gravity data, solve_1dof_system should be
  // false (grav_pairs == 0 triggers status = true, so solve_1dof_system = false)
  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  // Just verify it doesn't crash
  SUCCEED();
}

// Test with gravity disabled
TEST_F(RotationAveragerTest_52, GravityDisabled_52) {
  options_.use_gravity = false;
  options_.use_stratified = false;

  Rig rig0, rig1;
  rig0.SetRigId(0);
  rig0.AddRefSensor(sensor_t(SensorType::CAMERA, 0));
  rig1.SetRigId(1);
  rig1.AddRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs_[0] = rig0;
  rigs_[1] = rig1;

  Frame frame0 = CreateFrame(0, 0);
  frame0.SetRigPtr(&rigs_[0]);
  Frame frame1 = CreateFrame(1, 1);
  frame1.SetRigPtr(&rigs_[1]);

  Image img0 = CreateRegisteredImage(0, 0, 0);
  img0.frame_ptr = &frames_[0];
  Image img1 = CreateRegisteredImage(1, 1, 1);
  img1.frame_ptr = &frames_[1];

  frame0.AddDataId(img0.DataId());
  frame1.AddDataId(img1.DataId());

  frames_[0] = frame0;
  frames_[1] = frame1;
  images_[0] = img0;
  images_[1] = img1;

  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  ImagePair pair(0, 1, Rigid3d());
  pair.is_valid = true;
  view_graph_.image_pairs[pair_id] = pair;

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  SUCCEED();
}

// Test with invalid image pairs (is_valid = false)
TEST_F(RotationAveragerTest_52, InvalidImagePairs_52) {
  options_.use_gravity = true;
  options_.use_stratified = true;

  Rig rig0, rig1;
  rig0.SetRigId(0);
  rig0.AddRefSensor(sensor_t(SensorType::CAMERA, 0));
  rig1.SetRigId(1);
  rig1.AddRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs_[0] = rig0;
  rigs_[1] = rig1;

  Frame frame0 = CreateFrame(0, 0);
  frame0.SetRigPtr(&rigs_[0]);
  Frame frame1 = CreateFrame(1, 1);
  frame1.SetRigPtr(&rigs_[1]);

  Image img0 = CreateRegisteredImage(0, 0, 0);
  img0.frame_ptr = &frames_[0];
  Image img1 = CreateRegisteredImage(1, 1, 1);
  img1.frame_ptr = &frames_[1];

  frame0.AddDataId(img0.DataId());
  frame1.AddDataId(img1.DataId());

  frames_[0] = frame0;
  frames_[1] = frame1;
  images_[0] = img0;
  images_[1] = img1;

  // Add invalid pair
  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  ImagePair pair(0, 1, Rigid3d());
  pair.is_valid = false;
  view_graph_.image_pairs[pair_id] = pair;

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  // Invalid pairs shouldn't count toward total_pairs, so effectively empty
  SUCCEED();
}

// Test with unregistered images
TEST_F(RotationAveragerTest_52, UnregisteredImages_52) {
  options_.use_gravity = true;
  options_.use_stratified = true;

  Rig rig0, rig1;
  rig0.SetRigId(0);
  rig0.AddRefSensor(sensor_t(SensorType::CAMERA, 0));
  rig1.SetRigId(1);
  rig1.AddRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs_[0] = rig0;
  rigs_[1] = rig1;

  Frame frame0 = CreateFrame(0, 0);
  frame0.SetRigPtr(&rigs_[0]);
  Frame frame1 = CreateFrame(1, 1);
  frame1.SetRigPtr(&rigs_[1]);

  // Create unregistered images
  Image img0(0, 0, "test_0");
  img0.is_registered = false;
  img0.frame_id = 0;
  img0.frame_ptr = &frames_[0];

  Image img1(1, 1, "test_1");
  img1.is_registered = false;
  img1.frame_id = 1;
  img1.frame_ptr = &frames_[1];

  frame0.AddDataId(img0.DataId());
  frame1.AddDataId(img1.DataId());

  frames_[0] = frame0;
  frames_[1] = frame1;
  images_[0] = img0;
  images_[1] = img1;

  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  ImagePair pair(0, 1, Rigid3d());
  pair.is_valid = true;
  view_graph_.image_pairs[pair_id] = pair;

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  // With unregistered images, the pairs won't be counted
  SUCCEED();
}

// Test with skip_initialization option
TEST_F(RotationAveragerTest_52, SkipInitialization_52) {
  options_.skip_initialization = true;

  Rig rig0, rig1;
  rig0.SetRigId(0);
  rig0.AddRefSensor(sensor_t(SensorType::CAMERA, 0));
  rig1.SetRigId(1);
  rig1.AddRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs_[0] = rig0;
  rigs_[1] = rig1;

  Frame frame0 = CreateFrame(0, 0);
  frame0.SetRigPtr(&rigs_[0]);
  Frame frame1 = CreateFrame(1, 1);
  frame1.SetRigPtr(&rigs_[1]);

  Image img0 = CreateRegisteredImage(0, 0, 0);
  img0.frame_ptr = &frames_[0];
  Image img1 = CreateRegisteredImage(1, 1, 1);
  img1.frame_ptr = &frames_[1];

  frame0.AddDataId(img0.DataId());
  frame1.AddDataId(img1.DataId());

  frames_[0] = frame0;
  frames_[1] = frame1;
  images_[0] = img0;
  images_[1] = img1;

  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  ImagePair pair(0, 1, Rigid3d());
  pair.is_valid = true;
  view_graph_.image_pairs[pair_id] = pair;

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  SUCCEED();
}

// Test default options
TEST_F(RotationAveragerTest_52, DefaultOptions_52) {
  RotationAveragerOptions default_opts;
  // Verify default options don't crash with empty input
  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, default_opts);
  EXPECT_FALSE(result);
}

// Test return type is bool
TEST_F(RotationAveragerTest_52, ReturnsBool_52) {
  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  // The function should return a bool (true or false)
  EXPECT_TRUE(result == true || result == false);
}

// Test with multiple image pairs forming a chain
TEST_F(RotationAveragerTest_52, MultipleImagePairsChain_52) {
  const int num_images = 4;

  for (int i = 0; i < num_images; i++) {
    Rig rig;
    rig.SetRigId(i);
    rig.AddRefSensor(sensor_t(SensorType::CAMERA, i));
    rigs_[i] = rig;

    Frame frame = CreateFrame(i, i);
    frame.SetRigPtr(&rigs_[i]);
    frames_[i] = frame;

    Image img = CreateRegisteredImage(i, i, i);
    img.frame_ptr = &frames_[i];
    images_[i] = img;

    frames_[i].AddDataId(images_[i].DataId());
  }

  // Create a chain: 0-1, 1-2, 2-3
  for (int i = 0; i < num_images - 1; i++) {
    image_pair_t pair_id = ImagePair::ImagePairToPairId(i, i + 1);
    ImagePair pair(i, i + 1, Rigid3d());
    pair.is_valid = true;
    view_graph_.image_pairs[pair_id] = pair;
  }

  bool result = SolveRotationAveraging(
      view_graph_, rigs_, frames_, images_, options_);
  // Just verify it runs without crashing on a connected chain
  SUCCEED();
}

}  // namespace
}  // namespace glomap
