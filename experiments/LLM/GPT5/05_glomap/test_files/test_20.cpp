#include <gtest/gtest.h>

#include <unordered_map>

// Include the actual header from the project.
#include "glomap/estimators/view_graph_calibration.h"

namespace glomap {

// Fixture for ViewGraphCalibrator tests (TEST_ID = 20).
class ViewGraphCalibratorTest_20 : public ::testing::Test {
 protected:
  ViewGraphCalibrator calibrator_;
  ViewGraph view_graph_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;
};

//------------------------------------------------------------------------------
// Behavior: When there are no cameras, Solve should take the "no cameras to
// optimize" path and return true without attempting to run an optimization.
// This is directly based on the provided implementation.
//------------------------------------------------------------------------------
TEST_F(ViewGraphCalibratorTest_20, SolveReturnsTrueWhenNoCameras_20) {
  ASSERT_TRUE(cameras_.empty());  // Precondition: no cameras.

  const bool result = calibrator_.Solve(view_graph_, cameras_, images_);

  // From the code path: if num_cameras == 0 -> returns true.
  EXPECT_TRUE(result);
  // Cameras container should remain empty.
  EXPECT_TRUE(cameras_.empty());
}

//------------------------------------------------------------------------------
// Behavior: Normal operation with a small number of cameras.
// We verify that Solve can be invoked without throwing and that it does not
// remove cameras from the container (observable effect).
// This exercises the "few cameras" branch (DENSE_NORMAL_CHOLESKY).
//------------------------------------------------------------------------------
TEST_F(ViewGraphCalibratorTest_20, SolvePreservesCameraMapForFewCameras_20) {
  // Arrange: add a small number of cameras (< 50).
  camera_t id1 = static_cast<camera_t>(1);
  camera_t id2 = static_cast<camera_t>(2);

  cameras_[id1] = Camera();
  cameras_[id2] = Camera();

  const auto original_size = cameras_.size();

  bool result = false;
  // Ensure that Solve does not throw in normal conditions.
  EXPECT_NO_THROW(result = calibrator_.Solve(view_graph_, cameras_, images_));
  (void)result;  // We don't assert on the exact boolean value here.

  // Observable behavior: the number of cameras and their keys are preserved.
  EXPECT_EQ(original_size, cameras_.size());
  EXPECT_EQ(1u, cameras_.count(id1));
  EXPECT_EQ(1u, cameras_.count(id2));
}

//------------------------------------------------------------------------------
// Behavior: Normal operation with many cameras.
// We verify that Solve can be invoked without throwing and that it does not
// remove cameras from the container. This exercises the "many cameras" branch
// (SPARSE_NORMAL_CHOLESKY) as per the implementation.
//------------------------------------------------------------------------------
TEST_F(ViewGraphCalibratorTest_20, SolvePreservesCameraMapForManyCameras_20) {
  // Arrange: 50+ cameras to go through the "SPARSE" solver branch.
  for (int i = 0; i < 60; ++i) {
    cameras_[static_cast<camera_t>(i)] = Camera();
  }
  const auto original_size = cameras_.size();

  bool result = false;
  EXPECT_NO_THROW(result = calibrator_.Solve(view_graph_, cameras_, images_));
  (void)result;

  // Observable behavior: container size is preserved.
  EXPECT_EQ(original_size, cameras_.size());
}

}  // namespace glomap
