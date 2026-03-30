#include <gtest/gtest.h>

#include "track_filter.h"

#include "image.h"

#include "view_graph.h"



namespace glomap {



class TrackFilterTest_154 : public ::testing::Test {

protected:

    ViewGraph view_graph;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    void SetUp() override {

        // Setup basic valid data

        Image image1(1, 1, "image1.jpg");

        Image image2(2, 2, "image2.jpg");

        images[1] = image1;

        images[2] = image2;



        Track track1;

        track1.observations.emplace_back(Observation{1, 1});

        track1.observations.emplace_back(Observation{2, 2});

        tracks[1] = track1;



        Camera camera1;

        cameras[1] = camera1;

    }

};



TEST_F(TrackFilterTest_154, FilterTracksByReprojection_NoChange_NormalOperation_154) {

    double max_reprojection_error = 1.0;

    bool in_normalized_image = false;

    int result = TrackFilter::FilterTracksByReprojection(view_graph, cameras, images, tracks, max_reprojection_error, in_normalized_image);

    EXPECT_EQ(result, 0); // No tracks should be filtered

}



TEST_F(TrackFilterTest_154, FilterTracksByReprojection_AllFiltered_NormalOperation_154) {

    double max_reprojection_error = 0.0;

    bool in_normalized_image = false;

    int result = TrackFilter::FilterTracksByReprojection(view_graph, cameras, images, tracks, max_reprojection_error, in_normalized_image);

    EXPECT_EQ(result, 1); // All observations should be filtered out

}



TEST_F(TrackFilterTest_154, FilterTracksByReprojection_BoundaryCondition_MaxError_154) {

    double max_reprojection_error = EPS;

    bool in_normalized_image = false;

    int result = TrackFilter::FilterTracksByReprojection(view_graph, cameras, images, tracks, max_reprojection_error, in_normalized_image);

    EXPECT_EQ(result, 0); // No tracks should be filtered if reprojection error is exactly EPS

}



TEST_F(TrackFilterTest_154, FilterTracksByReprojection_NormalizedImage_154) {

    double max_reprojection_error = 1.0;

    bool in_normalized_image = true;

    int result = TrackFilter::FilterTracksByReprojection(view_graph, cameras, images, tracks, max_reprojection_error, in_normalized_image);

    EXPECT_EQ(result, 0); // No tracks should be filtered

}



TEST_F(TrackFilterTest_154, FilterTracksByReprojection_EmptyTracks_154) {

    double max_reprojection_error = 1.0;

    bool in_normalized_image = false;

    tracks.clear();

    int result = TrackFilter::FilterTracksByReprojection(view_graph, cameras, images, tracks, max_reprojection_error, in_normalized_image);

    EXPECT_EQ(result, 0); // No tracks to filter

}



TEST_F(TrackFilterTest_154, FilterTracksByReprojection_EmptyImages_154) {

    double max_reprojection_error = 1.0;

    bool in_normalized_image = false;

    images.clear();

    int result = TrackFilter::FilterTracksByReprojection(view_graph, cameras, images, tracks, max_reprojection_error, in_normalized_image);

    EXPECT_EQ(result, 1); // All observations should be filtered out due to missing images

}



TEST_F(TrackFilterTest_154, FilterTracksByReprojection_EmptyCameras_154) {

    double max_reprojection_error = 1.0;

    bool in_normalized_image = false;

    cameras.clear();

    int result = TrackFilter::FilterTracksByReprojection(view_graph, cameras, images, tracks, max_reprojection_error, in_normalized_image);

    EXPECT_EQ(result, 1); // All observations should be filtered out due to missing cameras

}



} // namespace glomap
