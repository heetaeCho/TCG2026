#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "view_graph_manipulation.cc"



using namespace glomap;

using ::testing::_;

using ::testing::Return;



class ViewGraphManipulaterTest_88 : public ::testing::Test {

protected:

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

};



TEST_F(ViewGraphManipulaterTest_88, NormalOperation_NoClusters_88) {

    StrongClusterCriteria criteria = INLIER_NUM;

    double min_thres = 10.0;

    int min_num_images = 2;



    image_t result = view_graph.Manipulater().EstablishStrongClusters(view_graph, frames, images, criteria, min_thres, min_num_images);

    EXPECT_EQ(result, 0); // Assuming no clusters formed

}



TEST_F(ViewGraphManipulaterTest_88, NormalOperation_SingleCluster_88) {

    StrongClusterCriteria criteria = INLIER_NUM;

    double min_thres = 10.0;

    int min_num_images = 2;



    // Setting up a single cluster scenario

    Image img1{1, 1};

    Image img2{2, 1};



    images.insert({1, img1});

    images.insert({2, img2});



    Frame frame1{1};

    frames.insert({1, frame1});



    ViewGraph::ImagePair pair1;

    pair1.image_id1 = 1;

    pair1.image_id2 = 2;

    pair1.inliers = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    pair1.is_valid = true;



    view_graph.image_pairs.insert({1, pair1});



    image_t result = view_graph.Manipulater().EstablishStrongClusters(view_graph, frames, images, criteria, min_thres, min_num_images);

    EXPECT_EQ(result, 1); // Single cluster formed

}



TEST_F(ViewGraphManipulaterTest_88, BoundaryConditions_EmptyInputs_88) {

    StrongClusterCriteria criteria = INLIER_NUM;

    double min_thres = 10.0;

    int min_num_images = 2;



    image_t result = view_graph.Manipulater().EstablishStrongClusters(view_graph, frames, images, criteria, min_thres, min_num_images);

    EXPECT_EQ(result, 0); // No clusters formed with empty inputs

}



TEST_F(ViewGraphManipulaterTest_88, BoundaryConditions_MinThreshold_88) {

    StrongClusterCriteria criteria = INLIER_NUM;

    double min_thres = 10.0;

    int min_num_images = 2;



    Image img1{1, 1};

    Image img2{2, 1};



    images.insert({1, img1});

    images.insert({2, img2});



    Frame frame1{1};

    frames.insert({1, frame1});



    ViewGraph::ImagePair pair1;

    pair1.image_id1 = 1;

    pair1.image_id2 = 2;

    pair1.inliers = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}; // Just below min_thres

    pair1.is_valid = true;



    view_graph.image_pairs.insert({1, pair1});



    image_t result = view_graph.Manipulater().EstablishStrongClusters(view_graph, frames, images, criteria, min_thres, min_num_images);

    EXPECT_EQ(result, 2); // No clusters formed due to inliers count

}



TEST_F(ViewGraphManipulaterTest_88, ExceptionalCases_InvalidPairs_88) {

    StrongClusterCriteria criteria = INLIER_NUM;

    double min_thres = 10.0;

    int min_num_images = 2;



    Image img1{1, 1};

    images.insert({1, img1});



    Frame frame1{1};

    frames.insert({1, frame1});



    ViewGraph::ImagePair pair1;

    pair1.image_id1 = 1;

    pair1.image_id2 = 2; // Invalid image_id2

    pair1.inliers = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    pair1.is_valid = true;



    view_graph.image_pairs.insert({1, pair1});



    image_t result = view_graph.Manipulater().EstablishStrongClusters(view_graph, frames, images, criteria, min_thres, min_num_images);

    EXPECT_EQ(result, 1); // Only one image available

}



TEST_F(ViewGraphManipulaterTest_88, VerificationOfExternalInteractions_ValidPairs_88) {

    StrongClusterCriteria criteria = INLIER_NUM;

    double min_thres = 10.0;

    int min_num_images = 2;



    Image img1{1, 1};

    Image img2{2, 1};



    images.insert({1, img1});

    images.insert({2, img2});



    Frame frame1{1};

    frames.insert({1, frame1});



    ViewGraph::ImagePair pair1;

    pair1.image_id1 = 1;

    pair1.image_id2 = 2;

    pair1.inliers = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    pair1.is_valid = true;



    view_graph.image_pairs.insert({1, pair1});



    image_t result = view_graph.Manipulater().EstablishStrongClusters(view_graph, frames, images, criteria, min_thres, min_num_images);

    EXPECT_EQ(result, 1); // Single cluster formed due to valid pairs

}
