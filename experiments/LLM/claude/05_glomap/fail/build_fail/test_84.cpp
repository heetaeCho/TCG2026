#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/processors/track_filter.h"
#include "glomap/types.h"

#include <unordered_map>
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace glomap {
namespace {

// Helper to create an identity pose image
Image CreateImageWithIdentityPose(image_t image_id, camera_t camera_id) {
    Image img;
    img.camera_id = camera_id;
    // Set identity pose (CamFromWorld = identity)
    img.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    return img;
}

class TrackFilterTest_84 : public ::testing::Test {
protected:
    void SetUp() override {
        // Default setup with a simple camera, image, and track
    }

    ViewGraph view_graph_;
    std::unordered_map<camera_t, Camera> cameras_;
    std::unordered_map<image_t, Image> images_;
    std::unordered_map<track_t, Track> tracks_;
    TrackFilter filter_;
};

// Test: Empty tracks map returns 0
TEST_F(TrackFilterTest_84, EmptyTracks_ReturnsZero_84) {
    int result = filter_.FilterTracksByReprojection(
        view_graph_, cameras_, images_, tracks_, 4.0, false);
    EXPECT_EQ(result, 0);
}

// Test: Track with no observations remains unchanged
TEST_F(TrackFilterTest_84, TrackWithNoObservations_ReturnsZero_84) {
    Track track;
    track.xyz = Eigen::Vector3d(0, 0, 5);
    tracks_[0] = track;

    int result = filter_.FilterTracksByReprojection(
        view_graph_, cameras_, images_, tracks_, 4.0, false);
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(tracks_[0].observations.empty());
}

// Test: Observation behind camera (z < EPS) is removed
TEST_F(TrackFilterTest_84, ObservationBehindCamera_IsRemoved_84) {
    // Create camera
    Camera cam;
    cam.camera_id = 0;
    cam.model_id = 0; // Simple pinhole
    cam.width = 640;
    cam.height = 480;
    cam.params = {500, 500, 320, 240}; // fx, fy, cx, cy
    cameras_[0] = cam;

    // Create image with identity pose
    Image img;
    img.camera_id = 0;
    img.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    img.features.push_back(Eigen::Vector2d(320, 240));
    images_[0] = img;

    // Create track behind the camera (negative z)
    Track track;
    track.xyz = Eigen::Vector3d(0, 0, -5);  // Behind camera
    track.observations.emplace_back(0, 0);
    tracks_[0] = track;

    int result = filter_.FilterTracksByReprojection(
        view_graph_, cameras_, images_, tracks_, 4.0, false);
    EXPECT_EQ(result, 1);
    EXPECT_TRUE(tracks_[0].observations.empty());
}

// Test: Observation with small reprojection error is kept (image space)
TEST_F(TrackFilterTest_84, SmallReprojectionError_ObservationKept_84) {
    Camera cam;
    cam.camera_id = 0;
    // Use a simple pinhole camera model
    cam.model_id = 0;
    cam.width = 640;
    cam.height = 480;
    cameras_[0] = cam;

    Image img;
    img.camera_id = 0;
    img.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());

    // 3D point at (0, 0, 5)
    // With identity pose, projected in camera coords is (0, 0, 5)
    // With pinhole, the image coords depend on camera params
    // We'll use normalized image mode to avoid camera model dependency
    Eigen::Vector3d feature_undist(0, 0, 1.0);  // normalized coords (0, 0)
    img.features_undist.push_back(feature_undist);
    images_[0] = img;

    Track track;
    track.xyz = Eigen::Vector3d(0, 0, 5);  // Projects to (0, 0) in normalized coords
    track.observations.emplace_back(0, 0);
    tracks_[0] = track;

    int result = filter_.FilterTracksByReprojection(
        view_graph_, cameras_, images_, tracks_, 4.0, true);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(tracks_[0].observations.size(), 1u);
}

// Test: Observation with large reprojection error is removed (normalized)
TEST_F(TrackFilterTest_84, LargeReprojectionError_ObservationRemoved_Normalized_84) {
    Camera cam;
    cam.camera_id = 0;
    cameras_[0] = cam;

    Image img;
    img.camera_id = 0;
    img.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());

    // Feature at normalized coords far from where the 3D point projects
    Eigen::Vector3d feature_undist(10.0, 10.0, 1.0);
    img.features_undist.push_back(feature_undist);
    images_[0] = img;

    Track track;
    track.xyz = Eigen::Vector3d(0, 0, 5);  // Projects to (0, 0) in normalized coords
    track.observations.emplace_back(0, 0);
    tracks_[0] = track;

    int result = filter_.FilterTracksByReprojection(
        view_graph_, cameras_, images_, tracks_, 0.01, true);
    EXPECT_EQ(result, 1);
    EXPECT_TRUE(tracks_[0].observations.empty());
}

// Test: Multiple observations, some kept some removed
TEST_F(TrackFilterTest_84, MixedObservations_PartiallyFiltered_84) {
    Camera cam;
    cam.camera_id = 0;
    cameras_[0] = cam;

    // Image 0: feature close to projection
    Image img0;
    img0.camera_id = 0;
    img0.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    Eigen::Vector3d feature0(0.0, 0.0, 1.0);  // Close to projection of (0,0,5)
    img0.features_undist.push_back(feature0);
    images_[0] = img0;

    // Image 1: feature far from projection
    Image img1;
    img1.camera_id = 0;
    img1.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    Eigen::Vector3d feature1(100.0, 100.0, 1.0);  // Far from projection
    img1.features_undist.push_back(feature1);
    images_[1] = img1;

    Track track;
    track.xyz = Eigen::Vector3d(0, 0, 5);
    track.observations.emplace_back(0, 0);
    track.observations.emplace_back(1, 0);
    tracks_[0] = track;

    int result = filter_.FilterTracksByReprojection(
        view_graph_, cameras_, images_, tracks_, 1.0, true);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(tracks_[0].observations.size(), 1u);
    EXPECT_EQ(tracks_[0].observations[0].first, 0);
}

