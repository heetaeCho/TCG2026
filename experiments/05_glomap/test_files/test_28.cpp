#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/estimators/global_rotation_averaging.h"

#include "./TestProjects/glomap/glomap/scene/view_graph.h"



using namespace glomap;

using ::testing::_;

using ::testing::NiceMock;



class RotationEstimatorTest : public ::testing::Test {

protected:

    RotationEstimatorOptions options;

    RotationEstimator estimator;

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    RotationEstimatorTest() : options(), estimator(options) {}



    void SetUp() override {

        // Initialize the view_graph, rigs, frames, and images as needed for tests

        // Example:

        // frame_t frame_id = 1;

        // image_t image_id = 1;

        // rig_t rig_id = 1;

        // camera_t camera_id = 1;



        // Frame frame(frame_id);

        // Image image(image_id, camera_id);



        // frames[frame_id] = frame;

        // images[image_id] = image;

    }

};



TEST_F(RotationEstimatorTest_28, SetupLinearSystem_EmptyInputs_NoCrash_28) {

    estimator.SetupLinearSystem(view_graph, rigs, frames, images);

}



TEST_F(RotationEstimatorTest_28, SetupLinearSystem_SingleFrameSingleImage_SuccessfulSetup_28) {

    frame_t frame_id = 1;

    image_t image_id = 1;

    rig_t rig_id = 1;

    camera_t camera_id = 1;



    Frame frame(frame_id);

    Image image(image_id, camera_id);



    frames[frame_id] = frame;

    images[image_id] = image;



    estimator.SetupLinearSystem(view_graph, rigs, frames, images);

}



TEST_F(RotationEstimatorTest_28, SetupLinearSystem_MultipleFramesMultipleImages_SuccessfulSetup_28) {

    for (int i = 1; i <= 3; ++i) {

        frame_t frame_id = i;

        image_t image_id = i * 10;

        rig_t rig_id = i % 2 == 0 ? 1 : 2;

        camera_t camera_id = i;



        Frame frame(frame_id);

        Image image(image_id, camera_id);



        frames[frame_id] = frame;

        images[image_id] = image;

    }



    estimator.SetupLinearSystem(view_graph, rigs, frames, images);

}



TEST_F(RotationEstimatorTest_28, SetupLinearSystem_UnregisteredFrame_Ignored_28) {

    frame_t frame_id1 = 1;

    frame_t frame_id2 = 2;

    image_t image_id1 = 10;

    rig_t rig_id = 1;

    camera_t camera_id = 1;



    Frame frame1(frame_id1);

    Frame frame2(frame_id2, false); // Unregistered frame

    Image image(image_id1, camera_id);



    frames[frame_id1] = frame1;

    frames[frame_id2] = frame2;

    images[image_id1] = image;



    estimator.SetupLinearSystem(view_graph, rigs, frames, images);

}



TEST_F(RotationEstimatorTest_28, SetupLinearSystem_UnregisteredImage_Ignored_28) {

    frame_t frame_id = 1;

    image_t image_id = 10;

    rig_t rig_id = 1;

    camera_t camera_id = 1;



    Frame frame(frame_id);

    Image image(image_id, camera_id, false); // Unregistered image



    frames[frame_id] = frame;

    images[image_id] = image;



    estimator.SetupLinearSystem(view_graph, rigs, frames, images);

}



TEST_F(RotationEstimatorTest_28, SetupLinearSystem_CameraWithoutRig_NoCrash_28) {

    frame_t frame_id = 1;

    image_t image_id = 10;

    camera_t camera_id = 1;



    Frame frame(frame_id);

    Image image(image_id, camera_id);



    frames[frame_id] = frame;

    images[image_id] = image;



    estimator.SetupLinearSystem(view_graph, rigs, frames, images);

}



TEST_F(RotationEstimatorTest_28, SetupLinearSystem_CameraWithRig_SuccessfulSetup_28) {

    frame_t frame_id = 1;

    image_t image_id = 10;

    rig_t rig_id = 1;

    camera_t camera_id = 1;



    Frame frame(frame_id);

    Image image(image_id, camera_id);



    frames[frame_id] = frame;

    images[image_id] = image;



    Rig rig(rig_id);

    rigs[rig_id] = rig;



    estimator.SetupLinearSystem(view_graph, rigs, frames, images);

}



TEST_F(RotationEstimatorTest_28, SetupLinearSystem_CameraWithRigAndInvalidRotation_Ignored_28) {

    frame_t frame_id = 1;

    image_t image_id = 10;

    rig_t rig_id = 1;

    camera_t camera_id = 1;



    Frame frame(frame_id);

    Image image(image_id, camera_id);



    frames[frame_id] = frame;

    images[image_id] = image;



    Rig rig(rig_id);

    Rigid3d cam_from_rig;

    cam_from_rig.translation = Eigen::Vector3d(NAN, NAN, NAN); // Invalid rotation

    rig.SetSensorFromRig(sensor_t(SensorType::CAMERA, camera_id), cam_from_rig);



    rigs[rig_id] = rig;



    estimator.SetupLinearSystem(view_graph, rigs, frames, images);

}



TEST_F(RotationEstimatorTest_28, SetupLinearSystem_ImagePairsWithGravity_SuccessfulSetup_28) {

    options.use_gravity = true;

    frame_t frame_id1 = 1;

    frame_t frame_id2 = 2;

    image_t image_id1 = 10;

    image_t image_id2 = 20;

    rig_t rig_id = 1;

    camera_t camera_id1 = 1;

    camera_t camera_id2 = 2;



    Frame frame1(frame_id1);

    Frame frame2(frame_id2);

    Image image1(image_id1, camera_id1);

    Image image2(image_id2, camera_id2);



    frames[frame_id1] = frame1;

    frames[frame_id2] = frame2;

    images[image_id1] = image1;

    images[image_id2] = image2;



    Rig rig(rig_id);

    rigs[rig_id] = rig;



    image_pair_t pair_id(1, 2);

    ImagePair image_pair(image_id1, image_id2);

    view_graph.image_pairs[pair_id] = image_pair;



    estimator.SetupLinearSystem(view_graph, rigs, frames, images);

}



TEST_F(RotationEstimatorTest_28, SetupLinearSystem_ImagePairsWithoutGravity_SuccessfulSetup_28) {

    options.use_gravity = false;

    frame_t frame_id1 = 1;

    frame_t frame_id2 = 2;

    image_t image_id1 = 10;

    image_t image_id2 = 20;

    rig_t rig_id = 1;

    camera_t camera_id1 = 1;

    camera_t camera_id2 = 2;



    Frame frame1(frame_id1);

    Frame frame2(frame_id2);

    Image image1(image_id1, camera_id1);

    Image image2(image_id2, camera_id2);



    frames[frame_id1] = frame1;

    frames[frame_id2] = frame2;

    images[image_id1] = image1;

    images[image_id2] = image2;



    Rig rig(rig_id);

    rigs[rig_id] = rig;



    image_pair_t pair_id(1, 2);

    ImagePair image_pair(image_id1, image_id2);

    view_graph.image_pairs[pair_id] = image_pair;



    estimator.SetupLinearSystem(view_graph, rigs, frames, images);

}
