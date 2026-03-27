#include <gtest/gtest.h>

#include "glomap/scene/view_graph.h"

#include "glomap/scene/frame.h"

#include "glomap/scene/image.h"

#include "glomap/scene/image_pair.h"



using namespace glomap;



class ViewGraphTest_93 : public ::testing::Test {

protected:

    ViewGraph view_graph;

};



TEST_F(ViewGraphTest_93, NoFramesNoImages_93) {

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    int result = view_graph.KeepLargestConnectedComponents(frames, images);



    EXPECT_EQ(result, 0);

}



TEST_F(ViewGraphTest_93, SingleFrameNoImages_93) {

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}};

    std::unordered_map<image_t, Image> images;



    int result = view_graph.KeepLargestConnectedComponents(frames, images);



    EXPECT_EQ(result, 0);

}



TEST_F(ViewGraphTest_93, SingleFrameSingleImageNotRegistered_93) {

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}};

    Image image(1, 1, "test.jpg");

    std::unordered_map<image_t, Image> images = {{1, image}};



    int result = view_graph.KeepLargestConnectedComponents(frames, images);



    EXPECT_EQ(result, 0);

}



TEST_F(ViewGraphTest_93, SingleFrameSingleImageRegistered_93) {

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}};

    Image image(1, 1, "test.jpg");

    image.frame_id = 1;

    frames[1].is_registered = true;

    std::unordered_map<image_t, Image> images = {{1, image}};



    int result = view_graph.KeepLargestConnectedComponents(frames, images);



    EXPECT_EQ(result, 1);

}



TEST_F(ViewGraphTest_93, MultipleFramesSingleComponent_93) {

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}, {2, Frame()}};

    Image image1(1, 1, "test1.jpg");

    Image image2(2, 1, "test2.jpg");

    image1.frame_id = 1;

    image2.frame_id = 1;

    std::unordered_map<image_t, Image> images = {{1, image1}, {2, image2}};



    int result = view_graph.KeepLargestConnectedComponents(frames, images);



    EXPECT_EQ(result, 2);

}



TEST_F(ViewGraphTest_93, MultipleFramesMultipleComponents_93) {

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}, {2, Frame()}};

    Image image1(1, 1, "test1.jpg");

    Image image2(2, 1, "test2.jpg");

    image1.frame_id = 1;

    image2.frame_id = 2;

    std::unordered_map<image_t, Image> images = {{1, image1}, {2, image2}};



    int result = view_graph.KeepLargestConnectedComponents(frames, images);



    EXPECT_EQ(result, 1);

}



TEST_F(ViewGraphTest_93, MultipleFramesMultipleImagesInOneComponent_93) {

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}, {2, Frame()}};

    Image image1(1, 1, "test1.jpg");

    Image image2(2, 1, "test2.jpg");

    Image image3(3, 1, "test3.jpg");

    image1.frame_id = 1;

    image2.frame_id = 1;

    image3.frame_id = 1;

    std::unordered_map<image_t, Image> images = {{1, image1}, {2, image2}, {3, image3}};



    int result = view_graph.KeepLargestConnectedComponents(frames, images);



    EXPECT_EQ(result, 2);

}



TEST_F(ViewGraphTest_93, MultipleFramesMultipleImagesInDifferentComponents_93) {

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}, {2, Frame()}};

    Image image1(1, 1, "test1.jpg");

    Image image2(2, 1, "test2.jpg");

    image1.frame_id = 1;

    image2.frame_id = 2;

    std::unordered_map<image_t, Image> images = {{1, image1}, {2, image2}};



    int result = view_graph.KeepLargestConnectedComponents(frames, images);



    EXPECT_EQ(result, 1);

}



TEST_F(ViewGraphTest_93, FramesWithNoImagesRegistered_93) {

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}, {2, Frame()}};

    std::unordered_map<image_t, Image> images;



    int result = view_graph.KeepLargestConnectedComponents(frames, images);



    EXPECT_EQ(result, 0);

}



TEST_F(ViewGraphTest_93, AllFramesRegisteredAfterProcessing_93) {

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}, {2, Frame()}};

    Image image1(1, 1, "test1.jpg");

    Image image2(2, 1, "test2.jpg");

    image1.frame_id = 1;

    image2.frame_id = 1;

    std::unordered_map<image_t, Image> images = {{1, image1}, {2, image2}};



    int result = view_graph.KeepLargestConnectedComponents(frames, images);



    EXPECT_TRUE(frames[1].is_registered);

    EXPECT_TRUE(frames[2].is_registered);

}



TEST_F(ViewGraphTest_93, ImagePairsInvalidatedCorrectly_93) {

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}, {2, Frame()}};

    Image image1(1, 1, "test1.jpg");

    Image image2(2, 1, "test2.jpg");

    image1.frame_id = 1;

    image2.frame_id = 2;

    view_graph.image_pairs = {{1, ImagePair(1, 2)}};

    std::unordered_map<image_t, Image> images = {{1, image1}, {2, image2}};



    int result = view_graph.KeepLargestConnectedComponents(frames, images);



    EXPECT_FALSE(view_graph.image_pairs[1].is_valid);

}
