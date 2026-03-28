#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/rotation_initializer.h"
#include "glomap/types.h"

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>
#include <limits>
#include <unordered_map>

namespace glomap {
namespace {

class ConvertRotationsFromImageToRigTest_22 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test that the function returns true with empty inputs
TEST_F(ConvertRotationsFromImageToRigTest_22, EmptyInputsReturnsTrue_22) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);
}

// Test that the function returns true when there are rigs but no frames
TEST_F(ConvertRotationsFromImageToRigTest_22, RigsButNoFramesReturnsTrue_22) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  // Create a rig with a ref sensor and a non-ref sensor
  Rig rig;
  rig.SetRefSensorId(sensor_t(SensorType::CAMERA, 0));
  rigs[0] = rig;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);
}

// Test with a single-camera rig (no non-ref sensors) - should still return true
TEST_F(ConvertRotationsFromImageToRigTest_22, SingleCameraRigReturnsTrue_22) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  Rig rig;
  rig.SetRefSensorId(sensor_t(SensorType::CAMERA, 0));
  rigs[0] = rig;

  // Create an image for camera 0
  Image img;
  img.camera_id = 0;
  img.SetRegistered(true);
  images[0] = img;

  // Create a frame that references this rig
  Frame frame;
  frame.SetRigPtr(&rigs[0]);
  frame.AddImageId(data_t(DataType::IMAGE, 0));
  frames[0] = frame;

  Rigid3d identity;
  identity.rotation = Eigen::Quaterniond::Identity();
  identity.translation = Eigen::Vector3d::Zero();
  cam_from_worlds[0] = identity;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);
}

// Test with a two-camera rig where both cameras see identity rotation
TEST_F(ConvertRotationsFromImageToRigTest_22, TwoCameraRigIdentityRotations_22) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  // Create a rig with ref camera 0 and non-ref camera 1
  Rig rig;
  rig.SetRefSensorId(sensor_t(SensorType::CAMERA, 0));
  rig.AddNonRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs[0] = rig;

  // Create images
  Image img0;
  img0.camera_id = 0;
  img0.SetRegistered(true);
  images[0] = img0;

  Image img1;
  img1.camera_id = 1;
  img1.SetRegistered(true);
  images[1] = img1;

  // Both cameras have identity rotation
  Rigid3d identity;
  identity.rotation = Eigen::Quaterniond::Identity();
  identity.translation = Eigen::Vector3d::Zero();
  cam_from_worlds[0] = identity;
  cam_from_worlds[1] = identity;

  // Create a frame referencing both images
  Frame frame;
  frame.SetRigPtr(&rigs[0]);
  frame.AddImageId(data_t(DataType::IMAGE, 0));
  frame.AddImageId(data_t(DataType::IMAGE, 1));
  frames[0] = frame;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);

  // The relative rotation (cam1_from_ref_cam0) should be identity
  auto cam_from_rig_opt = rigs[0].MaybeSensorFromRig(
      sensor_t(SensorType::CAMERA, 1));
  ASSERT_TRUE(cam_from_rig_opt.has_value());

  Eigen::Quaterniond expected_rotation = Eigen::Quaterniond::Identity();
  EXPECT_NEAR(cam_from_rig_opt.value().rotation.w(), expected_rotation.w(), 1e-6);
  EXPECT_NEAR(cam_from_rig_opt.value().rotation.x(), expected_rotation.x(), 1e-6);
  EXPECT_NEAR(cam_from_rig_opt.value().rotation.y(), expected_rotation.y(), 1e-6);
  EXPECT_NEAR(cam_from_rig_opt.value().rotation.z(), expected_rotation.z(), 1e-6);
}

