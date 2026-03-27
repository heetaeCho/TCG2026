#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <unordered_map>

#include <colmap/scene/reconstruction.h>

#include "glomap/glomap/io/colmap_converter.cc"

#include "glomap/glomap/scene/frame.h"

#include "glomap/glomap/scene/image.h"

#include "glomap/glomap/scene/camera.h"



using namespace glomap;

using ::testing::Eq;



class ColmapConverterTest_120 : public ::testing::Test {

protected:

    colmap::Reconstruction reconstruction;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    void SetUp() override {

        // Setup a basic reconstruction for testing

        colmap::Camera colmap_camera(1);

        reconstruction.AddCamera(colmap_camera);



        colmap::Rig colmap_rig(1);

        reconstruction.AddRig(colmap_rig);



        colmap::Frame colmap_frame;

        colmap_frame.SetImageId(1);

        colmap_frame.SetCameraId(1);

        colmap_frame.SetRigId(1);

        colmap_frame.SetHasPose(true);

        reconstruction.RegisterFrame(1, colmap_frame);



        colmap::Image colmap_image;

        colmap_image.SetImageId(1);

        colmap_image.SetCameraId(1);

        colmap_image.SetFrameId(1);

        colmap_image.SetName("test_image.jpg");

        colmap_image.AddPoint2D(Eigen::Vector2d(0, 0), 1, 2);

        reconstruction.RegisterImage(colmap_image);

    }

};



TEST_F(ColmapConverterTest_120, ConvertColmapToGlomap_NormalOperation_120) {

    ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);



    EXPECT_EQ(cameras.size(), 1);

    EXPECT_EQ(rigs.size(), 1);

    EXPECT_EQ(frames.size(), 1);

    EXPECT_EQ(images.size(), 1);



    const auto& frame = frames[1];

    EXPECT_TRUE(frame.is_registered);

    EXPECT_EQ(frame.RigId(), 1);



    const auto& image = images[1];

    EXPECT_EQ(image.image_id, 1);

    EXPECT_EQ(image.camera_id, 1);

    EXPECT_EQ(image.frame_id, 1);

    EXPECT_EQ(image.features.size(), 1);

}



TEST_F(ColmapConverterTest_120, ConvertColmapToGlomap_BoundaryConditions_EmptyReconstruction_120) {

    colmap::Reconstruction empty_reconstruction;

    ConvertColmapToGlomap(empty_reconstruction, rigs, cameras, frames, images, tracks);



    EXPECT_TRUE(cameras.empty());

    EXPECT_TRUE(rigs.empty());

    EXPECT_TRUE(frames.empty());

    EXPECT_TRUE(images.empty());

}



TEST_F(ColmapConverterTest_120, ConvertColmapToGlomap_BoundaryConditions_NoCameras_120) {

    reconstruction.Cameras().clear();

    ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);



    EXPECT_TRUE(cameras.empty());

    EXPECT_FALSE(rigs.empty());

    EXPECT_EQ(frames.size(), 1);

    EXPECT_TRUE(images.empty());

}



TEST_F(ColmapConverterTest_120, ConvertColmapToGlomap_BoundaryConditions_NoRigs_120) {

    reconstruction.Rigs().clear();

    ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);



    EXPECT_FALSE(cameras.empty());

    EXPECT_TRUE(rigs.empty());

    EXPECT_EQ(frames.size(), 1);

    EXPECT_TRUE(images.empty());

}



TEST_F(ColmapConverterTest_120, ConvertColmapToGlomap_BoundaryConditions_NoFrames_120) {

    reconstruction.Frames().clear();

    ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);



    EXPECT_FALSE(cameras.empty());

    EXPECT_FALSE(rigs.empty());

    EXPECT_TRUE(frames.empty());

    EXPECT_TRUE(images.empty());

}



TEST_F(ColmapConverterTest_120, ConvertColmapToGlomap_BoundaryConditions_NoImages_120) {

    reconstruction.Images().clear();

    ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);



    EXPECT_FALSE(cameras.empty());

    EXPECT_FALSE(rigs.empty());

    EXPECT_EQ(frames.size(), 1);

    EXPECT_TRUE(images.empty());

}



TEST_F(ColmapConverterTest_120, ConvertColmapToGlomap_ExceptionalCases_NoPoseInFrame_120) {

    colmap::Frame frame = reconstruction.Frame(1);

    frame.SetHasPose(false);

    reconstruction.RegisterFrame(1, frame);



    ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);



    const auto& glomap_frame = frames[1];

    EXPECT_FALSE(glomap_frame.is_registered);

}



TEST_F(ColmapConverterTest_120, ConvertColmapToGlomap_ExceptionalCases_MissingRigInFrame_120) {

    colmap::Frame frame = reconstruction.Frame(1);

    frame.SetRigId(-1); // Invalid Rig ID

    reconstruction.RegisterFrame(1, frame);



    ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);



    const auto& glomap_frame = frames[1];

    EXPECT_EQ(glomap_frame.RigId(), -1);

    EXPECT_EQ(glomap_frame.rig_ptr, nullptr);

}



TEST_F(ColmapConverterTest_120, ConvertColmapToGlomap_ExceptionalCases_MissingCameraInImage_120) {

    colmap::Image image = reconstruction.Image(1);

    image.SetCameraId(-1); // Invalid Camera ID

    reconstruction.RegisterImage(image);



    ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);



    const auto& glomap_image = images[1];

    EXPECT_EQ(glomap_image.camera_id, -1);

}



TEST_F(ColmapConverterTest_120, ConvertColmapToGlomap_ExceptionalCases_MissingFrameInImage_120) {

    colmap::Image image = reconstruction.Image(1);

    image.SetFrameId(-1); // Invalid Frame ID

    reconstruction.RegisterImage(image);



    ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);



    const auto& glomap_image = images[1];

    EXPECT_EQ(glomap_image.frame_id, -1);

    EXPECT_EQ(glomap_image.frame_ptr, nullptr);

}
