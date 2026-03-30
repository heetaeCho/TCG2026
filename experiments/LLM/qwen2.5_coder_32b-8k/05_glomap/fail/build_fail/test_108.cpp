#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/estimators/global_positioning.h"

#include "glomap/scene/image.h"

#include "glomap/scene/track.h"

#include "ceres/ceres.h"



using namespace glomap;

using ::testing::_;

using ::testing::NiceMock;



class MockProblem : public ceres::Problem {

public:

    MOCK_METHOD6(AddResidualBlock, ceres::ResidualBlockId*(const ceres::CostFunction*, const ceres::LossFunction*,

                                                           double const* const, double const* const, double* const, double* const));

    MOCK_METHOD6(AddResidualBlock, ceres::ResidualBlockId*(const ceres::CostFunction*, const ceres::LossFunction*,

                                                           double const* const, double const* const, double const* const,

                                                           double const* const, double* const));

    MOCK_METHOD3(SetParameterLowerBound, void(double* parameter_block, int index, double lower_bound));

};



class GlobalPositionerTest : public ::testing::Test {

protected:

    NiceMock<MockProblem> mock_problem;

    GlobalPositionerOptions options;

    GlobalPositioner global_positioner{options};

    

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    void SetUp() override {

        options.generate_scales = false;

        global_positioner.problem_ = &mock_problem;

    }

};



TEST_F(GlobalPositionerTest_108, AddTrackToProblem_ValidObservation_108) {

    // Arrange

    track_t track_id = 1;

    Track track;

    track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);

    track.is_initialized = true;

    track.observations.emplace_back(image_t{1}, feature_t{0});



    Image image(1, 1, "test.jpg");

    image.features_undist.push_back(Eigen::Vector3d(4.0, 5.0, 6.0));

    image.frame_ptr = new Frame();

    image.frame_ptr->RigFromWorld().translation = Eigen::Vector3d(7.0, 8.0, 9.0);

    image.camera_id = 1;

    image.IsRegistered = [](){ return true; };



    images[1] = std::move(image);

    tracks[track_id] = std::move(track);



    // Expect

    EXPECT_CALL(mock_problem, AddResidualBlock(_, _, _, _, _)).Times(1);



    // Act

    global_positioner.AddTrackToProblem(track_id, rigs, cameras, frames, images, tracks);



    // Cleanup

    delete images[1].frame_ptr;

}



TEST_F(GlobalPositionerTest_108, AddTrackToProblem_ImageNotRegistered_108) {

    // Arrange

    track_t track_id = 1;

    Track track;

    track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);

    track.is_initialized = true;

    track.observations.emplace_back(image_t{1}, feature_t{0});



    Image image(1, 1, "test.jpg");

    image.features_undist.push_back(Eigen::Vector3d(4.0, 5.0, 6.0));

    image.frame_ptr = new Frame();

    image.frame_ptr->RigFromWorld().translation = Eigen::Vector3d(7.0, 8.0, 9.0);

    image.camera_id = 1;

    image.IsRegistered = [](){ return false; };



    images[1] = std::move(image);

    tracks[track_id] = std::move(track);



    // Expect

    EXPECT_CALL(mock_problem, AddResidualBlock(_, _, _, _, _)).Times(0);



    // Act

    global_positioner.AddTrackToProblem(track_id, rigs, cameras, frames, images, tracks);



    // Cleanup

    delete images[1].frame_ptr;

}



TEST_F(GlobalPositionerTest_108, AddTrackToProblem_UndistortedFeatureNaN_108) {

    // Arrange

    track_t track_id = 1;

    Track track;

    track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);

    track.is_initialized = true;

    track.observations.emplace_back(image_t{1}, feature_t{0});



    Image image(1, 1, "test.jpg");

    image.features_undist.push_back(Eigen::Vector3d(std::numeric_limits<double>::quiet_NaN(), 5.0, 6.0));

    image.frame_ptr = new Frame();

    image.frame_ptr->RigFromWorld().translation = Eigen::Vector3d(7.0, 8.0, 9.0);

    image.camera_id = 1;

    image.IsRegistered = [](){ return true; };



    images[1] = std::move(image);

    tracks[track_id] = std::move(track);



    // Expect

    EXPECT_CALL(mock_problem, AddResidualBlock(_, _, _, _, _)).Times(0);



    // Act

    global_positioner.AddTrackToProblem(track_id, rigs, cameras, frames, images, tracks);



    // Cleanup

    delete images[1].frame_ptr;

}



