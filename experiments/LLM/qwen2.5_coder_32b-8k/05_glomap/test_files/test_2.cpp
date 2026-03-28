#include <gtest/gtest.h>

#include "TestProjects/glomap/glomap/scene/image.h"



namespace {



class ImageTest_2 : public ::testing::Test {

protected:

    glomap::Image imageWithoutFrame;

    glomap::Frame frameWithClusterId;

    glomap::Image imageWithFrame;



    ImageTest_2() 

        : imageWithoutFrame(1, 2, "test_file.jpg"),

          frameWithClusterId(),

          imageWithFrame(3, 4, "another_test_file.jpg") {

        frameWithClusterId.cluster_id = 5;

        imageWithFrame.frame_ptr = &frameWithClusterId;

    }

};



TEST_F(ImageTest_2, ClusterId_ReturnsMinusOne_WhenFrameIsNull_2) {

    EXPECT_EQ(imageWithoutFrame.ClusterId(), -1);

}



TEST_F(ImageTest_2, ClusterId_ReturnsCorrectValue_WhenFrameIsNotNull_2) {

    EXPECT_EQ(imageWithFrame.ClusterId(), 5);

}



} // namespace
