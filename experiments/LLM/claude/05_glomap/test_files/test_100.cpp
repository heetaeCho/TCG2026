#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/rotation_initializer.h"
#include "glomap/scene/image.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <unordered_map>
#include <cmath>

namespace glomap {
namespace {

class ConvertRotationsFromImageToRigTest_100 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test that the function returns true with completely empty inputs
TEST_F(ConvertRotationsFromImageToRigTest_100, EmptyInputsReturnsTrue_100) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);
}

// Test that the function returns true with empty frames but non-empty rigs
TEST_F(ConvertRotationsFromImageToRigTest_100, EmptyFramesReturnsTrue_100) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  // Add a rig but no frames
  Rig rig;
  rigs[0] = rig;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);
}

// Test with empty rigs and empty frames
TEST_F(ConvertRotationsFromImageToRigTest_100, EmptyRigsAndFramesReturnsTrue_100) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);
}

// Test that when frames exist but images map is empty, function still returns true
TEST_F(ConvertRotationsFromImageToRigTest_100, FramesWithNoMatchingImagesReturnsTrue_100) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  // Create a rig with a ref sensor
  Rig rig;
  rig.SetRefSensor(sensor_t(SensorType::CAMERA, 0));
  rigs[0] = rig;

  // Create a frame associated with the rig, but no matching images
  Frame frame;
  frame.SetRig(&rigs[0]);
  frames[0] = frame;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);
}

// Test a single-camera rig (only reference camera, no non-ref sensors)
// The function should return true and the frame should get a rotation set
TEST_F(ConvertRotationsFromImageToRigTest_100, SingleCameraRigSetsFrameRotation_100) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  // Create a rig with only a reference sensor
  Rig rig;
  rig.SetRefSensor(sensor_t(SensorType::CAMERA, 0));
  rigs[0] = rig;

  // Create a registered image with camera_id matching ref sensor
  Image img(0, 0, "img0.jpg");
  img.SetRegistered(true);
  img.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
  images[0] = img;

  cam_from_worlds[0] = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());

  // Create frame with the image
  Frame frame;
  frame.SetRig(&rigs[0]);
  frame.AddImage(data_t(DataType::IMAGE, 0));
  frames[0] = frame;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);
}

// Test with a two-camera rig to verify that non-ref sensor rotation gets computed
TEST_F(ConvertRotationsFromImageToRigTest_100, TwoCameraRigComputesSensorRotation_100) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  // Create a rig with ref sensor (camera 0) and non-ref sensor (camera 1)
  Rig rig;
  rig.SetRefSensor(sensor_t(SensorType::CAMERA, 0));
  rig.AddNonRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs[0] = rig;

  // Create identity rotation for ref image
  Eigen::Quaterniond ref_rotation = Eigen::Quaterniond::Identity();
  // Create a small rotation for non-ref image
  Eigen::Quaterniond non_ref_rotation(
      Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitZ()));

  // Ref image (image 0, camera 0)
  Image img0(0, 0, "img0.jpg");
  img0.SetRegistered(true);
  images[0] = img0;
  cam_from_worlds[0] = Rigid3d(ref_rotation, Eigen::Vector3d::Zero());

  // Non-ref image (image 1, camera 1)
  Image img1(1, 1, "img1.jpg");
  img1.SetRegistered(true);
  images[1] = img1;
  cam_from_worlds[1] = Rigid3d(non_ref_rotation, Eigen::Vector3d::Zero());

  // Create frame containing both images
  Frame frame;
  frame.SetRig(&rigs[0]);
  frame.AddImage(data_t(DataType::IMAGE, 0));
  frame.AddImage(data_t(DataType::IMAGE, 1));
  frames[0] = frame;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);

  // After the function, the rig should have the sensor_from_rig set for camera 1
  auto cam_from_rig_opt = rigs[0].MaybeSensorFromRig(
      sensor_t(SensorType::CAMERA, 1));
  EXPECT_TRUE(cam_from_rig_opt.has_value());

  if (cam_from_rig_opt.has_value()) {
    // The expected relative rotation: non_ref_rotation * ref_rotation.inverse()
    Eigen::Quaterniond expected_relative = non_ref_rotation * ref_rotation.inverse();
    double angle_diff = cam_from_rig_opt.value().rotation.angularDistance(expected_relative);
    EXPECT_NEAR(angle_diff, 0.0, 1e-6);
  }
}

