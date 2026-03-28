#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

// Adjust the include path to match your project structure if needed.
#include "glomap/math/gravity.h"

using Eigen::Matrix3d;
using Eigen::Vector3d;

namespace {

class GetAlignRotTest_62 : public ::testing::Test {
protected:
  // Helper to check that a matrix is a proper rotation matrix
  // (orthonormal with determinant close to +1).
  void ExpectRotationMatrix_62(const Matrix3d& R, double tol = 1e-12) {
    Matrix3d should_be_identity = R.transpose() * R;

    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        double expected = (i == j) ? 1.0 : 0.0;
        EXPECT_NEAR(should_be_identity(i, j), expected, tol);
      }
    }

    double det = R.determinant();
    EXPECT_NEAR(det, 1.0, 1e-10);
  }
};

// Normal operation: gravity aligned with +Y axis.
TEST_F(GetAlignRotTest_62, AlignsYToPositiveGravity_62) {
  const Vector3d gravity = Vector3d::UnitY();

  Matrix3d R = glomap::GetAlignRot(gravity);

  // Check rotation-matrix properties.
  ExpectRotationMatrix_62(R);

  // Check that the rotation maps the Y-axis to the gravity direction.
  Vector3d result = R * Vector3d::UnitY();
  EXPECT_NEAR(result.x(), gravity.x(), 1e-12);
  EXPECT_NEAR(result.y(), gravity.y(), 1e-12);
  EXPECT_NEAR(result.z(), gravity.z(), 1e-12);
}

// Normal operation: gravity aligned with -Y axis.
TEST_F(GetAlignRotTest_62, AlignsYToNegativeGravity_62) {
  const Vector3d gravity(0.0, -1.0, 0.0);

  Matrix3d R = glomap::GetAlignRot(gravity);

  ExpectRotationMatrix_62(R);

  Vector3d result = R * Vector3d::UnitY();
  EXPECT_NEAR(result.x(), gravity.x(), 1e-12);
  EXPECT_NEAR(result.y(), gravity.y(), 1e-12);
  EXPECT_NEAR(result.z(), gravity.z(), 1e-12);
}

// Normal operation: gravity is a non-axis arbitrary vector.
TEST_F(GetAlignRotTest_62, AlignsYToArbitraryGravityDirection_62) {
  const Vector3d gravity(1.0, 2.0, 3.0);
  const Vector3d gravity_normalized = gravity.normalized();

  Matrix3d R = glomap::GetAlignRot(gravity);

  ExpectRotationMatrix_62(R);

  // Y-axis should be mapped to the normalized gravity direction.
  Vector3d result = R * Vector3d::UnitY();
  EXPECT_NEAR(result.x(), gravity_normalized.x(), 1e-12);
  EXPECT_NEAR(result.y(), gravity_normalized.y(), 1e-12);
  EXPECT_NEAR(result.z(), gravity_normalized.z(), 1e-12);
}

// Boundary-ish case: gravity has very large magnitude but same direction.
TEST_F(GetAlignRotTest_62, HandlesLargeMagnitudeGravity_62) {
  const Vector3d gravity(1e6, -2e6, 5e5);
  const Vector3d gravity_normalized = gravity.normalized();

  Matrix3d R = glomap::GetAlignRot(gravity);

  ExpectRotationMatrix_62(R);

  Vector3d result = R * Vector3d::UnitY();
  EXPECT_NEAR(result.x(), gravity_normalized.x(), 1e-12);
  EXPECT_NEAR(result.y(), gravity_normalized.y(), 1e-12);
  EXPECT_NEAR(result.z(), gravity_normalized.z(), 1e-12);
}

// Additional robustness check: multiple orthogonality checks on columns.
TEST_F(GetAlignRotTest_62, ColumnsFormOrthonormalBasis_62) {
  const Vector3d gravity(0.3, 0.4, 0.5);

  Matrix3d R = glomap::GetAlignRot(gravity);

  ExpectRotationMatrix_62(R);

  // Explicitly check columns for orthonormality.
  Vector3d c0 = R.col(0);
  Vector3d c1 = R.col(1);
  Vector3d c2 = R.col(2);

  EXPECT_NEAR(c0.norm(), 1.0, 1e-12);
  EXPECT_NEAR(c1.norm(), 1.0, 1e-12);
  EXPECT_NEAR(c2.norm(), 1.0, 1e-12);

  EXPECT_NEAR(c0.dot(c1), 0.0, 1e-12);
  EXPECT_NEAR(c0.dot(c2), 0.0, 1e-12);
  EXPECT_NEAR(c1.dot(c2), 0.0, 1e-12);
}

}  // namespace
