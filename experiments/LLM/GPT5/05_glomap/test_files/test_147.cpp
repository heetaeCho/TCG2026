// File: glomap/math/rigid3d_test.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "glomap/math/rigid3d.h"
#include "glomap/types.h"

namespace glomap {

class AngleAxisToRotationTest_147 : public ::testing::Test {
 protected:
  // Utility: check if a matrix is a proper rotation matrix within tolerance.
  static void ExpectProperRotation(const Eigen::Matrix3d& R,
                                   double tol = 1e-12) {
    Eigen::Matrix3d should_be_identity = R * R.transpose();
    EXPECT_TRUE(should_be_identity.isApprox(Eigen::Matrix3d::Identity(), tol));
    EXPECT_NEAR(R.determinant(), 1.0, tol);
  }
};

// [Normal operation] Zero vector should produce identity matrix.
TEST_F(AngleAxisToRotationTest_147, ZeroVectorReturnsIdentity_147) {
  Eigen::Vector3d aa_vec = Eigen::Vector3d::Zero();

  Eigen::Matrix3d R = AngleAxisToRotation(aa_vec);

  EXPECT_TRUE(R.isApprox(Eigen::Matrix3d::Identity(), 1e-15));
  // Identity is a valid rotation matrix.
  ExpectProperRotation(R);
}

// [Normal operation] 90-degree rotation around Z axis.
TEST_F(AngleAxisToRotationTest_147, NinetyDegreeRotationAroundZ_147) {
  const double angle = M_PI / 2.0;
  Eigen::Vector3d aa_vec(0.0, 0.0, angle);

  Eigen::Matrix3d R = AngleAxisToRotation(aa_vec);

  Eigen::Matrix3d expected;
  expected << 0.0, -1.0, 0.0,
              1.0,  0.0, 0.0,
              0.0,  0.0, 1.0;

  EXPECT_TRUE(R.isApprox(expected, 1e-12));
  ExpectProperRotation(R);
}

// [Normal operation] Arbitrary axis: result should match Eigen::AngleAxis.
TEST_F(AngleAxisToRotationTest_147, ArbitraryAxisMatchesEigenAngleAxis_147) {
  Eigen::Vector3d axis(1.0, 2.0, 3.0);
  axis.normalize();
  const double angle = 0.3;  // radians
  Eigen::Vector3d aa_vec = axis * angle;

  Eigen::Matrix3d R = AngleAxisToRotation(aa_vec);

  Eigen::Matrix3d expected =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();

  EXPECT_TRUE(R.isApprox(expected, 1e-12));
  ExpectProperRotation(R);
}

// [Boundary] Very small angle along X-axis (norm < EPS) should be close to identity
// and consistent with Eigen::AngleAxis.
TEST_F(AngleAxisToRotationTest_147, VerySmallAngleBelowEpsAlongX_147) {
  // Make sure the norm is strictly smaller than EPS.
  Eigen::Vector3d aa_vec(glomap::EPS * 0.5, 0.0, 0.0);

  Eigen::Matrix3d R = AngleAxisToRotation(aa_vec);

  // For very small angles, a rotation matrix is almost identity.
  EXPECT_TRUE(R.isApprox(Eigen::Matrix3d::Identity(), 1e-12));

  // Also compare against Eigen::AngleAxis result (expected semantics).
  double angle = aa_vec.norm();
  Eigen::Vector3d axis = aa_vec.normalized();
  Eigen::Matrix3d expected =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();

  EXPECT_TRUE(R.isApprox(expected, 1e-12));
}

// [Boundary] Very small angle with non-axis-aligned vector (norm < EPS)
// should still be stable and consistent with Eigen::AngleAxis.
TEST_F(AngleAxisToRotationTest_147, VerySmallNonAxisAlignedBelowEps_147) {
  Eigen::Vector3d base(glomap::EPS * 0.4,
                       -glomap::EPS * 0.3,
                        glomap::EPS * 0.2);
  // Ensure the norm is below EPS.
  ASSERT_LT(base.norm(), glomap::EPS);
  Eigen::Vector3d aa_vec = base;

  Eigen::Matrix3d R = AngleAxisToRotation(aa_vec);

  // Close to identity.
  EXPECT_TRUE(R.isApprox(Eigen::Matrix3d::Identity(), 1e-12));

  // And consistent with Eigen::AngleAxis semantics.
  double angle = aa_vec.norm();
  if (angle > 0.0) {
    Eigen::Vector3d axis = aa_vec.normalized();
    Eigen::Matrix3d expected =
        Eigen::AngleAxisd(angle, axis).toRotationMatrix();
    EXPECT_TRUE(R.isApprox(expected, 1e-12));
  } else {
    // Degenerate case: zero; identity expected.
    EXPECT_TRUE(R.isApprox(Eigen::Matrix3d::Identity(), 1e-15));
  }
}

// [Boundary / Robustness] Angle just above EPS should behave like a proper
// small rotation and still be a valid rotation matrix.
TEST_F(AngleAxisToRotationTest_147, AngleSlightlyAboveEpsProducesRotation_147) {
  Eigen::Vector3d aa_vec(glomap::EPS * 2.0, 0.0, 0.0);

  Eigen::Matrix3d R = AngleAxisToRotation(aa_vec);

  // Compare against Eigen::AngleAxis semantics.
  double angle = aa_vec.norm();
  Eigen::Vector3d axis = aa_vec.normalized();
  Eigen::Matrix3d expected =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();

  EXPECT_TRUE(R.isApprox(expected, 1e-12));
  ExpectProperRotation(R);
}

}  // namespace glomap