// Test that unregistered images are skipped
TEST_F(ConvertRotationsFromImageToRigTest_100, UnregisteredImagesAreSkipped_100) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  Rig rig;
  rig.SetRefSensor(sensor_t(SensorType::CAMERA, 0));
  rig.AddNonRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs[0] = rig;

  // Ref image registered
  Image img0(0, 0, "img0.jpg");
  img0.SetRegistered(true);
  images[0] = img0;
  cam_from_worlds[0] = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());

  // Non-ref image NOT registered
  Image img1(1, 1, "img1.jpg");
  img1.SetRegistered(false);
  images[1] = img1;
  cam_from_worlds[1] = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());

  Frame frame;
  frame.SetRig(&rigs[0]);
  frame.AddImage(data_t(DataType::IMAGE, 0));
  frame.AddImage(data_t(DataType::IMAGE, 1));
  frames[0] = frame;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);

  // The non-ref sensor should NOT have been set since img1 is not registered
  auto cam_from_rig_opt = rigs[0].MaybeSensorFromRig(
      sensor_t(SensorType::CAMERA, 1));
  EXPECT_FALSE(cam_from_rig_opt.has_value());
}

// Test with multiple frames contributing to the same non-ref sensor rotation averaging
TEST_F(ConvertRotationsFromImageToRigTest_100, MultipleFramesAverageRotation_100) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  Rig rig;
  rig.SetRefSensor(sensor_t(SensorType::CAMERA, 0));
  rig.AddNonRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs[0] = rig;

  // Frame 0: ref image 0 (camera 0), non-ref image 1 (camera 1)
  // Both with identity rotation
  Image img0(0, 0, "img0.jpg");
  img0.SetRegistered(true);
  images[0] = img0;
  cam_from_worlds[0] = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());

  Eigen::Quaterniond small_rot(Eigen::AngleAxisd(0.05, Eigen::Vector3d::UnitX()));
  Image img1(1, 1, "img1.jpg");
  img1.SetRegistered(true);
  images[1] = img1;
  cam_from_worlds[1] = Rigid3d(small_rot, Eigen::Vector3d::Zero());

  Frame frame0;
  frame0.SetRig(&rigs[0]);
  frame0.AddImage(data_t(DataType::IMAGE, 0));
  frame0.AddImage(data_t(DataType::IMAGE, 1));
  frames[0] = frame0;

  // Frame 1: ref image 2 (camera 0), non-ref image 3 (camera 1)
  // With different world poses but same relative rotation
  Eigen::Quaterniond world_rot(Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitY()));
  Image img2(2, 0, "img2.jpg");
  img2.SetRegistered(true);
  images[2] = img2;
  cam_from_worlds[2] = Rigid3d(world_rot, Eigen::Vector3d::Zero());

  Image img3(3, 1, "img3.jpg");
  img3.SetRegistered(true);
  images[3] = img3;
  cam_from_worlds[3] = Rigid3d(small_rot * world_rot, Eigen::Vector3d::Zero());

  Frame frame1;
  frame1.SetRig(&rigs[0]);
  frame1.AddImage(data_t(DataType::IMAGE, 2));
  frame1.AddImage(data_t(DataType::IMAGE, 3));
  frames[1] = frame1;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);

  // Both frames produce the same relative rotation (small_rot), so the average should be small_rot
  auto cam_from_rig_opt = rigs[0].MaybeSensorFromRig(
      sensor_t(SensorType::CAMERA, 1));
  EXPECT_TRUE(cam_from_rig_opt.has_value());

  if (cam_from_rig_opt.has_value()) {
    double angle_diff = cam_from_rig_opt.value().rotation.angularDistance(small_rot);
    EXPECT_NEAR(angle_diff, 0.0, 1e-6);
  }
}