TEST_F(GlobalPositionerTest_108, AddTrackToProblem_HasTrivialFrame_108) {

    // Arrange

    track_t track_id = 1;

    Track track;

    track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);

    track.is_initialized = true;

    track.observations.emplace_back(image_t{1}, feature_t{0});



    Image image(1, 1, "test.jpg");

    image.features_undist.push_back(Eigen::Vector3d(4.0, 5.0, 6.0));

    image.frame_ptr = new Frame();

    image.frame_ptr->RigFromWorld().translation = Eigen::Vector3d(7.0, 8.0, 9.0);

    image.camera_id = 1;

    image.IsRegistered = [](){ return true; };

    image.HasTrivialFrame = [](){ return true; };



    images[1] = std::move(image);

    tracks[track_id] = std::move(track);



    // Expect

    EXPECT_CALL(mock_problem, AddResidualBlock(_, _, _, _, _)).Times(1);



    // Act

    global_positioner.AddTrackToProblem(track_id, rigs, cameras, frames, images, tracks);



    // Cleanup

    delete images[1].frame_ptr;

}



TEST_F(GlobalPositionerTest_108, AddTrackToProblem_NoTrivialFrame_RigTranslationValid_108) {

    // Arrange

    track_t track_id = 1;

    Track track;

    track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);

    track.is_initialized = true;

    track.observations.emplace_back(image_t{1}, feature_t{0});



    Image image(1, 1, "test.jpg");

    image.features_undist.push_back(Eigen::Vector3d(4.0, 5.0, 6.0));

    image.frame_ptr = new Frame();

    image.frame_ptr->RigFromWorld().translation = Eigen::Vector3d(7.0, 8.0, 9.0);

    image.camera_id = 1;

    image.IsRegistered = [](){ return true; };

    image.HasTrivialFrame = [](){ return false; };



    rig_t rig_id = 1;

    Rig rig;

    Sensor sensor(SensorType::CAMERA, 1);

    sensor.translation = Eigen::Vector3d(10.0, 11.0, 12.0);



    rig.Sensors().emplace(sensor_t(SensorType::CAMERA, 1), std::move(sensor));

    rigs[rig_id] = std::move(rig);

    images[1].frame_ptr->RigId = [](){ return rig_t{1}; };

    tracks[track_id] = std::move(track);



    // Expect

    EXPECT_CALL(mock_problem, AddResidualBlock(_, _, _, _, _, _)).Times(1);



    // Act

    global_positioner.AddTrackToProblem(track_id, rigs, cameras, frames, images, tracks);



    // Cleanup

    delete images[1].frame_ptr;

}



TEST_F(GlobalPositionerTest_108, AddTrackToProblem_NoTrivialFrame_RigTranslationNaN_108) {

    // Arrange

    track_t track_id = 1;

    Track track;

    track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);

    track.is_initialized = true;

    track.observations.emplace_back(image_t{1}, feature_t{0});



    Image image(1, 1, "test.jpg");

    image.features_undist.push_back(Eigen::Vector3d(4.0, 5.0, 6.0));

    image.frame_ptr = new Frame();

    image.frame_ptr->RigFromWorld().translation = Eigen::Vector3d(7.0, 8.0, 9.0);

    image.camera_id = 1;

    image.IsRegistered = [](){ return true; };

    image.HasTrivialFrame = [](){ return false; };



    rig_t rig_id = 1;

    Rig rig;

    Sensor sensor(SensorType::CAMERA, 1);

    sensor.translation = Eigen::Vector3d(std::numeric_limits<double>::quiet_NaN(), 11.0, 12.0);



    rig.Sensors().emplace(sensor_t(SensorType::CAMERA, 1), std::move(sensor));

    rigs[rig_id] = std::move(rig);

    images[1].frame_ptr->RigId = [](){ return rig_t{1}; };

    tracks[track_id] = std::move(track);



    // Expect

    EXPECT_CALL(mock_problem, AddResidualBlock(_, _, _, _, _, _, _)).Times(1);



    // Act

    global_positioner.AddTrackToProblem(track_id, rigs, cameras, frames, images, tracks);



    // Cleanup

    delete images[1].frame_ptr;

}



TEST_F(GlobalPositionerTest_108, AddTrackToProblem_NoTrivialFrame_RigTranslationNotInMap_108) {

    // Arrange

    track_t track_id = 1;

    Track track;

    track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);

    track.is_initialized = true;

    track.observations.emplace_back(image_t{1}, feature_t{0});



    Image image(1, 1, "test.jpg");

    image.features_undist.push_back(Eigen::Vector3d(4.0, 5.0, 6.0));

    image.frame_ptr = new Frame();

    image.frame_ptr->RigFromWorld().translation = Eigen::Vector3d(7.0, 8.0, 9.0);

    image.camera_id = 1;

    image.IsRegistered = [](){ return true; };

    image.HasTrivialFrame = [](){ return false; };



    images[1].frame_ptr->RigId = [](){ return rig_t{1}; };

    tracks[track_id] = std::move(track);



    // Expect

    EXPECT_CALL(mock_problem, AddResidualBlock(_, _, _, _, _, _, _)).Times(1);



    // Act

    global_positioner.AddTrackToProblem(track_id, rigs, cameras, frames, images, tracks);



    // Cleanup

    delete images[1].frame_ptr;

}
