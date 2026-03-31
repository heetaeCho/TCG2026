#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/io/colmap_converter.h"
#include "glomap/scene/types_sfm.h"

#include <unordered_map>

namespace glomap {
namespace {

class CreateFrameForImageTest_123 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up a default camera-from-world transformation (identity)
    cam_from_world_ = Rigid3d();
  }

  Rigid3d cam_from_world_;
  std::unordered_map<rig_t, Rig> rigs_;
  std::unordered_map<frame_t, Frame> frames_;
};

// Test that when frame_id and rig_id are invalid, defaults to image_id and camera_id
TEST_F(CreateFrameForImageTest_123, DefaultFrameAndRigIds_123) {
  Image image(42, 7, "test.jpg");
  
  CreateFrameForImage(cam_from_world_, image, rigs_, frames_,
                      colmap::kInvalidRigId, colmap::kInvalidFrameId);
  
  // frame_id should default to image_id
  EXPECT_EQ(image.frame_id, 42);
  // Frame should exist in the frames map
  EXPECT_TRUE(frames_.find(42) != frames_.end());
  // Frame pointer should be set
  EXPECT_NE(image.frame_ptr, nullptr);
  EXPECT_EQ(image.frame_ptr, &frames_[42]);
}

// Test that when explicit frame_id and rig_id are provided, they are used
TEST_F(CreateFrameForImageTest_123, ExplicitFrameAndRigIds_123) {
  Image image(10, 5, "test.jpg");
  
  Rig rig;
  rigs_[99] = rig;
  
  CreateFrameForImage(cam_from_world_, image, rigs_, frames_, 99, 200);
  
  EXPECT_EQ(image.frame_id, 200);
  EXPECT_TRUE(frames_.find(200) != frames_.end());
  EXPECT_NE(image.frame_ptr, nullptr);
  EXPECT_EQ(image.frame_ptr, &frames_[200]);
}

// Test that when rig exists in the map, the frame's rig pointer is set
TEST_F(CreateFrameForImageTest_123, RigExistsInMap_123) {
  Image image(1, 2, "img.jpg");
  
  Rig rig;
  rigs_[2] = rig;
  
  CreateFrameForImage(cam_from_world_, image, rigs_, frames_,
                      colmap::kInvalidRigId, colmap::kInvalidFrameId);
  
  // When rig_id is invalid, it defaults to camera_id = 2
  // Rig with id 2 exists, so frame's rig_ptr should be non-null
  ASSERT_TRUE(frames_.find(1) != frames_.end());
  Frame& frame = frames_[1];
  // The frame should have rig_id = 2 (camera_id)
  EXPECT_EQ(frame.GetRigId(), 2);
}

// Test that when rig does NOT exist in the map, the frame's rig pointer is null
TEST_F(CreateFrameForImageTest_123, RigNotInMap_123) {
  Image image(1, 2, "img.jpg");
  
  // Don't add any rig to the map
  CreateFrameForImage(cam_from_world_, image, rigs_, frames_,
                      colmap::kInvalidRigId, colmap::kInvalidFrameId);
  
  ASSERT_TRUE(frames_.find(1) != frames_.end());
  Frame& frame = frames_[1];
  EXPECT_EQ(frame.GetRigPtr(), nullptr);
}

// Test that the frame stores the correct rig-from-world transformation
TEST_F(CreateFrameForImageTest_123, RigFromWorldIsSet_123) {
  Image image(5, 3, "img.jpg");
  
  // Create a non-identity transformation
  Eigen::Quaterniond q(Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitZ()));
  Eigen::Vector3d t(1.0, 2.0, 3.0);
  Rigid3d custom_transform(q, t);
  
  CreateFrameForImage(custom_transform, image, rigs_, frames_,
                      colmap::kInvalidRigId, colmap::kInvalidFrameId);
  
  ASSERT_TRUE(frames_.find(5) != frames_.end());
  Frame& frame = frames_[5];
  
  Rigid3d stored = frame.GetRigFromWorld();
  EXPECT_NEAR(stored.translation().x(), 1.0, 1e-10);
  EXPECT_NEAR(stored.translation().y(), 2.0, 1e-10);
  EXPECT_NEAR(stored.translation().z(), 3.0, 1e-10);
}

// Test that calling the function multiple times with different images creates separate frames
TEST_F(CreateFrameForImageTest_123, MultipleImagesCreateSeparateFrames_123) {
  Image image1(1, 10, "img1.jpg");
  Image image2(2, 20, "img2.jpg");
  
  CreateFrameForImage(cam_from_world_, image1, rigs_, frames_,
                      colmap::kInvalidRigId, colmap::kInvalidFrameId);
  CreateFrameForImage(cam_from_world_, image2, rigs_, frames_,
                      colmap::kInvalidRigId, colmap::kInvalidFrameId);
  
  EXPECT_EQ(frames_.size(), 2u);
  EXPECT_TRUE(frames_.find(1) != frames_.end());
  EXPECT_TRUE(frames_.find(2) != frames_.end());
  
  EXPECT_EQ(image1.frame_id, 1);
  EXPECT_EQ(image2.frame_id, 2);
  EXPECT_NE(image1.frame_ptr, image2.frame_ptr);
}

