#include <gtest/gtest.h>

#include <unordered_map>

// Assuming the production header is available at this path.
// Adjust the include path if the actual project uses a different one.
#include "glomap/estimators/view_graph_calibration.h"

namespace {

using glomap::ViewGraphCalibrator;
using glomap::Camera;
using glomap::camera_t;

class ViewGraphCalibratorTest_21 : public ::testing::Test {
protected:
    ViewGraphCalibrator calibrator_;
};

// Boundary case: Empty camera map should result in zero cameras being
// parameterized, and must not crash or access invalid memory.
TEST_F(ViewGraphCalibratorTest_21, EmptyCameraMapReturnsZero_21) {
    std::unordered_map<camera_t, Camera> cameras;

    const size_t result = calibrator_.ParameterizeCameras(cameras);

    EXPECT_EQ(result, static_cast<size_t>(0));
    EXPECT_TRUE(cameras.empty());
}

// Normal / special case: If all cameras have a prior focal length,
// the implementation increments and then decrements the counter for any
// camera that has a parameter block, so the net result must always be 0,
// regardless of the behavior of HasParameterBlock.
TEST_F(ViewGraphCalibratorTest_21, AllCamerasHavePriorFocalLengthReturnsZero_21) {
    std::unordered_map<camera_t, Camera> cameras;

    Camera cam_with_prior;
    cam_with_prior.has_prior_focal_length = true;

    cameras.emplace(static_cast<camera_t>(1), cam_with_prior);
    cameras.emplace(static_cast<camera_t>(2), cam_with_prior);
    cameras.emplace(static_cast<camera_t>(3), cam_with_prior);

    // Make a copy to check that the input map is not modified.
    const auto cameras_before = cameras;

    const size_t result = calibrator_.ParameterizeCameras(cameras);

    EXPECT_EQ(result, static_cast<size_t>(0)) << "No cameras without prior focal length should be optimized.";
    // ParameterizeCameras should not modify the camera map contents.
    EXPECT_EQ(cameras.size(), cameras_before.size());
    for (const auto& [id, cam] : cameras_before) {
        auto it = cameras.find(id);
        ASSERT_NE(it, cameras.end());
        EXPECT_EQ(it->second.has_prior_focal_length, cam.has_prior_focal_length);
    }
}

// Normal / mixed case: For a mixture of cameras with and without prior focal
// length, the number of cameras to be optimized must be no larger than the
// number of cameras without prior focal length, regardless of how
// HasParameterBlock behaves internally.
TEST_F(ViewGraphCalibratorTest_21, ResultNotGreaterThanNumNonPriorCameras_21) {
    std::unordered_map<camera_t, Camera> cameras;

    Camera cam_no_prior;
    cam_no_prior.has_prior_focal_length = false;

    Camera cam_with_prior;
    cam_with_prior.has_prior_focal_length = true;

    cameras.emplace(static_cast<camera_t>(10), cam_no_prior);
    cameras.emplace(static_cast<camera_t>(11), cam_no_prior);
    cameras.emplace(static_cast<camera_t>(12), cam_with_prior);
    cameras.emplace(static_cast<camera_t>(13), cam_with_prior);

    // Count how many cameras *do not* have a prior focal length.
    size_t non_prior_count = 0;
    for (const auto& [id, cam] : cameras) {
        if (!cam.has_prior_focal_length) {
            ++non_prior_count;
        }
    }

    const auto cameras_before = cameras;

    const size_t result = calibrator_.ParameterizeCameras(cameras);

    // The implementation can only optimize cameras that
    // (a) have a parameter block, and
    // (b) do not have a prior focal length.
    // So result is always bounded by the count of cameras without priors.
    EXPECT_LE(result, non_prior_count);

    // Verify that the input camera map itself is not structurally modified.
    EXPECT_EQ(cameras.size(), cameras_before.size());
    for (const auto& [id, cam] : cameras_before) {
        auto it = cameras.find(id);
        ASSERT_NE(it, cameras.end());
        EXPECT_EQ(it->second.has_prior_focal_length, cam.has_prior_focal_length);
    }
}

}  // namespace
