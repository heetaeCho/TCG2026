#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

// Forward declare the function under test
namespace glomap {
extern const double EPS;
Eigen::Matrix3d AngleAxisToRotation(const Eigen::Vector3d& aa_vec);
}

class Rigid3dTest_147 : public ::testing::Test {
 protected:
  void SetUp() override {}

  // Helper to check if a matrix is a valid rotation matrix
  void ExpectValidRotationMatrix(const Eigen::Matrix3d& R) {
    // R^T * R should be identity
    Eigen::Matrix3d RtR = R.transpose() * R;
    EXPECT_NEAR((RtR - Eigen::Matrix3d::Identity()).norm(), 0.0, 1e-10);
    // det(R) should be 1
    EXPECT_NEAR(R.determinant(), 1.0, 1e-10);
  }
};

// Test zero rotation vector returns identity matrix
TEST_F(Rigid3dTest_147, ZeroVectorReturnsIdentity_147) {
  Eigen::Vector3d aa_vec(0.0, 0.0, 0.0);
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
  EXPECT_NEAR((R - Eigen::Matrix3d::Identity()).norm(), 0.0, 1e-12);
}

// Test rotation around X axis by pi/2
TEST_F(Rigid3dTest_147, RotationAroundXAxis_147) {
  double angle = M_PI / 2.0;
  Eigen::Vector3d aa_vec(angle, 0.0, 0.0);
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);

  Eigen::Matrix3d expected =
      Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX()).toRotationMatrix();

  EXPECT_NEAR((R - expected).norm(), 0.0, 1e-10);
  ExpectValidRotationMatrix(R);
}

// Test rotation around Y axis by pi/2
TEST_F(Rigid3dTest_147, RotationAroundYAxis_147) {
  double angle = M_PI / 2.0;
  Eigen::Vector3d aa_vec(0.0, angle, 0.0);
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);

  Eigen::Matrix3d expected =
      Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitY()).toRotationMatrix();

  EXPECT_NEAR((R - expected).norm(), 0.0, 1e-10);
  ExpectValidRotationMatrix(R);
}

// Test rotation around Z axis by pi/2
TEST_F(Rigid3dTest_147, RotationAroundZAxis_147) {
  double angle = M_PI / 2.0;
  Eigen::Vector3d aa_vec(0.0, 0.0, angle);
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);

  Eigen::Matrix3d expected =
      Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()).toRotationMatrix();

  EXPECT_NEAR((R - expected).norm(), 0.0, 1e-10);
  ExpectValidRotationMatrix(R);
}

// Test rotation by pi (180 degrees) around an arbitrary axis
TEST_F(Rigid3dTest_147, RotationByPi_147) {
  Eigen::Vector3d axis = Eigen::Vector3d(1.0, 1.0, 1.0).normalized();
  double angle = M_PI;
  Eigen::Vector3d aa_vec = angle * axis;
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);

  Eigen::Matrix3d expected =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();

  EXPECT_NEAR((R - expected).norm(), 0.0, 1e-10);
  ExpectValidRotationMatrix(R);
}

// Test very small rotation vector (below EPS threshold) - should use linear approximation
TEST_F(Rigid3dTest_147, VerySmallRotationBelowEps_147) {
  // EPS is ~1e-12, so use something smaller
  double tiny = 1e-14;
  Eigen::Vector3d aa_vec(tiny, tiny, tiny);
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);

  // For very small angles, the result should be close to:
  // I + [aa]_x (skew symmetric)
  Eigen::Matrix3d expected;
  expected << 1, -tiny, tiny,
              tiny, 1, -tiny,
              -tiny, tiny, 1;

  EXPECT_NEAR((R - expected).norm(), 0.0, 1e-20);
}

// Test rotation vector just above EPS threshold
TEST_F(Rigid3dTest_147, RotationJustAboveEps_147) {
  double small_angle = 1e-11; // Above EPS (~1e-12)
  Eigen::Vector3d aa_vec(small_angle, 0.0, 0.0);
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);

  Eigen::Matrix3d expected =
      Eigen::AngleAxisd(small_angle, Eigen::Vector3d::UnitX()).toRotationMatrix();

  EXPECT_NEAR((R - expected).norm(), 0.0, 1e-10);
  ExpectValidRotationMatrix(R);
}

// Test rotation vector just below EPS threshold
TEST_F(Rigid3dTest_147, RotationJustBelowEps_147) {
  double small_angle = 1e-14; // Well below EPS
  Eigen::Vector3d aa_vec(small_angle, 0.0, 0.0);
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);

  // Should use the linear approximation branch
  // Expected: identity + skew(aa_vec)
  EXPECT_NEAR(R(0, 0), 1.0, 1e-13);
  EXPECT_NEAR(R(1, 1), 1.0, 1e-13);
  EXPECT_NEAR(R(2, 2), 1.0, 1e-13);
  EXPECT_NEAR(R(2, 1), small_angle, 1e-20);
  EXPECT_NEAR(R(1, 2), -small_angle, 1e-20);
}

