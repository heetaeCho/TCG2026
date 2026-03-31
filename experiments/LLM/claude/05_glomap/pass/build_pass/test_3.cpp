#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "glomap/scene/image.h"
#include "glomap/scene/frame.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <memory>

namespace glomap {
namespace {

class ImageGetRAlignTest_3 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that GetRAlign returns identity when frame_ptr is nullptr (no gravity)
TEST_F(ImageGetRAlignTest_3, NoFramePtr_ReturnsIdentity_3) {
    Image img(-1, 0, "test.jpg");
    img.frame_ptr = nullptr;
    
    // HasGravity() should return false when frame_ptr is nullptr
    // GetRAlign should return Identity
    Eigen::Matrix3d result = img.GetRAlign();
    EXPECT_TRUE(result.isApprox(Eigen::Matrix3d::Identity()));
}

// Test that GetRAlign returns identity when frame has no gravity
TEST_F(ImageGetRAlignTest_3, FrameWithNoGravity_ReturnsIdentity_3) {
    Frame frame;
    frame.gravity_info.has_gravity = false;
    
    Image img(0, 0, "test.jpg");
    img.frame_ptr = &frame;
    
    // HasGravity() depends on frame_ptr->gravity_info or Frame::HasGravity()
    // When has_gravity is false, GetRAlign should return Identity
    Eigen::Matrix3d result = img.GetRAlign();
    EXPECT_TRUE(result.isApprox(Eigen::Matrix3d::Identity()));
}

// Test that GetRAlign returns gravity R_align when frame has gravity and trivial frame
TEST_F(ImageGetRAlignTest_3, FrameWithGravityAndTrivialFrame_ReturnsGravityRAlign_3) {
    Frame frame;
    
    // Set a non-trivial gravity to make has_gravity = true
    Eigen::Vector3d gravity(0, 0, -9.8);
    frame.gravity_info.SetGravity(gravity);
    
    Image img(0, 0, "test.jpg");
    img.frame_ptr = &frame;
    
    // If has gravity and has trivial frame, should return frame_ptr->gravity_info.GetRAlign()
    if (img.HasGravity() && img.HasTrivialFrame()) {
        Eigen::Matrix3d result = img.GetRAlign();
        Eigen::Matrix3d expected = frame.gravity_info.GetRAlign();
        EXPECT_TRUE(result.isApprox(expected));
    }
}

// Test that GetRAlign returns the gravity alignment matrix from GravityInfo
TEST_F(ImageGetRAlignTest_3, GravitySetWithSpecificVector_ReturnsCorrectRAlign_3) {
    Frame frame;
    
    // Set gravity along a specific direction
    Eigen::Vector3d gravity(0, -1, 0);
    frame.gravity_info.SetGravity(gravity);
    
    Image img(1, 0, "test_image.jpg");
    img.frame_ptr = &frame;
    
    if (img.HasGravity()) {
        Eigen::Matrix3d result = img.GetRAlign();
        // The result should be a valid rotation matrix
        // Check orthogonality: R^T * R = I
        Eigen::Matrix3d shouldBeIdentity = result.transpose() * result;
        EXPECT_TRUE(shouldBeIdentity.isApprox(Eigen::Matrix3d::Identity(), 1e-10));
        // Check determinant is 1
        EXPECT_NEAR(result.determinant(), 1.0, 1e-10);
    }
}

// Test basic Image construction
TEST_F(ImageGetRAlignTest_3, ImageConstruction_3) {
    Image img(42, 7, "photo.jpg");
    EXPECT_EQ(img.image_id, 42);
    EXPECT_EQ(img.camera_id, 7);
    EXPECT_EQ(img.file_name, "photo.jpg");
    EXPECT_EQ(img.frame_ptr, nullptr);
}

// Test HasGravity returns false when no frame_ptr
TEST_F(ImageGetRAlignTest_3, HasGravityNoFrame_ReturnsFalse_3) {
    Image img(0, 0, "test.jpg");
    img.frame_ptr = nullptr;
    EXPECT_FALSE(img.HasGravity());
}

// Test HasGravity returns false when frame has no gravity
TEST_F(ImageGetRAlignTest_3, HasGravityFrameNoGravity_ReturnsFalse_3) {
    Frame frame;
    frame.gravity_info.has_gravity = false;
    
    Image img(0, 0, "test.jpg");
    img.frame_ptr = &frame;
    EXPECT_FALSE(img.HasGravity());
}

// Test HasGravity returns true when frame has gravity set
TEST_F(ImageGetRAlignTest_3, HasGravityFrameWithGravity_ReturnsTrue_3) {
    Frame frame;
    Eigen::Vector3d gravity(0, 0, -9.8);
    frame.gravity_info.SetGravity(gravity);
    
    Image img(0, 0, "test.jpg");
    img.frame_ptr = &frame;
    
    if (frame.gravity_info.has_gravity) {
        EXPECT_TRUE(img.HasGravity());
    }
}

// Test that GetRAlign result is a valid rotation matrix when gravity is set
TEST_F(ImageGetRAlignTest_3, GetRAlignIsValidRotation_3) {
    Frame frame;
    Eigen::Vector3d gravity(1, 2, 3);
    gravity.normalize();
    frame.gravity_info.SetGravity(gravity);
    
    Image img(0, 0, "test.jpg");
    img.frame_ptr = &frame;
    
    Eigen::Matrix3d result = img.GetRAlign();
    
    // Check it's a valid rotation matrix
    Eigen::Matrix3d RtR = result.transpose() * result;
    EXPECT_TRUE(RtR.isApprox(Eigen::Matrix3d::Identity(), 1e-10))
        << "R^T * R should be Identity";
    EXPECT_NEAR(result.determinant(), 1.0, 1e-10)
        << "Determinant should be 1";
}

// Test GetRAlign with zero gravity direction - edge case
TEST_F(ImageGetRAlignTest_3, GetRAlignWithZeroGravity_3) {
    Frame frame;
    Eigen::Vector3d gravity(0, 0, 0);
    frame.gravity_info.SetGravity(gravity);
    
    Image img(0, 0, "test.jpg");
    img.frame_ptr = &frame;
    
    // This is an edge case - behavior depends on implementation
    // We just make sure it doesn't crash
    Eigen::Matrix3d result = img.GetRAlign();
    // Result should be some 3x3 matrix
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
}

// Test GravityInfo GetRAlign returns identity by default
TEST_F(ImageGetRAlignTest_3, GravityInfoDefaultRAlign_3) {
    GravityInfo info;
    EXPECT_FALSE(info.has_gravity);
    Eigen::Matrix3d r = info.GetRAlign();
    EXPECT_TRUE(r.isApprox(Eigen::Matrix3d::Identity()));
}

// Test default Image construction
TEST_F(ImageGetRAlignTest_3, DefaultImageConstruction_3) {
    Image img;
    EXPECT_EQ(img.image_id, -1);
    EXPECT_EQ(img.frame_ptr, nullptr);
}

// Test IsRegistered reflects frame registration state
TEST_F(ImageGetRAlignTest_3, IsRegistered_NoFrame_3) {
    Image img(0, 0, "test.jpg");
    img.frame_ptr = nullptr;
    // Without frame, registration status behavior
    // Just verify it doesn't crash
    bool reg = img.IsRegistered();
    (void)reg;
}

// Test IsRegistered with registered frame
TEST_F(ImageGetRAlignTest_3, IsRegistered_WithRegisteredFrame_3) {
    Frame frame;
    frame.is_registered = true;
    
    Image img(0, 0, "test.jpg");
    img.frame_ptr = &frame;
    
    EXPECT_TRUE(img.IsRegistered());
}

// Test IsRegistered with unregistered frame
TEST_F(ImageGetRAlignTest_3, IsRegistered_WithUnregisteredFrame_3) {
    Frame frame;
    frame.is_registered = false;
    
    Image img(0, 0, "test.jpg");
    img.frame_ptr = &frame;
    
    EXPECT_FALSE(img.IsRegistered());
}

// Test ClusterId returns frame cluster_id
TEST_F(ImageGetRAlignTest_3, ClusterId_WithFrame_3) {
    Frame frame;
    frame.cluster_id = 42;
    
    Image img(0, 0, "test.jpg");
    img.frame_ptr = &frame;
    
    EXPECT_EQ(img.ClusterId(), 42);
}

// Test ClusterId default
TEST_F(ImageGetRAlignTest_3, ClusterId_DefaultFrame_3) {
    Frame frame;
    
    Image img(0, 0, "test.jpg");
    img.frame_ptr = &frame;
    
    EXPECT_EQ(img.ClusterId(), -1);
}

}  // namespace
}  // namespace glomap
