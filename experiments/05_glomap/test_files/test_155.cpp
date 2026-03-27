#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/processors/track_filter.h"

#include "./TestProjects/glomap/glomap/scene/image.h"

#include "./TestProjects/glomap/glomap/scene/view_graph.h"

#include "./TestProjects/glomap/glomap/scene/track.h"

#include <unordered_map>



namespace glomap {



using ::testing::Return;

using ::testing::_;

using ::testing::ElementsAre;



class TrackFilterTest_155 : public ::testing::Test {

protected:

    ViewGraph view_graph;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    void SetUp() override {

        // Setup a basic structure for testing

        image_t img_id1 = 1, img_id2 = 2;

        camera_t cam_id1 = 10, cam_id2 = 20;

        feature_t feat_id1 = 100, feat_id2 = 200;



        // Adding images to the map

        images.emplace(img_id1, Image(img_id1, cam_id1, "image1.jpg"));

        images.emplace(img_id2, Image(img_id2, cam_id2, "image2.jpg"));



        // Adding a track with observations

        track_t track_id = 1;

        Track track;

        track.track_id = track_id;

        track.observations.emplace_back(Observation(img_id1, feat_id1));

        track.observations.emplace_back(Observation(img_id2, feat_id2));

        tracks.emplace(track_id, track);

    }

};



TEST_F(TrackFilterTest_155, FilterTracksByAngle_NoChange_155) {

    double max_angle_error = 30.0; // This should not filter out any tracks based on mock data

    int result = TrackFilter::FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error);

    EXPECT_EQ(result, 0); // No tracks should be filtered

}



TEST_F(TrackFilterTest_155, FilterTracksByAngle_AllFiltered_155) {

    double max_angle_error = 0.0; // This will filter out all tracks based on mock data

    int result = TrackFilter::FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error);

    EXPECT_EQ(result, 1); // All tracks should be filtered

}



TEST_F(TrackFilterTest_155, FilterTracksByAngle_BoundaryCondition_155) {

    double max_angle_error = 90.0; // Boundary condition where all points are considered valid

    int result = TrackFilter::FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error);

    EXPECT_EQ(result, 0); // No tracks should be filtered

}



TEST_F(TrackFilterTest_155, FilterTracksByAngle_UninitializedCamera_155) {

    double max_angle_error = 30.0; // This should not filter out any tracks based on mock data

    cameras[10].has_prior_focal_length = false;

    int result = TrackFilter::FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error);

    EXPECT_EQ(result, 0); // No tracks should be filtered due to uncalibrated camera logic

}



TEST_F(TrackFilterTest_155, FilterTracksByAngle_EmptyTracks_155) {

    double max_angle_error = 30.0;

    tracks.clear();

    int result = TrackFilter::FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error);

    EXPECT_EQ(result, 0); // No tracks to filter

}



TEST_F(TrackFilterTest_155, FilterTracksByAngle_EmptyImages_155) {

    double max_angle_error = 30.0;

    images.clear();

    int result = TrackFilter::FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error);

    EXPECT_EQ(result, 1); // All tracks should be filtered as no observations are valid

}



TEST_F(TrackFilterTest_155, FilterTracksByAngle_EmptyCameras_155) {

    double max_angle_error = 30.0;

    cameras.clear();

    int result = TrackFilter::FilterTracksByAngle(view_graph, cameras, images, tracks, max_angle_error);

    EXPECT_EQ(result, 1); // All tracks should be filtered as no observations are valid

}



} // namespace glomap