// Test arbitrary rotation
TEST_F(Rigid3dTest_147, ArbitraryRotation_147) {
  Eigen::Vector3d aa_vec(0.5, -0.3, 0.8);
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);

  double angle = aa_vec.norm();
  Eigen::Vector3d axis = aa_vec.normalized();
  Eigen::Matrix3d expected =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();

  EXPECT_NEAR((R - expected).norm(), 0.0, 1e-10);
  ExpectValidRotationMatrix(R);
}

// Test large rotation angle (greater than 2*pi)
TEST_F(Rigid3dTest_147, LargeRotationAngle_147) {
  double angle = 3.0 * M_PI;
  Eigen::Vector3d axis = Eigen::Vector3d(0.0, 0.0, 1.0);
  Eigen::Vector3d aa_vec = angle * axis;
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);

  Eigen::Matrix3d expected =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();

  EXPECT_NEAR((R - expected).norm(), 0.0, 1e-10);
  ExpectValidRotationMatrix(R);
}

// Test negative angle rotation
TEST_F(Rigid3dTest_147, NegativeAngle_147) {
  Eigen::Vector3d aa_vec(-1.0, 0.0, 0.0);
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);

  Eigen::Matrix3d expected =
      Eigen::AngleAxisd(1.0, -Eigen::Vector3d::UnitX()).toRotationMatrix();

  EXPECT_NEAR((R - expected).norm(), 0.0, 1e-10);
  ExpectValidRotationMatrix(R);
}

// Test that result is orthogonal for various inputs
TEST_F(Rigid3dTest_147, ResultIsOrthogonal_147) {
  std::vector<Eigen::Vector3d> test_vecs = {
      {0.1, 0.2, 0.3},
      {-0.5, 0.5, -0.5},
      {M_PI, 0, 0},
      {0, M_PI, 0},
      {0, 0, M_PI},
      {1.5, 2.3, -0.7},
  };

  for (const auto& v : test_vecs) {
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(v);
    ExpectValidRotationMatrix(R);
  }
}

// Test that applying rotation twice gives expected compound rotation
TEST_F(Rigid3dTest_147, DoubleRotation_147) {
  double angle = M_PI / 4.0;
  Eigen::Vector3d aa_vec(0.0, 0.0, angle);
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
  Eigen::Matrix3d R2 = R * R;

  Eigen::Vector3d aa_double(0.0, 0.0, 2.0 * angle);
  Eigen::Matrix3d R_double = glomap::AngleAxisToRotation(aa_double);

  EXPECT_NEAR((R2 - R_double).norm(), 0.0, 1e-10);
}

// Test single component small rotation vectors
TEST_F(Rigid3dTest_147, SmallRotationSingleComponentX_147) {
  double tiny = 1e-15;
  Eigen::Vector3d aa_vec(tiny, 0.0, 0.0);
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);

  // Linear approximation branch
  EXPECT_NEAR(R(0, 0), 1.0, 1e-14);
  EXPECT_NEAR(R(1, 1), 1.0, 1e-14);
  EXPECT_NEAR(R(2, 2), 1.0, 1e-14);
  EXPECT_NEAR(R(2, 1), tiny, 1e-20);
  EXPECT_NEAR(R(1, 2), -tiny, 1e-20);
  EXPECT_NEAR(R(0, 1), 0.0, 1e-20);
  EXPECT_NEAR(R(0, 2), 0.0, 1e-20);
  EXPECT_NEAR(R(1, 0), 0.0, 1e-20);
  EXPECT_NEAR(R(2, 0), 0.0, 1e-20);
}

// Test at boundary: norm exactly at EPS boundary
TEST_F(Rigid3dTest_147, AtEpsBoundary_147) {
  // EPS = 9.9999999999999998E-13
  // Vector with norm slightly above EPS should use AngleAxis path
  double val = 1e-12; // ~EPS
  Eigen::Vector3d aa_vec(val, 0.0, 0.0);
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);

  // Result should be close to identity regardless of which branch
  EXPECT_NEAR((R - Eigen::Matrix3d::Identity()).norm(), 0.0, 1e-10);
}

// Test rotation vector with all negative components
TEST_F(Rigid3dTest_147, AllNegativeComponents_147) {
  Eigen::Vector3d aa_vec(-0.3, -0.5, -0.7);
  Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);

  double angle = aa_vec.norm();
  Eigen::Vector3d axis = aa_vec.normalized();
  Eigen::Matrix3d expected =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();

  EXPECT_NEAR((R - expected).norm(), 0.0, 1e-10);
  ExpectValidRotationMatrix(R);
}
