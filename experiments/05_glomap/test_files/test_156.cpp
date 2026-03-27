#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "track_filter.h"

#include "view_graph.h"

#include "image.h"

#include "track.h"



using namespace glomap;



TEST_F(TrackFilterTest_156, NoTracks_NoFiltered_156) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;

    double min_angle = 30.0;



    int filtered_count = TrackFilter::FilterTrackTriangulationAngle(view_graph, images, tracks, min_angle);



    EXPECT_EQ(filtered_count, 0);

}



TEST_F(TrackFilterTest_156, SingleTrack_NoFiltered_156) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images = {{1, Image(1, 1, "image1.jpg")}};

    std::unordered_map<track_t, Track> tracks = {{1, Track{1, Eigen::Vector3d(0, 0, 1), {std::make_pair(1, 1)}}}};

    double min_angle = 30.0;



    int filtered_count = TrackFilter::FilterTrackTriangulationAngle(view_graph, images, tracks, min_angle);



    EXPECT_EQ(filtered_count, 0);

}



TEST_F(TrackFilterTest_156, SingleTrackWithMultipleObservations_Filtered_156) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images = {{1, Image(1, 1, "image1.jpg")}, {2, Image(2, 1, "image2.jpg")}};

    std::unordered_map<track_t, Track> tracks = {

        {1, Track{1, Eigen::Vector3d(0, 0, 1), {std::make_pair(1, 1), std::make_pair(2, 2)}}}

    };

    double min_angle = 90.0;



    int filtered_count = TrackFilter::FilterTrackTriangulationAngle(view_graph, images, tracks, min_angle);



    EXPECT_EQ(filtered_count, 1);

}



TEST_F(TrackFilterTest_156, MultipleTracks_OneFiltered_156) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images = {{1, Image(1, 1, "image1.jpg")}, {2, Image(2, 1, "image2.jpg")}};

    std::unordered_map<track_t, Track> tracks = {

        {1, Track{1, Eigen::Vector3d(0, 0, 1), {std::make_pair(1, 1), std::make_pair(2, 2)}}},

        {2, Track{2, Eigen::Vector3d(0, 0, 1), {std::make_pair(1, 1)}}}

    };

    double min_angle = 90.0;



    int filtered_count = TrackFilter::FilterTrackTriangulationAngle(view_graph, images, tracks, min_angle);



    EXPECT_EQ(filtered_count, 1);

}



TEST_F(TrackFilterTest_156, TracksWithSmallAngles_AllFiltered_156) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images = {{1, Image(1, 1, "image1.jpg")}, {2, Image(2, 1, "image2.jpg")}};

    std::unordered_map<track_t, Track> tracks = {

        {1, Track{1, Eigen::Vector3d(0, 0, 1), {std::make_pair(1, 1), std::make_pair(2, 2)}}},

        {2, Track{2, Eigen::Vector3d(0, 0, 1), {std::make_pair(1, 1), std::make_pair(2, 2)}}}

    };

    double min_angle = 90.0;



    int filtered_count = TrackFilter::FilterTrackTriangulationAngle(view_graph, images, tracks, min_angle);



    EXPECT_EQ(filtered_count, 2);

}



TEST_F(TrackFilterTest_156, TracksWithLargeAngles_NoneFiltered_156) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images = {{1, Image(1, 1, "image1.jpg")}, {2, Image(2, 1, "image2.jpg")}};

    std::unordered_map<track_t, Track> tracks = {

        {1, Track{1, Eigen::Vector3d(0, 0, 1), {std::make_pair(1, 1)}}},

        {2, Track{2, Eigen::Vector3d(1, 0, 0), {std::make_pair(2, 2)}}}

    };

    double min_angle = 90.0;



    int filtered_count = TrackFilter::FilterTrackTriangulationAngle(view_graph, images, tracks, min_angle);



    EXPECT_EQ(filtered_count, 0);

}



TEST_F(TrackFilterTest_156, BoundaryCondition_ZeroMinAngle_AllFiltered_156) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images = {{1, Image(1, 1, "image1.jpg")}, {2, Image(2, 1, "image2.jpg")}};

    std::unordered_map<track_t, Track> tracks = {

        {1, Track{1, Eigen::Vector3d(0, 0, 1), {std::make_pair(1, 1), std::make_pair(2, 2)}}}

    };

    double min_angle = 0.0;



    int filtered_count = TrackFilter::FilterTrackTriangulationAngle(view_graph, images, tracks, min_angle);



    EXPECT_EQ(filtered_count, 1);

}



TEST_F(TrackFilterTest_156, BoundaryCondition_MaxMinAngle_NoneFiltered_156) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images = {{1, Image(1, 1, "image1.jpg")}, {2, Image(2, 1, "image2.jpg")}};

    std::unordered_map<track_t, Track> tracks = {

        {1, Track{1, Eigen::Vector3d(0, 0, 1), {std::make_pair(1, 1)}}},

        {2, Track{2, Eigen::Vector3d(1, 0, 0), {std::make_pair(2, 2)}}}

    };

    double min_angle = 180.0;



    int filtered_count = TrackFilter::FilterTrackTriangulationAngle(view_graph, images, tracks, min_angle);



    EXPECT_EQ(filtered_count, 0);

}



TEST_F(TrackFilterTest_156, BoundaryCondition_InvalidMinAngle_LargeValue_NoneFiltered_156) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images = {{1, Image(1, 1, "image1.jpg")}, {2, Image(2, 1, "image2.jpg")}};

    std::unordered_map<track_t, Track> tracks = {

        {1, Track{1, Eigen::Vector3d(0, 0, 1), {std::make_pair(1, 1)}}},

        {2, Track{2, Eigen::Vector3d(1, 0, 0), {std::make_pair(2, 2)}}}

    };

    double min_angle = 181.0;



    int filtered_count = TrackFilter::FilterTrackTriangulationAngle(view_graph, images, tracks, min_angle);



    EXPECT_EQ(filtered_count, 0);

}



TEST_F(TrackFilterTest_156, BoundaryCondition_InvalidMinAngle_NegativeValue_NoneFiltered_156) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images = {{1, Image(1, 1, "image1.jpg")}, {2, Image(2, 1, "image2.jpg")}};

    std::unordered_map<track_t, Track> tracks = {

        {1, Track{1, Eigen::Vector3d(0, 0, 1), {std::make_pair(1, 1)}}},

        {2, Track{2, Eigen::Vector3d(1, 0, 0), {std::make_pair(2, 2)}}}

    };

    double min_angle = -1.0;



    int filtered_count = TrackFilter::FilterTrackTriangulationAngle(view_graph, images, tracks, min_angle);



    EXPECT_EQ(filtered_count, 0);

}
