#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/estimators/rotation_initializer.cc"

#include "glomap/scene/image.h"



using namespace glomap;

using ::testing::UnorderedElementsAre;



class RotationInitializerTest_100 : public ::testing::Test {

protected:

    std::unordered_map<image_t, Rigid3d> cam_from_worlds;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;



    void SetUp() override {

        // Setup some default values for the test cases

        Rigid3d rig_pose1(Eigen::Quaterniond(1, 0, 0, 0), Eigen::Vector3d::Zero());

        Rigid3d rig_pose2(Eigen::Quaterniond(1, 0, 0, 0), Eigen::Vector3d::Zero());



        Rig rig1;

        rig1.SetSensorFromRig(sensor_t(SensorType::CAMERA, 10), rig_pose1);

        rigs[1] = rig1;



        Rig rig2;

        rig2.SetSensorFromRig(sensor_t(SensorType::CAMERA, 20), rig_pose2);

        rigs[2] = rig2;



        Frame frame1;

        frame1.AddImageData(image_t(100));

        frames[1] = frame1;



        Frame frame2;

        frame2.AddImageData(image_t(200));

        frames[2] = frame2;



        cam_from_worlds[image_t(100)] = Rigid3d(Eigen::Quaterniond(1, 0, 0, 0), Eigen::Vector3d(1, 0, 0));

        cam_from_worlds[image_t(200)] = Rigid3d(Eigen::Quaterniond(1, 0, 0, 0), Eigen::Vector3d(2, 0, 0));



        images[image_t(100)] = Image(image_t(100), camera_t(10), "image1.jpg");

        images[image_t(200)] = Image(image_t(200), camera_t(20), "image2.jpg");



        images[image_t(100)].SetRegistered(true);

        images[image_t(200)].SetRegistered(true);



        images[image_t(100)].frame_ptr = &frames[1];

        images[image_t(200)].frame_ptr = &frames[2];

    }

};



TEST_F(RotationInitializerTest_100, NormalOperation_100) {

    EXPECT_TRUE(ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames));

}



TEST_F(RotationInitializerTest_100, NoImagesRegistered_100) {

    images[image_t(100)].SetRegistered(false);

    images[image_t(200)].SetRegistered(false);



    EXPECT_TRUE(ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames));

}



TEST_F(RotationInitializerTest_100, MissingCamFromWorld_100) {

    cam_from_worlds.erase(image_t(100));



    EXPECT_TRUE(ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames));

}



TEST_F(RotationInitializerTest_100, MultipleImagesInFrame_100) {

    Frame frame3;

    frame3.AddImageData(image_t(100));

    frame3.AddImageData(image_t(200));

    frames[3] = frame3;



    images[image_t(100)].frame_ptr = &frames[3];

    images[image_t(200)].frame_ptr = &frames[3];



    EXPECT_TRUE(ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames));

}



TEST_F(RotationInitializerTest_100, RefSensorInFrame_100) {

    Rig rig3;

    rig3.SetSensorFromRig(sensor_t(SensorType::CAMERA, 30), Rigid3d(Eigen::Quaterniond(1, 0, 0, 0), Eigen::Vector3d::Zero()));

    rigs[3] = rig3;



    Frame frame4;

    frame4.AddImageData(image_t(300));

    frames[4] = frame4;



    cam_from_worlds[image_t(300)] = Rigid3d(Eigen::Quaterniond(1, 0, 0, 0), Eigen::Vector3d(3, 0, 0));



    images[image_t(300)] = Image(image_t(300), camera_t(30), "image3.jpg");

    images[image_t(300)].SetRegistered(true);

    images[image_t(300)].frame_ptr = &frames[4];



    rigs[3].SetRefSensor(sensor_t(SensorType::CAMERA, 30));



    EXPECT_TRUE(ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames));

}
