#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/processors/image_pair_inliers.h"

#include "glomap/types.h"

#include "glomap/scene/image.h"

#include "glomap/scene/image_pair.h"



using namespace glomap;

using ::testing::ElementsAre;



class ImagePairInliersTest_79 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize necessary objects for testing

        image_id1 = 1;

        image_id2 = 2;

        pair_id = colmap::ImagePairToPairId(image_id1, image_id2);

        

        image1 = Image(image_id1, camera_id1, "image1.jpg");

        image2 = Image(image_id2, camera_id2, "image2.jpg");



        // Adding some features for the images

        image1.features.push_back(Eigen::Vector2d(0.1, 0.2));

        image2.features.push_back(Eigen::Vector2d(0.3, 0.4));



        matches = Eigen::MatrixXi(1, 2);

        matches << 0, 0;



        H_matrix.setIdentity();



        image_pair = ImagePair(image_id1, image_id2);

        image_pair.H = H_matrix;

        image_pair.matches = matches;



        options.max_epipolar_error_H = 4.0;



        images_map[image_id1] = image1;

        images_map[image_id2] = image2;

    }



    image_t image_id1, image_id2, pair_id, camera_id1 = 1, camera_id2 = 2;

    Image image1, image2;

    Eigen::MatrixXi matches;

    Eigen::Matrix3d H_matrix;

    ImagePair image_pair;

    InlierThresholdOptions options;

    std::unordered_map<image_t, Image> images_map;



    ImagePairInliers inliers_processor = ImagePairInliers(image_pair, images_map, options);

};



TEST_F(ImagePairInliersTest_79, ScoreErrorHomography_NormalOperation_79) {

    // Test normal operation with one match point

    double result = inliers_processor.ScoreErrorHomography();

    EXPECT_EQ(result, 0.0); // Assuming the homography error is within threshold and cheirality check passes

}



TEST_F(ImagePairInliersTest_79, ScoreErrorHomography_BoundaryCondition_NoMatches_79) {

    // Test boundary condition with no matches

    image_pair.matches.resize(0, 2);

    double result = inliers_processor.ScoreErrorHomography();

    EXPECT_EQ(result, 0.0); // No matches, score should be zero

}



TEST_F(ImagePairInliersTest_79, ScoreErrorHomography_BoundaryCondition_OutOfThreshold_79) {

    // Test boundary condition with match point out of threshold

    image_pair.matches(0, 1) = 1; // Modify the feature index to make error exceed threshold

    double result = inliers_processor.ScoreErrorHomography();

    EXPECT_EQ(result, options.max_epipolar_error_H * options.max_epipolar_error_H); // Error exceeds threshold, score should be max_threshold^2

}



TEST_F(ImagePairInliersTest_79, ScoreErrorHomography_ErrorWithinThreshold_CheiralityPass_79) {

    // Test normal operation with match point within threshold and cheirality check passes

    double result = inliers_processor.ScoreErrorHomography();

    EXPECT_EQ(result, 0.0); // Assuming the homography error is within threshold and cheirality check passes

}



TEST_F(ImagePairInliersTest_79, ScoreErrorHomography_ErrorWithinThreshold_CheiralityFail_79) {

    // Test normal operation with match point within threshold but cheirality check fails

    image_pair.H(0, 0) = 1e6; // Modify H to make cheirality fail

    double result = inliers_processor.ScoreErrorHomography();

    EXPECT_EQ(result, options.max_epipolar_error_H * options.max_epipolar_error_H); // Cheirality fails, score should be max_threshold^2

}



TEST_F(ImagePairInliersTest_79, ScoreErrorHomography_MultipleMatches_AllWithinThreshold_CheiralityPass_79) {

    // Test normal operation with multiple match points all within threshold and cheirality check passes

    image_pair.matches.resize(2, 2);

    image_pair.matches << 0, 0,

                         1, 1;

    image1.features.push_back(Eigen::Vector2d(0.5, 0.6));

    image2.features.push_back(Eigen::Vector2d(0.7, 0.8));



    double result = inliers_processor.ScoreErrorHomography();

    EXPECT_EQ(result, 0.0); // Assuming the homography error is within threshold and cheirality check passes for all matches

}



TEST_F(ImagePairInliersTest_79, ScoreErrorHomography_MultipleMatches_AllWithinThreshold_CheiralityFail_79) {

    // Test normal operation with multiple match points all within threshold but cheirality check fails

    image_pair.matches.resize(2, 2);

    image_pair.matches << 0, 0,

                         1, 1;

    image1.features.push_back(Eigen::Vector2d(0.5, 0.6));

    image2.features.push_back(Eigen::Vector2d(0.7, 0.8));



    image_pair.H(0, 0) = 1e6; // Modify H to make cheirality fail

    double result = inliers_processor.ScoreErrorHomography();

    EXPECT_EQ(result, options.max_epipolar_error_H * options.max_epipolar_error_H * 2); // Cheirality fails for all matches, score should be max_threshold^2 * num_matches

}



TEST_F(ImagePairInliersTest_79, ScoreErrorHomography_MultipleMatches_SomeWithinThreshold_CheiralityPassAndFail_79) {

    // Test normal operation with multiple match points some within threshold and cheirality check passes/fails

    image_pair.matches.resize(2, 2);

    image_pair.matches << 0, 0,

                         1, 1;

    image1.features.push_back(Eigen::Vector2d(0.5, 0.6));

    image2.features.push_back(Eigen::Vector2d(0.7, 0.8));



    image_pair.H(0, 0) = 1e6; // Modify H to make cheirality fail for one match

    double result = inliers_processor.ScoreErrorHomography();

    EXPECT_EQ(result, options.max_epipolar_error_H * options.max_epipolar_error_H); // Cheirality fails for one match, score should be max_threshold^2

}
