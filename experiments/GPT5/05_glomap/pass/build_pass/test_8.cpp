#include <gtest/gtest.h>
#include <Eigen/Core>

#include "glomap/scene/camera.h"

namespace {

class CameraTest_8 : public ::testing::Test {
 protected:
  glomap::Camera camera_;
};

// Verifies that GetK() places focal lengths and principal points
// into the intrinsic matrix in the expected positions.
TEST_F(CameraTest_8, GetKUsesFocalLengthsAndPrincipalPoints_8) {
  Eigen::Matrix3d K = camera_.GetK();

  // The test only checks observable relationships with the public interface.
  EXPECT_DOUBLE_EQ(camera_.FocalLengthX(),  K(0, 0));
  EXPECT_DOUBLE_EQ(0.0,                     K(0, 1));
  EXPECT_DOUBLE_EQ(camera_.PrincipalPointX(), K(0, 2));

  EXPECT_DOUBLE_EQ(0.0,                     K(1, 0));
  EXPECT_DOUBLE_EQ(camera_.FocalLengthY(),  K(1, 1));
  EXPECT_DOUBLE_EQ(camera_.PrincipalPointY(), K(1, 2));

  EXPECT_DOUBLE_EQ(0.0, K(2, 0));
  EXPECT_DOUBLE_EQ(0.0, K(2, 1));
  EXPECT_DOUBLE_EQ(1.0, K(2, 2));
}

// Verifies that GetK() returns a matrix by value (independent copy)
// and repeated calls are consistent for the same camera state.
TEST_F(CameraTest_8, GetKReturnsIndependentMatrix_8) {
  Eigen::Matrix3d K1 = camera_.GetK();
  Eigen::Matrix3d K2 = camera_.GetK();

  // For the same camera state, repeated calls should yield the same result.
  EXPECT_TRUE(K1.isApprox(K2));

  // Modifying the returned matrix must not affect subsequent GetK() results.
  K1(0, 0) += 10.0;

  Eigen::Matrix3d K3 = camera_.GetK();
  EXPECT_TRUE(K2.isApprox(K3));      // Still the same as before modification.
  EXPECT_NE(K1(0, 0), K3(0, 0));     // Confirms independence of the returned value.
}

}  // namespace
