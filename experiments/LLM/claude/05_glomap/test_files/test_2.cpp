#include <gtest/gtest.h>
#include "glomap/scene/image.h"
#include "glomap/scene/frame.h"

namespace glomap {
namespace {

class ImageTest_2 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor
TEST_F(ImageTest_2, DefaultConstructor_2) {
  Image img;
  EXPECT_EQ(img.image_id, -1);
  EXPECT_EQ(img.file_name, "");
}

// Test parameterized constructor
TEST_F(ImageTest_2, ParameterizedConstructor_2) {
  Image img(42, 10, "test_image.jpg");
  EXPECT_EQ(img.image_id, 42);
  EXPECT_EQ(img.camera_id, 10);
  EXPECT_EQ(img.file_name, "test_image.jpg");
}

// Test ClusterId returns -1 when frame_ptr is nullptr
TEST_F(ImageTest_2, ClusterIdReturnsNegativeOneWhenFramePtrIsNull_2) {
  Image img;
  EXPECT_EQ(img.frame_ptr, nullptr);
  EXPECT_EQ(img.ClusterId(), -1);
}

// Test ClusterId returns frame's cluster_id when frame_ptr is set
TEST_F(ImageTest_2, ClusterIdReturnsFrameClusterIdWhenFramePtrIsSet_2) {
  Image img;
  Frame frame;
  frame.cluster_id = 5;
  img.frame_ptr = &frame;
  EXPECT_EQ(img.ClusterId(), 5);
}

// Test ClusterId returns default frame cluster_id (-1) when frame has default cluster
TEST_F(ImageTest_2, ClusterIdReturnsDefaultFrameClusterId_2) {
  Image img;
  Frame frame;
  // frame.cluster_id defaults to -1
  img.frame_ptr = &frame;
  EXPECT_EQ(img.ClusterId(), -1);
}

// Test ClusterId with various cluster_id values
TEST_F(ImageTest_2, ClusterIdWithVariousValues_2) {
  Image img;
  Frame frame;
  
  frame.cluster_id = 0;
  img.frame_ptr = &frame;
  EXPECT_EQ(img.ClusterId(), 0);
  
  frame.cluster_id = 100;
  EXPECT_EQ(img.ClusterId(), 100);
  
  frame.cluster_id = -42;
  EXPECT_EQ(img.ClusterId(), -42);
}

// Test that frame_ptr defaults to nullptr
TEST_F(ImageTest_2, FramePtrDefaultsToNullptr_2) {
  Image img;
  EXPECT_EQ(img.frame_ptr, nullptr);
}

// Test parameterized constructor also has null frame_ptr
TEST_F(ImageTest_2, ParameterizedConstructorFramePtrIsNull_2) {
  Image img(1, 2, "img.png");
  EXPECT_EQ(img.frame_ptr, nullptr);
  EXPECT_EQ(img.ClusterId(), -1);
}

// Test IsRegistered when frame_ptr is null
TEST_F(ImageTest_2, IsRegisteredWhenFramePtrNull_2) {
  Image img;
  // With null frame_ptr, behavior should be defined
  // We test it doesn't crash; actual return depends on implementation
  bool registered = img.IsRegistered();
  (void)registered;  // Just verify it doesn't crash
}

// Test IsRegistered when frame is registered
TEST_F(ImageTest_2, IsRegisteredWhenFrameIsRegistered_2) {
  Image img;
  Frame frame;
  frame.is_registered = true;
  img.frame_ptr = &frame;
  EXPECT_TRUE(img.IsRegistered());
}

// Test IsRegistered when frame is not registered
TEST_F(ImageTest_2, IsRegisteredWhenFrameIsNotRegistered_2) {
  Image img;
  Frame frame;
  frame.is_registered = false;
  img.frame_ptr = &frame;
  EXPECT_FALSE(img.IsRegistered());
}

// Test frame_id defaults to -1
TEST_F(ImageTest_2, FrameIdDefaultsToNegativeOne_2) {
  Image img;
  EXPECT_EQ(img.frame_id, -1);
}

// Test setting frame_ptr and then resetting to nullptr
TEST_F(ImageTest_2, ResetFramePtrToNull_2) {
  Image img;
  Frame frame;
  frame.cluster_id = 10;
  img.frame_ptr = &frame;
  EXPECT_EQ(img.ClusterId(), 10);
  
  img.frame_ptr = nullptr;
  EXPECT_EQ(img.ClusterId(), -1);
}

// Test features vectors are initially empty
TEST_F(ImageTest_2, FeaturesInitiallyEmpty_2) {
  Image img;
  EXPECT_TRUE(img.features.empty());
  EXPECT_TRUE(img.features_undist.empty());
}

// Test HasTrivialFrame when frame_ptr is null
TEST_F(ImageTest_2, HasTrivialFrameWhenNull_2) {
  Image img;
  // Should not crash
  bool result = img.HasTrivialFrame();
  (void)result;
}

// Test camera_id assignment
TEST_F(ImageTest_2, CameraIdAssignment_2) {
  Image img(1, 42, "test.jpg");
  EXPECT_EQ(img.camera_id, 42);
}

// Test file_name with empty string
TEST_F(ImageTest_2, FileNameEmptyString_2) {
  Image img(1, 1, "");
  EXPECT_EQ(img.file_name, "");
}

// Test file_name with path-like string
TEST_F(ImageTest_2, FileNameWithPath_2) {
  Image img(1, 1, "/path/to/image.jpg");
  EXPECT_EQ(img.file_name, "/path/to/image.jpg");
}

}  // namespace
}  // namespace glomap
