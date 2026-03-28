#include <gtest/gtest.h>
#include "glomap/scene/image.h"
#include "glomap/scene/frame.h"

namespace glomap {

class ImageTest_1 : public ::testing::Test {
protected:
    Image image_;
    Frame frame_;
};

// Tests that IsRegistered returns false when frame_ptr is nullptr
TEST_F(ImageTest_1, IsRegistered_ReturnsFalse_WhenFramePtrNull_1) {
    image_.frame_ptr = nullptr;
    EXPECT_FALSE(image_.IsRegistered());
}

// Tests that IsRegistered returns false when frame_ptr is set but not registered
TEST_F(ImageTest_1, IsRegistered_ReturnsFalse_WhenFrameNotRegistered_1) {
    frame_.is_registered = false;
    image_.frame_ptr = &frame_;
    EXPECT_FALSE(image_.IsRegistered());
}

// Tests that IsRegistered returns true when frame_ptr is set and frame is registered
TEST_F(ImageTest_1, IsRegistered_ReturnsTrue_WhenFrameRegistered_1) {
    frame_.is_registered = true;
    image_.frame_ptr = &frame_;
    EXPECT_TRUE(image_.IsRegistered());
}

// Tests boundary case: IsRegistered behavior when frame_ptr points to an invalid or dangling Frame (simulated null)
TEST_F(ImageTest_1, IsRegistered_HandlesDanglingFramePtr_1) {
    Frame* dangling_ptr = nullptr;
    image_.frame_ptr = dangling_ptr;
    EXPECT_FALSE(image_.IsRegistered());
}

}  // namespace glomap
