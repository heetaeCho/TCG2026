#include <gtest/gtest.h>
#include "glomap/scene/camera.h"

namespace glomap {

class CameraTest_7 : public ::testing::Test {};

// Verifies that Focal() is consistent with the focal lengths exposed
// through the public interface (observable behavior only).
TEST_F(CameraTest_7, FocalMatchesAverageOfFocalLengths_7) {
    Camera camera;

    const double focal_x = camera.FocalLengthX();
    const double focal_y = camera.FocalLengthY();

    const double expected_focal = (focal_x + focal_y) / 2.0;
    EXPECT_DOUBLE_EQ(expected_focal, camera.Focal());
}

// Verifies that Focal() is preserved when a Camera is copy-constructed
// from another Camera (via the underlying colmap::Camera state).
TEST_F(CameraTest_7, FocalConsistentAfterCopyConstruction_7) {
    Camera original;
    const double original_focal = original.Focal();

    Camera copy(original);

    EXPECT_DOUBLE_EQ(original_focal, copy.Focal());
}

// Verifies that Focal() is preserved when a Camera is assigned from
// another Camera instance (observable via Focal()).
TEST_F(CameraTest_7, FocalConsistentAfterAssignment_7) {
    Camera source;
    Camera target;

    const double source_focal = source.Focal();

    target = source;

    EXPECT_DOUBLE_EQ(source_focal, target.Focal());
}

// Verifies that Focal() can be called on a const Camera instance and
// returns a value consistent with the non-const view.
TEST_F(CameraTest_7, FocalCallableOnConstCamera_7) {
    Camera camera;
    const double focal_non_const = camera.Focal();

    const Camera& const_ref = camera;
    const double focal_const = const_ref.Focal();

    EXPECT_DOUBLE_EQ(focal_non_const, focal_const);
}

// Verifies the observable default value of has_refined_focal_length.
TEST_F(CameraTest_7, DefaultHasRefinedFocalLengthIsFalse_7) {
    Camera camera;
    EXPECT_FALSE(camera.has_refined_focal_length);
}

// Verifies that has_refined_focal_length can be toggled via its public API.
TEST_F(CameraTest_7, CanToggleHasRefinedFocalLength_7) {
    Camera camera;

    camera.has_refined_focal_length = true;
    EXPECT_TRUE(camera.has_refined_focal_length);

    camera.has_refined_focal_length = false;
    EXPECT_FALSE(camera.has_refined_focal_length);
}

}  // namespace glomap
