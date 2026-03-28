// File: two_view_geometry_test_135.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "glomap/math/rigid3d.h"
#include "glomap/math/two_view_geometry.h"

namespace {

using glomap::Rigid3d;

// Test fixture for CheckCheirality
class CheckCheiralityTest_135 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default pose: identity rotation, zero translation
    pose_.rotation = Eigen::Quaterniond::Identity();
    pose_.translation = Eigen::Vector3d::Zero();
  }

  Rigid3d pose_;
};

// Normal operation: both depths lie strictly between min_depth and max_depth.
TEST_F(CheckCheiralityTest_135, ReturnsTrueWhenDepthsWithinRange_135) {
  // Geometry chosen so that internal depth values are positive and moderate.
  pose_.rotation = Eigen::Quaterniond::Identity();
  pose_.translation = Eigen::Vector3d(1.0, 1.0, 1.0);

  const Eigen::Vector3d x1(0.0, 0.0, -1.0);
  const Eigen::Vector3d x2(0.0, 1.0, 0.0);
  const double min_depth = 0.1;
  const double max_depth = 10.0;

  const bool result =
      glomap::CheckCheirality(pose_, x1, x2, min_depth, max_depth);

  EXPECT_TRUE(result);
}

// Boundary condition: depths fall below the minimum allowed depth.
TEST_F(CheckCheiralityTest_135, ReturnsFalseWhenDepthsBelowMinDepth_135) {
  // Same geometry as the passing case but with a larger min_depth,
  // so the effective depths are no longer valid.
  pose_.rotation = Eigen::Quaterniond::Identity();
  pose_.translation = Eigen::Vector3d(1.0, 1.0, 1.0);

  const Eigen::Vector3d x1(0.0, 0.0, -1.0);
  const Eigen::Vector3d x2(0.0, 1.0, 0.0);
  const double min_depth = 1.1;   // Larger than the valid depth
  const double max_depth = 10.0;

  const bool result =
      glomap::CheckCheirality(pose_, x1, x2, min_depth, max_depth);

  EXPECT_FALSE(result);
}

// Boundary condition: depths exceed the maximum allowed depth.
TEST_F(CheckCheiralityTest_135, ReturnsFalseWhenDepthsAboveMaxDepth_135) {
  // Same geometry as the passing case but with a smaller max_depth,
  // so the effective depths become too large.
  pose_.rotation = Eigen::Quaterniond::Identity();
  pose_.translation = Eigen::Vector3d(1.0, 1.0, 1.0);

  const Eigen::Vector3d x1(0.0, 0.0, -1.0);
  const Eigen::Vector3d x2(0.0, 1.0, 0.0);
  const double min_depth = 0.1;
  const double max_depth = 0.5;   // Smaller than the valid depth

  const bool result =
      glomap::CheckCheirality(pose_, x1, x2, min_depth, max_depth);

  EXPECT_FALSE(result);
}

// Degenerate configuration: viewing directions lead to zero scaling range,
// making it impossible for depths to satisfy strict inequalities.
TEST_F(CheckCheiralityTest_135, ReturnsFalseForDegenerateViewingDirections_135) {
  pose_.rotation = Eigen::Quaterniond::Identity();
  pose_.translation = Eigen::Vector3d(0.0, 0.0, 1.0);

  // x1 and x2 aligned with translation direction to create a degenerate case.
  const Eigen::Vector3d x1(0.0, 0.0, 1.0);
  const Eigen::Vector3d x2(0.0, 0.0, 1.0);
  const double min_depth = 0.1;
  const double max_depth = 10.0;

  const bool result =
      glomap::CheckCheirality(pose_, x1, x2, min_depth, max_depth);

  EXPECT_FALSE(result);
}

// Error-like case: invalid depth range (min_depth > max_depth) should not pass.
TEST_F(CheckCheiralityTest_135, ReturnsFalseForInvalidDepthRange_135) {
  pose_.rotation = Eigen::Quaterniond::Identity();
  pose_.translation = Eigen::Vector3d(1.0, 1.0, 1.0);

  const Eigen::Vector3d x1(0.0, 0.0, -1.0);
  const Eigen::Vector3d x2(0.0, 1.0, 0.0);
  const double min_depth = 2.0;   // Intentionally greater than max_depth
  const double max_depth = 1.0;

  const bool result =
      glomap::CheckCheirality(pose_, x1, x2, min_depth, max_depth);

  EXPECT_FALSE(result);
}

}  // namespace