// Test: Multiple tracks, only some are modified
TEST_F(TrackFilterTest_84, MultipleTracks_CountCorrect_84) {
    Camera cam;
    cam.camera_id = 0;
    cameras_[0] = cam;

    Image img;
    img.camera_id = 0;
    img.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    // Feature at origin in normalized coords
    img.features_undist.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
    images_[0] = img;

    // Track 0: good projection, should not be filtered
    Track track0;
    track0.xyz = Eigen::Vector3d(0, 0, 5);
    track0.observations.emplace_back(0, 0);
    tracks_[0] = track0;

    // Track 1: bad projection (point projects far from feature)
    Track track1;
    track1.xyz = Eigen::Vector3d(50, 50, 1);  // Projects to (50, 50) far from (0, 0)
    track1.observations.emplace_back(0, 0);
    tracks_[1] = track1;

    int result = filter_.FilterTracksByReprojection(
        view_graph_, cameras_, images_, tracks_, 1.0, true);
    // track1 should have its observation removed
    EXPECT_GE(result, 1);
}

// Test: All observations pass - counter should be 0
TEST_F(TrackFilterTest_84, AllObservationsPass_CounterZero_84) {
    Camera cam;
    cam.camera_id = 0;
    cameras_[0] = cam;

    Image img;
    img.camera_id = 0;
    img.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    img.features_undist.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
    images_[0] = img;

    Track track;
    track.xyz = Eigen::Vector3d(0, 0, 5);
    track.observations.emplace_back(0, 0);
    tracks_[0] = track;

    int result = filter_.FilterTracksByReprojection(
        view_graph_, cameras_, images_, tracks_, 100.0, true);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(tracks_[0].observations.size(), 1u);
}

// Test: Very strict threshold removes all observations
TEST_F(TrackFilterTest_84, VeryStrictThreshold_RemovesAll_84) {
    Camera cam;
    cam.camera_id = 0;
    cameras_[0] = cam;

    Image img;
    img.camera_id = 0;
    img.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    // Feature slightly offset from where (0.1, 0.1, 5) projects
    img.features_undist.push_back(Eigen::Vector3d(1.0, 1.0, 1.0));
    images_[0] = img;

    Track track;
    track.xyz = Eigen::Vector3d(0.1, 0.1, 5);
    track.observations.emplace_back(0, 0);
    tracks_[0] = track;

    // Use extremely strict threshold
    int result = filter_.FilterTracksByReprojection(
        view_graph_, cameras_, images_, tracks_, 1e-10, true);
    EXPECT_EQ(result, 1);
    EXPECT_TRUE(tracks_[0].observations.empty());
}

// Test: Point at z very close to 0 (near EPS) - should be filtered out
TEST_F(TrackFilterTest_84, PointAtNearZeroDepth_Filtered_84) {
    Camera cam;
    cam.camera_id = 0;
    cameras_[0] = cam;

    Image img;
    img.camera_id = 0;
    img.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    img.features_undist.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
    images_[0] = img;

    Track track;
    track.xyz = Eigen::Vector3d(0, 0, -1e-10);  // Very small negative z
    track.observations.emplace_back(0, 0);
    tracks_[0] = track;

    int result = filter_.FilterTracksByReprojection(
        view_graph_, cameras_, images_, tracks_, 100.0, true);
    EXPECT_EQ(result, 1);
    EXPECT_TRUE(tracks_[0].observations.empty());
}

// Test: Boundary - reprojection error exactly at threshold should NOT be kept (strict <)
TEST_F(TrackFilterTest_84, ReprojectionErrorAtThreshold_NotKept_84) {
    Camera cam;
    cam.camera_id = 0;
    cameras_[0] = cam;

    Image img;
    img.camera_id = 0;
    img.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    // Feature at (1, 0) in normalized coords
    img.features_undist.push_back(Eigen::Vector3d(1.0, 0.0, 1.0));
    images_[0] = img;

    // Track projects to (0, 0) in normalized coords
    // Error = distance from (0,0) to (1,0) = 1.0
    Track track;
    track.xyz = Eigen::Vector3d(0, 0, 1);
    track.observations.emplace_back(0, 0);
    tracks_[0] = track;

    // Threshold exactly 1.0 - since code uses strict <, this should be removed
    int result = filter_.FilterTracksByReprojection(
        view_graph_, cameras_, images_, tracks_, 1.0, true);
    EXPECT_EQ(result, 1);
    EXPECT_TRUE(tracks_[0].observations.empty());
}

// Test: Reprojection error just below threshold - should be kept
TEST_F(TrackFilterTest_84, ReprojectionErrorBelowThreshold_Kept_84) {
    Camera cam;
    cam.camera_id = 0;
    cameras_[0] = cam;

    Image img;
    img.camera_id = 0;
    img.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    // Feature at (0.5, 0) in normalized coords
    img.features_undist.push_back(Eigen::Vector3d(0.5, 0.0, 1.0));
    images_[0] = img;

    // Track projects to (0, 0) in normalized coords
    // Error = 0.5
    Track track;
    track.xyz = Eigen::Vector3d(0, 0, 1);
    track.observations.emplace_back(0, 0);
    tracks_[0] = track;

    // Threshold 1.0, error 0.5 < 1.0 -> kept
    int result = filter_.FilterTracksByReprojection(
        view_graph_, cameras_, images_, tracks_, 1.0, true);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(tracks_[0].observations.size(), 1u);
}

}  // namespace
}  // namespace glomap