// Test with a two-camera rig where camera 1 has a 90-degree rotation relative to camera 0
TEST_F(ConvertRotationsFromImageToRigTest_22, TwoCameraRigWithRelativeRotation_22) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  Rig rig;
  rig.SetRefSensorId(sensor_t(SensorType::CAMERA, 0));
  rig.AddNonRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs[0] = rig;

  Image img0;
  img0.camera_id = 0;
  img0.SetRegistered(true);
  images[0] = img0;

  Image img1;
  img1.camera_id = 1;
  img1.SetRegistered(true);
  images[1] = img1;

  // Camera 0 has identity rotation
  Rigid3d pose0;
  pose0.rotation = Eigen::Quaterniond::Identity();
  pose0.translation = Eigen::Vector3d::Zero();
  cam_from_worlds[0] = pose0;

  // Camera 1 has 90-degree rotation around Z axis
  Eigen::AngleAxisd rotation_90z(M_PI / 2.0, Eigen::Vector3d::UnitZ());
  Rigid3d pose1;
  pose1.rotation = Eigen::Quaterniond(rotation_90z);
  pose1.translation = Eigen::Vector3d::Zero();
  cam_from_worlds[1] = pose1;

  Frame frame;
  frame.SetRigPtr(&rigs[0]);
  frame.AddImageId(data_t(DataType::IMAGE, 0));
  frame.AddImageId(data_t(DataType::IMAGE, 1));
  frames[0] = frame;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);

  auto cam_from_rig_opt = rigs[0].MaybeSensorFromRig(
      sensor_t(SensorType::CAMERA, 1));
  ASSERT_TRUE(cam_from_rig_opt.has_value());

  // Expected: cam1_from_cam0 = cam1_from_world * world_from_cam0
  //         = rotation_90z * identity = rotation_90z
  Eigen::Quaterniond expected(rotation_90z);
  double dot = std::abs(cam_from_rig_opt.value().rotation.dot(expected));
  EXPECT_NEAR(dot, 1.0, 1e-6);
}

// Test that the translation in sensor_from_rig is NaN
TEST_F(ConvertRotationsFromImageToRigTest_22, SensorFromRigTranslationIsNaN_22) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  Rig rig;
  rig.SetRefSensorId(sensor_t(SensorType::CAMERA, 0));
  rig.AddNonRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs[0] = rig;

  Image img0;
  img0.camera_id = 0;
  img0.SetRegistered(true);
  images[0] = img0;

  Image img1;
  img1.camera_id = 1;
  img1.SetRegistered(true);
  images[1] = img1;

  Rigid3d identity;
  identity.rotation = Eigen::Quaterniond::Identity();
  identity.translation = Eigen::Vector3d::Zero();
  cam_from_worlds[0] = identity;
  cam_from_worlds[1] = identity;

  Frame frame;
  frame.SetRigPtr(&rigs[0]);
  frame.AddImageId(data_t(DataType::IMAGE, 0));
  frame.AddImageId(data_t(DataType::IMAGE, 1));
  frames[0] = frame;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);

  auto cam_from_rig_opt = rigs[0].MaybeSensorFromRig(
      sensor_t(SensorType::CAMERA, 1));
  ASSERT_TRUE(cam_from_rig_opt.has_value());

  // Translation should be NaN
  EXPECT_TRUE(std::isnan(cam_from_rig_opt.value().translation.x()));
  EXPECT_TRUE(std::isnan(cam_from_rig_opt.value().translation.y()));
  EXPECT_TRUE(std::isnan(cam_from_rig_opt.value().translation.z()));
}

// Test with unregistered images - they should be skipped
TEST_F(ConvertRotationsFromImageToRigTest_22, UnregisteredImagesAreSkipped_22) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  Rig rig;
  rig.SetRefSensorId(sensor_t(SensorType::CAMERA, 0));
  rig.AddNonRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs[0] = rig;

  // Ref image is unregistered
  Image img0;
  img0.camera_id = 0;
  img0.SetRegistered(false);
  images[0] = img0;

  Image img1;
  img1.camera_id = 1;
  img1.SetRegistered(true);
  images[1] = img1;

  Rigid3d identity;
  identity.rotation = Eigen::Quaterniond::Identity();
  identity.translation = Eigen::Vector3d::Zero();
  cam_from_worlds[0] = identity;
  cam_from_worlds[1] = identity;

  Frame frame;
  frame.SetRigPtr(&rigs[0]);
  frame.AddImageId(data_t(DataType::IMAGE, 0));
  frame.AddImageId(data_t(DataType::IMAGE, 1));
  frames[0] = frame;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);

  // Since ref image is unregistered, no relative rotation should be computed
  auto cam_from_rig_opt = rigs[0].MaybeSensorFromRig(
      sensor_t(SensorType::CAMERA, 1));
  EXPECT_FALSE(cam_from_rig_opt.has_value());
}

