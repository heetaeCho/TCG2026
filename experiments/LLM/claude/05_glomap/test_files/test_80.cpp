#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/processors/reconstruction_normalizer.h"
#include "glomap/types.h"

#include <unordered_map>
#include <cmath>
#include <limits>

namespace glomap {
namespace {

// Helper to create a registered image at a given position
Image CreateRegisteredImage(image_t id, const Eigen::Vector3d& center) {
    Image image;
    // To place the image center at 'center', we need to set the pose accordingly.
    // For identity rotation, cam_from_world translation = -center
    Eigen::Quaterniond q = Eigen::Quaterniond::Identity();
    Rigid3d cam_from_world(q, -center);
    image.cam_from_world = cam_from_world;
    image.is_registered = true;
    return image;
}

Image CreateUnregisteredImage() {
    Image image;
    image.is_registered = false;
    return image;
}

class NormalizeReconstructionTest_80 : public ::testing::Test {
protected:
    std::unordered_map<rig_t, Rig> rigs;
    std::unordered_map<camera_t, Camera> cameras;
    std::unordered_map<frame_t, Frame> frames;
    std::unordered_map<image_t, Image> images;
    std::unordered_map<track_t, Track> tracks;
};

// Test with a single registered image — should center on that image
TEST_F(NormalizeReconstructionTest_80, SingleImage_80) {
    images[0] = CreateRegisteredImage(0, Eigen::Vector3d(5.0, 10.0, 15.0));

    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, false, 10.0, 0.1, 0.9);

    // With a single image, P0=0, P1=0 (size-1=0), bbox extent = 0
    // scale stays 1 since old_extent < epsilon
    // mean_coord = (5, 10, 15), so translation = -1 * (5,10,15) = (-5,-10,-15)
    EXPECT_DOUBLE_EQ(tform.scale, 1.0);
    EXPECT_NEAR(tform.translation()(0), -5.0, 1e-9);
    EXPECT_NEAR(tform.translation()(1), -10.0, 1e-9);
    EXPECT_NEAR(tform.translation()(2), -15.0, 1e-9);
}

// Test with multiple images to verify centering and scaling
TEST_F(NormalizeReconstructionTest_80, MultipleImages_CenterAndScale_80) {
    // Place 5 images along different positions
    images[0] = CreateRegisteredImage(0, Eigen::Vector3d(0.0, 0.0, 0.0));
    images[1] = CreateRegisteredImage(1, Eigen::Vector3d(10.0, 10.0, 10.0));
    images[2] = CreateRegisteredImage(2, Eigen::Vector3d(5.0, 5.0, 5.0));
    images[3] = CreateRegisteredImage(3, Eigen::Vector3d(2.0, 2.0, 2.0));
    images[4] = CreateRegisteredImage(4, Eigen::Vector3d(8.0, 8.0, 8.0));

    double extent = 10.0;
    double p0 = 0.1;
    double p1 = 0.9;

    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, false, extent, p0, p1);

    // With 5 images (size=5):
    // P0 = floor(0.1 * 4) = 0
    // P1 = floor(0.9 * 4) = 3
    // sorted coords: 0, 2, 5, 8, 10
    // bbox_min = (0,0,0), bbox_max = (8,8,8)
    // old_extent = sqrt(8^2 + 8^2 + 8^2) = 8*sqrt(3) ≈ 13.856
    // scale = 10 / (8*sqrt(3))
    // mean of indices 0..3: (0+2+5+8)/4 = 3.75 for each coord

    double expected_old_extent = 8.0 * std::sqrt(3.0);
    double expected_scale = extent / expected_old_extent;
    double expected_mean = 3.75;

    EXPECT_NEAR(tform.scale, expected_scale, 1e-9);
    EXPECT_NEAR(tform.translation()(0), -expected_scale * expected_mean, 1e-6);
    EXPECT_NEAR(tform.translation()(1), -expected_scale * expected_mean, 1e-6);
    EXPECT_NEAR(tform.translation()(2), -expected_scale * expected_mean, 1e-6);
}

