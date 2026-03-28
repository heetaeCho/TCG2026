#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "relpose_estimation.h"

#include "view_graph.h"

#include "image.h"

#include "image_pair.h"



namespace glomap {



class RelativePoseEstimationTest_102 : public ::testing::Test {

protected:

    ViewGraph view_graph;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<image_t, Image> images;

    RelativePoseEstimationOptions options;



    void SetUp() override {

        // Initialize some basic valid data for tests

        image_t img_id1 = 0, img_id2 = 1;

        camera_t cam_id1 = 0, cam_id2 = 1;

        

        cameras[cam_id1] = Camera(); // Assuming default constructor initializes to a valid state

        cameras[cam_id2] = Camera();



        images[img_id1] = Image(img_id1, cam_id1, "image1.jpg");

        images[img_id2] = Image(img_id2, cam_id2, "image2.jpg");



        view_graph.image_pairs[colmap::ImagePairToPairId(img_id1, img_id2)] = ImagePair(img_id1, img_id2);

    }

};



TEST_F(RelativePoseEstimationTest_102, SingleValidPair_102) {

    EstimateRelativePoses(view_graph, cameras, images, options);

    EXPECT_TRUE(view_graph.image_pairs.begin()->second.is_valid);

}



TEST_F(RelativePoseEstimationTest_102, NoValidPairs_102) {

    view_graph.image_pairs.clear();

    EstimateRelativePoses(view_graph, cameras, images, options);

    EXPECT_TRUE(view_graph.image_pairs.empty());

}



TEST_F(RelativePoseEstimationTest_102, MultipleValidPairs_102) {

    image_t img_id3 = 2;

    camera_t cam_id3 = 2;

    

    cameras[cam_id3] = Camera();

    images[img_id3] = Image(img_id3, cam_id3, "image3.jpg");

    

    view_graph.image_pairs[colmap::ImagePairToPairId(img_id1, img_id3)] = ImagePair(img_id1, img_id3);

    EstimateRelativePoses(view_graph, cameras, images, options);

    EXPECT_TRUE(view_graph.image_pairs.size() == 2);

    for (const auto& pair : view_graph.image_pairs) {

        EXPECT_TRUE(pair.second.is_valid);

    }

}



TEST_F(RelativePoseEstimationTest_102, InvalidPairDueToMatches_102) {

    view_graph.image_pairs.begin()->second.matches = Eigen::MatrixXi(0, 2); // No matches

    EstimateRelativePoses(view_graph, cameras, images, options);

    EXPECT_FALSE(view_graph.image_pairs.begin()->second.is_valid);

}



TEST_F(RelativePoseEstimationTest_102, InvalidPairDueToException_102) {

    // To simulate an exception, we can modify the matches to cause an issue

    view_graph.image_pairs.begin()->second.matches = Eigen::MatrixXi(1, 2);

    view_graph.image_pairs.begin()->second.matches << 99999, 99999; // Invalid indices

    EstimateRelativePoses(view_graph, cameras, images, options);

    EXPECT_FALSE(view_graph.image_pairs.begin()->second.is_valid);

}



} // namespace glomap
