#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "global_positioning.h"



using namespace glomap;

using testing::_;

using testing::MockFunction;



class GlobalPositionerTest_110 : public ::testing::Test {

protected:

    GlobalPositionerOptions options;

    GlobalPositioner global_positioner;



    GlobalPositionerTest_110() : global_positioner(options) {}

};



TEST_F(GlobalPositionerTest_110, ParameterizeVariables_OptimizePositionsTrue_110) {

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<track_t, Track> tracks;



    options.optimize_positions = true;

    global_positioner.ParameterizeVariables(rigs, frames, tracks);



    // No specific observable behavior to check directly, but ensure no exceptions occur.

}



TEST_F(GlobalPositionerTest_110, ParameterizeVariables_OptimizePositionsFalse_110) {

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<track_t, Track> tracks;



    options.optimize_positions = false;

    global_positioner.ParameterizeVariables(rigs, frames, tracks);



    // No specific observable behavior to check directly, but ensure no exceptions occur.

}



TEST_F(GlobalPositionerTest_110, ParameterizeVariables_NoFramesWithPose_110) {

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<track_t, Track> tracks;



    Frame frame;

    frame.SetPose(Eigen::Vector3d(0, 0, 0), Eigen::Quaterniond::Identity());

    frame.SetHasPose(false);

    frames[1] = frame;



    global_positioner.ParameterizeVariables(rigs, frames, tracks);



    // No specific observable behavior to check directly, but ensure no exceptions occur.

}



TEST_F(GlobalPositionerTest_110, ParameterizeVariables_NoTracks_110) {

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;



    global_positioner.ParameterizeVariables(rigs, frames, {});



    // No specific observable behavior to check directly, but ensure no exceptions occur.

}



TEST_F(GlobalPositionerTest_110, ParameterizeVariables_NoScales_110) {

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<track_t, Track> tracks;



    global_positioner.ParameterizeVariables(rigs, frames, tracks);



    // No specific observable behavior to check directly, but ensure no exceptions occur.

}



TEST_F(GlobalPositionerTest_110, ParameterizeVariables_GpuEnabledButNotSupported_110) {

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<track_t, Track> tracks;



    options.use_gpu = true;

    global_positioner.ParameterizeVariables(rigs, frames, tracks);



    // No specific observable behavior to check directly, but ensure no exceptions occur.

}



TEST_F(GlobalPositionerTest_110, ParameterizeVariables_TooFewImagesForGpu_110) {

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<track_t, Track> tracks;



    options.use_gpu = true;

    options.min_num_images_gpu_solver = 100; // Set a high number to ensure not enough images

    global_positioner.ParameterizeVariables(rigs, frames, tracks);



    // No specific observable behavior to check directly, but ensure no exceptions occur.

}
