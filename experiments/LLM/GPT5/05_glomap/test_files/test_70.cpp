// File: ./TestProjects/glomap/glomap/math/rigid3d_calc_trans_angle_test_70.cc

#include <gtest/gtest.h>
#include <Eigen/Core>

#include "glomap/math/rigid3d.h"

namespace glomap {

class CalcTransAngleTest_70 : public ::testing::Test {
 protected:
  // Helper to construct a pose with a specific translation
  Rigid3d MakePoseWithTranslation(const Eigen::Vector3d& t) {
    Rigid3d pose;
    pose.translation = t;  // Uses the public interface as seen in the implementation
    return pose;
  }
};

// Normal case: parallel vectors in the same direction → angle ≈ 0°
TEST_F(CalcTransAngleTest_70, ParallelSameDirectionReturnsZero_70) {
  Rigid3d pose1 = MakePoseWithTranslation(Eigen::Vector3d(1.0, 0.0, 0.0));
  Rigid3d pose2 = MakePoseWithTranslation(Eigen::Vector3d(2.0, 0.0, 0.0));

  const double angle_deg = CalcTransAngle(pose1, pose2);

  EXPECT_NEAR(angle_deg, 0.0, 1e-9);
}

// Boundary case: opposite vectors → angle ≈ 180°
TEST_F(CalcTransAngleTest_70, OppositeDirectionReturns180Degrees_70) {
  Rigid3d pose1 = MakePoseWithTranslation(Eigen::Vector3d(1.0, 0.0, 0.0));
  Rigid3d pose2 = MakePoseWithTranslation(Eigen::Vector3d(-1.0, 0.0, 0.0));

  const double angle_deg = CalcTransAngle(pose1, pose2);

  EXPECT_NEAR(angle_deg, 180.0, 1e-9);
}

// Normal case: orthogonal vectors → angle ≈ 90°
TEST_F(CalcTransAngleTest_70, OrthogonalTranslationsReturn90Degrees_70) {
  Rigid3d pose1 = MakePoseWithTranslation(Eigen::Vector3d(1.0, 0.0, 0.0));
  Rigid3d pose2 = MakePoseWithTranslation(Eigen::Vector3d(0.0, 1.0, 0.0));

  const double angle_deg = CalcTransAngle(pose1, pose2);

  EXPECT_NEAR(angle_deg, 90.0, 1e-9);
}

// Normal case: non-unit vectors with known angle (45° between (1,0,0) and (1,1,0))
TEST_F(CalcTransAngleTest_70, NonUnitVectorsReturnCorrectAngle_70) {
  Rigid3d pose1 = MakePoseWithTranslation(Eigen::Vector3d(1.0, 0.0, 0.0));
  Rigid3d pose2 = MakePoseWithTranslation(Eigen::Vector3d(1.0, 1.0, 0.0));

  const double angle_deg = CalcTransAngle(pose1, pose2);

  EXPECT_NEAR(angle_deg, 45.0, 1e-9);
}

// Property-based behavior: symmetry CalcTransAngle(a,b) == CalcTransAngle(b,a)
TEST_F(CalcTransAngleTest_70, AngleIsSymmetricWrtArguments_70) {
  Rigid3d pose1 = MakePoseWithTranslation(Eigen::Vector3d(1.0, 2.0, 3.0));
  Rigid3d pose2 = MakePoseWithTranslation(Eigen::Vector3d(-4.0, 5.0, -6.0));

  const double angle_ab = CalcTransAngle(pose1, pose2);
  const double angle_ba = CalcTransAngle(pose2, pose1);

  EXPECT_NEAR(angle_ab, angle_ba, 1e-9);
}

// Range check: result is always within [0, 180]
TEST_F(CalcTransAngleTest_70, AngleIsWithinValidRange_70) {
  Rigid3d pose1 = MakePoseWithTranslation(Eigen::Vector3d(1.0, 2.0, 3.0));
  Rigid3d pose2 = MakePoseWithTranslation(Eigen::Vector3d(4.0, 5.0, 6.0));

  const double angle_deg = CalcTransAngle(pose1, pose2);

  EXPECT_LE(angle_deg, 180.0);
  EXPECT_GE(angle_deg, 0.0);
}

}  // namespace glomap
