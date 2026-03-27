// File: gravity_test_131.cc

#include <gtest/gtest.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "glomap/math/gravity.h"

namespace {

class GetAlignRotTest_131 : public ::testing::Test {
protected:
  // Helper: check if a matrix is (approximately) orthonormal with det ~= 1.
  static void ExpectRotationMatrix(const Eigen::Matrix3d& R,
                                   double tol = 1e-10) {
    Eigen::Matrix3d should_be_I = R.transpose() * R;
    Eigen::Matrix3d I = Eigen::Matrix3d::Identity();
    EXPECT_NEAR((should_be_I - I).norm(), 0.0, tol);
    double det = R.determinant();
    EXPECT_NEAR(det, 1.0, tol);
  }
};

// Normal case: Y-axis is aligned with gravity direction.
TEST_F(GetAlignRotTest_131, AlignsYWithGravityDirection_131) {
  // Gravity pointing down in world Y: (0, -9.81, 0)
  const Eigen::Vector3d gravity(0.0, -9.81, 0.0);

  const Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  // The rotation should map the local +Y axis to the gravity direction.
  const Eigen::Vector3d unit_y = Eigen::Vector3d::UnitY();
  const Eigen::Vector3d aligned = R * unit_y;
  const Eigen::Vector3d expected = gravity.normalized();

  EXPECT_NEAR((aligned - expected).norm(), 0.0, 1e-10);

  // And R should be a valid rotation matrix.
  ExpectRotationMatrix(R);
}

// Normal case: arbitrary non-axis-aligned gravity produces a rotation matrix.
TEST_F(GetAlignRotTest_131, ReturnsOrthonormalMatrixForArbitraryGravity_131) {
  const Eigen::Vector3d gravity(1.0, 2.0, 3.0);

  const Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  // Check rotation properties (orthonormal, det ~= 1).
  ExpectRotationMatrix(R);

  // Y-axis after rotation should be parallel and in same direction as gravity.
  const Eigen::Vector3d aligned = R * Eigen::Vector3d::UnitY();
  const Eigen::Vector3d expected = gravity.normalized();

  // Parallel & same direction: small angle between vectors.
  double cos_angle = aligned.normalized().dot(expected);
  EXPECT_NEAR(cos_angle, 1.0, 1e-10);
}

// Boundary: function should be invariant to gravity magnitude (only direction).
TEST_F(GetAlignRotTest_131, ScaleInvariantToGravityMagnitude_131) {
  const Eigen::Vector3d gravity1(1.0, 2.0, 3.0);
  const Eigen::Vector3d gravity2 = 10.0 * gravity1;  // Same direction, larger magnitude.

  const Eigen::Matrix3d R1 = glomap::GetAlignRot(gravity1);
  const Eigen::Matrix3d R2 = glomap::GetAlignRot(gravity2);

  // Rotations should be (nearly) identical.
  EXPECT_NEAR((R1 - R2).norm(), 0.0, 1e-10);
}

// Boundary: gravity aligned with world Z-axis.
TEST_F(GetAlignRotTest_131, HandlesGravityAlongZAxis_131) {
  const Eigen::Vector3d gravity(0.0, 0.0, -1.0);

  const Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  // Y-axis after rotation should align with gravity direction.
  const Eigen::Vector3d aligned = R * Eigen::Vector3d::UnitY();
  const Eigen::Vector3d expected = gravity.normalized();

  EXPECT_NEAR((aligned - expected).norm(), 0.0, 1e-10);

  // Still must be a proper rotation.
  ExpectRotationMatrix(R);
}

// Exceptional / error-like input: zero gravity vector.
TEST_F(GetAlignRotTest_131, ZeroGravityProducesNonFiniteRotation_131) {
  const Eigen::Vector3d gravity = Eigen::Vector3d::Zero();

  const Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  // For a zero vector, normalization is undefined; we just assert that
  // the result is not a valid finite rotation matrix. This captures the
  // observable behavior for this invalid input.
  EXPECT_FALSE(R.allFinite());
}

}  // namespace
