#include <gtest/gtest.h>
#include <Eigen/Core>

// Assuming the declaration is in this header (common pattern in the project).
// Adjust the include path if your actual header differs.
#include "glomap/math/two_view_geometry.h"

namespace {

using glomap::HomographyError;

// TEST_ID: 68

// For x1 = (0, 0) and H = I, the homogeneous point is (0, 0, 1),
// so the projected point becomes (0, 0) regardless of EPS.
// Thus, the error should be equal to the squared distance from the origin to x2.
TEST(HomographyErrorTest_68, IdentityWithOriginMatchesSquaredDistance_68) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(3.0, 4.0);  // distance from origin = 5, squared = 25

  const double error = HomographyError(H, x1, x2);

  EXPECT_DOUBLE_EQ(error, 25.0);
}

// If H is the zero matrix, then H * x1.homogeneous() = (0,0,0).
// After normalization, this also projects to (0,0), independent of EPS.
// So the error again equals the squared distance from origin to x2.
TEST(HomographyErrorTest_68, ZeroHomographyUsesOriginProjection_68) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Zero();
  Eigen::Vector2d x1(1.23, -4.56);  // arbitrary; gets mapped to zero
  Eigen::Vector2d x2(-2.0, 5.0);

  const double error = HomographyError(H, x1, x2);

  const double expected_squared_distance =
      (x2.x() * x2.x()) + (x2.y() * x2.y());  // (-2)^2 + 5^2 = 4 + 25 = 29

  EXPECT_DOUBLE_EQ(error, expected_squared_distance);
}

// With x1 = (0,0) and H = I, the projected point is again (0,0).
// Therefore, the error is simply ||x2||^2.
// A point farther from the origin should yield a strictly larger error.
TEST(HomographyErrorTest_68, LargerDisplacementYieldsLargerError_68) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(0.0, 0.0);

  Eigen::Vector2d x2_near(1.0, 0.0);  // squared distance = 1
  Eigen::Vector2d x2_far(2.0, 0.0);   // squared distance = 4

  const double error_near = HomographyError(H, x1, x2_near);
  const double error_far  = HomographyError(H, x1, x2_far);

  EXPECT_DOUBLE_EQ(error_near, 1.0);
  EXPECT_DOUBLE_EQ(error_far, 4.0);
  EXPECT_GT(error_far, error_near);
}

// General sanity check: error should always be non-negative for arbitrary inputs
// because it represents a squared Euclidean distance.
TEST(HomographyErrorTest_68, ErrorIsNonNegativeForArbitraryInputs_68) {
  Eigen::Matrix3d H;
  H << 1.0,  2.0, -1.0,
       0.5, -0.3,  2.0,
       0.1,  0.0,  1.5;

  Eigen::Vector2d x1(-1.0, 2.0);
  Eigen::Vector2d x2(0.3, -4.7);

  const double error = HomographyError(H, x1, x2);

  EXPECT_GE(error, 0.0);
}

}  // namespace
