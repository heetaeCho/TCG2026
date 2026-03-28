#include <gtest/gtest.h>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>

// Based on the code, Rigid3d must have a `translation` member (Eigen::Vector3d)
// and likely a `rotation` member. We'll use the colmap/glomap Rigid3d or define a compatible one.

namespace glomap {

struct Rigid3d {
  Eigen::Quaterniond rotation;
  Eigen::Vector3d translation;

  Rigid3d() : rotation(Eigen::Quaterniond::Identity()), translation(Eigen::Vector3d::Zero()) {}
  Rigid3d(const Eigen::Quaterniond& r, const Eigen::Vector3d& t) : rotation(r), translation(t) {}
};

double CalcTransAngle(const Rigid3d& pose1, const Rigid3d& pose2);

}  // namespace glomap

class CalcTransAngleTest_70 : public ::testing::Test {
 protected:
  glomap::Rigid3d MakePose(const Eigen::Vector3d& t) {
    return glomap::Rigid3d(Eigen::Quaterniond::Identity(), t);
  }
};

// Test: Same direction translations should give 0 degrees
TEST_F(CalcTransAngleTest_70, SameDirectionReturnsZero_70) {
  auto pose1 = MakePose(Eigen::Vector3d(1, 0, 0));
  auto pose2 = MakePose(Eigen::Vector3d(2, 0, 0));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 0.0, 1e-10);
}

// Test: Opposite direction translations should give 180 degrees
TEST_F(CalcTransAngleTest_70, OppositeDirectionReturns180_70) {
  auto pose1 = MakePose(Eigen::Vector3d(1, 0, 0));
  auto pose2 = MakePose(Eigen::Vector3d(-1, 0, 0));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 180.0, 1e-10);
}

// Test: Perpendicular translations should give 90 degrees
TEST_F(CalcTransAngleTest_70, PerpendicularReturns90_70) {
  auto pose1 = MakePose(Eigen::Vector3d(1, 0, 0));
  auto pose2 = MakePose(Eigen::Vector3d(0, 1, 0));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 90.0, 1e-10);
}

// Test: 45-degree angle between two translations in XY plane
TEST_F(CalcTransAngleTest_70, FortyFiveDegreeAngle_70) {
  auto pose1 = MakePose(Eigen::Vector3d(1, 0, 0));
  auto pose2 = MakePose(Eigen::Vector3d(1, 1, 0));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 45.0, 1e-10);
}

// Test: Same translation vectors should give 0 degrees
TEST_F(CalcTransAngleTest_70, IdenticalTranslationsReturnZero_70) {
  auto pose1 = MakePose(Eigen::Vector3d(3, 4, 5));
  auto pose2 = MakePose(Eigen::Vector3d(3, 4, 5));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 0.0, 1e-10);
}

// Test: Angle is symmetric
TEST_F(CalcTransAngleTest_70, Symmetry_70) {
  auto pose1 = MakePose(Eigen::Vector3d(1, 2, 3));
  auto pose2 = MakePose(Eigen::Vector3d(4, 5, 6));
  double angle12 = glomap::CalcTransAngle(pose1, pose2);
  double angle21 = glomap::CalcTransAngle(pose2, pose1);
  EXPECT_NEAR(angle12, angle21, 1e-10);
}

// Test: Perpendicular in 3D
TEST_F(CalcTransAngleTest_70, PerpendicularInZ_70) {
  auto pose1 = MakePose(Eigen::Vector3d(0, 0, 1));
  auto pose2 = MakePose(Eigen::Vector3d(0, 1, 0));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 90.0, 1e-10);
}

// Test: Very small angle between close vectors
TEST_F(CalcTransAngleTest_70, SmallAngle_70) {
  auto pose1 = MakePose(Eigen::Vector3d(1, 0, 0));
  auto pose2 = MakePose(Eigen::Vector3d(1, 1e-8, 0));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 0.0, 1e-3);  // very small angle, close to 0
}

// Test: Angle with negative coordinates
TEST_F(CalcTransAngleTest_70, NegativeCoordinates_70) {
  auto pose1 = MakePose(Eigen::Vector3d(-1, 0, 0));
  auto pose2 = MakePose(Eigen::Vector3d(0, -1, 0));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 90.0, 1e-10);
}

// Test: Scaled versions of same direction give 0
TEST_F(CalcTransAngleTest_70, ScaledSameDirectionZero_70) {
  auto pose1 = MakePose(Eigen::Vector3d(1, 1, 1));
  auto pose2 = MakePose(Eigen::Vector3d(100, 100, 100));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 0.0, 1e-10);
}

// Test: 120-degree angle
TEST_F(CalcTransAngleTest_70, OneTwentyDegreeAngle_70) {
  // cos(120°) = -0.5
  // Two unit vectors with dot product = -0.5
  auto pose1 = MakePose(Eigen::Vector3d(1, 0, 0));
  auto pose2 = MakePose(Eigen::Vector3d(-0.5, std::sqrt(3.0) / 2.0, 0));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 120.0, 1e-8);
}

// Test: 60-degree angle
TEST_F(CalcTransAngleTest_70, SixtyDegreeAngle_70) {
  auto pose1 = MakePose(Eigen::Vector3d(1, 0, 0));
  auto pose2 = MakePose(Eigen::Vector3d(0.5, std::sqrt(3.0) / 2.0, 0));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 60.0, 1e-8);
}

// Test: Rotation component does not affect the result (only translation matters)
TEST_F(CalcTransAngleTest_70, RotationDoesNotAffectResult_70) {
  glomap::Rigid3d pose1(
      Eigen::Quaterniond(Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitZ())),
      Eigen::Vector3d(1, 0, 0));
  glomap::Rigid3d pose2(
      Eigen::Quaterniond(Eigen::AngleAxisd(1.2, Eigen::Vector3d::UnitY())),
      Eigen::Vector3d(0, 1, 0));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 90.0, 1e-10);
}

// Test: Result is always non-negative and at most 180
TEST_F(CalcTransAngleTest_70, ResultInValidRange_70) {
  auto pose1 = MakePose(Eigen::Vector3d(1, -3, 7));
  auto pose2 = MakePose(Eigen::Vector3d(-2, 5, -1));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_GE(angle, 0.0);
  EXPECT_LE(angle, 180.0);
}

// Test: Large magnitude translations
TEST_F(CalcTransAngleTest_70, LargeMagnitude_70) {
  auto pose1 = MakePose(Eigen::Vector3d(1e10, 0, 0));
  auto pose2 = MakePose(Eigen::Vector3d(0, 1e10, 0));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 90.0, 1e-6);
}

// Test: Very small magnitude translations
TEST_F(CalcTransAngleTest_70, SmallMagnitude_70) {
  auto pose1 = MakePose(Eigen::Vector3d(1e-15, 0, 0));
  auto pose2 = MakePose(Eigen::Vector3d(0, 1e-15, 0));
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 90.0, 1e-3);
}

// Test: 3D diagonal vectors
TEST_F(CalcTransAngleTest_70, DiagonalVectors_70) {
  auto pose1 = MakePose(Eigen::Vector3d(1, 1, 0));
  auto pose2 = MakePose(Eigen::Vector3d(0, 1, 1));
  // cos(theta) = (0+1+0)/(sqrt(2)*sqrt(2)) = 1/2, theta = 60 degrees
  double angle = glomap::CalcTransAngle(pose1, pose2);
  EXPECT_NEAR(angle, 60.0, 1e-10);
}
