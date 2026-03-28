// File: two_view_geometry_test_140.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>

namespace glomap {
// Forward declaration of the function under test (from two_view_geometry.cc).
double HomographyError(const Eigen::Matrix3d& H,
                       const Eigen::Vector2d& x1,
                       const Eigen::Vector2d& x2);
}  // namespace glomap

// ---------------------------
// TEST_ID: 140
// ---------------------------

// Identity homography, same point -> error should be (numerically) ~ 0.
TEST(HomographyErrorTest_140, IdentitySamePoint_NearZeroError_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(1.0, 2.0);
  Eigen::Vector2d x2 = x1;

  const double error = glomap::HomographyError(H, x1, x2);

  // Expect extremely small numerical error.
  EXPECT_NEAR(error, 0.0, 1e-20);
}

// Identity homography, different points -> error should match squared distance
// between x1 and x2 (within numerical tolerance).
TEST(HomographyErrorTest_140, IdentityDifferentPoints_SquaredDistance_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(1.0, 2.0);
  Eigen::Vector2d x2(2.0, 4.0);

  const double error = glomap::HomographyError(H, x1, x2);

  // Squared Euclidean distance between x1 and x2.
  const double expected = (x1 - x2).squaredNorm();

  EXPECT_NEAR(error, expected, 1e-9);
}

// Scaling the homography matrix (by a non-zero scalar) should not
// significantly change the resulting reprojection error.
TEST(HomographyErrorTest_140, ScalingHomography_DoesNotChangeError_140) {
  // Simple translation homography.
  Eigen::Matrix3d H;
  H << 1.0, 0.0, 1.0,
       0.0, 1.0, 2.0,
       0.0, 0.0, 1.0;

  Eigen::Matrix3d H_scaled = 2.0 * H;

  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(1.0, 2.0);

  const double error_original = glomap::HomographyError(H, x1, x2);
  const double error_scaled   = glomap::HomographyError(H_scaled, x1, x2);

  // Both should be very small (near zero) and close to each other.
  EXPECT_NEAR(error_original, 0.0, 1e-18);
  EXPECT_NEAR(error_scaled,   0.0, 1e-18);
  EXPECT_NEAR(error_original, error_scaled, 1e-18);
}

// When the third component after applying H becomes zero, the implementation
// uses EPS in the denominator. We can at least verify that the result is finite
// and very large (since points are mapped far away).
TEST(HomographyErrorTest_140, ZeroWComponent_UsesEpsilonAvoidsInf_140) {
  // This homography zeroes out the third component.
  Eigen::Matrix3d H = Eigen::Matrix3d::Zero();
  H(0, 0) = 1.0;
  H(1, 1) = 1.0;
  // H(2,2) remains 0.0

  Eigen::Vector2d x1(1.0, 2.0);
  Eigen::Vector2d x2(0.0, 0.0);

  const double error = glomap::HomographyError(H, x1, x2);

  // Should be a huge but finite value (no division-by-zero infinities / NaNs).
  EXPECT_TRUE(std::isfinite(error));
  EXPECT_GT(error, 1e10);
}
