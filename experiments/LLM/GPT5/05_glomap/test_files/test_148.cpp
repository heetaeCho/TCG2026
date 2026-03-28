// File: center_from_pose_test_148.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "glomap/math/rigid3d.h"

namespace {

class CenterFromPoseTest_148 : public ::testing::Test {};

// Helper to get the rotation type without assuming its concrete Eigen type.
template <typename RigidType>
using RotationTypeOf = decltype(std::declval<RigidType>().rotation);

//----------------------------------------------------------------------------
// 1) Identity rotation & zero translation -> center at origin
//----------------------------------------------------------------------------
TEST_F(CenterFromPoseTest_148,
       IdentityRotationZeroTranslation_ReturnsOrigin_148) {
  glomap::Rigid3d pose;
  pose.rotation.setIdentity();
  pose.translation = Eigen::Vector3d::Zero();

  const Eigen::Vector3d center = glomap::CenterFromPose(pose);

  EXPECT_DOUBLE_EQ(center.x(), 0.0);
  EXPECT_DOUBLE_EQ(center.y(), 0.0);
  EXPECT_DOUBLE_EQ(center.z(), 0.0);
}

//----------------------------------------------------------------------------
// 2) Identity rotation -> center is negative translation
//----------------------------------------------------------------------------
TEST_F(CenterFromPoseTest_148,
       IdentityRotation_NegatesTranslation_148) {
  glomap::Rigid3d pose;
  pose.rotation.setIdentity();
  pose.translation = Eigen::Vector3d(1.0, -2.0, 3.5);

  const Eigen::Vector3d center = glomap::CenterFromPose(pose);

  EXPECT_DOUBLE_EQ(center.x(), -1.0);
  EXPECT_DOUBLE_EQ(center.y(),  2.0);
  EXPECT_DOUBLE_EQ(center.z(), -3.5);
}

//----------------------------------------------------------------------------
// 3) 180-degree rotation around Z with a simple translation
//    For a 180° rotation around Z: (x, y, z) -> (-x, -y, z)
//    With translation t = (1, 0, 0), the expected camera center is (1, 0, 0).
//----------------------------------------------------------------------------
TEST_F(CenterFromPoseTest_148,
       Rotation180AroundZ_TransformsCenterAsExpected_148) {
  glomap::Rigid3d pose;

  using RotationT = RotationTypeOf<glomap::Rigid3d>;

  const double kPi = std::acos(-1.0);
  // Build a 180-degree rotation around Z as a rotation matrix,
  // then assign it to whatever rotation type Rigid3d uses.
  Eigen::Matrix3d rot_matrix =
      Eigen::AngleAxisd(kPi, Eigen::Vector3d::UnitZ()).toRotationMatrix();
  RotationT rot = rot_matrix;
  pose.rotation = rot;

  pose.translation = Eigen::Vector3d(1.0, 0.0, 0.0);

  const Eigen::Vector3d center = glomap::CenterFromPose(pose);

  const double kEps = 1e-12;
  EXPECT_NEAR(center.x(), 1.0, kEps);
  EXPECT_NEAR(center.y(), 0.0, kEps);
  EXPECT_NEAR(center.z(), 0.0, kEps);
}

//----------------------------------------------------------------------------
// 4) Zero translation with arbitrary rotation -> center at origin
//----------------------------------------------------------------------------
TEST_F(CenterFromPoseTest_148,
       ZeroTranslation_ArbitraryRotation_ReturnsOrigin_148) {
  glomap::Rigid3d pose;

  using RotationT = RotationTypeOf<glomap::Rigid3d>;

  const double kPi = std::acos(-1.0);
  // Arbitrary non-identity rotation (e.g., 0.3 * pi around axis (1,1,1))
  Eigen::Matrix3d rot_matrix =
      Eigen::AngleAxisd(0.3 * kPi,
                        Eigen::Vector3d(1.0, 1.0, 1.0).normalized())
          .toRotationMatrix();
  RotationT rot = rot_matrix;
  pose.rotation = rot;

  pose.translation = Eigen::Vector3d::Zero();

  const Eigen::Vector3d center = glomap::CenterFromPose(pose);

  EXPECT_DOUBLE_EQ(center.x(), 0.0);
  EXPECT_DOUBLE_EQ(center.y(), 0.0);
  EXPECT_DOUBLE_EQ(center.z(), 0.0);
}

}  // namespace
