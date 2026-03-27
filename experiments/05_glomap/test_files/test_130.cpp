#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/math/tree.cc"

#include "TestProjects/glomap/glomap/scene/image.h"

#include "TestProjects/glomap/glomap/scene/image_pair.h"

#include "TestProjects/glomap/glomap/scene/view_graph.h"



using namespace glomap;



// Test Fixture

class MaximumSpanningTreeTest_130 : public ::testing::Test {

protected:

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<image_t, image_t> parents;



    void SetUp() override {

        // Setup some common data for tests

        images[1] = Image(1, 1, "image1.jpg");

        images[2] = Image(2, 2, "image2.jpg");

        images[3] = Image(3, 3, "image3.jpg");



        view_graph.image_pairs[1] = ImagePair(1, 2);

        view_graph.image_pairs[2] = ImagePair(2, 3);

    }

};



// Test normal operation with INLIER_RATIO

TEST_F(MaximumSpanningTreeTest_130, NormalOperation_INLIER_RATIO_130) {

    view_graph.image_pairs[1].weight = 0.8;

    view_graph.image_pairs[2].weight = 0.9;



    image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_RATIO);



    EXPECT_EQ(root, 1);

    EXPECT_EQ(parents.size(), 3);

    EXPECT_EQ(parents[2], 1);

    EXPECT_EQ(parents[3], 2);

}



// Test normal operation with INLIER_NUM

TEST_F(MaximumSpanningTreeTest_130, NormalOperation_INLIER_NUM_130) {

    view_graph.image_pairs[1].inliers = {1, 2, 3};

    view_graph.image_pairs[2].inliers = {4, 5};



    image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);



    EXPECT_EQ(root, 1);

    EXPECT_EQ(parents.size(), 3);

    EXPECT_EQ(parents[2], 1);

    EXPECT_EQ(parents[3], 2);

}



// Test boundary condition with no valid image pairs

TEST_F(MaximumSpanningTreeTest_130, NoValidImagePairs_130) {

    view_graph.image_pairs[1].is_valid = false;

    view_graph.image_pairs[2].is_valid = false;



    image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_RATIO);



    EXPECT_EQ(root, 1);

    EXPECT_TRUE(parents.empty());

}



// Test boundary condition with one registered image

TEST_F(MaximumSpanningTreeTest_130, OneRegisteredImage_130) {

    images[2] = Image(2, 2, "image2.jpg");

    images[2].IsRegistered() = false;



    view_graph.image_pairs.erase(2); // Remove pair involving unregistered image



    image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_RATIO);



    EXPECT_EQ(root, 1);

    EXPECT_TRUE(parents.empty());

}



// Test exceptional case with invalid image IDs in pairs

TEST_F(MaximumSpanningTreeTest_130, InvalidImageIDsInPairs_130) {

    view_graph.image_pairs[3] = ImagePair(4, 5); // Invalid image IDs



    image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_RATIO);



    EXPECT_EQ(root, 1);

    EXPECT_EQ(parents.size(), 2);

    EXPECT_EQ(parents[2], 1);

}



// Test exceptional case with all unregistered images

TEST_F(MaximumSpanningTreeTest_130, AllUnregisteredImages_130) {

    for (auto& [id, image] : images) {

        image.IsRegistered() = false;

    }



    image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_RATIO);



    EXPECT_EQ(root, 1);

    EXPECT_TRUE(parents.empty());

}
