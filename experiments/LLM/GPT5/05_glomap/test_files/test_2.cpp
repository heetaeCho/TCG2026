#include <gtest/gtest.h>

#include "glomap/scene/image.h"
#include "glomap/scene/frame.h"

namespace {

using glomap::Image;
using glomap::Frame;

// Fixture for Image::ClusterId tests
class ImageClusterIdTest_2 : public ::testing::Test {};

//
// Normal / default behavior: no frame associated
//
TEST_F(ImageClusterIdTest_2, ReturnsMinusOneWhenFramePtrIsNull_2) {
    Image image;  // Default-constructed; frame_ptr is expected to be nullptr
    EXPECT_EQ(-1, image.ClusterId());
}

//
// Normal behavior: frame_ptr points to a Frame with a valid cluster_id
//
TEST_F(ImageClusterIdTest_2, ReturnsClusterIdFromFrameWhenFrameIsSet_2) {
    Frame frame;
    frame.cluster_id = 7;

    Image image;
    image.frame_ptr = &frame;

    EXPECT_EQ(7, image.ClusterId());
}

//
// Boundary-ish behavior: frame is set but its cluster_id is left at default
// (verifies that the method simply forwards the Frame's cluster_id value)
//
TEST_F(ImageClusterIdTest_2, ReturnsDefaultClusterIdFromFrameIfNotModified_2) {
    Frame frame;           // cluster_id is expected to be initialized (e.g., -1)
    Image image;
    image.frame_ptr = &frame;

    EXPECT_EQ(frame.cluster_id, image.ClusterId());
}

//
// Additional behavior: changes to Frame::cluster_id are reflected in ClusterId()
// (verifies that the method always reads the current value, rather than caching)
//
TEST_F(ImageClusterIdTest_2, ReflectsUpdatedClusterIdFromFrame_2) {
    Frame frame;
    frame.cluster_id = 3;

    Image image;
    image.frame_ptr = &frame;

    EXPECT_EQ(3, image.ClusterId());

    frame.cluster_id = 10;
    EXPECT_EQ(10, image.ClusterId());
}

//
// Const-correctness: ClusterId can be called on a const Image instance
// when no frame is associated.
//
TEST_F(ImageClusterIdTest_2, ConstImageReturnsMinusOneWhenFramePtrIsNull_2) {
    const Image image;  // Default-constructed const object
    EXPECT_EQ(-1, image.ClusterId());
}

}  // namespace
