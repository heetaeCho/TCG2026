// File: rigid3d_test_73.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

// Assuming the declaration is available in this header.
// If your project uses a different path, adjust accordingly.
#include "glomap/math/rigid3d.h"

namespace {

using glomap::RotationToAngleAxis;

class RotationToAngleAxisTest_73 : public ::testing::Test {
protected:
  static constexpr double kTolerance;
  static constexpr double kPi;
};

constexpr double RotationToAngleAxisTest_73::kTolerance = 1e-10;
constexpr double RotationToAngleAxisTest_73::kPi = 3.14159265358979323846;

// -----------------------------------------------------------------------------
// Normal operation: identity rotation
// -----------------------------------------------------------------------------
TEST_F(RotationToAngleAxisTest_73, IdentityRotationReturnsZeroVector_73) {
  Eigen::Matrix3d rot = Eigen::Matrix3d::Identity();

  Eigen::Vector3d aa_vec = RotationToAngleAxis(rot);

  EXPECT_NEAR(0.0, aa_vec.x(), kTolerance);
  EXPECT_NEAR(0.0, aa_vec.y(), kTolerance);
  EXPECT_NEAR(0.0, aa_vec.z(), kTolerance);
}

// -----------------------------------------------------------------------------
// Normal operation: rotation of +90 degrees around X axis
// -----------------------------------------------------------------------------
TEST_F(RotationToAngleAxisTest_73, RotationAroundX90Degrees_73) {
  const double angle = kPi / 2.0;  // 90 degrees
  Eigen::AngleAxisd aa(angle, Eigen::Vector3d::UnitX());
  Eigen::Matrix3d rot = aa.toRotationMatrix();

  Eigen::Vector3d aa_vec = RotationToAngleAxis(rot);

  EXPECT_NEAR(angle, aa_vec.x(), kTolerance);
  EXPECT_NEAR(0.0,   aa_vec.y(), kTolerance);
  EXPECT_NEAR(0.0,   aa_vec.z(), kTolerance);
}

// -----------------------------------------------------------------------------
// Normal operation: rotation of -60 degrees around Y axis
// (checks sign handling of axis/angle representation)
// -----------------------------------------------------------------------------
TEST_F(RotationToAngleAxisTest_73, RotationAroundYMinus60Degrees_73) {
  const double angle = -kPi / 3.0;  // -60 degrees
  Eigen::AngleAxisd aa(angle, Eigen::Vector3d::UnitY());
  Eigen::Matrix3d rot = aa.toRotationMatrix();

  Eigen::Vector3d aa_vec = RotationToAngleAxis(rot);

  // For this rotation, angle-axis representation should correspond to
  // an effective vector whose Y component is -60 degrees (in radians).
  EXPECT_NEAR(0.0,   aa_vec.x(), kTolerance);
  EXPECT_NEAR(angle, aa_vec.y(), 1e-9);  // slightly relaxed tolerance
  EXPECT_NEAR(0.0,   aa_vec.z(), kTolerance);
}

// -----------------------------------------------------------------------------
// Boundary condition: rotation of 180 degrees around Z axis
// Note: axis direction is ambiguous for 180-degree rotations, so we check
//       the magnitude and that the rotation is along Z (X, Y near zero).
// -----------------------------------------------------------------------------
TEST_F(RotationToAngleAxisTest_73, RotationAroundZ180Degrees_73) {
  const double angle = kPi;  // 180 degrees
  Eigen::AngleAxisd aa(angle, Eigen::Vector3d::UnitZ());
  Eigen::Matrix3d rot = aa.toRotationMatrix();

  Eigen::Vector3d aa_vec = RotationToAngleAxis(rot);

  // X and Y components should be ~0 (rotation purely around Z).
  EXPECT_NEAR(0.0, aa_vec.x(), 1e-8);
  EXPECT_NEAR(0.0, aa_vec.y(), 1e-8);

  // Magnitude should be close to pi (axis may be +Z or -Z).
  EXPECT_NEAR(angle, aa_vec.norm(), 1e-8);
}

// -----------------------------------------------------------------------------
// Normal operation: rotation around an arbitrary normalized axis
// -----------------------------------------------------------------------------
TEST_F(RotationToAngleAxisTest_73, RotationAroundArbitraryAxis_73) {
  Eigen::Vector3d axis(1.0, 1.0, 1.0);
  axis.normalize();
  const double angle = kPi / 4.0;  // 45 degrees

  Eigen::AngleAxisd aa(angle, axis);
  Eigen::Matrix3d rot = aa.toRotationMatrix();

  Eigen::Vector3d aa_vec = RotationToAngleAxis(rot);

  // Expected angle-axis vector is angle * axis.
  Eigen::Vector3d expected = angle * axis;

  EXPECT_NEAR(expected.x(), aa_vec.x(), 1e-8);
  EXPECT_NEAR(expected.y(), aa_vec.y(), 1e-8);
  EXPECT_NEAR(expected.z(), aa_vec.z(), 1e-8);
}

}  // namespace
