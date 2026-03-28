// File: two_view_geometry_test_137.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/SVD>
#include <limits>

#include "glomap/scene/camera.h"
// Adjust this include to the actual declaration header of FundamentalFromMotionAndCameras.
#include "glomap/math/two_view_geometry.h"
// Adjust if Rigid3d lives in a different header (e.g., pose.h, rigid3d.h, etc.).
#include "glomap/base/pose.h"

namespace {

// Fixture for FundamentalFromMotionAndCameras tests.
class FundamentalFromMotionAndCamerasTest_137 : public ::testing::Test {
 protected:
  glomap::Camera CreateDefaultCamera() const {
    // Rely on the public default constructor only (black-box).
    return glomap::Camera();
  }

  // Create a pose with non-zero translation to avoid degenerate essential matrix.
  glomap::Rigid3d CreateTranslatedPose() const {
    // This assumes Rigid3d has a constructor compatible with COLMAP-style pose:
    // Rigid3d(const Eigen::Quaterniond& q, const Eigen::Vector3d& t)
    return glomap::Rigid3d(Eigen::Quaterniond::Identity(),
                           Eigen::Vector3d(1.0, 0.0, 0.0));
  }
};

}  // namespace

// Normal operation: verifies that FundamentalFromMotionAndCameras writes a finite 3x3 matrix
// into the output parameter for valid camera and pose inputs.
TEST_F(FundamentalFromMotionAndCamerasTest_137,
       WritesFiniteFundamentalMatrix_137) {
  glomap::Camera camera1 = CreateDefaultCamera();
  glomap::Camera camera2 = CreateDefaultCamera();
  glomap::Rigid3d pose;  // default pose

  Eigen::Matrix3d F;
  // Initialize with NaNs to ensure that the function actually overwrites the content.
  F.setConstant(std::numeric_limits<double>::quiet_NaN());

  glomap::FundamentalFromMotionAndCameras(camera1, camera2, pose, &F);

  // As an observable black-box property, the resulting matrix should contain finite values.
  EXPECT_TRUE(F.allFinite());
}

// Determinism: calling the function twice with exactly the same inputs should produce
// numerically identical results.
TEST_F(FundamentalFromMotionAndCamerasTest_137,
       DeterministicForSameInputs_137) {
  glomap::Camera camera1 = CreateDefaultCamera();
  glomap::Camera camera2 = CreateDefaultCamera();
  glomap::Rigid3d pose;  // default pose

  Eigen::Matrix3d F1;
  Eigen::Matrix3d F2;

  glomap::FundamentalFromMotionAndCameras(camera1, camera2, pose, &F1);
  glomap::FundamentalFromMotionAndCameras(camera1, camera2, pose, &F2);

  // Expect the two outputs to be (approximately) identical.
  EXPECT_TRUE(F1.isApprox(F2, 1e-12));
}

// Sensitivity to pose: changing the relative pose (while keeping cameras identical)
// should produce a different fundamental matrix (for a non-degenerate pose).
TEST_F(FundamentalFromMotionAndCamerasTest_137,
       DifferentPosesProduceDifferentFundamentalMatrices_137) {
  glomap::Camera camera1 = CreateDefaultCamera();
  glomap::Camera camera2 = CreateDefaultCamera();

  glomap::Rigid3d pose_identity;          // default pose (assumed identity / zero translation)
  glomap::Rigid3d pose_translated = CreateTranslatedPose();  // non-zero translation

  Eigen::Matrix3d F_identity;
  Eigen::Matrix3d F_translated;

  glomap::FundamentalFromMotionAndCameras(camera1, camera2,
                                          pose_identity, &F_identity);
  glomap::FundamentalFromMotionAndCameras(camera1, camera2,
                                          pose_translated, &F_translated);

  // For a reasonable implementation, different poses should yield different fundamental matrices.
  // Use a small epsilon to guard against numerical noise.
  const double diff_norm = (F_identity - F_translated).norm();
  EXPECT_GT(diff_norm, 1e-8);
}

// Geometric property: for a non-degenerate relative pose, the resulting fundamental
// matrix should have rank 2 (the classic property of a fundamental matrix).
TEST_F(FundamentalFromMotionAndCamerasTest_137,
       FundamentalMatrixHasRankTwoForNonDegeneratePose_137) {
  glomap::Camera camera1 = CreateDefaultCamera();
  glomap::Camera camera2 = CreateDefaultCamera();
  glomap::Rigid3d pose = CreateTranslatedPose();  // non-degenerate motion

  Eigen::Matrix3d F;
  glomap::FundamentalFromMotionAndCameras(camera1, camera2, pose, &F);

  // Compute singular values and verify rank-2 behavior:
  // two large singular values and one significantly smaller.
  Eigen::JacobiSVD<Eigen::Matrix3d> svd(F);
  Eigen::Vector3d singular = svd.singularValues();

  // Sort singular values in descending order for robust comparison.
  std::array<double, 3> s = {singular(0), singular(1), singular(2)};
  std::sort(s.begin(), s.end(), std::greater<double>());

  // Guard against an all-zero matrix (degenerate case).
  ASSERT_GT(s[0], 0.0);

  // Smallest singular value should be much smaller than the largest.
  EXPECT_LT(s[2] / s[0], 1e-3);
}

// Error / boundary behavior: passing a null output pointer is an interface misuse.
// The current implementation dereferences the pointer without checks, so this is
// expected to crash; we verify this with a death test to document the precondition.
TEST_F(FundamentalFromMotionAndCamerasTest_137,
       NullOutputPointerCausesDeath_137) {
  glomap::Camera camera1 = CreateDefaultCamera();
  glomap::Camera camera2 = CreateDefaultCamera();
  glomap::Rigid3d pose;  // default pose

  EXPECT_DEATH(
      {
        glomap::FundamentalFromMotionAndCameras(camera1, camera2, pose,
                                                /*F=*/nullptr);
      },
      ".*");
}
