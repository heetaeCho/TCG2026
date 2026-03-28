#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "colmap/base/database.h"

#include "glomap/controllers/global_mapper.h"



namespace glomap {



using ::testing::_;

using ::testing::Return;



class GlobalMapperTest_55 : public ::testing::Test {

protected:

    colmap::Database database;

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;

    GlobalMapper global_mapper;



    void SetOptionsToSkipAllSteps() {

        global_mapper.options_.skip_preprocessing = true;

        global_mapper.options_.skip_view_graph_calibration = true;

        global_mapper.options_.skip_relative_pose_estimation = true;

        global_mapper.options_.skip_rotation_averaging = true;

        global_mapper.options_.skip_track_establishment = true;

        global_mapper.options_.skip_global_positioning = true;

        global_mapper.options_.skip_bundle_adjustment = true;

        global_mapper.options_.skip_retriangulation = true;

        global_mapper.options_.skip_pruning = true;

    }

};



TEST_F(GlobalMapperTest_55, Solve_AllStepsSkipped_ReturnsTrue_55) {

    SetOptionsToSkipAllSteps();

    EXPECT_TRUE(global_mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalMapperTest_55, Solve_ViewGraphCalibrationFails_ReturnsFalse_55) {

    global_mapper.options_.skip_preprocessing = true;

    global_mapper.options_.skip_view_graph_calibration = false;

    global_mapper.options_.skip_relative_pose_estimation = true;

    global_mapper.options_.skip_rotation_averaging = true;

    global_mapper.options_.skip_track_establishment = true;

    global_mapper.options_.skip_global_positioning = true;

    global_mapper.options_.skip_bundle_adjustment = true;

    global_mapper.options_.skip_retriangulation = true;

    global_mapper.options_.skip_pruning = true;



    // Mock the behavior of ViewGraphCalibrator::Solve to return false

    EXPECT_CALL(*(new ::testing::NiceMock<colmap::ViewGraphCalibrator>(global_mapper.options_.opt_vgcalib)), Solve(_, _, _))

        .WillOnce(Return(false));



    EXPECT_FALSE(global_mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalMapperTest_55, Solve_RelativePoseEstimationFails_NoConnectedComponents_ReturnsFalse_55) {

    global_mapper.options_.skip_preprocessing = true;

    global_mapper.options_.skip_view_graph_calibration = true;

    global_mapper.options_.skip_relative_pose_estimation = false;

    global_mapper.options_.skip_rotation_averaging = true;

    global_mapper.options_.skip_track_establishment = true;

    global_mapper.options_.skip_global_positioning = true;

    global_mapper.options_.skip_bundle_adjustment = true;

    global_mapper.options_.skip_retriangulation = true;

    global_mapper.options_.skip_pruning = true;



    // Mock the behavior of view_graph.KeepLargestConnectedComponents to return 0

    EXPECT_CALL(view_graph, KeepLargestConnectedComponents(_, _))

        .WillOnce(Return(0));



    EXPECT_FALSE(global_mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalMapperTest_55, Solve_GlobalPositioningFails_OnlyPointsConstraint_ReturnsFalse_55) {

    global_mapper.options_.skip_preprocessing = true;

    global_mapper.options_.skip_view_graph_calibration = true;

    global_mapper.options_.skip_relative_pose_estimation = true;

    global_mapper.options_.skip_rotation_averaging = true;

    global_mapper.options_.skip_track_establishment = true;

    global_mapper.options_.skip_global_positioning = false;

    global_mapper.options_.skip_bundle_adjustment = true;

    global_mapper.options_.skip_retriangulation = true;

    global_mapper.options_.skip_pruning = true;



    // Set constraint type to something other than ONLY_POINTS

    global_mapper.options_.opt_gp.constraint_type = GlobalPositionerOptions::ConstraintType::PLANE;



    EXPECT_FALSE(global_mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalMapperTest_55, Solve_GlobalPositioningFails_GlobalPositionerSolve_ReturnsFalse_55) {

    global_mapper.options_.skip_preprocessing = true;

    global_mapper.options_.skip_view_graph_calibration = true;

    global_mapper.options_.skip_relative_pose_estimation = true;

    global_mapper.options_.skip_rotation_averaging = true;

    global_mapper.options_.skip_track_establishment = true;

    global_mapper.options_.skip_global_positioning = false;

    global_mapper.options_.skip_bundle_adjustment = true;

    global_mapper.options_.skip_retriangulation = true;

    global_mapper.options_.skip_pruning = true;



    // Set constraint type to ONLY_POINTS

    global_mapper.options_.opt_gp.constraint_type = GlobalPositionerOptions::ConstraintType::ONLY_POINTS;



    // Mock the behavior of gp_engine.Solve to return false

    EXPECT_CALL(*(new ::testing::NiceMock<GlobalPositioner>(global_mapper.options_.opt_gp)), Solve(_, _, _, _, _, _))

        .WillOnce(Return(false));



    EXPECT_FALSE(global_mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalMapperTest_55, Solve_BundleAdjustmentFails_ReturnsFalse_55) {

    global_mapper.options_.skip_preprocessing = true;

    global_mapper.options_.skip_view_graph_calibration = true;

    global_mapper.options_.skip_relative_pose_estimation = true;

    global_mapper.options_.skip_rotation_averaging = true;

    global_mapper.options_.skip_track_establishment = true;

    global_mapper.options_.skip_global_positioning = true;

    global_mapper.options_.skip_bundle_adjustment = false;

    global_mapper.options_.skip_retriangulation = true;

    global_mapper.options_.skip_pruning = true;



    // Mock the behavior of ba_engine.Solve to return false

    EXPECT_CALL(*(new ::testing::NiceMock<BundleAdjuster>(global_mapper.options_.opt_ba)), Solve(_, _, _, _, _))

        .WillOnce(Return(false));



    EXPECT_FALSE(global_mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalMapperTest_55, Solve_RetriangulationFails_ReturnsFalse_55) {

    global_mapper.options_.skip_preprocessing = true;

    global_mapper.options_.skip_view_graph_calibration = true;

    global_mapper.options_.skip_relative_pose_estimation = true;

    global_mapper.options_.skip_rotation_averaging = true;

    global_mapper.options_.skip_track_establishment = true;

    global_mapper.options_.skip_global_positioning = true;

    global_mapper.options_.skip_bundle_adjustment = false;

    global_mapper.options_.skip_retriangulation = false;

    global_mapper.options_.skip_pruning = true;



    // Mock the behavior of ba_engine.Solve to return false during retriangulation

    EXPECT_CALL(*(new ::testing::NiceMock<BundleAdjuster>(global_mapper.options_.opt_ba)), Solve(_, _, _, _, _))

        .WillOnce(Return(false));



    EXPECT_FALSE(global_mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks));

}



TEST_F(GlobalMapperTest_55, Solve_PruneWeaklyConnectedImages_Success_ReturnsTrue_55) {

    global_mapper.options_.skip_preprocessing = true;

    global_mapper.options_.skip_view_graph_calibration = true;

    global_mapper.options_.skip_relative_pose_estimation = true;

    global_mapper.options_.skip_rotation_averaging = true;

    global_mapper.options_.skip_track_establishment = true;

    global_mapper.options_.skip_global_positioning = true;

    global_mapper.options_.skip_bundle_adjustment = true;

    global_mapper.options_.skip_retriangulation = true;

    global_mapper.options_.skip_pruning = false;



    EXPECT_TRUE(global_mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks));

}



}  // namespace glomap
