#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "TestProjects/glomap/glomap/processors/view_graph_manipulation.h"

#include "TestProjects/glomap/glomap/scene/image.h"

#include "TestProjects/glomap/glomap/scene/image_pair.h"

#include "TestProjects/glomap/glomap/scene/view_graph.h"



using namespace glomap;



class ViewGraphManipulaterTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary objects or states

    }



    void TearDown() override {

        // Clean up if necessary

    }

};



TEST_F(ViewGraphManipulaterTest_158, NormalOperation_INLIER_NUM_158) {

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    // Populate the view_graph and related maps with test data

    image_t image_id1 = 1, image_id2 = 2;

    frame_t frame_id1 = 10, frame_id2 = 20;

    Frame frame1(frame_id1);

    Frame frame2(frame_id2);



    frames[frame_id1] = frame1;

    frames[frame_id2] = frame2;



    Image img1(image_id1, 1, "image1.jpg");

    Image img2(image_id2, 2, "image2.jpg");



    images[image_id1] = img1;

    images[image_id2] = img2;



    image_pair_t pair_id = colmap::ImagePairToPairId(image_id1, image_id2);

    ImagePair image_pair(image_id1, image_id2);



    image_pair.inliers.resize(5); // Assuming 5 inliers

    view_graph.image_pairs[pair_id] = image_pair;



    StrongClusterCriteria criteria = INLIER_NUM;

    double min_thres = 3.0;

    int min_num_images = 2;



    ViewGraphManipulater manipulator;

    int num_clusters = manipulator.EstablishStrongClusters(view_graph, frames, images, criteria, min_thres, min_num_images);



    EXPECT_EQ(num_clusters, 1);

}



TEST_F(ViewGraphManipulaterTest_158, NormalOperation_WEIGHT_158) {

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    // Populate the view_graph and related maps with test data

    image_t image_id1 = 1, image_id2 = 2;

    frame_t frame_id1 = 10, frame_id2 = 20;

    Frame frame1(frame_id1);

    Frame frame2(frame_id2);



    frames[frame_id1] = frame1;

    frames[frame_id2] = frame2;



    Image img1(image_id1, 1, "image1.jpg");

    Image img2(image_id2, 2, "image2.jpg");



    images[image_id1] = img1;

    images[image_id2] = img2;



    image_pair_t pair_id = colmap::ImagePairToPairId(image_id1, image_id2);

    ImagePair image_pair(image_id1, image_id2);



    image_pair.weight = 4.0; // Assuming weight 4.0

    view_graph.image_pairs[pair_id] = image_pair;



    StrongClusterCriteria criteria = WEIGHT;

    double min_thres = 3.0;

    int min_num_images = 2;



    ViewGraphManipulater manipulator;

    int num_clusters = manipulator.EstablishStrongClusters(view_graph, frames, images, criteria, min_thres, min_num_images);



    EXPECT_EQ(num_clusters, 1);

}



TEST_F(ViewGraphManipulaterTest_158, BoundaryCondition_EmptyViewGraph_158) {

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    StrongClusterCriteria criteria = INLIER_NUM;

    double min_thres = 3.0;

    int min_num_images = 2;



    ViewGraphManipulater manipulator;

    int num_clusters = manipulator.EstablishStrongClusters(view_graph, frames, images, criteria, min_thres, min_num_images);



    EXPECT_EQ(num_clusters, 0);

}



TEST_F(ViewGraphManipulaterTest_158, BoundaryCondition_SingleImagePair_158) {

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    // Populate the view_graph and related maps with test data

    image_t image_id1 = 1, image_id2 = 2;

    frame_t frame_id1 = 10, frame_id2 = 20;

    Frame frame1(frame_id1);

    Frame frame2(frame_id2);



    frames[frame_id1] = frame1;

    frames[frame_id2] = frame2;



    Image img1(image_id1, 1, "image1.jpg");

    Image img2(image_id2, 2, "image2.jpg");



    images[image_id1] = img1;

    images[image_id2] = img2;



    image_pair_t pair_id = colmap::ImagePairToPairId(image_id1, image_id2);

    ImagePair image_pair(image_id1, image_id2);



    image_pair.inliers.resize(5); // Assuming 5 inliers

    view_graph.image_pairs[pair_id] = image_pair;



    StrongClusterCriteria criteria = INLIER_NUM;

    double min_thres = 3.0;

    int min_num_images = 2;



    ViewGraphManipulater manipulator;

    int num_clusters = manipulator.EstablishStrongClusters(view_graph, frames, images, criteria, min_thres, min_num_images);



    EXPECT_EQ(num_clusters, 1);

}



TEST_F(ViewGraphManipulaterTest_158, BoundaryCondition_MaxIterations_158) {

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    // Populate the view_graph and related maps with test data

    for (int i = 0; i < 20; ++i) {

        image_t image_id = i + 1;

        frame_t frame_id = 10 + i;

        Frame frame(frame_id);

        frames[frame_id] = frame;



        Image img(image_id, i + 1, "image" + std::to_string(i) + ".jpg");

        images[image_id] = img;



        for (int j = i + 1; j < 20; ++j) {

            image_t image_id_j = j + 1;

            frame_t frame_id_j = 10 + j;

            image_pair_t pair_id = colmap::ImagePairToPairId(image_id, image_id_j);

            ImagePair image_pair(image_id, image_id_j);



            image_pair.inliers.resize(3); // Assuming 3 inliers

            view_graph.image_pairs[pair_id] = image_pair;

        }

    }



    StrongClusterCriteria criteria = INLIER_NUM;

    double min_thres = 5.0; // Set threshold high to ensure iterations reach max limit

    int min_num_images = 2;



    ViewGraphManipulater manipulator;

    int num_clusters = manipulator.EstablishStrongClusters(view_graph, frames, images, criteria, min_thres, min_num_images);



    EXPECT_EQ(num_clusters, 1); // All images should be in one cluster due to high threshold

}



TEST_F(ViewGraphManipulaterTest_158, ExceptionalCase_InvalidImagePair_158) {

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    // Populate the view_graph and related maps with test data

    image_t image_id1 = 1, image_id2 = 2;

    frame_t frame_id1 = 10, frame_id2 = 20;

    Frame frame1(frame_id1);

    Frame frame2(frame_id2);



    frames[frame_id1] = frame1;

    frames[frame_id2] = frame2;



    Image img1(image_id1, 1, "image1.jpg");

    Image img2(image_id2, 2, "image2.jpg");



    images[image_id1] = img1;

    images[image_id2] = img2;



    image_pair_t pair_id = colmap::ImagePairToPairId(image_id1, image_id2);

    ImagePair image_pair(image_id1, image_id2);



    image_pair.is_valid = false; // Mark the image pair as invalid

    view_graph.image_pairs[pair_id] = image_pair;



    StrongClusterCriteria criteria = INLIER_NUM;

    double min_thres = 3.0;

    int min_num_images = 2;



    ViewGraphManipulater manipulator;

    int num_clusters = manipulator.EstablishStrongClusters(view_graph, frames, images, criteria, min_thres, min_num_images);



    EXPECT_EQ(num_clusters, 0); // No valid pairs should result in no clusters

}
