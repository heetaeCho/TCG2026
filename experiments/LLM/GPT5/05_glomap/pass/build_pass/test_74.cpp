// File: glomap/test/angle_axis_to_rotation_test_74.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "glomap/math/rigid3d.h"

namespace {

using glomap::AngleAxisToRotation;

// TEST_ID: 74

// Zero angle-axis vector should produce the identity rotation matrix.
TEST(AngleAxisToRotationTest_74, ZeroAngleReturnsIdentity_74) {
  const Eigen::Vector3d aa_vec = Eigen::Vector3d::Zero();

  const Eigen::Matrix3d R = AngleAxisToRotation(aa_vec);

  const Eigen::Matrix3d I = Eigen::Matrix3d::Identity();
  EXPECT_TRUE(R.isApprox(I, 1e-15));
}

// A pure rotation around the X-axis by 90 degrees should match Eigen's AngleAxis.
TEST(AngleAxisToRotationTest_74, XAxisQuarterTurnMatchesEigen_74) {
  const double angle = M_PI / 2.0;
  const Eigen::Vector3d aa_vec(angle, 0.0, 0.0);  // angle * unit-x

  const Eigen::Matrix3d R = AngleAxisToRotation(aa_vec);

  const Eigen::AngleAxisd aa(angle, Eigen::Vector3d::UnitX());
  const Eigen::Matrix3d expected = aa.toRotationMatrix();

  EXPECT_TRUE(R.isApprox(expected, 1e-12));
}

// A general non-axis-aligned angle-axis vector should produce a rotation
// consistent with Eigen's AngleAxis representation.
TEST(AngleAxisToRotationTest_74, GeneralAngleAxisMatchesEigen_74) {
  const Eigen::Vector3d aa_vec(0.3, -0.4, 0.5);

  const Eigen::Matrix3d R = AngleAxisToRotation(aa_vec);

  const double angle = aa_vec.norm();
  if (angle > 0.0) {
    const Eigen::Vector3d axis = aa_vec.normalized();
    const Eigen::AngleAxisd aa(angle, axis);
    const Eigen::Matrix3d expected = aa.toRotationMatrix();

    EXPECT_TRUE(R.isApprox(expected, 1e-12));
  } else {
    // For completeness: if aa_vec is zero, we already have a dedicated test.
    const Eigen::Matrix3d I = Eigen::Matrix3d::Identity();
    EXPECT_TRUE(R.isApprox(I, 1e-15));
  }
}

// The result should be a proper rotation matrix: orthonormal with determinant 1.
TEST(AngleAxisToRotationTest_74, ResultIsProperRotationMatrix_74) {
  const Eigen::Vector3d aa_vec(1.0, 2.0, 3.0);

  const Eigen::Matrix3d R = AngleAxisToRotation(aa_vec);

  const Eigen::Matrix3d RtR = R.transpose() * R;
  EXPECT_TRUE(RtR.isApprox(Eigen::Matrix3d::Identity(), 1e-12));
  EXPECT_NEAR(R.determinant(), 1.0, 1e-12);
}

// Rotations for +aa and -aa should be inverses of each other.
TEST(AngleAxisToRotationTest_74, OppositeAngleAxisVectorsProduceInverseRotations_74) {
  const Eigen::Vector3d aa_vec(0.2, -0.1, 0.3);

  const Eigen::Matrix3d R = AngleAxisToRotation(aa_vec);
  const Eigen::Matrix3d R_inv = AngleAxisToRotation(-aa_vec);

  const Eigen::Matrix3d I = Eigen::Matrix3d::Identity();
  EXPECT_TRUE((R * R_inv).isApprox(I, 1e-12));
  EXPECT_TRUE((R_inv * R).isApprox(I, 1e-12));
}

}  // namespace
