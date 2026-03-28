#include <gtest/gtest.h>

#include "glomap/estimators/global_positioning.h"

#include "glomap/scene/view_graph.h"



namespace glomap {



class GlobalPositionerTest_103 : public ::testing::Test {

protected:

    GlobalPositionerOptions options_;

    GlobalPositioner global_positioner_;



    GlobalPositionerTest_103() : options_(), global_positioner_(options_) {}

};



TEST_F(GlobalPositionerTest_103, Solve_ReturnsFalseWhenImagesEmpty_103) {

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;  // Empty

    std::unordered_map<track_t, Track> tracks;



    EXPECT_FALSE(global_positioner_.Solve(view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalPositionerTest_103, Solve_ReturnsFalseWhenTracksEmptyAndConstraintTypeIsNotOnlyCameras_103) {

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images = {{1, Image()}};

    std::unordered_map<track_t, Track> tracks;  // Empty



    options_.constraint_type = ConstraintType::POINTS_AND_CAMERAS_BALANCED;



    EXPECT_FALSE(global_positioner_.Solve(view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalPositionerTest_103, Solve_ReturnsFalseWhenImagePairsEmptyAndConstraintTypeIsNotOnlyPoints_103) {

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images = {{1, Image()}};

    std::unordered_map<track_t, Track> tracks = {{1, Track()}};



    options_.constraint_type = ConstraintType::POINTS_AND_CAMERAS_BALANCED;



    EXPECT_FALSE(global_positioner_.Solve(view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalPositionerTest_103, Solve_ReturnsTrueForValidInput_103) {

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs = {{1, Rig()}};

    std::unordered_map<camera_t, Camera> cameras = {{1, Camera()}};

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}};

    std::unordered_map<image_t, Image> images = {{1, Image()}};

    std::unordered_map<track_t, Track> tracks = {{1, Track()}};



    options_.constraint_type = ConstraintType::ONLY_POINTS;



    EXPECT_TRUE(global_positioner_.Solve(view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalPositionerTest_103, Solve_LogsErrorWhenMultipleRigs_103) {

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs = {{1, Rig()}, {2, Rig()}};

    std::unordered_map<camera_t, Camera> cameras = {{1, Camera()}};

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}};

    std::unordered_map<image_t, Image> images = {{1, Image()}};

    std::unordered_map<track_t, Track> tracks = {{1, Track()}};



    EXPECT_FALSE(global_positioner_.Solve(view_graph, rigs, cameras, frames, images, tracks));

}



}  // namespace glomap
