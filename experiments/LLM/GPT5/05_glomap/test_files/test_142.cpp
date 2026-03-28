// File: rigid3d_calc_trans_test_142.cc

#include "glomap/math/rigid3d.h"

#include <Eigen/Core>
#include <gtest/gtest.h>

// All tests target: glomap::CalcTrans(const Rigid3d&, const Rigid3d&)
// TEST_ID: 142

namespace {

TEST(CalcTransTest_142, SamePoseReturnsZero_142) {
  glomap::Rigid3d pose;
  // Use a non-zero translation to ensure the result is not trivially zero
  pose.translation = Eigen::Vector3d(1.0, -2.0, 3.0);

  const double distance = glomap::CalcTrans(pose, pose);

  // Distance between identical poses should be zero.
  EXPECT_DOUBLE_EQ(distance, 0.0);
}

TEST(CalcTransTest_142, PureTranslationAlongXAxisMatchesDistance_142) {
  glomap::Rigid3d pose1;
  glomap::Rigid3d pose2;

  pose1.translation = Eigen::Vector3d(0.0, 0.0, 0.0);
  pose2.translation = Eigen::Vector3d(5.0, 0.0, 0.0);

  const double distance = glomap::CalcTrans(pose1, pose2);

  // For identity rotations, the distance should match the difference in
  // translation along the x-axis (here: 5.0 units).
  EXPECT_DOUBLE_EQ(distance, 5.0);
}

TEST(CalcTransTest_142, DistanceIsSymmetricBetweenTwoPoses_142) {
  glomap::Rigid3d pose1;
  glomap::Rigid3d pose2;

  pose1.translation = Eigen::Vector3d(1.0, 2.0, 3.0);
  pose2.translation = Eigen::Vector3d(-4.0, 5.0, -6.0);

  const double d12 = glomap::CalcTrans(pose1, pose2);
  const double d21 = glomap::CalcTrans(pose2, pose1);

  // Distance between two poses should be symmetric.
  EXPECT_DOUBLE_EQ(d12, d21);
}

TEST(CalcTransTest_142, LargerTranslationLeadsToLargerDistanceFromOrigin_142) {
  glomap::Rigid3d origin;
  glomap::Rigid3d near_pose;
  glomap::Rigid3d far_pose;

  origin.translation    = Eigen::Vector3d(0.0, 0.0, 0.0);
  near_pose.translation = Eigen::Vector3d(1.0, 1.0, 1.0);  // distance ~ sqrt(3)
  far_pose.translation  = Eigen::Vector3d(3.0, 0.0, 0.0);  // distance = 3.0 > sqrt(3)

  const double d_near = glomap::CalcTrans(origin, near_pose);
  const double d_far  = glomap::CalcTrans(origin, far_pose);

  // A pose that is "farther" in translation should yield a larger distance.
  EXPECT_GT(d_far, d_near);

  // Distances should always be non-negative.
  EXPECT_GE(d_near, 0.0);
  EXPECT_GE(d_far, 0.0);
}

}  // namespace
