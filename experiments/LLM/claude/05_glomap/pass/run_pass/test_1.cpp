#include <gtest/gtest.h>
#include "glomap/scene/image.h"
#include "glomap/scene/frame.h"

namespace glomap {
namespace {

class ImageTest_1 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor creates an image with null frame_ptr
TEST_F(ImageTest_1, DefaultConstructor_1) {
  Image img;
  EXPECT_EQ(img.frame_ptr, nullptr);
}

// Test parameterized constructor
TEST_F(ImageTest_1, ParameterizedConstructor_1) {
  Image img(42, 10, "test_image.jpg");
  EXPECT_EQ(img.image_id, 42);
  EXPECT_EQ(img.camera_id, 10);
  EXPECT_EQ(img.file_name, "test_image.jpg");
  EXPECT_EQ(img.frame_ptr, nullptr);
}

// Test IsRegistered returns false when frame_ptr is nullptr
TEST_F(ImageTest_1, IsRegistered_NullFramePtr_ReturnsFalse_1) {
  Image img;
  img.frame_ptr = nullptr;
  EXPECT_FALSE(img.IsRegistered());
}

// Test IsRegistered returns false when frame_ptr is valid but is_registered is false
TEST_F(ImageTest_1, IsRegistered_FrameNotRegistered_ReturnsFalse_1) {
  Image img;
  Frame frame;
  frame.is_registered = false;
  img.frame_ptr = &frame;
  EXPECT_FALSE(img.IsRegistered());
}

// Test IsRegistered returns true when frame_ptr is valid and is_registered is true
TEST_F(ImageTest_1, IsRegistered_FrameRegistered_ReturnsTrue_1) {
  Image img;
  Frame frame;
  frame.is_registered = true;
  img.frame_ptr = &frame;
  EXPECT_TRUE(img.IsRegistered());
}

// Test ClusterId when frame_ptr is set
TEST_F(ImageTest_1, ClusterId_WithFrame_1) {
  Image img;
  Frame frame;
  frame.cluster_id = 5;
  img.frame_ptr = &frame;
  EXPECT_EQ(img.ClusterId(), 5);
}

// Test ClusterId with default frame (cluster_id = -1)
TEST_F(ImageTest_1, ClusterId_DefaultFrame_1) {
  Image img;
  Frame frame;
  img.frame_ptr = &frame;
  EXPECT_EQ(img.ClusterId(), -1);
}

// Test HasGravity delegates to frame
TEST_F(ImageTest_1, HasGravity_WithFrame_1) {
  Image img;
  Frame frame;
  img.frame_ptr = &frame;
  // Default frame should not have gravity
  EXPECT_FALSE(img.HasGravity());
}

// Test default frame_id is -1
TEST_F(ImageTest_1, DefaultFrameId_1) {
  Image img;
  EXPECT_EQ(img.frame_id, -1);
}

// Test features vectors are initially empty
TEST_F(ImageTest_1, FeaturesInitiallyEmpty_1) {
  Image img;
  EXPECT_TRUE(img.features.empty());
  EXPECT_TRUE(img.features_undist.empty());
}

// Test setting and checking frame_ptr
TEST_F(ImageTest_1, FramePtrAssignment_1) {
  Image img;
  Frame frame;
  EXPECT_EQ(img.frame_ptr, nullptr);
  img.frame_ptr = &frame;
  EXPECT_NE(img.frame_ptr, nullptr);
  EXPECT_EQ(img.frame_ptr, &frame);
}

// Test IsRegistered toggling via frame's is_registered field
TEST_F(ImageTest_1, IsRegistered_ToggleRegistration_1) {
  Image img;
  Frame frame;
  img.frame_ptr = &frame;

  frame.is_registered = false;
  EXPECT_FALSE(img.IsRegistered());

  frame.is_registered = true;
  EXPECT_TRUE(img.IsRegistered());

  frame.is_registered = false;
  EXPECT_FALSE(img.IsRegistered());
}

// Test multiple images sharing the same frame
TEST_F(ImageTest_1, MultipleImagesShareFrame_1) {
  Frame frame;
  frame.is_registered = true;

  Image img1(1, 0, "img1.jpg");
  Image img2(2, 0, "img2.jpg");
  img1.frame_ptr = &frame;
  img2.frame_ptr = &frame;

  EXPECT_TRUE(img1.IsRegistered());
  EXPECT_TRUE(img2.IsRegistered());

  frame.is_registered = false;
  EXPECT_FALSE(img1.IsRegistered());
  EXPECT_FALSE(img2.IsRegistered());
}

// Test camera_id assignment
TEST_F(ImageTest_1, CameraIdAssignment_1) {
  Image img(1, 99, "test.jpg");
  EXPECT_EQ(img.camera_id, 99);
}

// Test file_name is correctly stored
TEST_F(ImageTest_1, FileNameStorage_1) {
  Image img(0, 0, "path/to/image.png");
  EXPECT_EQ(img.file_name, "path/to/image.png");
}

// Test empty file name
TEST_F(ImageTest_1, EmptyFileName_1) {
  Image img(0, 0, "");
  EXPECT_EQ(img.file_name, "");
}

// Test default constructor file_name is empty
TEST_F(ImageTest_1, DefaultConstructorFileName_1) {
  Image img;
  EXPECT_EQ(img.file_name, "");
}

}  // namespace
}  // namespace glomap
