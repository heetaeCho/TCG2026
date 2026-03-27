#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/io/colmap_converter.cc"

#include "./TestProjects/glomap/glomap/scene/frame.h"

#include "./TestProjects/glomap/glomap/scene/image.h"



namespace glomap {



using ::testing::_;

using ::testing::Eq;

using ::testing::Ne;



class CreateFrameForImageTest_123 : public ::testing::Test {

protected:

    Rigid3d cam_from_world;

    Image image;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    rig_t rig_id = 1;

    frame_t frame_id = 2;



    void SetUp() override {

        image.image_id = 3;

        image.camera_id = 4;

        image.file_name = "test_image.png";

    }

};



TEST_F(CreateFrameForImageTest_123, NormalOperation_123) {

    CreateFrameForImage(cam_from_world, image, rigs, frames, rig_id, frame_id);

    EXPECT_EQ(image.frame_id, frame_id);

    EXPECT_NE(image.frame_ptr, nullptr);

    EXPECT_EQ(frames.find(frame_id)->second.GetRigId(), rig_id);

}



TEST_F(CreateFrameForImageTest_123, FrameIdFromImage_123) {

    CreateFrameForImage(cam_from_world, image, rigs, frames, rig_id, colmap::kInvalidFrameId);

    EXPECT_EQ(image.frame_id, image.image_id);

    EXPECT_NE(image.frame_ptr, nullptr);

}



TEST_F(CreateFrameForImageTest_123, RigIdFromCamera_123) {

    CreateFrameForImage(cam_from_world, image, rigs, frames, colmap::kInvalidRigId, frame_id);

    EXPECT_EQ(image.frame_id, frame_id);

    EXPECT_NE(image.frame_ptr, nullptr);

    EXPECT_EQ(frames.find(frame_id)->second.GetRigId(), image.camera_id);

}



TEST_F(CreateFrameForImageTest_123, RigNotFound_123) {

    CreateFrameForImage(cam_from_world, image, rigs, frames, rig_id, frame_id);

    EXPECT_EQ(image.frame_id, frame_id);

    EXPECT_NE(image.frame_ptr, nullptr);

    EXPECT_EQ(frames.find(frame_id)->second.GetRigPtr(), nullptr);

}



TEST_F(CreateFrameForImageTest_123, FrameAlreadyExists_123) {

    Frame existing_frame;

    frames[frame_id] = existing_frame;

    CreateFrameForImage(cam_from_world, image, rigs, frames, rig_id, frame_id);

    EXPECT_EQ(image.frame_id, frame_id);

    EXPECT_NE(image.frame_ptr, nullptr);

    EXPECT_EQ(&frames.find(frame_id)->second, image.frame_ptr);

}



} // namespace glomap
