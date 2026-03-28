#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "track_filter.h"

#include "view_graph.h"

#include "camera.h"

#include "image.h"

#include "track.h"

#include "observation.h"

#include <unordered_map>



using namespace glomap;

using ::testing::_;

using ::testing::ElementsAre;



// Mock classes for Camera and Image if needed

class MockCamera : public Camera {

public:

    MOCK_CONST_METHOD0(has_prior_focal_length, bool());

};



class MockImage : public Image {

public:

    MOCK_CONST_METHOD0(features_undist, const std::unordered_map<feature_t, Eigen::Vector3d>&());

    MOCK_CONST_METHOD0(CamFromWorld, Eigen::Matrix3x4d());

    camera_t camera_id;

};



// Test fixture for TrackFilter

class TrackFilterTest_85 : public ::testing::Test {

protected:

    ViewGraph view_graph;

    std::unordered_map<camera_t, MockCamera> cameras;

    std::unordered_map<image_t, MockImage> images;

    std::unordered_map<track_t, Track> tracks;



    void SetUp() override {

        // Initialize some mock objects for testing

        MockCamera camera1, camera2;

        EXPECT_CALL(camera1, has_prior_focal_length()).WillRepeatedly(::testing::Return(true));

        EXPECT_CALL(camera2, has_prior_focal_length()).WillRepeatedly(::testing::Return(false));



        cameras[0] = camera1;

        cameras[1] = camera2;



        MockImage image1, image2;

        image1.camera_id = 0;

        image2.camera_id = 1;



        std::unordered_map<feature_t, Eigen::Vector3d> features_undist_image1 = {{0, Eigen::Vector3d(1.0, 0.0, 0.0)}};

        std::unordered_map<feature_t, Eigen::Vector3d> features_undist_image2 = {{1, Eigen::Vector3d(0.0, 1.0, 0.0)}};



        EXPECT_CALL(image1, features_undist()).WillRepeatedly(::testing::ReturnRef(features_undist_image1));

        EXPECT_CALL(image2, features_undist()).WillRepeatedly(::testing::ReturnRef(features_undist_image2));



        Eigen::Matrix3x4d cam_from_world1 = Eigen::Matrix3x4d::Identity();

        Eigen::Matrix3x4d cam_from_world2 = Eigen::Matrix3x4d::Identity();



        EXPECT_CALL(image1, CamFromWorld()).WillRepeatedly(::testing::ReturnRef(cam_from_world1));

        EXPECT_CALL(image2, CamFromWorld()).WillRepeatedly(::testing::ReturnRef(cam_from_world2));



        images[0] = image1;

        images[1] = image2;



        // Initialize a track with observations

        Track track1;

        track1.observations = {{0, 0}, {1, 1}};

        track1.xyz = Eigen::Vector3d(1.0, 1.0, 1.0);

        tracks[0] = track1;

    }

};



TEST_F(TrackFilterTest_85, PutIncreasesCount_85) {

    TrackFilter filter;

    double max_angle_error = 45.0; // Should be less than 60 degrees (cos(60) = 0.5)

    int result = filter.FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error);

    EXPECT_EQ(result, 1); // Track should be filtered

}



TEST_F(TrackFilterTest_85, NoChangeIfNoObservations_85) {

    TrackFilter filter;

    double max_angle_error = 45.0; 

    tracks[0].observations.clear(); // Remove all observations

    int result = filter.FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error);

    EXPECT_EQ(result, 0); // No track should be filtered

}



TEST_F(TrackFilterTest_85, NoChangeIfAllObservationsWithinThreshold_85) {

    TrackFilter filter;

    double max_angle_error = 60.0; // Should be more than 45 degrees (cos(45) = 0.707)

    int result = filter.FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error);

    EXPECT_EQ(result, 0); // No track should be filtered

}



TEST_F(TrackFilterTest_85, BoundaryConditionMaxAngleError_85) {

    TrackFilter filter;

    double max_angle_error = acos(Eigen::Vector3d(1.0, 0.0, 0.0).dot(Eigen::Vector3d(1.0, 1.0, 1.0).normalized())) * RadToDeg();

    int result = filter.FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error);

    EXPECT_EQ(result, 1); // Track should be filtered

}



TEST_F(TrackFilterTest_85, MultipleTracks_85) {

    TrackFilter filter;

    double max_angle_error = 45.0; 

    Track track2;

    track2.observations = {{0, 0}, {1, 1}};

    track2.xyz = Eigen::Vector3d(1.0, -1.0, 1.0);

    tracks[1] = track2;



    int result = filter.FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error);

    EXPECT_EQ(result, 2); // Both tracks should be filtered

}



TEST_F(TrackFilterTest_85, NoCameraForObservation_85) {

    TrackFilter filter;

    double max_angle_error = 45.0; 

    Track track1;

    track1.observations = {{99, 0}, {1, 1}}; // Non-existent camera_id

    track1.xyz = Eigen::Vector3d(1.0, 1.0, 1.0);

    tracks[0] = track1;



    EXPECT_THROW(filter.FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error), std::out_of_range);

}



TEST_F(TrackFilterTest_85, NoImageForObservation_85) {

    TrackFilter filter;

    double max_angle_error = 45.0; 

    Track track1;

    track1.observations = {{0, 99}, {1, 1}}; // Non-existent image_id

    track1.xyz = Eigen::Vector3d(1.0, 1.0, 1.0);

    tracks[0] = track1;



    EXPECT_THROW(filter.FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error), std::out_of_range);

}



TEST_F(TrackFilterTest_85, NoFeatureForObservation_85) {

    TrackFilter filter;

    double max_angle_error = 45.0; 

    MockImage image1;

    EXPECT_CALL(image1, features_undist()).WillRepeatedly(::testing::Return(std::unordered_map<feature_t, Eigen::Vector3d>{}));

    images[0] = image1;



    int result = filter.FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error);

    EXPECT_EQ(result, 1); // Track should be filtered due to missing feature

}
