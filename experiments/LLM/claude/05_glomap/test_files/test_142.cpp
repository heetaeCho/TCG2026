#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

// We need to understand the Rigid3d type used in glomap.
// Based on the code, Rigid3d has at least .translation and can be inverted via Inverse().
// This is likely from colmap's Rigid3d or a similar structure.

#include "glomap/math/rigid3d.h"

namespace glomap {
namespace {

// Helper to create a Rigid3d from rotation (quaternion) and translation
Rigid3d MakeRigid3d(const Eigen::Quaterniond& q, const Eigen::Vector3d& t) {
  Rigid3d pose;
  pose.rotation = q.normalized();
  pose.translation = t;
  return pose;
}

// Test with identity poses - both poses are identity, distance should be 0
TEST(CalcTransTest_142, IdentityPoses_142) {
  Rigid3d pose1 = MakeRigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
  Rigid3d pose2 = MakeRigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());

  double result = CalcTrans(pose1, pose2);
  EXPECT_NEAR(result, 0.0, 1e-10);
}

// Test with same poses - should return 0
TEST(CalcTransTest_142, SamePoses_142) {
  Eigen::Quaterniond q(Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitZ()));
  Eigen::Vector3d t(1.0, 2.0, 3.0);
  Rigid3d pose1 = MakeRigid3d(q, t);
  Rigid3d pose2 = MakeRigid3d(q, t);

  double result = CalcTrans(pose1, pose2);
  EXPECT_NEAR(result, 0.0, 1e-10);
}

// Test with identity rotations and different translations
// Inverse of a pose with identity rotation and translation t is (identity, -t)
// So the distance should be norm((-t1) - (-t2)) = norm(t2 - t1)
TEST(CalcTransTest_142, IdentityRotationDifferentTranslation_142) {
  Rigid3d pose1 = MakeRigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1.0, 0.0, 0.0));
  Rigid3d pose2 = MakeRigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d(4.0, 0.0, 0.0));

  double result = CalcTrans(pose1, pose2);
  EXPECT_NEAR(result, 3.0, 1e-10);
}

// Test with pure translations along different axes
TEST(CalcTransTest_142, TranslationsAlongDifferentAxes_142) {
  Rigid3d pose1 = MakeRigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1.0, 0.0, 0.0));
  Rigid3d pose2 = MakeRigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d(0.0, 1.0, 0.0));

  double result = CalcTrans(pose1, pose2);
  // Inverse of identity rotation + t is identity rotation + (-t)
  // norm((-1,0,0) - (0,-1,0)) = norm(-1, 1, 0) = sqrt(2)
  EXPECT_NEAR(result, std::sqrt(2.0), 1e-10);
}

// Test result is non-negative (distance property)
TEST(CalcTransTest_142, ResultIsNonNegative_142) {
  Rigid3d pose1 = MakeRigid3d(
      Eigen::Quaterniond(Eigen::AngleAxisd(1.0, Eigen::Vector3d::UnitX())),
      Eigen::Vector3d(-5.0, 3.0, -1.0));
  Rigid3d pose2 = MakeRigid3d(
      Eigen::Quaterniond(Eigen::AngleAxisd(0.3, Eigen::Vector3d::UnitY())),
      Eigen::Vector3d(2.0, -4.0, 6.0));

  double result = CalcTrans(pose1, pose2);
  EXPECT_GE(result, 0.0);
}

// Test symmetry: CalcTrans(a, b) == CalcTrans(b, a)
TEST(CalcTransTest_142, Symmetry_142) {
  Rigid3d pose1 = MakeRigid3d(
      Eigen::Quaterniond(Eigen::AngleAxisd(0.7, Eigen::Vector3d::UnitZ())),
      Eigen::Vector3d(1.0, 2.0, 3.0));
  Rigid3d pose2 = MakeRigid3d(
      Eigen::Quaterniond(Eigen::AngleAxisd(-0.3, Eigen::Vector3d::UnitY())),
      Eigen::Vector3d(-1.0, 5.0, -2.0));

  double result1 = CalcTrans(pose1, pose2);
  double result2 = CalcTrans(pose2, pose1);
  EXPECT_NEAR(result1, result2, 1e-10);
}

