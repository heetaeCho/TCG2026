#include <gtest/gtest.h>
#include "glomap/math/rigid3d.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

namespace glomap {
namespace {

class CalcTransTest_69 : public ::testing::Test {
 protected:
  Rigid3d MakeIdentityPose() {
    Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d::Zero();
    return pose;
  }

  Rigid3d MakePose(const Eigen::Quaterniond& q, const Eigen::Vector3d& t) {
    Rigid3d pose;
    pose.rotation = q.normalized();
    pose.translation = t;
    return pose;
  }
};

// When both poses are identity, the translation difference should be zero
TEST_F(CalcTransTest_69, IdentityPoses_ReturnsZero_69) {
  Rigid3d pose1 = MakeIdentityPose();
  Rigid3d pose2 = MakeIdentityPose();
  
  double result = CalcTrans(pose1, pose2);
  EXPECT_DOUBLE_EQ(result, 0.0);
}

// When both poses are the same, the result should be zero
TEST_F(CalcTransTest_69, SamePoses_ReturnsZero_69) {
  Rigid3d pose = MakePose(
      Eigen::Quaterniond(Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitZ())),
      Eigen::Vector3d(1.0, 2.0, 3.0));
  
  double result = CalcTrans(pose, pose);
  EXPECT_NEAR(result, 0.0, 1e-10);
}

// For identity rotation, inverse translation is just -t, so CalcTrans should
// give the norm of (t2 - t1) when rotations are identity
TEST_F(CalcTransTest_69, IdentityRotation_PureTranslation_69) {
  Rigid3d pose1 = MakePose(Eigen::Quaterniond::Identity(),
                            Eigen::Vector3d(1.0, 0.0, 0.0));
  Rigid3d pose2 = MakePose(Eigen::Quaterniond::Identity(),
                            Eigen::Vector3d(4.0, 0.0, 0.0));
  
  // Inverse of identity-rotation pose with translation t has translation -t
  // So result = ||(-1,0,0) - (-4,0,0)|| = ||(3,0,0)|| = 3.0
  double result = CalcTrans(pose1, pose2);
  EXPECT_NEAR(result, 3.0, 1e-10);
}

// Test with different translations along all axes
TEST_F(CalcTransTest_69, IdentityRotation_3DTranslation_69) {
  Rigid3d pose1 = MakePose(Eigen::Quaterniond::Identity(),
                            Eigen::Vector3d(1.0, 2.0, 3.0));
  Rigid3d pose2 = MakePose(Eigen::Quaterniond::Identity(),
                            Eigen::Vector3d(4.0, 6.0, 3.0));
  
  // Result = ||(-1,-2,-3) - (-4,-6,-3)|| = ||(3,4,0)|| = 5.0
  double result = CalcTrans(pose1, pose2);
  EXPECT_NEAR(result, 5.0, 1e-10);
}

// Test result is always non-negative (norm property)
TEST_F(CalcTransTest_69, ResultIsNonNegative_69) {
  Rigid3d pose1 = MakePose(
      Eigen::Quaterniond(Eigen::AngleAxisd(1.0, Eigen::Vector3d::UnitX())),
      Eigen::Vector3d(-5.0, 3.0, -1.0));
  Rigid3d pose2 = MakePose(
      Eigen::Quaterniond(Eigen::AngleAxisd(-0.7, Eigen::Vector3d::UnitY())),
      Eigen::Vector3d(2.0, -4.0, 6.0));
  
  double result = CalcTrans(pose1, pose2);
  EXPECT_GE(result, 0.0);
}

// Test symmetry: CalcTrans(a, b) == CalcTrans(b, a) since ||x|| == ||-x||
TEST_F(CalcTransTest_69, Symmetry_69) {
  Rigid3d pose1 = MakePose(
      Eigen::Quaterniond(Eigen::AngleAxisd(0.3, Eigen::Vector3d::UnitZ())),
      Eigen::Vector3d(1.0, 2.0, 3.0));
  Rigid3d pose2 = MakePose(
      Eigen::Quaterniond(Eigen::AngleAxisd(-0.5, Eigen::Vector3d::UnitX())),
      Eigen::Vector3d(4.0, 5.0, 6.0));
  
  double result1 = CalcTrans(pose1, pose2);
  double result2 = CalcTrans(pose2, pose1);
  EXPECT_NEAR(result1, result2, 1e-10);
}

// Test with rotation involved: the inverse of a rotated+translated pose
// has translation = -R^T * t, so rotations affect the result
TEST_F(CalcTransTest_69, WithRotation_90DegreeZ_69) {
  // Pose1: 90 degree rotation around Z, translation (1, 0, 0)
  // Inverse translation = -R^T * t = -Rz(-90) * (1,0,0) = -(0, -1, 0) = (0, 1, 0)
  Rigid3d pose1 = MakePose(
      Eigen::Quaterniond(Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitZ())),
      Eigen::Vector3d(1.0, 0.0, 0.0));
  