// Test fixed_scale: scale should remain 1
TEST_F(NormalizeReconstructionTest_80, FixedScale_80) {
    images[0] = CreateRegisteredImage(0, Eigen::Vector3d(0.0, 0.0, 0.0));
    images[1] = CreateRegisteredImage(1, Eigen::Vector3d(10.0, 10.0, 10.0));
    images[2] = CreateRegisteredImage(2, Eigen::Vector3d(5.0, 5.0, 5.0));
    images[3] = CreateRegisteredImage(3, Eigen::Vector3d(2.0, 2.0, 2.0));
    images[4] = CreateRegisteredImage(4, Eigen::Vector3d(8.0, 8.0, 8.0));

    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, true, 10.0, 0.1, 0.9);

    EXPECT_DOUBLE_EQ(tform.scale, 1.0);
}

// Test that unregistered images are ignored
TEST_F(NormalizeReconstructionTest_80, UnregisteredImagesIgnored_80) {
    images[0] = CreateRegisteredImage(0, Eigen::Vector3d(1.0, 1.0, 1.0));
    images[1] = CreateUnregisteredImage();
    images[2] = CreateRegisteredImage(2, Eigen::Vector3d(3.0, 3.0, 3.0));

    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, true, 10.0, 0.1, 0.9);

    // Only 2 registered images, size=2 <= 3, so P0=0, P1=1
    // mean = (1+3)/2 = 2 for each coord
    EXPECT_DOUBLE_EQ(tform.scale, 1.0);
    EXPECT_NEAR(tform.translation()(0), -2.0, 1e-9);
    EXPECT_NEAR(tform.translation()(1), -2.0, 1e-9);
    EXPECT_NEAR(tform.translation()(2), -2.0, 1e-9);
}

// Test that tracks are transformed
TEST_F(NormalizeReconstructionTest_80, TracksAreTransformed_80) {
    images[0] = CreateRegisteredImage(0, Eigen::Vector3d(0.0, 0.0, 0.0));
    images[1] = CreateRegisteredImage(1, Eigen::Vector3d(10.0, 0.0, 0.0));

    Track track;
    track.xyz = Eigen::Vector3d(5.0, 5.0, 5.0);
    tracks[0] = track;

    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, true, 10.0, 0.1, 0.9);

    // scale=1, mean=(5,0,0), translation = (-5,0,0)
    // transformed track = 1 * (5,5,5) + (-5,0,0) = (0,5,5)
    EXPECT_NEAR(tracks[0].xyz(0), 0.0, 1e-9);
    EXPECT_NEAR(tracks[0].xyz(1), 5.0, 1e-9);
    EXPECT_NEAR(tracks[0].xyz(2), 5.0, 1e-9);
}

// Test with exactly 3 images (boundary for the > 3 check)
TEST_F(NormalizeReconstructionTest_80, ThreeImages_BoundaryCondition_80) {
    images[0] = CreateRegisteredImage(0, Eigen::Vector3d(0.0, 0.0, 0.0));
    images[1] = CreateRegisteredImage(1, Eigen::Vector3d(5.0, 5.0, 5.0));
    images[2] = CreateRegisteredImage(2, Eigen::Vector3d(10.0, 10.0, 10.0));

    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, true, 10.0, 0.1, 0.9);

    // size=3, not > 3, so P0=0, P1=2
    // mean = (0+5+10)/3 = 5 for each coord
    EXPECT_DOUBLE_EQ(tform.scale, 1.0);
    EXPECT_NEAR(tform.translation()(0), -5.0, 1e-9);
    EXPECT_NEAR(tform.translation()(1), -5.0, 1e-9);
    EXPECT_NEAR(tform.translation()(2), -5.0, 1e-9);
}