// Test with rotations that affect the camera center computation
// For a camera pose (R, t), the camera center is C = -R^T * t
// So Inverse(pose).translation = -R^T * t
TEST(CalcTransTest_142, WithRotation_142) {
  // pose1: 90 degree rotation around Z, translation (1, 0, 0)
  // Camera center = -R^T * t
  Eigen::Quaterniond q1(Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitZ()));
  Eigen::Vector3d t1(1.0, 0.0, 0.0);
  Rigid3d pose1 = MakeRigid3d(q1, t1);

  // pose2: identity rotation, translation (0, 0, 0)
  Rigid3d pose2 = MakeRigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());

  double result = CalcTrans(pose1, pose2);
  // Camera center of pose1 = -R^T * t1
  // R is 90 deg around Z: R^T rotates (1,0,0) to (cos(-90), sin(-90), 0) = (0, -1, 0)
  // So camera center of pose1 = -(0, -1, 0) = (0, 1, 0)
  // Camera center of pose2 = (0, 0, 0)
  // Distance = 1.0
  EXPECT_NEAR(result, 1.0, 1e-10);
}

// Test with large translations
TEST(CalcTransTest_142, LargeTranslations_142) {
  Rigid3d pose1 = MakeRigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1e6, 0.0, 0.0));
  Rigid3d pose2 = MakeRigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d(-1e6, 0.0, 0.0));

  double result = CalcTrans(pose1, pose2);
  EXPECT_NEAR(result, 2e6, 1e-4);
}

// Test with very small translations
TEST(CalcTransTest_142, VerySmallTranslations_142) {
  Rigid3d pose1 = MakeRigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1e-15, 0.0, 0.0));
  Rigid3d pose2 = MakeRigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());

  double result = CalcTrans(pose1, pose2);
  EXPECT_NEAR(result, 1e-15, 1e-20);
}

// Test with 180-degree rotation
TEST(CalcTransTest_142, Rotation180Degrees_142) {
  Eigen::Quaterniond q1(Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitX()));
  Eigen::Vector3d t1(0.0, 1.0, 0.0);
  Rigid3d pose1 = MakeRigid3d(q1, t1);

  Rigid3d pose2 = MakeRigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d(0.0, 1.0, 0.0));

  // pose1 camera center: -R^T * t1
  // R is 180 around X: R^T = R. R*(0,1,0) = (0,-1,0)
  // camera center = -(0,-1,0) = (0,1,0)
  // pose2 camera center = -(0,1,0) = (0,-1,0)
  // distance = norm((0,1,0) - (0,-1,0)) = 2
  double result = CalcTrans(pose1, pose2);
  EXPECT_NEAR(result, 2.0, 1e-10);
}

// Test with 3D translation difference
TEST(CalcTransTest_142, ThreeDimensionalTranslation_142) {
  Rigid3d pose1 = MakeRigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1.0, 2.0, 3.0));
  Rigid3d pose2 = MakeRigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d(4.0, 6.0, 3.0));

  double result = CalcTrans(pose1, pose2);
  // With identity rotation, camera centers are -t
  // norm((-1,-2,-3) - (-4,-6,-3)) = norm(3, 4, 0) = 5
  EXPECT_NEAR(result, 5.0, 1e-10);
}

// Test triangle inequality
TEST(CalcTransTest_142, TriangleInequality_142) {
  Rigid3d pose1 = MakeRigid3d(
      Eigen::Quaterniond(Eigen::AngleAxisd(0.2, Eigen::Vector3d::UnitX())),
      Eigen::Vector3d(1.0, 0.0, 0.0));
  Rigid3d pose2 = MakeRigid3d(
      Eigen::Quaterniond(Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitY())),
      Eigen::Vector3d(0.0, 1.0, 0.0));
  Rigid3d pose3 = MakeRigid3d(
      Eigen::Quaterniond(Eigen::AngleAxisd(-0.3, Eigen::Vector3d::UnitZ())),
      Eigen::Vector3d(0.0, 0.0, 1.0));

  double d12 = CalcTrans(pose1, pose2);
  double d23 = CalcTrans(pose2, pose3);
  double d13 = CalcTrans(pose1, pose3);

  EXPECT_LE(d13, d12 + d23 + 1e-10);
}

}  // namespace
}  // namespace glomap
