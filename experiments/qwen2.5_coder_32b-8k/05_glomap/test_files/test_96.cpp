#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "view_graph.h"

#include "image.h"



using namespace glomap;

using ::testing::UnorderedElementsAreArray;



class ViewGraphTest_96 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any necessary preconditions here

        image1 = Image(1, 101, "image1.jpg");

        image2 = Image(2, 102, "image2.jpg");

        image3 = Image(3, 103, "image3.jpg");



        image_pairs = {

            {colmap::ImagePairToPairId(image1.image_id, image2.image_id), ImagePair(image1.image_id, image2.image_id)},

            {colmap::ImagePairToPairId(image2.image_id, image3.image_id), ImagePair(image2.image_id, image3.image_id)}

        };



        images = {

            {image1.image_id, image1},

            {image2.image_id, image2},

            {image3.image_id, image3}

        };

    }



    ViewGraph view_graph;

    Image image1, image2, image3;

    std::unordered_map<image_pair_t, ImagePair> image_pairs;

    std::unordered_map<image_t, Image> images;

};



TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_NormalOperation_96) {

    auto adjacency_list = view_graph.CreateFrameAdjacencyList(images);

    

    EXPECT_EQ(adjacency_list.size(), 3);

    EXPECT_THAT(adjacency_list[image1.frame_id], UnorderedElementsAreArray({image2.frame_id}));

    EXPECT_THAT(adjacency_list[image2.frame_id], UnorderedElementsAreArray({image1.frame_id, image3.frame_id}));

    EXPECT_THAT(adjacency_list[image3.frame_id], UnorderedElementsAreArray({image2.frame_id}));

}



TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_BoundaryCondition_NoImages_96) {

    std::unordered_map<image_t, Image> empty_images;

    auto adjacency_list = view_graph.CreateFrameAdjacencyList(empty_images);

    

    EXPECT_TRUE(adjacency_list.empty());

}



TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_BoundaryCondition_SingleImage_96) {

    Image single_image(4, 104, "single_image.jpg");

    std::unordered_map<image_t, Image> single_image_map = {{single_image.image_id, single_image}};

    

    auto adjacency_list = view_graph.CreateFrameAdjacencyList(single_image_map);

    

    EXPECT_EQ(adjacency_list.size(), 1);

    EXPECT_TRUE(adjacency_list[single_image.frame_id].empty());

}



TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_ExceptionalCase_ImageNotFound_96) {

    // Modify image_pairs to refer to an image not in images

    image_pairs[colmap::ImagePairToPairId(4, 5)] = ImagePair(4, 5);

    

    EXPECT_THROW(view_graph.CreateFrameAdjacencyList(images), std::out_of_range);

}
