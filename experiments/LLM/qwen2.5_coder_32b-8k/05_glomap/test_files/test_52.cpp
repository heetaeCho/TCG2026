#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "glomap/controllers/rotation_averager.h"



namespace glomap {

namespace {



class MockViewGraph : public ViewGraph {

public:

    MOCK_METHOD(void, KeepLargestConnectedComponents, (std::unordered_map<frame_t, Frame>& frames, std::unordered_map<image_t, Image>& images), (override));

};



class MockRotationEstimator : public RotationEstimator {

public:

    using RotationEstimator::RotationEstimator;

    MOCK_METHOD(bool, EstimateRotations, (const ViewGraph& view_graph, std::unordered_map<rig_t, Rig>& rigs, std::unordered_map<frame_t, Frame>& frames, std::unordered_map<image_t, Image>& images), (override));

};



class RotationAveragerTest_52 : public ::testing::Test {

protected:

    MockViewGraph mock_view_graph;

    RotationAveragerOptions options;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    void SetUp() override {

        // Setup default options

        options.use_gravity = false;

        options.use_stratified = false;

        options.skip_initialization = true;

    }

};



TEST_F(RotationAveragerTest_52, SolveRotationAveraging_NonGravitational_NoUnknownCameras_52) {

    EXPECT_CALL(mock_view_graph, KeepLargestConnectedComponents(::testing::Ref(frames), ::testing::Ref(images))).Times(3);



    MockRotationEstimator mock_rotation_estimator(options);

    EXPECT_CALL(mock_rotation_estimator, EstimateRotations(::testing::_, ::testing::Ref(rigs), ::testing::Ref(frames), ::testing::Ref(images)))

        .WillOnce(::testing::Return(true));



    RotationAveragerOptions local_options = options;

    bool result = SolveRotationAveraging(mock_view_graph, rigs, frames, images, local_options);

    EXPECT_TRUE(result);

}



TEST_F(RotationAveragerTest_52, SolveRotationAveraging_NonGravitational_WithUnknownCameras_52) {

    EXPECT_CALL(mock_view_graph, KeepLargestConnectedComponents(::testing::Ref(frames), ::testing::Ref(images))).Times(3);



    MockRotationEstimator mock_rotation_estimator(options);

    EXPECT_CALL(mock_rotation_estimator, EstimateRotations(::testing::_, ::testing::Ref(rigs), ::testing::Ref(frames), ::testing::Ref(images)))

        .WillOnce(::testing::Return(true))

        .WillRepeatedly(::testing::Return(false));



    Rig rig;

    rig.AddRefSensor(sensor_t(SensorType::CAMERA, 1));

    rigs[0] = rig;



    Frame frame;

    frame.SetFrameId(0);

    frame.SetRigId(0);

    frames[0] = frame;



    Image image;

    image.SetCameraId(1);

    images[0] = image;



    RotationAveragerOptions local_options = options;

    bool result = SolveRotationAveraging(mock_view_graph, rigs, frames, images, local_options);

    EXPECT_TRUE(result);

}



TEST_F(RotationAveragerTest_52, SolveRotationAveraging_Gravitational_NoUnknownCameras_AllPairsValid_52) {

    EXPECT_CALL(mock_view_graph, KeepLargestConnectedComponents(::testing::Ref(frames), ::testing::Ref(images))).Times(4);



    MockRotationEstimator mock_rotation_estimator(options);

    EXPECT_CALL(mock_rotation_estimator, EstimateRotations(::testing::_, ::testing::Ref(rigs), ::testing::Ref(frames), ::testing::Ref(images)))

        .WillOnce(::testing::Return(true))

        .WillRepeatedly(::testing::Return(false));



    options.use_gravity = true;

    options.use_stratified = true;



    Image image1, image2;

    image1.SetCameraId(1);

    image1.SetGravityDirection(Eigen::Vector3d(0, 0, -1));

    image2.SetCameraId(2);

    image2.SetGravityDirection(Eigen::Vector3d(0, 0, -1));



    images[0] = image1;

    images[1] = image2;



    ImagePair pair(0, 1, Eigen::Matrix3d::Identity());

    mock_view_graph.image_pairs.emplace(0, pair);



    RotationAveragerOptions local_options = options;

    bool result = SolveRotationAveraging(mock_view_graph, rigs, frames, images, local_options);

    EXPECT_TRUE(result);

}



TEST_F(RotationAveragerTest_52, SolveRotationAveraging_Gravitational_NoUnknownCameras_AllPairsInvalid_52) {

    EXPECT_CALL(mock_view_graph, KeepLargestConnectedComponents(::testing::Ref(frames), ::testing::Ref(images))).Times(1);



    options.use_gravity = true;

    options.use_stratified = true;



    Image image1, image2;

    image1.SetCameraId(1);

    image2.SetCameraId(2);



    images[0] = image1;

    images[1] = image2;



    ImagePair pair(0, 1, Eigen::Matrix3d::Identity());

    mock_view_graph.image_pairs.emplace(0, pair);



    RotationAveragerOptions local_options = options;

    bool result = SolveRotationAveraging(mock_view_graph, rigs, frames, images, local_options);

    EXPECT_TRUE(result);

}



TEST_F(RotationAveragerTest_52, SolveRotationAveraging_Gravitational_NoUnknownCameras_NotSolve1Dof_52) {

    EXPECT_CALL(mock_view_graph, KeepLargestConnectedComponents(::testing::Ref(frames), ::testing::Ref(images))).Times(3);



    options.use_gravity = true;

    options.use_stratified = false;



    Image image1, image2;

    image1.SetCameraId(1);

    image1.SetGravityDirection(Eigen::Vector3d(0, 0, -1));

    image2.SetCameraId(2);

    image2.SetGravityDirection(Eigen::Vector3d(0, 0, -1));



    images[0] = image1;

    images[1] = image2;



    ImagePair pair(0, 1, Eigen::Matrix3d::Identity());

    mock_view_graph.image_pairs.emplace(0, pair);



    RotationAveragerOptions local_options = options;

    bool result = SolveRotationAveraging(mock_view_graph, rigs, frames, images, local_options);

    EXPECT_TRUE(result);

}



TEST_F(RotationAveragerTest_52, SolveRotationAveraging_Gravitational_NoUnknownCameras_Solve1DofFailure_52) {

    EXPECT_CALL(mock_view_graph, KeepLargestConnectedComponents(::testing::Ref(frames), ::testing::Ref(images))).Times(3);



    MockRotationEstimator mock_rotation_estimator(options);

    EXPECT_CALL(mock_rotation_estimator, EstimateRotations(::testing::_, ::testing::Ref(rigs), ::testing::Ref(frames), ::testing::Ref(images)))

        .WillOnce(::testing::Return(false));



    options.use_gravity = true;

    options.use_stratified = true;



    Image image1, image2;

    image1.SetCameraId(1);

    image1.SetGravityDirection(Eigen::Vector3d(0, 0, -1));

    image2.SetCameraId(2);

    image2.SetGravityDirection(Eigen::Vector3d(0, 0, -1));



    images[0] = image1;

    images[1] = image2;



    ImagePair pair(0, 1, Eigen::Matrix3d::Identity());

    mock_view_graph.image_pairs.emplace(0, pair);



    RotationAveragerOptions local_options = options;

    bool result = SolveRotationAveraging(mock_view_graph, rigs, frames, images, local_options);

    EXPECT_FALSE(result);

}



TEST_F(RotationAveragerTest_52, SolveRotationAveraging_Gravitational_NoUnknownCameras_NotSkipInitialization_52) {

    EXPECT_CALL(mock_view_graph, KeepLargestConnectedComponents(::testing::Ref(frames), ::testing::Ref(images))).Times(4);



    MockRotationEstimator mock_rotation_estimator(options);

    EXPECT_CALL(mock_rotation_estimator, EstimateRotations(::testing::_, ::testing::Ref(rigs), ::testing::Ref(frames), ::testing::Ref(images)))

        .WillOnce(::testing::Return(true))

        .WillRepeatedly(::testing::Return(false));



    options.use_gravity = true;

    options.use_stratified = true;

    options.skip_initialization = false;



    Image image1, image2;

    image1.SetCameraId(1);

    image1.SetGravityDirection(Eigen::Vector3d(0, 0, -1));

    image2.SetCameraId(2);

    image2.SetGravityDirection(Eigen::Vector3d(0, 0, -1));



    images[0] = image1;

    images[1] = image2;



    ImagePair pair(0, 1, Eigen::Matrix3d::Identity());

    mock_view_graph.image_pairs.emplace(0, pair);



    RotationAveragerOptions local_options = options;

    bool result = SolveRotationAveraging(mock_view_graph, rigs, frames, images, local_options);

    EXPECT_TRUE(result);

}



TEST_F(RotationAveragerTest_52, SolveRotationAveraging_Gravitational_WithUnknownCameras_AllPairsValid_52) {

    EXPECT_CALL(mock_view_graph, KeepLargestConnectedComponents(::testing::Ref(frames), ::testing::Ref(images))).Times(6);



    MockRotationEstimator mock_rotation_estimator(options);

    EXPECT_CALL(mock_rotation_estimator, EstimateRotations(::testing::_, ::testing::Ref(rigs), ::testing::Ref(frames), ::testing::Ref(images)))

        .WillOnce(::testing::Return(true))

        .WillRepeatedly(::testing::Return(false));



    options.use_gravity = true;

    options.use_stratified = true;



    Image image1, image2, image3;

    image1.SetCameraId(1);

    image1.SetGravityDirection(Eigen::Vector3d(0, 0, -1));

    image2.SetCameraId(2);

    image2.SetGravityDirection(Eigen::Vector3d(0, 0, -1));

    image3.SetCameraId(3);



    images[0] = image1;

    images[1] = image2;

    images[2] = image3;



    ImagePair pair1(0, 1, Eigen::Matrix3d::Identity());

    mock_view_graph.image_pairs.emplace(0, pair1);

    ImagePair pair2(1, 2, Eigen::Matrix3d::Identity());

    mock_view_graph.image_pairs.emplace(1, pair2);



    Rig rig;

    rig.AddRefSensor(sensor_t(SensorType::CAMERA, 1));

    rigs[0] = rig;



    Frame frame;

    frame.SetFrameId(0);

    frame.SetRigId(0);

    frames[0] = frame;



    RotationAveragerOptions local_options = options;

    bool result = SolveRotationAveraging(mock_view_graph, rigs, frames, images, local_options);

    EXPECT_TRUE(result);

}



}  // namespace

}  // namespace glomap
