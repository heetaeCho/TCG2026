// File: camera_test_97.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>

#include "glomap/scene/camera.h"

// If glomap/scene/camera.h already includes the appropriate COLMAP header,
// you won't need to include it again here. If not, add the correct include, e.g.:
// #include <colmap/scene/camera.h>  // Adjust path as needed.

namespace {

class CameraTest_97 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

//------------------------------------------------------------------------------
// Normal behavior: operator=(const colmap::Camera&) should produce a state
// equivalent to constructing from the same colmap::Camera.
// This uses only the public interface of glomap::Camera (Focal, PrincipalPoint,
// GetK) and treats everything as a black box.
//------------------------------------------------------------------------------
TEST_F(CameraTest_97, AssignFromColmapMatchesCtor_97) {
  // Arrange
  colmap::Camera colmap_camera;

  glomap::Camera camera_from_ctor(colmap_camera);  // uses converting ctor
  glomap::Camera camera_assigned;                  // default-constructed

  // Act
  camera_assigned = colmap_camera;

  // Assert: Focal() should match between the two glomap::Camera instances.
  EXPECT_DOUBLE_EQ(camera_from_ctor.Focal(), camera_assigned.Focal());

  // PrincipalPoint() comparison via coordinates.
  Eigen::Vector2d pp_ctor = camera_from_ctor.PrincipalPoint();
  Eigen::Vector2d pp_assigned = camera_assigned.PrincipalPoint();
  EXPECT_DOUBLE_EQ(pp_ctor.x(), pp_assigned.x());
  EXPECT_DOUBLE_EQ(pp_ctor.y(), pp_assigned.y());

  // GetK() comparison via Eigen's isApprox.
  Eigen::Matrix3d K_ctor = camera_from_ctor.GetK();
  Eigen::Matrix3d K_assigned = camera_assigned.GetK();
  EXPECT_TRUE(K_ctor.isApprox(K_assigned));
}

//------------------------------------------------------------------------------
// Contract of assignment: operator= should return *this (self reference).
// This is observable purely via the return reference.
//------------------------------------------------------------------------------
TEST_F(CameraTest_97, AssignmentReturnsSelfReference_97) {
  // Arrange
  colmap::Camera colmap_camera;
  glomap::Camera camera;
  glomap::Camera* camera_ptr = &camera;

  // Act
  glomap::Camera& result_ref = (camera = colmap_camera);

  // Assert
  EXPECT_EQ(camera_ptr, &result_ref);
}

//------------------------------------------------------------------------------
// Boundary/robustness: multiple assignments from the same colmap::Camera should
// be stable (idempotent). We just verify no observable change in the public
// interface of glomap::Camera between assignments.
//------------------------------------------------------------------------------
TEST_F(CameraTest_97, MultipleAssignmentsAreStable_97) {
  // Arrange
  colmap::Camera colmap_camera;
  glomap::Camera camera;

  // First assignment
  camera = colmap_camera;
  const double focal_first = camera.Focal();
  const Eigen::Vector2d pp_first = camera.PrincipalPoint();
  const Eigen::Matrix3d K_first = camera.GetK();

  // Act: assign again from the same colmap::Camera
  camera = colmap_camera;

  // Assert: public observable state should remain the same.
  EXPECT_DOUBLE_EQ(focal_first, camera.Focal());

  Eigen::Vector2d pp_second = camera.PrincipalPoint();
  EXPECT_DOUBLE_EQ(pp_first.x(), pp_second.x());
  EXPECT_DOUBLE_EQ(pp_first.y(), pp_second.y());

  Eigen::Matrix3d K_second = camera.GetK();
  EXPECT_TRUE(K_first.isApprox(K_second));
}

//------------------------------------------------------------------------------
// Basic construction / boundary: verify that the public flag
// has_refined_focal_length is initialized as expected by the interface
// (it is public, so it is part of the observable state).
//------------------------------------------------------------------------------
TEST_F(CameraTest_97, DefaultConstructorInitializesHasRefinedFocalLength_97) {
  glomap::Camera camera;

  // According to the interface snippet, this is initialized to false.
  EXPECT_FALSE(camera.has_refined_focal_length);
}

}  // namespace