  // Pose2: identity rotation, translation (0, 1, 0)
  // Inverse translation = -(0, 1, 0) = (0, -1, 0)
  Rigid3d pose2 = MakePose(Eigen::Quaterniond::Identity(),
                            Eigen::Vector3d(0.0, 1.0, 0.0));
  
  // Result = ||(0,1,0) - (0,-1,0)|| = ||(0,2,0)|| = 2.0
  double result = CalcTrans(pose1, pose2);
  EXPECT_NEAR(result, 2.0, 1e-10);
}

// Test with 180 degree rotation
TEST_F(CalcTransTest_69, WithRotation_180DegreeX_69) {
  // Pose: 180 degree rotation around X, translation (0, 1, 0)
  // R_x(180) = diag(1, -1, -1)
  // Inverse translation = -R^T * t = -R_x(-180) * (0,1,0) = -R_x(180) * (0,1,0) = -(0,-1,0) = (0,1,0)
  Rigid3d pose1 = MakePose(
      Eigen::Quaterniond(Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitX())),
      Eigen::Vector3d(0.0, 1.0, 0.0));
  
  Rigid3d pose2 = MakeIdentityPose();
  
  // Inverse of pose1 has translation (0, 1, 0), inverse of identity has (0, 0, 0)
  // Result = ||(0,1,0)|| = 1.0
  double result = CalcTrans(pose1, pose2);
  EXPECT_NEAR(result, 1.0, 1e-10);
}

// Test with zero translation but different rotations
TEST_F(CalcTransTest_69, ZeroTranslation_DifferentRotations_69) {
  Rigid3d pose1 = MakePose(
      Eigen::Quaterniond(Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitY())),
      Eigen::Vector3d::Zero());
  Rigid3d pose2 = MakePose(
      Eigen::Quaterniond(Eigen::AngleAxisd(-0.5, Eigen::Vector3d::UnitZ())),
      Eigen::Vector3d::Zero());
  
  // Both have zero translation, so inverse translations are also zero
  double result = CalcTrans(pose1, pose2);
  EXPECT_NEAR(result, 0.0, 1e-10);
}

// Test with large translation values
TEST_F(CalcTransTest_69, LargeTranslation_69) {
  Rigid3d pose1 = MakePose(Eigen::Quaterniond::Identity(),
                            Eigen::Vector3d(1e6, 1e6, 1e6));
  Rigid3d pose2 = MakePose(Eigen::Quaterniond::Identity(),
                            Eigen::Vector3d(-1e6, -1e6, -1e6));
  
  double expected = (Eigen::Vector3d(2e6, 2e6, 2e6)).norm();
  double result = CalcTrans(pose1, pose2);
  EXPECT_NEAR(result, expected, 1e-2);
}

// Test with very small translation differences
TEST_F(CalcTransTest_69, SmallTranslationDifference_69) {
  Rigid3d pose1 = MakePose(Eigen::Quaterniond::Identity(),
                            Eigen::Vector3d(1e-10, 0.0, 0.0));
  Rigid3d pose2 = MakePose(Eigen::Quaterniond::Identity(),
                            Eigen::Vector3d::Zero());
  
  double result = CalcTrans(pose1, pose2);
  EXPECT_NEAR(result, 1e-10, 1e-15);
}

}  // namespace
}  // namespace glomap
