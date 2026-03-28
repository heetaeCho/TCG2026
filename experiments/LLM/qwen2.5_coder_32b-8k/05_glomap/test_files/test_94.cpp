#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/scene/view_graph.h"



using namespace glomap;



class ViewGraphTest_94 : public ::testing::Test {

protected:

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

};



TEST_F(ViewGraphTest_94, MarkConnectedComponents_NoFrames_94) {

    int min_num_img = 1;

    int result = view_graph.MarkConnectedComponents(frames, images, min_num_img);

    EXPECT_EQ(result, 0);

}



TEST_F(ViewGraphTest_94, MarkConnectedComponents_OneFrameNoImages_94) {

    frames[1] = Frame();

    int min_num_img = 1;

    int result = view_graph.MarkConnectedComponents(frames, images, min_num_img);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(frames[1].cluster_id, -1);

}



TEST_F(ViewGraphTest_94, MarkConnectedComponents_OneFrameOneImageBelowThreshold_94) {

    frames[1] = Frame();

    images[1];

    int min_num_img = 2;

    int result = view_graph.MarkConnectedComponents(frames, images, min_num_img);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(frames[1].cluster_id, -1);

}



TEST_F(ViewGraphTest_94, MarkConnectedComponents_OneFrameOneImageAboveThreshold_94) {

    frames[1] = Frame();

    images[1];

    int min_num_img = 1;

    int result = view_graph.MarkConnectedComponents(frames, images, min_num_img);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(frames[1].cluster_id, 0);

}



TEST_F(ViewGraphTest_94, MarkConnectedComponents_MultipleFramesMultipleImagesBelowThreshold_94) {

    frames[1] = Frame();

    frames[2] = Frame();

    images[1];

    images[2];

    int min_num_img = 3;

    int result = view_graph.MarkConnectedComponents(frames, images, min_num_img);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(frames[1].cluster_id, -1);

    EXPECT_EQ(frames[2].cluster_id, -1);

}



TEST_F(ViewGraphTest_94, MarkConnectedComponents_MultipleFramesMultipleImagesAboveThreshold_94) {

    frames[1] = Frame();

    frames[2] = Frame();

    images[1];

    images[2];

    int min_num_img = 1;

    int result = view_graph.MarkConnectedComponents(frames, images, min_num_img);

    EXPECT_EQ(result, 1);

    EXPECT_TRUE((frames[1].cluster_id == 0 && frames[2].cluster_id == 0) ||

                (frames[1].cluster_id == 1 && frames[2].cluster_id == 1));

}



TEST_F(ViewGraphTest_94, MarkConnectedComponents_DisconnectedFrames_94) {

    frames[1] = Frame();

    frames[2] = Frame();

    images[1];

    images[2];

    int min_num_img = 1;

    int result = view_graph.MarkConnectedComponents(frames, images, min_num_img);

    EXPECT_EQ(result, 2);

    EXPECT_TRUE((frames[1].cluster_id == 0 && frames[2].cluster_id == 1) ||

                (frames[1].cluster_id == 1 && frames[2].cluster_id == 0));

}



TEST_F(ViewGraphTest_94, MarkConnectedComponents_ConnectedFramesBelowThreshold_94) {

    frames[1] = Frame();

    frames[2] = Frame();

    images[1];

    images[2];

    // Assuming some logic in CreateFrameAdjacencyList connects these frames

    int min_num_img = 3;

    int result = view_graph.MarkConnectedComponents(frames, images, min_num_img);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(frames[1].cluster_id, -1);

    EXPECT_EQ(frames[2].cluster_id, -1);

}



TEST_F(ViewGraphTest_94, MarkConnectedComponents_ConnectedFramesAboveThreshold_94) {

    frames[1] = Frame();

    frames[2] = Frame();

    images[1];

    images[2];

    // Assuming some logic in CreateFrameAdjacencyList connects these frames

    int min_num_img = 1;

    int result = view_graph.MarkConnectedComponents(frames, images, min_num_img);

    EXPECT_EQ(result, 1);

    EXPECT_TRUE((frames[1].cluster_id == 0 && frames[2].cluster_id == 0) ||

                (frames[1].cluster_id == 1 && frames[2].cluster_id == 1));

}