// Test with multiple frames contributing to the same relative rotation
TEST_F(ConvertRotationsFromImageToRigTest_22, MultipleFramesAverageRotation_22) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  Rig rig;
  rig.SetRefSensorId(sensor_t(SensorType::CAMERA, 0));
  rig.AddNonRefSensor(sensor_t(SensorType::CAMERA, 1));
  rigs[0] = rig;

  // Frame 0: images 0 and 1
  Image img0;
  img0.camera_id = 0;
  img0.SetRegistered(true);
  images[0] = img0;

  Image img1;
  img1.camera_id = 1;
  img1.SetRegistered(true);
  images[1] = img1;

  // Frame 1: images 2 and 3
  Image img2;
  img2.camera_id = 0;
  img2.SetRegistered(true);
  images[2] = img2;

  Image img3;
  img3.camera_id = 1;
  img3.SetRegistered(true);
  images[3] = img3;

  // Both frames have identity rotation for all cameras
  Rigid3d identity;
  identity.rotation = Eigen::Quaterniond::Identity();
  identity.translation = Eigen::Vector3d::Zero();
  cam_from_worlds[0] = identity;
  cam_from_worlds[1] = identity;
  cam_from_worlds[2] = identity;
  cam_from_worlds[3] = identity;

  Frame frame0;
  frame0.SetRigPtr(&rigs[0]);
  frame0.AddImageId(data_t(DataType::IMAGE, 0));
  frame0.AddImageId(data_t(DataType::IMAGE, 1));
  frames[0] = frame0;

  Frame frame1;
  frame1.SetRigPtr(&rigs[0]);
  frame1.AddImageId(data_t(DataType::IMAGE, 2));
  frame1.AddImageId(data_t(DataType::IMAGE, 3));
  frames[1] = frame1;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);

  auto cam_from_rig_opt = rigs[0].MaybeSensorFromRig(
      sensor_t(SensorType::CAMERA, 1));
  ASSERT_TRUE(cam_from_rig_opt.has_value());

  // Average of identity rotations should be identity
  Eigen::Quaterniond expected = Eigen::Quaterniond::Identity();
  double dot = std::abs(cam_from_rig_opt.value().rotation.dot(expected));
  EXPECT_NEAR(dot, 1.0, 1e-6);
}

// Test frame with missing image in the images map
TEST_F(ConvertRotationsFromImageToRigTest_22, MissingImageInMapIsSkipped_22) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  Rig rig;
  rig.SetRefSensorId(sensor_t(SensorType::CAMERA, 0));
  rigs[0] = rig;

  // Frame references image 0 but it's not in the images map
  Frame frame;
  frame.SetRigPtr(&rigs[0]);
  frame.AddImageId(data_t(DataType::IMAGE, 0));
  frames[0] = frame;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);
}

// Test that sensor_from_rig is already set - the function skips it
TEST_F(ConvertRotationsFromImageToRigTest_22, AlreadySetSensorFromRigIsSkipped_22) {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  Rig rig;
  rig.SetRefSensorId(sensor_t(SensorType::CAMERA, 0));
  rig.AddNonRefSensor(sensor_t(SensorType::CAMERA, 1));

  // Pre-set the sensor_from_rig for camera 1
  Rigid3d preset;
  preset.rotation = Eigen::Quaterniond(
      Eigen::AngleAxisd(M_PI / 4.0, Eigen::Vector3d::UnitX()));
  preset.translation = Eigen::Vector3d(1, 2, 3);
  rig.SetSensorFromRig(sensor_t(SensorType::CAMERA, 1), preset);
  rigs[0] = rig;

  Image img0;
  img0.camera_id = 0;
  img0.SetRegistered(true);
  images[0] = img0;

  Image img1;
  img1.camera_id = 1;
  img1.SetRegistered(true);
  images[1] = img1;

  Rigid3d identity;
  identity.rotation = Eigen::Quaterniond::Identity();
  identity.translation = Eigen::Vector3d::Zero();
  cam_from_worlds[0] = identity;
  cam_from_worlds[1] = identity;

  Frame frame;
  frame.SetRigPtr(&rigs[0]);
  frame.AddImageId(data_t(DataType::IMAGE, 0));
  frame.AddImageId(data_t(DataType::IMAGE, 1));
  frames[0] = frame;

  bool result = ConvertRotationsFromImageToRig(
      cam_from_worlds, images, rigs, frames);
  EXPECT_TRUE(result);

  // Since sensor_from_rig was already set, the code skips this camera
  // and no new relative rotation is computed. The existing one should remain.
  auto cam_from_rig_opt = rigs[0].MaybeSensorFromRig(
      sensor_t(SensorType::CAMERA, 1));
  ASSERT_TRUE(cam_from_rig_opt.has_value());
}

}  // namespace
}  // namespace glomap
