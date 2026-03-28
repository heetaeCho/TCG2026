#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/controllers/track_establishment.h"

#include "TestProjects/glomap/glomap/scene/image.h"

#include "TestProjects/glomap/glomap/scene/track.h"



using namespace glomap;



class TrackEngineTest_114 : public ::testing::Test {

protected:

    ViewGraph view_graph_;

    std::unordered_map<image_t, Image> images_;

    TrackEstablishmentOptions options_;



    TrackEngine track_engine_{view_graph_, images_, options_};



    void SetUp() override {

        // Setup some default values for tests

        options_.min_num_tracks_per_view = 1;

        options_.max_num_view_per_track = 5;

        options_.max_num_tracks = 10;



        // Adding registered images to the map

        images_[1] = Image(1, 10, "image1.jpg");

        images_[2] = Image(2, 11, "image2.jpg");

        images_[3] = Image(3, 12, "image3.jpg");



        // Marking images as registered

        images_[1].camera_id = 1;

        images_[2].camera_id = 2;

        images_[3].camera_id = 3;



        for (auto& [id, img] : images_) {

            img.frame_ptr = new Frame();

            img.features = 5;

            img.features_undist = 5;

        }

    }



    void TearDown() override {

        // Clean up any allocated resources

        for (auto& [id, img] : images_) {

            delete img.frame_ptr;

        }

    }

};



TEST_F(TrackEngineTest_114, NormalOperation_114) {

    std::unordered_map<track_t, Track> tracks_full = {

        {1, {{1, 10}, {2, 11}}},

        {2, {{2, 11}, {3, 12}}}

    };

    std::unordered_map<track_t, Track> tracks_selected;



    size_t result = track_engine_.FindTracksForProblem(tracks_full, tracks_selected);



    EXPECT_EQ(result, 2);

    EXPECT_EQ(tracks_selected.size(), 2);

}



TEST_F(TrackEngineTest_114, BoundaryCondition_MinViewsPerTrack_114) {

    std::unordered_map<track_t, Track> tracks_full = {

        {1, {{1, 10}}}

    };

    std::unordered_map<track_t, Track> tracks_selected;



    size_t result = track_engine_.FindTracksForProblem(tracks_full, tracks_selected);



    EXPECT_EQ(result, 0);

    EXPECT_EQ(tracks_selected.size(), 0);

}



TEST_F(TrackEngineTest_114, BoundaryCondition_MaxViewsPerTrack_114) {

    options_.max_num_view_per_track = 2;

    std::unordered_map<track_t, Track> tracks_full = {

        {1, {{1, 10}, {2, 11}, {3, 12}}}

    };

    std::unordered_map<track_t, Track> tracks_selected;



    size_t result = track_engine_.FindTracksForProblem(tracks_full, tracks_selected);



    EXPECT_EQ(result, 0);

    EXPECT_EQ(tracks_selected.size(), 0);

}



TEST_F(TrackEngineTest_114, BoundaryCondition_MaxTracks_114) {

    options_.max_num_tracks = 1;

    std::unordered_map<track_t, Track> tracks_full = {

        {1, {{1, 10}, {2, 11}}},

        {2, {{2, 11}, {3, 12}}}

    };

    std::unordered_map<track_t, Track> tracks_selected;



    size_t result = track_engine_.FindTracksForProblem(tracks_full, tracks_selected);



    EXPECT_EQ(result, 1);

    EXPECT_EQ(tracks_selected.size(), 1);

}



TEST_F(TrackEngineTest_114, UnregisteredImage_114) {

    images_[3].camera_id = -1; // Marking image 3 as unregistered

    std::unordered_map<track_t, Track> tracks_full = {

        {1, {{1, 10}, {2, 11}}},

        {2, {{2, 11}, {3, 12}}}

    };

    std::unordered_map<track_t, Track> tracks_selected;



    size_t result = track_engine_.FindTracksForProblem(tracks_full, tracks_selected);



    EXPECT_EQ(result, 1);

    EXPECT_EQ(tracks_selected.size(), 1);

}



TEST_F(TrackEngineTest_114, NoTracksFull_114) {

    std::unordered_map<track_t, Track> tracks_full;

    std::unordered_map<track_t, Track> tracks_selected;



    size_t result = track_engine_.FindTracksForProblem(tracks_full, tracks_selected);



    EXPECT_EQ(result, 0);

    EXPECT_EQ(tracks_selected.size(), 0);

}
