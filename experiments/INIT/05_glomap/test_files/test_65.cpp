// File: two_view_geometry_test_65.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "glomap/math/two_view_geometry.h"

namespace glomap {

class TwoViewGeometryTest_65 : public ::testing::Test {};

// Degenerate case: zero translation (same camera center) should not pass cheirality.
TEST_F(TwoViewGeometryTest_65, DegenerateZeroTranslationReturnsFalse_65) {
  Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());

  // Two arbitrary viewing directions.
  const Eigen::Vector3d x1(1.0, 0.0, 0.0);
  const Eigen::Vector3d x2(0.0, 1.0, 0.0);

  const double min_depth = 0.1;
  const double max_depth = 10.0;

  EXPECT_FALSE(CheckCheirality(pose, x1, x2, min_depth, max_depth));
}

// Normal operation: a valid configuration within the depth range should return true.
TEST_F(TwoViewGeometryTest_65, ValidConfigurationReturnsTrue_65) {
  // Pre-computed configuration that satisfies the cheirality condition
  // for the given depth range.
  const Eigen::Vector3d x1(0.60000205, -0.16701530, 0.78237039);
  const Eigen::Vector3d x2(0.97717133, -0.15023209, -0.15022156);
  const Eigen::Vector3d t(1.57921282, 0.76743473, -0.46947439);

  Rigid3d pose(Eigen::Quaterniond::Identity(), t);

  const double min_depth = 0.1;
  const double max_depth = 10.0;

  EXPECT_TRUE(CheckCheirality(pose, x1, x2, min_depth, max_depth));
}

// Boundary / error case: same geometry as above but with a very small max depth
// so that the depth constraints are violated and cheirality should fail.
TEST_F(TwoViewGeometryTest_65, TooSmallMaxDepthReturnsFalse_65) {
  const Eigen::Vector3d x1(0.60000205, -0.16701530, 0.78237039);
  const Eigen::Vector3d x2(0.97717133, -0.15023209, -0.15022156);
  const Eigen::Vector3d t(1.57921282, 0.76743473, -0.46947439);

  Rigid3d pose(Eigen::Quaterniond::Identity(), t);

  const double min_depth = 0.1;
  const double max_depth = 0.2;  // Much tighter upper bound.

  EXPECT_FALSE(CheckCheirality(pose, x1, x2, min_depth, max_depth));
}

// Boundary case: rays are parallel (or nearly parallel) such that the geometry
// is degenerate; cheirality check should fail.
TEST_F(TwoViewGeometryTest_65, ParallelRaysDegenerateConfigurationReturnsFalse_65) {
  // x1 and x2 point in exactly the same direction.
  const Eigen::Vector3d x1(0.0, 0.0, 1.0);
  const Eigen::Vector3d x2(0.0, 0.0, 1.0);
  const Eigen::Vector3d t(0.0, 0.0, 1.0);

  Rigid3d pose(Eigen::Quaterniond::Identity(), t);

  const double min_depth = 0.1;
  const double max_depth = 10.0;

  EXPECT_FALSE(CheckCheirality(pose, x1, x2, min_depth, max_depth));
}

}  // namespace glomap