// Test explicit rig_id with rig existing in map
TEST_F(CreateFrameForImageTest_123, ExplicitRigIdWithRigInMap_123) {
  Image image(15, 8, "img.jpg");
  
  Rig rig;
  rigs_[50] = rig;
  
  CreateFrameForImage(cam_from_world_, image, rigs_, frames_, 50, 100);
  
  ASSERT_TRUE(frames_.find(100) != frames_.end());
  Frame& frame = frames_[100];
  EXPECT_EQ(frame.GetRigId(), 50);
  EXPECT_NE(frame.GetRigPtr(), nullptr);
}

// Test explicit rig_id with rig NOT in map
TEST_F(CreateFrameForImageTest_123, ExplicitRigIdWithRigNotInMap_123) {
  Image image(15, 8, "img.jpg");
  
  CreateFrameForImage(cam_from_world_, image, rigs_, frames_, 50, 100);
  
  ASSERT_TRUE(frames_.find(100) != frames_.end());
  Frame& frame = frames_[100];
  EXPECT_EQ(frame.GetRigId(), 50);
  EXPECT_EQ(frame.GetRigPtr(), nullptr);
}

// Test that image's frame_ptr points to the frame in the map
TEST_F(CreateFrameForImageTest_123, ImageFramePtrPointsToMapEntry_123) {
  Image image(3, 1, "img.jpg");
  
  CreateFrameForImage(cam_from_world_, image, rigs_, frames_,
                      colmap::kInvalidRigId, colmap::kInvalidFrameId);
  
  EXPECT_EQ(image.frame_ptr, &frames_[3]);
}

// Test that the frame's data_id contains the image's data id
TEST_F(CreateFrameForImageTest_123, FrameContainsImageDataId_123) {
  Image image(7, 4, "img.jpg");
  
  CreateFrameForImage(cam_from_world_, image, rigs_, frames_,
                      colmap::kInvalidRigId, colmap::kInvalidFrameId);
  
  ASSERT_TRUE(frames_.find(7) != frames_.end());
  Frame& frame = frames_[7];
  EXPECT_EQ(frame.GetFrameId(), 7);
}

// Test overwriting an existing frame in the map
TEST_F(CreateFrameForImageTest_123, OverwriteExistingFrame_123) {
  Image image1(5, 1, "img1.jpg");
  Image image2(10, 2, "img2.jpg");
  
  CreateFrameForImage(cam_from_world_, image1, rigs_, frames_,
                      colmap::kInvalidRigId, 5);
  
  // Now create another frame with the same frame_id=5
  Eigen::Vector3d t(5.0, 6.0, 7.0);
  Rigid3d different_transform(Eigen::Quaterniond::Identity(), t);
  
  CreateFrameForImage(different_transform, image2, rigs_, frames_,
                      colmap::kInvalidRigId, 5);
  
  // Should still have only one entry with frame_id=5
  EXPECT_EQ(frames_.size(), 1u);
  EXPECT_EQ(image2.frame_id, 5);
  
  Rigid3d stored = frames_[5].GetRigFromWorld();
  EXPECT_NEAR(stored.translation().x(), 5.0, 1e-10);
  EXPECT_NEAR(stored.translation().y(), 6.0, 1e-10);
  EXPECT_NEAR(stored.translation().z(), 7.0, 1e-10);
}

// Test with only frame_id invalid (rig_id is explicit)
TEST_F(CreateFrameForImageTest_123, OnlyFrameIdInvalid_123) {
  Image image(20, 3, "img.jpg");
  
  Rig rig;
  rigs_[77] = rig;
  
  CreateFrameForImage(cam_from_world_, image, rigs_, frames_,
                      77, colmap::kInvalidFrameId);
  
  // frame_id defaults to image_id=20
  EXPECT_EQ(image.frame_id, 20);
  ASSERT_TRUE(frames_.find(20) != frames_.end());
  EXPECT_EQ(frames_[20].GetRigId(), 77);
  EXPECT_NE(frames_[20].GetRigPtr(), nullptr);
}

// Test with only rig_id invalid (frame_id is explicit)
TEST_F(CreateFrameForImageTest_123, OnlyRigIdInvalid_123) {
  Image image(20, 3, "img.jpg");
  
  Rig rig;
  rigs_[3] = rig;  // rig with camera_id as key
  
  CreateFrameForImage(cam_from_world_, image, rigs_, frames_,
                      colmap::kInvalidRigId, 55);
  
  // rig_id defaults to camera_id=3
  EXPECT_EQ(image.frame_id, 55);
  ASSERT_TRUE(frames_.find(55) != frames_.end());
  EXPECT_EQ(frames_[55].GetRigId(), 3);
  EXPECT_NE(frames_[55].GetRigPtr(), nullptr);
}

}  // namespace
}  // namespace glomap