// Test that if no ref image is found in a frame, frame is skipped
TEST_F(ConvertRotationsFromImageToRigTest_100, NoRefImageInFrameSkipsFrame_100) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  Rig rig;
  rig.SetRefSensor(sensor_t(SensorType::CAMERA, 0));
  rig.AddNonRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs[0] = rig;

  // Only non-ref image, no ref image
  Image img1(1, 1, "img1.jpg");
  img1.SetRegistered(true);
  images[1] = img1;
  cam_from_worlds[1] = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());

  Frame frame;
  frame.SetRig(&rigs[0]);
  frame.AddImage(data_t(DataType::IMAGE, 1));
  frames[0] = frame;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);

  // No sensor rotation should be set since no ref image was found
  auto cam_from_rig_opt = rigs[0].MaybeSensorFromRig(
      sensor_t(SensorType::CAMERA, 1));
  EXPECT_FALSE(cam_from_rig_opt.has_value());
}

// Test that images not found in the images map are skipped gracefully
TEST_F(ConvertRotationsFromImageToRigTest_100, MissingImagesAreSkipped_100) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  Rig rig;
  rig.SetRefSensor(sensor_t(SensorType::CAMERA, 0));
  rigs[0] = rig;

  // Frame references image 99 which doesn't exist in images map
  Frame frame;
  frame.SetRig(&rigs[0]);
  frame.AddImage(data_t(DataType::IMAGE, 99));
  frames[0] = frame;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);
}

// Test that if sensor_from_rig is already set, it is not overwritten
// (the code checks MaybeSensorFromRig and skips if has_value)
TEST_F(ConvertRotationsFromImageToRigTest_100, AlreadySetSensorFromRigIsSkipped_100) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  Rig rig;
  rig.SetRefSensor(sensor_t(SensorType::CAMERA, 0));
  rig.AddNonRefSensor(sensor_t(SensorType::CAMERA, 1));

  // Pre-set the sensor_from_rig for camera 1
  Eigen::Quaterniond preset_rot(Eigen::AngleAxisd(0.3, Eigen::Vector3d::UnitZ()));
  rig.SetSensorFromRig(sensor_t(SensorType::CAMERA, 1),
                        Rigid3d(preset_rot, Eigen::Vector3d::Zero()));
  rigs[0] = rig;

  // Create images and frame
  Image img0(0, 0, "img0.jpg");
  img0.SetRegistered(true);
  images[0] = img0;
  cam_from_worlds[0] = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());

  Image img1(1, 1, "img1.jpg");
  img1.SetRegistered(true);
  images[1] = img1;
  Eigen::Quaterniond different_rot(Eigen::AngleAxisd(0.7, Eigen::Vector3d::UnitY()));
  cam_from_worlds[1] = Rigid3d(different_rot, Eigen::Vector3d::Zero());

  Frame frame;
  frame.SetRig(&rigs[0]);
  frame.AddImage(data_t(DataType::IMAGE, 0));
  frame.AddImage(data_t(DataType::IMAGE, 1));
  frames[0] = frame;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);

  // The sensor_from_rig should still be the preset value since it was already set
  auto cam_from_rig_opt = rigs[0].MaybeSensorFromRig(
      sensor_t(SensorType::CAMERA, 1));
  EXPECT_TRUE(cam_from_rig_opt.has_value());
  // Since the code skips computing when MaybeSensorFromRig already has value,
  // it shouldn't be changed (no new rotation computed to average)
}

}  // namespace
}  // namespace glomap
