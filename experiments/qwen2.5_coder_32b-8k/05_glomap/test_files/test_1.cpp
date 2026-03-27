#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/scene/image.h"

#include "TestProjects/glomap/glomap/scene/frame.h"



using namespace glomap;



class ImageTest_1 : public ::testing::Test {

protected:

    std::unique_ptr<Image> image;

    std::unique_ptr<Frame> frame;



    void SetUp() override {

        frame = std::make_unique<Frame>();

        image = std::make_unique<Image>(0, 0, "test_image.jpg");

    }

};



TEST_F(ImageTest_1, IsRegistered_ReturnsFalse_WhenFrameIsNullptr_1) {

    image->frame_ptr = nullptr;

    EXPECT_FALSE(image->IsRegistered());

}



TEST_F(ImageTest_1, IsRegistered_ReturnsTrue_WhenFrameIsRegistered_1) {

    frame->is_registered = true;

    image->frame_ptr = frame.get();

    EXPECT_TRUE(image->IsRegistered());

}



TEST_F(ImageTest_1, IsRegistered_ReturnsFalse_WhenFrameIsNotRegistered_1) {

    frame->is_registered = false;

    image->frame_ptr = frame.get();

    EXPECT_FALSE(image->IsRegistered());

}