// Test with exactly 4 images (first case where > 3 is true)
TEST_F(NormalizeReconstructionTest_80, FourImages_JustAboveBoundary_80) {
    images[0] = CreateRegisteredImage(0, Eigen::Vector3d(0.0, 0.0, 0.0));
    images[1] = CreateRegisteredImage(1, Eigen::Vector3d(3.0, 3.0, 3.0));
    images[2] = CreateRegisteredImage(2, Eigen::Vector3d(6.0, 6.0, 6.0));
    images[3] = CreateRegisteredImage(3, Eigen::Vector3d(9.0, 9.0, 9.0));

    double p0 = 0.1, p1 = 0.9;
    // size=4, > 3: P0 = floor(0.1 * 3) = 0, P1 = floor(0.9 * 3) = 2
    // sorted: 0, 3, 6, 9
    // bbox_min = (0,0,0), bbox_max = (6,6,6)
    // old_extent = 6*sqrt(3)
    // mean of indices 0..2: (0+3+6)/3 = 3

    double expected_old_extent = 6.0 * std::sqrt(3.0);
    double expected_scale = 10.0 / expected_old_extent;

    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, false, 10.0, p0, p1);

    EXPECT_NEAR(tform.scale, expected_scale, 1e-9);
    EXPECT_NEAR(tform.translation()(0), -expected_scale * 3.0, 1e-6);
    EXPECT_NEAR(tform.translation()(1), -expected_scale * 3.0, 1e-6);
    EXPECT_NEAR(tform.translation()(2), -expected_scale * 3.0, 1e-6);
}

// Test that rotation is identity in the returned transform
TEST_F(NormalizeReconstructionTest_80, ReturnedRotationIsIdentity_80) {
    images[0] = CreateRegisteredImage(0, Eigen::Vector3d(1.0, 2.0, 3.0));
    images[1] = CreateRegisteredImage(1, Eigen::Vector3d(4.0, 5.0, 6.0));

    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, false, 10.0, 0.1, 0.9);

    Eigen::Quaterniond q = tform.rotation;
    EXPECT_NEAR(q.w(), 1.0, 1e-9);
    EXPECT_NEAR(q.x(), 0.0, 1e-9);
    EXPECT_NEAR(q.y(), 0.0, 1e-9);
    EXPECT_NEAR(q.z(), 0.0, 1e-9);
}

// Test with all images at the same position (zero extent)
TEST_F(NormalizeReconstructionTest_80, AllImagesAtSamePosition_80) {
    for (int i = 0; i < 10; ++i) {
        images[i] = CreateRegisteredImage(i, Eigen::Vector3d(5.0, 5.0, 5.0));
    }

    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, false, 10.0, 0.1, 0.9);

    // old_extent = 0, which is < epsilon, so scale remains 1
    EXPECT_DOUBLE_EQ(tform.scale, 1.0);
    EXPECT_NEAR(tform.translation()(0), -5.0, 1e-9);
    EXPECT_NEAR(tform.translation()(1), -5.0, 1e-9);
    EXPECT_NEAR(tform.translation()(2), -5.0, 1e-9);
}

// Test with two registered images
TEST_F(NormalizeReconstructionTest_80, TwoRegisteredImages_80) {
    images[0] = CreateRegisteredImage(0, Eigen::Vector3d(0.0, 0.0, 0.0));
    images[1] = CreateRegisteredImage(1, Eigen::Vector3d(10.0, 0.0, 0.0));

    // size=2, <= 3, so P0=0, P1=1
    // bbox = (0,0,0) to (10,0,0), extent = 10
    // mean = (5, 0, 0)
    // scale = 10/10 = 1

    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, false, 10.0, 0.1, 0.9);

    EXPECT_NEAR(tform.scale, 1.0, 1e-9);
    EXPECT_NEAR(tform.translation()(0), -5.0, 1e-9);
    EXPECT_NEAR(tform.translation()(1), 0.0, 1e-9);
    EXPECT_NEAR(tform.translation()(2), 0.0, 1e-9);
}

// Test with custom extent value
TEST_F(NormalizeReconstructionTest_80, CustomExtent_80) {
    images[0] = CreateRegisteredImage(0, Eigen::Vector3d(0.0, 0.0, 0.0));
    images[1] = CreateRegisteredImage(1, Eigen::Vector3d(20.0, 0.0, 0.0));

    // size=2 <= 3: P0=0, P1=1
    // old_extent = 20, scale = 5/20 = 0.25
    double extent = 5.0;
    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, false, extent, 0.1, 0.9);

    EXPECT_NEAR(tform.scale, 0.25, 1e-9);
    EXPECT_NEAR(tform.translation()(0), -0.25 * 10.0, 1e-9);
}

