#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

// Forward declaration based on the provided interface.
namespace glomap {
double CalcAngle(const Eigen::Matrix3d& rotation1, const Eigen::Matrix3d& rotation2);
}

class CalcAngleTest_71 : public ::testing::Test {};

// Same rotation -> angle should be ~0 degrees.
TEST_F(CalcAngleTest_71, IdentityMatricesReturnZero_71) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::Matrix3d R2 = Eigen::Matrix3d::Identity();

  double angle = glomap::CalcAngle(R1, R2);

  EXPECT_NEAR(angle, 0.0, 1e-10);
}

// 90-degree rotation around Z-axis vs identity -> ~90 degrees.
TEST_F(CalcAngleTest_71, NinetyDegreeRotationAroundZ_71) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::AngleAxisd aa(M_PI / 2.0, Eigen::Vector3d::UnitZ());
  Eigen::Matrix3d R2 = aa.toRotationMatrix();

  double angle = glomap::CalcAngle(R1, R2);

  EXPECT_NEAR(angle, 90.0, 1e-8);
}

// 180-degree rotation around X-axis vs identity -> ~180 degrees (upper bound).
TEST_F(CalcAngleTest_71, OneEightyDegreeRotationAroundX_71) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::AngleAxisd aa(M_PI, Eigen::Vector3d::UnitX());
  Eigen::Matrix3d R2 = aa.toRotationMatrix();

  double angle = glomap::CalcAngle(R1, R2);

  EXPECT_NEAR(angle, 180.0, 1e-8);
}

// Symmetry: angle(R1, R2) == angle(R2, R1).
TEST_F(CalcAngleTest_71, AngleIsSymmetricInArguments_71) {
  Eigen::AngleAxisd aa1(M_PI / 4.0, Eigen::Vector3d::UnitX());
  Eigen::AngleAxisd aa2(M_PI / 3.0, Eigen::Vector3d::UnitY());

  Eigen::Matrix3d R1 = aa1.toRotationMatrix();
  Eigen::Matrix3d R2 = aa2.toRotationMatrix();

  double angle12 = glomap::CalcAngle(R1, R2);
  double angle21 = glomap::CalcAngle(R2, R1);

  EXPECT_NEAR(angle12, angle21, 1e-10);
}

// Invariance under left-multiplication by the same rotation:
// angle(R * R1, R * R2) == angle(R1, R2).
TEST_F(CalcAngleTest_71, LeftMultiplicationInvariance_71) {
  Eigen::AngleAxisd aa1(M_PI / 6.0, Eigen::Vector3d::UnitX());
  Eigen::AngleAxisd aa2(M_PI / 4.0, Eigen::Vector3d::UnitY());
  Eigen::AngleAxisd aaCommon(M_PI / 5.0, Eigen::Vector3d::UnitZ());

  Eigen::Matrix3d R1 = aa1.toRotationMatrix();
  Eigen::Matrix3d R2 = aa2.toRotationMatrix();
  Eigen::Matrix3d Rcommon = aaCommon.toRotationMatrix();

  double base_angle = glomap::CalcAngle(R1, R2);
  double transformed_angle = glomap::CalcAngle(Rcommon * R1, Rcommon * R2);

  EXPECT_NEAR(base_angle, transformed_angle, 1e-10);
}
