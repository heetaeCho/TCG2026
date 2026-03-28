// File: rigid3d_calc_trans_test_69.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "glomap/math/rigid3d.h"

namespace {

using glomap::CalcTrans;
using glomap::Rigid3d;
using Eigen::Quaterniond;
using Eigen::Vector3d;

constexpr double kEps = 1e-10;

class CalcTransTest_69 : public ::testing::Test {};

// TEST_ID = 69
TEST_F(CalcTransTest_69, ZeroDistanceForIdenticalPoses_69) {
  // Same pose for both arguments should yield zero translation distance.
  Rigid3d pose(Quaterniond::Identity(), Vector3d(1.0, -2.0, 3.5));

  const double dist = CalcTrans(pose, pose);

  EXPECT_NEAR(dist, 0.0, kEps);
}

// TEST_ID = 69
TEST_F(CalcTransTest_69, ReturnsExpectedDistanceForSimpleTranslations_69) {
  // Two poses with identity rotation and simple translations.
  // The translation "baseline" between them should be 5 (3-4-5 triangle).
  Rigid3d pose1(Quaterniond::Identity(), Vector3d(0.0, 0.0, 0.0));
  Rigid3d pose2(Quaterniond::Identity(), Vector3d(3.0, 4.0, 0.0));

  const double dist = CalcTrans(pose1, pose2);

  EXPECT_NEAR(dist, 5.0, 1e-10);
}

// TEST_ID = 69
TEST_F(CalcTransTest_69, SymmetricWithRespectToPoseOrder_69) {
  // Swapping the two poses should not change the result.
  Rigid3d pose1(Quaterniond::Identity(), Vector3d(0.5, -1.0, 2.0));
  Rigid3d pose2(Quaterniond::Identity(), Vector3d(-2.0, 0.0, 1.0));

  const double dist12 = CalcTrans(pose1, pose2);
  const double dist21 = CalcTrans(pose2, pose1);

  EXPECT_NEAR(dist12, dist21, kEps);
}

// TEST_ID = 69
TEST_F(CalcTransTest_69, RotationDoesNotAffectTranslationDistanceWhenTranslationsMatch_69) {
  // If the two poses share the same translation but differ in rotation,
  // the translation distance should still be zero.
  const Vector3d t(1.0, 2.0, 3.0);

  Rigid3d pose1(Quaterniond::Identity(), t);

  // 90-degree rotation around Z, same translation.
  Quaterniond rot2(Eigen::AngleAxisd(M_PI / 2.0, Vector3d::UnitZ()));
  Rigid3d pose2(rot2, t);

  const double dist = CalcTrans(pose1, pose2);

  EXPECT_NEAR(dist, 0.0, kEps);
}

}  // namespace
