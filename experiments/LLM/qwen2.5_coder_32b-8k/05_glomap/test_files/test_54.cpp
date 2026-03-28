#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <unordered_map>

#include <vector>

#include <utility>



namespace glomap {



class Track {

public:

    std::unordered_map<image_t, feature_id_t> observations;

    track_t track_id;

};



class TrackEngine {

public:

    size_t FindTracksForProblem(const std::unordered_map<track_t, Track>& tracks_full,

                                std::unordered_map<track_t, Track>& tracks_selected);

private:

    struct Options {

        size_t min_num_view_per_track = 2;

        size_t max_num_view_per_track = 10;

        size_t min_num_tracks_per_view = 1;

        size_t max_num_tracks = 5;

    };

    std::unordered_map<image_t, Image> images_;

    Options options_;

};



} // namespace glomap



using namespace glomap;



class TrackEngineTest_54 : public ::testing::Test {

protected:

    TrackEngine track_engine;

    std::unordered_map<track_t, Track> tracks_full;

    std::unordered_map<track_t, Track> tracks_selected;

};



TEST_F(TrackEngineTest_54, NormalOperation_54) {

    // Arrange

    Track track1 = {{1, 101}, {2, 102}};

    Track track2 = {{1, 103}, {2, 104}, {3, 105}};

    tracks_full = {{1, track1}, {2, track2}};



    // Act

    size_t result = track_engine.FindTracksForProblem(tracks_full, tracks_selected);



    // Assert

    EXPECT_EQ(result, 2);

    EXPECT_EQ(tracks_selected.size(), 2);

}



TEST_F(TrackEngineTest_54, BoundaryConditionMinViewsPerTrack_54) {

    // Arrange

    Track track1 = {{1, 101}, {2, 102}};

    tracks_full = {{1, track1}};



    // Act

    size_t result = track_engine.FindTracksForProblem(tracks_full, tracks_selected);



    // Assert

    EXPECT_EQ(result, 1);

    EXPECT_EQ(tracks_selected.size(), 1);

}



TEST_F(TrackEngineTest_54, BoundaryConditionMaxViewsPerTrack_54) {

    // Arrange

    Track track1 = {{1, 101}, {2, 102}, {3, 103}, {4, 104}, {5, 105}, {6, 106}, {7, 107}, {8, 108}, {9, 109}, {10, 110}};

    tracks_full = {{1, track1}};



    // Act

    size_t result = track_engine.FindTracksForProblem(tracks_full, tracks_selected);



    // Assert

    EXPECT_EQ(result, 1);

    EXPECT_EQ(tracks_selected.size(), 1);

}



TEST_F(TrackEngineTest_54, TrackTooFewViews_54) {

    // Arrange

    Track track1 = {{1, 101}};

    tracks_full = {{1, track1}};



    // Act

    size_t result = track_engine.FindTracksForProblem(tracks_full, tracks_selected);



    // Assert

    EXPECT_EQ(result, 0);

    EXPECT_TRUE(tracks_selected.empty());

}



TEST_F(TrackEngineTest_54, TrackTooManyViews_54) {

    // Arrange

    Track track1 = {{1, 101}, {2, 102}, {3, 103}, {4, 104}, {5, 105}, {6, 106}, {7, 107}, {8, 108}, {9, 109}, {10, 110}, {11, 111}};

    tracks_full = {{1, track1}};



    // Act

    size_t result = track_engine.FindTracksForProblem(tracks_full, tracks_selected);



    // Assert

    EXPECT_EQ(result, 0);

    EXPECT_TRUE(tracks_selected.empty());

}



TEST_F(TrackEngineTest_54, MaxNumTracksReached_54) {

    // Arrange

    Track track1 = {{1, 101}, {2, 102}};

    Track track2 = {{1, 103}, {2, 104}, {3, 105}};

    Track track3 = {{1, 106}, {2, 107}, {3, 108}};

    Track track4 = {{1, 109}, {2, 110}, {3, 111}};

    Track track5 = {{1, 112}, {2, 113}, {3, 114}};

    Track track6 = {{1, 115}, {2, 116}, {3, 117}};



    tracks_full = {{1, track1}, {2, track2}, {3, track3}, {4, track4}, {5, track5}, {6, track6}};



    // Act

    size_t result = track_engine.FindTracksForProblem(tracks_full, tracks_selected);



    // Assert

    EXPECT_EQ(result, 5);

    EXPECT_EQ(tracks_selected.size(), 5);

}



TEST_F(TrackEngineTest_54, NoRegisteredImages_54) {

    // Arrange

    Track track1 = {{1, 101}, {2, 102}};

    tracks_full = {{1, track1}};



    // Act

    size_t result = track_engine.FindTracksForProblem(tracks_full, tracks_selected);



    // Assert

    EXPECT_EQ(result, 0);

    EXPECT_TRUE(tracks_selected.empty());

}



TEST_F(TrackEngineTest_54, MultipleTracksSameImages_54) {

    // Arrange

    Track track1 = {{1, 101}, {2, 102}};

    Track track2 = {{1, 103}, {2, 104}};



    tracks_full = {{1, track1}, {2, track2}};



    // Act

    size_t result = track_engine.FindTracksForProblem(tracks_full, tracks_selected);



    // Assert

    EXPECT_EQ(result, 2);

    EXPECT_EQ(tracks_selected.size(), 2);

}
