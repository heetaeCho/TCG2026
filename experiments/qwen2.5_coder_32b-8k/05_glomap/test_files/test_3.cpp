#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/scene/image.h"

#include "glomap/scene/frame.h"



using namespace glomap;

using ::testing::Return;



class ImageTest_3 : public ::testing::Test {

protected:

    Frame frame;

    Image image;



    void SetUp() override {

        // Initialize the Frame object

        frame.gravity_info.has_gravity = false;  // Default no gravity



        // Initialize the Image object with a reference to the Frame

        image.frame_ptr = &frame;

        image.camera_id = 0;

        image.image_id = 1;

        image.file_name = "test_image.png";

    }

};



TEST_F(ImageTest_3, GetRAlign_NoGravity_3) {

    // No gravity case should return Identity matrix

    EXPECT_EQ(image.GetRAlign(), Eigen::Matrix3d::Identity());

}



TEST_F(ImageTest_3, GetRAlign_HasGravityTrivialFrame_3) {

    // Set up the frame with gravity and trivial frame

    frame.gravity_info.has_gravity = true;

    frame.gravity_info.R_align_ = Eigen::Matrix3d::Random();



    EXPECT_CALL(frame, HasTrivialFrame()).WillRepeatedly(Return(true));

    EXPECT_EQ(image.GetRAlign(), frame.gravity_info.GetRAlign());

}



TEST_F(ImageTest_3, GetRAlign_HasGravityNonTrivialFrame_3) {

    // Set up the frame with gravity and non-trivial frame

    frame.gravity_info.has_gravity = true;

    frame.gravity_info.R_align_ = Eigen::Matrix3d::Random();



    EXPECT_CALL(frame, HasTrivialFrame()).WillRepeatedly(Return(false));

    auto sensor_from_rig_rotation = Eigen::Quaterniond::Identity();

    EXPECT_EQ(image.GetRAlign(), sensor_from_rig_rotation.toRotationMatrix() * frame.gravity_info.GetRAlign());

}



TEST_F(ImageTest_3, HasGravity_ReturnsFalse_3) {

    // Default case where has_gravity is false

    EXPECT_FALSE(image.HasGravity());

}



TEST_F(ImageTest_3, HasGravity_ReturnsTrue_3) {

    // Set gravity and check if HasGravity returns true

    frame.gravity_info.has_gravity = true;

    EXPECT_TRUE(image.HasGravity());

}

```



**Notes:**

- The `HasTrivialFrame` and `RigPtr` methods are not mocked because they are internal to the `Frame` class. According to the constraints, we should treat the implementation as a black box.

- Since `HasTrivialFrame` is used in `GetRAlign`, it is mocked to simulate both trivial and non-trivial frame scenarios.
