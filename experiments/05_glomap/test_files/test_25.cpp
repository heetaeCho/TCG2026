#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "global_positioning.h"



using namespace glomap;

using testing::_;

using testing::NiceMock;



class GlobalPositionerTest_25 : public ::testing::Test {

protected:

    GlobalPositioner global_positioner_;

};



TEST_F(GlobalPositionerTest_25, SolveWithMultipleRigs_25) {

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs = {{1, Rig()}, {2, Rig()}};

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    EXPECT_FALSE(global_positioner_.Solve(view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalPositionerTest_25, SolveWithNoImages_25) {

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs = {{1, Rig()}};

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    EXPECT_FALSE(global_positioner_.Solve(view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalPositionerTest_25, SolveWithNoImagePairsAndTracksOnlyPoints_25) {

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs = {{1, Rig()}};

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images = {{1, Image()}};

    std::unordered_map<track_t, Track> tracks;



    global_positioner_.options_.constraint_type = GlobalPositionerOptions::ONLY_POINTS;

    EXPECT_TRUE(global_positioner_.Solve(view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalPositionerTest_25, SolveWithNoTracksAndCamerasOnlyPoints_25) {

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs = {{1, Rig()}};

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images = {{1, Image()}, {2, Image()}};

    view_graph.image_pairs.push_back({1, 2});

    std::unordered_map<track_t, Track> tracks;



    global_positioner_.options_.constraint_type = GlobalPositionerOptions::ONLY_CAMERAS;

    EXPECT_TRUE(global_positioner_.Solve(view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalPositionerTest_25, SolveWithNormalConditions_25) {

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs = {{1, Rig()}};

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images = {{1, Image()}, {2, Image()}};

    view_graph.image_pairs.push_back({1, 2});

    std::unordered_map<track_t, Track> tracks = {{1, Track()}};



    EXPECT_TRUE(global_positioner_.Solve(view_graph, rigs, cameras, frames, images, tracks));

}