// Test frames are transformed
TEST_F(NormalizeReconstructionTest_80, FramesAreTransformed_80) {
    images[0] = CreateRegisteredImage(0, Eigen::Vector3d(0.0, 0.0, 0.0));
    images[1] = CreateRegisteredImage(1, Eigen::Vector3d(10.0, 0.0, 0.0));

    Frame frame;
    frame.is_registered = true;
    Rigid3d rig_from_world(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1.0, 2.0, 3.0));
    frame.rig_from_world = rig_from_world;
    frames[0] = frame;

    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, true, 10.0, 0.1, 0.9);

    // The frame should have been transformed
    // We just verify it has a pose and the transformation was applied
    EXPECT_TRUE(frames[0].HasPose());
}

// Test with large number of images
TEST_F(NormalizeReconstructionTest_80, LargeNumberOfImages_80) {
    for (int i = 0; i < 100; ++i) {
        images[i] = CreateRegisteredImage(
            i, Eigen::Vector3d(i * 1.0, i * 2.0, i * 3.0));
    }

    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, false, 10.0, 0.1, 0.9);

    // Should complete without error and return a valid transform
    EXPECT_GT(tform.scale, 0.0);
}

// Test with negative coordinates
TEST_F(NormalizeReconstructionTest_80, NegativeCoordinates_80) {
    images[0] = CreateRegisteredImage(0, Eigen::Vector3d(-10.0, -10.0, -10.0));
    images[1] = CreateRegisteredImage(1, Eigen::Vector3d(10.0, 10.0, 10.0));

    // P0=0, P1=1 (size=2<=3)
    // sorted: -10, 10
    // bbox extent = sqrt(20^2*3) = 20*sqrt(3)
    // mean = (0, 0, 0)

    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, false, 10.0, 0.1, 0.9);

    double expected_extent = 20.0 * std::sqrt(3.0);
    double expected_scale = 10.0 / expected_extent;

    EXPECT_NEAR(tform.scale, expected_scale, 1e-9);
    EXPECT_NEAR(tform.translation()(0), 0.0, 1e-9);
    EXPECT_NEAR(tform.translation()(1), 0.0, 1e-9);
    EXPECT_NEAR(tform.translation()(2), 0.0, 1e-9);
}

// Test multiple tracks are all transformed
TEST_F(NormalizeReconstructionTest_80, MultipleTracksTransformed_80) {
    images[0] = CreateRegisteredImage(0, Eigen::Vector3d(0.0, 0.0, 0.0));
    images[1] = CreateRegisteredImage(1, Eigen::Vector3d(10.0, 0.0, 0.0));

    Track t1, t2;
    t1.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
    t2.xyz = Eigen::Vector3d(4.0, 5.0, 6.0);
    tracks[0] = t1;
    tracks[1] = t2;

    colmap::Sim3d tform = NormalizeReconstruction(
        rigs, cameras, frames, images, tracks, true, 10.0, 0.1, 0.9);

    // scale=1, mean=(5,0,0), translation=(-5,0,0)
    // t1 transformed: (1-5, 2, 3) = (-4, 2, 3)
    // t2 transformed: (4-5, 5, 6) = (-1, 5, 6)
    EXPECT_NEAR(tracks[0].xyz(0), -4.0, 1e-9);
    EXPECT_NEAR(tracks[0].xyz(1), 2.0, 1e-9);
    EXPECT_NEAR(tracks[0].xyz(2), 3.0, 1e-9);
    EXPECT_NEAR(tracks[1].xyz(0), -1.0, 1e-9);
    EXPECT_NEAR(tracks[1].xyz(1), 5.0, 1e-9);
    EXPECT_NEAR(tracks[1].xyz(2), 6.0, 1e-9);
}

}  // namespace
}  // namespace glomap
