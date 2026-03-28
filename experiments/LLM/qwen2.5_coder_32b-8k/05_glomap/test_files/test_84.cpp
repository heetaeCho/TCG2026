#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/processors/track_filter.h"

#include "Eigen/Dense"



using namespace glomap;



namespace {



struct ViewGraph {};

struct Camera {

    Eigen::Matrix4d cam_from_world;

    Eigen::Matrix3d img_from_cam;

    Eigen::Vector3d ImgFromCam(const Eigen::Vector3d& pt_calc) const {

        return img_from_cam * pt_calc.head<3>() / pt_calc(2);

    }

};

struct Image {

    camera_t camera_id;

    std::unordered_map<feature_t, Eigen::Vector3d> features_undist;

    std::unordered_map<feature_t, Eigen::Vector2d> features;

    Eigen::Matrix4d cam_from_world;



    Eigen::Vector3d CamFromWorld() const {

        return cam_from_world.inverse();

    }

};

struct Observation {

    image_t image_id;

    feature_t feature_id;

};

struct Track {

    Eigen::Vector3d xyz;

    std::unordered_map<image_t, feature_t> observations;

};



class TrackFilterTest_84 : public ::testing::Test {

protected:

    ViewGraph view_graph_;

    std::unordered_map<camera_t, Camera> cameras_;

    std::unordered_map<image_t, Image> images_;

    std::unordered_map<track_t, Track> tracks_;

    double max_reprojection_error_ = 0.1;

    bool in_normalized_image_ = true;



    void SetUp() override {

        // Set up a basic track with one observation

        Camera cam1;

        cam1.cam_from_world << 1, 0, 0, 0,

                               0, 1, 0, 0,

                               0, 0, 1, 0,

                               0, 0, 0, 1;

        cam1.img_from_cam << 1, 0, 0,

                             0, 1, 0,

                             0, 0, 1;



        Image img1;

        img1.camera_id = 1;

        img1.cam_from_world = cam1.cam_from_world.inverse();

        img1.features_undist[1] << 1, 1, 1;



        Track track1;

        track1.xyz << 1, 1, 2; // Point in front of the camera

        track1.observations[1] = 1;



        cameras_[1] = cam1;

        images_[1] = img1;

        tracks_[1] = track1;

    }

};



TEST_F(TrackFilterTest_84, PutIncreasesCount_84) {

    max_reprojection_error_ = 0.05; // Set a small threshold to filter out the track

    TrackFilter filter;

    int result = filter.FilterTracksByReprojection(view_graph_, cameras_, images_, tracks_, max_reprojection_error_, in_normalized_image_);

    EXPECT_EQ(result, 1); // The track should be filtered out

}



TEST_F(TrackFilterTest_84, NoChangeBelowThreshold_84) {

    TrackFilter filter;

    int result = filter.FilterTracksByReprojection(view_graph_, cameras_, images_, tracks_, max_reprojection_error_, in_normalized_image_);

    EXPECT_EQ(result, 0); // The track should not be filtered out

}



TEST_F(TrackFilterTest_84, BehindCameraFilteredOut_84) {

    // Move the point behind the camera

    tracks_[1].xyz << 1, 1, -2;

    max_reprojection_error_ = 0.1; // Any threshold should work here as the point is behind the camera



    TrackFilter filter;

    int result = filter.FilterTracksByReprojection(view_graph_, cameras_, images_, tracks_, max_reprojection_error_, in_normalized_image_);

    EXPECT_EQ(result, 1); // The track should be filtered out

}



TEST_F(TrackFilterTest_84, NoObservationsNoChange_84) {

    tracks_[1].observations.clear(); // Clear all observations



    TrackFilter filter;

    int result = filter.FilterTracksByReprojection(view_graph_, cameras_, images_, tracks_, max_reprojection_error_, in_normalized_image_);

    EXPECT_EQ(result, 0); // No change as there are no observations to filter

}



TEST_F(TrackFilterTest_84, MultipleObservationsOneFilteredOut_84) {

    // Add another observation that will be filtered out

    images_[2].camera_id = 1;

    images_[2].cam_from_world = cameras_[1].cam_from_world.inverse();

    images_[2].features_undist[1] << -1, -1, -1;



    tracks_[1].observations[2] = 1; // This observation is behind the camera



    TrackFilter filter;

    int result = filter.FilterTracksByReprojection(view_graph_, cameras_, images_, tracks_, max_reprojection_error_, in_normalized_image_);

    EXPECT_EQ(result, 1); // Only one observation should be filtered out

}



TEST_F(TrackFilterTest_84, NormalizedImageTrueReprojectionError_84) {

    TrackFilter filter;

    int result = filter.FilterTracksByReprojection(view_graph_, cameras_, images_, tracks_, max_reprojection_error_, true);

    EXPECT_EQ(result, 0); // The track should not be filtered out with the given reprojection error threshold

}



TEST_F(TrackFilterTest_84, NormalizedImageFalseReprojectionError_84) {

    in_normalized_image_ = false;



    Camera cam1;

    cam1.cam_from_world << 1, 0, 0, 0,

                           0, 1, 0, 0,

                           0, 0, 1, 0,

                           0, 0, 0, 1;

    cam1.img_from_cam << fx, 0, cx,

                         0, fy, cy,

                         0, 0, 1;



    Image img1;

    img1.camera_id = 1;

    img1.cam_from_world = cam1.cam_from_world.inverse();

    img1.features[1] << u, v; // Distorted feature coordinates



    cameras_[1] = cam1;

    images_[1] = img1;



    TrackFilter filter;

    int result = filter.FilterTracksByReprojection(view_graph_, cameras_, images_, tracks_, max_reprojection_error_, in_normalized_image_);

    EXPECT_EQ(result, 0); // The track should not be filtered out with the given reprojection error threshold

}



} // namespace
