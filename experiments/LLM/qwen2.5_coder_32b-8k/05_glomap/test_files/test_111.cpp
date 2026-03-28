#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "global_positioning.h"



namespace glomap {



class GlobalPositionerTest : public ::testing::Test {

protected:

    GlobalPositionerOptions options;

    GlobalPositioner globalPositioner;



    GlobalPositionerTest() : globalPositioner(options) {}



    std::unordered_map<rig_t, Rig> createRigs(size_t num_rigs) {

        std::unordered_map<rig_t, Rig> rigs;

        for (size_t i = 0; i < num_rigs; ++i) {

            Rig rig;

            rig.set_id(i);

            // Assuming Rig has a method to add sensors with default values

            rig.NonRefSensors()[0] = std::make_optional<ceres::Pose3d>();

            rigs[i] = rig;

        }

        return rigs;

    }



    std::unordered_map<frame_t, Frame> createFrames(size_t num_frames) {

        std::unordered_map<frame_t, Frame> frames;

        for (size_t i = 0; i < num_frames; ++i) {

            Frame frame;

            frame.set_id(i);

            // Assuming Frame has a method to set RigFromWorld with default values

            frame.RigFromWorld().rotation = Eigen::Matrix3d::Identity();

            frame.RigFromWorld().translation = Eigen::Vector3d::Zero();

            frames[i] = frame;

        }

        return frames;

    }

};



TEST_F(GlobalPositionerTest_111, ConvertResults_EmptyInput_111) {

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;



    globalPositioner.ConvertResults(rigs, frames);



    EXPECT_TRUE(rigs.empty());

    EXPECT_TRUE(frames.empty());

}



TEST_F(GlobalPositionerTest_111, ConvertResults_SingleFrame_NoNonRefSensor_111) {

    auto rigs = createRigs(1);

    auto frames = createFrames(1);



    globalPositioner.ConvertResults(rigs, frames);



    EXPECT_EQ(frames[0].RigFromWorld().translation, Eigen::Vector3d::Zero());

}



TEST_F(GlobalPositionerTest_111, ConvertResults_SingleFrame_HasNonRefSensor_NoParameterBlock_111) {

    auto rigs = createRigs(1);

    auto frames = createFrames(1);



    // Set non-ref sensor with default values

    rigs[0].NonRefSensors()[0]->translation = Eigen::Vector3d::Ones();

    rigs[0].NonRefSensors()[0]->rotation = Eigen::Matrix3d::Identity();



    globalPositioner.ConvertResults(rigs, frames);



    EXPECT_EQ(rigs[0].NonRefSensors()[0]->translation, Eigen::Vector3d::Ones());

}



TEST_F(GlobalPositionerTest_111, ConvertResults_MultipleFramesAndRigs_111) {

    auto rigs = createRigs(2);

    auto frames = createFrames(2);



    // Set non-ref sensor with default values

    rigs[0].NonRefSensors()[0]->translation = Eigen::Vector3d::Ones();

    rigs[0].NonRefSensors()[0]->rotation = Eigen::Matrix3d::Identity();

    rigs[1].NonRefSensors()[0]->translation = 2 * Eigen::Vector3d::Ones();

    rigs[1].NonRefSensors()[0]->rotation = Eigen::Matrix3d::Identity();



    // Set frame transformations

    frames[0].RigFromWorld().translation = Eigen::Vector3d(1, 2, 3);

    frames[0].set_rigid_id(0);

    frames[1].RigFromWorld().translation = 3 * Eigen::Vector3d(1, 2, 3);

    frames[1].set_rigid_id(1);



    globalPositioner.ConvertResults(rigs, frames);



    EXPECT_EQ(frames[0].RigFromWorld().translation, -Eigen::Vector3d(1, 2, 3));

    EXPECT_EQ(frames[1].RigFromWorld().translation, -3 * Eigen::Vector3d(1, 2, 3));



    // Assuming rig_scales_ is initialized to {0: 1.0, 1: 1.0}

    EXPECT_EQ(rigs[0].NonRefSensors()[0]->translation, Eigen::Vector3d::Ones());

    EXPECT_EQ(rigs[1].NonRefSensors()[0]->translation, 2 * Eigen::Vector3d::Ones());

}



} // namespace glomap
