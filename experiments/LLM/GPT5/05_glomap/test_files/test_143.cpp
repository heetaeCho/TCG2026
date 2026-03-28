// File: rigid3d_calc_trans_angle_test_143.cc

#include <gtest/gtest.h>

#include "glomap/math/rigid3d.h"

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace glomap {

class CalcTransAngleTest_143 : public ::testing::Test {
 protected:
  using Vector3d = Eigen::Vector3d;
  using Quaterniond = Eigen::Quaterniond;

  Rigid3d MakePose(const Vector3d& t) {
    return Rigid3d(Quaterniond::Identity(), t);
  }
};

// Normal case: parallel, same direction -> 0 degrees
TEST_F(CalcTransAngleTest_143, ParallelSameDirection_ReturnsZero_143) {
  Rigid3d pose1 = MakePose(Vector3d(1.0, 0.0, 0.0));
  Rigid3d pose2 = MakePose(Vector3d(2.0, 0.0, 0.0));

  const double angle = CalcTransAngle(pose1, pose2);

  EXPECT_NEAR(angle, 0.0, 1e-9);
}

// Normal case: opposite directions -> 180 degrees
TEST_F(CalcTransAngleTest_143, OppositeDirections_Returns180Degrees_143) {
  Rigid3d pose1 = MakePose(Vector3d(1.0, 0.0, 0.0));
  Rigid3d pose2 = MakePose(Vector3d(-1.0, 0.0, 0.0));

  const double angle = CalcTransAngle(pose1, pose2);

  EXPECT_NEAR(angle, 180.0, 1e-6);
}

// Normal case: orthogonal translations -> 90 degrees
TEST_F(CalcTransAngleTest_143, OrthogonalTranslations_Returns90Degrees_143) {
  Rigid3d pose1 = MakePose(Vector3d(1.0, 0.0, 0.0));
  Rigid3d pose2 = MakePose(Vector3d(0.0, 1.0, 0.0));

  const double angle = CalcTransAngle(pose1, pose2);

  EXPECT_NEAR(angle, 90.0, 1e-6);
}

// Boundary-ish: non-trivial acute angle between 0 and 90 degrees
TEST_F(CalcTransAngleTest_143, AcuteAngle_IsBetween0And90_AndConsistent_143) {
  Rigid3d pose1 = MakePose(Vector3d(1.0, 0.0, 0.0));
  Rigid3d pose2 = MakePose(Vector3d(1.0, 1.0, 0.0));

  const double angle = CalcTransAngle(pose1, pose2);

  // Expected angle is 45 degrees
  EXPECT_GT(angle, 0.0);
  EXPECT_LT(angle, 90.0);
  EXPECT_NEAR(angle, 45.0, 1e-6);
}

// Boundary-ish: obtuse angle between 90 and 180 degrees
TEST_F(CalcTransAngleTest_143, ObtuseAngle_IsBetween90And180_AndConsistent_143) {
  Rigid3d pose1 = MakePose(Vector3d(1.0, 0.0, 0.0));
  Rigid3d pose2 = MakePose(Vector3d(-1.0, 1.0, 0.0));

  const double angle = CalcTransAngle(pose1, pose2);

  // Angle should be between 90 and 180 degrees and around 135 degrees
  EXPECT_GT(angle, 90.0);
  EXPECT_LT(angle, 180.0);
  EXPECT_NEAR(angle, 135.0, 1e-6);
}

// Property: symmetry CalcTransAngle(p1, p2) == CalcTransAngle(p2, p1)
TEST_F(CalcTransAngleTest_143, Symmetry_BetweenArguments_143) {
  Rigid3d pose1 = MakePose(Vector3d(1.0, 2.0, 3.0));
  Rigid3d pose2 = MakePose(Vector3d(-4.0, 5.0, -6.0));

  const double angle12 = CalcTransAngle(pose1, pose2);
  const double angle21 = CalcTransAngle(pose2, pose1);

  EXPECT_NEAR(angle12, angle21, 1e-9);
}

// Scaling invariance: scaling translations should not change the angle
TEST_F(CalcTransAngleTest_143, ScalingTranslations_DoesNotChangeAngle_143) {
  Rigid3d pose1 = MakePose(Vector3d(1.0, 2.0, 3.0));
  Rigid3d pose2 = MakePose(Vector3d(4.0, 5.0, 6.0));

  Rigid3d pose1_scaled = MakePose(10.0 * pose1.translation);
  Rigid3d pose2_scaled = MakePose(0.5 * pose2.translation);

  const double angle_original = CalcTransAngle(pose1, pose2);
  const double angle_scaled = CalcTransAngle(pose1_scaled, pose2_scaled);

  EXPECT_NEAR(angle_original, angle_scaled, 1e-9);
}

}  // namespace glomap
