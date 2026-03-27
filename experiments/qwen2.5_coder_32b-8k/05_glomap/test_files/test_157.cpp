#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/scene/image.h"

#include "glomap/scene/image_pair.h"

#include "glomap/scene/view_graph.h"

#include "glomap/processors/view_graph_manipulation.h"



using namespace glomap;

using ::testing::UnorderedElementsAre;

using ::testing::Return;



class ViewGraphManipulaterTest : public ::testing::Test {

protected:

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

};



TEST_F(ViewGraphManipulaterTest_157, SparsifyGraph_NormalOperation_157) {

    // Setup

    image_t img_id1 = 1;

    image_t img_id2 = 2;

    image_pair_t pair_id = colmap::ImagePairToPairId(img_id1, img_id2);

    Image img1(img_id1, 1, "img1.jpg");

    Image img2(img_id2, 2, "img2.jpg");

    images[img_id1] = img1;

    images[img_id2] = img2;

    view_graph.image_pairs[pair_id] = ImagePair(img_id1, img_id2);



    // Act

    int expected_degree = 1;

    image_pair_t result = ViewGraphManipulater::SparsifyGraph(view_graph, frames, images, expected_degree);



    // Assert

    EXPECT_EQ(result, 1);

}



TEST_F(ViewGraphManipulaterTest_157, SparsifyGraph_NoImagesRegistered_157) {

    // Setup

    image_t img_id1 = 1;

    image_t img_id2 = 2;

    image_pair_t pair_id = colmap::ImagePairToPairId(img_id1, img_id2);

    Image img1(img_id1, 1, "img1.jpg");

    Image img2(img_id2, 2, "img2.jpg");

    images[img_id1] = img1;

    images[img2] = img2;

    view_graph.image_pairs[pair_id] = ImagePair(img_id1, img_id2);



    // Modify images to be unregistered

    images[img_id1].IsRegistered = []() { return false; };

    images[img_id2].IsRegistered = []() { return false; };



    // Act

    int expected_degree = 1;

    image_pair_t result = ViewGraphManipulater::SparsifyGraph(view_graph, frames, images, expected_degree);



    // Assert

    EXPECT_EQ(result, 0);

}



TEST_F(ViewGraphManipulaterTest_157, SparsifyGraph_AllEdgesRemoved_157) {

    // Setup

    image_t img_id1 = 1;

    image_t img_id2 = 2;

    image_pair_t pair_id = colmap::ImagePairToPairId(img_id1, img_id2);

    Image img1(img_id1, 1, "img1.jpg");

    Image img2(img_id2, 2, "img2.jpg");

    images[img_id1] = img1;

    images[img_id2] = img2;

    view_graph.image_pairs[pair_id] = ImagePair(img_id1, img_id2);



    // Act

    int expected_degree = 10; // High expected degree to ensure all edges are removed

    image_pair_t result = ViewGraphManipulater::SparsifyGraph(view_graph, frames, images, expected_degree);



    // Assert

    EXPECT_EQ(result, 0);

}



TEST_F(ViewGraphManipulaterTest_157, SparsifyGraph_BoundaryCondition_EmptyGraph_157) {

    // Setup: Empty graph



    // Act

    int expected_degree = 1;

    image_pair_t result = ViewGraphManipulater::SparsifyGraph(view_graph, frames, images, expected_degree);



    // Assert

    EXPECT_EQ(result, 0);

}



TEST_F(ViewGraphManipulaterTest_157, SparsifyGraph_BoundaryCondition_SingleImage_157) {

    // Setup

    image_t img_id = 1;

    Image img(img_id, 1, "img1.jpg");

    images[img_id] = img;



    // Act

    int expected_degree = 1;

    image_pair_t result = ViewGraphManipulater::SparsifyGraph(view_graph, frames, images, expected_degree);



    // Assert

    EXPECT_EQ(result, 0);

}



TEST_F(ViewGraphManipulaterTest_157, SparsifyGraph_BoundaryCondition_ZeroExpectedDegree_157) {

    // Setup

    image_t img_id1 = 1;

    image_t img_id2 = 2;

    image_pair_t pair_id = colmap::ImagePairToPairId(img_id1, img_id2);

    Image img1(img_id1, 1, "img1.jpg");

    Image img2(img_id2, 2, "img2.jpg");

    images[img_id1] = img1;

    images[img_id2] = img2;

    view_graph.image_pairs[pair_id] = ImagePair(img_id1, img_id2);



    // Act

    int expected_degree = 0;

    image_pair_t result = ViewGraphManipulater::SparsifyGraph(view_graph, frames, images, expected_degree);



    // Assert

    EXPECT_EQ(result, 0);

}
